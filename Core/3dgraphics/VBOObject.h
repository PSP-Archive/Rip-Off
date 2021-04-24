#pragma once

#ifdef _3D
	
	#ifdef _PC
		#include "../pc/3dgraphics/PCVBOObject.h"
		typedef PCVBOObject VBOObject;
	#elif _SPSP
		#include "../psp/3dgraphics/PSPVBOObject.h"
		typedef PSPVBOObject VBOObject;
	#elif _GC
		//#include "../psp/3dgraphics/GCVBOObject.h"
		//typedef GCVBOObject VBOObject;
	#endif

#endif