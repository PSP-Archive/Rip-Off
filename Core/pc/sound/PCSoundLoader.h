#pragma once

#include "sound/SoundLoaderIF.h"
#include "sound/Sound.h"
#include "AL/al.h"
#include "AL/alc.h"
#include "foundation/ConfigItem.h"

/*	=====================================================================
		PC implementation of sound loader.
		
		A pc sound config item would look like this:

			item SoundEffect
				string	wavFile		name_of_wav_file.wav
				integer looping		0						(or 1)
			enditem

	=====================================================================	*/
class PCSoundLoader : public SoundLoaderIF
{
public:
	// Load a sound wave file into a AL source. Return true if the operation 
	// was successful and false otherwise.
	Sound* load(const ConfigItem& configItem);

private:
	// Text constants for the config file
	static const std::string VAR_WAV_FILE;
	static const std::string VAR_LOOPING;
};
