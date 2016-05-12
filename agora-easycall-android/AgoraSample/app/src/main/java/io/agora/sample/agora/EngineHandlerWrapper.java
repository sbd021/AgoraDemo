package io.agora.sample.agora;

import io.agora.rtc.IRtcEngineEventHandler;
import android.util.Log;
import android.util.SparseArray;
import io.agora.rtc.Constants;


/**
 * Created by chenwei on 2016/02/16.
 */
public class EngineHandlerWrapper extends IRtcEngineEventHandler {
    public final static String TAG="AGORA_SDK_TEST_CALLBACK";

    public final static SparseArray<String> mErrorMap = new SparseArray<String>() {
        {
            // worn code
            put(WarnCode.WARN_NO_AVAILABLE_CHANNEL, "WARN_NO_AVAILABLE_CHANNEL".toLowerCase());
            put(WarnCode.WARN_LOOKUP_CHANNEL_TIMEOUT, "WARN_LOOKUP_CHANNEL_TIMEOUT".toLowerCase());
            put(WarnCode.WARN_LOOKUP_CHANNEL_REJECTED, "WARN_LOOKUP_CHANNEL_REJECTED".toLowerCase());
            put(WarnCode.WARN_OPEN_CHANNEL_TIMEOUT, "WARN_OPEN_CHANNEL_TIMEOUT".toLowerCase());
            put(WarnCode.WARN_OPEN_CHANNEL_REJECTED, "WARN_OPEN_CHANNEL_REJECTED".toLowerCase());
            //put(WarnCode.WARN_REQUEST_DEFERRED, "WARN_REQUEST_DEFERRED".toLowerCase());
            put(WarnCode.WARN_ADM_RUNTIME_PLAYOUT_WARNING, "WARN_ADM_RUNTIME_PLAYOUT_WARNING".toLowerCase());
            put(WarnCode.WARN_ADM_RUNTIME_RECORDING_WARNING, "WARN_ADM_RUNTIME_RECORDING_WARNING".toLowerCase());
            put(WarnCode.WARN_ADM_RECORD_AUDIO_SILENCE, "WARN_ADM_RECORD_AUDIO_SILENCE".toLowerCase());
            put(WarnCode.WARN_ADM_PLAYOUT_MALFUNCTION, "WARN_ADM_PLAYOUT_MALFUNCTION".toLowerCase());
            put(WarnCode.WARN_ADM_RECORD_MALFUNCTION, "WARN_ADM_RECORD_MALFUNCTION".toLowerCase());
            put(WarnCode.WARN_APM_HOWLING, "WARN_APM_HOWLING".toLowerCase());
            // error code
            put(ErrorCode.ERR_OK, "ERR_OK".toLowerCase());
            put(ErrorCode.ERR_FAILED, "ERR_FAILED".toLowerCase());
            put(ErrorCode.ERR_INVALID_ARGUMENT, "ERR_INVALID_ARGUMENT".toLowerCase());
            put(ErrorCode.ERR_NOT_READY, "ERR_NOT_READY".toLowerCase());
            put(ErrorCode.ERR_NOT_SUPPORTED, "ERR_NOT_SUPPORTED".toLowerCase());
            put(ErrorCode.ERR_REFUSED, "ERR_REFUSED".toLowerCase());
            put(ErrorCode.ERR_BUFFER_TOO_SMALL, "ERR_BUFFER_TOO_SMALL".toLowerCase());
            put(ErrorCode.ERR_NOT_INITIALIZED, "ERR_NOT_INITIALIZED".toLowerCase());
            put(ErrorCode.ERR_INVALID_VIEW, "ERR_INVALID_VIEW".toLowerCase());
            put(ErrorCode.ERR_NO_PERMISSION, "ERR_NO_PERMISSION".toLowerCase());
            put(ErrorCode.ERR_TIMEDOUT, "ERR_TIMEDOUT".toLowerCase());
            put(ErrorCode.ERR_CANCELED, "ERR_CANCELED".toLowerCase());
            put(ErrorCode.ERR_TOO_OFTEN, "ERR_TOO_OFTEN".toLowerCase());
            put(ErrorCode.ERR_BIND_SOCKET, "ERR_BIND_SOCKET".toLowerCase());
            put(ErrorCode.ERR_NET_DOWN, "ERR_NET_DOWN".toLowerCase());
            put(ErrorCode.ERR_NET_NOBUFS, "ERR_NET_NOBUFS".toLowerCase());
            put(ErrorCode.ERR_INIT_VIDEO, "ERR_INIT_VIDEO".toLowerCase());
            put(ErrorCode.ERR_JOIN_CHANNEL_REJECTED, "ERR_JOIN_CHANNEL_REJECTED".toLowerCase());
            put(ErrorCode.ERR_LEAVE_CHANNEL_REJECTED, "ERR_LEAVE_CHANNEL_REJECTED".toLowerCase());
            put(ErrorCode.ERR_INVALID_VENDOR_KEY, "ERR_INVALID_VENDOR_KEY".toLowerCase());
            put(ErrorCode.ERR_INVALID_CHANNEL_NAME, "ERR_INVALID_CHANNEL_NAME".toLowerCase());
            put(ErrorCode.ERR_DYNAMIC_KEY_TIMEOUT, "ERR_DYNAMIC_KEY_TIMEOUT".toLowerCase());
            put(ErrorCode.ERR_INVALID_DYNAMIC_KEY, "ERR_INVALID_DYNAMIC_KEY".toLowerCase());
            put(ErrorCode.ERR_LOAD_MEDIA_ENGINE, "ERR_LOAD_MEDIA_ENGINE".toLowerCase());
            put(ErrorCode.ERR_START_CALL, "ERR_START_CALL".toLowerCase());
            put(ErrorCode.ERR_START_CAMERA, "ERR_START_CAMERA".toLowerCase());
            put(ErrorCode.ERR_START_VIDEO_RENDER, "ERR_START_VIDEO_RENDER".toLowerCase());
            put(ErrorCode.ERR_ADM_GENERAL_ERROR, "ERR_ADM_GENERAL_ERROR".toLowerCase());
            put(ErrorCode.ERR_ADM_JAVA_RESOURCE, "ERR_ADM_JAVA_RESOURCE".toLowerCase());
            put(ErrorCode.ERR_ADM_SAMPLE_RATE, "ERR_ADM_SAMPLE_RATE".toLowerCase());
            put(ErrorCode.ERR_ADM_INIT_PLAYOUT, "ERR_ADM_INIT_PLAYOUT".toLowerCase());
            put(ErrorCode.ERR_ADM_START_PLAYOUT, "ERR_ADM_START_PLAYOUT".toLowerCase());
            put(ErrorCode.ERR_ADM_STOP_PLAYOUT, "ERR_ADM_STOP_PLAYOUT".toLowerCase());
            put(ErrorCode.ERR_ADM_INIT_RECORDING, "ERR_ADM_INIT_RECORDING".toLowerCase());
            put(ErrorCode.ERR_ADM_START_RECORDING, "ERR_ADM_START_RECORDING".toLowerCase());
            put(ErrorCode.ERR_ADM_STOP_RECORDING, "ERR_ADM_STOP_RECORDING".toLowerCase());
            put(ErrorCode.ERR_ADM_RUNTIME_PLAYOUT_ERROR, "ERR_ADM_RUNTIME_PLAYOUT_ERROR".toLowerCase());
            put(ErrorCode.ERR_ADM_RUNTIME_RECORDING_ERROR, "ERR_ADM_RUNTIME_RECORDING_ERROR".toLowerCase());
            put(ErrorCode.ERR_ADM_RECORD_AUDIO_FAILED, "ERR_ADM_RECORD_AUDIO_FAILED".toLowerCase());
            put(ErrorCode.ERR_ADM_INIT_LOOPBACK, "ERR_ADM_INIT_LOOPBACK".toLowerCase());
            put(ErrorCode.ERR_ADM_START_LOOPBACK, "ERR_ADM_START_LOOPBACK".toLowerCase());
            put(ErrorCode.ERR_VDM_CAMERA_NOT_AUTHORIZED, "ERR_VDM_CAMERA_NOT_AUTHORIZED".toLowerCase());
        }
    };


    public String translateErrorCode(int error) {
        return mErrorMap.get(error, "Unknown warn/error code:" + error);
    }


    public void onJoinChannelSuccess(String channel, int uid, int elapsed) {
        Log.e(TAG, "onJoinChannelSuccess," + channel + "," + uid + "," + elapsed);
    }

    public void onRejoinChannelSuccess(String channel, int uid, int elapsed) {
        Log.e(TAG, "onRejoinChannelSuccess," + channel + "," + uid + "," + elapsed);
    }

    public void onWarning(int warn) {
        Log.e(TAG, "onWarning," + translateErrorCode(warn));
    }

    public void onError(int err) {
        Log.e(TAG, "onError," + translateErrorCode(err));
    }

    public void onApiCallExecuted(String api, int error) {
        Log.e(TAG, "onApiCallExecuted," + api + "," + translateErrorCode(error));
    }

    public void onCameraReady() {
        Log.e(TAG, "onCameraReady");
    }

    public void onVideoStopped() {
        Log.e(TAG, "onVideoStopped");
    }

    public void onAudioQuality(int uid, int quality, short delay, short lost) {
        Log.e(TAG, "onAudioQuality," + uid + "," + quality + "," + delay + "," + lost);
    }

    // TODO: dump stats information
    public void onLeaveChannel(RtcStats stats) {
        Log.e(TAG, "onLeaveChannel");
    }

    public void onRtcStats(RtcStats stats) {
        Log.e(TAG, "onRtcStats=> totalduration:" +stats.totalDuration + ",txB:" + stats.txBytes +
                    ",rxB:" + stats.rxBytes + ",txR:" + stats.txKBitRate + ",rxR:" + stats.rxKBitRate +
                    ",lastm:" + stats.lastmileQuality + ",user:" + stats.users +
                    ",cput:" + stats.cpuTotalUsage + ",cpua" + stats.cpuAppUsage);

    }

    // TODO: dump Audio volume infomation
    public void onAudioVolumeIndication(AudioVolumeInfo[] speakers, int totalVolume) {
        Log.e(TAG, "onAudioVolumeIndication: totalvolume:" + totalVolume);
        for (int i = 0; i < speakers.length; i++) {
            Log.e(TAG, "uid:" + speakers[i].uid + ",volume:" + speakers[i].volume);
        }
    }

    public void onNetworkQuality(int quality) {
        Log.e(TAG, "onNetworkQuality," + quality);
    }

    public void onUserJoined(int uid, int elapsed) {
        Log.e(TAG, "onUserJoined," + uid + "," + elapsed);
    }


    public void onUserOffline(int uid, int reason) {
        String desc;
        if (reason == 0) {
            desc = "USER_OFFLINE_QUIT";
        } else if (reason == 1) {
            desc = "USER_OFFLINE_DROPPED";
        } else {
            Log.e(TAG, "onUserOffline callback failed with wrong reason: " + reason);
            return;
        }
        Log.e(TAG, "onUserOffline," + uid + "," + desc);
    }

    public void onUserMuteAudio(int uid, boolean muted) {
        Log.e(TAG, "onUserMuteAudio," + uid + "," + muted);
    }

    public void onUserMuteVideo(int uid, boolean muted) {
        Log.e(TAG, "onUserMuteVideo," + uid + "," + muted);
    }

    public void onUserEnableVideo(int uid, boolean enabled) {
        Log.e(TAG, "onUserEnableVideo," + uid + "," + enabled);
    }

    public void onRemoteVideoStats(IRtcEngineEventHandler.RemoteVideoStats stats) {
        Log.e(TAG, "onRemoteVideoStat=> uid:" + stats.uid + ",delay:" + stats.delay + ",w:" + stats.width
                + ",h:" + stats.height + ",rxBitRate:" + stats.receivedBitrate + ",rxFramerate:" + stats.receivedFrameRate);
    }

    public void onLocalVideoStats(IRtcEngineEventHandler.LocalVideoStats stats) {
        Log.e(TAG, "onLocalVideoStat=> txBitrate:" + stats.sentBitrate + ",txFramerate:" +stats.sentFrameRate);
    }

    public void onFirstRemoteVideoFrame(int uid, int width, int height, int elapsed) {
        Log.e(TAG, "onFirstRemoteVideoFrame");
    }

    public void onFirstLocalVideoFrame(int width, int height, int elapsed) {
        Log.e(TAG, "onFirstLocalVideoFrame");
    }

    public void onFirstRemoteVideoDecoded(int uid, int width, int height, int elapsed) {
        Log.e(TAG, "onFirstRemoteVideoDecoded");
    }

    public void onConnectionLost() {
        Log.e(TAG, "onConnectionLost");
    }

    public void onConnectionInterrupted() {
        Log.e(TAG, "onConnectionInterrupted");
    }

    public void onMediaEngineEvent(int code) {
        Log.e(TAG, "onJoinChannelSuccess");
    }

}
