#include "PSPTexMemInitializer.h"

PSPBaseTexMemInitializer::PSPBaseTexMemInitializer(){
	m_vramAddr=(u_char8*)sceGeEdramGetAddr();
	m_vramAddr+=SCEGU_VRAM_BUFSIZE32*2+SCEGU_VRAM_BUFSIZE;
	m_currentBP=m_vramAddr;
}

void PSPBaseTexMemInitializer::increaseVramAddr(int size){
	m_currentBP+=size;
}
