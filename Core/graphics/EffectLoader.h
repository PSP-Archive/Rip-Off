#pragma once

#ifdef _3D
	#include "3dgraphics/loaders/Effect3DLoader.h"
	typedef Effect3DLoader EffectLoader;
#elif _VECTOR
	#include "vectorgraphics/loaders/EffectVectorLoader.h"
	typedef EffectVectorLoader EffectLoader;
#endif