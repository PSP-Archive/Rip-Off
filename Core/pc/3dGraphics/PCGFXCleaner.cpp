#include "PCGFXCleaner.h"
#include "PCGlex.h"

#ifdef _3D
#ifdef _PC

void PCGFXCleaner::clean(){
	PCGlex::release();
}

#endif
#endif