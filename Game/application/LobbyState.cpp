#include "application/LobbyState.h"
#include "application/RipOffApplication.h"
#include "input/InputManager.h"
#include "foundation/Vector2f.h"



#ifdef _SPSP
#include <libgu.h>
#include <libgum.h>
#endif

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
LobbyState::LobbyState(Application& app) :
AppState(app)
{
	Vector2f uiPosition = Vector2f(-0.17f,0.7f);
	Vector3f uiColor = Vector3f(1.0f,0.5f,0.0f);
	Vector3f uiSelectedColor = Vector3f(1.0f,1.0f,0.5f);

	m_uiScene.addWidget(uiPosition,"multiplayer",0,3.0f,uiColor);

	float scale = 4.0f;

	//menu items
	uiPosition = Vector2f(-0.2f,0.4f);
	m_uiScene.addMenuWidget(uiPosition,"host game",scale,uiColor,uiColor);
	uiPosition[1] -= 0.2f;
	m_uiScene.addMenuWidget(uiPosition,"join game",scale,uiColor,uiColor);
	uiPosition[1] -= 0.2f;
	m_uiScene.addMenuWidget(uiPosition,"return",scale,uiColor ,uiColor);
	//uiPosition[1] -= 0.2f;
	//m_uiScene.addMenuWidget(uiPosition,"quit",	 scale,uiColor ,uiColor);

	uiPosition = Vector2f(-0.3f,0.4f);
	m_uiScene.addWidget(uiPosition,"o",1,scale,uiColor);
	uiPosition[1] -= 0.2f;
	m_uiScene.addWidget(uiPosition,"o",2,scale,uiColor);
	uiPosition[1] -= 0.2f;
	m_uiScene.addWidget(uiPosition,"o",3,scale,uiColor);
	//uiPosition[1] -= 0.2f;
	//m_uiScene.addWidget(uiPosition,"o",4,scale,uiColor);

#ifdef _VECTOR
	//shading for selected menu item only wanted on vector version
	uiPosition = Vector2f(-0.1975f,0.4025f);
	m_uiScene.addWidget(uiPosition,"host game",1,scale,uiSelectedColor);
	uiPosition[1] -= 0.2f;
	m_uiScene.addWidget(uiPosition,"join game",2,scale,uiSelectedColor);
	uiPosition[1] -= 0.2f;
	m_uiScene.addWidget(uiPosition,"return",3,scale,uiSelectedColor);
	//uiPosition[1] -= 0.2f;
	//m_uiScene.addWidget(uiPosition,"quit",4, scale,uiSelectedColor);
#endif
}

//--------------------------------------------------------------------------------
void
LobbyState::onEnter()
{
	//testing
	//m_uiScene.addWidget(Vector2f(-0.9f,0.9f),"abcdefghijklmnopqrstuvwxyz 0123456789",0);
	//m_uiScene.addWidget(Vector2f(-0.9f,0.8f),"ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789",0);

	// play menu background music
	//GameEngine::get()->getMenuMusic()->play();
}
//--------------------------------------------------------------------------------
void LobbyState::onUpdate()
{
#ifndef _SPSP
	glClear(GL_COLOR_BUFFER_BIT);
#else
	sceGuClear(SCEGU_CLEAR_ALL);
#endif

	m_uiScene.render();


	if(InputManager::get()->isButtonJustPressed(0, InputDevice::UP))
	{
		m_uiScene.previous();
		// play menu button sound
		GameEngine::get()->getKeyButtonSound()->stop();
		GameEngine::get()->getKeyButtonSound()->play();
	}

	if(InputManager::get()->isButtonJustPressed(0, InputDevice::DOWN))
	{
		m_uiScene.next();
		// play menu button sound
		GameEngine::get()->getKeyButtonSound()->stop();
		GameEngine::get()->getKeyButtonSound()->play();
	}

	// Hot keys...
	if(InputManager::get()->isButtonJustPressed(0, InputDevice::BUTTON4))
	{
		static_cast<RipOffApplication&>(getApp()).mainMenuState();
	}
	//------------

	if(InputManager::get()->isButtonJustPressed(0, InputDevice::START) || 
		InputManager::get()->isButtonJustPressed(0, InputDevice::BUTTON3))
	{
		// play menu button selection sound
		GameEngine::get()->getSelectButtonSound()->stop();
		GameEngine::get()->getSelectButtonSound()->play();

		switch(m_uiScene.getSelectedMenuItem())
		{
			//case 0: // 1 player game
			//	//GameEngine::get()->setPlayers(1);
			//	static_cast<RipOffApplication&>(getApp()).gameState();
			//	break;
			case 0: // 2 player game
				//GameEngine::get()->setPlayers(2);
				static_cast<RipOffApplication&>(getApp()).hostGameState();
				break;
			case 1: // highScore (not implemented)
				static_cast<RipOffApplication&>(getApp()).joinGameState();
				break;
			case 2://quit
				static_cast<RipOffApplication&>(getApp()).mainMenuState();
				break;
		}
		
	
	}

}

//--------------------------------------------------------------------------------
void
LobbyState::onLeave()
{
	// stop music when leaving menu			
	GameEngine::get()->getMenuMusic()->stop();
}

