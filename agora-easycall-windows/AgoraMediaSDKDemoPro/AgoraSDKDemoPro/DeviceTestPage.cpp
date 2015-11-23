// DeviceTestPage.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraSDKDemoPro.h"
#include "DeviceTestPage.h"
#include "AGResourceVisitor.h"

// CDeviceTestPage 对话框

IMPLEMENT_DYNAMIC(CDeviceTestPage, CPropertyPage)

CDeviceTestPage::CDeviceTestPage()
	: CPropertyPage(CDeviceTestPage::IDD)
{

}

CDeviceTestPage::~CDeviceTestPage()
{
}

void CDeviceTestPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBRCDSEL_DEVICETEST, m_ctrRocordDeviceSel);
	DDX_Control(pDX, IDC_SLDRCDVSET_DEVICETEST, m_ctrRecordVolSet);
	DDX_Control(pDX, IDC_CMBPLOSEL_DEVICETEST, m_ctrPlayoutDeviceSel);
	DDX_Control(pDX, IDC_SLDPLOVSET_DEVICETEST, m_ctrVolVolSet);
}


BEGIN_MESSAGE_MAP(CDeviceTestPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTNRCDCTRL_DEVICETEST, &CDeviceTestPage::OnBnClickedBtnrcdctrlDevicetest)
	ON_BN_CLICKED(IDC_BTNPLOCTRL_DEVICETEST, &CDeviceTestPage::OnBnClickedBtnploctrlDevicetest)
END_MESSAGE_MAP()


// CDeviceTestPage 消息处理程序

void CDeviceTestPage::OnBnClickedBtnrcdctrlDevicetest()
{
	// TODO: 在此添加控件通知处理程序代码

	IAudioDeviceManager *lpDeviceManager = CAgoraObject::GetEngine()->getAudioDeviceManager();

	CString str;

	if(lpDeviceManager != NULL)
		lpDeviceManager->startRecordingDeviceTest(100);
}

void CDeviceTestPage::OnBnClickedBtnploctrlDevicetest()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szWavPath[MAX_PATH];

	::GetModuleFileName(NULL, szWavPath, MAX_PATH);
	LPTSTR lpLastSlash = (LPTSTR)_tcsrchr(szWavPath, _T('\\'))+1;

	_tcscpy_s(lpLastSlash, 16, _T("test.wav"));

	CAGResourceVisitor::SaveResourceToFile(_T("WAVE"), IDR_TEST_WAVE, szWavPath);

	IAudioDeviceManager *lpDeviceManager = CAgoraObject::GetEngine()->getAudioDeviceManager();

#ifdef UNICODE
	char szWavPathA[MAX_PATH];

	::WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, szWavPath, -1, szWavPathA, MAX_PATH, NULL, NULL);

	int nRet = lpDeviceManager->startPlaybackDeviceTest(szWavPathA);
#else
	int nRet = lpDeviceManager->startPlaybackDeviceTest(szWavPath);
#endif
}

BOOL CDeviceTestPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化

#ifdef UNICODE
	CString strDeviceName;
	CString strDeviceID;
#endif

	char szDeviceName[MAX_DEVICE_ID_LENGTH];
	char szDeviceID[MAX_DEVICE_ID_LENGTH];

	IAudioDeviceManager *lpDeviceManager = CAgoraObject::GetEngine()->getAudioDeviceManager();

	IAudioDeviceCollection *lpPlayoutCollection = lpDeviceManager->enumeratePlaybackDevices();
	IAudioDeviceCollection *lpRecordingCollection = lpDeviceManager->enumerateRecordingDevices();

	if(lpPlayoutCollection == NULL || lpRecordingCollection == NULL){
		SetDlgItemText(IDC_STTEXT_DEVICETEST, _T("登录就绪之前，设备枚举不可用"));
		return TRUE;
	}

	for(int nIndex = 0; nIndex < lpPlayoutCollection->getCount(); nIndex++){
		lpPlayoutCollection->getDevice(nIndex, szDeviceName, szDeviceID);

#ifdef UNICODE
		::MultiByteToWideChar(CP_UTF8, 0, szDeviceName, -1, strDeviceName.GetBuffer(MAX_DEVICE_ID_LENGTH), MAX_DEVICE_ID_LENGTH);
		::MultiByteToWideChar(CP_UTF8, 0, szDeviceID, -1, strDeviceID.GetBuffer(MAX_DEVICE_ID_LENGTH), MAX_DEVICE_ID_LENGTH);

		strDeviceName.ReleaseBuffer();
		strDeviceID.ReleaseBuffer();
#else
		strDeviceName = szDeviceName;
		strDeviceID = szDeviceID;
#endif

		m_ctrPlayoutDeviceSel.InsertString(nIndex, strDeviceName);
	}

	for(int nIndex = 0; nIndex < lpRecordingCollection->getCount(); nIndex++){
		lpRecordingCollection->getDevice(nIndex, szDeviceName, szDeviceID);

#ifdef UNICODE
		::MultiByteToWideChar(CP_UTF8, 0, szDeviceName, -1, strDeviceName.GetBuffer(MAX_DEVICE_ID_LENGTH), MAX_DEVICE_ID_LENGTH);
		::MultiByteToWideChar(CP_UTF8, 0, szDeviceID, -1, strDeviceID.GetBuffer(MAX_DEVICE_ID_LENGTH), MAX_DEVICE_ID_LENGTH);

		strDeviceName.ReleaseBuffer();
		strDeviceID.ReleaseBuffer();
#else
		strDeviceName = szDeviceName;
		strDeviceID = szDeviceID;
#endif

		m_ctrRocordDeviceSel.InsertString(nIndex, strDeviceName);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
