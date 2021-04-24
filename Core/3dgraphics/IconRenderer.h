#pragma once

#ifdef _3D
	#ifdef _PC
		#include "../pc/3dgraphics/PCIconRenderer.h"
		typedef PCIconRenderer IconRenderer;
	#elif _SPSP
		#include "../psp/3dgraphics/PSPIconRenderer.h"
		typedef PSPIconRenderer IconRenderer;
	#elif _GC
		//#include "../psp/3dgraphics/GCIconRenderer.h"
		//typedef GCIconRenderer IconRenderer;
	#endif
#endif