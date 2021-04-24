#include "foundation/Singleton.h"

//--------------------------------------------------------------------------------
/**
	Implements platform specific Debug functions as a singleton.
	Usage:

		Debug::get()->output("Debug message that hopefully someone will read.");

	NOTE:
	Remember to call Debug::release() somewhere in the application cleanup.
*/
#ifdef _PC
	#include "pc/PCDebug.h"
	typedef Singleton<PCDebug> Debug;
#elif _SPSP
	#include "psp/PSPDebug.h"
	typedef Singleton<PSPDebug> Debug;
#elif _GC
	#include "gc/GCDebug.h"
	typedef Singleton<GCDebug> Debug;
#endif