#pragma once

#include "foundation/Singleton.h"
#include <libgu.h>
#include <libgum.h>


class PSPBaseTexMemInitializer{
public:
	PSPBaseTexMemInitializer();

	u_char8 * getVramAddr();
	
	//increase Vram addr from graphics memory
	//note that it supposes all the textures are loaded once,
	//and are not deallocated during the game
	void increaseVramAddr(int size);

private:
	u_char8 *m_vramAddr;
	u_char8 *m_currentBP;
};

inline u_char8 * PSPBaseTexMemInitializer::getVramAddr(){
	return m_currentBP;
	//return m_vramAddr;
}

typedef Singleton<PSPBaseTexMemInitializer> PSPTexMemInitializer;