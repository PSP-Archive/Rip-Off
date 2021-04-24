#pragma once

#ifdef _3D
	#ifdef _PC
		#include "../pc/3dgraphics/PCSphereRenderer.h"
		typedef PCSphereRenderer SphereRenderer;
	#elif _SPSP
		#include "../psp/3dgraphics/PSPSphereRenderer.h"
		typedef PSPSphereRenderer SphereRenderer;
	#elif _GC
		//#include "../psp/3dgraphics/GCSphereRenderer.h"
		//typedef GCSphereRenderer SphereRenderer;
	#endif
#endif