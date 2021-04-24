#pragma once

#ifdef _3D
	#include "3dgraphics/loaders/GFXObject3DLoader.h"
	typedef GFXObject3DLoader GFXObjectLoader;
#elif _VECTOR
	#include "vectorgraphics/loaders/GFXObjectVectorLoader.h"
	typedef GFXObjectVectorLoader GFXObjectLoader;
#endif