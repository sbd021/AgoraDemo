package io.agora.demo.agora;

import android.app.Application;
import android.util.Log;

import com.avos.avoscloud.AVAnalytics;
import com.avos.avoscloud.AVOSCloud;
import com.avos.avoscloud.LogUtil;

import io.agora.rtc.RtcEngine;

/**
 * Created by apple on 15/9/9.
 */
public class AgoraApplication extends Application {

    private RtcEngine rtcEngine;
    private MessageHandler messageHandler;

    @Override
    public void onCreate(){

        super.onCreate();

        AVOSCloud.initialize(this, "iMBlcA22YEc08R3PcSu3ON11", "c5Bz4P2erIpXde7EsKaegCLw");
        AVAnalytics.enableCrashReport(this, true);
        AVOSCloud.setLastModifyEnabled(true);
        AVOSCloud.setDebugLogEnabled(true);

        Log.d("CrashReport","0");

        messageHandler = new MessageHandler();
    }

    /**
     * Test vendor key:  6D7A26A1D3554A54A9F43BE6797FE3E2
     * @param vendorKey
     */
    public void setRtcEngine(String vendorKey){

        if(rtcEngine==null) {
            rtcEngine = RtcEngine.create(getApplicationContext(), vendorKey, messageHandler);
        }
    }

    public RtcEngine getRtcEngine(){

        return rtcEngine;
    }

    public void setEngineEventHandlerActivity(BaseEngineEventHandlerActivity engineEventHandlerActivity){
        messageHandler.setActivity(engineEventHandlerActivity);
    }
}
