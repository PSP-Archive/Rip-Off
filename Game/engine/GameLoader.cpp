#include "engine/GameLoader.h"
#include "foundation/ConfigDataLoader.h"
#include "foundation/ConfigItem.h"
#include "graphics/GFXObjectLoader.h"
#include "graphics/SceneLoader.h"
#include "engine/Game.h"
#include "foundation/PSPHeap.h"

#ifdef _3D
#include "3dgraphics/loaders/MaterialsLoader.h"
#include "3dgraphics/ui3d/Symbols.h"
#endif

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
GameLoader::GameLoader()
{	
	for(int i=0; i<NUM_GFX; ++i)
	{
		m_gfx[i] = NULL;
	}
	for(int i=0; i<NUM_SFX; ++i)
	{
		m_sounds[i] = NULL;
	}
}

//--------------------------------------------------------------------------------
#ifdef _3D
#include "3dgraphics/managers/TextureManager.h"
#include "3dgraphics/managers/MeshManager.h"
#include "3dgraphics/managers/MaterialManager.h"
#include "3dgraphics/managers/RandomHashTable.h"
#endif

GameLoader::~GameLoader()
{
	for(int i=0; i<NUM_GFX; ++i)
	{
		if(m_gfx[i])
		{
			delete m_gfx[i];
		}
	}
	for(int i=0; i<NUM_SFX; ++i)
	{
		if(m_sounds[i])
		{
			delete m_sounds[i];
		}
	}

#ifdef _3D
	Symbols::release();
	TextureManager::release();
	MaterialManager::release();
	RandomHashTable::release();
	MeshManager::release();
#endif
}

//--------------------------------------------------------------------------------
bool
GameLoader::load(const ConfigData* confData)
{
	assert(confData);

	m_config = confData;
	
	// Preload handles
	m_handles[GUARDIAN1_HANDLE] = m_config->getItemHandle("GUARDIAN1");
	assert(m_handles[GUARDIAN1_HANDLE] != ConfigData::INVALID_HANDLE);
	m_handles[GUARDIAN2_HANDLE] = m_config->getItemHandle("GUARDIAN2");
	assert(m_handles[GUARDIAN2_HANDLE] != ConfigData::INVALID_HANDLE);

	m_handles[GUARDIAN_BULLET_HANDLE] = m_config->getItemHandle("GUARDIAN_BULLET");
	assert(m_handles[GUARDIAN_BULLET_HANDLE] != ConfigData::INVALID_HANDLE);

	m_handles[THIEF1_HANDLE] = m_config->getItemHandle("THIEF1");
	assert(m_handles[THIEF1_HANDLE] != ConfigData::INVALID_HANDLE);
	m_handles[THIEF2_HANDLE] = m_config->getItemHandle("THIEF2");
	assert(m_handles[THIEF2_HANDLE] != ConfigData::INVALID_HANDLE);
	m_handles[THIEF3_HANDLE] = m_config->getItemHandle("THIEF3");
	assert(m_handles[THIEF3_HANDLE] != ConfigData::INVALID_HANDLE);
	m_handles[THIEF4_HANDLE] = m_config->getItemHandle("THIEF4");
	assert(m_handles[THIEF4_HANDLE] != ConfigData::INVALID_HANDLE);
	m_handles[THIEF5_HANDLE] = m_config->getItemHandle("THIEF5");
	assert(m_handles[THIEF5_HANDLE] != ConfigData::INVALID_HANDLE);
	m_handles[THIEF6_HANDLE] = m_config->getItemHandle("THIEF6");
	assert(m_handles[THIEF6_HANDLE] != ConfigData::INVALID_HANDLE);

	m_handles[CARGO_HANDLE] = m_config->getItemHandle("CARGO");
	assert(m_handles[CARGO_HANDLE] != ConfigData::INVALID_HANDLE);

	m_handles[SCENE_HANDLE] = m_config->getItemHandle("SCENE_GFX");
	assert(m_handles[SCENE_HANDLE] != ConfigData::INVALID_HANDLE);

	m_handles[THIEF_EXPLOSION1_HANDLE] = m_config->getItemHandle("THIEF_EXPLOSION1");
	assert(m_handles[THIEF_EXPLOSION1_HANDLE] != ConfigData::INVALID_HANDLE);
	m_handles[THIEF_EXPLOSION2_HANDLE] = m_config->getItemHandle("THIEF_EXPLOSION2");
	assert(m_handles[THIEF_EXPLOSION2_HANDLE] != ConfigData::INVALID_HANDLE);
	m_handles[GUARDIAN_EXPLOSION1_HANDLE] = m_config->getItemHandle("GUARDIAN_EXPLOSION1");
	assert(m_handles[GUARDIAN_EXPLOSION1_HANDLE] != ConfigData::INVALID_HANDLE);
	m_handles[GUARDIAN_EXPLOSION2_HANDLE] = m_config->getItemHandle("GUARDIAN_EXPLOSION2");
	assert(m_handles[GUARDIAN_EXPLOSION2_HANDLE] != ConfigData::INVALID_HANDLE);
	m_handles[LASER_HANDLE] = m_config->getItemHandle("LASER");
	assert(m_handles[LASER_HANDLE] != ConfigData::INVALID_HANDLE);

#ifdef _3D
	m_handles[GAMEOVER_EXPLOSION_HANDLE] = m_config->getItemHandle("GAMEOVER_EXPLOSION");
	assert(m_handles[GAMEOVER_EXPLOSION_HANDLE] != ConfigData::INVALID_HANDLE);
	m_handles[GAMEOVER_EXPLOSION1_HANDLE] = m_config->getItemHandle("GAMEOVER_EXPLOSION1");
	assert(m_handles[GAMEOVER_EXPLOSION1_HANDLE] != ConfigData::INVALID_HANDLE);
	m_handles[FIRE_JET_HANDLE] = m_config->getItemHandle("FIRE_JET");
	assert(m_handles[FIRE_JET_HANDLE] != ConfigData::INVALID_HANDLE);
#endif


	
	//m_pSceneHack=m_sceneLoader.load(*m_config->getItem(m_handles[SCENE_HANDLE]));

	ConfigData::ItemHandle handle;
	
	#ifdef _3D
		if( (handle = m_config->getItemHandle("MATERIALS_GFX")) != ConfigData::INVALID_HANDLE ){
			MaterialsLoader matLoader;
			matLoader.load(*m_config->getItem(handle));
			assert(handle != ConfigData::INVALID_HANDLE);
		}
		//make a get for the random generator, for not initializing it during the game
		RandomHashTable::get()->randomf();
		Symbols::get()->init();
	#endif


	// GfxObjects for the guardian ships
	if( (handle = m_config->getItemHandle("GUARDIAN1_GFX")) != ConfigData::INVALID_HANDLE )
		m_gfx[GUARDIAN1_GFX] = m_gfxObjLoader.load(*m_config->getItem(handle));
	assert(handle != ConfigData::INVALID_HANDLE);

	if( (handle = m_config->getItemHandle("GUARDIAN2_GFX")) != ConfigData::INVALID_HANDLE )
		m_gfx[GUARDIAN2_GFX] = m_gfxObjLoader.load(*m_config->getItem(handle));
	assert(handle != ConfigData::INVALID_HANDLE);

	// GfxObjects for the guardians bullets
	if( (handle = m_config->getItemHandle("GUARDIAN_BULLET_GFX")) != ConfigData::INVALID_HANDLE )
		m_gfx[GUARDIAN_BULLET_GFX] = m_gfxObjLoader.load(*m_config->getItem(handle));
	assert(handle != ConfigData::INVALID_HANDLE);

	// GfxObjects for the cargo
	if( (handle = m_config->getItemHandle("CARGO_GFX")) != ConfigData::INVALID_HANDLE )
		m_gfx[CARGO_GFX] = m_gfxObjLoader.load(*m_config->getItem(handle));
	assert(handle != ConfigData::INVALID_HANDLE);

	if( (handle = m_config->getItemHandle("CARGO_HOOK_GFX")) != ConfigData::INVALID_HANDLE )
		m_gfx[CARGO_HOOK_GFX] = m_gfxObjLoader.load(*m_config->getItem(handle));
	assert(handle != ConfigData::INVALID_HANDLE);

	
	// Sounds for the guardian ships
	if( (handle = m_config->getItemHandle("GUARDIAN_SHOOT_SFX")) != ConfigData::INVALID_HANDLE )
		m_sounds[GUARDIAN_SHOOT_SFX] = m_soundLoader.load(*m_config->getItem(handle));
	assert(handle != ConfigData::INVALID_HANDLE);

	if( (handle = m_config->getItemHandle("THIEF_SHOOT_SFX")) != ConfigData::INVALID_HANDLE )
		m_sounds[THIEF_SHOOT_SFX] = m_soundLoader.load(*m_config->getItem(handle));
	assert(handle != ConfigData::INVALID_HANDLE);

	if( (handle = m_config->getItemHandle("EXPLODE_SFX")) != ConfigData::INVALID_HANDLE )
		m_sounds[EXPLOSION_SFX] = m_soundLoader.load(*m_config->getItem(handle));
	assert(handle != ConfigData::INVALID_HANDLE);

	if( (handle = m_config->getItemHandle("THIEF_HOOK_SFX")) != ConfigData::INVALID_HANDLE )
		m_sounds[THIEF_HOOK_SFX] = m_soundLoader.load(*m_config->getItem(handle));
	assert(handle != ConfigData::INVALID_HANDLE);

	if( (handle = m_config->getItemHandle("KEY_SFX")) != ConfigData::INVALID_HANDLE )
	{
		m_sounds[KEY_SFX] = m_soundLoader.load(*m_config->getItem(handle));
		GameEngine::get()->setKeyButtonSound(m_sounds[KEY_SFX]);
	}
	if( (handle = m_config->getItemHandle("SELECT_SFX")) != ConfigData::INVALID_HANDLE )
	{
		m_sounds[SELECT_SFX] = m_soundLoader.load(*m_config->getItem(handle));
		GameEngine::get()->setSelectButtonSound(m_sounds[SELECT_SFX]);
	}

	// Load the music phase
	if( (handle = m_config->getItemHandle("PHASE1_MUSIC")) != ConfigData::INVALID_HANDLE )
	{
		m_sounds[PHASE1_MUSIC] = m_soundLoader.load(*m_config->getItem(handle));
		GameEngine::get()->setPhaseMusic(0, m_sounds[PHASE1_MUSIC]);
	}
	assert(handle != ConfigData::INVALID_HANDLE);
	if( (handle = m_config->getItemHandle("PHASE2_MUSIC")) != ConfigData::INVALID_HANDLE )
	{
		m_sounds[PHASE2_MUSIC] = m_soundLoader.load(*m_config->getItem(handle));
		GameEngine::get()->setPhaseMusic(1, m_sounds[PHASE2_MUSIC]);
	}
	assert(handle != ConfigData::INVALID_HANDLE);
	if( (handle = m_config->getItemHandle("PHASE3_MUSIC")) != ConfigData::INVALID_HANDLE )
	{
		m_sounds[PHASE3_MUSIC] = m_soundLoader.load(*m_config->getItem(handle));
		GameEngine::get()->setPhaseMusic(2, m_sounds[PHASE3_MUSIC]);
	}
	assert(handle != ConfigData::INVALID_HANDLE);
	if( (handle = m_config->getItemHandle("PHASE4_MUSIC")) != ConfigData::INVALID_HANDLE )
	{
		m_sounds[PHASE4_MUSIC] = m_soundLoader.load(*m_config->getItem(handle));
		GameEngine::get()->setPhaseMusic(3, m_sounds[PHASE4_MUSIC]);
	}
	assert(handle != ConfigData::INVALID_HANDLE);
	if( (handle = m_config->getItemHandle("PHASE5_MUSIC")) != ConfigData::INVALID_HANDLE )
	{
		m_sounds[PHASE5_MUSIC] = m_soundLoader.load(*m_config->getItem(handle));
		GameEngine::get()->setPhaseMusic(4, m_sounds[PHASE5_MUSIC]);
	}
	assert(handle != ConfigData::INVALID_HANDLE);
	if( (handle = m_config->getItemHandle("PHASE6_MUSIC")) != ConfigData::INVALID_HANDLE )
	{
		m_sounds[PHASE6_MUSIC] = m_soundLoader.load(*m_config->getItem(handle));
		GameEngine::get()->setPhaseMusic(5, m_sounds[PHASE6_MUSIC]);
	}
	assert(handle != ConfigData::INVALID_HANDLE);

	// Load the background music
	if( (handle = m_config->getItemHandle("BACKGROUND_MUSIC")) != ConfigData::INVALID_HANDLE )
	{
		m_sounds[BACKGROUND_MUSIC] = m_soundLoader.load(*m_config->getItem(handle));
		GameEngine::get()->setBackgroundMusic(m_sounds[BACKGROUND_MUSIC]);
	}

	// Load the menu sound
	if( (handle = m_config->getItemHandle("MENU_MUSIC")) != ConfigData::INVALID_HANDLE )
	{
		m_sounds[MENU_MUSIC] = m_soundLoader.load(*m_config->getItem(handle));
		GameEngine::get()->setMenuMusic(m_sounds[MENU_MUSIC]);
	}
	

	// GfxObjects for the enemy ships
	if( (handle = m_config->getItemHandle("THIEF1_GFX")) != ConfigData::INVALID_HANDLE )
		m_gfx[THIEF1_GFX] = m_gfxObjLoader.load(*m_config->getItem(handle));
	assert(handle != ConfigData::INVALID_HANDLE);

	if( (handle = m_config->getItemHandle("THIEF2_GFX")) != ConfigData::INVALID_HANDLE )
		m_gfx[THIEF2_GFX] = m_gfxObjLoader.load(*m_config->getItem(handle));
	assert(handle != ConfigData::INVALID_HANDLE);

	if( (handle = m_config->getItemHandle("THIEF3_GFX")) != ConfigData::INVALID_HANDLE )
		m_gfx[THIEF3_GFX] = m_gfxObjLoader.load(*m_config->getItem(handle));
	assert(handle != ConfigData::INVALID_HANDLE);

	if( (handle = m_config->getItemHandle("THIEF4_GFX")) != ConfigData::INVALID_HANDLE )
		m_gfx[THIEF4_GFX] = m_gfxObjLoader.load(*m_config->getItem(handle));
	assert(handle != ConfigData::INVALID_HANDLE);

	if( (handle = m_config->getItemHandle("THIEF5_GFX")) != ConfigData::INVALID_HANDLE )
		m_gfx[THIEF5_GFX] = m_gfxObjLoader.load(*m_config->getItem(handle));
	assert(handle != ConfigData::INVALID_HANDLE);

	if( (handle = m_config->getItemHandle("THIEF6_GFX")) != ConfigData::INVALID_HANDLE )
		m_gfx[THIEF6_GFX] = m_gfxObjLoader.load(*m_config->getItem(handle));
	assert(handle != ConfigData::INVALID_HANDLE);

	// Set the game parameters
	if( (handle = m_config->getItemHandle("GAME")) != ConfigData::INVALID_HANDLE )
	{
		const ConfigItem* item = m_config->getItem(handle);

		if(item->hasFloat("shipSpeedIncrement"))
			GameEngine::get()->setShipSpeedIncrement(item->getFloat("shipSpeedIncrement"));
		if(item->hasFloat("spawnPointOffset"))
			GameEngine::get()->setSpawnPointOffset(item->getFloat("spawnPointOffset"));
		if(item->hasFloat("distanceFromSpawnPoint"))
			GameEngine::get()->setDistanceFromSpawnPoint(item->getFloat("distanceFromSpawnPoint"));
	}
	assert(handle != ConfigData::INVALID_HANDLE);
	
	return true;
}

//--------------------------------------------------------------------------------
GuardianShip*
GameLoader::createGuardianShip(unsigned int index)
{
	// Create ship
	GuardianShip *guardianShip = new GuardianShip();
	
	// Check handle and get config item
	if(m_handles[GUARDIAN1_HANDLE + index] != ConfigData::INVALID_HANDLE)
	{
		const ConfigItem* item = m_config->getItem(m_handles[GUARDIAN1_HANDLE + index]);

		// Create and setup ship
		if(item->hasFloat("mass"))
		{
			guardianShip->setMass(item->getFloat("mass"));
		}
		if(item->hasFloat("radius"))
		{
			guardianShip->setRadius(item->getFloat("radius"));
		}
		if(item->hasFloat("maxSpeed"))
		{
			guardianShip->setMaxSpeed(item->getFloat("maxSpeed"));
		}
		if(item->hasFloat("throttle"))
		{
			guardianShip->setThrottle(item->getFloat("throttle"));
		}
		if(item->hasFloat("steering"))
		{
			guardianShip->setSteering(item->getFloat("steering"));
		}
		if(item->hasFloat("drag"))
		{
			guardianShip->setDrag(item->getFloat("drag"));
		}
		if(item->hasFloat("drag"))
		{
			guardianShip->setDrag(item->getFloat("drag"));
		}
		if(item->hasFloat("respawnTime"))
		{
			guardianShip->setRespawnTime(item->getFloat("respawnTime"));
		}
		if(item->hasVector("respawnPoint"))
		{
			Vector3f p = item->getVector("respawnPoint");
			guardianShip->setRespawnPoint(Vector2f(p[0] * GameEngine::get()->getAspectRatio(), p[1]));
		}
		if(item->hasFloat("respawnRotation"))
		{
			guardianShip->setRespawnRotation(item->getFloat("respawnRotation"));
		}
	}

	// Ship graphics
	guardianShip->setGFXObject(m_gfx[GUARDIAN1_GFX + index]);

	// Ship sounds
	guardianShip->setShootingSound(m_sounds[GUARDIAN_SHOOT_SFX]);
	guardianShip->setExplosionSound(m_sounds[EXPLOSION_SFX]);

	return guardianShip;
}

//--------------------------------------------------------------------------------
ThiefShip*
GameLoader::createThiefShip(unsigned int index)
{
	// Create ship
	ThiefShip* thiefShip = new ThiefShip();
	
	// Check handle and get config item
	if(m_handles[THIEF1_HANDLE + index] != ConfigData::INVALID_HANDLE)
	{
		const ConfigItem* item = m_config->getItem(m_handles[THIEF1_HANDLE + index]);

		// Create and setup ship
		if(item->hasFloat("mass"))
		{
			thiefShip->setMass(item->getFloat("mass"));
		}
		if(item->hasFloat("radius"))
		{
			thiefShip->setRadius(item->getFloat("radius"));
		}
		if(item->hasFloat("maxSpeed"))
		{
			thiefShip->setMaxSpeed(item->getFloat("maxSpeed"));
		}
		if(item->hasFloat("throttle"))
		{
			thiefShip->setThrottle(item->getFloat("throttle"));
		}
		if(item->hasFloat("steering"))
		{
			thiefShip->setSteering(item->getFloat("steering"));
		}
		if(item->hasFloat("drag"))
		{
			thiefShip->setDrag(item->getFloat("drag"));
		}
		if(item->hasFloat("cargoCarryDistance"))
		{
			thiefShip->setCargoCarryDistance(item->getFloat("cargoCarryDistance"));
		}
		if(item->hasFloat("laserLength"))
		{
			thiefShip->setLaserLength(item->getFloat("laserLength"));
		}
	}

	// Ship graphics
	thiefShip->setGFXObject(m_gfx[THIEF1_GFX + index]);
	thiefShip->setCargoHookGfx(m_gfx[CARGO_HOOK_GFX]);

	// Ship sounds
	thiefShip->setShootingSound(m_sounds[THIEF_SHOOT_SFX]);
	thiefShip->setExplosionSound(m_sounds[EXPLOSION_SFX]);
	thiefShip->setHookCargoSound(m_sounds[THIEF_HOOK_SFX]);

	return thiefShip;
}

//--------------------------------------------------------------------------------
Cargo *
GameLoader::createCargo()
{
	Cargo *cargo = new Cargo();

	// Nothing to load for the cargo from the config

	cargo->setGFXObject(m_gfx[CARGO_GFX]);

	return cargo;
}

//--------------------------------------------------------------------------------
Bullet *
GameLoader::createBullet()
{
	Bullet *bullet = new Bullet();
	
	// Setup the bullet
	bullet->setDrag(0.0f);

	// Check handle and get config item
	if(m_handles[GUARDIAN_BULLET_HANDLE] != ConfigData::INVALID_HANDLE)
	{
		const ConfigItem* item = m_config->getItem(m_handles[GUARDIAN_BULLET_HANDLE]);

		// Create and setup ship
		if(item->hasFloat("speed"))
		{
			bullet->setMaxSpeed(item->getFloat("speed"));
		}
		if(item->hasFloat("radius"))
		{
			bullet->setRadius(item->getFloat("radius"));
		}
	}

	// Ship graphics
	bullet->setGFXObject(m_gfx[GUARDIAN_BULLET_GFX]);

	return bullet;
}

//--------------------------------------------------------------------------------
Scene*
GameLoader::createScene()
{
	return m_sceneLoader.load(*m_config->getItem(m_handles[SCENE_HANDLE]));
	//return m_pSceneHack;
}

//--------------------------------------------------------------------------------
EffectIF*
GameLoader::createThiefExplosion1()
{
	return m_effectLoader.load(*m_config->getItem(m_handles[THIEF_EXPLOSION1_HANDLE]));
}

//--------------------------------------------------------------------------------
EffectIF*
GameLoader::createThiefExplosion2()
{
	return m_effectLoader.load(*m_config->getItem(m_handles[THIEF_EXPLOSION2_HANDLE]));
}

//--------------------------------------------------------------------------------
EffectIF*
GameLoader::createGuardianExplosion1()
{
	return m_effectLoader.load(*m_config->getItem(m_handles[GUARDIAN_EXPLOSION1_HANDLE]));
}

//--------------------------------------------------------------------------------
EffectIF*
GameLoader::createGuardianExplosion2()
{
	return m_effectLoader.load(*m_config->getItem(m_handles[GUARDIAN_EXPLOSION2_HANDLE]));
}

//--------------------------------------------------------------------------------
EffectIF*
GameLoader::createLaser()
{
	return m_effectLoader.load(*m_config->getItem(m_handles[LASER_HANDLE]));
}

//--------------------------------------------------------------------------------
EffectIF*
GameLoader::createGameoverExplosion()
{
	return m_effectLoader.load(*m_config->getItem(m_handles[GAMEOVER_EXPLOSION_HANDLE]));
}

//--------------------------------------------------------------------------------
EffectIF*
GameLoader::createGameoverExplosion1()
{
	return m_effectLoader.load(*m_config->getItem(m_handles[GAMEOVER_EXPLOSION1_HANDLE]));
}

//--------------------------------------------------------------------------------

EffectIF*
GameLoader::createFireJet()
{
	return m_effectLoader.load(*m_config->getItem(m_handles[FIRE_JET_HANDLE]));
}

//--------------------------------------------------------------------------------
