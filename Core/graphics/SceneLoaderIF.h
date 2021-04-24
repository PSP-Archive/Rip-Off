#pragma once
#include "foundation/ConfigItem.h"
#include "Scene.h"

// Disable warning for unreferenced formal parameters as this is an interface
#pragma warning( disable: 4100 )

//--------------------------------------------------------------------------------
class SceneLoaderIF
{
public:
	//returns a Scene if the loading was successfull, NULL otherwise
	Scene* load(const ConfigItem& confItem){ assert(!"Interface not implemented"); return NULL; }
};