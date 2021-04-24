#include <algorithm>
#include <cassert>

#include "application/Application.h"
#include "input/InputManager.h"
#include "sound/SoundManager.h"
#include "foundation/ConfigDataLoader.h"
#include "foundation/ConfigItem.h"
#include "foundation/GlobalTimer.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

const std::string Application::CFG_OS("OS");
const std::string Application::CFG_INPUT("INPUT");

//--------------------------------------------------------------------------------
Application::Application(OS& os) :
	m_currentState(NULL),
	m_quitRequest(false),
	m_nextState(INVALID_HANDLE),
	m_os(os),
	m_isOpen(false)
{

	Debug::get()->ActivateMemoryLeakCheck();

}

//--------------------------------------------------------------------------------
Application::~Application()
{
	// Delete all states
	std::for_each(m_states.begin(), m_states.end(), DeleteState());
}

//--------------------------------------------------------------------------------
bool
Application::loadConfig(const std::string& file)
{
	// Load the configuration file (do thing now as some managers need it)
	ConfigDataLoader loader;
	if(!loader.load(file, m_config))
	{
		assert(!"Error reading the config file");
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------
bool
Application::init()
{
	const ConfigItem* conf;
	ConfigData::ItemHandle h;

	// Init the OS
	conf = NULL;
	if((h = m_config.getItemHandle(CFG_OS)) != ConfigData::INVALID_HANDLE)
	{
		conf = m_config.getItem(h);
	}
	if(!m_os.init(conf))
	{
		assert(!"Failed to init the OS");
		return false;
	}

	// Init the input manager
	conf = NULL;
	if((h = m_config.getItemHandle(CFG_INPUT)) != ConfigData::INVALID_HANDLE)
	{
		conf = m_config.getItem(h);
	}
	if(!InputManager::get()->init(conf))
	{
		assert(!"Failed to init the Input Manager");
		cleanUp();
		return false;
	}
	
	// Init the sound manager
	if(!SoundManager::get()->init())
	{
		assert(!"Failed to init the Sound Manager");
		cleanUp();
		return false; 
	}

	m_isOpen = true;

	onInit();
	return true;
}

//--------------------------------------------------------------------------------
void
Application::run()
{
	if(!m_isOpen)
	{
		return;
	}
	
	// Main application loop
	while(!m_quitRequest && !m_os.quitRequested())
	{
		// Pre update os
		m_os.preUpdate();
		
		// Update servers
		InputManager::get()->update();
		
		// Change state
		if(m_nextState != INVALID_HANDLE)
		{
			// End previous state
			if(m_currentState != NULL)
			{
				m_currentState->onLeave();
			}

			// Start new state
			m_currentState = m_states.at(m_nextState);
			m_currentState->onEnter();

			m_nextState = INVALID_HANDLE;
		}
		
		m_currentState->onUpdate();

		// Pre update os
		m_os.postUpdate();
	}

	// If a state is active, call its onLeave
	if(m_currentState)
	{
		m_currentState->onLeave();
	}

	cleanUp();
}

//--------------------------------------------------------------------------------
void
Application::cleanUp()
{
	//onCleanUp();

	//// Close the sound manager
	SoundManager::get()->cleanUp();
	//
	// Close the input manager
	InputManager::get()->cleanUp();
	
	// Tell the OS to close
	m_os.cleanUp();

	//// Release singletons
	SoundManager::release();
	InputManager::release();
	GlobalTimer::release();

	Debug::release();
}

//--------------------------------------------------------------------------------
void
Application::setState(StateHandle sh)
{
	if(sh >= 0 && sh < static_cast<int>(m_states.size()))
	{
		m_nextState = sh;
	}
}

//--------------------------------------------------------------------------------
Application::StateHandle
Application::addState(AppState* state)
{
	assert(state);
	m_states.push_back(state);
	return m_states.size() - 1;
}
