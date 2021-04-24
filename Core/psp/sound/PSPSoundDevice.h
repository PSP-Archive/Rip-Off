/* VERSION HISTORY

25/02/2010 - Ewe Yee Seong	- Setup PSP sound context and device
							- Added PSP sound thread

*/
#pragma once

#include "sound/SoundDeviceIF.h"

using namespace std;

#define	SAMPLES				(256)

/*	=====================================================================
		PSP implementation of sound device

		ToUse:
			First initialize PSP sound, then start the PSP sound thread

	=====================================================================	*/
class PSPSoundDevice : public SoundDeviceIF
{
public:
	PSPSoundDevice();
	~PSPSoundDevice();

	// Initialize the context and sound device.
	bool init();

	// Release the context and sound device. 
	void cleanUp();

	// PSP sound thread
	void startThread();
	void endThread();

	// The main Sound Thread function
	static int sasThread(unsigned int args, void *argp);

private:
	// pcmBuf is a double buffer. It has 64-byte alignment
	static short pcmBuf[2][SAMPLES] __attribute__((aligned(64)));

	int m_threadID;
};
