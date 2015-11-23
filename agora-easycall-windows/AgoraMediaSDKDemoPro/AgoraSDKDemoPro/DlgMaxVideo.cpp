// DlgMaxVideo.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraSDKDemoPro.h"
#include "DlgMaxVideo.h"


// CDlgMaxVideo 对话框

IMPLEMENT_DYNAMIC(CDlgMaxVideo, CDialog)

CDlgMaxVideo::CDlgMaxVideo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMaxVideo::IDD, pParent)
	, m_nUID(0)
{

}

CDlgMaxVideo::~CDlgMaxVideo()
{
}

void CDlgMaxVideo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMaxVideo, CDialog)
END_MESSAGE_MAP()


// CDlgMaxVideo 消息处理程序

BOOL CDlgMaxVideo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgMaxVideo::SetUID(UINT nUID)
{
	CString str;

	m_nUID = nUID;
	str.Format(_T("UID: %d"), nUID);

	SetWindowText(str);
}
void CDlgMaxVideo::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	#define WM_MAXVIDEOCLOSED	(WM_USER+200)

	/*
	CWnd *lpParentWnd = GetParent();

	HWND hParent = lpParentWnd->GetSafeHwnd();
	GetParent()->SendMessage(WM_MAXVIDEOCLOSED, 0, 0);
*/
	AfxGetMainWnd()->GetDlgItem(AFX_IDW_PANE_FIRST)->SendMessage(WM_MAXVIDEOCLOSED, 0, 0);
	CDialog::OnCancel();
}
