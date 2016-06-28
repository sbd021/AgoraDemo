package io.agora.sample.agora;

/**
 * Created by sting on 2016/3/24.
 */
public class RtcEngineEncryption {
    static {
        System.loadLibrary("agora-encrypt-demo-jni");
    }
    public static native int enableEncryption(long rtcEngineHandle);
}
