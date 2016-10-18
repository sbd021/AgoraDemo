#include "stdafx.h"
#include "AgoraRtcEngineControlEventHandler.h"
#include "AgoraRtcEngineControlImpl.h"
#include <comutil.h>

using namespace agora::rtc;
#define MY_PROP TEXT("AgoraRtcEngineControl")


void RtcEngineEventHandlerImpl::onWarning(int warn, const char* msg)
{
	m_control.Fire_onWarning(warn);
}

void RtcEngineEventHandlerImpl::onError(int error, const char* msg)
{
	m_control.Fire_onError(error);
}

void RtcEngineEventHandlerImpl::onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{
	m_control.Fire_onJoinChannelSuccess(_bstr_t(channel), uid, elapsed);
}

void RtcEngineEventHandlerImpl::onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{
	m_control.Fire_onRejoinChannelSuccess(_bstr_t(channel), uid, elapsed);
}

void RtcEngineEventHandlerImpl::onLeaveChannel(const RtcStats& stats)
{
	m_control.Fire_onLeaveChannel(stats.duration, stats.txBytes, stats.rxBytes);
}

void RtcEngineEventHandlerImpl::onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost)
{
	m_control.Fire_onAudioQuality(uid, (enum Quality)quality, delay, lost);
}

void RtcEngineEventHandlerImpl::onRtcStats(const RtcStats& stats)
{
	m_control.Fire_onRtcStats(stats.duration, stats.txBytes, stats.rxBytes);
}

void RtcEngineEventHandlerImpl::onNetworkQuality(uid_t uid, int txQuality, int rxQuality)
{
	m_control.Fire_onNetworkQuality(uid, (enum Quality)txQuality, (enum Quality)rxQuality);
}

void RtcEngineEventHandlerImpl::onLastmileQuality(int quality)
{
	m_control.Fire_onLastmileQuality((enum Quality)quality);
}

void RtcEngineEventHandlerImpl::onUserJoined(uid_t uid, int elapsed)
{
	m_control.Fire_onUserJoined(uid, elapsed);
}

void RtcEngineEventHandlerImpl::onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason)
{
	m_control.Fire_onUserOffline(uid, (UserOfflineReason)reason);
}

void RtcEngineEventHandlerImpl::onUserMuteAudio(uid_t uid, bool muted)
{
	m_control.Fire_onUserMuteAudio(uid, muted ? VARIANT_TRUE : VARIANT_FALSE);
}

void RtcEngineEventHandlerImpl::onUserMuteVideo(uid_t uid, bool muted)
{
	m_control.Fire_onUserMuteVideo(uid, muted ? VARIANT_TRUE : VARIANT_FALSE);
}

void RtcEngineEventHandlerImpl::onUserEnableVideo(uid_t uid, bool enabled)
{
	m_control.Fire_onUserEnableVideo(uid, enabled ? VARIANT_TRUE : VARIANT_FALSE);
}

void RtcEngineEventHandlerImpl::onApiCallExecuted(const char* api, int error)
{
	m_control.Fire_onApiCallExecuted(_bstr_t(api), error);
}

void RtcEngineEventHandlerImpl::onConnectionLost()
{
	m_control.Fire_onConnectionLost();
}

void RtcEngineEventHandlerImpl::onConnectionInterrupted()
{
	m_control.Fire_onConnectionInterrupted();
}

void RtcEngineEventHandlerImpl::onCameraReady()
{
	m_control.Fire_onCameraReady();
}

void RtcEngineEventHandlerImpl::onVideoStopped()
{
	m_control.Fire_onVideoStopped();
}

void RtcEngineEventHandlerImpl::onLocalVideoStats(const LocalVideoStats& stats)
{
	m_control.Fire_onLocalVideoStats(stats.sentBitrate, stats.sentFrameRate);
}

void RtcEngineEventHandlerImpl::onRemoteVideoStats(const RemoteVideoStats& stats)
{
	m_control.Fire_onRemoteVideoStats(stats.uid, stats.delay, stats.receivedBitrate, stats.receivedFrameRate);
}

void RtcEngineEventHandlerImpl::onFirstLocalVideoFrame(int width, int height, int elapsed)
{
	m_control.Fire_onFirstLocalVideoFrame(width, height, elapsed);
}

void RtcEngineEventHandlerImpl::onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed)
{
	m_control.Fire_onFirstRemoteVideoDecoded(uid, width, height, elapsed);
}

void RtcEngineEventHandlerImpl::onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed)
{
	m_control.Fire_onFirstRemoteVideoFrame(uid, width, height, elapsed);
}

void RtcEngineEventHandlerImpl::onRefreshRecordingServiceStatus(int status)
{
	m_control.Fire_onRefreshRecordingServiceStatus(status);
}

void RtcEngineEventHandlerImpl::onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
    m_control.Fire_onAudioDeviceStateChanged(_bstr_t(deviceId), (MediaDevice)deviceType, (MediaDeviceState)deviceState);
}

void RtcEngineEventHandlerImpl::onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
    m_control.Fire_onVideoDeviceStateChanged(_bstr_t(deviceId), (MediaDevice)deviceType, (MediaDeviceState)deviceState);
}

void RtcEngineEventHandlerImpl::onAudioMixingFinished()
{
    m_control.Fire_onAudioMixingFinished();
}
