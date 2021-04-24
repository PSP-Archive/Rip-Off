#ifdef _3DSFX

#include "PCSoundEFX.h"
#include "AL/efx-creative.h"
#include <iostream>

//--------------------------------------------------------------------------------
PCSoundEFX::PCSoundEFX()
{
	alGenEffects = NULL;
	alDeleteEffects = NULL;
	alIsEffect = NULL;
	alEffecti = NULL;
	alEffectiv = NULL;
	alEffectf = NULL;
	alEffectfv = NULL;
	alGetEffecti = NULL;
	alGetEffectiv = NULL;
	alGetEffectf = NULL;
	alGetEffectfv = NULL;

	alGenAuxiliaryEffectSlots = NULL;
	alDeleteAuxiliaryEffectSlots = NULL;
	alIsAuxiliaryEffectSlot = NULL;
	alAuxiliaryEffectSloti = NULL;
	alAuxiliaryEffectSlotiv = NULL;
	alAuxiliaryEffectSlotf = NULL;
	alAuxiliaryEffectSlotfv = NULL;
	alGetAuxiliaryEffectSloti = NULL;
	alGetAuxiliaryEffectSlotiv = NULL;
	alGetAuxiliaryEffectSlotf = NULL;
	alGetAuxiliaryEffectSlotfv = NULL;
		
	alGenFilters = NULL;
	alDeleteFilters = NULL;
	alIsFilter = NULL;
	alFilteri = NULL;
	alFilteriv = NULL;
	alFilterf = NULL;
	alFilterfv = NULL;
	alGetFilteri = NULL;
	alGetFilteriv = NULL;
	alGetFilterf = NULL;
	alGetFilterfv = NULL;
}

//--------------------------------------------------------------------------------
PCSoundEFX::~PCSoundEFX()
{
	// empty
}

//--------------------------------------------------------------------------------
bool 
PCSoundEFX::init()
{
	ALCdevice *device = NULL;
	ALCcontext *context = NULL;

	context = alcGetCurrentContext();
	device = alcGetContextsDevice(context);

	if (alcIsExtensionPresent(device, (ALCchar*)ALC_EXT_EFX_NAME) == AL_TRUE) 
	{
		// EFX Extension found!
	
		// Get the Effect Extension function pointers
		alGenEffects = (LPALGENEFFECTS)alGetProcAddress("alGenEffects");
		alDeleteEffects = (LPALDELETEEFFECTS )alGetProcAddress("alDeleteEffects");
		alIsEffect = (LPALISEFFECT )alGetProcAddress("alIsEffect");
		alEffecti = (LPALEFFECTI)alGetProcAddress("alEffecti");
		alEffectiv = (LPALEFFECTIV)alGetProcAddress("alEffectiv");
		alEffectf = (LPALEFFECTF)alGetProcAddress("alEffectf");
		alEffectfv = (LPALEFFECTFV)alGetProcAddress("alEffectfv");
		alGetEffecti = (LPALGETEFFECTI)alGetProcAddress("alGetEffecti");
		alGetEffectiv = (LPALGETEFFECTIV)alGetProcAddress("alGetEffectiv");
		alGetEffectf = (LPALGETEFFECTF)alGetProcAddress("alGetEffectf");
		alGetEffectfv = (LPALGETEFFECTFV)alGetProcAddress("alGetEffectfv");

		// Get the Effect Slots Extension function pointers
		alGenAuxiliaryEffectSlots = (LPALGENAUXILIARYEFFECTSLOTS)alGetProcAddress("alGenAuxiliaryEffectSlots");
		alDeleteAuxiliaryEffectSlots = (LPALDELETEAUXILIARYEFFECTSLOTS)alGetProcAddress("alDeleteAuxiliaryEffectSlots");
		alIsAuxiliaryEffectSlot = (LPALISAUXILIARYEFFECTSLOT)alGetProcAddress("alIsAuxiliaryEffectSlot");
		alAuxiliaryEffectSloti = (LPALAUXILIARYEFFECTSLOTI)alGetProcAddress("alAuxiliaryEffectSloti");
		alAuxiliaryEffectSlotiv = (LPALAUXILIARYEFFECTSLOTIV)alGetProcAddress("alAuxiliaryEffectSlotiv");
		alAuxiliaryEffectSlotf = (LPALAUXILIARYEFFECTSLOTF)alGetProcAddress("alAuxiliaryEffectSlotf");
		alAuxiliaryEffectSlotfv = (LPALAUXILIARYEFFECTSLOTFV)alGetProcAddress("alAuxiliaryEffectSlotfv");
		alGetAuxiliaryEffectSloti = (LPALGETAUXILIARYEFFECTSLOTI)alGetProcAddress("alGetAuxiliaryEffectSloti");
		alGetAuxiliaryEffectSlotiv = (LPALGETAUXILIARYEFFECTSLOTIV)alGetProcAddress("alGetAuxiliaryEffectSlotiv");
		alGetAuxiliaryEffectSlotf = (LPALGETAUXILIARYEFFECTSLOTF)alGetProcAddress("alGetAuxiliaryEffectSlotf");
		alGetAuxiliaryEffectSlotfv = (LPALGETAUXILIARYEFFECTSLOTFV)alGetProcAddress("alGetAuxiliaryEffectSlotfv");
		
		// Get the Effect Filter Extension function pointers
		alGenFilters = (LPALGENFILTERS)alGetProcAddress("alGenFilters");
		alDeleteFilters = (LPALDELETEFILTERS)alGetProcAddress("alDeleteFilters");
		alIsFilter = (LPALISFILTER)alGetProcAddress("alIsFilter");
		alFilteri = (LPALFILTERI)alGetProcAddress("alFilteri");
		alFilteriv = (LPALFILTERIV)alGetProcAddress("alFilteriv");
		alFilterf = (LPALFILTERF)alGetProcAddress("alFilterf");
		alFilterfv = (LPALFILTERFV)alGetProcAddress("alFilterfv");
		alGetFilteri = (LPALGETFILTERI )alGetProcAddress("alGetFilteri");
		alGetFilteriv= (LPALGETFILTERIV )alGetProcAddress("alGetFilteriv");
		alGetFilterf = (LPALGETFILTERF )alGetProcAddress("alGetFilterf");
		alGetFilterfv= (LPALGETFILTERFV )alGetProcAddress("alGetFilterfv");
	}
	else
	{
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------
bool 
PCSoundEFX::createEffectsSlot(ALuint &effectSlot)
{
	// Clear AL Error state
	alGetError();

	// Generate an Auxiliary Effect Slot
	alGenAuxiliaryEffectSlots(1, &effectSlot);
	if (alGetError() != AL_NO_ERROR)
		return false;

	return true;
}

//--------------------------------------------------------------------------------
bool 
PCSoundEFX::createEffect(ALuint &effect)
{
	// Clear AL Error State
	alGetError();

	// Generate an Effect
	alGenEffects(1, &effect);
	alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB);

	if (alGetError() != AL_NO_ERROR)
		return false;

	return true;
}

//--------------------------------------------------------------------------------
bool 
PCSoundEFX::createFilter(ALuint &filter)
{
	// Clear AL Error State
	alGetError();

	// Generate a filter
	alGenFilters(1, &filter);

	if (alGetError() != AL_NO_ERROR)
		return false;

	return true;
}

//--------------------------------------------------------------------------------
bool 
PCSoundEFX::loadEffect(ALuint &effect, ALuint &effectSlot)
{
	// Clear AL Error State
	alGetError();

	// Generate a filter
	alAuxiliaryEffectSloti(effectSlot, AL_EFFECTSLOT_EFFECT, effect);

	if (alGetError() != AL_NO_ERROR)
		return false;

	return true;
}

//--------------------------------------------------------------------------------
bool 
PCSoundEFX::setEFXEAXReverbProperties(EFXEAXREVERBPROPERTIES &reverb, ALuint &effect)
{
	// Clear AL Error code
	alGetError();

	alEffectf(effect, AL_EAXREVERB_DENSITY, reverb.flDensity);
	alEffectf(effect, AL_EAXREVERB_DIFFUSION, reverb.flDiffusion);
	alEffectf(effect, AL_EAXREVERB_GAIN, reverb.flGain);
	alEffectf(effect, AL_EAXREVERB_GAINHF, reverb.flGainHF);
	alEffectf(effect, AL_EAXREVERB_GAINLF, reverb.flGainLF);
	alEffectf(effect, AL_EAXREVERB_DECAY_TIME, reverb.flDecayTime);
	alEffectf(effect, AL_EAXREVERB_DECAY_HFRATIO, reverb.flDecayHFRatio);
	alEffectf(effect, AL_EAXREVERB_DECAY_LFRATIO, reverb.flDecayLFRatio);
	alEffectf(effect, AL_EAXREVERB_REFLECTIONS_GAIN, reverb.flReflectionsGain);
	alEffectf(effect, AL_EAXREVERB_REFLECTIONS_DELAY, reverb.flReflectionsDelay);
	alEffectfv(effect, AL_EAXREVERB_REFLECTIONS_PAN, reverb.flReflectionsPan);
	alEffectf(effect, AL_EAXREVERB_LATE_REVERB_GAIN, reverb.flLateReverbGain);
	alEffectf(effect, AL_EAXREVERB_LATE_REVERB_DELAY, reverb.flLateReverbDelay);
	alEffectfv(effect, AL_EAXREVERB_LATE_REVERB_PAN, reverb.flLateReverbPan);
	alEffectf(effect, AL_EAXREVERB_ECHO_TIME, reverb.flEchoTime);
	alEffectf(effect, AL_EAXREVERB_ECHO_DEPTH, reverb.flEchoDepth);
	alEffectf(effect, AL_EAXREVERB_MODULATION_TIME, reverb.flModulationTime);
	alEffectf(effect, AL_EAXREVERB_MODULATION_DEPTH, reverb.flModulationDepth);
	alEffectf(effect, AL_EAXREVERB_AIR_ABSORPTION_GAINHF, reverb.flAirAbsorptionGainHF);
	alEffectf(effect, AL_EAXREVERB_HFREFERENCE, reverb.flHFReference);
	alEffectf(effect, AL_EAXREVERB_LFREFERENCE, reverb.flLFReference);
	alEffectf(effect, AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, reverb.flRoomRolloffFactor);
	alEffecti(effect, AL_EAXREVERB_DECAY_HFLIMIT, reverb.iDecayHFLimit);

	if (alGetError() != AL_NO_ERROR)
		return false;

	return true;
}

#endif