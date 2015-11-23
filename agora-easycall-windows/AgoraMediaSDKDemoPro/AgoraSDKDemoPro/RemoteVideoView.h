#pragma once

#include "AgoraObject.h"
#include "AgoraVideoWnd.h"
// CRemoteVideoView

class CRemoteVideoView : public CDockablePane
{
	DECLARE_DYNAMIC(CRemoteVideoView)

public:
	CRemoteVideoView();
	virtual ~CRemoteVideoView();

	CAgoraVideoWnd *GetAgoraVideoWnd(int nIndex);
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMClickVideoWnd(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

private:
	CAgoraVideoWnd	m_wndRemoteVideo[4];
	IRtcEngine		*m_lpRTCEngine;
};


