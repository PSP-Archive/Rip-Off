/* VERSION HISTORY

23/02/2010 - David Wright - Class created
27/02/10	- Birgit, added empty function bodies for Init and Cleanup according to 
			  definitions in ControllerIF
*/

#pragma once
#include "engine\controllerif.h"

class InputController :
	public ControllerIF
{
public:
	InputController(int playerNo);
	~InputController(void);

	void Update(float frameTime);
	void Init();
	void Cleanup();

private:
	int m_playerNo;
};
