#pragma once


// CPaneToolbar

class CPaneToolbar : public CMFCToolBar
{
	DECLARE_DYNAMIC(CPaneToolbar)

public:
	CPaneToolbar();
	virtual ~CPaneToolbar();

protected:

	virtual void OnUpdateCmdUI(CFrameWnd* lpTarget, BOOL bDisableIfNoHndler);
	virtual BOOL AllowShowOnList() const { return FALSE; };

	DECLARE_MESSAGE_MAP()
};


