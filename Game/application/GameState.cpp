#include "application/GameState.h"
#include "application/RipOffApplication.h"
#include "input/InputManager.h"
#include "sound/SoundLoader.h"
#include "foundation/ToString.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

#define GAME_STATUS_SIZE 2.0f

//--------------------------------------------------------------------------------
GameState::GameState(Application& app) :
	AppState(app)
{
#ifdef _SPSP
	Vector2f uiPosition = Vector2f(-0.1f,0.7f);
#else
	Vector2f uiPosition = Vector2f(-0.1f,0.9f);
#endif

	Vector3f uiColor1 = Vector3f(1.0f,1.0f,1.0f);
	Vector3f uiColor2 = Vector3f(1.0f,1.0f,0.0f);

	//UISceneLoader.load("uiScene.txt",&m_uiScene);

	m_uiScene.addWidget(uiPosition,"score",0,GAME_STATUS_SIZE,uiColor1);
#ifdef _VECTOR
	uiPosition[0] += 0.3f;
#elif _3D
	uiPosition[0] += 0.3f;
#endif
	m_uiScene.addWidget(uiPosition, "",0,GAME_STATUS_SIZE,uiColor2); //score variable

	uiPosition[0] -= 0.95f;
	m_uiScene.addWidget(uiPosition,"round",0,GAME_STATUS_SIZE,uiColor1);
#ifdef _VECTOR
	uiPosition[0] += 0.3f;
#elif _3D
	uiPosition[0] += 0.3f;
#endif
	m_uiScene.addWidget(uiPosition,"",0,GAME_STATUS_SIZE,uiColor2); //round variable
}

//--------------------------------------------------------------------------------
void
GameState::onEnter()
{
	GameEngine::get()->setPlayers(1);
	GameEngine::get()->start();
}

//--------------------------------------------------------------------------------
void
GameState::onUpdate()
{
	GameEngine::get()->update();
	GameEngine::get()->render();

	std::string strScore = toString(GameEngine::get()->getScore());
	m_uiScene.setText(1,strScore);

	std::string strRound = toString(GameEngine::get()->getRound());
	m_uiScene.setText(3,strRound);

	m_uiScene.render();

#ifdef _SPSP
	if(InputManager::get()->isButtonJustPressed(0, InputDevice::SELECT))
	{
		GameEngine::get()->end();
		static_cast<RipOffApplication&>(getApp()).mainMenuState();
	}
#endif

	// Check input for state change
	if(GameEngine::get()->isOver())
	{
		static_cast<RipOffApplication&>(getApp()).gameOverState();
	}
}

//--------------------------------------------------------------------------------
void
GameState::onLeave()
{
	//GameEngine::get()->end();
}
