#ifdef _PC
	#include "../pc/sound/PCSound.h"
	typedef PCSound Sound;
#elif _SPSP
	#include "../psp/sound/PSPSound.h"
	typedef PSPSound Sound;
#elif _GC
	#include "../psp/sound/GCSound.h"
	typedef GCSound Sound;
#endif