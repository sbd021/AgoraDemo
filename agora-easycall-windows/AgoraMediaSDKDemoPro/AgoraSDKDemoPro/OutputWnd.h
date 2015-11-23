
#pragma once

#include "PaneToolbar.h"
/////////////////////////////////////////////////////////////////////////////
// COutputList 窗口

class COutputWnd : public CDockablePane
{
// 构造
public:
	COutputWnd();

// 属性
protected:
	

protected:

// 实现
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:
	CFont			m_Font;
	CMFCListCtrl	m_ctrLogList;
	CImageList		m_imgLog;
	CPaneToolbar	m_wndToolBar;
};

