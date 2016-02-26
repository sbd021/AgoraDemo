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

import java.util.Random;

import io.agora.rtc.IRtcEngineEventHandler;
import io.agora.rtc.RtcEngine;
import io.agora.rtc.video.VideoCanvas;


public class BaseTestActivity extends BaseEngineHandlerActivity {

    public final static String TAG = "BaseTestActivity";
    public final static String TEST_CHANNEL = "99527";

    public final static int CALL_MODE_VIDEO = 0;
    public final static int CALL_MODE_VOICE = 1;

    protected RtcEngine rtcEngine;

    // calling variable
    protected int userId = new Random().nextInt(Math.abs((int) System.currentTimeMillis()));
    protected String callId;

    // UI elements
    protected FrameLayout mVideos[];
    protected SparseArray<VideoCanvas> mCanvasMap = new SparseArray<VideoCanvas>();

    // states
    private boolean mIsJoined = false;
    protected CommandReceiver mCmdReceiver;

    @Override
    public void onCreate(Bundle savedInstance) {
        super.requestWindowFeature(Window.FEATURE_NO_TITLE);
        super.onCreate(savedInstance);
        setContentView(R.layout.activity_base_test);

        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        setupRtcEngine();
        initViews();
        initCmdHandler();
        // testJoinChannl();
        //joinChannel(CALL_MODE_VIDEO);
    }

    @Override
    public void onBackPressed() {
        getApplicationContext().unregisterReceiver(mCmdReceiver);
        rtcEngine.leaveChannel();
        rtcEngine.stopPreview();
        getWindow().clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
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

    protected void initCmdHandler() {
        IntentFilter filter = new IntentFilter("io.agora.sample.agora.CMD");
        mCmdReceiver = new CommandReceiver();
        getApplicationContext().registerReceiver(mCmdReceiver, filter);
    }


    protected void initViews() {
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

    @Override
    public void onLeaveChannel(final IRtcEngineEventHandler.RtcStats stats) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                for (int i = 0; i < mCanvasMap.size() + 1; i++) {
                    removeViewForUser(mCanvasMap.keyAt(0));
                }
                finish();
            }
        });

    }

    // Test framework
    public class CommandReceiver extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {
            // Log.e(TAG, "onReceive command:");
            String cmd = intent.getStringExtra("cmd");
            String para = intent.getStringExtra("para");
            Log.e(TAG, "onReceive command:" + cmd + ", parameter:" + para);
            if (("enableNetworkTest").equals(cmd)) {
                rtcEngine.enableNetworkTest();
                return;
            }

            if (("disableNetworkTest").equals(cmd)) {
                rtcEngine.disableNetworkTest();
                return;
            }
        }

    }

}
