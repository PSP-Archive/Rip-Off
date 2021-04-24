#ifdef _3DSFX

#pragma once

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/efx.h"
#include "AL/efx-util.h"
#include "foundation/Singleton.h"

class PCSoundEFX
{
public:
	PCSoundEFX();
	~PCSoundEFX();
	
	// Initialize the Effects Extension.
	bool init();

	// Create auxiliary Effect Slots, Effects, and Filters
	bool createEffectsSlot(ALuint &effectSlot);
	bool createEffect(ALuint &effect);
	bool createFilter(ALuint &filter);
	
	// Load Effect into Auxiliary Effect Slot
	bool loadEffect(ALuint &effect, ALuint &effectSlot);

	// Set EFX reverb properties
	bool setEFXEAXReverbProperties(EFXEAXREVERBPROPERTIES &reverb, ALuint &effect);

private:
	//Effect objects
	LPALGENEFFECTS alGenEffects;
	LPALDELETEEFFECTS alDeleteEffects;
	LPALISEFFECT alIsEffect;
	LPALEFFECTI alEffecti;
	LPALEFFECTIV alEffectiv;
	LPALEFFECTF alEffectf;
	LPALEFFECTFV alEffectfv;
	LPALGETEFFECTI alGetEffecti;
	LPALGETEFFECTIV alGetEffectiv;
	LPALGETEFFECTF alGetEffectf;
	LPALGETEFFECTFV alGetEffectfv;

	// Auxiliary slot object
	LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots;
	LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots;
	LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot;
	LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti;
	LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv;
	LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf;
	LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv;
	LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti;
	LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv;
	LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf;
	LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv;
		
	//Filter objects
	LPALGENFILTERS alGenFilters;
	LPALDELETEFILTERS alDeleteFilters;
	LPALISFILTER alIsFilter;
	LPALFILTERI alFilteri;
	LPALFILTERIV alFilteriv;
	LPALFILTERF alFilterf;
	LPALFILTERFV alFilterfv;
	LPALGETFILTERI alGetFilteri;
	LPALGETFILTERIV alGetFilteriv;
	LPALGETFILTERF alGetFilterf;
	LPALGETFILTERFV alGetFilterfv;
};

// Define the singleton manager
typedef Singleton<PCSoundEFX> SoundEFX;


#endif