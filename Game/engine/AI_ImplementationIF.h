// created by Birgit

#pragma once
#include "../engine/Ship.h"

class AI_ImplementationIF {
public:
	AI_ImplementationIF() {}
	virtual ~AI_ImplementationIF() {}

	virtual void Update(Ship* pShip) = 0;
	virtual void Init() = 0;
	virtual void Cleanup() = 0;
	virtual void setAgentType(int AIType) = 0;
};