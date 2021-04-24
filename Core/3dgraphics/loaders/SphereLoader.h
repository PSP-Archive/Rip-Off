#pragma once

#ifdef _3D

#include "../Sphere.h"
#include "../Material.h"
#include "foundation/ConfigItem.h"

class SphereLoader{
public:
	Shape3D* load(const ConfigItem& confItem, Material **ppMaterial) const;
};

#endif