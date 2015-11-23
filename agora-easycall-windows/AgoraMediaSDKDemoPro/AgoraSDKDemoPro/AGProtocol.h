#pragma once

#define PRI_MSGID_TEST		0x00000000
#define PRI_MSGID_CHAT		0x00000001
#define PRI_MSGID_TRSFILE	0x00000002

typedef struct _PRI_PROTOCOL_HEADER
{
	DWORD	dwMsgID;
	DWORD	dwFlag;
	DWORD	dwSEQ;
	DWORD	dwPackLen;

} PRI_PROTOCOL_HEADER,  *PPRI_PROTOCOL_HEADER, *LPPRI_PROTOCOL_HEADER;


class CAGProtocol
{
public:
	CAGProtocol(void);
	~CAGProtocol(void);
};
