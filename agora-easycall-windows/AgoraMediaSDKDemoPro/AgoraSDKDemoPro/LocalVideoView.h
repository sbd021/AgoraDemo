#pragma once

#include "AgoraObject.h"
#include "AgoraVideoWnd.h"

class CLocalVideoView : public CDockablePane
{
	DECLARE_DYNAMIC(CLocalVideoView)

public:
	CLocalVideoView(void);
	virtual ~CLocalVideoView(void);

	CAgoraVideoWnd *GetAgoraVideoWnd() {return &m_wndLocalVideo;};
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnNMClickVideoWnd(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

private:
	CAgoraVideoWnd	m_wndLocalVideo;
	IRtcEngine		*m_lpRTCEngine;
};
