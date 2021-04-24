#pragma once

#ifdef _3D
#ifdef _SPSP

#include "../../3dgraphics/GFXCleanerIF.h"

class PSPGFXCleaner: public GFXCleanerIF{
public:
	void clean(); 
};

#endif
#endif