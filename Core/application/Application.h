#pragma once

#include <vector>
#include <cassert>
#include <functional>

#include "../application/OS.h"
#include "../application/AppState.h"
#include "../foundation/ConfigData.h"

//--------------------------------------------------------------------------------
/**
	Main program class that manages the different states of the program. Clients
	should extend this class and implement the onOpen method so that it creates
	the required states and sets the initial one.
*/
class Application
{
public:
	// Handle to the created states
	typedef int StateHandle;
	static const StateHandle INVALID_HANDLE = -1;
	
	// Ctor
	Application(OS& os);

	// Dtor
	virtual ~Application();

	// Initializes the application
	bool init();

	// Starts the application
	void run();

	// Tells the application to quit
	void quit() { m_quitRequest = true; }

	// Changes the state
	void setState(StateHandle sh);

	// Returns a reference to the ConfigData object
	const ConfigData& getConfig() { return m_config; }

	// Returns a reference to the OS object
	const OS& getOS() { return m_os; }

	// Loads a config file in the apps config object
	bool loadConfig(const std::string& file);

protected:
	// Starts the application
	void cleanUp();

	// Adds a state and returns the handle to that state
	StateHandle addState(AppState* state);

	// Called when the application initializes
	virtual void onInit() = 0;

	// Called when the application is closing
	virtual void onCleanUp() = 0;

private:
	// Functor for deleting all the States
	struct DeleteState : public std::unary_function<const AppState*, void> {
		void operator()(const AppState* state) { delete state; } };

	// Config constants
	static const std::string CFG_OS;
	static const std::string CFG_INPUT;
		
	std::vector<AppState*> m_states;
	AppState* m_currentState;
	bool m_quitRequest;
	StateHandle m_nextState;
	OS& m_os;
	bool m_isOpen;
	ConfigData m_config;
};
