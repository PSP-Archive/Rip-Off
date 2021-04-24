#ifdef _VECTOR

#include "vectorgraphics/loaders/EffectVectorLoader.h"
#include "vectorgraphics/VectorLineExplosionEffect.h"
#include "vectorgraphics/VectorTriangleExplosionEffect.h"
#include "vectorgraphics/VectorLaserEffect.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

// Config constants
const std::string EffectVectorLoader::TYPE("type");
const std::string EffectVectorLoader::TYPE_LINEEXPLOSION("lineExplosion");
const std::string EffectVectorLoader::TYPE_TRIEXPLOSION("triangleExplosion");
const std::string EffectVectorLoader::TYPE_LASER("laser");
const std::string EffectVectorLoader::TYPE_NONE("none");
const std::string EffectVectorLoader::LINEWIDTH("lineWidth");
const std::string EffectVectorLoader::COLOR("color");
const std::string EffectVectorLoader::SCALE("scale");
const std::string EffectVectorLoader::DURATION("duration");

// Line explosion specific
const std::string EffectVectorLoader::LINECOUNT("lineCount");
const std::string EffectVectorLoader::ANGLE_RAND("angleRandomness");
const std::string EffectVectorLoader::LENGTH_RAND("lengthRandomness");

// Triangle explosion specific
const std::string EffectVectorLoader::TRIANGLECOUNT("triangleCount");
const std::string EffectVectorLoader::TRIANGLESIZE("triangleSize");

// Laser specific
const std::string EffectVectorLoader::LENGTH("length");
const std::string EffectVectorLoader::WIDTH("width");
const std::string EffectVectorLoader::OFFSET("offset");

//--------------------------------------------------------------------------------
EffectIF*
EffectVectorLoader::load(const ConfigItem& item) const
{
	if(item.hasString(TYPE))
	{
		if(!item.getString(TYPE).compare(TYPE_LINEEXPLOSION))
		{
			return loadLineExplosion(item);
		}
		else if(!item.getString(TYPE).compare(TYPE_TRIEXPLOSION))
		{
			return loadTriExplosion(item);
		}
		else if(!item.getString(TYPE).compare(TYPE_LASER))
		{
			return loadLaser(item);
		}
	}

	return NULL;
}

//--------------------------------------------------------------------------------
EffectIF*
EffectVectorLoader::loadLineExplosion(const ConfigItem& item) const
{
	VectorLineExplosionEffect* effect = new VectorLineExplosionEffect;

	// Load the gfx object data
	loadGfxObjectData(item, &(effect->getGfxObject()));
	
	if(item.hasInteger(LINECOUNT))
	{
		effect->setLineCount(item.getInteger(LINECOUNT));
	}
	
	if(item.hasFloat(DURATION))
	{
		effect->setDuration(item.getFloat(DURATION));
	}
	
	if(item.hasFloat(ANGLE_RAND))
	{
		effect->setAngleRandomness(item.getFloat(ANGLE_RAND));
	}
	
	if(item.hasFloat(LENGTH_RAND))
	{
		effect->setLengthRandomness(item.getFloat(LENGTH_RAND));
	}
	
	return effect;
}

//--------------------------------------------------------------------------------
EffectIF*
EffectVectorLoader::loadTriExplosion(const ConfigItem& item) const
{
	VectorTriangleExplosionEffect* effect = new VectorTriangleExplosionEffect;

	// Load the gfx object data
	loadGfxObjectData(item, &(effect->getGfxObject()));
	
	if(item.hasInteger(TRIANGLECOUNT))
	{
		effect->setTriangleCount(item.getInteger(TRIANGLECOUNT));
	}
	
	if(item.hasFloat(DURATION))
	{
		effect->setDuration(item.getFloat(DURATION));
	}
	
	if(item.hasFloat(TRIANGLESIZE))
	{
		effect->setTriangleSize(item.getFloat(TRIANGLESIZE));
	}
	
	return effect;
}

//--------------------------------------------------------------------------------
EffectIF*
EffectVectorLoader::loadLaser(const ConfigItem& item) const
{
	VectorLaserEffect* effect = new VectorLaserEffect;

	// Load the gfx object data
	loadGfxObjectData(item, &(effect->getGfxObject()));
	
	if(item.hasFloat(DURATION))
	{
		effect->setDuration(item.getFloat(DURATION));
	}
	
	if(item.hasFloat(LENGTH))
	{
		effect->setLength(item.getFloat(LENGTH));
	}
	
	if(item.hasFloat(WIDTH))
	{
		effect->setWidth(item.getFloat(WIDTH));
	}
	
	if(item.hasFloat(OFFSET))
	{
		effect->setOffset(item.getFloat(OFFSET));
	}
	
	return effect;
}

//--------------------------------------------------------------------------------
void
EffectVectorLoader::loadGfxObjectData(const ConfigItem& item, GFXObjectVector* object) const
{
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
}

#endif