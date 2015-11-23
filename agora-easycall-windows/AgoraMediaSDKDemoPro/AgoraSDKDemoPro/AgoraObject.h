#pragma once

#include "../../AgoraSDK/include/IAgoraRtcEngine.h"
#include "AGEngineEventHandler.h"

using namespace agora::rtc;

// 引擎标记位
#define AG_ENGFLAG_ENNETTEST	0x00000001
#define AG_ENGFLAG_ECHOTEST		0x00000002
#define AG_ENGFLAG_SPKPHTEST	0x00000004
#define AG_ENGFLAG_MICPHTEST	0x00000008


class CAgoraObject
{
public:
	~CAgoraObject(void);

	void SetNetworkTestFlag(BOOL bEnable);
	BOOL GetNetworkTestFlag();

	void SetEchoTestFlag(BOOL bEnable);
	BOOL GetEchoTestFlag();

	void SetSpeakerphoneTestFlag(BOOL bEnable);
	BOOL GetSpeakerphoneTestFlag();

	void SetMicrophoneTestFlag(BOOL bEnable);
	BOOL GetMicrophoneTestFlag();

	void SetMsgHandlerWnd(HWND hWnd);
	HWND GetMsgHandlerWnd();

	static IRtcEngine *GetEngine();
	
	static CString GetSDKVersion();

protected:
	CAgoraObject(void);

private:
	DWORD	m_dwEngineFlag;
	static  CAgoraObject *m_lpAgoraObject;

	static IRtcEngine *m_lpAgoraEngine;

public:
	static CAgoraObject *GetAgoraObject();
	static void CloseAgoraObject();

	static CAGEngineEventHandler m_EngineEventHandler;
};
