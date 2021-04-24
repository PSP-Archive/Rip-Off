#ifdef _PC

#include <iostream>
#include "pc/sound/PCSoundDevice.h"

#ifdef _3DSFX
#include "pc/sound/PCSoundEFX.h"
#endif

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
PCSoundDevice::PCSoundDevice()
{
	// empty
}

//--------------------------------------------------------------------------------
PCSoundDevice::~PCSoundDevice()
{
	// empty
}

//--------------------------------------------------------------------------------
bool 
PCSoundDevice::init()
{
	m_device = alcOpenDevice("DirectSound3D");
	if(m_device == NULL)
	{
		return false;
	}
		
	//Create context(s)
	m_context = alcCreateContext(m_device, NULL);
	if (m_context == NULL)
	{
		return false; 
	}

	//Set active context
	alcMakeContextCurrent(m_context);

	// Clear Error Code
	alGetError();

#ifdef _3DSFX

	// Set EFX
	SoundEFX::get()->init();

#endif

	return true;
}

//--------------------------------------------------------------------------------
void 
PCSoundDevice::cleanUp()
{
	//Get active context
	m_context = alcGetCurrentContext();

	//Get device for active context
	m_device = alcGetContextsDevice(m_context);

	//Disable context
	alcMakeContextCurrent(NULL);

	//Release context(s)
	alcDestroyContext(m_context);

	//Close device
	alcCloseDevice(m_device);
}

#endif
