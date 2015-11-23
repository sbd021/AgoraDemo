#pragma once


// CDlgMaxVideo 对话框

class CDlgMaxVideo : public CDialog
{
	DECLARE_DYNAMIC(CDlgMaxVideo)

public:
	CDlgMaxVideo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMaxVideo();

	void SetUID(UINT nUID);
	UINT GetUID() {return m_nUID;};

// 对话框数据
	enum { IDD = IDD_DLGMAXVIDEO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

private:
	UINT	m_nUID;

};
