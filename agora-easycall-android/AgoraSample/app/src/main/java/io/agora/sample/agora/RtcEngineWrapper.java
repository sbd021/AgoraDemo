package io.agora.sample.agora;

import android.content.Context;


import io.agora.rtc.RtcEngine;
//import io.agora.rtc.RtcEngineEx;
import io.agora.rtc.video.VideoCanvas;
import io.agora.rtc.IRtcEngineEventHandler;
import android.util.Log;


public class RtcEngineWrapper extends RtcEngine{
    public final static String TAG="AGORA_SDK_TEST_INTRFACE";

    private static RtcEngineWrapper mInstance;
    private RtcEngine mEngine;

    public static synchronized RtcEngineWrapper create(Context context, String vendorKey, IRtcEngineEventHandler handler) {
        if (mInstance == null) {
            mInstance = new RtcEngineWrapper(context, vendorKey, handler);
        }
        return mInstance;
    }

    private RtcEngineWrapper(Context context, String vendorKey, IRtcEngineEventHandler handler) {
        mEngine = RtcEngine.create(context, vendorKey, handler);
    }

    public int joinChannel(String key, String channelName, String optionalInfo, int optionalUid) {
        Log.e(TAG, "joinChannel," + key + "," + channelName + "," + optionalInfo + "," + optionalUid);
        return mEngine.joinChannel(key, channelName, optionalInfo, optionalUid);
    }

    public int leaveChannel() {
        Log.e(TAG, "leaveChannel");
        return mEngine.leaveChannel();
    }

    public boolean enableHighPerfWifiMode(boolean enable) {
        Log.e(TAG, "enableHighPerfWifiMode," + enable);
        return mEngine.enableHighPerfWifiMode(enable);
    }

    public int enableNetworkTest() {
        Log.e(TAG, "enableNetworkTest");
        return mEngine.enableNetworkTest();
    }

    public int disableNetworkTest() {
        Log.e(TAG, "disableNetworkTest");
        return mEngine.disableNetworkTest();
    }

    public int enableVideo() {
        Log.e(TAG, "enableVideo");
        return mEngine.enableVideo();
    }

    public int disableVideo() {
        Log.e(TAG, "disableVideo");
        return mEngine.disableVideo();
    }

    public int startPreview() {
        Log.e(TAG, "startPreview");
        return mEngine.startPreview();
    }

    public int stopPreview() {
        Log.e(TAG, "stopPreview");
        return mEngine.stopPreview();
    }

//    public String getParameters(String parameters) {
//        Log.e(TAG, "getParameters");
//        return mEngine.getParameters(parameters);
//    }

    public String getParameter(String parameter, String args) {
        Log.e(TAG, "getParameter");
        return mEngine.getParameter(parameter, args);
    }

    public int setParameters(String parameters) {
        Log.e(TAG, "setParameters," + parameters);
        return mEngine.setParameters(parameters);
    }

//    public String makeQualityReportUrl(String channel, int listenerUid, int speakerUid, int format) {
//        Log.e(TAG, "makeQualityReportUrl," + channel + "," + listenerUid + "," + speakerUid + "," + format);
//        return mEngine.makeQualityReportUrl(channel, listenerUid, speakerUid, format);
//    }

    public String getCallId() {
        Log.e(TAG, "getCallId");
        return mEngine.getCallId();
    }

    public int rate(String callId, int rating, String description) {
        Log.e(TAG, "rate," + callId + "," + rating + "," + description);
        return mEngine.rate(callId, rating, description);
    }

    public int complain(String callId, String description) {
        Log.e(TAG, "complain," + callId + "," + description);
        return mEngine.complain(callId, description);
    }

    public void monitorConnectionEvent(boolean monitor) {
        Log.e(TAG, "monitorConnectionEvent," + monitor);
        mEngine.monitorConnectionEvent(monitor);
    }

    public int setLogFile(String filePath) {
        Log.e(TAG, "setLogFile," + filePath);
        return mEngine.setLogFile(filePath);
    }

    public int setLogFilter(int filter) {
        Log.e(TAG, "setLogFilter," + filter);
        return mEngine.setLogFilter(filter);
    }

    public int setupLocalVideo(VideoCanvas local) {
        Log.e(TAG, "setupLocalVideo");
        return mEngine.setupLocalVideo(local);
    }

    public int setupRemoteVideo(VideoCanvas remote) {
        Log.e(TAG, "setupRemoteVideo");
        return mEngine.setupRemoteVideo(remote);
    }

    public int setLocalRenderMode(int mode) {
        Log.e(TAG, "setLocalRenderMode," + mode);
        return mEngine.setLocalRenderMode(mode);
    }

    public int setRemoteRenderMode(int uid, int mode) {
        Log.e(TAG, "setRemoteRenderMode," + uid + "," + mode);
        return mEngine.setRemoteRenderMode(uid, mode);
    }

    public void switchView(int uid1, int uid2) {
        Log.e(TAG, "switchView," + uid1 + "," + uid2);
        mEngine.switchView(uid1, uid2);
    }

    public int switchCamera() {
        Log.e(TAG, "switchCamera");
        return mEngine.switchCamera();
    }

    public int setVideoProfile(int profile) {
        Log.e(TAG, "setVideoProfile," + profile);
        return mEngine.setVideoProfile(profile);
    }

    public int muteLocalVideoStream(boolean muted) {
        Log.e(TAG, "muteLocalVideoStream," + muted);
        return mEngine.muteLocalVideoStream(muted);
    }

    public int muteAllRemoteVideoStreams(boolean muted) {
        Log.e(TAG, "muteAllRemoteVideoStreams," + muted);
        return mEngine.muteAllRemoteVideoStreams(muted);
    }

    public void monitorHeadsetEvent(boolean monitor) {
        Log.e(TAG, "monitorHeadsetEvent," + monitor);
        mEngine.monitorHeadsetEvent(monitor);
    }

    public void monitorBluetoothHeadsetEvent(boolean monitor) {
        Log.e(TAG, "monitorBluetoothHeadsetEvent," + monitor);
        mEngine.monitorBluetoothHeadsetEvent(monitor);
    }

    public int setEnableSpeakerphone(boolean enabled) {
        Log.e(TAG, "setEnableSpeakerphone," + enabled);
        return mEngine.setEnableSpeakerphone(enabled);
    }

    public boolean isSpeakerphoneEnabled() {
        Log.e(TAG, "isSpeakerphoneEnabled");
        return mEngine.isSpeakerphoneEnabled();
    }

    public int setSpeakerphoneVolume(int volume) {
        Log.e(TAG, "setSpeakerphoneVolume," + volume);
        return mEngine.setSpeakerphoneVolume(volume);
    }

    public int enableAudioVolumeIndication(int interval, int smooth) {
        Log.e(TAG, "enableAudioVolumeIndication," + interval + "," + smooth);
        return mEngine.enableAudioVolumeIndication(interval, smooth);
    }

    public int enableAudioQualityIndication(boolean enabled) {
        Log.e(TAG, "enableAudioQualityIndication," + enabled);
        return mEngine.enableAudioQualityIndication(enabled);
    }

    public int startAudioRecording(String filePath) {
        Log.e(TAG, "startAudioRecording," + filePath);
        return mEngine.startAudioRecording(filePath);
    }

    public int stopAudioRecording() {
        Log.e(TAG, "stopAudioRecording");
        return mEngine.stopAudioRecording();
    }

    public int startRecordingService(String key) {
        Log.e(TAG, "startRecordingService");
        return mEngine.startRecordingService(key);
    }

    public int stopRecordingService(String key) {
        Log.e(TAG, "stopRecordingService");
        return mEngine.stopRecordingService(key);
    }

    public int refreshRecordingServiceStatus() {
        Log.e(TAG, "refreshRecordingServiceStatus");
        return mEngine.refreshRecordingServiceStatus();
    }

    public int startEchoTest() {
        Log.e(TAG, "startEchoTest");
        return mEngine.startEchoTest();
    }

    public int stopEchoTest() {
        Log.e(TAG, "stopEchoTest");
        return mEngine.stopEchoTest();
    }

    public int muteLocalAudioStream(boolean muted) {
        Log.e(TAG, "muteLocalAudioStream," + muted);
        return mEngine.muteLocalAudioStream(muted);
    }

    public int muteAllRemoteAudioStreams(boolean muted) {
        Log.e(TAG, "muteAllRemoteAudioStreams," + muted);
        return mEngine.muteAllRemoteAudioStreams(muted);
    }

    public int muteRemoteAudioStream(int uid, boolean muted) {
        Log.e(TAG, "muteRemoteAudioStream," + uid + "," + muted);
        return mEngine.muteRemoteAudioStream(uid, muted);
    }

    public int muteRemoteVideoStream(int uid, boolean muted) {
        Log.e(TAG, "muteRemoteVideoStream," + uid + "," + muted);
        return mEngine.muteRemoteVideoStream(uid, muted);
    }

    public int renewDynamicKey(String key) {
        Log.e(TAG, "renewDynamicKey," + key);
        return mEngine.renewDynamicKey(key);
    }

    public int setChannelProfile(int profile) {
        Log.e(TAG, "setChannelProfile," + profile);
        return mEngine.setChannelProfile(profile);
    }

    public long getNativeHandle() {
        Log.e(TAG, "getNativeHandle");
        return mEngine.getNativeHandle();
    }

    public void setPreferHeadset(boolean enabled) {
        Log.e(TAG, "setPreferHeadset," + enabled);
        mEngine.setPreferHeadset(enabled);
    }
}
