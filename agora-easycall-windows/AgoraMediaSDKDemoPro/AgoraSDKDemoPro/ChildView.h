
// ChildView.h : CChildView 类的接口
//


#pragma once

#include "AGEngineEventHandler.h"
#include "AgoraVideoWnd.h"

#include "DlgMaxVideo.h"

#include <atlcoll.h>
#include "AGProtocol.h"

// CChildView 窗口

#define WM_MAXVIDEOCLOSED	(WM_USER+200)

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 属性
public:

// 操作
public:

// 重写
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	BOOL ActiveRenderWnd(UINT nUID);
	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBtnJoinChannel();
	afx_msg void OnBtnLeaveChannel();
	afx_msg void OnBtnSetup();
	afx_msg void OnBtnSendChatMessage();
	afx_msg void OnBtnTestSend();

	afx_msg void OnUpdateViewUserList(CCmdUI* pCmdUI);
	afx_msg void OnViewUserlist();

	afx_msg void OnUpdateLocalVideoView(CCmdUI* pCmdUI);
	afx_msg void OnLocalVideoView();

	afx_msg void OnUpdateRemoteVideoView(CCmdUI* pCmdUI);
	afx_msg void OnRemoteVideoView();

	afx_msg void OnNMClickLocalVideoWnd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickVideoWnd(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg LRESULT OnMaxVideoWndClosed(WPARAM wParam, LPARAM lParam);

	// 用于处理引擎的回调消息
	afx_msg LRESULT OnEIDJoinChannelSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDReJoinChannelSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDError(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnEIDAudioVolumeIndication(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnEIDNetworkQuality(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnEIDFirstFrameDecoded(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnEIDUserJoined(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDUserOffline(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnEIDConnectionLost(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnEIDVendorMessage(WPARAM wParam, LPARAM lParam);

	void OnTestMsgReceived(UINT nUID, LPPRI_PROTOCOL_HEADER lpHeader, LPCVOID lpData);
	void OnChatMsgReceived(UINT nUID, LPPRI_PROTOCOL_HEADER lpHeader, LPCVOID lpData);
	void OnFileMsgReceived(UINT nUID, LPPRI_PROTOCOL_HEADER lpHeader, LPCVOID lpData);


	DECLARE_MESSAGE_MAP()

private:
	CAgoraObject	*m_lpAgoraObject;
	CAgoraVideoWnd	m_wndLocalVideo;
	CAgoraVideoWnd	m_wndRemoteVideo[4];

	CDlgMaxVideo	m_dlgMaxVideo;

	CMFCListCtrl	m_ctrUserList;

	CImageList		m_imgUserStat;

	IRtcEngine		*m_lpRTCEngine;

	bool			m_bIsWndBusy[4];

	CString			m_strRoomName;

	CEdit			m_ctrChatBox;
	CEdit			m_ctrHistroyBox;
	CButton			m_ctrBtnSend;
	CButton			m_ctrBtnTestSend;

	LPBYTE			m_lpProtocalBuf;
	LPBYTE			m_lpCoreBuf;
	LPPRI_PROTOCOL_HEADER	m_lpHeader;

public:
	
};

