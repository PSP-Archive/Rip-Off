#pragma once

#include "sound/SoundLoaderIF.h"
#include "sound/Sound.h"

#include "foundation/ConfigItem.h"

using namespace std;

/*	=====================================================================
		PSP implementation of sound loader.
		
		A pc sound config item would look like this:

			item SoundEffect
				string	wavFile		name_of_wav_file.wav
				integer looping		0						(or 1)
			enditem

	=====================================================================	*/
class PSPSoundLoader : public SoundLoaderIF
{
public:
	// Load a sound wave file into a AL source. Return true if the operation 
	// was successful and false otherwise.
	PSPSoundLoader();
	~PSPSoundLoader();

	Sound* load(const ConfigItem& configItem);

private:
	// Text constants for the config file
	static const string VAR_WAV_FILE;
	static const string VAR_LOOPING;

	static int m_soundNum;

	static void* m_effectBuffer[32] __attribute__((aligned(16)));
	static SceUID m_bufID[32];
};

