// NetworkTestPage.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraSDKDemoPro.h"
#include "NetworkTestPage.h"


// CNetworkTestPage 对话框

IMPLEMENT_DYNAMIC(CNetworkTestPage, CPropertyPage)

CNetworkTestPage::CNetworkTestPage()
	: CPropertyPage(CNetworkTestPage::IDD)
	, m_bEnableNETTest(FALSE)
{

}

CNetworkTestPage::~CNetworkTestPage()
{
}

void CNetworkTestPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CKTEST_NETWORKTEST, m_bEnableNETTest);
}


BEGIN_MESSAGE_MAP(CNetworkTestPage, CPropertyPage)

END_MESSAGE_MAP()


// CNetworkTestPage 消息处理程序

BOOL CNetworkTestPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}