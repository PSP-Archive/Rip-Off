#pragma once

#include <windows.h>
#include "foundation/GlobalTimerIF.h"
#include <mmSystem.h>

#pragma comment(lib, "Winmm.lib")

//--------------------------------------------------------------------------------
/**
	PC implementation of a timing functionality. Currently uses windows' 
	timeGetTime() which gives 10ms precision and 49 days wrap around.
*/
class PCGlobalTimer
{
public:
	PCGlobalTimer();
	void reset();
	float getTime() const;

private:
	DWORD m_start;
};

//--------------------------------------------------------------------------------
inline
PCGlobalTimer::PCGlobalTimer()
{
	reset();
}

//--------------------------------------------------------------------------------
inline
void
PCGlobalTimer::reset()
{
	m_start = timeGetTime();
}

//--------------------------------------------------------------------------------
inline
float
PCGlobalTimer::getTime() const
{
	return (static_cast<float>(timeGetTime()) - static_cast<float>(m_start)) / 1000.0f;
}

