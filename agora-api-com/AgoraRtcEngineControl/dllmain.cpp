// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "AgoraRtcEngineControl_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CAgoraRtcEngineControlModule _AtlModule;
HINSTANCE g_hInstance;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		g_hInstance = hInstance;
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(hInstance, dwReason, lpReserved))
		return FALSE;
#endif
	return _AtlModule.DllMain(dwReason, lpReserved);
}
