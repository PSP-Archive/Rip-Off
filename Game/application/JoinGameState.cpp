#include "application/JoinGameState.h"
#include "application/RipOffApplication.h"
#include "input/InputManager.h"
#include "foundation/Vector2f.h"
#include "network/PSPNetwork.h"

#define DISCOVER_TIMEOUT	(60)	/* 60sec */


#ifdef _SPSP
#include <libgu.h>
#include <libgum.h>

#include <pspnet_adhoc_discover.h>
#endif

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
JoinGameState::JoinGameState(Application& app) :
AppState(app)
{
	Vector2f uiPosition = Vector2f(-0.4f,0.7f);
	Vector3f uiColor = Vector3f(1.0f,0.5f,0.0f);
	Vector3f uiSelectedColor = Vector3f(1.0f,1.0f,0.5f);

	m_uiScene.addWidget(uiPosition,"joining game...",0,3.0f,uiColor);

	float scale = 4.0f;

	//menu items
	uiPosition = Vector2f(-0.3f,0.4f);
	m_uiScene.addMenuWidget(uiPosition,"return",scale,uiColor,uiColor);

	uiPosition = Vector2f(-0.4f,0.4f);
	m_uiScene.addWidget(uiPosition,"o",1,scale,uiColor);
	uiPosition[1] -= 0.2f;

	uiPosition = Vector2f(-0.2f,0.2f);
	m_uiScene.addWidget(uiPosition,PSPNetwork::get()->getLastMessage(),0, scale,uiColor);

#ifdef _VECTOR
	//shading for selected menu item only wanted on vector version
	uiPosition = Vector2f(-0.3f,0.4025f);
	m_uiScene.addWidget(uiPosition,"return",1,scale,uiSelectedColor);
#endif
}

//--------------------------------------------------------------------------------
void
JoinGameState::onEnter()
{
	
	PSPNetwork::get()->net_update();


	// play menu background music
	//GameEngine::get()->getMenuMusic()->play();
}
//--------------------------------------------------------------------------------
void JoinGameState::onUpdate()
{
	PSPNetwork::get()->net_update();

	m_uiScene.setText(3,PSPNetwork::get()->getLastMessage());

	if (PSPNetwork::get()->isConnectCompleted())
		static_cast<RipOffApplication&>(getApp()).networkGameState();
	/*
	int status;
	status = sceNetAdhocDiscoverGetStatus();
	if (status == SCE_NET_ADHOC_DISCOVER_STATUS_RUNNING) {
		sceNetAdhocDiscoverUpdate();
	}
	else if (status == SCE_NET_ADHOC_DISCOVER_STATUS_FINISHED) {
		// Processing for end-of-operation state (see next step)
		// Library termination processing (see step after next step)
		sceNetAdhocDiscoverTerm();

		switch(param.result)
		{
		case SCE_NET_ADHOC_DISCOVER_RESULT_OK:
			printf("Host discovered\n");
			break;
		}
	}*/

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
		static_cast<RipOffApplication&>(getApp()).lobbyState();
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
			case 0: // 1 player game
				//GameEngine::get()->setPlayers(1);
				static_cast<RipOffApplication&>(getApp()).lobbyState();
				break;
		}
		
	
	}

}

//--------------------------------------------------------------------------------
void
JoinGameState::onLeave()
{
	// stop music when leaving menu			
	GameEngine::get()->getMenuMusic()->stop();
}

