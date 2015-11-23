#pragma once


// CEchoTestPage 对话框

class CEchoTestPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CEchoTestPage)

public:
	CEchoTestPage();
	virtual ~CEchoTestPage();

// 对话框数据
	enum { IDD = IDD_ECHOTESTPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnBnClickedBtnctrEchotest();

	DECLARE_MESSAGE_MAP()

};
