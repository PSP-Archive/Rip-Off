#pragma once
#include "graphics/GFXObject.h"
#include "foundation/ConfigItem.h"

// Disable warning for unreferenced formal parameters as this is an interface
#pragma warning( disable: 4100 )

//--------------------------------------------------------------------------------
/**
	Interface for GFX object loader.
*/
class GFXObjectLoaderIF
{
public:
	// Reads the data from a conf file and creates a GFXObject
	GFXObject* load(const ConfigItem& confItem) { assert(!"Interface not implemented"); return NULL; }
};