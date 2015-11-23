
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "AgoraSDKDemoPro.h"
#include "ChildView.h"
#include "DlgJoinChannel.h"

#include "AgoraObject.h"
#include "AGEventDef.h"
#include "SetupSheet.h"

#include "DlgMaxVideo.h"

#include "AGProtocol.h"
#include "CRC32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView

CChildView::CChildView()
{
	m_lpProtocalBuf = new BYTE[1400];
	m_lpHeader = (LPPRI_PROTOCOL_HEADER)m_lpProtocalBuf;
	m_lpCoreBuf = m_lpProtocalBuf + sizeof(PRI_PROTOCOL_HEADER);
	srand(::GetTickCount());
}

CChildView::~CChildView()
{
	delete [] m_lpProtocalBuf;
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()

	ON_MESSAGE(WM_MAXVIDEOCLOSED, &CChildView::OnMaxVideoWndClosed)

	ON_MESSAGE(WM_MSGID(EID_JOINCHANNEL_SUCCESS), &CChildView::OnEIDJoinChannelSuccess)
	ON_MESSAGE(WM_MSGID(EID_REJOINCHANNEL_SUCCESS), &CChildView::OnEIDReJoinChannelSuccess)
	ON_MESSAGE(WM_MSGID(EID_ERROR), &CChildView::OnEIDError)
	ON_MESSAGE(WM_MSGID(EID_AUDIO_VOLUME_INDICATION), &CChildView::OnEIDAudioVolumeIndication)

	ON_MESSAGE(WM_MSGID(EID_NETWORK_QUALITY), &CChildView::OnEIDNetworkQuality)
	ON_MESSAGE(WM_MSGID(EID_FIRST_REMOTE_VIDEO_DECODED), &CChildView::OnEIDFirstFrameDecoded)

	ON_MESSAGE(WM_MSGID(EID_USER_JOINED), &CChildView::OnEIDUserJoined)
	ON_MESSAGE(WM_MSGID(EID_USER_OFFLINE), &CChildView::OnEIDUserOffline)
	ON_MESSAGE(WM_MSGID(EID_CONNECTION_LOST), &CChildView::OnEIDConnectionLost)
	ON_MESSAGE(WM_MSGID(EID_VENDOR_MESSAGE), &CChildView::OnEIDVendorMessage)

	ON_COMMAND(ID_JOIN_TOOLBAR, &CChildView::OnBtnJoinChannel)
	ON_COMMAND(ID_LEAVE_TOOLBAR, &CChildView::OnBtnLeaveChannel)
	ON_COMMAND(ID_SETUP_TOOLBAR, &CChildView::OnBtnSetup)
	ON_COMMAND(ID_BTN_SEND, &CChildView::OnBtnSendChatMessage)
	ON_COMMAND(ID_BTN_TESTSEND, &CChildView::OnBtnTestSend)


	ON_NOTIFY(NM_CLICK, ID_WND_LOCALVIDEO, &CChildView::OnNMClickLocalVideoWnd)
	ON_NOTIFY(NM_CLICK, ID_WND_REMOTEVIDEO+0, &CChildView::OnNMClickVideoWnd)
	ON_NOTIFY(NM_CLICK, ID_WND_REMOTEVIDEO+1, &CChildView::OnNMClickVideoWnd)
	ON_NOTIFY(NM_CLICK, ID_WND_REMOTEVIDEO+2, &CChildView::OnNMClickVideoWnd)
	ON_NOTIFY(NM_CLICK, ID_WND_REMOTEVIDEO+3, &CChildView::OnNMClickVideoWnd)

	ON_WM_SIZE()
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO: 在此处添加消息处理程序代码
	
	// 不要为绘制消息而调用 CWnd::OnPaint()
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rcVideoRect;
	BOOL bRet = FALSE;
	DWORD dwLastError = 0;

	const DWORD dwListWndStyle = WS_TABSTOP | WS_CHILD | WS_BORDER | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;

	CRect rcClientRect;

	rcClientRect.SetRect(1, 1, 1, 1);

	m_wndLocalVideo.Create(NULL, _T("Local"), WS_BORDER | WS_VISIBLE, rcClientRect, this, ID_WND_LOCALVIDEO);

	m_ctrUserList.Create(dwListWndStyle, rcClientRect, this, ID_LIST_USERLIST);
	m_ctrUserList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES | LVS_EX_INFOTIP | LVS_EX_FULLROWSELECT);
	m_ctrUserList.SetImageList(&m_imgUserStat, LVSIL_SMALL);
	m_ctrUserList.InsertColumn(0, _T("UID"), 0, 150, 0);
	m_ctrUserList.InsertColumn(1, _T("Elapsed"), 0, 120, 1);

	for(int nIndex = 0; nIndex < 4; nIndex++) {
		m_wndRemoteVideo[nIndex].Create(NULL, _T("Remote"), WS_BORDER | WS_VISIBLE, rcClientRect, this, ID_WND_REMOTEVIDEO+nIndex);
		m_wndRemoteVideo[nIndex].SetVolbarPos(CAgoraVideoWnd::VOLBAR_RIGHT);
	}

	m_lpAgoraObject = CAgoraObject::GetAgoraObject();
	m_lpAgoraObject->SetMsgHandlerWnd(GetSafeHwnd());
	m_lpRTCEngine = CAgoraObject::GetEngine();
	m_lpRTCEngine->initialize("6D7A26A1D3554A54A9F43BE6797FE3E2");

	m_dlgMaxVideo.Create(CDlgMaxVideo::IDD, this);

	m_ctrHistroyBox.Create(WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_READONLY, rcClientRect, this, ID_WND_HISTROYBOX);
	m_ctrChatBox.Create(WS_VISIBLE | WS_CHILD | WS_BORDER, rcClientRect, this, ID_WND_CHATBOX);
	m_ctrBtnSend.Create(_T("Send"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD, rcClientRect, this, ID_BTN_SEND);
	m_ctrBtnTestSend.Create(_T("Test"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD, rcClientRect, this, ID_BTN_TESTSEND);
	
	return 0;
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (GetSafeHwnd() == NULL)
		return;

	int nVideoHeight = cy/4;

	m_wndLocalVideo.SetWindowPos(NULL, 0, 0, 295, 250, SWP_NOACTIVATE | SWP_NOZORDER);
	m_ctrUserList.SetWindowPos(NULL, 0, 255, 295, 285, SWP_NOACTIVATE | SWP_NOZORDER);
	m_ctrHistroyBox.SetWindowPos(NULL, 300, 0, 350, 400, SWP_NOACTIVATE | SWP_NOZORDER);

	m_ctrChatBox.SetWindowPos(NULL, 300, 405, 350, 110, SWP_NOACTIVATE | SWP_NOZORDER);
	m_ctrBtnSend.SetWindowPos(NULL, 600, 517, 50, 25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_ctrBtnTestSend.SetWindowPos(NULL, 540, 517, 50, 25, SWP_NOACTIVATE | SWP_NOZORDER);

	for(int nIndex = 0; nIndex < 4; nIndex++)
		m_wndRemoteVideo[nIndex].SetWindowPos(NULL, 655, nIndex*135, 220, 135, SWP_NOACTIVATE | SWP_NOZORDER);
}



BOOL CChildView::ActiveRenderWnd(UINT nUID)
{
	int nFoundIndex = -1;

	for(int nIndex = 0; nIndex< 4; nIndex++){
		if(!m_bIsWndBusy[nIndex]) {
			nFoundIndex = nIndex;
			break;
		}
	}

	if(nFoundIndex == -1)
		return FALSE;

	return TRUE;
/*	m_arrVideoCanvas[nFoundIndex].uid = nUID;
	m_arrVideoCanvas[nFoundIndex].renderMode = VideoCanvas::RenderMode::RENDER_MODE_FIT;
	CAgoraAudio::GetEngine(NULL)->setupRemoteVideo(m_arrVideoCanvas[nFoundIndex]);
	m_mapUIDToWndIndex.SetAt(nUID, nFoundIndex);
*/
}


void CChildView::OnBtnJoinChannel()
{
	int				nRet = 0;
	CString			str;
	CDlgJoinChannel dlg(this);
	RtcEngineParameters rep(m_lpRTCEngine);

	if( dlg.DoModal() != IDOK)
		return;

	m_lpRTCEngine->enableVendorMessage();
	if(dlg.GetWorkMode() == CDlgJoinChannel::WORKMODE_MEDIA)
		m_lpRTCEngine->enableVideo();
	else
		m_lpRTCEngine->disableVideo();

	if(dlg.IsPureRecvMode())
		rep.setPureRecvMode(true);
	else
		rep.setPureRecvMode(false);

	switch (dlg.GetDecodeMode())
	{
	case CDlgJoinChannel::CODER_AGORA:
		{
			rep.setStandVP8Mode(false);
		}
		break;
	case CDlgJoinChannel::CODER_VP8:
		{
			rep.setStandVP8Mode(true);
		}
		break;
	default:
		{
			rep.setStandVP8Mode(false);
		}
		break;
	}

	/*make sure the resolution is supported by your video camera*/
	switch (dlg.GetMaxResolution())
	{
	case CDlgJoinChannel::MAXRES_DEFAULT:
		break;
	case CDlgJoinChannel::MAXRES_720P:
		rep.setVideoResolution(1280, 720);
		break;
	case CDlgJoinChannel::MAXRES_1080P:
		rep.setVideoResolution(1920, 1080);
		break;
	default:
		break;
	}

	VideoCanvas canvas;
	canvas.uid = 0;
	canvas.view = m_wndLocalVideo.GetVideoSafeHwnd();
	canvas.renderMode = RENDER_MODE_HIDDEN;
	m_lpRTCEngine->setupLocalVideo(canvas);

#ifdef UNICODE
	CHAR szVendorKey[128];
	CHAR szChannelName[128];

	str = dlg.GetVendorKey();
	::WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, str, -1, szVendorKey, 128, NULL ,NULL);

	str = dlg.GetChannelName();
	::WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, str, -1, szChannelName, 128, NULL ,NULL);

	nRet = m_lpRTCEngine->joinChannel(szVendorKey, szChannelName, "", dlg.GetUID());
#else
	nRet = m_lpRTCEngine->joinChannel(dlg.GetVendorKey(), dlg.GetChannelName(), "", dlg.GetUID());
#endif

	if(nRet == 0) {
		rep.enableAudioVolumeIndication(1000, 10);

		CMFCRibbonStatusBar *lpStatusBar = (CMFCRibbonStatusBar *)AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR);
		CMFCRibbonStatusBarPane* lpTextInfo = (CMFCRibbonStatusBarPane *)lpStatusBar->FindByID(ID_STATUSBAR_USERSTATUS);
		CMFCRibbonStatusBarPane* lpRoomInfo = (CMFCRibbonStatusBarPane *)lpStatusBar->FindByID(ID_STATUSBAR_ROOMINFO);

		lpTextInfo->SetText(_T("成功指令已发送"));
		lpTextInfo->Redraw();

		str.Format(_T("等待加入房间: %s"), dlg.GetChannelName());
		lpRoomInfo->SetText(str);
		lpRoomInfo->Redraw();
	}
	else{
		str.Format(_T("登陆失败, 错误号:0x%08X"), nRet);
		MessageBox(str, _T("错误"), MB_OK|MB_ICONERROR);
	}
}

void CChildView::OnBtnLeaveChannel()
{
	if(m_lpRTCEngine != NULL)
		m_lpRTCEngine->leaveChannel();

	m_ctrUserList.DeleteAllItems();

	Sleep(200);
	m_wndLocalVideo.SetUID(0);
	for(int nIndex = 0; nIndex < 4; nIndex++)
		m_wndRemoteVideo[nIndex].SetUID(0);

	CMFCRibbonStatusBar *lpStatusBar = (CMFCRibbonStatusBar *)AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	CMFCRibbonStatusBarPane* lpTextInfo = (CMFCRibbonStatusBarPane *)lpStatusBar->FindByID(ID_STATUSBAR_USERSTATUS);
	CMFCRibbonStatusBarPane* lpRoomInfo = (CMFCRibbonStatusBarPane *)lpStatusBar->FindByID(ID_STATUSBAR_ROOMINFO);

	lpTextInfo->SetText(_T("已退出房间"));
	lpTextInfo->Redraw();

	lpRoomInfo->SetText(_T("未加入房间"));
	lpRoomInfo->Redraw();

	Invalidate(TRUE);
	UpdateWindow();
}

void CChildView::OnBtnSetup()
{
	CSetupSheet SetupSheet(this);

	SetupSheet.DoModal();
}

void CChildView::OnBtnSendChatMessage()
{
	int nCoreLen = (m_ctrChatBox.GetWindowText((LPTSTR)m_lpCoreBuf, 1400-sizeof(PRI_PROTOCOL_HEADER))+1)*sizeof(TCHAR);

	m_lpHeader->dwMsgID = PRI_MSGID_CHAT;
	m_lpHeader->dwFlag = 0;
	m_lpHeader->dwSEQ = 0;
	m_lpHeader->dwPackLen = nCoreLen;
	
	int nDataLen = sizeof(PRI_PROTOCOL_HEADER)+nCoreLen;

	m_lpRTCEngine->sendVendorMessage((char *)m_lpProtocalBuf, nDataLen);

	CString str;
	SYSTEMTIME st;

	::GetLocalTime(&st);

	LPCTSTR lpText = (LPCTSTR)m_lpCoreBuf;
	str.Format(_T("[I Said]-%d:%d %ds:\r\n%s\r\n"), st.wHour, st.wMinute, st.wSecond, lpText);
	m_ctrHistroyBox.SetWindowText(str);

	m_ctrChatBox.SetWindowText(_T(""));
}

void CChildView::OnBtnTestSend()
{
	int nCoreLen = rand()%(1400-sizeof(PRI_PROTOCOL_HEADER));

	m_lpHeader->dwMsgID = PRI_MSGID_TEST;
	m_lpHeader->dwFlag = 0;
	m_lpHeader->dwSEQ = 0;
	m_lpHeader->dwPackLen = nCoreLen;

	int nDataLen = sizeof(PRI_PROTOCOL_HEADER)+nCoreLen;

	for(int nIndex = 0; nIndex < nCoreLen; nIndex++){
		m_lpCoreBuf[nIndex] = rand()%0x100;
	}

	m_lpRTCEngine->sendVendorMessage((char *)m_lpProtocalBuf, nDataLen);

	CString str;
	SYSTEMTIME st;

	::GetLocalTime(&st);

	str.Format(_T("[Test Data Sent]-%d:%d %ds:\r\n Len:%dBytes, CRC32:0x%08X.\r\n"), st.wHour, st.wMinute, st.wSecond, nCoreLen, ::GetDataCRC32(m_lpCoreBuf, nCoreLen, 0));
	m_ctrHistroyBox.SetWindowText(str);
}

void CChildView::OnNMClickVideoWnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMAGVIDEOWND pNMVideoWnd = reinterpret_cast<LPNMAGVIDEOWND>(pNMHDR);
	RtcEngineParameters rep(m_lpRTCEngine);
	CAgoraVideoWnd *lpAgoraVideoWnd = (CAgoraVideoWnd *)GetDlgItem(pNMVideoWnd->hdr.idFrom);

	DWORD dwUserFlag = lpAgoraVideoWnd->GetUserFlag();
	BOOL bValue = FALSE;

	switch (pNMVideoWnd->nMousePos)
	{
	case CAgoraVideoWnd::MOUSE_POS_BIGSCREEN:
		
		for(int nIndex = 0; nIndex < 4; nIndex++) {
			if(m_wndRemoteVideo[nIndex].GetUID() == pNMVideoWnd->nUID) {
				
//				m_wndRemoteVideo[nIndex].SetUID(0);
				m_dlgMaxVideo.SetUID(pNMVideoWnd->nUID);
		
				m_dlgMaxVideo.ShowWindow(SW_MAXIMIZE);
				VideoCanvas canvas;
				canvas.uid = pNMVideoWnd->nUID;
				canvas.view = m_dlgMaxVideo.GetSafeHwnd();
				canvas.renderMode = agora::rtc::RENDER_MODE_TYPE::RENDER_MODE_HIDDEN;
				
				m_lpRTCEngine->setupRemoteVideo(canvas);

				break;
			}
		}

		break;
	case CAgoraVideoWnd::MOUSE_POS_MUTEVIDEO:
		bValue = lpAgoraVideoWnd->IsVideoMuted();

		break;
	case CAgoraVideoWnd::MOUSE_POS_MUTEAUDIO:
		bValue = lpAgoraVideoWnd->IsAudioMuted();
		if(rep.muteRemoteAudioStream(lpAgoraVideoWnd->GetUID(), !bValue) == 0)
			lpAgoraVideoWnd->SetMuteAudioFlag(!bValue);
		break;
	default:
		break;
	}

	Invalidate();
	UpdateWindow();
}

void CChildView::OnNMClickLocalVideoWnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMAGVIDEOWND pNMVideoWnd = reinterpret_cast<LPNMAGVIDEOWND>(pNMHDR);
	RtcEngineParameters rep(m_lpRTCEngine);
	CAgoraVideoWnd *lpAgoraVideoWnd = (CAgoraVideoWnd *)GetDlgItem(pNMVideoWnd->hdr.idFrom);

	DWORD dwUserFlag = lpAgoraVideoWnd->GetUserFlag();
	BOOL bValue = FALSE;

	switch (pNMVideoWnd->nMousePos)
	{
	case CAgoraVideoWnd::MOUSE_POS_BIGSCREEN:
		break;
	case CAgoraVideoWnd::MOUSE_POS_MUTEVIDEO:
		bValue = lpAgoraVideoWnd->IsVideoMuted();
		if(rep.muteLocalVideoStream(!bValue) == 0)
			lpAgoraVideoWnd->SetMuteVideoFlag(!bValue);
		break;
	case CAgoraVideoWnd::MOUSE_POS_MUTEAUDIO:
		bValue = lpAgoraVideoWnd->IsAudioMuted();
		if(rep.muteLocalAudioStream(!bValue) == 0)
			lpAgoraVideoWnd->SetMuteAudioFlag(!bValue);
		break;
	default:
		break;
	}

	Invalidate();
	UpdateWindow();
}

LRESULT CChildView::OnMaxVideoWndClosed(WPARAM wParam, LPARAM lParam)
{
	for(int nIndex = 0; nIndex < 4; nIndex++) {
		if(m_wndRemoteVideo[nIndex].GetUID() == m_dlgMaxVideo.GetUID()) {
	
			VideoCanvas canvas;
			canvas.uid = m_wndRemoteVideo[nIndex].GetUID();
			canvas.view = m_wndRemoteVideo[nIndex].GetVideoSafeHwnd();
			canvas.renderMode = agora::rtc::RENDER_MODE_TYPE::RENDER_MODE_HIDDEN;

			m_lpRTCEngine->setupRemoteVideo(canvas);

			break;
		}
	}

	return 0;
}

LRESULT CChildView::OnEIDJoinChannelSuccess(WPARAM wParam, LPARAM lParam)
{
	LPAGE_JOINCHANNEL_SUCCESS lpData = (LPAGE_JOINCHANNEL_SUCCESS)wParam;

	CString	str;

	int nIndex = m_ctrUserList.GetItemCount();

	str.Format(_T("%u"), lpData->uid);
	m_ctrUserList.InsertItem(nIndex, str, 0);
	str.Format(_T("%d"), lpData->elapsed);
	m_ctrUserList.SetItemText(nIndex, 1, str);
	m_ctrUserList.SetItemData(nIndex, lpData->uid);
	m_wndLocalVideo.SetUID(lpData->uid);

#ifdef UNICODE
	WCHAR wszChannelName[64];
	::MultiByteToWideChar(CP_UTF7, 0, lpData->channel, -1, wszChannelName, 64);
	m_strRoomName = wszChannelName;
#else
	wszChannelName = lpData->channel;
#endif


	str.Format(_T("ROOM:%s(%d)"), m_strRoomName, m_ctrUserList.GetItemCount());
	CMFCRibbonStatusBar *lpStatusBar = (CMFCRibbonStatusBar *)AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	CMFCRibbonStatusBarPane* lpTextInfo = (CMFCRibbonStatusBarPane *)lpStatusBar->FindByID(ID_STATUSBAR_USERSTATUS);
	CMFCRibbonStatusBarPane* lpRoomInfo = (CMFCRibbonStatusBarPane *)lpStatusBar->FindByID(ID_STATUSBAR_ROOMINFO);

	lpTextInfo->SetText(_T("登录房间成功"));
	lpTextInfo->Redraw();

	lpRoomInfo->SetText(str);
	lpRoomInfo->Redraw();

	delete [] lpData->channel;
	delete lpData;

	return 0;
}

LRESULT CChildView::OnEIDReJoinChannelSuccess(WPARAM wParam, LPARAM lParam)
{
	LPAGE_JOINCHANNEL_SUCCESS lpData = (LPAGE_JOINCHANNEL_SUCCESS)wParam;

	CString str;

	LVFINDINFO FindInfo;

	FindInfo.flags = LVFI_PARAM;
	FindInfo.lParam = (LPARAM)lpData->uid;

	int nIndex = m_ctrUserList.FindItem(&FindInfo);
	if(nIndex != -1)		// find it
		m_ctrUserList.SetItem(nIndex, 0, LVIF_IMAGE, NULL, 0, 0, 0, 0);
	else{					// must insert
		nIndex = m_ctrUserList.GetItemCount();
		str.Format(_T("%u"), lpData->uid);
		m_ctrUserList.InsertItem(nIndex, str, 0);
	}

	str.Format(_T("%d"), lpData->elapsed);
	m_ctrUserList.SetItemText(nIndex, 1, str);
	m_ctrUserList.SetItemData(nIndex, (DWORD_PTR)lpData->uid);

	
	CMFCRibbonStatusBar *lpStatusBar = (CMFCRibbonStatusBar *)AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	CMFCRibbonStatusBarPane* lpTextInfo = (CMFCRibbonStatusBarPane *)lpStatusBar->FindByID(ID_STATUSBAR_USERSTATUS);
	CMFCRibbonStatusBarPane* lpRoomInfo = (CMFCRibbonStatusBarPane *)lpStatusBar->FindByID(ID_STATUSBAR_ROOMINFO);

	str.Format(_T("%u重登录房间成功"), lpData->uid);
	lpTextInfo->SetText(str);
	lpTextInfo->Redraw();

	str.Format(_T("ROOM:%s(%d)"), m_strRoomName, m_ctrUserList.GetItemCount());
	lpRoomInfo->SetText(str);
	lpRoomInfo->Redraw();

	Invalidate(TRUE);
	UpdateWindow();

	delete [] lpData->channel;
	delete lpData;

	return 0;
}

LRESULT CChildView::OnEIDError(WPARAM wParam, LPARAM lParam)
{
	LPAGE_ERROR lpData = (LPAGE_ERROR)wParam;

	CString str;

#ifdef UNICODE
	WCHAR wszMsg[128];

	if(lpData->msg != NULL) {
		::MultiByteToWideChar(CP_ACP, 0, lpData->msg, -1, wszMsg, 128);
	}
	else
		_tcscpy_s(wszMsg, 128, _T("(empty message)"));
	str.Format(_T("本次操作出错:0x%08X(%s)"), lpData->err, wszMsg);
#else
	str.Format(_T("本次操作出错:0x%08X(%s)"), lpData->err, lpData->msg);
#endif

	CMFCRibbonStatusBar *lpStatusBar = (CMFCRibbonStatusBar *)AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	CMFCRibbonStatusBarPane* lpTextInfo = (CMFCRibbonStatusBarPane *)lpStatusBar->FindByID(ID_STATUSBAR_USERSTATUS);
	lpTextInfo->SetText(str);
	lpTextInfo->Redraw();

	Invalidate(TRUE);
	UpdateWindow();

	if(lpData->msg != NULL)
		delete [] lpData->msg;

	delete lpData;

	return 0;
}

LRESULT CChildView::OnEIDAudioVolumeIndication(WPARAM wParam, LPARAM lParam)
{
	LPAGE_AUDIO_VOLUME_INDICATION lpData = (LPAGE_AUDIO_VOLUME_INDICATION)wParam;

	for(int nIndex = 0; nIndex < 4; nIndex++)
		m_wndRemoteVideo[nIndex].SetCurVol(0);

	m_wndLocalVideo.SetCurVol(0);

	for(int i = 0; i < (int)lpData->speakerNumber; i++){
		for(int j = 0; j < 4; j++) {
			if(lpData->speakers[i].uid == m_wndRemoteVideo[j].GetUID())
				m_wndRemoteVideo[j].SetCurVol(lpData->speakers[i].volume);
		}

		if(m_wndLocalVideo.GetUID() == lpData->speakers[i].uid)
			m_wndLocalVideo.SetCurVol(lpData->speakers[i].volume);
	}

	delete [] lpData->speakers;
	delete lpData;

	return 0;
}

LRESULT CChildView::OnEIDNetworkQuality(WPARAM wParam, LPARAM lParam)
{
	LPAGE_NETWORK_QUALITY lpData = (LPAGE_NETWORK_QUALITY)wParam;
	CMFCRibbonStatusBar *lpStatusBar = (CMFCRibbonStatusBar *)AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	CMFCRibbonStatusBarPane* lpNetInfo = (CMFCRibbonStatusBarPane *)lpStatusBar->FindByID(ID_STATUSBAR_NETINFO);

	CString str;

	str.Format(_T("网络质量:%d"), lpData->quality);
	lpNetInfo->SetText(str);
	lpNetInfo->Redraw();

	delete lpData;
	return 0;
}

LRESULT CChildView::OnEIDFirstFrameDecoded(WPARAM wParam, LPARAM lParam)
{
	LPAGE_FIRST_REMOTE_VIDEO_DECODED lpData = (LPAGE_FIRST_REMOTE_VIDEO_DECODED)wParam;
	int nFreeWndIndex = -1;

	VideoCanvas canvas;
	canvas.uid = lpData->uid;
	canvas.renderMode = agora::rtc::RENDER_MODE_TYPE::RENDER_MODE_HIDDEN;

	for(int nIndex = 0; nIndex < 4; nIndex++) {
		if(m_wndRemoteVideo[nIndex].IsWndFree()){
			if(nFreeWndIndex < 0)
				nFreeWndIndex = nIndex;
		}
		else{
			if(m_wndRemoteVideo[nIndex].GetUID() == lpData->uid) {
				nFreeWndIndex = nIndex;
				break;
			}
		}
	}

	if(nFreeWndIndex != -1){
		canvas.view = m_wndRemoteVideo[nFreeWndIndex].GetVideoSafeHwnd();
		m_wndRemoteVideo[nFreeWndIndex].SetUID(lpData->uid);
		m_lpRTCEngine->setupRemoteVideo(canvas);
	}

	delete lpData;

	return 0;
}

LRESULT CChildView::OnEIDUserJoined(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_JOINED lpData = (LPAGE_USER_JOINED)wParam;

	CString str;

	LVFINDINFO FindInfo;

	FindInfo.flags = LVFI_PARAM;
	FindInfo.lParam = (LPARAM)lpData->uid;

	int nIndex = m_ctrUserList.FindItem(&FindInfo);
	if(nIndex != -1)		// find it
		m_ctrUserList.SetItem(nIndex, 0, LVIF_IMAGE, NULL, 0, 0, 0, 0);
	else{					// must insert
		nIndex = m_ctrUserList.GetItemCount();
		str.Format(_T("%u"), lpData->uid);
		m_ctrUserList.InsertItem(nIndex, str, 0);
	}

	str.Format(_T("%d"), lpData->elapsed);
	m_ctrUserList.SetItemText(nIndex, 1, str);
	m_ctrUserList.SetItemData(nIndex, (DWORD_PTR)lpData->uid);

	
	CMFCRibbonStatusBar *lpStatusBar = (CMFCRibbonStatusBar *)AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	CMFCRibbonStatusBarPane* lpTextInfo = (CMFCRibbonStatusBarPane *)lpStatusBar->FindByID(ID_STATUSBAR_USERSTATUS);
	CMFCRibbonStatusBarPane* lpRoomInfo = (CMFCRibbonStatusBarPane *)lpStatusBar->FindByID(ID_STATUSBAR_ROOMINFO);
	
	str.Format(_T("用户%u加入房间"), lpData->uid);
	lpTextInfo->SetText(str);
	lpTextInfo->Redraw();

	str.Format(_T("ROOM:%s(%d)"), m_strRoomName, m_ctrUserList.GetItemCount());
	lpRoomInfo->SetText(str);
	lpRoomInfo->Redraw();

	Invalidate(TRUE);
	UpdateWindow();

	delete lpData;

	return 0;
}

LRESULT CChildView::OnEIDUserOffline(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_OFFLINE lpData = (LPAGE_USER_OFFLINE)wParam;

	CString str;

	LVFINDINFO FindInfo;

	FindInfo.flags = LVFI_PARAM;
	FindInfo.lParam = (LPARAM)lpData->uid;

	int nIndex = m_ctrUserList.FindItem(&FindInfo);
	if(nIndex != -1)		// find it
		m_ctrUserList.DeleteItem(nIndex);

	for(int nIndex = 0; nIndex < 4; nIndex++){
		if(m_wndRemoteVideo[nIndex].GetUID() == lpData->uid){
			m_wndRemoteVideo[nIndex].SetUID(0);
		}
	}

	CMFCRibbonStatusBar *lpStatusBar = (CMFCRibbonStatusBar *)AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	CMFCRibbonStatusBarPane* lpTextInfo = (CMFCRibbonStatusBarPane *)lpStatusBar->FindByID(ID_STATUSBAR_USERSTATUS);
	CMFCRibbonStatusBarPane* lpRoomInfo = (CMFCRibbonStatusBarPane *)lpStatusBar->FindByID(ID_STATUSBAR_ROOMINFO);

	str.Format(_T("用户%u离开房间"), lpData->uid);
	lpTextInfo->SetText(str);
	lpTextInfo->Redraw();

	str.Format(_T("ROOM:%s(%d)"), m_strRoomName, m_ctrUserList.GetItemCount());
	lpRoomInfo->SetText(str);
	lpRoomInfo->Redraw();

	Invalidate(TRUE);
	UpdateWindow();

	delete lpData;

	return 0;
}

LRESULT CChildView::OnEIDConnectionLost(WPARAM wParam, LPARAM lParam)
{

	return 0;
}

LRESULT CChildView::OnEIDVendorMessage(WPARAM wParam, LPARAM lParam)
{
	LPAGE_VENDOR_MESSAGE lpData = (LPAGE_VENDOR_MESSAGE)wParam;

	LPPRI_PROTOCOL_HEADER lpHeader = (LPPRI_PROTOCOL_HEADER)lpData->data;

	LPBYTE lpCoreBuf = (LPBYTE)(lpData->data+sizeof(PRI_PROTOCOL_HEADER));

	switch (lpHeader->dwMsgID)
	{
	case PRI_MSGID_TEST:
		OnTestMsgReceived(lpData->uid, lpHeader, lpCoreBuf);
		break;
	case PRI_MSGID_CHAT:
		OnChatMsgReceived(lpData->uid, lpHeader, lpCoreBuf);
		break;
	case PRI_MSGID_TRSFILE:
		OnFileMsgReceived(lpData->uid, lpHeader, lpCoreBuf);
		break;
	default:
		break;
	}

	if(lpData->data != NULL)
		delete [] lpData->data;

	delete lpData;

	return 0;
}

void CChildView::OnTestMsgReceived(UINT nUID, LPPRI_PROTOCOL_HEADER lpHeader, LPCVOID lpData)
{
	CString str;
	SYSTEMTIME st;

	DWORD dwCRC32 = ::GetDataCRC32(lpData, lpHeader->dwPackLen, 0);

	::GetLocalTime(&st);

	str.Format(_T("[%u]-%d:%d %ds:\r\nTest Data Recevied: Len:%dBytes, CRC32:0x%08X.\r\n"), nUID, st.wHour, st.wMinute, st.wSecond, lpHeader->dwPackLen, dwCRC32);
	m_ctrHistroyBox.SetWindowText(str);
}

void CChildView::OnChatMsgReceived(UINT nUID, LPPRI_PROTOCOL_HEADER lpHeader, LPCVOID lpData)
{
	CString str;
	SYSTEMTIME st;

	::GetLocalTime(&st);

	LPCTSTR lpText = (LPCTSTR)lpData;
	str.Format(_T("[%u]-%d:%d %ds:\r\n%s\r\n"), nUID, st.wHour, st.wMinute, st.wSecond, lpText);
	m_ctrHistroyBox.SetWindowText(str);
}

void CChildView::OnFileMsgReceived(UINT nUID, LPPRI_PROTOCOL_HEADER lpHeader, LPCVOID lpData)
{

}
