#ifdef _PC
	#include "pc/PCInputDevice.h"
	typedef PCInputDevice InputDevice;
#elif _SPSP
	#include "psp/PSPInputDevice.h"
	typedef PSPInputDevice InputDevice;
#elif _GC
	#include "psp/GCInputDevice.h"
	typedef GCInputDevice InputDevice;
#endif