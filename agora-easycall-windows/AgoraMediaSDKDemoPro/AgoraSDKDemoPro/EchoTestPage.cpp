// EchoTestPage.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraSDKDemoPro.h"
#include "EchoTestPage.h"


// CEchoTestPage 对话框

IMPLEMENT_DYNAMIC(CEchoTestPage, CPropertyPage)

CEchoTestPage::CEchoTestPage()
	: CPropertyPage(CEchoTestPage::IDD)
{

}

CEchoTestPage::~CEchoTestPage()
{
}

void CEchoTestPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEchoTestPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTNCTR_ECHOTEST, &CEchoTestPage::OnBnClickedBtnctrEchotest)
END_MESSAGE_MAP()


// CEchoTestPage 消息处理程序

void CEchoTestPage::OnBnClickedBtnctrEchotest()
{
	// TODO: 在此添加控件通知处理程序代码
	CAgoraObject *lpAgoraObject = CAgoraObject::GetAgoraObject();
	IRtcEngine *lpAgoraRTCEngine = CAgoraObject::GetEngine();
	
	// runing->stop
	if(lpAgoraObject->GetEchoTestFlag()) {
		SetDlgItemText(IDC_BTNCTR_ECHOTEST, _T("开启测试"));
		lpAgoraRTCEngine->stopEchoTest();
		lpAgoraObject->SetEchoTestFlag(FALSE);
	}
	else{
		SetDlgItemText(IDC_BTNCTR_ECHOTEST, _T("停止测试"));
		lpAgoraRTCEngine->startEchoTest();
		lpAgoraObject->SetEchoTestFlag(TRUE);

		RtcEngineParameters rep(lpAgoraRTCEngine);
		rep.enableAudioVolumeIndication(1000, 10);
	}
}
