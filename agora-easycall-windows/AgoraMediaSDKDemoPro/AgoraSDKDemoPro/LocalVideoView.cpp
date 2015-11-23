#include "StdAfx.h"
#include "AgoraSDKDemoPro.h"
#include "LocalVideoView.h"

IMPLEMENT_DYNAMIC(CLocalVideoView, CDockablePane)

CLocalVideoView::CLocalVideoView(void)
{
}

CLocalVideoView::~CLocalVideoView(void)
{
}


BEGIN_MESSAGE_MAP(CLocalVideoView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, ID_WND_LOCALVIDEO, &CLocalVideoView::OnNMClickVideoWnd)

END_MESSAGE_MAP()

int CLocalVideoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	// 创建视图:
	const DWORD dwViewStyle = WS_TABSTOP | WS_CHILD | WS_BORDER | WS_VISIBLE;

	CRect rcClientRect;

	rcClientRect.SetRect(1, 1, 1, 1);

	m_wndLocalVideo.Create(NULL, _T("Local"), WS_BORDER | WS_VISIBLE | WS_VISIBLE, rcClientRect, this, ID_WND_LOCALVIDEO);
	m_lpRTCEngine = CAgoraObject::GetEngine();

	return 0;
}

void CLocalVideoView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (GetSafeHwnd() == NULL)
		return;

	CRect rectClient;
	GetClientRect(rectClient);

	m_wndLocalVideo.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
//	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

//	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
//	m_ctrUserList.SetWindowPos(NULL, rectClient.left, rectClient.top+cyTlb, rectClient.Width(), rectClient.Height()-cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CLocalVideoView::OnNMClickVideoWnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMAGVIDEOWND pNMVideoWnd = reinterpret_cast<LPNMAGVIDEOWND>(pNMHDR);
	RtcEngineParameters rep(m_lpRTCEngine);
	DWORD dwUserFlag = m_wndLocalVideo.GetUserFlag();
	BOOL bValue = FALSE;

	switch (pNMVideoWnd->nMousePos)
	{
	case CAgoraVideoWnd::MOUSE_POS_BIGSCREEN:
		
		break;
	case CAgoraVideoWnd::MOUSE_POS_MUTEVIDEO:
		bValue = m_wndLocalVideo.IsVideoMuted();
		if(rep.muteLocalVideoStream(!bValue) == 0)
			m_wndLocalVideo.SetMuteVideoFlag(!bValue);

		break;
	case CAgoraVideoWnd::MOUSE_POS_MUTEAUDIO:
		bValue = m_wndLocalVideo.IsAudioMuted();
		if(rep.muteLocalAudioStream(!bValue) == 0)
			m_wndLocalVideo.SetMuteAudioFlag(!bValue);

		break;
	default:
		break;
	}

	Invalidate();
	UpdateWindow();
}