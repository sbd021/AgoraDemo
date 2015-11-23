#pragma once

typedef struct tagNMAGVIDEOWND
{
	NMHDR   hdr;
	UINT	nUID;
	DWORD	dwUserFlag;
	LPARAM  lParam;

} NMAGVIDEOWND, *PNMAGVIDEOWND, *LPNMAGVIDEOWND;


#define	AGUSER_NORMAL		0x00000000	// 状态正常
#define AGUSER_SPEAKING		0x00000001	// 正在讲话
#define AGUSER_MUTEAUDIO	0x00000002	// 静音
#define AGUSER_MUTEVIDEO	0x00000004	// 视频关闭

// CAgoraVideoWnd

class CAgoraVideoWnd : public CWnd
{
	enum {
		MOUSE_POS_NORMAL = 0,
		MOUSE_POS_TIP = 1,
		MOUSE_POS_MENU = 2
	};

	DECLARE_DYNAMIC(CAgoraVideoWnd)

public:
	CAgoraVideoWnd();
	virtual ~CAgoraVideoWnd();

	HWND GetVideoSafeHwnd() {return m_wndVideoWnd.GetSafeHwnd();};

	void SetUID(UINT nUID);
	UINT GetUID() {return m_nUID;};

	void SetSpeakingFlag(BOOL bSpeaking = FALSE);
	BOOL IsSpeaking() {return (m_dwUserFlag&AGUSER_SPEAKING) != 0;};

	void SetMuteAudioFlag(BOOL bMuteAudio = FALSE);
	BOOL IsAudioMuted() {return (m_dwUserFlag&AGUSER_MUTEAUDIO) != 0;};

	void SetMuteVideoFlag(BOOL bMuteVideo = FALSE);
	BOOL IsVideoMuted() {return (m_dwUserFlag&AGUSER_MUTEVIDEO) != 0;};

	BOOL IsWndFree();

protected:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

private:
	int JudgePointPos(CPoint &point);

private:
	CWnd		m_wndVideoWnd;	// the wnd for show video
	UINT		m_nUID;			// UID
	CFont		m_ftClient;
	CRect		m_rcClientRect;

	CBrush		m_brhButton;

	CString		m_strFirstTitle;
	CToolTipCtrl	m_ctrToolTip;

	DWORD		m_dwUserFlag;
};


