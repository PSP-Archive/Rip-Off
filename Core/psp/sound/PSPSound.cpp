#ifdef _SPSP

#include "psp/sound/PSPSound.h"

//--------------------------------------------------------------------------------
PSPSound::PSPSound()
	: m_voiceID(-1)
{
	// empty
}

//--------------------------------------------------------------------------------
PSPSound::PSPSound(int id, const void *source, SceUInt32 size, bool looping)
	: m_voiceID(id)
{
	/*	set the voice for which sound is to be produced 
		int sceSasSetVoice(	int iVoiceNum,			Voice number (0 - 31)
							const void *vagBuf,		Pointer to waveform data buffer 
							SceSize size,			Waveform data size 
							int loopflag);			Loop flag(SCE_SAS_LOOP_ENABLE or SCE_SAS_LOOP_DISABLE
	*/
	sceSasSetVoice(m_voiceID, source, size, looping);

	/*	sets the time change of an envelope of a voice.
		int sceSasSetADSR(	int iVoiceNum, 			Voice number (0 - 31)
							int flag,				Setting flag 
							SceUInt32 a,			SCE_SAS_ATTACK_VALID rate
							SceUInt32 d,			SCE_SAS_DECAY_VALID rate
							SceUInt32 s,			SCE_SAS_SUSTAIN_VALID rate
							SceUInt32 r);			SCE_SAS_RELEASE_VALID rate

		Envelope processing simulates the reproduction of the key on to key off of existing sound
		Attack ~	Interval from immediately after key on is performed until the envelope value reaches its peak 
		Decay ~		Interval after Attack until the envelope value falls to a specified level (Sustain Level) 
		Sustain ~	Interval after Decay until key off is performed 
		Release ~	Interval after key off is performed until the envelope value becomes 0 
	*/
	sceSasSetADSR(m_voiceID, 
					SCE_SAS_ATTACK_VALID|SCE_SAS_DECAY_VALID|SCE_SAS_SUSTAIN_VALID|SCE_SAS_RELEASE_VALID,
					0x40000000, 100, 100, 0x10000000);
	
	/*	set volume of the voice
		int sceSasSetVolume(	int iVoiceNum,		Voice number (0 - 31)
								int l,				Left volume   
								int r,				Right volume   
								int wl,				Left effect volume   
								int wr);			Right effect volume
	*/
	sceSasSetVolume(m_voiceID, SCE_SAS_VOLUME_MAX, SCE_SAS_VOLUME_MAX, 0, 0);
	
	// set pitch of the voice
	sceSasSetPitch(m_voiceID, 0x1000);
}

//--------------------------------------------------------------------------------
PSPSound::~PSPSound()
{
	// empty
}

//--------------------------------------------------------------------------------
void 
PSPSound::play()
{
	//sceSasSetKeyOff(m_voiceID);
	sceSasSetKeyOn(m_voiceID);
}

//--------------------------------------------------------------------------------
void 
PSPSound::stop()
{
	sceSasSetKeyOff(m_voiceID);
}

#endif