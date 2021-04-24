#pragma once

#include "foundation/GlobalTimer.h"

//--------------------------------------------------------------------------------
/** 
	Timer class, provides advanced timing functionality. Required to be updated
	periodically (every frame) but is guaranteed to return the same value until
	the update() method is called again. Also it can be pause and resumed.
*/
class Timer
{
public:
	// Ctor - starts the timer
	Timer();

	// Resets the timer to 0.
	void reset();

	// Pauses the timer.
	void pause();

	// Resumes the timer from a paused state. Has no effect if it is not paused.
	void resume();

	// Returns whether the timer is currently paused.
	bool isPaused();

	// Updates the timer from the system time. Should be called periodically.
	void update();

	// Returns the current time of this timer.
	float getTime();

	// Returns the time passed from the last update
	float getFrameTime();

private:
	float m_accumulator;
	float m_prevUpdate;
	bool m_isPaused;
	float m_frameTime;
};

//--------------------------------------------------------------------------------
inline
void
Timer::reset()
{
	m_accumulator = 0.0f;
	m_frameTime = 0;
	m_prevUpdate = GlobalTimer::get()->getTime();
}

//--------------------------------------------------------------------------------
inline
void
Timer::pause()
{
	m_isPaused = true;
}

//--------------------------------------------------------------------------------
inline
void
Timer::resume()
{
	m_isPaused = false;
}

//--------------------------------------------------------------------------------
inline
bool
Timer::isPaused()
{
	return m_isPaused;
}

//--------------------------------------------------------------------------------
inline
void
Timer::update()
{
	if(!m_isPaused)
	{
		float time = GlobalTimer::get()->getTime();
		m_frameTime = time - m_prevUpdate;
		m_accumulator += m_frameTime;
		m_prevUpdate = time;
	}
	else
	{
		m_frameTime = 0;
		m_prevUpdate = GlobalTimer::get()->getTime();
	}
}

//--------------------------------------------------------------------------------
inline
float
Timer::getTime()
{
	return m_accumulator;
}

//--------------------------------------------------------------------------------
inline
float
Timer::getFrameTime()
{
	return m_frameTime;
}
