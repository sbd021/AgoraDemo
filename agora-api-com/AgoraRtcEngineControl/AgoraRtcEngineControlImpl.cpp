// AgoraRtcEngineControlImpl.cpp : Implementation of CAgoraRtcEngineControlImpl

#include "stdafx.h"
#include "AgoraRtcEngineControlImpl.h"
#include "AgoraRtcEngineControlEventHandler.h"
#include "cJSON.h"
#include <string>
#include <comutil.h>
#pragma comment(lib, "comsuppw.lib")


using namespace agora::commons::cjson;
typedef agora::rtc::IRtcEngine* (AGORA_CALL *PFN_CreateAgoraRtcEngine)();

extern HINSTANCE g_hInstance;

static HINSTANCE MyLoadLibrary(LPCTSTR dllname)
{
	TCHAR path[MAX_PATH];
	GetModuleFileName(g_hInstance, path, MAX_PATH);
	auto p = _tcsrchr(path, TEXT('\\'));
	_tcscpy(p + 1, dllname);
	HINSTANCE hDll = LoadLibrary(path);
	if (hDll)
		return hDll;

	hDll = LoadLibrary(dllname);
	return hDll;
}

class AgoraRtcEngineLib
{
public:
	AgoraRtcEngineLib()
		:m_firstInit(true)
		, m_pfnCreateAgoraRtcEngine(nullptr)
	{
	}
	bool initialize()
	{
		if (!m_firstInit)
			return isValid();
		m_firstInit = false;
		m_hDll = MyLoadLibrary(TEXT("agorartc.dll"));
		if (m_hDll)
		{
			m_pfnCreateAgoraRtcEngine = (PFN_CreateAgoraRtcEngine)GetProcAddress(m_hDll, "createAgoraRtcEngine");
		}
		return isValid();
	}
	~AgoraRtcEngineLib()
	{
		if (m_hDll)
			FreeLibrary(m_hDll);
	}
	bool isValid()
	{
		return	m_pfnCreateAgoraRtcEngine != nullptr;
	}
	agora::rtc::IRtcEngine* createEngine()
	{
		return m_pfnCreateAgoraRtcEngine ? m_pfnCreateAgoraRtcEngine() : nullptr;
	}
private:
	bool m_firstInit;
	HINSTANCE m_hDll;
	PFN_CreateAgoraRtcEngine m_pfnCreateAgoraRtcEngine;
};

using namespace agora::rtc;

static std::string to_std_string(const wchar_t* pstr, long wslen)
{
	int len = ::WideCharToMultiByte(CP_UTF8, 0, pstr, wslen, NULL, 0, NULL, NULL);

	std::string dblstr(len, '\0');
	len = ::WideCharToMultiByte(CP_UTF8, 0 /* no flags */,
		pstr, wslen /* not necessary NULL-terminated */,
		&dblstr[0], len,
		NULL, NULL /* no default char */);

	return dblstr;
}

static std::string to_std_string(BSTR bstr)
{
	if (!bstr) return std::string();
	int wslen = ::SysStringLen(bstr);
	return to_std_string((wchar_t*)bstr, wslen);
}

static BSTR from_std_string(const std::string& str)
{
	int wslen = ::MultiByteToWideChar(CP_UTF8, 0 /* no flags */,
		str.data(), str.length(),
		NULL, 0);

	BSTR wsdata = ::SysAllocStringLen(NULL, wslen);
	::MultiByteToWideChar(CP_UTF8, 0 /* no flags */,
		str.data(), str.length(),
		wsdata, wslen);
	return wsdata;
}

// CAgoraRtcEngineControlImpl
CAgoraRtcEngineControlImpl::CAgoraRtcEngineControlImpl()
{
}

CAgoraRtcEngineControlImpl::~CAgoraRtcEngineControlImpl()
{

}

HRESULT CAgoraRtcEngineControlImpl::FinalConstruct()
{
	return S_OK;
}

void CAgoraRtcEngineControlImpl::FinalRelease()
{
	//call release2() instead of release to wait for all resources geting freed
	auto p = m_rtcEngine.release();
	if (p)
		p->sync_release();
	m_rtcEngine.reset();
}

STDMETHODIMP CAgoraRtcEngineControlImpl::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] =
	{
		&IID_IAgoraRtcEngineControl
	};

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::release()
{
	if (m_rtcEngine)
	{
		m_rtcEngine.reset();
	}

	return S_OK;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::initialize(BSTR appId, LONG* result)
{
//	::MessageBox(NULL, L"Attach to the process to start debugging", L"Agora Rtc Engine Control", MB_OK);
	std::string appId1 = to_std_string(appId);
	if (appId1.empty())
	{
		*result = ERR_INVALID_ARGUMENT;
		return ERROR_INVALID_PARAMETER;
	}

	if (m_rtcEngine)
	{
		*result = 0;
		return S_OK;
	}
	if (!m_lib)
	{
		m_lib.reset(new AgoraRtcEngineLib);
		if (!m_lib->initialize())
		{
			*result = ERR_FAILED;
			return ERROR_MOD_NOT_FOUND;
		}
	}
	m_rtcEngine.reset(m_lib->createEngine());


    m_eh.reset(new RtcEngineEventHandlerImpl(*this));
	int r;
	RtcEngineContext context;
	context.appId = appId1.c_str();
	context.eventHandler = m_eh.get();
	r = m_rtcEngine->initialize(context);

	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::joinChannel(BSTR channelKey, BSTR channelName, BSTR info, ULONG uid, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	std::string channel1 = to_std_string(channelName);
	if (channel1.empty())
		return ERROR_INVALID_PARAMETER;

	std::string key1 = to_std_string(channelKey);
	std::string info1 = to_std_string(info);
	int r = m_rtcEngine->joinChannel(key1.c_str(), channel1.c_str(), info1.c_str(), (agora::rtc::uid_t)uid);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::leaveChannel(LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	int r = m_rtcEngine->leaveChannel();
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::setParameters(BSTR parameters, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	std::string parameters1 = to_std_string(parameters);
	AParameter ap(*m_rtcEngine);
	int r = ap->setParameters(parameters1.c_str());
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::muteLocalAudioStream(VARIANT_BOOL muted, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.muteLocalAudioStream(muted == VARIANT_TRUE ? true : false);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::muteAllRemoteAudioStreams(VARIANT_BOOL muted, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.muteAllRemoteAudioStreams(muted == VARIANT_TRUE ? true : false);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::muteRemoteAudioStream(ULONG uid, VARIANT_BOOL muted, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.muteRemoteAudioStream(uid, muted == VARIANT_TRUE ? true : false);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::setChannelProfile(enum ChannelProfile profile, LONG* result)
{
    if (!m_rtcEngine)
    {
        *result = ERR_NOT_INITIALIZED;
        return ERROR_NOT_READY;
    }
    int r = m_rtcEngine->setChannelProfile((CHANNEL_PROFILE_TYPE)profile);
    *result = r;
    return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::setClientRole(enum ClientRole role, BSTR permissionKey, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
    std::string key = to_std_string(permissionKey);
    int r = m_rtcEngine->setClientRole((CLIENT_ROLE_TYPE)role, key.c_str());
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::renewChannelKey(BSTR channelKey, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	std::string key1 = to_std_string(channelKey);
	if (key1.empty())
		return ERROR_INVALID_PARAMETER;

	int r = m_rtcEngine->renewChannelKey(key1.c_str());
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::startEchoTest(LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	int r = m_rtcEngine->startEchoTest();
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::stopEchoTest(LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	int r = m_rtcEngine->stopEchoTest();
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::enableLastmileTest(LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	int r = m_rtcEngine->enableLastmileTest();
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::disableLastmileTest(LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	int r = m_rtcEngine->disableLastmileTest();
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::getCallId(BSTR* callId)
{
	if (!m_rtcEngine)
		return ERROR_NOT_READY;
	agora::util::AString url;
	int r = m_rtcEngine->getCallId(url);
	if (!r && !url->empty())
	{
		_bstr_t str(url->c_str());
		*callId = str.Detach();
		return S_OK;
	}
	return ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::rate(BSTR callId, LONG rating, BSTR description, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	std::string callId1 = to_std_string(callId);
	if (callId1.empty())
	{
		*result = ERR_INVALID_ARGUMENT;
		return ERROR_INVALID_PARAMETER;
	}

	int r = m_rtcEngine->rate(callId1.c_str(), rating, to_std_string(description).c_str());
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::complain(BSTR callId, BSTR description, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	std::string callId1 = to_std_string(callId);
	if (callId1.empty())
	{
		*result = ERR_INVALID_ARGUMENT;
		return ERROR_INVALID_PARAMETER;
	}
	int r = m_rtcEngine->complain(callId1.c_str(), to_std_string(description).c_str());
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::enableVideo(LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	int r = m_rtcEngine->enableVideo();
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::disableVideo(LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	int r = m_rtcEngine->disableVideo();
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::startPreview(LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	int r = m_rtcEngine->startPreview();
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::stopPreview(LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	int r = m_rtcEngine->stopPreview();
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::setVideoProfile(enum VideoProfile profile, VARIANT_BOOL swapWidthAndHeight, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
    int r = m_rtcEngine->setVideoProfile((VIDEO_PROFILE_TYPE)profile, swapWidthAndHeight == VARIANT_TRUE ? true : false);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::setupLocalVideo(LONG_PTR** view, enum RenderMode renderMode, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	agora::rtc::VideoCanvas canvas((view_t)view, (int)renderMode, 0);
	int r = m_rtcEngine->setupLocalVideo(canvas);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::setupRemoteVideo(ULONG uid, LONG_PTR** view, enum RenderMode renderMode, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	agora::rtc::VideoCanvas canvas((view_t)view, (int)renderMode, uid);
	int r = m_rtcEngine->setupRemoteVideo(canvas);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::muteLocalVideoStream(VARIANT_BOOL muted, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.muteLocalVideoStream(muted == VARIANT_TRUE ? true : false);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::muteAllRemoteVideoStreams(VARIANT_BOOL muted, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.muteAllRemoteVideoStreams(muted == VARIANT_TRUE ? true : false);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::muteRemoteVideoStream(ULONG uid, VARIANT_BOOL muted, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.muteRemoteVideoStream(uid, muted == VARIANT_TRUE ? true : false);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::startAudioRecording(BSTR filePath, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}

	std::string filePath1 = to_std_string(filePath);
	if (filePath1.empty())
		return ERROR_INVALID_PARAMETER;

	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.startAudioRecording(filePath1.c_str());
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::stopAudioRecording(LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}

	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.stopAudioRecording();
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::setEncryptionSecret(BSTR secret, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	int r = m_rtcEngine->setEncryptionSecret(to_std_string(secret).c_str());
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::setEncryptionMode(BSTR encryptionMode, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	int r = m_rtcEngine->setEncryptionMode(to_std_string(encryptionMode).c_str());
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::setLogFile(BSTR filePath, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}

	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.setLogFile(to_std_string(filePath).c_str());
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::setLogFilter(ULONG filter, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}

	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.setLogFilter(filter);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::setLocalRenderMode(RenderMode renderMode, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}

	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.setLocalRenderMode((RENDER_MODE_TYPE)renderMode);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::setRemoteRenderMode(ULONG uid, RenderMode renderMode, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}

	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.setRemoteRenderMode(uid, (RENDER_MODE_TYPE)renderMode);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::setPlaybackDeviceVolume(LONG volume, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}

	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.setPlaybackDeviceVolume(volume);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::startRecordingService(BSTR recordingKey, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}

	std::string key1 = to_std_string(recordingKey);
	if (key1.empty())
		return ERROR_INVALID_PARAMETER;

	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.startRecordingService(key1.c_str());
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::stopRecordingService(BSTR recordingKey, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}

	std::string key1 = to_std_string(recordingKey);
	if (key1.empty())
		return ERROR_INVALID_PARAMETER;

	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.stopRecordingService(key1.c_str());
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::refreshRecordingServiceStatus(LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}

	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.refreshRecordingServiceStatus();
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::startScreenCapture(LONG_PTR** window, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.startScreenCapture((HWND)window);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::setScreenCaptureWindow(LONG_PTR** window, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.setScreenCaptureWindow((HWND)window);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::stopScreenCapture(LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.stopScreenCapture();
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::startAudioMixing(BSTR filePath, VARIANT_BOOL loopback, VARIANT_BOOL replace, LONG cycle, LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}
	std::string filePath1 = to_std_string(filePath);
	if (filePath1.empty())
		return ERROR_INVALID_PARAMETER;

	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.startAudioMixing(filePath1.c_str(), loopback == VARIANT_TRUE ? true : false, replace == VARIANT_TRUE ? true : false, cycle);
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::stopAudioMixing(LONG* result)
{
	if (!m_rtcEngine)
	{
		*result = ERR_NOT_INITIALIZED;
		return ERROR_NOT_READY;
	}

	RtcEngineParameters rep(*m_rtcEngine);
	int r = rep.stopAudioMixing();
	*result = r;
	return !r ? S_OK : ERROR_GEN_FAILURE;
}

template<class T>
static HRESULT processDevices(T* pCollection, BSTR* result)
{
    if (!pCollection)
        return ERROR_GEN_FAILURE;
    agora::util::AutoPtr<T> spCollection(pCollection);

    cJSON* devices = cJSON_CreateArray();

    char name[MAX_DEVICE_ID_LENGTH], guid[MAX_DEVICE_ID_LENGTH];
    int count = spCollection->getCount();
    for (int i = 0; i < count; i++)
    {
        if (!spCollection->getDevice(i, name, guid))
        {
            cJSON* item = cJSON_CreateObject();
            cJSON_AddItemToObject(item, "deviceId", cJSON_CreateString(guid));
            cJSON_AddItemToObject(item, "deviceName", cJSON_CreateString(name));
            cJSON_AddItemToArray(devices, item);
        }
    }
    char* s = cJSON_PrintUnformatted(devices);
    _bstr_t str(s);
    free(s);
    cJSON_Delete(devices);
    *result = str.Detach();
    return S_OK;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::enumeratePlaybackDevices(BSTR* result)
{
    if (!m_rtcEngine)
    {
        *result = nullptr;
        return ERROR_NOT_READY;
    }

    AAudioDeviceManager adm(*m_rtcEngine);
    if (adm)
        return processDevices(adm->enumeratePlaybackDevices(), result);
    else
    {
        return ERROR_GEN_FAILURE;
    }
    return S_OK;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::enumerateRecordingDevices(BSTR* result)
{
    if (!m_rtcEngine)
    {
        *result = nullptr;
        return ERROR_NOT_READY;
    }

    AAudioDeviceManager adm(*m_rtcEngine);
    if (adm)
        return processDevices(adm->enumerateRecordingDevices(), result);
    else
    {
        return ERROR_GEN_FAILURE;
    }
    return S_OK;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::enumerateVideoCaptureDevices(BSTR* result)
{
    if (!m_rtcEngine)
    {
        *result = nullptr;
        return ERROR_NOT_READY;
    }

    AVideoDeviceManager vdm(*m_rtcEngine);
    if (vdm)
        return processDevices(vdm->enumerateVideoDevices(), result);
    else
    {
        return ERROR_GEN_FAILURE;
    }
    return S_OK;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::setPlaybackDevice(BSTR deviceId, LONG* result)
{
    if (!m_rtcEngine)
    {
        *result = ERR_NOT_INITIALIZED;
        return ERROR_NOT_READY;
    }
    std::string did = to_std_string(deviceId);
    if (did.empty())
        return ERROR_INVALID_PARAMETER;

    int r = 0;
    AAudioDeviceManager adm(*m_rtcEngine);
    if (adm)
    {
        r = adm->setPlaybackDevice(did.c_str());
    }
    return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::setRecordingDevice(BSTR deviceId, LONG* result)
{
    if (!m_rtcEngine)
    {
        *result = ERR_NOT_INITIALIZED;
        return ERROR_NOT_READY;
    }
    std::string did = to_std_string(deviceId);
    if (did.empty())
        return ERROR_INVALID_PARAMETER;

    int r = 0;
    AAudioDeviceManager adm(*m_rtcEngine);
    if (adm)
    {
        r = adm->setRecordingDevice(did.c_str());
    }
    return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::setVideoCaptureDevice(BSTR deviceId, LONG* result)
{
    if (!m_rtcEngine)
    {
        *result = ERR_NOT_INITIALIZED;
        return ERROR_NOT_READY;
    }
    std::string did = to_std_string(deviceId);
    if (did.empty())
        return ERROR_INVALID_PARAMETER;

    int r = 0;
    AVideoDeviceManager vdm(*m_rtcEngine);
    if (vdm)
    {
        r = vdm->setDevice(did.c_str());
    }
    return !r ? S_OK : ERROR_GEN_FAILURE;
}

STDMETHODIMP CAgoraRtcEngineControlImpl::get_fireEventInInitializationThread(VARIANT_BOOL* pVal)
{
	return S_FALSE;
}


STDMETHODIMP CAgoraRtcEngineControlImpl::put_fireEventInInitializationThread(VARIANT_BOOL newVal)
{
    return S_FALSE;
}
