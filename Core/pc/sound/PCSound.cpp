#ifdef _PC

#include "pc/sound/PCSound.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
PCSound::PCSound()
	: m_alSource(0)
{
	// empty
}

//--------------------------------------------------------------------------------
PCSound::PCSound(unsigned int source, bool looping)
:m_alSource(source)
{
	if(looping)
	{
		alSourcei(source, AL_LOOPING, AL_TRUE);
	}
	else
	{
		alSourcei(source, AL_LOOPING, AL_FALSE);
	}
}

PCSound::~PCSound()
{
	// empty
}

#ifdef _3DSFX
//--------------------------------------------------------------------------------
void
PCSound::createEFX(EAXREVERBPROPERTIES &eaxReverb)
{
	// Create Effect Slot, Effect and Filter for the AL source
	SoundEFX::get()->createEffectsSlot(m_effectSlot);
	SoundEFX::get()->createEffect(m_effect);
	SoundEFX::get()->createFilter(m_filter);
	
	// Convert the EAX reverb properties to EFX reverb properties
	ConvertReverbParameters(&eaxReverb, &efxReverb);

	// Attach the EFX reverb properties to the AL source
	SoundEFX::get()->setEFXEAXReverbProperties(efxReverb, m_effect);

	// Load Effect into Auxiliary Effect Slot
	SoundEFX::get()->loadEffect(m_effect, m_effectSlot);

	// Enable (non-filtered) Send from Source to Auxiliary Effect Slot
	alSource3i(m_alSource, AL_AUXILIARY_SEND_FILTER, m_effectSlot, 0, AL_FILTER_NULL);
}
#endif
//--------------------------------------------------------------------------------


#endif