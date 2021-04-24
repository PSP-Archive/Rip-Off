#pragma once

#include "foundation/DebugIF.h"

//--------------------------------------------------------------------------------
/**
	PC specific Debug functionalities.
*/
class PCDebug : public DebugIF
{
public:
	PCDebug();

protected:
	void onOutput(const std::string& text);
};

