#pragma once

#include "graphics/EffectIF.h"
#include "foundation/ConfigItem.h"

// Disable warning for unreferenced formal parameters as this is an interface
#pragma warning( disable: 4100 )

//--------------------------------------------------------------------------------
/**
	Interface for loading effects.
*/
class EffectLoaderIF
{
public:
	// Reads the data from a conf file and creates a GFXObject
	EffectIF* load(const ConfigItem& confItem) const { assert(!"Interface not implemented"); return NULL; }
};