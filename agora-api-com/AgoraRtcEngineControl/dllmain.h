// dllmain.h : Declaration of module class.

class CAgoraRtcEngineControlModule : public ATL::CAtlDllModuleT< CAgoraRtcEngineControlModule >
{
public :
	DECLARE_LIBID(LIBID_AgoraRtcEngineControlLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_AGORARTCENGINECONTROL, "{94E69032-614E-45CD-8A1B-C31EA4F07FC1}")
};

extern class CAgoraRtcEngineControlModule _AtlModule;
