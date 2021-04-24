#include "foundation/Timer.h"

//--------------------------------------------------------------------------------
Timer::Timer() :
	m_accumulator(0.0f),
	m_isPaused(false)
{
	m_prevUpdate = GlobalTimer::get()->getTime();
}

