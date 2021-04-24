#pragma once

#include <string>
#include <cassert>
#include "sound/Sound.h"
#include "foundation/ConfigItem.h"

// Disable warning for unreferenced formal parameters as this is an interface
#pragma warning( disable: 4100 )

/*	=====================================================================
		Interface for platform specific sound loader.
	=====================================================================	*/
class SoundLoaderIF
{
public:
	// Load the sound file. Return true if the operation was successful and false otherwise.
	Sound* load(const ConfigItem& configItem) { assert(!"Interface not implemented"); return NULL; }
};
