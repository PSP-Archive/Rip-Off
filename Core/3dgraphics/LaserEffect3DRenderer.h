#pragma once

#ifdef _3D

	#ifdef _PC
		#include "../pc/3dgraphics/PCLaserEffect3DRenderer.h"
		typedef PCLaserEffect3DRenderer LaserEffect3DRenderer;
	#elif _SPSP
		#include "../psp/3dgraphics/PSPLaserEffect3DRenderer.h"
		typedef PSPLaserEffect3DRenderer LaserEffect3DRenderer;
	#elif _GC
		#include "../gc/3dgraphics/GCLaserEffect3DRenderer.h"
		typedef GCLaserEffect3DRenderer LaserEffect3DRenderer;
	#endif

#endif