#pragma once

#include "graphics/EffectLoaderIF.h"
#include "vectorgraphics/GFXObjectVector.h"

//--------------------------------------------------------------------------------
/**
	Creats and loads a vector effect from the config item. Should be in one of
	these forms:

	Line Explosion Effect:
		item XXX
			string type lineExplosion
			vector color 1 1 1
			float lineWidth 1.5
			float scale 0.2
			integer lineCount 20
			float duration 1
			float angleRandomness 15
			float lengthRandomness 0.2
		enditem

	Triangle Explosion Effect:
		item XXX
			string type triangleExplosion
			vector color 1 1 1
			float lineWidth 1.5
			float scale 0.2
			integer triangleCount 8
			float duration 1
			float triangleSize 0.4
		enditem

	Laser Effect:
		item XXX
			string type laser
			vector color 1 1 1
			float lineWidth 1.5
			float scale 0.2
			float duration 1
			float length 0.2
			float width 0.01
		enditem

	No Effect:
		item XXX
			string type none
		enditem
*/
class EffectVectorLoader : public EffectLoaderIF
{
public:
	// Loads
	EffectIF* load(const ConfigItem& confItem) const;

private:
	// Effect specific loaders
	EffectIF* loadLineExplosion(const ConfigItem& confItem) const;
	EffectIF* loadTriExplosion(const ConfigItem& confItem) const;
	EffectIF* loadLaser(const ConfigItem& confItem) const;
	void loadGfxObjectData(const ConfigItem& confItem, GFXObjectVector* obj) const;

	// Config constants
	static const std::string TYPE;
	static const std::string TYPE_LINEEXPLOSION;
	static const std::string TYPE_TRIEXPLOSION;
	static const std::string TYPE_LASER;
	static const std::string TYPE_NONE;
	static const std::string LINEWIDTH;
	static const std::string COLOR;
	static const std::string SCALE;
	static const std::string DURATION;

	// Line explosion specific
	static const std::string LINECOUNT;
	static const std::string ANGLE_RAND;
	static const std::string LENGTH_RAND;

	// Triangle explosion specific
	static const std::string TRIANGLECOUNT;
	static const std::string TRIANGLESIZE;

	// Laser specific
	static const std::string LENGTH;
	static const std::string WIDTH;
	static const std::string OFFSET;
};
