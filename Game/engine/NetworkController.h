#pragma once
#include "engine/controllerif.h"
#include "engine/ship.h"

class NetworkController :
	public ControllerIF
{
public:
	NetworkController(int playerNo);
	~NetworkController(void);

	// Called when the controller is to be updated
	void Update(float frameTime) {}

	// Called when the controller is to be initialized
	void Init() {}

	// Called when the controller should cleanup
	void Cleanup() {}
};
