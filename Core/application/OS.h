#ifdef _PC
	#include "../pc/PCOS.h"
	typedef PCOS OS;
#elif _SPSP
	#include "../psp/PSPOS.h"
	typedef PSPOS OS;
#elif _GC
	#include "psp/GCOS.h"
	typedef GCOS OS;
#endif

	