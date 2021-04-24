#include "EffectIF.h"

//--------------------------------------------------------------------------------
EffectIF::EffectIF() :
	m_position(0.0f, 0.0f),
	m_rotation(0.0f),
	m_isFinished(false),
	m_pBody(0)
{
	// empty
}
