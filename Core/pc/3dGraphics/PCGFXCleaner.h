#pragma once

#ifdef _3D
#ifdef _PC

#include "../../3dgraphics/GFXCleanerIF.h"

class PCGFXCleaner: public GFXCleanerIF{
public:
	void clean(); 
};

#endif
#endif