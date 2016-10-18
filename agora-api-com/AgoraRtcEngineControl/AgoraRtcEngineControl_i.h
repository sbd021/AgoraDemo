

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __AgoraRtcEngineControl_i_h__
#define __AgoraRtcEngineControl_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAgoraRtcEngineControl_FWD_DEFINED__
#define __IAgoraRtcEngineControl_FWD_DEFINED__
typedef interface IAgoraRtcEngineControl IAgoraRtcEngineControl;
#endif 	/* __IAgoraRtcEngineControl_FWD_DEFINED__ */


#ifndef ___IAgoraRtcEngineControlEvents_FWD_DEFINED__
#define ___IAgoraRtcEngineControlEvents_FWD_DEFINED__
typedef interface _IAgoraRtcEngineControlEvents _IAgoraRtcEngineControlEvents;
#endif 	/* ___IAgoraRtcEngineControlEvents_FWD_DEFINED__ */


#ifndef __AgoraRtcEngineControl_FWD_DEFINED__
#define __AgoraRtcEngineControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class AgoraRtcEngineControl AgoraRtcEngineControl;
#else
typedef struct AgoraRtcEngineControl AgoraRtcEngineControl;
#endif /* __cplusplus */

#endif 	/* __AgoraRtcEngineControl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __AgoraRtcEngineControlLib_LIBRARY_DEFINED__
#define __AgoraRtcEngineControlLib_LIBRARY_DEFINED__

/* library AgoraRtcEngineControlLib */
/* [version][uuid] */ 

typedef /* [uuid] */  DECLSPEC_UUID("A6F8DE5D-E3E1-425D-956C-80B998BD8FA0") 
enum ChannelProfile
    {	ChannelProfile_Communication	= 0,
	ChannelProfile_LiveBroadcasting	= 1
    } 	ChannelProfile;

typedef /* [uuid] */  DECLSPEC_UUID("52DE87DF-132C-4875-BF87-60DDF2FC38E3") 
enum ClientRole
    {	ClientRole_BroadCaster	= 1,
	ClientRole_Audience	= 2
    } 	ClientRole;

typedef /* [uuid] */  DECLSPEC_UUID("99593833-D4CC-4A7D-BCF4-2D54F85F06A3") 
enum QualityReportFormat
    {	QualityReport_Json	= 0,
	QualityReport_Html	= 1
    } 	QualityReportFormat;

typedef /* [uuid] */  DECLSPEC_UUID("E11120CA-13E0-4CC5-B9AE-A8664EB2384C") 
enum Quality
    {	Quality_Unknown	= 0,
	Quality_Excellent	= 1,
	Quality_Good	= 2,
	Quality_Poor	= 3,
	Quality_Bad	= 4,
	Quality_VBad	= 5,
	Quality_Down	= 6
    } 	Quality;

typedef /* [uuid] */  DECLSPEC_UUID("8BE4A242-A9E6-4878-93A8-319903EB4C36") 
enum VideoProfile
    {	VIDEO_PROFILE_120P	= 0,
	VIDEO_PROFILE_120P_3	= 2,
	VIDEO_PROFILE_180P	= 10,
	VIDEO_PROFILE_180P_3	= 12,
	VIDEO_PROFILE_180P_4	= 13,
	VIDEO_PROFILE_240P	= 20,
	VIDEO_PROFILE_240P_3	= 22,
	VIDEO_PROFILE_240P_4	= 23,
	VIDEO_PROFILE_360P	= 30,
	VIDEO_PROFILE_360P_3	= 32,
	VIDEO_PROFILE_360P_4	= 33,
	VIDEO_PROFILE_360P_6	= 35,
	VIDEO_PROFILE_360P_7	= 36,
	VIDEO_PROFILE_360P_8	= 37,
	VIDEO_PROFILE_360P_9	= 38,
	VIDEO_PROFILE_480P	= 40,
	VIDEO_PROFILE_480P_3	= 42,
	VIDEO_PROFILE_480P_4	= 43,
	VIDEO_PROFILE_480P_6	= 45,
	VIDEO_PROFILE_480P_8	= 47,
	VIDEO_PROFILE_480P_9	= 48,
	VIDEO_PROFILE_720P	= 50,
	VIDEO_PROFILE_720P_3	= 52,
	VIDEO_PROFILE_720P_5	= 54,
	VIDEO_PROFILE_720P_6	= 55,
	VIDEO_PROFILE_1080P	= 60,
	VIDEO_PROFILE_1080P_3	= 62,
	VIDEO_PROFILE_1080P_5	= 64,
	VIDEO_PROFILE_1440P	= 66,
	VIDEO_PROFILE_1440P_2	= 67,
	VIDEO_PROFILE_4K	= 70,
	VIDEO_PROFILE_4K_3	= 72,
	VIDEO_PROFILE_DEFAULT	= VIDEO_PROFILE_360P
    } 	VideoProfile;

typedef /* [uuid] */  DECLSPEC_UUID("D178C7A6-E955-49B4-BB91-9F8924D9402E") 
enum RenderMode
    {	RenderMode_Hidden	= 1,
	RenderMode_Fit	= 2,
	RenderMode_Adaptive	= 3
    } 	RenderMode;

typedef /* [uuid] */  DECLSPEC_UUID("8FA790A8-C84B-4BE8-8B62-2F80FB743A23") 
enum UserOfflineReason
    {	UserOffline_Quit	= 0,
	UserOffline_Dropped	= 1
    } 	UserOfflineReason;

typedef /* [uuid] */  DECLSPEC_UUID("6A6C603E-3766-48D7-B054-D3682E7198B3") 
enum MediaDeviceState
    {	MEDIA_DEVICE_STATE_ACTIVE	= 1,
	MEDIA_DEVICE_STATE_DISABLED	= 2,
	MEDIA_DEVICE_STATE_NOT_PRESENT	= 4,
	MEDIA_DEVICE_STATE_UNPLUGGED	= 8
    } 	MediaDeviceState;

typedef /* [uuid] */  DECLSPEC_UUID("CACD3155-54A3-4BEF-A5D2-1A9F5DD815ED") 
enum MediaDevice
    {	UNKNOWN_AUDIO_DEVICE	= -1,
	AUDIO_PLAYOUT_DEVICE	= 0,
	AUDIO_RECORDING_DEVICE	= 1,
	VIDEO_RENDER_DEVICE	= 2,
	VIDEO_CAPTURE_DEVICE	= 3
    } 	MediaDevice;


EXTERN_C const IID LIBID_AgoraRtcEngineControlLib;

#ifndef __IAgoraRtcEngineControl_INTERFACE_DEFINED__
#define __IAgoraRtcEngineControl_INTERFACE_DEFINED__

/* interface IAgoraRtcEngineControl */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAgoraRtcEngineControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7F7C6262-B8C8-4F5D-A569-02A0F5998442")
    IAgoraRtcEngineControl : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE initialize( 
            /* [in] */ BSTR appId,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE joinChannel( 
            /* [in] */ BSTR channelKey,
            /* [in] */ BSTR channelName,
            /* [in] */ BSTR info,
            /* [in] */ ULONG uid,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE leaveChannel( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setParameters( 
            /* [in] */ BSTR parameters,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE muteLocalAudioStream( 
            /* [in] */ VARIANT_BOOL muted,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE muteAllRemoteAudioStreams( 
            /* [in] */ VARIANT_BOOL muted,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE muteRemoteAudioStream( 
            /* [in] */ ULONG uid,
            /* [in] */ VARIANT_BOOL muted,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setClientRole( 
            /* [in] */ enum ClientRole role,
            /* [in] */ BSTR permissionKey,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE renewChannelKey( 
            /* [in] */ BSTR channelKey,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE startEchoTest( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE stopEchoTest( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE enableLastmileTest( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE disableLastmileTest( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE getCallId( 
            /* [retval][out] */ BSTR *callId) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE rate( 
            /* [in] */ BSTR callId,
            /* [in] */ LONG rating,
            /* [in] */ BSTR description,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE complain( 
            /* [in] */ BSTR callId,
            /* [in] */ BSTR description,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE enableVideo( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE disableVideo( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE startPreview( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE stopPreview( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setVideoProfile( 
            /* [in] */ enum VideoProfile profile,
            /* [in] */ VARIANT_BOOL swapWidthAndHeight,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setupLocalVideo( 
            /* [in] */ LONG_PTR **view,
            /* [in] */ enum RenderMode renderMode,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setupRemoteVideo( 
            /* [in] */ ULONG uid,
            /* [in] */ LONG_PTR **view,
            /* [in] */ enum RenderMode renderMode,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE muteLocalVideoStream( 
            /* [in] */ VARIANT_BOOL muted,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE muteAllRemoteVideoStreams( 
            /* [in] */ VARIANT_BOOL muted,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE muteRemoteVideoStream( 
            /* [in] */ ULONG uid,
            /* [in] */ VARIANT_BOOL muted,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE release( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE startAudioRecording( 
            /* [in] */ BSTR filePath,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE stopAudioRecording( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setLogFile( 
            /* [in] */ BSTR filePath,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setLogFilter( 
            /* [in] */ ULONG filter,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setLocalRenderMode( 
            /* [in] */ RenderMode renderMode,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setRemoteRenderMode( 
            /* [in] */ ULONG uid,
            /* [in] */ RenderMode renderMode,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setPlaybackDeviceVolume( 
            /* [in] */ LONG volume,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE startRecordingService( 
            /* [in] */ BSTR recordingKey,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE stopRecordingService( 
            /* [in] */ BSTR recordingKey,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE refreshRecordingServiceStatus( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE startScreenCapture( 
            /* [in] */ LONG_PTR **window,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setScreenCaptureWindow( 
            /* [in] */ LONG_PTR **window,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE stopScreenCapture( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE startAudioMixing( 
            /* [in] */ BSTR filePath,
            /* [in] */ VARIANT_BOOL loopback,
            /* [in] */ VARIANT_BOOL replace,
            /* [in] */ LONG cycle,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE stopAudioMixing( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setEncryptionSecret( 
            /* [in] */ BSTR secret,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setEncryptionMode( 
            /* [in] */ BSTR encryptionMode,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setChannelProfile( 
            /* [in] */ enum ChannelProfile profile,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE enumeratePlaybackDevices( 
            /* [retval][out] */ BSTR *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE enumerateRecordingDevices( 
            /* [retval][out] */ BSTR *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE enumerateVideoCaptureDevices( 
            /* [retval][out] */ BSTR *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setPlaybackDevice( 
            /* [in] */ BSTR deviceId,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setRecordingDevice( 
            /* [in] */ BSTR deviceId,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setVideoCaptureDevice( 
            /* [in] */ BSTR deviceId,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_fireEventInInitializationThread( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_fireEventInInitializationThread( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgoraRtcEngineControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAgoraRtcEngineControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAgoraRtcEngineControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAgoraRtcEngineControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *initialize )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR appId,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *joinChannel )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR channelKey,
            /* [in] */ BSTR channelName,
            /* [in] */ BSTR info,
            /* [in] */ ULONG uid,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *leaveChannel )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setParameters )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR parameters,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *muteLocalAudioStream )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ VARIANT_BOOL muted,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *muteAllRemoteAudioStreams )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ VARIANT_BOOL muted,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *muteRemoteAudioStream )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ ULONG uid,
            /* [in] */ VARIANT_BOOL muted,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setClientRole )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ enum ClientRole role,
            /* [in] */ BSTR permissionKey,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *renewChannelKey )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR channelKey,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *startEchoTest )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *stopEchoTest )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *enableLastmileTest )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *disableLastmileTest )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *getCallId )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ BSTR *callId);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *rate )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR callId,
            /* [in] */ LONG rating,
            /* [in] */ BSTR description,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *complain )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR callId,
            /* [in] */ BSTR description,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *enableVideo )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *disableVideo )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *startPreview )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *stopPreview )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setVideoProfile )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ enum VideoProfile profile,
            /* [in] */ VARIANT_BOOL swapWidthAndHeight,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setupLocalVideo )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ LONG_PTR **view,
            /* [in] */ enum RenderMode renderMode,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setupRemoteVideo )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ ULONG uid,
            /* [in] */ LONG_PTR **view,
            /* [in] */ enum RenderMode renderMode,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *muteLocalVideoStream )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ VARIANT_BOOL muted,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *muteAllRemoteVideoStreams )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ VARIANT_BOOL muted,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *muteRemoteVideoStream )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ ULONG uid,
            /* [in] */ VARIANT_BOOL muted,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *release )( 
            IAgoraRtcEngineControl * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *startAudioRecording )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR filePath,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *stopAudioRecording )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setLogFile )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR filePath,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setLogFilter )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ ULONG filter,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setLocalRenderMode )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ RenderMode renderMode,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setRemoteRenderMode )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ ULONG uid,
            /* [in] */ RenderMode renderMode,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setPlaybackDeviceVolume )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ LONG volume,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *startRecordingService )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR recordingKey,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *stopRecordingService )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR recordingKey,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *refreshRecordingServiceStatus )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *startScreenCapture )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ LONG_PTR **window,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setScreenCaptureWindow )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ LONG_PTR **window,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *stopScreenCapture )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *startAudioMixing )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR filePath,
            /* [in] */ VARIANT_BOOL loopback,
            /* [in] */ VARIANT_BOOL replace,
            /* [in] */ LONG cycle,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *stopAudioMixing )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setEncryptionSecret )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR secret,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setEncryptionMode )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR encryptionMode,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setChannelProfile )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ enum ChannelProfile profile,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *enumeratePlaybackDevices )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ BSTR *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *enumerateRecordingDevices )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ BSTR *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *enumerateVideoCaptureDevices )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ BSTR *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setPlaybackDevice )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR deviceId,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setRecordingDevice )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR deviceId,
            /* [retval][out] */ LONG *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setVideoCaptureDevice )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ BSTR deviceId,
            /* [retval][out] */ LONG *result);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fireEventInInitializationThread )( 
            IAgoraRtcEngineControl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fireEventInInitializationThread )( 
            IAgoraRtcEngineControl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IAgoraRtcEngineControlVtbl;

    interface IAgoraRtcEngineControl
    {
        CONST_VTBL struct IAgoraRtcEngineControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgoraRtcEngineControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAgoraRtcEngineControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAgoraRtcEngineControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAgoraRtcEngineControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAgoraRtcEngineControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAgoraRtcEngineControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAgoraRtcEngineControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAgoraRtcEngineControl_initialize(This,appId,result)	\
    ( (This)->lpVtbl -> initialize(This,appId,result) ) 

#define IAgoraRtcEngineControl_joinChannel(This,channelKey,channelName,info,uid,result)	\
    ( (This)->lpVtbl -> joinChannel(This,channelKey,channelName,info,uid,result) ) 

#define IAgoraRtcEngineControl_leaveChannel(This,result)	\
    ( (This)->lpVtbl -> leaveChannel(This,result) ) 

#define IAgoraRtcEngineControl_setParameters(This,parameters,result)	\
    ( (This)->lpVtbl -> setParameters(This,parameters,result) ) 

#define IAgoraRtcEngineControl_muteLocalAudioStream(This,muted,result)	\
    ( (This)->lpVtbl -> muteLocalAudioStream(This,muted,result) ) 

#define IAgoraRtcEngineControl_muteAllRemoteAudioStreams(This,muted,result)	\
    ( (This)->lpVtbl -> muteAllRemoteAudioStreams(This,muted,result) ) 

#define IAgoraRtcEngineControl_muteRemoteAudioStream(This,uid,muted,result)	\
    ( (This)->lpVtbl -> muteRemoteAudioStream(This,uid,muted,result) ) 

#define IAgoraRtcEngineControl_setClientRole(This,role,permissionKey,result)	\
    ( (This)->lpVtbl -> setClientRole(This,role,permissionKey,result) ) 

#define IAgoraRtcEngineControl_renewChannelKey(This,channelKey,result)	\
    ( (This)->lpVtbl -> renewChannelKey(This,channelKey,result) ) 

#define IAgoraRtcEngineControl_startEchoTest(This,result)	\
    ( (This)->lpVtbl -> startEchoTest(This,result) ) 

#define IAgoraRtcEngineControl_stopEchoTest(This,result)	\
    ( (This)->lpVtbl -> stopEchoTest(This,result) ) 

#define IAgoraRtcEngineControl_enableLastmileTest(This,result)	\
    ( (This)->lpVtbl -> enableLastmileTest(This,result) ) 

#define IAgoraRtcEngineControl_disableLastmileTest(This,result)	\
    ( (This)->lpVtbl -> disableLastmileTest(This,result) ) 

#define IAgoraRtcEngineControl_getCallId(This,callId)	\
    ( (This)->lpVtbl -> getCallId(This,callId) ) 

#define IAgoraRtcEngineControl_rate(This,callId,rating,description,result)	\
    ( (This)->lpVtbl -> rate(This,callId,rating,description,result) ) 

#define IAgoraRtcEngineControl_complain(This,callId,description,result)	\
    ( (This)->lpVtbl -> complain(This,callId,description,result) ) 

#define IAgoraRtcEngineControl_enableVideo(This,result)	\
    ( (This)->lpVtbl -> enableVideo(This,result) ) 

#define IAgoraRtcEngineControl_disableVideo(This,result)	\
    ( (This)->lpVtbl -> disableVideo(This,result) ) 

#define IAgoraRtcEngineControl_startPreview(This,result)	\
    ( (This)->lpVtbl -> startPreview(This,result) ) 

#define IAgoraRtcEngineControl_stopPreview(This,result)	\
    ( (This)->lpVtbl -> stopPreview(This,result) ) 

#define IAgoraRtcEngineControl_setVideoProfile(This,profile,swapWidthAndHeight,result)	\
    ( (This)->lpVtbl -> setVideoProfile(This,profile,swapWidthAndHeight,result) ) 

#define IAgoraRtcEngineControl_setupLocalVideo(This,view,renderMode,result)	\
    ( (This)->lpVtbl -> setupLocalVideo(This,view,renderMode,result) ) 

#define IAgoraRtcEngineControl_setupRemoteVideo(This,uid,view,renderMode,result)	\
    ( (This)->lpVtbl -> setupRemoteVideo(This,uid,view,renderMode,result) ) 

#define IAgoraRtcEngineControl_muteLocalVideoStream(This,muted,result)	\
    ( (This)->lpVtbl -> muteLocalVideoStream(This,muted,result) ) 

#define IAgoraRtcEngineControl_muteAllRemoteVideoStreams(This,muted,result)	\
    ( (This)->lpVtbl -> muteAllRemoteVideoStreams(This,muted,result) ) 

#define IAgoraRtcEngineControl_muteRemoteVideoStream(This,uid,muted,result)	\
    ( (This)->lpVtbl -> muteRemoteVideoStream(This,uid,muted,result) ) 

#define IAgoraRtcEngineControl_release(This)	\
    ( (This)->lpVtbl -> release(This) ) 

#define IAgoraRtcEngineControl_startAudioRecording(This,filePath,result)	\
    ( (This)->lpVtbl -> startAudioRecording(This,filePath,result) ) 

#define IAgoraRtcEngineControl_stopAudioRecording(This,result)	\
    ( (This)->lpVtbl -> stopAudioRecording(This,result) ) 

#define IAgoraRtcEngineControl_setLogFile(This,filePath,result)	\
    ( (This)->lpVtbl -> setLogFile(This,filePath,result) ) 

#define IAgoraRtcEngineControl_setLogFilter(This,filter,result)	\
    ( (This)->lpVtbl -> setLogFilter(This,filter,result) ) 

#define IAgoraRtcEngineControl_setLocalRenderMode(This,renderMode,result)	\
    ( (This)->lpVtbl -> setLocalRenderMode(This,renderMode,result) ) 

#define IAgoraRtcEngineControl_setRemoteRenderMode(This,uid,renderMode,result)	\
    ( (This)->lpVtbl -> setRemoteRenderMode(This,uid,renderMode,result) ) 

#define IAgoraRtcEngineControl_setPlaybackDeviceVolume(This,volume,result)	\
    ( (This)->lpVtbl -> setPlaybackDeviceVolume(This,volume,result) ) 

#define IAgoraRtcEngineControl_startRecordingService(This,recordingKey,result)	\
    ( (This)->lpVtbl -> startRecordingService(This,recordingKey,result) ) 

#define IAgoraRtcEngineControl_stopRecordingService(This,recordingKey,result)	\
    ( (This)->lpVtbl -> stopRecordingService(This,recordingKey,result) ) 

#define IAgoraRtcEngineControl_refreshRecordingServiceStatus(This,result)	\
    ( (This)->lpVtbl -> refreshRecordingServiceStatus(This,result) ) 

#define IAgoraRtcEngineControl_startScreenCapture(This,window,result)	\
    ( (This)->lpVtbl -> startScreenCapture(This,window,result) ) 

#define IAgoraRtcEngineControl_setScreenCaptureWindow(This,window,result)	\
    ( (This)->lpVtbl -> setScreenCaptureWindow(This,window,result) ) 

#define IAgoraRtcEngineControl_stopScreenCapture(This,result)	\
    ( (This)->lpVtbl -> stopScreenCapture(This,result) ) 

#define IAgoraRtcEngineControl_startAudioMixing(This,filePath,loopback,replace,cycle,result)	\
    ( (This)->lpVtbl -> startAudioMixing(This,filePath,loopback,replace,cycle,result) ) 

#define IAgoraRtcEngineControl_stopAudioMixing(This,result)	\
    ( (This)->lpVtbl -> stopAudioMixing(This,result) ) 

#define IAgoraRtcEngineControl_setEncryptionSecret(This,secret,result)	\
    ( (This)->lpVtbl -> setEncryptionSecret(This,secret,result) ) 

#define IAgoraRtcEngineControl_setEncryptionMode(This,encryptionMode,result)	\
    ( (This)->lpVtbl -> setEncryptionMode(This,encryptionMode,result) ) 

#define IAgoraRtcEngineControl_setChannelProfile(This,profile,result)	\
    ( (This)->lpVtbl -> setChannelProfile(This,profile,result) ) 

#define IAgoraRtcEngineControl_enumeratePlaybackDevices(This,result)	\
    ( (This)->lpVtbl -> enumeratePlaybackDevices(This,result) ) 

#define IAgoraRtcEngineControl_enumerateRecordingDevices(This,result)	\
    ( (This)->lpVtbl -> enumerateRecordingDevices(This,result) ) 

#define IAgoraRtcEngineControl_enumerateVideoCaptureDevices(This,result)	\
    ( (This)->lpVtbl -> enumerateVideoCaptureDevices(This,result) ) 

#define IAgoraRtcEngineControl_setPlaybackDevice(This,deviceId,result)	\
    ( (This)->lpVtbl -> setPlaybackDevice(This,deviceId,result) ) 

#define IAgoraRtcEngineControl_setRecordingDevice(This,deviceId,result)	\
    ( (This)->lpVtbl -> setRecordingDevice(This,deviceId,result) ) 

#define IAgoraRtcEngineControl_setVideoCaptureDevice(This,deviceId,result)	\
    ( (This)->lpVtbl -> setVideoCaptureDevice(This,deviceId,result) ) 

#define IAgoraRtcEngineControl_get_fireEventInInitializationThread(This,pVal)	\
    ( (This)->lpVtbl -> get_fireEventInInitializationThread(This,pVal) ) 

#define IAgoraRtcEngineControl_put_fireEventInInitializationThread(This,newVal)	\
    ( (This)->lpVtbl -> put_fireEventInInitializationThread(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAgoraRtcEngineControl_INTERFACE_DEFINED__ */


#ifndef ___IAgoraRtcEngineControlEvents_DISPINTERFACE_DEFINED__
#define ___IAgoraRtcEngineControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IAgoraRtcEngineControlEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IAgoraRtcEngineControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C9A10FD6-1660-4DEF-856C-55DF11772DAE")
    _IAgoraRtcEngineControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IAgoraRtcEngineControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IAgoraRtcEngineControlEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IAgoraRtcEngineControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IAgoraRtcEngineControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IAgoraRtcEngineControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IAgoraRtcEngineControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IAgoraRtcEngineControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IAgoraRtcEngineControlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IAgoraRtcEngineControlEventsVtbl;

    interface _IAgoraRtcEngineControlEvents
    {
        CONST_VTBL struct _IAgoraRtcEngineControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IAgoraRtcEngineControlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IAgoraRtcEngineControlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IAgoraRtcEngineControlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IAgoraRtcEngineControlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IAgoraRtcEngineControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IAgoraRtcEngineControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IAgoraRtcEngineControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IAgoraRtcEngineControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_AgoraRtcEngineControl;

#ifdef __cplusplus

class DECLSPEC_UUID("DA06DE88-2602-478F-A731-5BEA37508D69")
AgoraRtcEngineControl;
#endif
#endif /* __AgoraRtcEngineControlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


