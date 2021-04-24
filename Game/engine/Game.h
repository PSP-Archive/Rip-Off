/* VERSION HISTORY

13/04/2010 - Wendy - added menu sound objects and functions
*/

#pragma once

#include "foundation/singleton.h"
#include "foundation/Vector2f.h"
#include "engine/controllerif.h"
#include "engine/physicsworld.h"
#include "engine/gameentity.h"
#include "engine/ship.h"
#include "engine/cargo.h"
#include "engine/gameloader.h"
#include "graphics/Scene.h"
#include "foundation/Timer.h"

#include <list>
#include <set>

// Effects DEBUG
#include "vectorgraphics/VectorLineExplosionEffect.h"
#include "vectorgraphics/VectorTriangleExplosionEffect.h"

// For networking
#ifdef _SPSP
#include "Network/NetworkMessage.h"
#include "network/PSPNetwork.h"
#endif

//--------------------------------------------------------------------------------
class Game
{
public:
	// List types
	typedef std::list<Cargo*> CargoList;
	typedef std::list<Ship*> ShipList;

	// Entity types
	enum
	{
		NONE = 0,

		BULLET,
		GUARDIAN,
		THIEF,
		CARGO,

		NUM_ENTITYTYPES,
		SPAWN_BULLET
	};
	
	// Ctor
	Game();

	// initializes the game
	void init(const ConfigData* confData);

	// Starts a game
	void start();

	// Updates the game
	void update();

	//update for gameover state
	void postUpdate();

	// Renders the game
	void render();

	// Returns weather the game is over
	bool isOver() { return m_isOver; }

	// Returns the score
	int getScore() { return m_score; }
	void addScore(int score) { m_score += score; }
	// Returns the high score
	void setHighScore(int score) { m_highScore = score; }
	int getHighScore() { return m_highScore; }
	void updateHighScore() { m_highScore = m_score; }

	// Returns the current round
	unsigned int getRound() { return m_round + 1; }

	// Ends the game
	void end();

	// Creates a bullet for a ship
	Bullet* spawnBullet();
	
	// Spawns an enemy ship
	Ship* spawnEnemy(unsigned int type);

	// Sets the game's aspect ratio
	void setAspectRatio(float ar);

	// returns the game's aspect ratio
	float getAspectRatio() { return m_aspectRatio; }

	// Returns a reference to the list of cargos
	CargoList& getCargoList() { return m_cargo; }
	
	// Returns a reference to the list of guardian ships
	ShipList& getPlayerList() { return m_guardianShips; }

	// Returns a reference to the list of thief ships
	ShipList& getThiefList() { return m_thiefShips; }

	// Returns a reference to the background music
	Sound* getBackgroundMusic() { return m_backgroundMusic; }

	// Returns a reference to the button sound
	Sound* getMenuMusic() { return m_menuMusic; }
	Sound* getKeyButtonSound() { return m_keyButtonSound; }
	Sound* getSelectButtonSound() { return m_selectButtonSound; }

	// Registers an entity for destruction
	void registerDestruction(GameEntity* e) { if(m_toDestroy.find(e) == m_toDestroy.end())  m_toDestroy.insert(e); } 

	// Starts a phase
	void spawnPhase();

	// Physics groups ids
	static const int PHYS_GUARDIAN_SHIPS = 0;
	static const int PHYS_THIEF_SHIPS = 1;
	static const int PHYS_CARGOS = 2;
	static const int PHYS_BULLETS = 3;

	// DIFFICULTY
	enum Difficulty
	{
		EASY = 0,
		NORMAL
	};

	// Set music to play for a phase
	void setPhaseMusic(unsigned int phase, Sound* s) { m_phaseMusic[phase] = s; }

	// Set music to play in the background
	void setBackgroundMusic(Sound* s) { m_backgroundMusic = s; }

	// Set sound to play for the button control
	void setMenuMusic(Sound* s) { m_menuMusic = s; }
	void setKeyButtonSound(Sound* s) { m_keyButtonSound = s; }
	void setSelectButtonSound(Sound* s) { m_selectButtonSound = s; }

	// Set the difficulty
	void setDifficulty(Difficulty d) { m_difficulty = d; }

	// Set the difficulty
	void setPlayers(unsigned int p) { m_players = p; }
	unsigned int getPlayers() { return m_players; }

	// Set the game params
	void setShipSpeedIncrement(float i) { m_shipSpeedIncrement = i; }
	void setSpawnPointOffset(float i) { m_spawnPointOffset = i; }
	void setDistanceFromSpawnPoint(float i) { m_distanceFromSpawnPoint = i; }

	// Create effects
	void spawnThiefExplosion1(const Vector2f& pos, float rot, const Vector2f& velocity);
	void spawnThiefExplosion2(const Vector2f& pos, float rot, const Vector2f& velocity);
	void spawnGuardianExplosion1(const Vector2f& pos, float rot, const Vector2f& velocity);
	void spawnGuardianExplosion2(const Vector2f& pos, float rot, const Vector2f& velocity);
	void spawnLaser(const Vector2f& pos, float rot);
	void spawnGameoverExplosion(const Vector2f& pos, float rot);
	void spawnGameoverExplosion1(const Vector2f& pos, float rot);
	void spawnFireJet(const Vector2f& pos, float rot, const Vector2f& velocity, const RigidBody* pBody);

	
#ifdef _SPSP
	int packMessage(void* buffer);
	void updateNetworkData(void *buffer, int bufferSize);
#endif

private:
	// How many phases per round.
	static const unsigned int PHASES_PER_ROUND = 6;
	
	// Loader for loading in game objects such as ship, cargo and bullet.
	GameLoader data;

	// The graphics Scene
	Scene* m_pScene;

	// Physics world
	PhysicsWorld m_physics;

	// Game settings
	Difficulty m_difficulty;
	int m_players;
	
	// Instance dependant settings
	int m_score;
	int m_highScore;
	Timer m_timer;
	bool m_isOver;
	unsigned int m_round;
	unsigned int m_phase;
	bool m_isFirstPhase;
	
	// Increment of the ship's speed
	float m_shipSpeedIncrement;

	// How far off the screen the spawn point is.
	float m_spawnPointOffset;
	
	// How far the ships are distributed from the spawning point.
	float m_distanceFromSpawnPoint;
	
	// List of game objects
	std::list<GameEntity*> m_entities;
	typedef std::list<GameEntity*>::iterator EntityIt;
	std::list<ControllerIF*> m_controllers;
	typedef std::list<ControllerIF*>::iterator ControllerIt;
	CargoList m_cargo;
	ShipList m_guardianShips;
	ShipList m_thiefShips;

	// The aspect ratio of the game area
	float m_aspectRatio;

	// Entities to be destroyed
	std::set<GameEntity*> m_toDestroy;

	// Music
	Sound* m_phaseMusic[PHASES_PER_ROUND];
	Sound* m_backgroundMusic;
	Sound* m_menuMusic;
	Sound* m_keyButtonSound;
	Sound* m_selectButtonSound;

	// Round spawn
	Timer m_phaseSpawnTimer;
	bool m_isSpawning;
	float m_phaseSpawnTime;

	// Effects
	std::list<EffectIF*> m_effects;
	typedef std::list<EffectIF*>::iterator EffectIt;
};

typedef Singleton<Game> GameEngine;
