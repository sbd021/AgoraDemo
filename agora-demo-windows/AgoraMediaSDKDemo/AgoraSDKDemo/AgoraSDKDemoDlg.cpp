
// AgoraSDKDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraSDKDemo.h"
#include "AgoraSDKDemoDlg.h"

#include "DlgLogin.h"

#include "AGEventDef.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CAgoraSDKDemoDlg 对话框




CAgoraSDKDemoDlg::CAgoraSDKDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAgoraSDKDemoDlg::IDD, pParent)
	, m_lpRTCEngine(NULL)
	, m_bInChannel(FALSE)
	, m_nCurPeerUID(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	m_ctrBackBrush.CreateSolidBrush(RGB(0xB2, 0xD0, 0xFF));
	SetBackgroundColor(RGB(0xB2, 0xD0, 0xFF), TRUE);
}

void CAgoraSDKDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAgoraSDKDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTNCHCTRL_MAIN, &CAgoraSDKDemoDlg::OnBnClickedBtnloginMain)
	
	ON_BN_CLICKED(ID_IDR_MUTELAUDIO, &CAgoraSDKDemoDlg::OnBnClickedMuteLAudio)
	ON_BN_CLICKED(ID_IDR_MUTELVIDEO, &CAgoraSDKDemoDlg::OnBnClickedMuteLVideo)
	ON_BN_CLICKED(ID_IDR_MUTERAUDIO, &CAgoraSDKDemoDlg::OnBnClickedMuteRAudio)
	ON_BN_CLICKED(ID_IDR_MUTERVIDEO, &CAgoraSDKDemoDlg::OnBnClickedMuteRVideo)
	
	ON_NOTIFY(NM_CLICK, IDW_BIGVIDEO, &CAgoraSDKDemoDlg::OnNMClickVideoWnd)

	ON_NOTIFY(NM_CLICK, IDW_SMALLVIDEO+0, &CAgoraSDKDemoDlg::OnNMClickVideoWnd)
	ON_NOTIFY(NM_CLICK, IDW_SMALLVIDEO+1, &CAgoraSDKDemoDlg::OnNMClickVideoWnd)
	ON_NOTIFY(NM_CLICK, IDW_SMALLVIDEO+2, &CAgoraSDKDemoDlg::OnNMClickVideoWnd)
	ON_NOTIFY(NM_CLICK, IDW_SMALLVIDEO+3, &CAgoraSDKDemoDlg::OnNMClickVideoWnd)

	ON_MESSAGE(WM_MSGID(EID_JOINCHANNEL_SUCCESS), &CAgoraSDKDemoDlg::OnEIDJoinChannelSuccess)
	ON_MESSAGE(WM_MSGID(EID_REJOINCHANNEL_SUCCESS), &CAgoraSDKDemoDlg::OnEIDReJoinChannelSuccess)
	ON_MESSAGE(WM_MSGID(EID_ERROR), &CAgoraSDKDemoDlg::OnEIDError)
	ON_MESSAGE(WM_MSGID(EID_AUDIO_VOLUME_INDICATION), &CAgoraSDKDemoDlg::OnAudioVolumeIndication)

	ON_MESSAGE(WM_MSGID(EID_FIRST_REMOTE_VIDEO_DECODED), &CAgoraSDKDemoDlg::OnEIDFirstFrameDecoded)

	ON_MESSAGE(WM_MSGID(EID_USER_JOINED), &CAgoraSDKDemoDlg::OnEIDUserJoined)
	ON_MESSAGE(WM_MSGID(EID_USER_OFFLINE), &CAgoraSDKDemoDlg::OnEIDUserOffline)
	ON_MESSAGE(WM_MSGID(EID_CONNECTION_LOST), &CAgoraSDKDemoDlg::OnEIDConnectionLost)

END_MESSAGE_MAP()


// CAgoraSDKDemoDlg 消息处理程序

BOOL CAgoraSDKDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect		rcChildRect;

	rcChildRect.SetRect(10, 10, 425, 430);

	m_AVWBig.Create(NULL, _T("BigVideo"), WS_BORDER | WS_VISIBLE | WS_VISIBLE, rcChildRect, this, IDW_BIGVIDEO);

	for(int nIndex = 0; nIndex < 4; nIndex++) {
		rcChildRect.SetRect(10+105*nIndex, 435, 110+105*nIndex, 545);
		m_AVWSmall[nIndex].Create(NULL, _T("SmallVideo"), WS_BORDER | WS_VISIBLE | WS_VISIBLE, rcChildRect, this, IDW_SMALLVIDEO+nIndex);
	}

	m_lpRTCEngine = CAgoraObject::GetEngine(AfxGetMainWnd()->GetSafeHwnd());

	CString strEngineVer;
	
#ifdef UNICODE
	const char *szEngineVer = getAgoraRtcEngineVersion();

	WCHAR wszEngineVer[128];

	::MultiByteToWideChar(CP_ACP, 0, szEngineVer, -1, wszEngineVer, 128);

	strEngineVer.Format(_T("SDKVer: %s"), wszEngineVer);
	SetDlgItemText(IDC_STSDKVER_MAIN, strEngineVer);
#else
	strEngineVer.Format(_T("SDKVersion: %s"), getAgoraRtcEngineVersion());
	SetDlgItemText(IDC_STSDKVER_MAIN, strEngineVer);
#endif

	GetWindowText(m_strTitle);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAgoraSDKDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAgoraSDKDemoDlg::OnPaint()
{
	CPaintDC dc(this);

	if (IsIconic())
	{

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		dc.SetBkColor(RGB(0xB2, 0xD0, 0xFF));
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAgoraSDKDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAgoraSDKDemoDlg::OnBnClickedBtnloginMain()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bInChannel) {
		OnLoginChannel();

		RtcEngineParameters rep(m_lpRTCEngine);
		rep.enableAudioVolumeIndication(1000, 10);

	}
	else{
		OnLeavelChannel();
	}

}


void CAgoraSDKDemoDlg::OnLoginChannel()
{
	CDlgLogin dlg(this);

	if(dlg.DoModal() != IDOK)
		return;

	int		nEngineMode = dlg.GetEngineMode();
	CString	strVendorKey = dlg.GetVendorKey();
	CString strChannelName = dlg.GetChannelName();
	UINT	nUID = dlg.GetUID();

	if (nEngineMode == 1)
	{
		m_lpRTCEngine->enableVideo();

		VideoCanvas canvas;
		canvas.uid = 0;
		canvas.view = m_AVWBig.GetVideoSafeHwnd();
		canvas.renderMode = RENDER_MODE_HIDDEN;
		m_lpRTCEngine->setupLocalVideo(canvas);
	}
	else
		m_lpRTCEngine->disableVideo();

#ifdef UNICODE

	CHAR szVendorKey[64];
	CHAR szChannelName[64];

	memset(szVendorKey, 0, sizeof(CHAR)*64);
	memset(szChannelName, 0, sizeof(CHAR)*64);

	::WideCharToMultiByte(CP_ACP, 0, strVendorKey, -1, szVendorKey, 64, NULL ,NULL);
	::WideCharToMultiByte(CP_ACP, 0, strChannelName, -1, szChannelName, 64, NULL ,NULL);

	int nRet = m_lpRTCEngine->joinChannel(szVendorKey, szChannelName, "", dlg.GetUID());
#else
	int nRet = m_lpRTCEngine->joinChannel(dlg.GetVendorKey(), dlg.GetChannelName(), "", dlg.GetUID());
#endif

	CString str;

	if(nRet == 0) {
		str.Format(_T("%s-[频道: %s]"), m_strTitle, strChannelName);
		SetWindowText(str);
	}
	else{
		str.Format(_T("登陆失败, 错误号:0x%08X"), nRet);
		MessageBox(str, _T("错误"), MB_OK|MB_ICONERROR);
	}
}

void CAgoraSDKDemoDlg::OnLeavelChannel()
{
	m_lpRTCEngine->leaveChannel();

	m_AVWBig.Invalidate();
	m_AVWBig.UpdateWindow();

	for(int nIndex = 0; nIndex < 4; nIndex++){
		m_AVWSmall[nIndex].SetUID(0);	
		m_AVWSmall[nIndex].Invalidate();
		m_AVWSmall[nIndex].UpdateWindow();
	}

	SetWindowText(m_strTitle);

	SetDlgItemText(IDC_BTNCHCTRL_MAIN, _T("退出频道"));
	m_bInChannel = FALSE;
}

void CAgoraSDKDemoDlg::OnNMClickVideoWnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMAGVIDEOWND pNMVideoWnd = reinterpret_cast<LPNMAGVIDEOWND>(pNMHDR);

	CMenu	Menu;
	CPoint	Point;
	
	::GetCursorPos(&Point);
	// BigWnd
	if( pNMVideoWnd->hdr.hwndFrom == m_AVWBig.GetSafeHwnd()) {
		Menu.LoadMenu(IDR_MENU_LOCALCTRL);

		Menu.CheckMenuItem(ID_IDR_MUTELAUDIO, (pNMVideoWnd->dwUserFlag&AGUSER_MUTEAUDIO)? MF_CHECKED : MF_UNCHECKED);
		Menu.CheckMenuItem(ID_IDR_MUTELVIDEO, (pNMVideoWnd->dwUserFlag&AGUSER_MUTEVIDEO)? MF_CHECKED : MF_UNCHECKED);
	}
	else {
		m_nCurPeerUID = pNMVideoWnd->nUID;
		Menu.LoadMenu(IDR_MENU_RMTCTRL);

		Menu.CheckMenuItem(ID_IDR_MUTERAUDIO, (pNMVideoWnd->dwUserFlag&AGUSER_MUTEAUDIO)? MF_CHECKED : MF_UNCHECKED);
		Menu.CheckMenuItem(ID_IDR_MUTERVIDEO, (pNMVideoWnd->dwUserFlag&AGUSER_MUTEVIDEO)? MF_CHECKED : MF_UNCHECKED);
		Menu.EnableMenuItem(ID_IDR_MUTERVIDEO, MF_DISABLED);
	}

	CMenu *lpMenuPopup = Menu.GetSubMenu(0);
	lpMenuPopup->TrackPopupMenu(TPM_RIGHTBUTTON, Point.x, Point.y, this);
	lpMenuPopup->DestroyMenu();

	Invalidate();
	UpdateWindow();
}

void CAgoraSDKDemoDlg::OnBnClickedMuteLAudio()
{
	BOOL bMuted = m_AVWBig.IsAudioMuted();

	RtcEngineParameters rep(m_lpRTCEngine);
	if(rep.muteLocalAudioStream(!bMuted) == 0)
		m_AVWBig.SetMuteAudioFlag(!bMuted);
}

void CAgoraSDKDemoDlg::OnBnClickedMuteLVideo()
{
	BOOL bMuted = m_AVWBig.IsVideoMuted();

	RtcEngineParameters rep(m_lpRTCEngine);
	if(rep.muteLocalVideoStream(!bMuted) == 0)
		m_AVWBig.SetMuteVideoFlag(!bMuted);
}

void CAgoraSDKDemoDlg::OnBnClickedMuteRAudio()
{
	CAgoraVideoWnd *lpRemoteViedo = NULL;
	for(int nIndex = 0; nIndex < 4; nIndex++){
		if(m_AVWSmall[nIndex].GetUID() == m_nCurPeerUID) {
			lpRemoteViedo = &m_AVWSmall[nIndex];
			break;
		}
	}

	if(lpRemoteViedo == NULL)
		return;

	BOOL bMuted = lpRemoteViedo->IsAudioMuted();

	RtcEngineParameters rep(m_lpRTCEngine);
//	if(rep.muteRemoteAudioStream(m_nCurPeerUID, !bMuted) == 0)
//		lpRemoteViedo->SetMuteAudioFlag(!bMuted);
}

void CAgoraSDKDemoDlg::OnBnClickedMuteRVideo()
{
/*	CAgoraVideoWnd *lpRemoteViedo = NULL;
	for(int nIndex = 0; nIndex < 4; nIndex++){
		if(m_AVWSmall[nIndex].GetUID() == m_nCurPeerUID) {
			lpRemoteViedo = &m_AVWSmall[nIndex];
			break;
		}
	}

	if(lpRemoteViedo == NULL)
		return;

	BOOL bMuted = lpRemoteViedo->IsVideoMuted();

	RtcEngineParameters rep(m_lpRTCEngine);
	if(rep.muteRemoteVideoStream(m_nCurPeerUID, !bMuted) == 0)
		lpRemoteViedo->SetMuteAudioFlag(!bMuted);
*/
}

LRESULT CAgoraSDKDemoDlg::OnEIDJoinChannelSuccess(WPARAM wParam, LPARAM lParam)
{
	LPAGE_JOINCHANNEL_SUCCESS lpData = (LPAGE_JOINCHANNEL_SUCCESS)wParam;

	m_AVWBig.SetUID(lpData->uid);
	m_bInChannel = TRUE;
	SetDlgItemText(IDC_BTNCHCTRL_MAIN, _T("退出频道"));

	delete [] lpData->channel;
	delete lpData;

	return 0;
}

LRESULT CAgoraSDKDemoDlg::OnEIDReJoinChannelSuccess(WPARAM wParam, LPARAM lParam)
{
	LPAGE_JOINCHANNEL_SUCCESS lpData = (LPAGE_JOINCHANNEL_SUCCESS)wParam;

	m_AVWBig.SetUID(lpData->uid);
	m_bInChannel = TRUE;

	SetDlgItemText(IDC_BTNCHCTRL_MAIN, _T("退出频道"));
	SetDlgItemText(IDC_STSTATUS_MAIN, _T("重登录频道成功"));

	Invalidate(TRUE);
	UpdateWindow();

	delete [] lpData->channel;
	delete lpData;

	return 0;
}

LRESULT CAgoraSDKDemoDlg::OnEIDError(WPARAM wParam, LPARAM lParam)
{
	LPAGE_ERROR lpData = (LPAGE_ERROR)wParam;

	CString str;

#ifdef UNICODE
	WCHAR wszMsg[128];

	::MultiByteToWideChar(CP_ACP, 0, lpData->msg, -1, wszMsg, 128);
	str.Format(_T("本次操作出错:0x%08X(%s)"), lpData->err, wszMsg);
#else
	str.Format(_T("本次操作出错:0x%08X(%s)"), lpData->err, lpData->msg);
#endif

	// MFC featurePack的BUG，渲染主窗口背景的时候直接透明化了static子控件背景
	// 这里内容改变后必须强制重绘，否则会产生重影(下同)
	SetDlgItemText(IDC_STSTATUS_MAIN, str);
	Invalidate(TRUE);
	UpdateWindow();

	delete [] lpData->msg;
	delete lpData;

	return 0;
}

LRESULT CAgoraSDKDemoDlg::OnAudioVolumeIndication(WPARAM wParam, LPARAM lParam)
{
	LPAGE_AUDIO_VOLUME_INDICATION lpData = (LPAGE_AUDIO_VOLUME_INDICATION)wParam;

	for(int nIndex = 0; nIndex < 4; nIndex++)
		m_AVWSmall[nIndex].SetSpeakingFlag(FALSE);

	for(int i = 0; i < (int)lpData->speakerNumber; i++){
		for(int j = 0; j < 4; j++) {
			if(lpData->speakers[i].uid == m_AVWSmall[j].GetUID())
				m_AVWSmall[j].SetSpeakingFlag(TRUE);
		}
	}

	delete [] lpData->speakers;
	delete lpData;

	return 0;
}

LRESULT CAgoraSDKDemoDlg::OnEIDFirstFrameDecoded(WPARAM wParam, LPARAM lParam)
{
	LPAGE_FIRST_REMOTE_VIDEO_DECODED lpData = (LPAGE_FIRST_REMOTE_VIDEO_DECODED)wParam;

	VideoCanvas canvas;
	canvas.uid = lpData->uid;
	canvas.renderMode = agora::rtc::RENDER_MODE_TYPE::RENDER_MODE_HIDDEN;
	
	for(int nIndex = 0; nIndex < 4; nIndex++) {
		if(m_AVWSmall[nIndex].IsWndFree()){
			canvas.view = m_AVWSmall[nIndex].GetVideoSafeHwnd();
			m_AVWSmall[nIndex].SetUID(lpData->uid);
			m_lpRTCEngine->setupRemoteVideo(canvas);
			break;
		}
	}

	delete lpData;

	return 0;
}

LRESULT CAgoraSDKDemoDlg::OnEIDUserJoined(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_JOINED lpData = (LPAGE_USER_JOINED)wParam;

	CString str;

	str.Format(_T("用户%u加入频道(elps:%d)"), lpData->uid, lpData->elapsed);
	SetDlgItemText(IDC_STSTATUS_MAIN, str);
	Invalidate(TRUE);
	UpdateWindow();

	delete lpData;

	return 0;
}

LRESULT CAgoraSDKDemoDlg::OnEIDUserOffline(WPARAM wParam, LPARAM lParam)
{
	LPAGE_USER_OFFLINE lpData = (LPAGE_USER_OFFLINE)wParam;

	CString str;

	str.Format(_T("用户%u离开频道"), lpData->uid);
	SetDlgItemText(IDC_STSTATUS_MAIN, str);


	for(int nIndex = 0; nIndex < 4; nIndex++){
		if(m_AVWSmall[nIndex].GetUID() == lpData->uid){
			m_AVWSmall[nIndex].SetUID(0);
		}
	}

	Invalidate(TRUE);
	UpdateWindow();

	delete lpData;

	return 0;
}

LRESULT CAgoraSDKDemoDlg::OnEIDConnectionLost(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

void CAgoraSDKDemoDlg::OnNMClickSloptionMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
