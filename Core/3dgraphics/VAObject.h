#pragma once
#ifdef _3D
	#ifdef _PC
		#include "../pc/3dgraphics/PCVAObject.h"
		typedef PCVAObject VAObject;
	#elif _SPSP
		#include "../psp/3dgraphics/PSPVAObject.h"
		typedef PSPVAObject VAObject;
	#elif _GC
		//#include "../gc/3dgraphics/GCVAObject.h"
		//typedef GCVAObject VAObject;
	#endif
#endif