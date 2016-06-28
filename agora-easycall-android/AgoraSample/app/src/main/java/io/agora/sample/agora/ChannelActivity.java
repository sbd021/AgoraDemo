package io.agora.sample.agora;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.text.TextUtils;
import android.util.TypedValue;
import android.view.LayoutInflater;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

import io.agora.rtc.IRtcEngineEventHandler;
import io.agora.rtc.RtcEngine;
import io.agora.rtc.video.VideoCanvas;
import android.widget.FrameLayout;
import android.util.Log;

/**
 * Created by apple on 15/9/18.
 */
public class ChannelActivity extends BaseEngineHandlerActivity {


    public final static int CALLING_TYPE_VIDEO = 0x100;
    public final static int CALLING_TYPE_VOICE = 0x101;

    private TextView mDuration;
    private TextView mByteCounts;

    private DrawerLayout mDrawerLayout;

    private SeekBar mResolutionSeekBar;
    private SeekBar mRateSeekBar;
    private SeekBar mFrameSeekBar;
    private SeekBar mVolumeSeekBar;
    private Switch mTapeSwitch;
    private Switch mFloatSwitch;

    private TextView mVendorKey;
    private TextView mUsername;
    private TextView mResolutionValue;
    private TextView mRateValue;
    private TextView mFrameValue;
    private TextView mVolumeValue;
    private TextView mPathValue;

    private LinearLayout mCameraEnabler;
    private LinearLayout mCameraSwitcher;

    private ImageView mNetworkQuality;

	// Used to contain thumbnail videos
	// When no thumbnail exists, this container becomes invisible
    private LinearLayout mThumbnailsContainer;
	// Used to contain main video
	private FrameLayout mMainVideoContainer;

    private RelativeLayout mEvaluationContainer;

    private ImageView mStarOne;
    private ImageView mStarTwo;
    private ImageView mStarThree;
    private ImageView mStarFour;
    private ImageView mStarFive;

    private List<ImageView> stars = new ArrayList<>();

    private RelativeLayout mFloatContainer;
    private LinearLayout mStatsContainer;
    private TextView mNotificationOld;
    private TextView mNotificationNew;

    private int time = 0;
    private int mLastRxBytes = 0;
    private int mLastTxBytes = 0;
    private int mLastDuration = 0;
    private int mThumbnailViewWidth = 0;

    private RtcEngine rtcEngine;

    private int callingType;
    private String channel;

    private int userId=new Random().nextInt(Math.abs((int) System.currentTimeMillis()));

    private String callId;

    private boolean isMuted=false;
    private boolean isCorrect=true;

    private int score=0;
    private int errorCount=0;

    public final static String EXTRA_TYPE="EXTRA_TYPE";
    public final static String EXTRA_CHANNEL="EXTRA_CHANNEL";

    @Override
    public void onCreate(Bundle savedInstance){

        super.requestWindowFeature(Window.FEATURE_NO_TITLE);

        super.onCreate(savedInstance);
        setContentView(R.layout.activity_channel);

        callingType =getIntent().getIntExtra(EXTRA_TYPE, CALLING_TYPE_VIDEO);
        channel=getIntent().getStringExtra(EXTRA_CHANNEL);

        // keep screen on - turned on
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        mThumbnailViewWidth = (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 80, getResources().getDisplayMetrics());

        setupRtcEngine();

        initViews();

        setupChannel();

        setupTime();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig){

        super.onConfigurationChanged(newConfig);
    }

    @Override
    public void onBackPressed(){

        rtcEngine.leaveChannel();

        // keep screen on - turned off
        getWindow().clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    }

    @Override
    public void onActivityResult(int requestCode,int resultCode,Intent data){

        if(requestCode==0&&resultCode==RESULT_OK&&data!=null){

            mVendorKey.setText(data.getStringExtra(ProfileActivity.EXTRA_NEW_KEY));
            mUsername.setText(data.getStringExtra(ProfileActivity.EXTRA_NEW_NAME));

            if(data.getBooleanExtra(ProfileActivity.EXTRA_HAS_CHANGED,false)){

                AlertDialog.Builder builder=new AlertDialog.Builder(ChannelActivity.this);

                builder.setCancelable(false)
                        .setMessage(getString(R.string.error))
                        .setPositiveButton(getString(R.string.error_confirm), new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                rtcEngine.leaveChannel();
                            }
                        }).show();

                AlertDialog dialog=builder.create();
            }
        }
    }

    @Override
    public void onUserInteraction(View view){

        switch (view.getId()) {

            default:

                super.onUserInteraction(view);
                break;

            case R.id.wrapper_action_video_calling: {

                callingType =CALLING_TYPE_VIDEO;

                mCameraEnabler.setVisibility(View.VISIBLE);
                mCameraSwitcher.setVisibility(View.VISIBLE);

                removeBackgroundOfCallingWrapper();

                findViewById(R.id.wrapper_action_video_calling).setBackgroundResource(R.drawable.ic_room_button_yellow_bg);
                findViewById(R.id.user_local_voice_bg).setVisibility(View.GONE);

                // enable video call
                ensureLocalViewIsCreated();

                rtcEngine.enableVideo();
                rtcEngine.muteLocalVideoStream(false);
                rtcEngine.muteLocalAudioStream(false);
                rtcEngine.muteAllRemoteVideoStreams(false);

                // join video call
                /*if (mRemoteUserContainer.getChildCount() == 0)*/ {

                    setupChannel();
                }

                // ensure video camera enabler states
                CheckBox cameraEnabler = (CheckBox) findViewById(R.id.action_camera_enabler);
                cameraEnabler.setChecked(false);

				updateAllViews();
            }
            break;

            case R.id.wrapper_action_voice_calling: {

                callingType =CALLING_TYPE_VOICE;

                mCameraEnabler.setVisibility(View.GONE);
                mCameraSwitcher.setVisibility(View.GONE);

                removeBackgroundOfCallingWrapper();
                findViewById(R.id.wrapper_action_voice_calling).setBackgroundResource(R.drawable.ic_room_button_yellow_bg);

                // show background for voice call
                findViewById(R.id.user_local_voice_bg).setVisibility(View.VISIBLE);

                ensureLocalViewIsCreated();

                // disable video call when necessary
                rtcEngine.disableVideo();
                rtcEngine.muteLocalVideoStream(true);
                rtcEngine.muteAllRemoteVideoStreams(true);

                // join voice call
                /*if (mRemoteUserContainer.getChildCount() == 0)*/ {

                    setupChannel();
                }

				updateAllViews();
            }
            break;

            case R.id.action_hung_up:
            case R.id.channel_back: {
                onBackPressed();
            }
            break;

            case R.id.evaluation_star_one:{

                setupStars(1);
            }
            break;

            case R.id.evaluation_star_two:{

                setupStars(2);
            }
            break;

            case R.id.evaluation_star_three:{

                setupStars(3);
            }
            break;

            case R.id.evaluation_star_four:{

                setupStars(4);
            }
            break;

            case R.id.evaluation_star_five:{

                setupStars(5);
            }
            break;

            //open or close drawer
            case R.id.channel_drawer_button:{

                if(mDrawerLayout.isDrawerOpen(GravityCompat.END)){
                    mDrawerLayout.closeDrawer(GravityCompat.END);
                }else{
                    mDrawerLayout.openDrawer(GravityCompat.END);
                }
            }
            break;

            //go to Profile
            case R.id.channel_drawer_profile:{

                mDrawerLayout.closeDrawer(GravityCompat.END);

                ((AgoraApplication)getApplication()).setChannelTime(time);

                Intent i=new Intent(ChannelActivity.this,ProfileActivity.class);
                startActivityForResult(i, 0);
            }
            break;

            //go to record
            case R.id.channel_drawer_record:{

                mDrawerLayout.closeDrawer(GravityCompat.END);

                ((AgoraApplication)getApplication()).setChannelTime(time);

                Intent i=new Intent(ChannelActivity.this,RecordActivity.class);
                startActivity(i);
            }
            break;

            //go to About
            case R.id.channel_drawer_about:{

                mDrawerLayout.closeDrawer(GravityCompat.END);

                ((AgoraApplication)getApplication()).setChannelTime(time);

                Intent i=new Intent(ChannelActivity.this,AboutActivity.class);
                startActivity(i);
            }
            break;
        }
    }

    private void setupRtcEngine(){

        rtcEngine=((AgoraApplication) getApplication()).getRtcEngine();

        ((AgoraApplication) getApplication()).setEngineHandlerActivity(this);

        rtcEngine.setLogFile(((AgoraApplication) getApplication()).getPath() + "/" + Integer.toString(Math.abs((int) System.currentTimeMillis())) + ".txt");

        RtcEngineEncryption.enableEncryption(rtcEngine.getNativeHandle());
    }

    private void setupChannel(){

        ((TextView)findViewById(R.id.channel_id)).setText(String.format(getString(R.string.channel_title),channel));

        rtcEngine.joinChannel(((AgoraApplication) getApplication()).getVendorKey(), channel, "", userId);
    }

    private void initViews(){

        // muter
        CheckBox muter = (CheckBox) findViewById(R.id.action_muter);
        muter.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean mutes) {

                rtcEngine.muteLocalAudioStream(mutes);
                compoundButton.setBackgroundResource(mutes ? R.drawable.ic_room_mute_pressed : R.drawable.ic_room_mute);
            }
        });

        // speaker
        CheckBox speaker = (CheckBox) findViewById(R.id.action_speaker);
        speaker.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean usesSpeaker) {

                rtcEngine.setEnableSpeakerphone(!usesSpeaker);
                compoundButton.setBackgroundResource(usesSpeaker ? R.drawable.ic_room_loudspeaker_pressed : R.drawable.ic_room_loudspeaker);
            }
        });

        // camera enabler
        CheckBox cameraEnabler = (CheckBox) findViewById(R.id.action_camera_enabler);
        cameraEnabler.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean disablesCamera) {

                rtcEngine.muteLocalVideoStream(disablesCamera);

                if (disablesCamera) {
                    findViewById(R.id.user_local_voice_bg).setVisibility(View.VISIBLE);
                    rtcEngine.muteLocalVideoStream(true);

                } else {
                    findViewById(R.id.user_local_voice_bg).setVisibility(View.GONE);
                    rtcEngine.muteLocalVideoStream(false);
                }

                compoundButton.setBackgroundResource(disablesCamera ? R.drawable.ic_room_button_close_pressed : R.drawable.ic_room_button_close);
            }
        });

        // camera switcher
        CheckBox cameraSwitch = (CheckBox) findViewById(R.id.action_camera_switcher);
        cameraSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean switches) {

                rtcEngine.switchCamera();

                compoundButton.setBackgroundResource(switches ? R.drawable.ic_room_button_change_pressed : R.drawable.ic_room_button_change);
            }
        });

        // setup states of action buttons
        muter.setChecked(false);
        speaker.setChecked(false);
        cameraEnabler.setChecked(false);
        cameraSwitch.setChecked(false);

        mDuration = (TextView) findViewById(R.id.stat_time);
        mByteCounts = (TextView) findViewById(R.id.stat_bytes);
        mDrawerLayout=(DrawerLayout)findViewById(R.id.channel_drawer_layout);
        mResolutionValue=(TextView)findViewById(R.id.channel_drawer_resolution_value);
        mRateValue=(TextView)findViewById(R.id.channel_drawer_rate_value);
        mFrameValue=(TextView)findViewById(R.id.channel_drawer_frame_value);
        mVolumeValue=(TextView)findViewById(R.id.channel_drawer_volume_value);
        mCameraEnabler = (LinearLayout)findViewById(R.id.wrapper_action_camera_enabler);
        mCameraSwitcher = (LinearLayout)findViewById(R.id.wrapper_action_camera_switcher);
        mFloatContainer=(RelativeLayout)findViewById(R.id.channel_float_container);
        mStatsContainer=(LinearLayout)findViewById(R.id.wrapper_session_stats);
        mNotificationOld=(TextView)findViewById(R.id.channel_notification_old);
        mNotificationNew=(TextView)findViewById(R.id.channel_notification_new);
        mNetworkQuality=(ImageView)findViewById(R.id.channel_network_quality);
		mMainVideoContainer = (FrameLayout) findViewById(R.id.user_main_view_container);
        mThumbnailsContainer=(LinearLayout) findViewById(R.id.user_remote_views);

        mEvaluationContainer=(RelativeLayout)findViewById(R.id.channel_evaluation);
        mEvaluationContainer.setVisibility(View.GONE);

        mStarOne=(ImageView)findViewById(R.id.evaluation_star_one);
        mStarTwo=(ImageView)findViewById(R.id.evaluation_star_two);
        mStarThree=(ImageView)findViewById(R.id.evaluation_star_three);
        mStarFour=(ImageView)findViewById(R.id.evaluation_star_four);
        mStarFive=(ImageView)findViewById(R.id.evaluation_star_five);

        stars.add(mStarOne);
        stars.add(mStarTwo);
        stars.add(mStarThree);
        stars.add(mStarFour);
        stars.add(mStarFive);

        if (callingType ==CALLING_TYPE_VIDEO) {
            // video call

            View simulateClick = new View(getApplicationContext());
            simulateClick.setId(R.id.wrapper_action_video_calling);
            this.onUserInteraction(simulateClick);


        } else if (callingType ==CALLING_TYPE_VOICE) {
            // voice call
            View simulateClick = new View(getApplicationContext());
            simulateClick.setId(R.id.wrapper_action_voice_calling);
            this.onUserInteraction(simulateClick);
        }

        findViewById(R.id.wrapper_action_video_calling).setOnClickListener(getViewClickListener());
        findViewById(R.id.wrapper_action_voice_calling).setOnClickListener(getViewClickListener());
        findViewById(R.id.action_hung_up).setOnClickListener(getViewClickListener());
        findViewById(R.id.channel_back).setOnClickListener(getViewClickListener());
        findViewById(R.id.channel_drawer_button).setOnClickListener(getViewClickListener());
        findViewById(R.id.channel_drawer_profile).setOnClickListener(getViewClickListener());
        findViewById(R.id.channel_drawer_record).setOnClickListener(getViewClickListener());
        findViewById(R.id.channel_drawer_about).setOnClickListener(getViewClickListener());

        mVendorKey=(TextView)findViewById(R.id.channel_drawer_profile_key);
        mVendorKey.setText(((AgoraApplication) getApplication()).getVendorKey());

        mUsername=(TextView)findViewById(R.id.channel_drawer_profile_name);
        mUsername.setText(((AgoraApplication) getApplication()).getUsername());

        mPathValue=(TextView)findViewById(R.id.channel_drawer_path_value);
        mPathValue.setText(((AgoraApplication) getApplication()).getPath());

        mResolutionSeekBar=(SeekBar)findViewById(R.id.channel_drawer_resolution_seekbar);
        mResolutionSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                setResolution(progress);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

        mRateSeekBar=(SeekBar)findViewById(R.id.channel_drawer_rate_seekbar);
        mRateSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                setRate(progress);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

        mFrameSeekBar=(SeekBar)findViewById(R.id.channel_drawer_frame_seekbar);
        mFrameSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                setFrame(progress);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

        mVolumeSeekBar=(SeekBar)findViewById(R.id.channel_drawer_volume_seekbar);
        mVolumeSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                setVolume(progress);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

        mTapeSwitch=(Switch)findViewById(R.id.channel_drawer_tape_switch);
        mTapeSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

                setTape(isChecked);
            }
        });

        mFloatSwitch=(Switch)findViewById(R.id.channel_drawer_float_switch);
        mFloatSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

                setFloat(isChecked);
            }
        });

        setResolution(((AgoraApplication) getApplication()).getResolution());

        setRate(((AgoraApplication) getApplication()).getRate());

        setFrame(((AgoraApplication) getApplication()).getFrame());

        setVolume(((AgoraApplication) getApplication()).getVolume());

        setTape(((AgoraApplication) getApplication()).getTape());

        setFloat(((AgoraApplication) getApplication()).getFloat());
    }

    private void removeBackgroundOfCallingWrapper() {

        findViewById(R.id.wrapper_action_video_calling).setBackgroundResource(R.drawable.shape_transparent);
        findViewById(R.id.wrapper_action_voice_calling).setBackgroundResource(R.drawable.shape_transparent);
    }

    //Show Local
    private void ensureLocalViewIsCreated() {
    	ViewGroup vg = findViewFor(0);
		if(vg != null)
			return;

		vg = setupViewFor(0);

		if(vg == null)
			return;
		SurfaceView canvasView = getVideoSurface(vg, false);
		if(canvasView == null)
			return;
        rtcEngine.enableVideo(); // If video has not been started, then start it
        int rc;
		rc = rtcEngine.setupLocalVideo(new VideoCanvas(canvasView));
        if (rc < 0) {
            Log.e("AGORA_SDK", "Failed to call rtcEngine.setupLocalVideo for local preview");
        }

    }

    //switch click
    public void onSwitchRemoteUsers(View view){

        // In voice call
        if(CALLING_TYPE_VOICE == callingType){
            return;
        }


        // In Video Call

		// view: on which the tap event raised
    	ViewGroup v1 = (ViewGroup) view.getParent();
		if(v1 == null)
			return;

		// switch with main view
		ViewGroup v2 = (ViewGroup) mMainVideoContainer.getChildAt(0);
		if(v2 == null)
			return;

		// if click on main view: no switch
		if(v2.getTag() == v1.getTag())
			return;

		// switch
		ViewGroup v1_parent = (ViewGroup) v1.getParent();
		if(v1_parent == null)
			return;

		int pos = v1_parent.indexOfChild(v1); // keep position
		v1_parent.removeView(v1);
		mMainVideoContainer.removeView(v2);
		v1_parent.addView(v2, pos, new FrameLayout.LayoutParams(mThumbnailViewWidth, mThumbnailViewWidth));
		mMainVideoContainer.addView(v1, new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT));

		// bring the new main view to background and
		// thumbnail view top
		SurfaceView c;
		c = getVideoSurface(v1, false);
		if(c != null)
		{
        	c.setZOrderOnTop(false);
        	c.setZOrderMediaOverlay(false);
		}

		c = getVideoSurface(v2, true);
		if(c != null)
		{
        	c.setZOrderOnTop(true);
        	c.setZOrderMediaOverlay(true);
		}
    }

	private void updateAllViews() {
		// check main view
		RelativeLayout vg;
		vg = (RelativeLayout) mMainVideoContainer.getChildAt(0);
		if(vg != null && (int)vg.getTag() != 0) {
			updateViewStatus(vg, (int)vg.getTag());
		}

		// check thumbnails view
		int child_count = mThumbnailsContainer.getChildCount();
		int i;
		for(i=0; i<child_count; i++) {
			vg = (RelativeLayout) mThumbnailsContainer.getChildAt(i);
			if(vg != null && (int)vg.getTag() != 0) {
				updateViewStatus(vg, (int)vg.getTag());
			}
		}
	}

    //mute others
    public void onMuteRemoteUsers(View view){
        isMuted=!isMuted;

        rtcEngine.muteAllRemoteAudioStreams(isMuted);

		// check main view
		RelativeLayout vg;
		vg = (RelativeLayout) mMainVideoContainer.getChildAt(0);
		if(vg != null && (int)vg.getTag() != 0) {
			updateViewStatus(vg, (int)vg.getTag());
		}

		// check thumbnails view
		int child_count = mThumbnailsContainer.getChildCount();
		int i;
		for(i=0; i<child_count; i++) {
			vg = (RelativeLayout) mThumbnailsContainer.getChildAt(i);
			if(vg != null && (int)vg.getTag() != 0) {
				updateViewStatus(vg, (int)vg.getTag());
			}
		}
    }

    public void onJoinChannelSuccess(String channel,final int uid,int elapsed){

        userId=uid;

        ((AgoraApplication)getApplication()).setIsInChannel(true);

        callId=rtcEngine.getCallId();

        ((AgoraApplication)getApplication()).setCallId(callId);
    }

    public void onError(final int err){

        runOnUiThread(new Runnable() {
            @Override
            public void run() {

                if (err == 101) {

                    isCorrect=false;

                    errorCount=errorCount+1;

                    if(errorCount==1) {
                        AlertDialog.Builder builder = new AlertDialog.Builder(ChannelActivity.this);

                        builder.setCancelable(false)
                                .setMessage(getString(R.string.error_101))
                                .setPositiveButton(getString(R.string.error_confirm), new DialogInterface.OnClickListener() {
                                    @Override
                                    public void onClick(DialogInterface dialog, int which) {

                                        rtcEngine.leaveChannel();
                                    }
                                }).show();

                        AlertDialog dialog = builder.create();
                    }
                }
            }
        });
    }

    public synchronized void onFirstRemoteVideoDecoded(final int uid, int width, int height, final int elapsed) {

        runOnUiThread(new Runnable() {
            @Override
            public void run() {
				// Enable view now
				ViewGroup vg = findViewFor(uid);
				if(vg == null)
					return;
				SurfaceView canvasView = getVideoSurface(vg, false);
				if(canvasView == null)
					return;
		        rtcEngine.enableVideo(); // If video has not been started, then start it
		        int rc;
				if(uid == 0)
					rc = rtcEngine.setupLocalVideo(new VideoCanvas(canvasView));
				else
					rc = rtcEngine.setupRemoteVideo(new VideoCanvas(canvasView, VideoCanvas.RENDER_MODE_HIDDEN, uid));
		        if (rc < 0) {
		            Log.e("AGORA_SDK", "Failed to call rtcEngine.setupRemoteVideo for user " + uid);
		        }

            }
        });
    }

    public synchronized void onUserJoined(final int uid, int elapsed) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
				Log.e("AGORA_SDK", "onUserJoined: " + uid);
				// a view with the UserID already there?
				// if yes, continue use that view and return
				ViewGroup vg = findViewFor(uid);
				if(vg != null) {
					Log.e("AGORA_SDK", "a previous view is used for user " + uid);
					return;
				}

				// if no, create a new view and do some configure
				vg = setupViewFor(uid);
				if(vg == null) {
					Log.e("AGORA_SDK", "Failed to create a anchor window for user " + uid);
					return;
				}

				// Notification
		        setupNotification(Math.abs(uid) + getString(R.string.channel_join));

                // app hints before you join
                TextView appNotification = (TextView) findViewById(R.id.app_notification);
                appNotification.setText("");
            }
        });
    }


    public void onUserOffline(final int uid) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                removeViewFor(uid);
                setupNotification(Math.abs(uid) + getString(R.string.channel_leave));
            }
        });
    }

    public void onUpdateSessionStats(final IRtcEngineEventHandler.RtcStats stats) {

        runOnUiThread(new Runnable() {
            @Override
            public void run() {

                // bytes
                mByteCounts.setText(((stats.txBytes + stats.rxBytes - mLastTxBytes - mLastRxBytes) / 1024 / (stats.totalDuration - mLastDuration + 1)) + "KB/s");

                // remember data from this call back
                mLastRxBytes = stats.rxBytes;
                mLastTxBytes = stats.txBytes;
                mLastDuration = stats.totalDuration;
            }
        });
    }

    public void onUserMuteVideo(final int uid, final boolean muted) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
				ViewGroup gr = findViewFor(uid);
				if(gr == null)
					return;
            	SurfaceView sv = getVideoSurface(gr, uid == 0);
				sv.setVisibility( muted ? View.GONE : View.VISIBLE);
                setupNotification(muted ? Math.abs(uid) + getString(R.string.channel_mute_video) : Math.abs(uid) + getString(R.string.channel_open_video));
            }
        });
    }

    public void onUserMuteAudio(final int uid, final boolean muted) {

        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                setupNotification(muted ? Math.abs(uid) + getString(R.string.channel_mute_audio) : Math.abs(uid) + getString(R.string.channel_open_audio));
            }
        });
    }

    public void onNetworkQuality(final int quality){

        runOnUiThread(new Runnable() {
            @Override
            public void run() {

                switch (quality){

                    case 1: {
                        mNetworkQuality.setImageResource(R.drawable.ic_room_signal_three);
                    }
                    break;

                    case 2:
                    case 3:{
                        mNetworkQuality.setImageResource(R.drawable.ic_room_signal_two);
                    }
                    break;

                    case 4:
                    case 5:{
                        mNetworkQuality.setImageResource(R.drawable.ic_room_signal_one);
                    }
                    break;

                    case 6:{
                        mNetworkQuality.setImageResource(R.drawable.ic_room_signal_none);
                    }
                    break;

                    default:
                    break;
                }
            }
        });
    }

    public void onAudioQuality(final int uid,final int quality,short delay,short lost){

        runOnUiThread(new Runnable() {
            @Override
            public void run() {

                try {

                    View remoteView = findViewFor(uid);

                    if(remoteView==null){
                        return;
                    }

                    switch (quality){

                        case 1:{
                            ((ImageView) remoteView.findViewById(R.id.viewlet_remote_video_signal)).setImageResource(R.drawable.ic_room_signal_three);
                        }
                        break;

                        case 2:
                        case 3:{
                            ((ImageView) remoteView.findViewById(R.id.viewlet_remote_video_signal)).setImageResource(R.drawable.ic_room_signal_two);
                        }
                        break;

                        case 4:
                        case 5:{
                            ((ImageView) remoteView.findViewById(R.id.viewlet_remote_video_signal)).setImageResource(R.drawable.ic_room_signal_one);
                        }
                        break;

                        case 6:{
                            ((ImageView) remoteView.findViewById(R.id.viewlet_remote_video_signal)).setImageResource(R.drawable.ic_room_signal_none);
                        }
                        break;

                        default:
                        break;
                    }

                }catch (Exception e){

                    return;
                }
            }
        });
    }

    public void onLeaveChannel(final IRtcEngineEventHandler.RtcStats stats){

        runOnUiThread(new Runnable() {
            @Override
            public void run() {

                ((AgoraApplication)getApplication()).setIsInChannel(false);
                ((AgoraApplication)getApplication()).setChannelTime(0);

                if(isCorrect) {

                    mEvaluationContainer.setVisibility(View.VISIBLE);

                    if (stats.totalDuration >= 3600) {
                        ((TextView) findViewById(R.id.evaluation_time)).setText(String.format("%d:%02d:%02d", time / 3600, (time % 3600) / 60, (time % 60)));
                    } else {
                        ((TextView) findViewById(R.id.evaluation_time)).setText(String.format("%02d:%02d", (time % 3600) / 60, (time % 60)));
                    }

                    if (((stats.txBytes + stats.rxBytes) / 1024 / 1024) > 0) {
                        ((TextView) findViewById(R.id.evaluation_bytes)).setText(Integer.toString((stats.txBytes + stats.rxBytes) / 1024 / 1024) + "MB");
                    } else {
                        ((TextView) findViewById(R.id.evaluation_bytes)).setText(Integer.toString((stats.txBytes + stats.rxBytes) / 1024) + "KB");
                    }

                    mStarOne.setOnClickListener(getViewClickListener());
                    mStarTwo.setOnClickListener(getViewClickListener());
                    mStarThree.setOnClickListener(getViewClickListener());
                    mStarFour.setOnClickListener(getViewClickListener());
                    mStarFive.setOnClickListener(getViewClickListener());

                    ((AgoraApplication) getApplication()).setIsInChannel(false);

                    (findViewById(R.id.evaluation_close)).setOnClickListener(new View.OnClickListener() {
                        @Override
                        public void onClick(View v) {

                            mEvaluationContainer.setVisibility(View.GONE);
                            finish();

                            Intent i = new Intent(ChannelActivity.this, SelectActivity.class);
                            startActivity(i);
                        }
                    });

                    (findViewById(R.id.evaluation_evaluate)).setOnClickListener(new View.OnClickListener() {
                        @Override
                        public void onClick(View v) {

                            rtcEngine.rate(callId, score * 2, "");

                            mEvaluationContainer.setVisibility(View.GONE);
                            finish();

                            Intent i = new Intent(ChannelActivity.this, SelectActivity.class);
                            startActivity(i);
                        }
                    });

                }else{

                    finish();

                    Intent i=new Intent(ChannelActivity.this, LoginActivity.class);
                    startActivity(i);
                }
            }
        });
    }

    private void setupTime() {

        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {

                        time++;

                        if (time >= 3600) {
                            mDuration.setText(String.format("%d:%02d:%02d", time / 3600, (time % 3600) / 60, (time % 60)));
                        } else {
                            mDuration.setText(String.format("%02d:%02d", (time % 3600) / 60, (time % 60)));
                        }
                    }
                });
            }
        };

        Timer timer = new Timer();
        timer.schedule(task, 1000, 1000);
    }

    private void setupNotification(String notification){

        if(TextUtils.isEmpty(mNotificationNew.getText())){
            mNotificationNew.setText(notification);
        }else{
            mNotificationOld.setText(mNotificationNew.getText().toString());
            mNotificationNew.setText(notification);
        }
    }

    private void clearStars(){

        for(int i=0;i<stars.size();i++){
            stars.get(i).setImageResource(R.drawable.ic_evaluate_dialog_cell_star);
        }
    }

    private void setupStars(int i){

        clearStars();

        if(score==i){

            score=0;

        }else{

            score=i;

            for(int j=0;j<i;j++){
                stars.get(j).setImageResource(R.drawable.ic_evaluate_dialog_cell_star_yellow);
            }
        }
    }

    //set resolution
    private void setResolution(int resolution) {

        String[] resolutionValues = new String[]{
                getString(R.string.sliding_value_cif),
                getString(R.string.sliding_value_480),
                getString(R.string.sliding_value_720),
                getString(R.string.sliding_value_1080)};

        int[][] videoResolutions = {
                {352,288},
                {640,480},
                {1280,720},
                {1920,1080}};

        mResolutionSeekBar.setProgress(resolution);
        ((AgoraApplication) getApplication()).setResolution(resolution);

        mResolutionValue.setText(resolutionValues[resolution]);
//        rtcEngine.setVideoResolution(videoResolutions[resolution][0], videoResolutions[resolution][1]);
    }

    //set rate
    private void setRate(int rate) {

        String[] rateValues = new String[]{
                getString(R.string.sliding_value_150k),
                getString(R.string.sliding_value_500k),
                getString(R.string.sliding_value_800k),
                getString(R.string.sliding_value_1m),
                getString(R.string.sliding_value_2m),
                getString(R.string.sliding_value_5m),
                getString(R.string.sliding_value_10m)};

        int[] maxBitRates = new int[]{
                150,
                500,
                800,
                1024,
                2048,
                5120,
                10240
        };

        mRateSeekBar.setProgress(rate);
        ((AgoraApplication) getApplication()).setRate(rate);

        mRateValue.setText(rateValues[rate]);
//        rtcEngine.setVideoMaxBitrate(maxBitRates[rate]);
    }

    //set frame
    private void setFrame(int frame) {

        String[] frameValues = new String[]{
                getString(R.string.sliding_value_15),
                getString(R.string.sliding_value_20),
                getString(R.string.sliding_value_24),
                getString(R.string.sliding_value_30),
                getString(R.string.sliding_value_60)};

        int[] videoMaxFrameRates = new int[]{
                15,
                20,
                24,
                30,
                60};

        mFrameSeekBar.setProgress(frame);
        ((AgoraApplication) getApplication()).setFrame(frame);

        mFrameValue.setText(frameValues[frame]);
//        rtcEngine.setVideoMaxFrameRate(videoMaxFrameRates[frame]);
    }

    //set volume
    private void setVolume(int volume) {

        String[] volumeValues = new String[]{
                getString(R.string.sliding_value_0),
                getString(R.string.sliding_value_50),
                getString(R.string.sliding_value_100),
                getString(R.string.sliding_value_150),
                getString(R.string.sliding_value_200),
                getString(R.string.sliding_value_255)};

        int[] speakerPhoneVolume = new int[]{
                0,
                50,
                100,
                150,
                200,
                255};

        mVolumeSeekBar.setProgress(volume);
        ((AgoraApplication) getApplication()).setVolume(volume);

        //mVolumeValue.setText(volumeValues[volume]);
        rtcEngine.setSpeakerphoneVolume(speakerPhoneVolume[volume]);
    }

    //set tape
    private void setTape(boolean isChecked){

        mTapeSwitch.setChecked(isChecked);

        ((AgoraApplication)getApplication()).setTape(isChecked);

        if(isChecked){

            rtcEngine.startAudioRecording(((AgoraApplication) getApplication()).getPath() + "/" + Integer.toString(Math.abs((int) System.currentTimeMillis())) + ".wav");

        }else{

            rtcEngine.stopAudioRecording();
        }
    }

    //set float
    private void setFloat(boolean isChecked){

        mFloatSwitch.setChecked(isChecked);

        ((AgoraApplication)getApplication()).setFloat(isChecked);

        mFloatContainer.setBackgroundResource(isChecked ? R.drawable.ic_room_bg_talk_time : R.color.transparent);
        mStatsContainer.setBackgroundResource(isChecked?R.color.transparent:R.drawable.ic_room_bg_talk_time);
        mNotificationOld.setVisibility(isChecked ? View.VISIBLE : View.GONE);
        mNotificationNew.setVisibility(isChecked ? View.VISIBLE : View.GONE);
        (findViewById(R.id.channel_notification_icon)).setVisibility(isChecked ? View.VISIBLE : View.GONE);
    }


	//------------------------------------------------------------------------------------------
	// View management
	// Highly depends on your layout design
	//------------------------------------------------------------------------------------------

	// create local view: could differ with remote view
	private ViewGroup createLocalView() {
        LayoutInflater layoutInflater = getLayoutInflater();
        View top = layoutInflater.inflate(R.layout.viewlet_remote_user, null);

		return (ViewGroup) top;
	}

	// create remote view: here we use the same as local view. you can define
	// a different view layout
	private ViewGroup createRemoteView() {
        LayoutInflater layoutInflater = getLayoutInflater();
        View top = layoutInflater.inflate(R.layout.viewlet_remote_user, null);

		return (ViewGroup) top;
	}

	private void updateViewStatus(ViewGroup view, int uid) {
		if(view == null)
			return;

		if(uid == 0) {
			// local
			View mic = view.findViewById(R.id.viewlet_remote_video_voice);
			if(mic != null) {
				mic.setVisibility(View.GONE);
			}

			TextView name = (TextView) view.findViewById(R.id.remote_user_name);
			if(name != null) {
				name.setVisibility(View.GONE);
			}
		}
		else {
			View mic = view.findViewById(R.id.viewlet_remote_video_voice);
			if(mic != null) {
				mic.setBackgroundResource(isMuted ? R.drawable.ic_room_voice_red : R.drawable.ic_room_voice_grey);
				mic.setVisibility(View.VISIBLE);
			}

			TextView name = (TextView) view.findViewById(R.id.remote_user_name);
			if(name != null) {
		        name.setText(String.valueOf(uid));
				name.setVisibility(View.VISIBLE);
			}

			SurfaceView sv = getVideoSurface(view, false);
            if (callingType == CALLING_TYPE_VIDEO) {
                sv.setVisibility(View.VISIBLE);
            } else {
                sv.setVisibility(View.GONE);
            }
		}
	}

	// return the innermost view where video view will be attached at
	private FrameLayout getAnchorPoint(ViewGroup view, boolean isLocal) {
		if(isLocal) {
			// depends on your view layout
			FrameLayout anchor = (FrameLayout) view.findViewById(R.id.viewlet_anchor);
			return anchor;
		}
		else {
			// depends on your view layout
			FrameLayout anchor = (FrameLayout) view.findViewById(R.id.viewlet_anchor);
			return anchor;
		}
	}

	private SurfaceView getVideoSurface(ViewGroup view, boolean isLocal) {
		FrameLayout fl = getAnchorPoint(view, isLocal);
		if(fl == null)
			return null;
		if(isLocal)
			return (SurfaceView)((ViewGroup) fl).getChildAt(0);
		else
			return (SurfaceView)((ViewGroup) fl).getChildAt(0);
	}

	// create a new ViewGroup for user uid and attach to app's view tree
	// caller must make sure no other ViewGroup for that user exists
	private ViewGroup setupViewFor(int uid) {
		boolean videoViewOnTop = false;
		ViewGroup gr;
		FrameLayout anchor;

		if(uid == 0) {
			gr = createLocalView();
		}
		else {
			gr = createRemoteView();
		}

		anchor = getAnchorPoint(gr, uid==0);
		if(anchor == null)
			return null;

		gr.setTag(uid);


		// Insert host to app's view tree
		if(mMainVideoContainer.getChildCount() == 0) {
	        mMainVideoContainer.addView(gr, new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT));

			videoViewOnTop = false;
		}
		else {
	        mThumbnailsContainer.addView(gr, new FrameLayout.LayoutParams(mThumbnailViewWidth, mThumbnailViewWidth));

			videoViewOnTop = true;

			// container is visible now
			mThumbnailsContainer.setVisibility(View.VISIBLE);
		}

		// Create an internal view for video rendering
        final SurfaceView canvasView = RtcEngine.CreateRendererView(getApplicationContext());

        canvasView.setZOrderOnTop(videoViewOnTop);
        canvasView.setZOrderMediaOverlay(videoViewOnTop);

		// Insert in host view
        anchor.addView(canvasView);

		// Update the status
		updateViewStatus(gr, uid);

		return gr;
	}

	// return a ViewGroup for user uid
	private ViewGroup findViewFor(int uid) {
		ViewGroup gr;
		gr = (ViewGroup) mMainVideoContainer.getChildAt(0);
		if(gr != null && (int)gr.getTag() == uid)
			return gr;

		int child_count = mThumbnailsContainer.getChildCount();
		int i;
		for(i=0; i<child_count; i++) {
			gr = (ViewGroup) mThumbnailsContainer.getChildAt(i);

			if(gr != null && (int)gr.getTag() == uid)
				return gr;
		}

		return null;
	}

	// Caller make sure mMainVideoAnchor does not contain
	// a child calling this funciton
	private void moveThumbnailVideoToMain() {
		if(mThumbnailsContainer.getChildCount() == 0)
			return;

		ViewGroup gr = (ViewGroup) mThumbnailsContainer.getChildAt(0);
		mThumbnailsContainer.removeView(gr);
		mMainVideoContainer.addView(gr, new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT));

		if(mThumbnailsContainer.getChildCount() == 0)
			mThumbnailsContainer.setVisibility(View.GONE);

		int uid = (int)gr.getTag();
		SurfaceView c = getVideoSurface(gr, uid==0);
		if(c != null)
		{
        	c.setZOrderOnTop(false);
        	c.setZOrderMediaOverlay(false);
		}
	}

	// must run in gui thread
	private void removeViewFor(int uid) {
		ViewGroup gr = findViewFor(uid);
		if(gr == null)
			return;

		// notify SDK
		if(uid == 0)
			rtcEngine.setupLocalVideo(new VideoCanvas(null));
		else
			rtcEngine.setupRemoteVideo(new VideoCanvas(null, VideoCanvas.RENDER_MODE_HIDDEN, uid));

		ViewGroup parent = (ViewGroup) gr.getParent();
		if(parent == null)
			return;

		parent.removeView(gr);

		if(mThumbnailsContainer.getChildCount() == 0) {
			mThumbnailsContainer.setVisibility(View.GONE);
		}

		if(mMainVideoContainer.getChildCount() == 0)
			moveThumbnailVideoToMain();
	}
}
