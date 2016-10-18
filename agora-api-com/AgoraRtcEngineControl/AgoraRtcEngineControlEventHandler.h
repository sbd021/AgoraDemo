#pragma once
#include <windows.h>
#include <memory>
#include <queue>
#include <string>
#include <mutex>
#include "AgoraRtcEngineControlImpl.h"

class RtcEngineEventHandlerImpl : public agora::rtc::IRtcEngineEventHandler
{
public:
	RtcEngineEventHandlerImpl(CAgoraRtcEngineControlImpl& control)
		:m_control(control)
	{}
	virtual void onWarning(int warn, const char* msg) override;
	virtual void onError(int error, const char* msg) override;
	virtual void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) override;
	virtual void onRejoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) override;
	virtual void onLeaveChannel(const agora::rtc::RtcStats& stats) override;
	virtual void onAudioQuality(agora::rtc::uid_t uid, int quality, unsigned short delay, unsigned short lost) override;
	virtual void onRtcStats(const agora::rtc::RtcStats& stats) override;
	virtual void onNetworkQuality(agora::rtc::uid_t uid, int txQuality, int rxQuality) override;
	virtual void onLastmileQuality(int quality) override;
	virtual void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;
	virtual void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;
	virtual void onUserMuteAudio(agora::rtc::uid_t uid, bool muted) override;
	virtual void onUserMuteVideo(agora::rtc::uid_t uid, bool muted) override;
	virtual void onUserEnableVideo(agora::rtc::uid_t uid, bool enabled) override;
	virtual void onApiCallExecuted(const char* api, int error) override;
	virtual void onConnectionLost() override;
	virtual void onConnectionInterrupted() override;
	virtual void onCameraReady() override;
	virtual void onVideoStopped() override;
	virtual void onLocalVideoStats(const agora::rtc::LocalVideoStats& stats) override;
	virtual void onRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats) override;
	virtual void onFirstLocalVideoFrame(int width, int height, int elapsed) override;
	virtual void onFirstRemoteVideoDecoded(agora::rtc::uid_t uid, int width, int height, int elapsed) override;
	virtual void onFirstRemoteVideoFrame(agora::rtc::uid_t uid, int width, int height, int elapsed) override;
	virtual void onRefreshRecordingServiceStatus(int status) override;
    virtual void onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) override;
    virtual void onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) override;
    virtual void onAudioMixingFinished() override;
private:
	CAgoraRtcEngineControlImpl& m_control;
};
