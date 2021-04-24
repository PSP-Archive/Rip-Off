#pragma once

#include "engine/Ship.h"
#include "engine/Cargo.h"
#include "engine/Bullet.h"
#include "foundation/ConfigData.h"
#include "graphics/GFXObjectLoader.h"
#include "sound/Sound.h"
#include "sound/SoundLoader.h"
#include "graphics/SceneLoader.h"
#include "engine/GuardianShip.h"
#include "engine/ThiefShip.h"
#include "graphics/EffectLoader.h"

//--------------------------------------------------------------------------------
class GameLoader
{
public:
	// Ctor
	GameLoader();

	// Dtor
	~GameLoader();

	// Preloads data
	bool load(const ConfigData* confData);

	// Creates and returns a Guardian ship
	GuardianShip* createGuardianShip(unsigned int index);

	// Creates and returns a thief ship
	ThiefShip* createThiefShip(unsigned int index);

	// Creates and returns a cargo
	Cargo* createCargo();

	// Creates and returns a bullet
	Bullet* createBullet();

	// Creates and returns a bullet
	Scene* createScene();

	// Create effects
	EffectIF* createThiefExplosion1();
	EffectIF* createThiefExplosion2();
	EffectIF* createGuardianExplosion1();
	EffectIF* createGuardianExplosion2();
	EffectIF* createLaser();
	EffectIF* createGameoverExplosion();
	EffectIF* createGameoverExplosion1();
	EffectIF* createFireJet();

private:
	// Sound objects
	enum
	{
		GUARDIAN_SHOOT_SFX = 0,
		THIEF_SHOOT_SFX,
		EXPLOSION_SFX,
		THIEF_HOOK_SFX,
		PHASE1_MUSIC,
		PHASE2_MUSIC,
		PHASE3_MUSIC,
		PHASE4_MUSIC,
		PHASE5_MUSIC,
		PHASE6_MUSIC,
		BACKGROUND_MUSIC,
		MENU_MUSIC,					// sound object for menu
		KEY_SFX,
		SELECT_SFX,

		NUM_SFX
	};

	// Graphics objects
	enum
	{
		GUARDIAN1_GFX = 0,
		GUARDIAN2_GFX,
		GUARDIAN_BULLET_GFX,
		THIEF1_GFX,
		THIEF2_GFX,
		THIEF3_GFX,
		THIEF4_GFX,
		THIEF5_GFX,
		THIEF6_GFX,
		CARGO_GFX,
		CARGO_HOOK_GFX,

		NUM_GFX
	};

	// Config handles
	enum
	{
		GUARDIAN1_HANDLE = 0,
		GUARDIAN2_HANDLE,
		GUARDIAN_BULLET_HANDLE,
		THIEF1_HANDLE,
		THIEF2_HANDLE,
		THIEF3_HANDLE,
		THIEF4_HANDLE,
		THIEF5_HANDLE,
		THIEF6_HANDLE,
		CARGO_HANDLE,
		SCENE_HANDLE,

		THIEF_EXPLOSION1_HANDLE,
		THIEF_EXPLOSION2_HANDLE,
		GUARDIAN_EXPLOSION1_HANDLE,
		GUARDIAN_EXPLOSION2_HANDLE,
		LASER_HANDLE,
		GAMEOVER_EXPLOSION_HANDLE,
		GAMEOVER_EXPLOSION1_HANDLE,
		FIRE_JET_HANDLE,
		NUM_HANDLES
	};

	// Collections
	ConfigData::ItemHandle m_handles[NUM_HANDLES];
	GFXObject* m_gfx[NUM_GFX];
	Sound* m_sounds[NUM_SFX];
	
	// Loaders
	GFXObjectLoader m_gfxObjLoader;
	SoundLoader m_soundLoader;
	SceneLoader m_sceneLoader;
	EffectLoader m_effectLoader;

	//Scene *m_pSceneHack;

	// Reference to the config data
	const ConfigData* m_config;
};
