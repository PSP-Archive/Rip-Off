/* VERSION HISTORY

25/02/2010 - Ewe Yee Seong	- Setup sound class
							- TODO: Sync the constructor with PCSound
									Research on playing a looping sound

*/

#pragma once

#include "sound/SoundIF.h"
#include <libsas.h>

/* lib files to be include :
	libsas_weak.a
*/

/*	=====================================================================
		PSP implementation of sound
	=====================================================================	*/
class PSPSound : public SoundIF
{
public:
	PSPSound();
	PSPSound(int id, const void *source, SceUInt32 size, bool looping = false);
	~PSPSound();

	// Play the sound.
	void play();

	// Stop the sound.
	void stop();

private:
	// voice id
	int m_voiceID;
};

