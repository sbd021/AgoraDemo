// UserListView.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraSDKDemoPro.h"
#include "UserListView.h"
//#include "AgoraAudio.h"

// CUserListView

IMPLEMENT_DYNAMIC(CUserListView, CDockablePane)

CUserListView::CUserListView()
{

}

CUserListView::~CUserListView()
{
}


BEGIN_MESSAGE_MAP(CUserListView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()

/*	ON_COMMAND(ID_SWITCHRES_USERLIST, &CUserListView::OnSwitchBitrate)
	ON_COMMAND(ID_MUTESOUND_USERLIST, &CUserListView::OnMuteSound)
	ON_COMMAND(ID_MUTEVIDEO_USERLIST, &CUserListView::OnMuteVideo)
*/
END_MESSAGE_MAP()



// CUserListView 消息处理程序



int CUserListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rectDummy;
	CBitmap	bmpUserStat;

	rectDummy.SetRectEmpty();

	// 创建视图:
	const DWORD dwViewStyle = WS_TABSTOP | WS_CHILD | WS_BORDER | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;

	bmpUserStat.LoadBitmap(IDB_STAT_USERLIST);
	m_imgUserStat.Create(16, 16, ILC_COLOR32 | ILC_MASK, 2, 1);
	m_imgUserStat.Add(&bmpUserStat, RGB(192, 192, 192));

	m_ctrUserList.Create(dwViewStyle, rectDummy, this, ID_LIST_USERLIST);
	m_ctrUserList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES | LVS_EX_INFOTIP | LVS_EX_FULLROWSELECT);
	m_ctrUserList.SetImageList(&m_imgUserStat, LVSIL_SMALL);
	m_ctrUserList.InsertColumn(0, _T("UID"), 0, 150, 0);
	m_ctrUserList.InsertColumn(1, _T("Elapsed"), 0, 120, 1);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, ID_TOOLBAR_USERLIST);
	m_wndToolBar.LoadToolBar(IDR_USERLIST, 0, 0, TRUE, IDB_TBDIS_USERLIST);
	m_wndToolBar.SetOwner(this);
	m_wndToolBar.SetRouteCommandsViaFrame (FALSE);

	return 0;
}

void CUserListView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (GetSafeHwnd() == NULL)
		return;

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_ctrUserList.SetWindowPos(NULL, rectClient.left, rectClient.top+cyTlb, rectClient.Width(), rectClient.Height()-cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CUserListView::InsertUID(UINT nUID, int nElapsed)
{
	CString str;

	LVFINDINFO FindInfo;

	FindInfo.flags = LVFI_PARAM;
	FindInfo.lParam = (LPARAM)nUID;

	int nIndex = m_ctrUserList.FindItem(&FindInfo);
	if(nIndex != -1)		// find it
		m_ctrUserList.SetItem(nIndex, 0, LVIF_IMAGE, NULL, 0, 0, 0, 0);
	else{					// must insert
		nIndex = m_ctrUserList.GetItemCount();
		str.Format(_T("%u"), nUID);
		m_ctrUserList.InsertItem(nIndex, str, 0);
	}

	str.Format(_T("%d"), nElapsed);
	m_ctrUserList.SetItemText(nIndex, 1, str);
	m_ctrUserList.SetItemData(nIndex, (DWORD_PTR)nUID);

	str.Format(_T("当前在线: %d"), m_ctrUserList.GetItemCount());
	SetWindowText(str);
}

void CUserListView::DeleteUID(UINT nUID)
{
	CString str;

	LVFINDINFO FindInfo;

	FindInfo.flags = LVFI_PARAM;
	FindInfo.lParam = (LPARAM)nUID;

	int nIndex = m_ctrUserList.FindItem(&FindInfo);
	if(nIndex != -1)		// find it
		m_ctrUserList.DeleteItem(nIndex);

	str.Format(_T("当前在线: %d"), m_ctrUserList.GetItemCount());
	SetWindowText(str);
}

void CUserListView::DeleteAll()
{
	CString str;

	m_ctrUserList.DeleteAllItems();

	SetWindowText(_T("当前在线: 0"));
}

void CUserListView::OnSwitchBitrate()
{

}

void CUserListView::OnMuteSound()
{

}

void CUserListView::OnMuteVideo()
{

}