package io.agora.voipdemo;

import java.util.concurrent.atomic.AtomicReference;


import android.app.Application;
import android.util.Log;

import com.xsj.crasheye.Crasheye;

import io.agora.rtc.RtcEngine;

public class MediaDemoApplication extends Application {

	private static final String LOG = MediaDemoApplication.class
			.getSimpleName();

	private RtcEngine mNative = null;
	private MediaHandlerMgr mHandlerMgr = null;
	private AgoraVoiceSdkDemo mActivity = null;

	private static AtomicReference<MediaDemoApplication> mInstance = new AtomicReference<MediaDemoApplication>();

	public static MediaDemoApplication getInstance() {
		return mInstance.get();
	}
	public void setActivity(AgoraVoiceSdkDemo activity) {
		mActivity = activity;
	}
	public AgoraVoiceSdkDemo getActivity() {
		return mActivity;
	}

	@Override
	public void onCreate() {
		Log.i(LOG, "onCreate begin");

		super.onCreate();

		Crasheye.initWithNativeHandle(this, "3c6f5380");

		mInstance.set(this);
		mNative = null;
		mHandlerMgr = new MediaHandlerMgr(this);
		Log.i(LOG, "onCreate end");
	}

	public synchronized void createRtcEngineInstance(String vendorKey) {
		if (mNative == null) {
			mNative = RtcEngine.create(this, vendorKey, mHandlerMgr);
			mNative.monitorHeadsetEvent(true);
			mNative.monitorConnectionEvent(true);
			mNative.monitorBluetoothHeadsetEvent(true);
			mNative.enableHighPerfWifiMode(true);
        }
	}

	RtcEngine getAgoraRtcEngine() {
		return mNative;
	}

	MediaHandlerMgr getMediaHandlerMgr() {
		return mHandlerMgr;
	}

}
