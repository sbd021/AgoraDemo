//
//  Agora Rtc Engine SDK
//
//  Created by Sting Feng in 2015-02.
//  Copyright (c) 2015 Agora IO. All rights reserved.
//

#ifndef AGORA_RTC_ENGINE_H
#define AGORA_RTC_ENGINE_H

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define AGORA_CALL __cdecl
#if defined(AGORARTC_EXPORT)
#define AGORA_API extern "C" __declspec(dllexport)
#else
#define AGORA_API extern "C" __declspec(dllimport)
#endif
#else
#define AGORA_API extern "C"
#define AGORA_CALL
#endif

namespace agora {

	namespace util {

template<class T>
class AutoPtr {
	typedef T value_type;
	typedef T* pointer_type;
public:
	AutoPtr(pointer_type p=0)
		:ptr_(p)
	{}
	~AutoPtr() {
		if (ptr_)
			ptr_->release();
	}
	operator bool() const { return ptr_ != (pointer_type)0; }
	value_type& operator*() const {
		return *get();
	}

	pointer_type operator->() const {
		return get();
	}

	pointer_type get() const {
		return ptr_;
	}

	pointer_type release() {
		pointer_type tmp = ptr_;
		ptr_ = 0;
		return tmp;
	}

	void reset(pointer_type ptr = 0) {
		if (ptr != ptr_ && ptr_)
			ptr_->release();
		ptr_ = ptr;
	}
private:
	AutoPtr(const AutoPtr&);
	AutoPtr& operator=(const AutoPtr&);
private:
	pointer_type ptr_;
};
class IString {
public:
	virtual bool empty() const = 0;
	virtual const char* c_str() = 0;
	virtual const char* data() = 0;
	virtual size_t length() = 0;
	virtual void release() = 0;
};
typedef AutoPtr<IString> AString;

	}//namespace util
namespace rtc {
	typedef unsigned int uid_t;
	typedef void* view_t;

enum INTERFACE_ID_TYPE
{
	AGORA_IID_AUDIO_DEVICE_MANAGER = 1,
	AGORA_IID_VIDEO_DEVICE_MANAGER = 2,
};

enum WARN_CODE_TYPE
{
	WARN_NO_AVAILABLE_CHANNEL = 103,
	WARN_LOOKUP_CHANNEL_TIMEOUT = 104,
	WARN_LOOKUP_CHANNEL_REJECTED = 105,
	WARN_OPEN_CHANNEL_TIMEOUT = 106,
	WARN_OPEN_CHANNEL_REJECTED = 107,
	WARN_REQUEST_DEFERRED = 108,
	WARN_ADM_RUNTIME_PLAYOUT_WARNING = 1014,
	WARN_ADM_RUNTIME_RECORDING_WARNING = 1016,
	WARN_ADM_RECORD_AUDIO_SILENCE = 1019,
	WARN_ADM_PLAYOUT_ABNORMAL_FREQUENCY = 1020,
	WARN_ADM_RECORD_ABNORMAL_FREQUENCY = 1021,
};

enum ERROR_CODE_TYPE
{
	ERR_OK = 0,
	//1~1000
	ERR_FAILED = 1,
	ERR_INVALID_ARGUMENT = 2,
	ERR_NOT_READY = 3,
	ERR_NOT_SUPPORTED = 4,
	ERR_REFUSED = 5,
	ERR_BUFFER_TOO_SMALL = 6,
	ERR_NOT_INITIALIZED = 7,
	ERR_INVALID_VIEW = 8,
	ERR_NO_PERMISSION = 9,
	ERR_TIMEDOUT = 10,
	ERR_CANCELED = 11,
	ERR_TOO_OFTEN = 12,
	ERR_BIND_SOCKET = 13,
	ERR_NET_DOWN = 14,
	ERR_NET_NOBUFS = 15,
	ERR_INIT_VIDEO = 16,
	ERR_JOIN_CHANNEL_REJECTED = 17,
	ERR_LEAVE_CHANNEL_REJECTED = 18,
	ERR_INVALID_VENDOR_KEY = 101,
	ERR_INVALID_CHANNEL_NAME = 102,
	ERR_DYNAMIC_KEY_TIMEOUT = 109,
	//1001~2000
	ERR_LOAD_MEDIA_ENGINE = 1001,
	ERR_START_CALL = 1002,
	ERR_START_CAMERA = 1003,
	ERR_START_VIDEO_RENDER = 1004,
	ERR_ADM_GENERAL_ERROR = 1005,
	ERR_ADM_JAVA_RESOURCE = 1006,
	ERR_ADM_SAMPLE_RATE = 1007,
	ERR_ADM_INIT_PLAYOUT = 1008,
	ERR_ADM_START_PLAYOUT = 1009,
	ERR_ADM_STOP_PLAYOUT = 1010,
	ERR_ADM_INIT_RECORDING = 1011,
	ERR_ADM_START_RECORDING = 1012,
	ERR_ADM_STOP_RECORDING = 1013,
	ERR_ADM_RUNTIME_PLAYOUT_ERROR = 1015,
	ERR_ADM_RUNTIME_RECORDING_ERROR = 1017,
    ERR_ADM_RECORD_AUDIO_FAILED = 1018,
};

enum LOG_FILTER_TYPE
{
	LOG_FILTER_DEBUG = 0x0800,
	LOG_FILTER_INFO = 0x0001,
	LOG_FILTER_WARN = 0x0002,
	LOG_FILTER_ERROR = 0x0004,
	LOG_FILTER_CRITICAL = 0x0008,
};

enum MAX_DEVICE_ID_LENGTH_TYPE
{
	MAX_DEVICE_ID_LENGTH = 128
};

enum QUALITY_REPORT_FORMAT_TYPE
{
	QUALITY_REPORT_JSON = 0,
	QUALITY_REPORT_HTML = 1,
};

enum MEDIA_ENGINE_EVENT_CODE_TYPE
{
	MEDIA_ENGINE_RECORDING_ERROR = 0,
	MEDIA_ENGINE_PLAYOUT_ERROR = 1,
	MEDIA_ENGINE_RECORDING_WARNING = 2,
	MEDIA_ENGINE_PLAYOUT_WARNING = 3
};

enum MEDIA_DEVICE_STATE_TYPE
{
	MEDIA_DEVICE_STATE_ACTIVE = 1,
	MEDIA_DEVICE_STATE_DISABLED = 2,
	MEDIA_DEVICE_STATE_NOT_PRESENT = 4,
	MEDIA_DEVICE_STATE_UNPLUGGED = 8
};

enum MEDIA_DEVICE_TYPE
{
	UNKNOWN_AUDIO_DEVICE = -1,
	AUDIO_PLAYOUT_DEVICE = 0,
	AUDIO_RECORDING_DEVICE = 1,
	VIDEO_RENDER_DEVICE = 2,
	VIDEO_CAPTURE_DEVICE = 3,
};

enum QUALITY_TYPE
{
	QUALITY_UNKNOWN = 0,
	QUALITY_EXCELLENT = 1,
	QUALITY_GOOD = 2,
	QUALITY_POOR = 3,
	QUALITY_BAD = 4,
	QUALITY_VBAD = 5,
	QUALITY_DOWN = 6,
};

enum RENDER_MODE_TYPE
{
	RENDER_MODE_HIDDEN = 1,
	RENDER_MODE_FIT = 2,
	RENDER_MODE_ADAPTIVE = 3,
};

enum VIDEO_PROFILE_TYPE
{                                   // res       fps  kbps
	VIDEO_PROFILE_120P = 0,         // 160x120   15   80
	VIDEO_PROFILE_120P_2 = 1,		// 120x160   15   80
	VIDEO_PROFILE_120P_3 = 2,		// 120x120   15   60
	VIDEO_PROFILE_180P = 10,		// 320x180   15   160
	VIDEO_PROFILE_180P_2 = 11,		// 180x320   15   160
	VIDEO_PROFILE_180P_3 = 12,		// 180x180   15   120
	VIDEO_PROFILE_240P = 20,		// 320x240   15   200
	VIDEO_PROFILE_240P_2 = 21,		// 240x320   15   200
	VIDEO_PROFILE_240P_3 = 22,		// 240x240   15   160
	VIDEO_PROFILE_360P = 30,		// 640x360   15   400
	VIDEO_PROFILE_360P_2 = 31,		// 360x640   15   400
	VIDEO_PROFILE_360P_3 = 32,		// 360x360   15   300
	VIDEO_PROFILE_360P_4 = 33,		// 640x360   30   800
	VIDEO_PROFILE_360P_5 = 34,		// 360x640   30   800
	VIDEO_PROFILE_360P_6 = 35,		// 360x360   30   600
	VIDEO_PROFILE_480P = 40,		// 640x480   15   500
	VIDEO_PROFILE_480P_2 = 41,		// 480x640   15   500
	VIDEO_PROFILE_480P_3 = 42,		// 480x480   15   400
	VIDEO_PROFILE_480P_4 = 43,		// 640x480   30   1000
	VIDEO_PROFILE_480P_5 = 44,		// 480x640   30   1000
	VIDEO_PROFILE_480P_6 = 45,		// 480x480   30   800
	VIDEO_PROFILE_720P = 50,		// 1280x720  15   1000
	VIDEO_PROFILE_720P_2 = 51,		// 720x1280  15   1000
	VIDEO_PROFILE_720P_3 = 52,		// 1280x720  30   2000
	VIDEO_PROFILE_720P_4 = 53,		// 720x1280  30   2000
	VIDEO_PROFILE_1080P = 60,		// 1920x1080 15   1500
	VIDEO_PROFILE_1080P_2 = 61,		// 1080x1920 15   1500
	VIDEO_PROFILE_1080P_3 = 62,		// 1920x1080 30   3000
	VIDEO_PROFILE_1080P_4 = 63,		// 1080x1920 30   3000
	VIDEO_PROFILE_1080P_5 = 64,		// 1920x1080 60   6000
	VIDEO_PROFILE_1080P_6 = 65,		// 1080x1920 60   6000
	VIDEO_PROFILE_4K = 70,			// 3840x2160 30   8000
	VIDEO_PROFILE_4K_2 = 71,		// 2160x3080 30   8000
	VIDEO_PROFILE_4K_3 = 72,		// 3840x2160 60   16000
	VIDEO_PROFILE_4K_4 = 73,		// 2160x3840 60   16000
	VIDEO_PROFILE_DEFAULT = VIDEO_PROFILE_360P,
};

enum CHANNEL_PROFILE_TYPE
{
	CHANNEL_PROFILE_FREE = 0,
	CHANNEL_PROFILE_BROADCASTER = 1,
	CHANNEL_PROFILE_AUDIENCE = 2,
};

struct AudioVolumeInfo
{
	uid_t uid;
	unsigned int volume; // [0,255]
};

struct RtcStats
{
	unsigned int duration;
	unsigned int txBytes;
	unsigned int rxBytes;
	unsigned short txKBitRate;
	unsigned short rxKBitRate;
	unsigned int lastmileQuality;
	double cpuAppUsage;
	double cpuTotalUsage;
};

struct LocalVideoStat
{
	// local stat
	int sentBytes;
	int sentFrames;
};

struct RemoteVideoStat
{
	// remote stat
	uid_t uid;
	int delay;
	int renderedFrames;
	int receivedBytes;
};

#if defined(WIN32)
struct VideoCanvas
{
	view_t view;
	int renderMode;
	uid_t uid;

	VideoCanvas()
		: view(NULL)
		, renderMode(RENDER_MODE_HIDDEN)
		, uid(0)
	{}
	VideoCanvas(view_t v, int m, uid_t u)
		: view(v)
		, renderMode(m)
		, uid(u)
	{}
};
#else
struct VideoCanvas;
#endif

class IPacketObserver
{
public:
	struct Packet
	{
		const unsigned char* buffer;
		unsigned int size;
	};
	/**
	* called by sdk before the packet is sent to other participants
	* @param [in,out] packet:
	*      buffer *buffer points the data to be sent
	*      size of buffer data to be sent
	* @return returns true to send out the packet, returns false to discard the packet
	*/
	virtual bool onSendPacket(Packet& packet) = 0;
	/**
	* called by sdk when the packet is received from other participants
	* @param [in,out] packet
	*      buffer *buffer points the data to be sent
	*      size of buffer data to be sent
	* @return returns true to process the packet, returns false to discard the packet
	*/
	virtual bool onReceivePacket(Packet& packet) = 0;
};

class IRtcEngineEventHandler
{
public:
	virtual ~IRtcEngineEventHandler() {}
	virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) {}
	virtual void onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed) {}
	virtual void onWarning(int warn, const char* msg) {}
	virtual void onError(int err, const char* msg) {}
	virtual void onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost) {}
	virtual void onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) {}
	virtual void onLeaveChannel(const RtcStats& stat) {}
	virtual void onRtcStats(const RtcStats& stat) {}
	virtual void onMediaEngineEvent(int evt) {}
	virtual void onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) {}
	virtual void onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) {}
	virtual void onNetworkQuality(int quality) {}
	virtual void onFirstLocalVideoFrame(int width, int height, int elapsed) {}
	virtual void onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed) {}
	virtual void onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed) {}
	virtual void onUserJoined(uid_t uid, int elapsed) {}
	virtual void onUserOffline(uid_t uid) {}
	virtual void onUserMuteAudio(uid_t uid, bool muted) {}
	virtual void onUserMuteVideo(uid_t uid, bool muted) {}
	virtual void onApiCallExecuted(const char* api, int error) {}
	virtual void onLocalVideoStat(int sentBitrate, int sentFrameRate) {}
	virtual void onRemoteVideoStat(uid_t uid, int delay, int receivedBitrate, int receiveFrameRate) {}
    virtual void onCameraReady() {}
	virtual void onVideoStopped() {}
	virtual void onConnectionLost() {}
	virtual void onVendorMessage(uid_t uid, const char* data, size_t length) {}
};

class IVideoDeviceCollection
{
public:
	virtual int getCount() = 0;
	virtual int getDevice(int index, char deviceName[MAX_DEVICE_ID_LENGTH], char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;
	virtual int setDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;
	virtual void release() = 0;
};

class IVideoDeviceManager
{
public:
	virtual IVideoDeviceCollection* enumerateVideoDevices() = 0;
	virtual int setDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;
	virtual int getDevice(char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;
	virtual int startDeviceTest(view_t hwnd) = 0;
	virtual int stopDeviceTest() = 0;
	virtual void release() = 0;
};

class IAudioDeviceCollection
{
public:
	virtual int getCount() = 0;
	virtual int getDevice(int index, char deviceName[MAX_DEVICE_ID_LENGTH], char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;
	virtual int setDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;
	virtual void release() = 0;
};

class IAudioDeviceManager
{
public:
	virtual IAudioDeviceCollection* enumeratePlaybackDevices() = 0;
	virtual IAudioDeviceCollection* enumerateRecordingDevices() = 0;
	virtual int setPlaybackDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;
	virtual int getPlaybackDevice(char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;
	virtual int setPlaybackDeviceVolume(int volume) = 0;
	virtual int getPlaybackDeviceVolume(int *volume) = 0;

	virtual int setRecordingDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;
	virtual int getRecordingDevice(char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;
	virtual int setRecordingDeviceVolume(int volume) = 0;
	virtual int getRecordingDeviceVolume(int *volume) = 0;

	virtual int startPlaybackDeviceTest(const char* testAudioFilePath) = 0;
	virtual int stopPlaybackDeviceTest() = 0;
	
	virtual int startRecordingDeviceTest(int indicationInterval) = 0;
	virtual int stopRecordingDeviceTest() = 0;
	virtual void release() = 0;
};

struct RtcEngineContext
{
	IRtcEngineEventHandler* eventHandler;
	const char* vendorKey;
};


class IRtcEngine
{
public:
	virtual void release() = 0;
	virtual int initialize(const RtcEngineContext& context) = 0;
	virtual int queryInterface(INTERFACE_ID_TYPE iid, void** inter) = 0;
	virtual int joinChannel(const char* key, const char* channel, const char* info, uid_t uid) = 0;
	virtual int leaveChannel() = 0;
	virtual int renewChannelDynamicKey(const char* key) = 0;
	virtual int setChannelProfile(CHANNEL_PROFILE_TYPE profile) = 0;
	virtual int startEchoTest() = 0;
	virtual int stopEchoTest() = 0;
	virtual int enableNetworkTest() = 0;
	virtual int disableNetworkTest() = 0;
	virtual int enableVideo() = 0;
	virtual int disableVideo() = 0;
	virtual int startPreview() = 0;
	virtual int stopPreview() = 0;
	virtual int setVideoProfile(VIDEO_PROFILE_TYPE profile) = 0;
	virtual int setupRemoteVideo(const VideoCanvas& canvas) = 0;
	virtual int setupLocalVideo(const VideoCanvas& canvas) = 0;
	virtual int getCallId(agora::util::AString& callId) = 0;
	virtual int rate(const char* callId, int rating, const char* description) = 0; // 0~10
	virtual int complain(const char* callId, const char* description) = 0;
	virtual int makeQualityReportUrl(const char* channel, uid_t listenerUid, uid_t speakerUid, int format, agora::util::AString& url) = 0;
	virtual int registerPacketObserver(IPacketObserver* observer) = 0;
	virtual int enableVendorMessage() = 0;
	virtual int disableVendorMessage() = 0;
	virtual int sendVendorMessage(const char* data, size_t length) = 0;
};


class IRtcEngineParameter
{
public:
	virtual void release() = 0;
	virtual int setBool(const char* key, bool value) = 0;
	virtual int setInt(const char* key, int value) = 0;
	virtual int setUInt(const char* key, unsigned int value) = 0;
	virtual int setNumber(const char* key, double value) = 0;
	virtual int setString(const char* key, const char* value) = 0;
	virtual int setObject(const char* key, const char* value) = 0;
	virtual int getBool(const char* key, bool& value) = 0;
	virtual int getInt(const char* key, int& value) = 0;
	virtual int getUInt(const char* key, unsigned int& value) = 0;
	virtual int getNumber(const char* key, double& value) = 0;
	virtual int getString(const char* key, agora::util::AString& value) = 0;
	virtual int getObject(const char* key, agora::util::AString& value) = 0;
	virtual int getArray(const char* key, agora::util::AString& value) = 0;
	//magics
	virtual int setParameters(const char* parameters) = 0;
	virtual int setProfile(const char* profile, bool merge) = 0;
};

AGORA_API IRtcEngineParameter* AGORA_CALL createRtcEngineParameter(IRtcEngine& engine);

class AAudioDeviceManager : public agora::util::AutoPtr<IAudioDeviceManager>
{
public:
	AAudioDeviceManager(IRtcEngine& engine)
	{
		IAudioDeviceManager* p;
		if (!engine.queryInterface(AGORA_IID_AUDIO_DEVICE_MANAGER, (void**)&p))
			reset(p);
	}
};

class AVideoDeviceManager : public agora::util::AutoPtr<IVideoDeviceManager>
{
public:
	AVideoDeviceManager(IRtcEngine& engine)
	{
		IVideoDeviceManager* p;
		if (!engine.queryInterface(AGORA_IID_VIDEO_DEVICE_MANAGER, (void**)&p))
			reset(p);
	}
};

class AParameter : public agora::util::AutoPtr<IRtcEngineParameter>
{
public:
	AParameter(IRtcEngine& engine)
		: AutoPtr<IRtcEngineParameter>(createRtcEngineParameter(engine))
	{}
	AParameter(IRtcEngineParameter* p)
		:AutoPtr<IRtcEngineParameter>(p)
	{}
};

class RtcEngineParameters
{
public:
	RtcEngineParameters(IRtcEngine& engine)
		:m_parameter(engine){}
	int muteLocalAudioStream(bool mute) {
		return setParameters("{\"rtc.audio.mute_me\":%s,\"che.audio.mute_me\":%s}", mute ? "true" : "false", mute ? "true" : "false");
	}
	// mute/unmute all peers. unmute will clear all muted peers specified mutePeer() interface
    int muteAllRemoteAudioStreams(bool mute) {
        return m_parameter->setBool("rtc.audio.mute_peers", mute);
    }
	int muteRemoteAudioStream(uid_t uid, bool mute) {
		return setObject("rtc.audio.mute_peer", "{\"uid\":%u,\"mute\":%s}", uid, mute?"true":"false");
	}
	int muteLocalVideoStream(bool mute) {
		return setParameters("{\"rtc.video.mute_me\":%s,\"che.video.local.send\":%s}", mute ? "true" : "false", mute ? "false" : "true");
    }
    int muteAllRemoteVideoStreams(bool mute) {
        return m_parameter->setBool("rtc.video.mute_peers", mute);
    }
	int muteRemoteVideoStream(uid_t uid, bool mute) {
		return setObject("rtc.video.mute_peer", "{\"uid\":%u,\"mute\":%s}", uid, mute ? "true" : "false");
	}
	int setPlaybackDeviceVolume(int volume) {// [0,255]
        return m_parameter->setInt("che.audio.output.volume", volume);
    }
    int enableAudioVolumeIndication(int interval, int smooth) { // in ms: <= 0: disable, > 0: enable, interval in ms
        if (interval < 0)
            interval = 0;
		return setObject("che.audio.volume_indication", "{\"interval\":%d,\"smooth\":%d}", interval, smooth);
    }
    int startAudioRecording(const char* filePath) {
        return m_parameter->setString("che.audio.start_recording", filePath);
    }
    int stopAudioRecording() {
        return m_parameter->setBool("che.audio.stop_recording", true);
    }
    int setLogFile(const char* filePath) {
        return m_parameter->setString("rtc.log_file", filePath);
    }
    int setLogFilter(unsigned int filter) {
		return m_parameter->setUInt("rtc.log_filter", filter&0x80f);
	}
	int setLocalRenderMode(RENDER_MODE_TYPE renderMode) {
		return setRemoteRenderMode(0, renderMode);
	}
	int setRemoteRenderMode(uid_t uid, RENDER_MODE_TYPE renderMode) {
		return setObject("che.video.peer.render_mode", "{\"uid\":%u,\"mode\":%d}", uid, renderMode);
	}
protected:
	AParameter& parameter() {
		return m_parameter;
	}
	int setParameters(const char* format, ...) {
		char buf[512];
		va_list args;
		va_start(args, format);
		vsnprintf(buf, sizeof(buf)-1, format, args);
		va_end(args);
		return m_parameter->setParameters(buf);
	}
	int setObject(const char* key, const char* format, ...) {
		char buf[512];
		va_list args;
		va_start(args, format);
		vsnprintf(buf, sizeof(buf)-1, format, args);
		va_end(args);
		return m_parameter->setObject(key, buf);
	}
	int enableLocalVideoCapture(bool enabled) {
		return m_parameter->setBool("che.video.local.capture", enabled);
	}
	int enableLocalVideoRender(bool enabled) {
		return m_parameter->setBool("che.video.local.render", enabled);
	}
	int enableLocalVideoSend(bool enabled) {
		return muteLocalVideoStream(!enabled);
	}
	int stopAllRemoteVideo() {
		return m_parameter->setBool("che.video.peer.stop_render", true);
	}
private:
	AParameter m_parameter;
};

} //namespace rtc
} // namespace agora

AGORA_API const char* AGORA_CALL getAgoraRtcEngineVersion(int* build);
AGORA_API agora::rtc::IRtcEngine* AGORA_CALL createAgoraRtcEngine();
AGORA_API const char* AGORA_CALL getAgoraRtcEngineErrorDescription(int err);

#endif
