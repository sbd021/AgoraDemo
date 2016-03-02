package io.agora.voipdemo;

import java.util.concurrent.CopyOnWriteArraySet;
import android.os.Message;
import io.agora.rtc.IRtcEngineEventHandler;

public class MediaHandlerMgr extends IRtcEngineEventHandler {

	public MediaHandlerMgr(MediaDemoApplication app) {
		mApp = app;
	}
	private MediaDemoApplication mApp;
	private CopyOnWriteArraySet<MediaHandler> mHandlers = new CopyOnWriteArraySet<MediaHandler>();

	public void add(MediaHandler handler) {
		mHandlers.add(handler);
	}

	public void remove(MediaHandler handler) {
		mHandlers.remove(handler);
	}

	public boolean notify2UIThread(int message) {
		return notify2UIThread(message, (Object[]) null);
	}

	public boolean notify2UIThread(int message, Object... params) {
		for (MediaHandler handler : mHandlers) {
			if (handler.canHandleMessage(message)) {
				Message msg = handler.obtainMessage();
				msg.what = message;
				msg.obj = params;
				handler.sendMessage(msg);
			}
		}
		return true;
	}

	@Override
	public void onError(int err) {
        notify2UIThread(MediaMessage.onWriteLog, "Agora Voice SDK report error: " + err);
	}

	@Override
	public void onJoinChannelSuccess(String channelName, int uid, int elapsed) {
		notify2UIThread(MediaMessage.onWriteLog, "Channel joined: channel " + channelName + " uid " + (uid&0xFFFFFFFFL) + " elapsed "+ elapsed + " ms");
	}

    @Override
    public void onRejoinChannelSuccess(String channelName, int uid, int elapsed) {
        notify2UIThread(MediaMessage.onWriteLog, "Channel rejoined: channel " + channelName + " uid " + (uid&0xFFFFFFFFL) + " elapsed "+ elapsed + " ms");
    }

	@Override
	public void onLeaveChannel(RtcStats stats) {
		notify2UIThread(MediaMessage.onWriteLog, "end of call: duration " + stats.totalDuration + " secs, total " + (stats.txBytes+stats.rxBytes) + " bytes");
	}

	@Override
	public void onRtcStats(RtcStats stats) {
		onNetworkQuality(stats.lastmileQuality);
	}
	static String getQualityDesc(int quality) {
		switch (quality) {
		case Quality.EXCELLENT:
			return "5";
		case Quality.GOOD:
			return "4";
		case Quality.POOR:
			return "3";
		case Quality.BAD:
			return "2";
		case Quality.VBAD:
			return "1";
		case Quality.DOWN:
			return "0";
		case Quality.UNKNOWN:
		default:
			return "unknown";
		}
	}

	@Override
    public void onAudioQuality(int uid, int quality, short delay, short lost) {
        String msg = String.format("user %d quality %s delay %d lost %d", (uid&0xFFFFFFFFL), getQualityDesc(quality), delay, lost);
		notify2UIThread(MediaMessage.onWriteLog, msg);
	}

	@Override
	public void onUserJoined(int uid, int elapsed) {
		notify2UIThread(MediaMessage.onWriteLog, "user " + (uid&0xFFFFFFFFL) + " is joined");
	}
	
	@Override
	public void onUserOffline(int uid, int reason) {
        notify2UIThread(MediaMessage.onWriteLog, "user " + (uid&0xFFFFFFFFL) + " is offline");
	}

	@Override
	public void onUserMuteAudio(int uid, boolean muted) {

	}
	
	@Override
    public void onUserMuteVideo(int uid, boolean muted) {
		String msg = String.format("user %d onUserMuteVideo fired", (uid&0xFFFFFFFFL));
		notify2UIThread(MediaMessage.onWriteLog, msg);
	}

	@Override
	public void onNetworkQuality(int quality) {
//        String msg = String.format("network quality %s", getQualityDesc(quality));
//        notify2UIThread(MediaMessage.onWriteLog, msg);
	}

    @Override
    public void onLocalVideoStat(int sentBytes, int sentFrames) {

    }


	@Override
	public void onConnectionLost() {
		String msg = String.format("connection lost");
		notify2UIThread(MediaMessage.onWriteLog, msg);
	}

}
