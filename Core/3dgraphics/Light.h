#pragma once

#ifdef _3D
	#ifdef _PC
		#include "../pc/3dgraphics/PCLight.h"
		typedef PCLight Light;
	#elif _SPSP
		#include "../psp/3dgraphics/PSPLight.h"
		typedef PSPLight Light;
	#elif _GC
		//#include "../psp/3dgraphics/GCLight.h"
		//typedef GCLight Light;
	#endif
#endif