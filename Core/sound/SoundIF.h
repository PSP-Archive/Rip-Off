#pragma once

#include <cassert>

/*	=====================================================================
		Interface for platform specific sound access.
	=====================================================================	*/
class SoundIF
{
public:
	// Play the sound.
	void play() { assert(!"Interface not implemented"); }

	// Stop the sound.
	void stop() { assert(!"Interface not implemented"); }
};
