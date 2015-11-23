#pragma once

#include "../../AgoraSDK/include/IAgoraRtcEngine.h"
#include "AGEngineEventHandler.h"

using namespace agora::rtc;

class CAgoraObject
{
public:
	~CAgoraObject(void);

protected:
	CAgoraObject(void);


public:
	static IRtcEngine *m_lpAgoraEngine;
	static IRtcEngine *GetEngine(HWND hWnd);
	static void CloseEngine();
	static CAGEngineEventHandler m_EngineEventHandler;
};
