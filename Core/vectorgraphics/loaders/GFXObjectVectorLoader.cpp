#ifdef _VECTOR

#include <sstream>

#include "vectorgraphics/loaders/GFXObjectVectorLoader.h"
#include "vectorgraphics/GFXObjectVector.h"
#include "foundation/File.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

const std::string GFXObjectVectorLoader::LINEWIDTH("lineWidth");
const std::string GFXObjectVectorLoader::COLOR("color");
const std::string GFXObjectVectorLoader::GEOMETRY("geometry");
const std::string GFXObjectVectorLoader::GEOMETRY_STRIP("strip");
const std::string GFXObjectVectorLoader::GEOMETRY_LIST("list");
const std::string GFXObjectVectorLoader::SCALE("scale");

//--------------------------------------------------------------------------------
GFXObject*
GFXObjectVectorLoader::load(const ConfigItem& item)
{
	GFXObjectVector* object = new GFXObjectVector;
	
	if(item.hasVector(COLOR))
	{
		Vector3f color = item.getVector(COLOR);
		object->SetColour(Vector4f(color[0], color[1], color[2], 1.0f));
	}
	
	if(item.hasFloat(LINEWIDTH))
	{
		object->SetLineWidth(item.getFloat(LINEWIDTH));
	}
	
	if(item.hasFloat(SCALE))
	{
		object->SetScale(item.getFloat(SCALE));
	}
	
	if(item.hasString(GEOMETRY))
	{
		LinePrimitive* lp;
		if(lp = loadPrimitiveFromFile(item.getString(GEOMETRY)))
		{
			object->setPrimitive(lp);	
		}
	}
	
	return object;
}

//--------------------------------------------------------------------------------
LinePrimitive*
GFXObjectVectorLoader::loadPrimitiveFromFile(const std::string& filepath)
{
	File file;

	if(!file.open(filepath))
	{
		Debug::get()->output("Error opening vector graphics file.");
		return NULL;
	}

	std::string temp;
	
	// The first line must be STRIP or LIST
	if(!file.readLine(temp))
	{
		Debug::get()->output("Error in vector graphics file format.");
		return NULL;
	}

	// Extract the type
	std::istringstream stream(temp);
	if(!(stream >> temp))
	{
		Debug::get()->output("Error in vector graphics file format.");
		return NULL;
	}

	LinePrimitive::LinePrimitiveType type;
	
	// Check type
	if(!temp.compare(GEOMETRY_LIST))
	{
		type = LinePrimitive::LIST;
	}
	else if(!temp.compare(GEOMETRY_STRIP))
	{
		type = LinePrimitive::STRIP;
	}
	else
	{
		Debug::get()->output("Error in vector graphics file format.");
		return NULL;
	}

	// Create the primitive as now it is valid for sure
	LinePrimitive* lp = new LinePrimitive;
	lp->SetLPType(type);

	// Populate the primitive
	float x;
	float y;
	while(file.readLine(temp))
	{
		if(temp[0] == '/' && temp[1] == '/')
		{
			continue;
		}
		
		std::istringstream stream(temp);
		stream >> x;
		stream >> y;
		lp->AddPoint(Vector2f(x, y));
	}
	
	return lp;
}

#endif