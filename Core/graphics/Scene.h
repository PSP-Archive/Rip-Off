#pragma once
#ifdef _VECTOR
	#include "vectorgraphics/VectorScene.h"
	typedef VectorScene Scene;
#elif _3D
	#include "3dgraphics/Scene3D.h"
	typedef Scene3D Scene;
#endif

