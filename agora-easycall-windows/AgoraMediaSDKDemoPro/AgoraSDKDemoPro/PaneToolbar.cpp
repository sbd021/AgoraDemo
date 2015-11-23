// PaneToolbar.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraSDKDemoPro.h"
#include "PaneToolbar.h"


// CPaneToolbar

IMPLEMENT_DYNAMIC(CPaneToolbar, CMFCToolBar)

CPaneToolbar::CPaneToolbar()
{

}

CPaneToolbar::~CPaneToolbar()
{
}


BEGIN_MESSAGE_MAP(CPaneToolbar, CMFCToolBar)
END_MESSAGE_MAP()



// CPaneToolbar 消息处理程序
void CPaneToolbar::OnUpdateCmdUI(CFrameWnd* lpTarget, BOOL bDisableIfNoHndler)
{
	CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
}

