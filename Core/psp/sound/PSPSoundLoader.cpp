#ifdef _SPSP

#include <kernel.h>
#include "psp/sound/PSPSoundLoader.h"

int PSPSoundLoader::m_soundNum = -1;

// define vag file offset
#define	VAGFILE_HDR		48

const string PSPSoundLoader::VAR_WAV_FILE("vagFile");
const string PSPSoundLoader::VAR_LOOPING("looping");
void* PSPSoundLoader::m_effectBuffer[32] __attribute__((aligned(16)));
SceUID PSPSoundLoader::m_bufID[32];

//--------------------------------------------------------------------------------
PSPSoundLoader::PSPSoundLoader()
{
}

//--------------------------------------------------------------------------------
PSPSoundLoader::~PSPSoundLoader()
{
	for (int i = 0; i < m_soundNum; i++)
	{
		/*	free memory	  
			int sceKernelFreeMemoryBlock(	SceUID mbid	);		Memory block ID to be free

		*/
		sceKernelFreeMemoryBlock(m_bufID[i]);
	}
}

//--------------------------------------------------------------------------------
Sound*
PSPSoundLoader::load(const ConfigItem& configItem)
{
	// Check if the wav file path exists
	if(!configItem.hasString(VAR_WAV_FILE))
	{
		return NULL;
	}
	
	SceUID fd;

	if ((fd = sceIoOpen(configItem.getString(VAR_WAV_FILE).c_str(), SCE_O_RDONLY, 0)) < 0) {
		printf("File to open wave file %s\n", configItem.getString(VAR_WAV_FILE).c_str());
		return NULL;
	}

	//printf("File %s loaded.\n", configItem.getString(VAR_WAV_FILE).c_str());

	m_soundNum++;

	SceUInt32 sourceSize = (SceUInt32)sceIoLseek(fd, (SceOff)0, SCE_SEEK_END);

	SceUInt32 vagSize = (SceSize)sourceSize - VAGFILE_HDR;

	/*	allocate memory space for the sound 
		int sceKernelAllocMemoryBlock(	const char *name,					Name of the memory block. (Max 31 bytes)
										SceKernelSysMemAlloc_t type,		Memory block allocation type. 
										SceSize size,						Size of the memory block 
						const SceKernelMemoryBlockOptParam *optParam);		Reserved 

		Return Memory block ID.
	*/
	m_bufID[m_soundNum] = sceKernelAllocMemoryBlock(configItem.getString(VAR_WAV_FILE).c_str(), SCE_KERNEL_SMEM_LOW, (SceSize)vagSize, NULL);


	/*	load the sound buffer to the memory	  
		int sceKernelGetMemoryBlockAddr(	SceUID mbid						Memory block ID
											void **blockp );				Pointer to waveform data buffer 

	*/
	sceKernelGetMemoryBlockAddr(m_bufID[m_soundNum], &m_effectBuffer[m_soundNum]);


	sceIoLseek(fd, (SceOff)VAGFILE_HDR, SCE_SEEK_SET);

	sceIoRead(fd, m_effectBuffer[m_soundNum], (SceSize)vagSize);

	sceIoClose(fd);
	sceKernelDcacheWritebackInvalidateAll();

	// Check whether looping
	int looping = SCE_SAS_LOOP_DISABLE;
	if(configItem.hasInteger(VAR_LOOPING) && configItem.getInteger(VAR_LOOPING) != 0)
	{
		looping = SCE_SAS_LOOP_ENABLE;
	}

	return new Sound(m_soundNum, m_effectBuffer[m_soundNum], sourceSize, looping);
}

#endif
