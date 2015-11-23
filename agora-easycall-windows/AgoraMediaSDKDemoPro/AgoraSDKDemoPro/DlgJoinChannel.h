#pragma once


// CDlgJoinChannel 对话框

class CDlgJoinChannel : public CDialog
{
	DECLARE_DYNAMIC(CDlgJoinChannel)

public:
	CDlgJoinChannel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgJoinChannel();

// 对话框数据
	enum { IDD = IDD_DLGJOIN };

	enum { 
		WORKMODE_MEDIA = 0,
		WORKMODE_AUDIO
	};

	enum { 
		CODER_AGORA = 0,
		CODER_VP8,
		CODER_H264
	};

	enum {
		MAXRES_DEFAULT = 0,
		MAXRES_720P,
		MAXRES_1080P
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

private:
	CString m_strVendorKey;
	CString m_strChannelName;
	UINT	m_nUID;

	int		m_nWorkMode;
	int		m_nDecodeMode;
	BOOL	m_bRecvMode;
	int		m_nMaxResolution;

public:
	CString GetVendorKey() {return m_strVendorKey;};
	UINT GetUID() {return m_nUID;};
	CString GetChannelName() {return m_strChannelName;};

	int GetWorkMode() {return m_nWorkMode;};
	int GetDecodeMode() {return m_nDecodeMode;};
	int GetMaxResolution() {return m_nMaxResolution;};
	BOOL IsPureRecvMode() {return m_bRecvMode;};

};
