#pragma once

#include <cassert>

/*	=====================================================================
		Interface for platform specific sound implementations.
	=====================================================================	*/
class SoundDeviceIF
{
public:
	// Called when sound framework should be initialized.
	bool init() { assert(!"Interface not implemented"); }

	// Called when the sound framework should be closed.
	void cleanUp() { assert(!"Interface not implemented"); }
};
