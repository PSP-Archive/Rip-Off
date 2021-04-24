
#include "sound/SoundManager.h"
#include "foundation/ConfigDataLoader.h"
#include "foundation/ConfigData.h"
#include "foundation/ConfigItem.h"

//--------------------------------------------------------------------------------
SoundManagerBase::SoundManagerBase()
{
	// empty
}

//--------------------------------------------------------------------------------
SoundManagerBase::~SoundManagerBase()
{
	// empty
}

//--------------------------------------------------------------------------------
bool 
SoundManagerBase::init()
{
	m_sound = new SoundDevice();

	return m_sound->init();
}

//--------------------------------------------------------------------------------
void 
SoundManagerBase::cleanUp()
{
	m_sound->cleanUp();
	
	delete m_sound;
}

