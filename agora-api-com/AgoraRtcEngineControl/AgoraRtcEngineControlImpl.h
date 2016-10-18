// AgoraRtcEngineControlImpl.h : Declaration of the CAgoraRtcEngineControlImpl

#pragma once
#include "resource.h"       // main symbols



#include "AgoraRtcEngineControl_i.h"
#include "_IAgoraRtcEngineControlEvents_CP.h"
#include <memory>
#include <IAgoraRtcEngine.h>



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

#define AGORA_RTC_MAJOR_VERSION 1
#define AGORA_RTC_MINOR_VERSION 0

class AgoraRtcEngineLib;

// CAgoraRtcEngineControlImpl

class ATL_NO_VTABLE CAgoraRtcEngineControlImpl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAgoraRtcEngineControlImpl, &CLSID_AgoraRtcEngineControl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CAgoraRtcEngineControlImpl>,
	public CProxy_IAgoraRtcEngineControlEvents<CAgoraRtcEngineControlImpl>,
	public IDispatchImpl<IAgoraRtcEngineControl, &IID_IAgoraRtcEngineControl, &LIBID_AgoraRtcEngineControlLib, AGORA_RTC_MAJOR_VERSION, AGORA_RTC_MINOR_VERSION>,
	public IObjectSafetyImpl<CAgoraRtcEngineControlImpl, INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IProvideClassInfo2Impl<&CLSID_AgoraRtcEngineControl, &DIID__IAgoraRtcEngineControlEvents, &LIBID_AgoraRtcEngineControlLib, AGORA_RTC_MAJOR_VERSION, AGORA_RTC_MINOR_VERSION>
{
public:
	CAgoraRtcEngineControlImpl();
	~CAgoraRtcEngineControlImpl();

DECLARE_REGISTRY_RESOURCEID(IDR_AGORARTCENGINECONTROLIMPL)


BEGIN_COM_MAP(CAgoraRtcEngineControlImpl)
	COM_INTERFACE_ENTRY(IAgoraRtcEngineControl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CAgoraRtcEngineControlImpl)
	CONNECTION_POINT_ENTRY(__uuidof(_IAgoraRtcEngineControlEvents))
END_CONNECTION_POINT_MAP()
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();
private:
	agora::util::AutoPtr<agora::rtc::IRtcEngine> m_rtcEngine;
	std::unique_ptr<AgoraRtcEngineLib> m_lib;
	std::unique_ptr<agora::rtc::IRtcEngineEventHandler> m_eh;
public:
	STDMETHOD(release)();
	STDMETHOD(initialize)(BSTR appId, LONG* result);
	STDMETHOD(joinChannel)(BSTR channelKey, BSTR channelName, BSTR info, ULONG uid, LONG* result);
	STDMETHOD(leaveChannel)(LONG* result);
	STDMETHOD(setParameters)(BSTR parameters, LONG* result);
	STDMETHOD(muteLocalAudioStream)(VARIANT_BOOL muted, LONG* result);
	STDMETHOD(muteAllRemoteAudioStreams)(VARIANT_BOOL muted, LONG* result);
	STDMETHOD(muteRemoteAudioStream)(ULONG uid, VARIANT_BOOL muted, LONG* result);
    STDMETHOD(setChannelProfile)(enum ChannelProfile profile, LONG* result);
    STDMETHOD(setClientRole)(enum ClientRole role, BSTR permissionKey, LONG* result);
	STDMETHOD(renewChannelKey)(BSTR channelKey, LONG* result);
	STDMETHOD(startEchoTest)(LONG* result);
	STDMETHOD(stopEchoTest)(LONG* result);
	STDMETHOD(enableLastmileTest)(LONG* result);
	STDMETHOD(disableLastmileTest)(LONG* result);
	STDMETHOD(getCallId)(BSTR* callId);
	STDMETHOD(rate)(BSTR callId, LONG rating, BSTR description, LONG* result);
	STDMETHOD(complain)(BSTR callId, BSTR description, LONG* result);
	STDMETHOD(enableVideo)(LONG* result);
	STDMETHOD(disableVideo)(LONG* result);
	STDMETHOD(startPreview)(LONG* result);
	STDMETHOD(stopPreview)(LONG* result);
    STDMETHOD(setVideoProfile)(enum VideoProfile profile, VARIANT_BOOL swapWidthAndHeight, LONG* result);
	STDMETHOD(setupLocalVideo)(LONG_PTR** view, enum RenderMode renderMode, LONG* result);
	STDMETHOD(setupRemoteVideo)(ULONG uid, LONG_PTR** view, enum RenderMode renderMode, LONG* result);
	STDMETHOD(muteLocalVideoStream)(VARIANT_BOOL muted, LONG* result);
	STDMETHOD(muteAllRemoteVideoStreams)(VARIANT_BOOL muted, LONG* result);
	STDMETHOD(muteRemoteVideoStream)(ULONG uid, VARIANT_BOOL muted, LONG* result);
	STDMETHOD(startAudioRecording)(BSTR filePath, LONG* result);
	STDMETHOD(stopAudioRecording)(LONG* result);
	STDMETHOD(setEncryptionSecret)(BSTR secret, LONG* result);
	STDMETHOD(setEncryptionMode)(BSTR encryptionMode, LONG* result);
	STDMETHOD(setLogFile)(BSTR filePath, LONG* result);
	STDMETHOD(setLogFilter)(ULONG filter, LONG* result);
	STDMETHOD(setLocalRenderMode)(RenderMode renderMode, LONG* result);
	STDMETHOD(setRemoteRenderMode)(ULONG uid, RenderMode renderMode, LONG* result);
	STDMETHOD(setPlaybackDeviceVolume)(LONG volume, LONG* result);
	STDMETHOD(startRecordingService)(BSTR recordingKey, LONG* result);
	STDMETHOD(stopRecordingService)(BSTR recordingKey, LONG* result);
	STDMETHOD(refreshRecordingServiceStatus)(LONG* result);
	STDMETHOD(startScreenCapture)(LONG_PTR** window, LONG* result);
	STDMETHOD(setScreenCaptureWindow)(LONG_PTR** window, LONG* result);
	STDMETHOD(stopScreenCapture)(LONG* result);
	STDMETHOD(startAudioMixing)(BSTR filePath, VARIANT_BOOL loopback, VARIANT_BOOL replace, LONG cycle, LONG* result);
	STDMETHOD(stopAudioMixing)(LONG* result);
    STDMETHOD(enumeratePlaybackDevices)(BSTR* result);
    STDMETHOD(enumerateRecordingDevices)(BSTR* result);
    STDMETHOD(enumerateVideoCaptureDevices)(BSTR* result);
    STDMETHOD(setPlaybackDevice)(BSTR deviceId, LONG* result);
    STDMETHOD(setRecordingDevice)(BSTR deviceId, LONG* result);
    STDMETHOD(setVideoCaptureDevice)(BSTR deviceId, LONG* result);

	STDMETHOD(get_fireEventInInitializationThread)(VARIANT_BOOL* pVal);
	STDMETHOD(put_fireEventInInitializationThread)(VARIANT_BOOL newVal);

};

OBJECT_ENTRY_AUTO(__uuidof(AgoraRtcEngineControl), CAgoraRtcEngineControlImpl)
