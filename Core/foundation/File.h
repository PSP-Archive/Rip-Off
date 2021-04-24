#ifdef _PC
	#include "pc/PCFile.h"
	typedef PCFile File;
#elif _SPSP
	#include "psp/PSPFile.h"
	typedef PSPFile File;
#elif _GC
	#include "psp/GCFile.h"
	typedef GCFile File;
#endif