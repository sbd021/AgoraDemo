#pragma once
#include "PaneToolbar.h"


// CUserListView

class CUserListView : public CDockablePane
{
	DECLARE_DYNAMIC(CUserListView)

public:
	CUserListView();
	virtual ~CUserListView();

	void InsertUID(UINT nUID, int nElapsed);
	void DeleteUID(UINT nUID);
	void DeleteAll();

	CMFCListCtrl *GetUserListCtrl() {return &m_ctrUserList;};

protected:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnSwitchBitrate();
	afx_msg void OnMuteSound();
	afx_msg void OnMuteVideo();

	DECLARE_MESSAGE_MAP()

private:
	CString			m_strChannelName;
	CImageList		m_imgUserStat;

	CMFCListCtrl	m_ctrUserList;
	CImageList		m_FileViewImages;
	CPaneToolbar	m_wndToolBar;
};


