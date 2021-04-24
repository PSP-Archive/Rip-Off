#ifdef _PC

#include <iostream>
#include "pc/sound/PCSoundLoader.h"
#include "pc/sound/CWaves.h"

const std::string PCSoundLoader::VAR_WAV_FILE("wavFile");
const std::string PCSoundLoader::VAR_LOOPING("looping");

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
Sound*
PCSoundLoader::load(const ConfigItem& configItem)
{
	// Check if the wav file path exists
	if(!configItem.hasString(VAR_WAV_FILE))
	{
		return NULL;
	}
	
	CWaves cwave;
	WAVEID WaveID;
	ALint alBufferLen;			//length of the wave file
	ALint alFreqBuffer;			//for the frequency of the wave
	ALenum alFormatBuffer;		//for the wave format
	ALchar* alBuffer;			//data for the wave

	if(SUCCEEDED(cwave.LoadWaveFile(configItem.getString(VAR_WAV_FILE).c_str(), &WaveID)))
	{
		cwave.GetWaveSize(WaveID, (unsigned long*)&alBufferLen);
		cwave.GetWaveData(WaveID, (void**)&alBuffer);
		cwave.GetWaveFrequency(WaveID, (unsigned long*)&alFreqBuffer);
		cwave.GetWaveALBufferFormat(WaveID, &alGetEnumValue, (unsigned long*)&alFormatBuffer);

		//create 1 buffer
		unsigned int alSampleSet;
		alGenBuffers(1, &alSampleSet);

		//alBufferData(alSampleSet, AL_FORMAT_MONO16, alBuffer, uBufSize, 44000);

		//put the data into our sampleset buffer
		alBufferData(alSampleSet, alFormatBuffer, alBuffer, alBufferLen, alFreqBuffer);

		//create 1 source
		unsigned int source;
		alGenSources(1, &source);

		//assign the buffer to this source
		alSourcei(source, AL_BUFFER, alSampleSet);

		//release the data
		cwave.DeleteWaveFile(WaveID);

		// Check whether looping
		bool looping = false;
		if(configItem.hasInteger(VAR_LOOPING) && configItem.getInteger(VAR_LOOPING) != 0)
		{
			looping = true;
		}

		return new Sound(source, looping);
	}
	else
	{
		// wave file not found
		return NULL;
	}

}

#endif
