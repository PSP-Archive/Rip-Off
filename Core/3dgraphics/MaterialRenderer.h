#pragma once

#ifdef _3D
	#ifdef _PC
		#include "../pc/3dgraphics/PCMaterialRenderer.h"
		typedef PCMaterialRenderer MaterialRenderer;
	#elif _SPSP
		#include "../psp/3dgraphics/PSPMaterialRenderer.h"
		typedef PSPMaterialRenderer MaterialRenderer;
	#elif _GC
		//#include "../psp/3dgraphics/GCMaterialRenderer.h"
		//typedef GCMaterialRenderer MaterialRenderer;
	#endif
#endif