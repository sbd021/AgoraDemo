// AgoraVideoWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraSDKDemo.h"
#include "AgoraVideoWnd.h"


// CAgoraVideoWnd

IMPLEMENT_DYNAMIC(CAgoraVideoWnd, CWnd)

CAgoraVideoWnd::CAgoraVideoWnd()
	: m_nUID(0)
	, m_dwUserFlag(AGUSER_NORMAL)
{
	m_brhButton.CreateSolidBrush(RGB(255, 255, 255));
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
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()

	CString strTitle;

	GetWindowText(strTitle);

	if( (m_dwUserFlag&AGUSER_SPEAKING) )
		dc.FillSolidRect(0, 0, m_rcClientRect.Width(), 18, RGB(192, 96, 96));
	else
		dc.FillSolidRect(0, 0, m_rcClientRect.Width(), 18, RGB(96, 96, 96));

	CFont* lpDefFont = dc.SelectObject(&m_ftClient);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.TextOut(3, 3, strTitle);
	dc.SelectObject(lpDefFont);
	
	CBrush* lpOldBrush = dc.SelectObject(&m_brhButton);

	// draw the triangle button
	POINT pts[3] = {{m_rcClientRect.Width()-12, 4}, {m_rcClientRect.Width()-4, 4},{m_rcClientRect.Width()-8, 12}};
	dc.Polygon(pts, 3);
	
	dc.SelectObject(lpOldBrush);

	dc.FillSolidRect(0, 18, m_rcClientRect.Width(), m_rcClientRect.Height()-18, RGB(128, 128, 128));
}

int CAgoraVideoWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect		rcChildRect; 
	LOGFONT		lf;

	DWORD dwWndStyle = WS_VISIBLE | WS_VISIBLE;

	rcChildRect.SetRect(0, 18, lpCreateStruct->cx, lpCreateStruct->cy-18);

	m_wndVideoWnd.Create(NULL, _T("AgoraVideoWnd"), dwWndStyle, rcChildRect, this, IDC_STATIC);
	
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 12;
	lf.lfWeight = 400;

	::lstrcpy(lf.lfFaceName, _T("宋体"));
	m_ftClient.CreateFontIndirect(&lf);
	SetFont(&m_ftClient, TRUE);
	m_strFirstTitle = lpCreateStruct->lpszName;

	return 0;
}

void CAgoraVideoWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_rcClientRect.SetRect(0, 0, cx, cy);
	m_wndVideoWnd.MoveWindow(0, 18, cx, cy-18, TRUE);
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

	Invalidate(TRUE);
	UpdateWindow();
}

void CAgoraVideoWnd::SetSpeakingFlag(BOOL bSpeaking)
{
	if(m_nUID == 0)
		return;
	
	if(bSpeaking)
		m_dwUserFlag |= AGUSER_SPEAKING;
	else
		m_dwUserFlag &= (~AGUSER_SPEAKING);

	CRect rcDirty;

	rcDirty.SetRect(0, 0, m_rcClientRect.Width(), 18);

	InvalidateRect(&rcDirty, TRUE);
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

}

void CAgoraVideoWnd::SetMuteVideoFlag(BOOL bMuteVideo)
{
	if(m_nUID == 0)
		return;

	if(bMuteVideo)
		m_dwUserFlag |= AGUSER_MUTEVIDEO;
	else
		m_dwUserFlag &= (~AGUSER_MUTEVIDEO);

}

BOOL CAgoraVideoWnd::IsWndFree()
{
	return m_nUID == 0 ? TRUE:FALSE;
}


void CAgoraVideoWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(JudgePointPos(point) == MOUSE_POS_MENU) 
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
	else
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));

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
	if( point.y > 1 && point.y < 18){
		if(point.x > 1 && point.x < m_rcClientRect.Width()-20)
			return MOUSE_POS_TIP;
		else if(point.x >=m_rcClientRect.Width()-20 && point.x < m_rcClientRect.Width())
			return MOUSE_POS_MENU;
	}

	return MOUSE_POS_NORMAL;
}

void CAgoraVideoWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nResult = JudgePointPos(point);

	if (nResult == MOUSE_POS_MENU)
	{
		NMAGVIDEOWND nmhdr;

		nmhdr.hdr.hwndFrom = GetSafeHwnd();
		nmhdr.hdr.code = NM_CLICK;
		nmhdr.hdr.idFrom = GetDlgCtrlID();

		nmhdr.nUID = m_nUID;
		nmhdr.dwUserFlag = m_dwUserFlag;

		GetParent()->SendMessage(WM_NOTIFY, WPARAM(nmhdr.hdr.idFrom), LPARAM(&nmhdr));
	}

	ReleaseCapture();

	CWnd::OnLButtonUp(nFlags, point);
}
