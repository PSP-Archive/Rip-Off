#pragma once

#ifdef _PC
	#include "../pc/VectorGraphics/PCVectorRenderer.h"
	typedef PCVectorRenderer VectorRenderer;
#elif _SPSP
	#include "../psp/VectorGraphics/PSPVectorRenderer.h"
	typedef PSPVectorRenderer VectorRenderer;
#elif _GC
	//#include "../psp/VectorGraphics/GCVectorRenderer.h"
	//typedef GCVectorRenderer VectorRenderer;
#endif
