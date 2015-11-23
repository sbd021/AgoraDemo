#pragma once


// CSetupPage 对话框

class CSetupPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CSetupPage)

public:
	CSetupPage();
	virtual ~CSetupPage();

// 对话框数据
	enum { IDD = IDD_SETUPPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnApply();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:
	int m_nResolution;

};
