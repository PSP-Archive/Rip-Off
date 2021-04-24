#pragma once

//#include "AL/al.h"
//#include "AL/alc.h"
#include "sound/SoundDevice.h"
#include "foundation/Singleton.h"

/*	=====================================================================
		Generic Sound Manager.
	=====================================================================	*/
class SoundManagerBase
{
public:
	SoundManagerBase();
	~SoundManagerBase();

	// Initialize the context and sound device.
	bool init();

	// Release the context and sound device.
	void cleanUp();

	// Read the sound wave data from sound config file. Return true if the operation 
	// was successful and false otherwise.
	//bool readConfigData(const string& config);

private:
	SoundDevice* m_sound;
};

// Define the singleton manager
typedef Singleton<SoundManagerBase> SoundManager;