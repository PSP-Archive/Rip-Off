#pragma once

#ifdef _3D

#include "../../ui/TextIF.h"
#include "Symbols.h"


class ConfigItem;

class Text3D:public TextIF{
public:

	~Text3D();
	
	void printChar(const char character)const;

};



inline void Text3D::printChar(const char c)const{
	Symbols::get()->printChar(c,getScale());
}

#endif