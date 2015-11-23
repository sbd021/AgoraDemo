#pragma once

/*
coded by walker05 2015 in Agorus
*/

class CAGAudioDeviceManager
{
public:
	CAGAudioDeviceManager(void);
	~CAGAudioDeviceManager(void);

	int GetInputDeviceCount();
	int GetOutputDeviceCount();

private:
	int m_nInputDeviceCount;
	int m_nOutputDeviceCount;
};
