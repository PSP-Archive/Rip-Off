#pragma once

#ifdef _3D

#include "foundation/ConfigItem.h"
#include "../ParticleSystem.h"


class ParticleSystemLoader{
public:
	ParticleSystem* load(const ConfigItem& item) const;
};

#endif