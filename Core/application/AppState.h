#pragma once

class Application;

//--------------------------------------------------------------------------------
/**
	Interface for an application state. Implement as necessary.
*/
class AppState
{
public:
	// Ctor - requires a reference to the app creating it.
	AppState(Application& app);

	// Dtor
	virtual ~AppState();

	// Called when the state is entered
	virtual void onEnter() = 0;

	// Called when the state is to be updated
	virtual void onUpdate() = 0;

	// Called when the state is left
	virtual void onLeave() = 0;

	// Returns a reference to the application
	Application& getApp() { return m_app; }



private:
	// Prevent copying and assigning
	AppState& operator=(const AppState&);
	AppState(const AppState&);
	
	Application& m_app;
};
