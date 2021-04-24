#pragma once

#ifdef _3D

#include "foundation/ConfigItem.h"
#include "../Material.h"
#include "../Texture.h"
#include "../Icon3D.h"

class Icon3DLoader{
public:
	~Icon3DLoader(){}

	virtual Icon3D* load(const ConfigItem& confItem, int id=0, bool isBack=false) const;
};

#endif