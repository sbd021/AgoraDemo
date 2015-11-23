
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "ChildView.h"
#include "UserListView.h"
#include "LocalVideoView.h"
#include "RemoteVideoView.h"

#include "OutputWnd.h"

class CMainFrame : public CFrameWndEx
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// 属性
public:

// 操作
public:

// 重写
public:

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar			m_wndMenuBar;
	CMFCToolBar			m_wndToolBar;
//	CMFCStatusBar		m_wndStatusBar;
	
	CMFCRibbonStatusBar		m_wndStatusBar;
	CMFCRibbonBaseElement	*m_lpElementTextInfo;		// message text
	CMFCRibbonBaseElement	*m_lpElementRoomInfo;		// room info
	CMFCRibbonBaseElement	*m_lpElementNetQuality;		// NetworkQuality
	CMFCRibbonBaseElement	*m_lpElementSDKVer;			// SDKVersion

//	CUserListView		m_wndUserView;

//	CLocalVideoView		m_wndLocalView;
//	CRemoteVideoView	m_wndRemoteView;

	CChildView			m_wndView;

	IRtcEngine			*m_lpRTCEngine;
	CAgoraObject		*m_lpAgoraObject;

	CAgoraVideoWnd		*m_lpWndLocalVideo;
	CAgoraVideoWnd		*m_lpWndRemoteVideo[4];

	CMFCListCtrl		*m_lpUserListCtrl;

// 生成的消息映射函数
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnViewCustomize();
	
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};


