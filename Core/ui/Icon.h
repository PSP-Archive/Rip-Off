#pragma once

#ifdef _VECTOR
	#include "../vectorgraphics/VectorIcon.h"
	typedef VectorIcon Icon;
#elif _3D
#include "../3dgraphics/ui3d/UIIcon3D.h"
	typedef UIIcon3D Icon;
#endif