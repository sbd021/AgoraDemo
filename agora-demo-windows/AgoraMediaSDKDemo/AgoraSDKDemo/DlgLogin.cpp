// DlgLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraSDKDemo.h"
#include "DlgLogin.h"


// CDlgLogin 对话框

IMPLEMENT_DYNAMIC(CDlgLogin, CDialog)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
	, m_nUID(0)
	, m_strVendorKey(_T("6D7A26A1D3554A54A9F43BE6797FE3E2"))
	, m_strChannelName(_T(""))
	, m_nEngineMode(1)
{

}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDUID_LOGIN, m_nUID);
	DDX_Text(pDX, IDC_EDVDKEY_LOGIN, m_strVendorKey);
	DDX_Text(pDX, IDC_EDCHNAME_LOGIN, m_strChannelName);
	DDX_Radio(pDX, IDC_RDAUDIO_LOGIN, m_nEngineMode);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgLogin::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgLogin 消息处理程序

BOOL CDlgLogin::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgLogin::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	if(m_strVendorKey.IsEmpty()) {
		MessageBox(_T("VendorKey内容为空"), _T("错误"), MB_OK|MB_ICONERROR);
		return;
	}

	if(m_strChannelName.IsEmpty()) {
		MessageBox(_T("ChannelName内容为空"), _T("错误"), MB_OK|MB_ICONERROR);
		return;
	}

	OnOK();
}
