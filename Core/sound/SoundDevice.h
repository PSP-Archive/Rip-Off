#ifdef _PC
	#include "pc/sound/PCSoundDevice.h"
	typedef PCSoundDevice SoundDevice;
#elif _SPSP
	#include "psp/sound/PSPSoundDevice.h"
	typedef PSPSoundDevice SoundDevice;
#elif _GC
	#include "psp/sound/GCSoundDevice.h"
	typedef GCSoundDevice SoundDevice;
#endif