#pragma once

#ifdef _3D

	#ifdef _PC
		#include "../pc/3dgraphics/PCPositioner.h"
		typedef PCPositioner Positioner;
	#elif _SPSP
		#include "../psp/3dgraphics/PSPPositioner.h"
		typedef PSPPositioner Positioner;
	#elif _GC
		#include "../psp/3dgraphics/GCPositioner.h"
		typedef GCPositioner Positioner;
	#endif

#endif