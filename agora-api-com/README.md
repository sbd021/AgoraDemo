#Setup the DEMO
1. Copy headers of Agora SDK into the AgoraRtcEngineControl/lib directory before you build the project.
2. Copy binaries of Agora SDK into the directory where AgoraRtcEngineControl.dll is genereated.
3. After AgoraRtcEngineControl.dll is genereated, run a command shell with Administrator privilege and then run the following command to register the COM component
    regsvr32 AgoraRtcEngineControl.dll
4. Specify your own APP ID when initialing Agora Rtc Engine in the function setupRtcEngine() within Form1.cs.
