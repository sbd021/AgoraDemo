How to build the project?
0. every project in the repo doesn't contain library or framework.
1. please get the latest agora sdk framework and library.
2. put sdk into sdk projects, and the project could be built.
3. Use your vendor key to replace the default key:"6D7A26A1D3554A54A9F43BE6797FE3E2".

The directory of sdk for each project:

About android, the sdk contains 
--agora-rtc-sdk.jar
  |
  |--armeabi-v7a
  |      |
  |      |-- libagora-rtc-sdk-jni.so
  |      |-- libHDACEngine.so
  | 
  |--x86
      |
      |-- libagora-rtc-sdk-jni.so
      |-- libHDACEngine.so

For project agora-demo-android, put them into directory
agora-demo-android/libs

For project agora-easycall-android, put them into directory
agora-easycall-android/libs

For project agora-voice-demo-android, put them into directory
agora-voice-demo-android/libs



About iOS, the sdk is AgoraRtcEngineKit.framework for media, and AgoraAudioKit.framework for voice.

For project agora-demo-ios-oc, put AgoraRtcEngineKit.framework into directory
agora-demo-ios-oc/libs

For project agora-demo-ios-swift, put AgoraRtcEngineKit.framework into directory
agora-demo-ios-swift/libs

For project agora-easycall-ios-oc, put AgoraRtcEngineKit.framework into directory
agora-easycall-ios-oc/libs

For project agora-easycall-ios-swift, put AgoraRtcEngineKit.framework into directory
agora-easycall-ios-swift/libs

For project agora-voice-demo-oc, put AgoraAudioKit.framework into directory
agora-voice-demo-oc/libs

The same thing on mac:
For project agora-voice-demo-mac, put AgoraAudioKit.framework into directory
agora-voice-demo-mac/libs
