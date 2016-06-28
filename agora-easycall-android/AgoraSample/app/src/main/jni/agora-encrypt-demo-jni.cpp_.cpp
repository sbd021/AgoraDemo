#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <vector>
#include <stddef.h>

namespace agora {
namespace rtc {
class IPacketObserver
{
public:

	struct Packet
	{
		const unsigned char* buffer;
		unsigned int size;
	};
	/**
	* called by sdk before the audio packet is sent to other participants
	* @param [in,out] packet:
	*      buffer *buffer points the data to be sent
	*      size of buffer data to be sent
	* @return returns true to send out the packet, returns false to discard the packet
	*/
	virtual bool onSendAudioPacket(Packet& packet) = 0;
	/**
	* called by sdk before the video packet is sent to other participants
	* @param [in,out] packet:
	*      buffer *buffer points the data to be sent
	*      size of buffer data to be sent
	* @return returns true to send out the packet, returns false to discard the packet
	*/
	virtual bool onSendVideoPacket(Packet& packet) = 0;
	/**
	* called by sdk when the audio packet is received from other participants
	* @param [in,out] packet
	*      buffer *buffer points the data to be sent
	*      size of buffer data to be sent
	* @return returns true to process the packet, returns false to discard the packet
	*/
	virtual bool onReceiveAudioPacket(Packet& packet) = 0;
	/**
	* called by sdk when the video packet is received from other participants
	* @param [in,out] packet
	*      buffer *buffer points the data to be sent
	*      size of buffer data to be sent
	* @return returns true to process the packet, returns false to discard the packet
	*/
	virtual bool onReceiveVideoPacket(Packet& packet) = 0;
};
}
}

class AgoraPacketObserver : public agora::rtc::IPacketObserver
{
	typedef std::vector<unsigned char> buffer_type;
public:
	AgoraPacketObserver()
	{
		m_txAudioBuffer.resize(2048);
		m_rxAudioBuffer.resize(2048);
		m_txVideoBuffer.resize(2048);
		m_rxVideoBuffer.resize(2048);
	}
	virtual bool onSendAudioPacket(Packet& packet) override
	{
		return onSendPacket(packet, m_txAudioBuffer);
	}
	virtual bool onSendVideoPacket(Packet& packet) override
	{
		return onSendPacket(packet, m_txVideoBuffer);
	}
	virtual bool onReceiveAudioPacket(Packet& packet) override
	{
		return onReceivePacket(packet, m_rxAudioBuffer);
	}
	virtual bool onReceiveVideoPacket(Packet& packet) override
	{
		return onReceivePacket(packet, m_rxVideoBuffer);
	}
private:
	static bool onSendPacket(Packet& packet, buffer_type& buffer)
	{
		size_t i;
		const unsigned char* p = packet.buffer;
		const unsigned char* pe = packet.buffer + packet.size;
		for (i = 0; p < pe && i < buffer.size(); ++p, ++i)
		{
			buffer[i] = *p ^ 0x55;
		}
		packet.buffer = &buffer[0];
		packet.size = i;
		return true;
	}
	static bool onReceivePacket(Packet& packet, buffer_type& buffer)
	{
		size_t i = 0;
		const unsigned char* p = packet.buffer;
		const unsigned char* pe = packet.buffer + packet.size;
		for (i = 0; p < pe && i < buffer.size(); ++p, ++i)
		{
			buffer[i] = *p ^ 0x55;
		}
		packet.buffer = &buffer[0];
		packet.size = i;
		return true;
	}
private:
	buffer_type m_txAudioBuffer;
	buffer_type m_rxAudioBuffer;
	buffer_type m_txVideoBuffer;
	buffer_type m_rxVideoBuffer;
};
static AgoraPacketObserver s_packetObserver;

#ifdef __cplusplus
extern "C" {
#endif

jint JNICALL JNI_OnLoad(JavaVM* jvm, void* reserved)
{
	return JNI_VERSION_1_6;
}

void JNICALL JNI_OnUnload(JavaVM* jvm, void* reserved)
{
}

JNIEXPORT jint JNICALL java_io_agora_sample_agora_RtcEngineEncryption_enableEncryption(JNIEnv *env, jclass clazz, jlong engineHandle)
{
	typedef jint (*PFN_registerAgoraPacketObserver)(void* engine, agora::rtc::IPacketObserver* observer);
		
	void* handle = dlopen("libagora-rtc-sdk-jni.so", RTLD_LAZY);
	if (!handle)
	{
		__android_log_print(ANDROID_LOG_ERROR, "aogra encrypt demo", "cannot find libagora-rtc-sdk-jni.so");
		return -1;
	}
	PFN_registerAgoraPacketObserver pfn = (PFN_registerAgoraPacketObserver)dlsym(handle, "registerAgoraPacketObserver");
	if (!pfn)
	{
		__android_log_print(ANDROID_LOG_ERROR, "aogra encrypt demo", "cannot find registerAgoraPacketObserver");
		return -2;
	}
	return pfn((void*)engineHandle, &s_packetObserver);
}

#ifdef __cplusplus
}
#endif
