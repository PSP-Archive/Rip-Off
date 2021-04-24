#ifdef _PC
	#include "pc/sound/PCSoundLoader.h"
	typedef PCSoundLoader SoundLoader;
#elif _SPSP
	#include "psp/sound/PSPSoundLoader.h"
	typedef PSPSoundLoader SoundLoader;
#elif _GC
	#include "psp/sound/GCSoundLoader.h"
	typedef GCSoundLoader SoundLoader;
#endif