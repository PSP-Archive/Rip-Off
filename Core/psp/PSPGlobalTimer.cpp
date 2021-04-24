#ifdef _SPSP

#include "psp/PSPGlobalTimer.h"


void
PSPGlobalTimer::reset()
{
	m_start = sceKernelGetSystemTimeLow();
}

float
PSPGlobalTimer::getTime() const
{
	return (float)((sceKernelGetSystemTimeLow() - m_start) / 1000000.0f);
}

#endif
