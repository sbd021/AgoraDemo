

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Oct 18 11:39:57 2016
 */
/* Compiler settings for AgoraRtcEngineControl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_AgoraRtcEngineControlLib,0x25184BF7,0x4EC2,0x4B07,0xBD,0xAA,0x6F,0xEF,0x3D,0xB7,0x8B,0x00);


MIDL_DEFINE_GUID(IID, IID_IAgoraRtcEngineControl,0x7F7C6262,0xB8C8,0x4F5D,0xA5,0x69,0x02,0xA0,0xF5,0x99,0x84,0x42);


MIDL_DEFINE_GUID(IID, DIID__IAgoraRtcEngineControlEvents,0xC9A10FD6,0x1660,0x4DEF,0x85,0x6C,0x55,0xDF,0x11,0x77,0x2D,0xAE);


MIDL_DEFINE_GUID(CLSID, CLSID_AgoraRtcEngineControl,0xDA06DE88,0x2602,0x478F,0xA7,0x31,0x5B,0xEA,0x37,0x50,0x8D,0x69);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



