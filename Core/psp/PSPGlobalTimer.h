#pragma once


#include "foundation/GlobalTimerIF.h"
#include <kernel.h>



class PSPGlobalTimer
{
public:
	PSPGlobalTimer();
	void reset();
	float getTime() const;

private:
	double m_start;
};

//--------------------------------------------------------------------------------
inline
PSPGlobalTimer::PSPGlobalTimer()
{
	reset();
}

//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------


