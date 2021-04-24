#ifdef _PC

#include <iostream>
#include "pc/PCDebug.h"

//--------------------------------------------------------------------------------
PCDebug::PCDebug()
{
	// empty
}

//--------------------------------------------------------------------------------
void
PCDebug::onOutput(const std::string& text)
{
	std::cout << text << std::endl;
}

#endif