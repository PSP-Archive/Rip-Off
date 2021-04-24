#pragma once
#include "engine/AI_ImplementationIF.h"
#include "engine/ControllerIF.h"
#include "engine/Ship.h"

class AIController : public ControllerIF {
public:
	AIController();
	~AIController();
	void Update(float frameTime);

	// set current AI implementation
	// The controller will call delete on it when deleted itself
	void SetImpl(AI_ImplementationIF* impl);

	// currently without function, included for the coming AI ACW
	// Might be good to call this for the different agent types, just in case
	void setAgentType(int AIType);

	void Init();
	void Cleanup();

private:
	AI_ImplementationIF* mp_impl;
	int					 m_AIType;
};