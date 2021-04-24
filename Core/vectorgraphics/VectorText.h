#pragma once

#ifdef _PC
	#include "../pc/VectorGraphics/PCVectorText.h"
	typedef PCVectorText VectorText;
#elif _SPSP
	#include "../psp/VectorGraphics/PSPVectorText.h"
	typedef PSPVectorText VectorText;
#elif _GC
	//#include "../psp/VectorGraphics/GCVectorRenderer.h"
	//typedef GCVectorRenderer VectorRenderer;
#endif
