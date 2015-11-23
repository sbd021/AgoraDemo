#include "StdAfx.h"
#include "AGAudioDeviceManager.h"

#include <Mmsystem.h>

#pragma comment(lib, "Winmm")

CAGAudioDeviceManager::CAGAudioDeviceManager(void)
	: m_nInputDeviceCount(-1)
	, m_nOutputDeviceCount(-1)
{
}

CAGAudioDeviceManager::~CAGAudioDeviceManager(void)
{
}

int CAGAudioDeviceManager::GetInputDeviceCount()
{
	if(m_nInputDeviceCount == -1)
		m_nInputDeviceCount = ::waveInGetNumDevs();

	return m_nInputDeviceCount;
}

int CAGAudioDeviceManager::GetOutputDeviceCount()
{
	if(m_nOutputDeviceCount == -1)
		m_nOutputDeviceCount = ::waveOutGetNumDevs();

	return m_nOutputDeviceCount;
}