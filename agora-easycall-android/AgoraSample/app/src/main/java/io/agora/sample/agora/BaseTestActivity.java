package io.agora.sample.agora;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.util.SparseArray;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.FrameLayout;
import android.util.Log;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.nio.charset.CoderMalfunctionError;
import java.util.HashMap;
import java.util.Random;

import io.agora.rtc.IRtcEngineEventHandler;
import io.agora.rtc.RtcEngine;
import io.agora.rtc.Constants;
import io.agora.rtc.video.VideoCanvas;

import static java.lang.Integer.getInteger;


public class BaseTestActivity extends BaseEngineHandlerActivity {

    public final static String TAG = "AGORA_SDK_TEST_ACTIVITY";
    public final static String TEST_CHANNEL = "99527";

    public final static int CALL_MODE_VIDEO = 0;
    public final static int CALL_MODE_VOICE = 1;

    protected RtcEngine rtcEngine = null;

    // calling variable
    protected int userId = new Random().nextInt(Math.abs((int) System.currentTimeMillis()));
    //protected int userId = 8888;
    protected String callId;

    // UI elements
    protected FrameLayout mVideos[];
    protected SparseArray<VideoCanvas> mCanvasMap = new SparseArray<VideoCanvas>();

    // states
    private boolean mIsJoined = false;
    protected CommandReceiver mCmdReceiver = null;

    @Override
    public void onCreate(Bundle savedInstance) {
        super.requestWindowFeature(Window.FEATURE_NO_TITLE);
        super.onCreate(savedInstance);
        setContentView(R.layout.activity_base_test);

        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        setupRtcEngine();
        initTestFramework();
        // setupUI();
        // testJoinChannl();
        // joinChannel(CALL_MODE_VIDEO);
    }

    @Override
    public void onBackPressed() {
        getApplicationContext().unregisterReceiver(mCmdReceiver);
        mCmdReceiver = null;
        rtcEngine.leaveChannel();
        rtcEngine.stopPreview();
        finish();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        if (mCmdReceiver != null) {
            getApplicationContext().unregisterReceiver(mCmdReceiver);
        }
        getWindow().clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        destroyUI();
    }


    @Override
    public void onUserInteraction(View view) {
        switch (view.getId()) {
            default:
                super.onUserInteraction(view);
                break;
        }
    }

    protected void setupRtcEngine() {
        rtcEngine = ((AgoraApplication) getApplication()).getRtcEngine();
        ((AgoraApplication) getApplication()).setEngineHandlerActivity(this);
    }


    protected void initTestFramework() {
        IntentFilter filter = new IntentFilter("io.agora.sample.agora.CMD");
        mCmdReceiver = new CommandReceiver();
        getApplicationContext().registerReceiver(mCmdReceiver, filter);
        initCommandHandler();
    }


    protected void setupUI() {
        // init layout
        mVideos = new FrameLayout[] {
                (FrameLayout) findViewById(R.id.video0),
                (FrameLayout) findViewById(R.id.video1),
                (FrameLayout) findViewById(R.id.video2),
                (FrameLayout) findViewById(R.id.video3),
        };

        // create view for local video
        createViewForUser(0);
    }

    public void destroyUI() {
        runOnUiThread(new Runnable() {
            public void run() {
//                for (int i = 0; i < mCanvasMap.size() + 1; i++) {
                while (mCanvasMap.size() != 0) {
                    removeViewForUser(mCanvasMap.keyAt(0));
                }

                mVideos = null;
            }
        });
    }

    public int createViewForUser(int uid) {
        for (FrameLayout fl : mVideos) {
            if (fl.getChildAt(0) == null) {
                // get a empty container for new SurfaceView
                SurfaceView view = RtcEngine.CreateRendererView(getApplicationContext());
                fl.addView(view, new FrameLayout.LayoutParams(
                        ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
                fl.setVisibility(View.VISIBLE);
                view.setVisibility(View.VISIBLE);
                view.setZOrderOnTop(true);
                view.setZOrderMediaOverlay(true);
                view.setTag(fl);
                mCanvasMap.put(uid, new VideoCanvas(view, VideoCanvas.RENDER_MODE_FIT, uid));
                return 0;
            }
        }
        return -1;  // no empty postion
    }


    public void removeViewForUser(int uid) {
        if (mCanvasMap.get(uid) != null) {
            if (uid == 0) {
                rtcEngine.setupLocalVideo(new VideoCanvas(null));
            } else {
                rtcEngine.setupRemoteVideo(new VideoCanvas(null, VideoCanvas.RENDER_MODE_ADAPTIVE, uid));
            }
            FrameLayout fl = (FrameLayout) mCanvasMap.get(uid).view.getTag();
            fl.removeView(mCanvasMap.get(uid).view);
            mCanvasMap.remove(uid);
        }
    }


    protected int joinChannel(int callMode, int uid) {
        if (callMode == CALL_MODE_VIDEO) {
            rtcEngine.enableVideo();
            // Attention please: before you call setupLocalVideo, you MUST call enableVideo() !!!!
            rtcEngine.setupLocalVideo(mCanvasMap.get(0));
            //rtcEngine.setupLocalVideo(null);
            rtcEngine.startPreview();
            rtcEngine.joinChannel(((AgoraApplication) getApplication()).getVendorKey(), TEST_CHANNEL, "", uid);
        } else if (callMode == CALL_MODE_VOICE) {
            rtcEngine.joinChannel(((AgoraApplication) getApplication()).getVendorKey(), TEST_CHANNEL, "", uid);
        }

        return 0;
    }


    // Callbacks of RTCEngineEvent
    @Override
    public synchronized void onUserJoined(final int uid, int elapsed) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Log.e(TAG, "onUserJoined: " + uid);
                if (mCanvasMap.get(uid) == null) {
                    if (createViewForUser(uid) == 0) {
                        rtcEngine.setupRemoteVideo(mCanvasMap.get(uid));
                    } else {
                        Log.e(TAG, "no position for new comer's view: " + uid);
                    }
                }
            }
        });
    }

    @Override
    public synchronized void onFirstRemoteVideoDecoded(final int uid, int width, int height, final int elapsed) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Log.e(TAG, "onFirstRemoteVideoDecoded: " + uid);
            }
        });
    }

    @Override
    public void onUserOffline(final int uid) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                removeViewForUser(uid);
            }
        });
    }




    // Test framework
    protected HashMap<String, CommandHandler> mHandlerMap= new HashMap<String, CommandHandler>();

    protected void initCommandHandler() {
        CommandHandler defaultHandler = new CommandHandler();
        CommandHandler boolHandler = new BoolCommandHandler();
        CommandHandler intHandler = new IntHandler();
        CommandHandler stringHandler = new StringHandler();
        CommandHandler headsetEventHandler = new HeadsetEventHandler();
        mHandlerMap.put("setupUI", new SetupUIHandler());
        mHandlerMap.put("setupLocalVideo", new SetupLocalVideoHandler());
        mHandlerMap.put("destroyUI", new DestroyUIHandler());
        mHandlerMap.put("joinChannel", new JoinChannelHandler());
        mHandlerMap.put("joinChannelOnly", new JoinChannelOnlyHandler());
        mHandlerMap.put("leaveChannel", defaultHandler);
        mHandlerMap.put("enableNetworkTest", defaultHandler);
        mHandlerMap.put("disableNetworkTest", defaultHandler);
        mHandlerMap.put("enableVideo", defaultHandler);
        mHandlerMap.put("disableVideo", defaultHandler);
        mHandlerMap.put("startPreview", defaultHandler);
        mHandlerMap.put("stopPreview", defaultHandler);
        mHandlerMap.put("switchCamera", defaultHandler);
        mHandlerMap.put("startEchoTest", defaultHandler);
        mHandlerMap.put("stopEchoTest", defaultHandler);
        mHandlerMap.put("stopAudioRecording", defaultHandler);
        mHandlerMap.put("getCallId", new GetCallIdHandler());
        mHandlerMap.put("rate", new RateHandler());
        mHandlerMap.put("complain", new ComplainHandler());
        mHandlerMap.put("setChannelProfile", new SetChannelProfileHandler());
        mHandlerMap.put("monitorConnectionEvent", boolHandler);
        mHandlerMap.put("muteLocalVideoStream", boolHandler);
        mHandlerMap.put("muteAllRemoteVideoStreams", boolHandler);
        mHandlerMap.put("setEnableSpeakerphone", boolHandler);
        mHandlerMap.put("enableAudioQualityIndication", boolHandler);
        mHandlerMap.put("muteLocalAudioStream", boolHandler);
        mHandlerMap.put("muteAllRemoteAudioStreams", boolHandler);
        mHandlerMap.put("setPreferHeadset", new SetPreferHeadsetHandler());
        mHandlerMap.put("setSpeakerphoneVolume", intHandler);
        mHandlerMap.put("setLogFilter", intHandler);
        mHandlerMap.put("setLocalRenderMode", intHandler);
        mHandlerMap.put("setVideoProfile", intHandler);
        mHandlerMap.put("setChannelProfile", intHandler);
        mHandlerMap.put("enableAudioVolumeIndication", new EnableAudioVolumeIndicationHandler());
        mHandlerMap.put("setLogFile", stringHandler);
        mHandlerMap.put("isSpeakerphoneEnabled", new IsSpeakerphoneEnabledHandler());
        mHandlerMap.put("enableHighPerfWifiMode", new EnableHighPerfWifiModeHandler());
        mHandlerMap.put("monitorConnectionEvent", new MonitorConnectionEventHandler());
        mHandlerMap.put("switchView", new SwitchViewHandler());
        mHandlerMap.put("monitorHeadsetEvent", headsetEventHandler);
        mHandlerMap.put("monitorBluetoothHeadsetEvent", headsetEventHandler);
        mHandlerMap.put("startAudioRecording", stringHandler);
        mHandlerMap.put("stopAudioRecording", defaultHandler);
    }


    protected class CommandHandler {
        public synchronized int run(Intent intent) {
            String cmd = intent.getStringExtra("cmd");
            String para = intent.getStringExtra("para");
            Log.e(TAG, "receive cmd:[" + cmd + "]; with parameters:[" + para + "]");
            Class clazz = rtcEngine.getClass();
            Method m = null;
            try {
                m = clazz.getDeclaredMethod(cmd);
            } catch (NoSuchMethodException e) {
                e.printStackTrace();
            }
            try {
                int ret = (int) m.invoke(rtcEngine);
                // TODO: process return value
                Log.e(TAG, "call method:" + cmd + ", return value:" + ret);
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.printStackTrace();
            }
            return 0;
        }
    }

    protected class BoolCommandHandler extends CommandHandler {
        public synchronized int run(Intent intent) {
            String cmd = intent.getStringExtra("cmd");
            String para = intent.getStringExtra("para");
            boolean arg;
            Log.e(TAG, "receive cmd:[" + cmd + "]; with parameters:[" + para + "]");
            if (para.equals("true")) {
                arg = true;
            } else if (para.equals("false")) {
                arg = false;
            } else {
                Log.e(TAG, "wrong parameter");
                return -1;
            }
            Class clazz = rtcEngine.getClass();
            Method m = null;
            try {
                m = clazz.getDeclaredMethod(cmd, boolean.class);
            } catch (NoSuchMethodException e) {
                e.printStackTrace();
            }
            try {
                int ret = (int) m.invoke(rtcEngine, arg);
                Log.e(TAG, "call method:" + cmd + ", return value:" + ret);
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.printStackTrace();
            }
            return 0;
        }
    }

    protected class IntHandler extends CommandHandler {
        @Override
        public synchronized int run(Intent intent) {
            String cmd = intent.getStringExtra("cmd");
            String para = intent.getStringExtra("para");
            Log.e(TAG, "receive cmd:[" + cmd + "]; with parameters:[" + para + "]");
            Integer varI = new Integer(para);
            int arg = varI.intValue();
            Class clazz = rtcEngine.getClass();
            Method m = null;
            try {
                m = clazz.getDeclaredMethod(cmd, int.class);
            } catch (NoSuchMethodException e) {
                e.printStackTrace();
            }
            try {
                int ret = (int) m.invoke(rtcEngine, arg);
                Log.e(TAG, "call method:" + cmd + ", return value:" + ret);
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.printStackTrace();
            }
            return 0;
        }
    }

    protected class StringHandler extends CommandHandler {
        @Override
        public synchronized int run(Intent intent) {
            String cmd = intent.getStringExtra("cmd");
            String para = intent.getStringExtra("para");
            Log.e(TAG, "receive cmd:[" + cmd + "]; with parameters:[" + para + "]");
            Class clazz = rtcEngine.getClass();
            Method m = null;
            try {
                m = clazz.getDeclaredMethod(cmd, String.class);
            } catch (NoSuchMethodException e) {
                e.printStackTrace();
            }
            try {
                int ret = (int) m.invoke(rtcEngine, para);
                Log.e(TAG, "call method:" + cmd + ", return value:" + ret);
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.printStackTrace();
            }
            return 0;
        }
    }

    protected class HeadsetEventHandler extends CommandHandler {
        public synchronized int run(Intent intent) {
            String cmd = intent.getStringExtra("cmd");
            String para = intent.getStringExtra("para");
            boolean arg;
            Log.e(TAG, "receive cmd:[" + cmd + "]; with parameters:[" + para + "]");
            if (para.equals("true")) {
                arg = true;
            } else if (para.equals("false")) {
                arg = false;
            } else {
                Log.e(TAG, "wrong parameter");
                return -1;
            }
            Class clazz = rtcEngine.getClass();
            Method m = null;
            try {
                m = clazz.getDeclaredMethod(cmd, boolean.class);
            } catch (NoSuchMethodException e) {
                e.printStackTrace();
            }
            try {
                m.invoke(rtcEngine, arg);
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.printStackTrace();
            }
            return 0;
        }
    }

    protected class JoinChannelHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: joinChannel");
            String para = intent.getStringExtra("para");
            Log.e(TAG, "with para:" + para);
            if (para == null) {
                return joinChannel(CALL_MODE_VIDEO, userId);
            } else if (para.equals("auto_uid")) {
                return joinChannel(CALL_MODE_VIDEO, 0);
            }
            return 0;
        }
    }

    protected class JoinChannelOnlyHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: JoinChannelonly");
            return rtcEngine.joinChannel(((AgoraApplication) getApplication()).getVendorKey(), TEST_CHANNEL, "", 0);
        }
    }

    protected class SetupUIHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: setupUI");
            setupUI();
            return 0;
        }
    }

    protected class SetupLocalVideoHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: setupLocalVideo");
            return rtcEngine.setupLocalVideo(mCanvasMap.get(0));
        }
    }

    protected class DestroyUIHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: destroyUI");
            destroyUI();
            return 0;
        }
    }

    protected class GetCallIdHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: getCallId");
            Log.e(TAG, "call id is:" + rtcEngine.getCallId());
            return 0;
        }
    }

    protected class RateHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: rate");
            String desc = "sdk test";
            return rtcEngine.rate(rtcEngine.getCallId(), 3, desc);
        }
    }

    protected class ComplainHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: complainHandler");
            String desc ="sdk test complain";
            return rtcEngine.complain(rtcEngine.getCallId(), desc);
        }
    }

    protected class SetChannelProfileHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: setChannelProfile");
            String para = intent.getStringExtra("para");
            Log.e(TAG, "with para:" + para);
            int profile;
            if (para.equals("free")) {
                profile = 0;
            } else if (para.equals("broadcaster")) {
                profile = 1;
            } else if (para.equals("audience")) {
                profile = 2;
            } else {
                return -1;
            }
            return rtcEngine.setChannelProfile(profile);
        }
    }

    protected class SetPreferHeadsetHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: setPreferHeadsetHandler");
            String para = intent.getStringExtra("para");
            Log.e(TAG, "with para" + para);
            boolean arg;
            if (para.equals("true")) {
                arg = true;
            } else if (para.equals("false")) {
                arg = false;
            } else {
                Log.e(TAG, "wrong parameters");
                return -1;
            }
            rtcEngine.setPreferHeadset(arg);
            return 0;
        }
    }

    protected class EnableAudioVolumeIndicationHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: enableAudioVolumeIndiction");
            String para = intent.getStringExtra("para");
            Log.e(TAG, "with para" + para);
            Integer varI = new Integer(para);
            int arg = varI.intValue();
            return rtcEngine.enableAudioVolumeIndication(arg, 10);
        }
    }

    protected class IsSpeakerphoneEnabledHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: isSpeakerphoneEnabled");
            boolean res = rtcEngine.isSpeakerphoneEnabled();
            Log.e(TAG, "isSpeakerphoneEnabled returns: " + res);
            return 0;
        }
    }

    protected class EnableHighPerfWifiModeHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: EnableHighPerfWifiMode");
            String para = intent.getStringExtra("para");
            Log.e(TAG, "with parameter:" + para);
            boolean arg;
            if (para.equals("true")) {
                arg = true;
            } else if (para.equals("false")) {
                arg = false;
            } else {
                Log.e(TAG, "wrong parameter");
                return -1;
            }
            boolean res = rtcEngine.enableHighPerfWifiMode(arg);
            Log.e(TAG, "enableHighPerfWifiMode returns: " + res);
            return 0;
        }
    }

    protected class SwitchViewHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: switchView");
            if (mCanvasMap.size() <= 1) {
                Log.e(TAG, "wait for another one joining the channel");
                return -1;
            }
            rtcEngine.switchView(mCanvasMap.keyAt(0), mCanvasMap.keyAt(1));
            return 0;
        }
    }

    protected class MonitorConnectionEventHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: monitorConnectionEvent");
            String para = intent.getStringExtra("para");
            Log.e(TAG, "with parameter:" + para);
            boolean arg;
            if (para.equals("true")) {
                arg = true;
            } else if (para.equals("false")) {
                arg = false;
            } else {
                Log.e(TAG, "wrong parameter");
                return -1;
            }
            rtcEngine.monitorConnectionEvent(arg);
            return 0;
        }
    }

    public int executeCommand(Intent intent) {
        String cmd = intent.getStringExtra("cmd");
        if (mHandlerMap.containsKey(cmd)) {
            return mHandlerMap.get(cmd).run(intent);
        } else {
            // no handler found!
            return -1;
        }
    }


    public class CommandReceiver extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {
            String cmd = intent.getStringExtra("cmd");
            Log.e(TAG, "onReceive command:" + cmd);
            if (executeCommand(intent) != 0) {
                Log.e(TAG, "failed to execute command");
            }
        }
    }

}
