#pragma once

//used for cleaning platform specific singletons

#ifdef _3D

	#ifdef _PC
		#include "../pc/3dgraphics/PCGFXCleaner.h"
		typedef PCGFXCleaner GFXCleaner;
	#elif _SPSP
		#include "../psp/3dgraphics/PSPGFXCleaner.h"
		typedef PSPGFXCleaner GFXCleaner;
	#elif _GC
		#include "../psp/3dgraphics/GCGFXCleaner.h"
		typedef GCGFXCleaner GFXCleaner;
	#endif

#endif