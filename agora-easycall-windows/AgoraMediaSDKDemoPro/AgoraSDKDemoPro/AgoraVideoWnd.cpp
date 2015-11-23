// AgoraVideoWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraSDKDemoPro.h"
#include "AgoraVideoWnd.h"


// CAgoraVideoWnd

IMPLEMENT_DYNAMIC(CAgoraVideoWnd, CWnd)

CAgoraVideoWnd::CAgoraVideoWnd()
	: m_nUID(0)
	, m_dwUserFlag(AGUSER_NORMAL)
	, m_nVolbarPos(VOLBAR_RIGHT)
	, m_nVolRange(255)
	, m_nCurVol(0)
	, m_dwVolbarFreeColor(RGB(32, 32, 32))
	, m_dwVolbarBusyColor(RGB(208, 208, 208))
	, m_dwVolbarBackColor(RGB(64, 64, 64))
{

}

CAgoraVideoWnd::~CAgoraVideoWnd()
{
}


BEGIN_MESSAGE_MAP(CAgoraVideoWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CAgoraVideoWnd 消息处理程序



void CAgoraVideoWnd::OnPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	CPaintDC dc(this);
	CDC memDC;
	CBitmap memBitmap;

	memDC.CreateCompatibleDC(&dc);
	memBitmap.CreateCompatibleBitmap(&dc, m_rcClientRect.Width(), m_rcClientRect.Height());
	CBitmap *pOldBit=memDC.SelectObject(&memBitmap);

	memDC.FillSolidRect(0, 0, m_rcClientRect.Width(), 18, RGB(96, 96, 96));

	DrawUIDInfo(&memDC);
	DrawVolbar(&memDC);
	DrawButton(&memDC);
	
	dc.BitBlt(0, 0, m_rcClientRect.Width(), m_rcClientRect.Height(), &memDC, 0, 0, SRCCOPY);
}

void CAgoraVideoWnd::DrawUIDInfo(CDC *lpDC)
{
	CString strTitle;

	// set the UID
	GetWindowText(strTitle);
	CFont* lpDefFont = lpDC->SelectObject(&m_ftClient);
	lpDC->SetBkMode(TRANSPARENT);
	lpDC->SetTextColor(RGB(255, 255, 255));
	lpDC->TextOut(3, 3, strTitle);
	lpDC->SelectObject(lpDefFont);
}

void CAgoraVideoWnd::DrawVolbar(CDC *lpDC)
{
	// brush the video background
	lpDC->FillSolidRect(0, 18, m_rcClientRect.Width(), m_rcClientRect.Height()-18, RGB(128, 128, 128));
	lpDC->FillSolidRect(&m_rcVolBarRect, m_dwVolbarBackColor);

	int nMarkCount = m_rcVolBarRect.Height()/5;
	int nTopPoint = m_nCurVol*nMarkCount/m_nVolRange;

	for(int nIndex = 0; nIndex < nMarkCount; nIndex++) {
		if(nIndex <= nTopPoint)
			lpDC->FillSolidRect(m_rcVolBarRect.left, m_rcVolBarRect.bottom - 5*nIndex-3, m_rcVolBarRect.Width(), 3, m_dwVolbarBusyColor);
		else
			lpDC->FillSolidRect(m_rcVolBarRect.left, m_rcVolBarRect.bottom - 5*nIndex-3, m_rcVolBarRect.Width(), 3, m_dwVolbarFreeColor);
	}

}

void CAgoraVideoWnd::DrawButton(CDC *lpDC)
{
	if(m_nUID == 0)
		return;

	if(!IsBigScreen())
		m_imgBtnList.Draw(lpDC, 0, CPoint(m_rcClientRect.Width()-60, 1), ILD_TRANSPARENT);
	else
		m_imgBtnList.Draw(lpDC, 1, CPoint(m_rcClientRect.Width()-60, 1), ILD_TRANSPARENT);

	if(!IsVideoMuted())
		m_imgBtnList.Draw(lpDC, 2, CPoint(m_rcClientRect.Width()-40, 1), ILD_TRANSPARENT);
	else
		m_imgBtnList.Draw(lpDC, 3, CPoint(m_rcClientRect.Width()-40, 1), ILD_TRANSPARENT);

	if(!IsAudioMuted())
		m_imgBtnList.Draw(lpDC, 4, CPoint(m_rcClientRect.Width()-20, 1), ILD_TRANSPARENT);
	else
		m_imgBtnList.Draw(lpDC, 5, CPoint(m_rcClientRect.Width()-20, 1), ILD_TRANSPARENT);
}

int CAgoraVideoWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect		rcChildRect; 
	LOGFONT		lf;
	CBitmap		bmpBtnList;

	DWORD dwWndStyle = WS_VISIBLE | WS_VISIBLE;

	rcChildRect.SetRect(0, 18, lpCreateStruct->cx, lpCreateStruct->cy-18);

	m_wndVideoWnd.Create(NULL, _T("AgoraVideoWnd"), dwWndStyle, rcChildRect, this, IDC_STATIC);
	m_rcVolBarRect.SetRect(lpCreateStruct->cx-20, 18, lpCreateStruct->cx, lpCreateStruct->cy-18);

	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 12;
	lf.lfWeight = 400;

	::lstrcpy(lf.lfFaceName, _T("宋体"));
	m_ftClient.CreateFontIndirect(&lf);
	SetFont(&m_ftClient, TRUE);
	m_strFirstTitle = lpCreateStruct->lpszName;

	bmpBtnList.LoadBitmap(IDB_VIDEOWND_BTCTRL);
	m_imgBtnList.Create(16, 16, ILC_COLOR24|ILC_MASK, 6, 1);
	m_imgBtnList.Add(&bmpBtnList, RGB(255, 0, 255));

	m_ctrToolTip.Create(this, TTS_ALWAYSTIP);
	m_ctrToolTip.SetDelayTime(150);              

	return 0;
}

void CAgoraVideoWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_rcClientRect.SetRect(0, 0, cx, cy);

	switch (m_nVolbarPos)
	{
	case VOLBAR_LEFT:
		m_wndVideoWnd.MoveWindow(20, 18, cx, cy-18, TRUE);
		m_rcVolBarRect.SetRect(0, 18, 20, cy);
		break;
	case VOLBAR_RIGHT:
		m_wndVideoWnd.MoveWindow(0, 18, cx-20, cy-18, TRUE);
		m_rcVolBarRect.SetRect(cx-20, 18, cx, cy);
		break;
	default:
		m_wndVideoWnd.MoveWindow(0, 18, cx-20, cy-18, TRUE);
		m_rcVolBarRect.SetRect(cx-20, 18, cx, cy);
		break;
	}
}

void CAgoraVideoWnd::SetVolbarPos(int nPos)
{
	switch (nPos)
	{
	case VOLBAR_LEFT:
	case VOLBAR_RIGHT:
		m_nVolbarPos = nPos;
		break;
	default:
		m_nVolbarPos = VOLBAR_RIGHT;
		break;
	}

	InvalidateRect(&m_rcVolBarRect, TRUE);
}

int CAgoraVideoWnd::GetVolbarPos()
{
	return m_nVolbarPos;
}

// 音量条指示
void CAgoraVideoWnd::SetVolbarColor(DWORD dwFreeColor, DWORD dwBusyColor, DWORD dwBackColor)	// 设定空闲颜色
{
	m_dwVolbarFreeColor = dwFreeColor;
	m_dwVolbarBusyColor = dwBusyColor;
	m_dwVolbarBackColor = dwBackColor;

	InvalidateRect(&m_rcVolBarRect, TRUE);
}

void CAgoraVideoWnd::SetVolRange(int nRange)
{
	if(nRange > 100 || nRange < 0)
		nRange = 100;

	m_nVolRange = nRange;

	InvalidateRect(&m_rcVolBarRect, TRUE);
}

void CAgoraVideoWnd::SetCurVol(int nCurVol)
{
	if(m_nUID == 0)
		nCurVol = 0;

	if(nCurVol < 0 || nCurVol > m_nVolRange)
		nCurVol = 0;

	m_nCurVol = nCurVol;

	if(m_nCurVol > 0)
		m_dwUserFlag |= AGUSER_SPEAKING;
	else
		m_dwUserFlag &= (~AGUSER_SPEAKING);

	InvalidateRect(&m_rcVolBarRect, TRUE);
}

void CAgoraVideoWnd::SetUID(UINT nUID)
{
	CString str;

	if(nUID != 0)
		str.Format(_T("UID:%u"), nUID);
	else {
		m_dwUserFlag = AGUSER_NORMAL;
		str = m_strFirstTitle;
	}

	m_nUID = nUID;
	SetWindowText(str);

/*	CRect rcBtnListRect(0, 0, m_rcClientRect.Width(), 18);
	InvalidateRect(&rcBtnListRect, TRUE);
	m_wndVideoWnd.Invalidate(TRUE);
*/
	Invalidate(TRUE);
	UpdateWindow();
}

void CAgoraVideoWnd::SetMuteAudioFlag(BOOL bMuteAudio)
{
	if(m_nUID == 0)
		return;

	if(bMuteAudio)
		m_dwUserFlag |= AGUSER_MUTEAUDIO;
	else
		m_dwUserFlag &= (~AGUSER_MUTEAUDIO);

	CRect rcBtnListRect(m_rcClientRect.Width()-60, 0, m_rcClientRect.Width(), 18);
	InvalidateRect(&rcBtnListRect, TRUE);
	UpdateWindow();
}

void CAgoraVideoWnd::SetMuteVideoFlag(BOOL bMuteVideo)
{
	if(m_nUID == 0)
		return;

	if(bMuteVideo)
		m_dwUserFlag |= AGUSER_MUTEVIDEO;
	else
		m_dwUserFlag &= (~AGUSER_MUTEVIDEO);

	CRect rcBtnListRect(m_rcClientRect.Width()-60, 0, m_rcClientRect.Width(), 18);
	InvalidateRect(&rcBtnListRect, TRUE);
	UpdateWindow();
}

void CAgoraVideoWnd::SetBigScreenFlag(BOOL bBigScreen)
{
	if(m_nUID == 0)
		return;

	if(bBigScreen)
		m_dwUserFlag |= AGUSER_BIGSCREEN;
	else
		m_dwUserFlag &= (~AGUSER_BIGSCREEN);

	CRect rcBtnListRect(m_rcClientRect.Width()-60, 0, m_rcClientRect.Width(), 18);
	InvalidateRect(&rcBtnListRect, TRUE);
	UpdateWindow();
}

BOOL CAgoraVideoWnd::IsWndFree()
{
	return m_nUID == 0 ? TRUE:FALSE;
}


void CAgoraVideoWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nMousePos = JudgePointPos(point);

	switch (nMousePos)
	{
	case MOUSE_POS_NORMAL:
	case MOUSE_POS_TIP:	
		m_ctrToolTip.Activate(FALSE);
		break;
	case MOUSE_POS_BIGSCREEN:	
		m_ctrToolTip.Activate(TRUE);
		m_ctrToolTip.AddTool(this, _T("full screen"));
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
		break;
	case MOUSE_POS_MUTEVIDEO:	
		m_ctrToolTip.Activate(TRUE);
		m_ctrToolTip.AddTool(this, _T("mute the video stream"));
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
		break;
	case MOUSE_POS_MUTEAUDIO:
		m_ctrToolTip.Activate(TRUE);
		m_ctrToolTip.AddTool(this, _T("mute the audio stream"));
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
		break;
	default:
		m_ctrToolTip.EnableToolTips(FALSE);
		break;
	}

	CWnd::OnMouseMove(nFlags, point);
}


void CAgoraVideoWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetFocus();
	SetCapture();

	CWnd::OnLButtonDown(nFlags, point);
}

int CAgoraVideoWnd::JudgePointPos(CPoint &point)
{
	if(m_nUID == 0)
		return MOUSE_POS_NORMAL;

	if( point.y > 0 && point.y < 18){
		if(point.x > m_rcClientRect.Width()-20 && point.x < m_rcClientRect.Width())
			return MOUSE_POS_MUTEAUDIO;
		else if(point.x >=m_rcClientRect.Width()-40 && point.x < m_rcClientRect.Width()-20)
			return MOUSE_POS_MUTEVIDEO;
		else if(point.x >=m_rcClientRect.Width()-60 && point.x < m_rcClientRect.Width()-40)
			return MOUSE_POS_BIGSCREEN;
	}

	return MOUSE_POS_NORMAL;
}

void CAgoraVideoWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nResult = JudgePointPos(point);

	if (nResult > MOUSE_POS_TIP)
	{
		NMAGVIDEOWND nmhdr;

		nmhdr.hdr.hwndFrom = GetSafeHwnd();
		nmhdr.hdr.code = NM_CLICK;
		nmhdr.hdr.idFrom = GetDlgCtrlID();

		nmhdr.nUID = m_nUID;
		nmhdr.nMousePos = nResult;
		nmhdr.dwUserFlag = m_dwUserFlag;

		GetParent()->SendMessage(WM_NOTIFY, WPARAM(nmhdr.hdr.idFrom), LPARAM(&nmhdr));
	}

	ReleaseCapture();

	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CAgoraVideoWnd::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_ctrToolTip.RelayEvent(pMsg);     

	return CWnd::PreTranslateMessage(pMsg);
}
