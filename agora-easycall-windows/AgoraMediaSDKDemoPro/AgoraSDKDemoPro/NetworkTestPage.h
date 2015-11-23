#pragma once
#include "afxlistctrl.h"


// CNetworkTestPage 对话框

class CNetworkTestPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CNetworkTestPage)

public:
	CNetworkTestPage();
	virtual ~CNetworkTestPage();

// 对话框数据
	enum { IDD = IDD_NETWORKTESTPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bEnableNETTest;
};
