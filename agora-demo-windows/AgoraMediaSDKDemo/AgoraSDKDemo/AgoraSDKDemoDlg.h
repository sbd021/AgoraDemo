
// AgoraSDKDemoDlg.h : 头文件
//

#pragma once

#include "AgoraVideoWnd.h"
#include "AgoraObject.h"


// CAgoraSDKDemoDlg 对话框
class CAgoraSDKDemoDlg : public CDialogEx
{
// 构造
public:
	CAgoraSDKDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AGORASDKDEMO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnloginMain();

	afx_msg void OnBnClickedMuteLAudio();
	afx_msg void OnBnClickedMuteLVideo();

	afx_msg void OnBnClickedMuteRAudio();
	afx_msg void OnBnClickedMuteRVideo();

	afx_msg void OnNMClickVideoWnd(NMHDR *pNMHDR, LRESULT *pResult);


// 用于处理引擎的回调消息
	afx_msg LRESULT OnEIDJoinChannelSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDReJoinChannelSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDError(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnAudioVolumeIndication(WPARAM wParam, LPARAM lParam);
	
	afx_msg LRESULT OnEIDFirstFrameDecoded(WPARAM wParam, LPARAM lParam);
	
	afx_msg LRESULT OnEIDUserJoined(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDUserOffline(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnEIDConnectionLost(WPARAM wParam, LPARAM lParam);

	void OnLoginChannel();
	void OnLeavelChannel();

	DECLARE_MESSAGE_MAP()

private:
	CAgoraVideoWnd		m_AVWBig;
	CAgoraVideoWnd		m_AVWSmall[4];

	IRtcEngine			*m_lpRTCEngine;
	CString				m_strTitle;

	BOOL				m_bInChannel;

	UINT				m_nCurPeerUID;

public:
	
	afx_msg void OnNMClickSloptionMain(NMHDR *pNMHDR, LRESULT *pResult);
};
