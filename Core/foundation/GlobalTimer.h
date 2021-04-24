#include "foundation/Singleton.h"

//--------------------------------------------------------------------------------
/**
	Implements platform specific global timer signleton. It is just a raw timing
	class. For more advanced functionality use the Timer class.

	NOTE:
	Remember to call Debug::release() somewhere in the application cleanup.
*/
#ifdef _PC
	#include "pc/PCGlobalTimer.h"
	typedef Singleton<PCGlobalTimer> GlobalTimer;
#elif _SPSP
	#include "psp/PSPGlobalTimer.h"
	typedef Singleton<PSPGlobalTimer> GlobalTimer;
#elif _GC
	#include "gc/GCGlobalTimer.h"
	typedef Singleton<GCGlobalTimer> GlobalTimer;
#endif