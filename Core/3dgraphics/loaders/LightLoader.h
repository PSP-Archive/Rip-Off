#pragma once

#ifdef _3D

#include "../Light.h"
#include "foundation/ConfigItem.h"

class LightLoader{
public:
	Light* load(const ConfigItem& confItem, int lightId);
};

#endif