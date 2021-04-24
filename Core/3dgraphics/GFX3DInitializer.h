#ifdef _3D
	#ifdef _PC
		#include "../pc/3dgraphics/PCGfx3dInitializer.h"
		typedef PCGfx3dInitializer GFX3DInitializer;
	#elif _SPSP
		#include "../psp/3dgraphics/PSPGfx3dInitializer.h"
		typedef PSPGfx3DInitializer GFX3DInitializer;
	#elif _GC
		//#include "../psp/3dgraphics/GCGfx3dInitializer.h"
		//typedef GCGfx3dInitializer GFX3DInitializer;
	#endif
#endif