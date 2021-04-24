/* Version history
	Class created by Birgit
*/

#pragma once

//DECLARE SHIP HERE TO PREVENT CYCLIC DEPENDENCY
class Ship;

//--------------------------------------------------------------------------------
class ControllerIF {
public:
	// Dtor
	virtual ~ControllerIF() {}
	
	// Called when the controller is to be updated
	virtual void Update(float frameTime) = 0;

	// Called when the controller is to be initialized
	virtual void Init() = 0;

	// Called when the controller should cleanup
	virtual void Cleanup() = 0;

	// Sets the target ship
	void setShip(Ship* ship) { mp_ship = ship; }

protected:
	Ship* mp_ship;
};