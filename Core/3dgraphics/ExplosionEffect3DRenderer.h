#pragma once

#ifdef _3D

	#ifdef _PC
		#include "../pc/3dgraphics/PCExplosionEffect3DRenderer.h"
		typedef PCExplosionEffect3DRenderer ExplosionEffect3DRenderer;
	#elif _SPSP
		#include "../psp/3dgraphics/PSPExplosionEffect3DRenderer.h"
		typedef PSPExplosionEffect3DRenderer ExplosionEffect3DRenderer;
	#elif _GC
		#include "../gc/3dgraphics/GCLaserEffect3DRenderer.h"
		typedef GCExplosionEffect3DRenderer ExplosionEffect3DRenderer;
	#endif

#endif