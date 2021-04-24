#pragma once

#include <cassert>

//--------------------------------------------------------------------------------
/**
	Interface for a global timing signleton.

	NOTE:
	This is a raw timing implementation. For more advanced functionality use the
	Timer class.
*/
class GlobalTimerIF
{
public:
	// Restarts the global time in SECONDS.
	void reset() { assert(!"Interface not implemented"); }

	// Closes the file and cleans up.
	float getTime() const { assert(!"Interface not implemented"); return false; }
};
