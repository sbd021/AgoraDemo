#pragma once

using namespace agora::rtc;

class CAGEngineEventHandler :
	public IRtcEngineEventHandler
{
public:
	CAGEngineEventHandler(void);
	~CAGEngineEventHandler(void);

	void SetMsgReceiver(HWND hWnd = NULL);
	HWND GetMsgReceiver() {return m_hMainWnd;};

	virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
	virtual void onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
	virtual void onError(int err, const char* msg);
	virtual void onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost);
	virtual void onAudioTransportQuality(uid_t uid, unsigned short delay, unsigned short lost);
	virtual void onVideoTransportQuality(uid_t uid, unsigned short delay, unsigned short lost);
	virtual void onRecap(const char* recapData, int length);
	virtual void onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume);
	virtual void onLeaveChannel(const SessionStat& stat);
	virtual void onUpdateSessionStats(const SessionStat& stat);
	virtual void onMediaEngineEvent(int evt);
	virtual void onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState);
	virtual void onNetworkQuality(int quality);
	virtual void onFirstLocalVideoFrame(int width, int height, int elapsed);
	virtual void onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed);
	virtual void onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed);
	virtual void onUserJoined(uid_t uid, int elapsed);
	virtual void onUserOffline(uid_t uid);
	virtual void onUserMuteAudio(uid_t uid, bool muted);
	virtual void onUserMuteVideo(uid_t uid, bool muted);

	virtual void onAudioRecorderException(int elapsed);
	virtual void onLocalVideoStat(int sentBytes, int sentFrames);
	virtual void onRemoteVideoStat(uid_t uid, int frameCount, int delay, int receivedBytes);
	virtual void onCameraReady();
	virtual void onConnectionLost();

	virtual void onVendorMessage(uid_t uid, const char* data, size_t length);

private:
	HWND		m_hMainWnd;
};
