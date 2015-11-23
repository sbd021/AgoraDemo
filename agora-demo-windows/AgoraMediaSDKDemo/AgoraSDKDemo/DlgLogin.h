#pragma once
#include "DemoData.h"

// CDlgLogin 对话框

class CDlgLogin : public CDialog
{
	DECLARE_DYNAMIC(CDlgLogin)

public:
	CDlgLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLogin();

	CString GetVendorKey() {return m_strVendorKey;};
	CString GetChannelName() {return m_strChannelName;};
	UINT GetUID() {return m_nUID;};
	int	GetEngineMode() {return m_nEngineMode;};
// 对话框数据
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

private:

	CString			m_strVendorKey;
	CString			m_strChannelName;
	UINT			m_nUID;
	int				m_nEngineMode;
};
