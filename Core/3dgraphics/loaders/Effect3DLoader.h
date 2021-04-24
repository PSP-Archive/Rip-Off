#pragma once

#ifdef _3D

#include "../../graphics/EffectLoaderIF.h"

class Effect3DLoader:public EffectLoaderIF{
public:
	EffectIF* load(const ConfigItem& item) const;
};

#endif