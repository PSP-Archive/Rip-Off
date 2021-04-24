#pragma once
#include "Widget.h"

class IconIF: public Widget
{
public:
	
	//IconIF(){};
	//~IconIF(void){};

	virtual void renderGeometry() const=0;
};
