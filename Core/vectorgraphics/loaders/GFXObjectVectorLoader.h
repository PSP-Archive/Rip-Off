#pragma once

#include <map>

#include "graphics/GFXObjectLoaderIF.h"
#include "vectorgraphics/LinePrimitive.h"

//--------------------------------------------------------------------------------
/**
	Loader for vector specific geometry. Reads a ConfigItem formatted this way:

	item XXX
		float lineWidth 2.0
		vector color 1.0 0.0 1.0
		string geometry vector/ship1.dat
	enditem

	NOTE:
	Alpha not implemented as not needed fo now

	TODO:
	Optimize by loading each primitve file once. Currently not a problem as the
	GameLoader loads each GFXObject only once.
*/
class GFXObjectVectorLoader : public GFXObjectLoaderIF
{
public:
	// Loads
	GFXObject* load(const ConfigItem& confItem);

private:
	// Config constants
	static const std::string LINEWIDTH;
	static const std::string COLOR;
	static const std::string GEOMETRY;
	static const std::string GEOMETRY_STRIP;
	static const std::string GEOMETRY_LIST;
	static const std::string SCALE;

	// Loads a file with vector data
	LinePrimitive* loadPrimitiveFromFile(const std::string&);
};
