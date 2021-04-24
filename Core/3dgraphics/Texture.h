#pragma once

#ifdef _3D

	#ifdef _PC
		#include "../pc/3dgraphics/PCTexture.h"
		typedef PCTexture Texture;
	#elif _SPSP
		#include "../psp/3dgraphics/PSPTexture.h"
		typedef PSPTexture Texture;
	#elif _GC
		//#include "../psp/3dgraphics/GCTexture.h"
		//typedef GCTexture Texture;
	#endif

#endif