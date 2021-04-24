#pragma once

#include "sound/SoundDeviceIF.h"
#include "AL/al.h"
#include "AL/alc.h"

#pragma comment (lib, "OpenAL32.lib")

/*	=====================================================================
		PC implementation of sound loader
	=====================================================================	*/
class PCSoundDevice : public SoundDeviceIF
{
public:
	PCSoundDevice();
	~PCSoundDevice();

	// Initialize the context and sound device.
	bool init();

	// Release the context and sound device. 
	void cleanUp();

private:
	ALCcontext* m_context;
	ALCdevice* m_device;
};
