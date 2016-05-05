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
import java.util.HashMap;
import java.util.Random;

import io.agora.rtc.IRtcEngineEventHandler;
import io.agora.rtc.RtcEngine;
import io.agora.rtc.video.VideoCanvas;


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
                mCanvasMap.put(uid, new VideoCanvas(view, VideoCanvas.RENDER_MODE_ADAPTIVE, uid));
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
                rtcEngine.setupRemoteVideo(new VideoCanvas(null, VideoCanvas.RENDER_MODE_HIDDEN, uid));
            }
            FrameLayout fl = (FrameLayout) mCanvasMap.get(uid).view.getTag();
            fl.removeView(mCanvasMap.get(uid).view);
            mCanvasMap.remove(uid);
        }
    }


    protected int joinChannel(int callMode) {
        if (callMode == CALL_MODE_VIDEO) {
            rtcEngine.enableVideo();
            // Attention please: before you call setupLocalVideo, you MUST call enableVideo() !!!!
            rtcEngine.setupLocalVideo(mCanvasMap.get(0));
            rtcEngine.startPreview();
            rtcEngine.joinChannel(((AgoraApplication) getApplication()).getVendorKey(), TEST_CHANNEL, "", userId);
        } else {
            rtcEngine.joinChannel(((AgoraApplication) getApplication()).getVendorKey(), TEST_CHANNEL, "", userId);
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
        mHandlerMap.put("setupUI", new setupUIHandler());
        mHandlerMap.put("destroyUI", new destroyUIHandler());
        mHandlerMap.put("joinChannel", new JoinChannelHandler());
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
    }


    protected class CommandHandler {
        public synchronized int run(Intent intent) {
            String cmd = intent.getStringExtra("cmd");
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

    protected class JoinChannelHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: joinChannel");
            return joinChannel(CALL_MODE_VIDEO);
        }
    }

    protected class setupUIHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: setupUI");
            setupUI();
            return 0;
        }
    }

    protected class destroyUIHandler extends CommandHandler {
        @Override
        public int run(Intent intent) {
            Log.e(TAG, "call method: destroyUI");
            destroyUI();
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
            Log.e(TAG, "onReceive command:");
            if (executeCommand(intent) != 0) {
                Log.e(TAG, "failed to execute command");
            }
        }
    }

}
