#pragma once
#include "NetworkTestPage.h"
#include "EchoTestPage.h"
#include "DeviceTestPage.h"
#include "SetupPage.h"

// CSetupSheet

class CSetupSheet : public CMFCPropertySheet
{
	DECLARE_DYNAMIC(CSetupSheet)

public:
	CSetupSheet(CWnd* lpParentWnd = NULL);
	virtual ~CSetupSheet();

protected:
	virtual BOOL OnInitDialog();


	DECLARE_MESSAGE_MAP()


private:
	CNetworkTestPage	m_pageNetworkTest;
	CEchoTestPage		m_pageEchoTest;
	CDeviceTestPage		m_pageDeviceTest;
	CSetupPage			m_pageSetup;
};


