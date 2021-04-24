#ifdef _VECTOR
	#include "vectorgraphics/loaders/SceneVectorLoader.h"
	typedef SceneVectorLoader SceneLoader;
#elif _3D
	#include "../3dgraphics/loaders/Scene3DLoader.h"
	typedef Scene3DLoader SceneLoader;
#endif
