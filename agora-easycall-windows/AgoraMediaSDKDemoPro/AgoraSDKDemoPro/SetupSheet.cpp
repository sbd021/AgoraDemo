// SetupSheet.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraSDKDemoPro.h"
#include "SetupSheet.h"


// CSetupSheet

IMPLEMENT_DYNAMIC(CSetupSheet, CMFCPropertySheet)

CSetupSheet::CSetupSheet(CWnd* lpParentWnd)
	: CMFCPropertySheet(_T("参数设置"), lpParentWnd)
{
	SetLook(CMFCPropertySheet::PropSheetLook_OutlookBar);
	SetIconsList(IDB_SETUP_SHEET, 32);

	AddPage(&m_pageNetworkTest);
	AddPage(&m_pageEchoTest);
	AddPage(&m_pageDeviceTest);
	AddPage(&m_pageSetup);
}

CSetupSheet::~CSetupSheet()
{
}


BEGIN_MESSAGE_MAP(CSetupSheet, CMFCPropertySheet)
END_MESSAGE_MAP()



// CSetupSheet 消息处理程序



BOOL CSetupSheet::OnInitDialog()
{
	BOOL bResult = CMFCPropertySheet::OnInitDialog();

	// TODO:  在此添加您的专用代码
	

	return bResult;
}
