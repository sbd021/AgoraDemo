#include "StdAfx.h"
#include "AgoraObject.h"

IRtcEngine *CAgoraObject::m_lpAgoraEngine = NULL;
CAGEngineEventHandler CAgoraObject::m_EngineEventHandler;

CAgoraObject::CAgoraObject(void)
{

}

CAgoraObject::~CAgoraObject(void)
{
}


IRtcEngine *CAgoraObject::GetEngine(HWND hWnd)
{
	if(m_lpAgoraEngine == NULL){
		m_lpAgoraEngine = createAgoraRtcEngine(&m_EngineEventHandler);
		m_EngineEventHandler.SetMsgReceiver(hWnd);
	}
	else {
		if(m_EngineEventHandler.GetMsgReceiver() != hWnd && hWnd != NULL)
			m_EngineEventHandler.SetMsgReceiver(hWnd);
	}

	return m_lpAgoraEngine;
}


void CAgoraObject::CloseEngine()
{

}