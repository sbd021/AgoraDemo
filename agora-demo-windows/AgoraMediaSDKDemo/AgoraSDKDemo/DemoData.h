#ifndef __AGORA_SDK_DEMO_DATA_H_
#define __AGORA_SDK_DEMO_DATA_H_

typedef struct _AG_LOGIN_INFO 
{
	char	szVendorKey[32];
	char	szChannelName[32];
	UINT	nUID;

} AG_LOGIN_INFO, *PAG_LOGIN_INFO, LPAG_LOGIN_INFO ;

#endif