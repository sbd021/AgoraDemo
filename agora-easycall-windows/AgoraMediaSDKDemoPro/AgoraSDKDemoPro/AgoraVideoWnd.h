#pragma once

typedef struct tagNMAGVIDEOWND
{
	NMHDR   hdr;
	UINT	nUID;
	int		nMousePos;
	DWORD	dwUserFlag;
	LPARAM  lParam;

} NMAGVIDEOWND, *PNMAGVIDEOWND, *LPNMAGVIDEOWND;


#define	AGUSER_NORMAL		0x00000000	// 状态正常
#define AGUSER_SPEAKING		0x00000001	// 正在讲话
#define AGUSER_MUTEAUDIO	0x00000002	// 静音
#define AGUSER_MUTEVIDEO	0x00000004	// 视频关闭
#define AGUSER_BIGSCREEN	0x00000008	// 最大化窗口展示

// CAgoraVideoWnd

class CAgoraVideoWnd : public CWnd
{
public:
	enum {
		MOUSE_POS_NORMAL = 0,
		MOUSE_POS_TIP = 1,
		MOUSE_POS_BIGSCREEN = 2,
		MOUSE_POS_MUTEVIDEO = 3,
		MOUSE_POS_MUTEAUDIO = 4,
		
	};

	enum {
		VOLBAR_LEFT = 0,
		VOLBAR_RIGHT = 1
	};

	DECLARE_DYNAMIC(CAgoraVideoWnd)

public:
	CAgoraVideoWnd();
	virtual ~CAgoraVideoWnd();

	HWND GetVideoSafeHwnd() {return m_wndVideoWnd.GetSafeHwnd();};

	void SetVolbarPos(int nPos);
	int GetVolbarPos();
	
	// 音量条指示
	void SetVolbarColor(DWORD dwFreeColor = RGB(184, 184, 184), DWORD dwBusyColor = RGB(0, 255, 0), DWORD dwBackColor = RGB(0, 0, 0));	// 设定空闲颜色
	void SetVolRange(int nRange = 100);
	void SetCurVol(int nCurVol = 0);

	void SetUID(UINT nUID);
	UINT GetUID() {return m_nUID;};

	DWORD GetUserFlag() {return m_dwUserFlag;};
	void SetSpeakingFlag(BOOL bSpeaking = FALSE);
	BOOL IsSpeaking() {return (m_dwUserFlag&AGUSER_SPEAKING) != 0;};

	void SetMuteAudioFlag(BOOL bMuteAudio = FALSE);
	BOOL IsAudioMuted() {return (m_dwUserFlag&AGUSER_MUTEAUDIO) != 0;};

	void SetMuteVideoFlag(BOOL bMuteVideo = FALSE);
	BOOL IsVideoMuted() {return (m_dwUserFlag&AGUSER_MUTEVIDEO) != 0;};

	void SetBigScreenFlag(BOOL bBigScreen = FALSE);
	BOOL IsBigScreen() {return (m_dwUserFlag&AGUSER_BIGSCREEN) != 0;};

	BOOL IsWndFree();

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

private:
	void DrawUIDInfo(CDC *lpDC);
	void DrawVolbar(CDC *lpDC);
	void DrawButton(CDC *lpDC);

	int JudgePointPos(CPoint &point);

private:
	CWnd		m_wndVideoWnd;	// the wnd for show video
	UINT		m_nUID;			// UID
	
	CFont		m_ftClient;
	CRect		m_rcClientRect;
	CRect		m_rcVolBarRect;

	CString		m_strFirstTitle;
	DWORD		m_dwUserFlag;

	int			m_nVolbarPos;			// the vol bar pos

	int			m_nVolRange;			// the max vol
	int			m_nCurVol;				// the current vol
	DWORD		m_dwVolbarFreeColor;	
	DWORD		m_dwVolbarBusyColor;
	DWORD		m_dwVolbarBackColor;

	CImageList	m_imgBtnList;
	CToolTipCtrl	m_ctrToolTip;

};


