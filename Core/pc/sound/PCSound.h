#pragma once

#include "sound/SoundIF.h"
#include <AL/al.h>
#include "foundation/Vector2f.h"
#include "foundation/Vector3f.h"

#ifdef _3DSFX
#include "pc/sound/PCSoundEFX.h"
#endif

/*	=====================================================================
		PC implementation of sound
	=====================================================================	*/
class PCSound : public SoundIF
{
public:
	PCSound();
	PCSound(unsigned int source, bool looping = false);
	~PCSound();

	// Play the sound.
	void play();

	// Stop the sound.
	void stop();

	// Set an AL source. 
	void setSource(unsigned int source);

	// Return an AL source. Returns 0 if the AL source does not exist.
	unsigned int getSource() const ;

	// set the listener position in 3D sound. 
	// The listener is the reference point from which to hear the sound.
	inline void setListenerPosition(const Vector2f &listenerPos) 
	{
		alListener3f(AL_POSITION, -listenerPos[0], listenerPos[1], 0.0f);
	}

	inline void setListenerPosition(const Vector3f &listenerPos) 
	{
		alListenerfv(AL_POSITION, listenerPos.GetArray());
	}

	// set the listener orientation in 3D sound.
	inline void setListenerOrientation(const float* listenerOrientation)
	{
		alListenerfv(AL_ORIENTATION, listenerOrientation);
	}

#ifdef _3DSFX

	// Create the EFX effect from an EAX reverb properties preset (EAX-Util.h)
	void createEFX(EAXREVERBPROPERTIES &eaxReverb);
	// Enable EFX sound effect
	inline void enableEFX() { alSource3i(m_alSource, AL_AUXILIARY_SEND_FILTER, m_effectSlot, 0, AL_FILTER_NULL); }
	// Disable EFX sound effect
	inline void disableEFX() { alSource3i(m_alSource, AL_AUXILIARY_SEND_FILTER, AL_EFFECT_NULL, 0, AL_FILTER_NULL); }

#endif

private:
	//buffer source
	unsigned int m_alSource;

#ifdef _3DSFX

	ALuint m_effectSlot;
	ALuint m_effect; 
	ALuint m_filter;
	EFXEAXREVERBPROPERTIES efxReverb;

#endif

};

//--------------------------------------------------------------------------------
inline
void
PCSound::setSource(unsigned int source)
{
	 m_alSource = source;
}

//--------------------------------------------------------------------------------
inline 
unsigned int 
PCSound::getSource() const 
{ 
	return m_alSource; 
}

//--------------------------------------------------------------------------------
inline 
void 
PCSound::play()
{
	alSourcePlay(m_alSource);
}

//--------------------------------------------------------------------------------
inline 
void 
PCSound::stop()
{
 	alSourceStop(m_alSource);
}

