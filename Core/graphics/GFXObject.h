#pragma once

#ifdef _3D
	#include "../3dgraphics/GFXObject3D.h"
	typedef GFXObject3D GFXObject;
#elif _VECTOR
	#include "vectorgraphics/GFXObjectVector.h"
	typedef GFXObjectVector GFXObject;
#endif