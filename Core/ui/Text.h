#pragma once

#ifdef _VECTOR
	#include "../vectorgraphics/VectorText.h"
	typedef VectorText Text;
#elif _3D
#include "../3dgraphics/ui3d/Text3D.h"
	typedef Text3D Text;
#endif