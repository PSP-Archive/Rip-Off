#ifdef _SPSP

#include <cstdio>
#include "psp/sound/PSPSoundDevice.h"
#include <psperror.h>
#include <libsas.h>
#include <libwave.h>
#include <kernel.h>

/* lib files to be include :
	libwave.a
	libsas_weak.a
*/

short PSPSoundDevice::pcmBuf[2][256];

//--------------------------------------------------------------------------------
PSPSoundDevice::PSPSoundDevice()
{
	// empty
}

//--------------------------------------------------------------------------------
PSPSoundDevice::~PSPSoundDevice()
{
	// empty
}

//--------------------------------------------------------------------------------
bool 
PSPSoundDevice::init()
{
	// Initializes the libwave sound library.
	if (sceWaveInit() != SCE_OK){
		printf("sceWaveInit error\n");
		return false;
	}

	// Set the output length of Channel 0 to 256 samples
	sceWaveAudioSetSample(0, SAMPLES);

	// Initializes the SAS state.
	if (sceSasInit() != SCE_OK){
		printf("sceSasInit error\n");
		return false;
	}

	startThread();

	return true;
}

//--------------------------------------------------------------------------------
void 
PSPSoundDevice::cleanUp()
{
	endThread(); 

	if (sceSasExit() != SCE_OK){
		printf("sceSasExit() error\n");
	}
	if (sceWaveExit() != SCE_OK){
		printf("sceWaveExit() error\n");
	}
}

//--------------------------------------------------------------------------------
int 
PSPSoundDevice::sasThread(unsigned int args, void *argp)
{	
	int iSide = 0;

	//// Warning measure
	(void) args;
	(void) argp;

	//printf("running sound thread\n");

	while(true){

		// Generates PCM sound 
		sceSasCore(pcmBuf[iSide]);

		/* 
			This function performs low-level audio output of the generated PCM sound. 
			It registers the output data buffer specified by pcmBuf in the audio driver. 
			If the output data buffer could not be registered in the audio driver, 
			the thread that called this API enters a wait state and waits until it can be registered. 
			When the output data buffer can be registered in the audio driver, 
			the thread transitions from READY to RUN state, 
			and processing to register the output buffer in the audio driver is performed. 
			After the output buffer has been registered in the audio driver, the function returns to the caller.

			int sceWaveAudioWriteBlocking(	int iCh,				Audio output-only channel number (0 - 2) 
											int iVolL,				Left channel volume (0 - 32768)
											int iVolR,				Right channel volume (0 - 32768)
											const void* pBuf )		Output buffer
		*/
		sceWaveAudioWriteBlocking(0, SCE_WAVE_AUDIO_VOL_MAX, SCE_WAVE_AUDIO_VOL_MAX, pcmBuf[iSide]);
		iSide ^= 1;
	}

	while(sceWaveAudioGetRestSample(0) > 0){
		sceKernelDelayThread( 1000 );
	}

	sceKernelExitThread(0);

	return 0;
}

void PSPSoundDevice::startThread() 
{
	/* Creates a thread.for PSP SAS sound and allocates thread management area 
		SceUID sceKernelCreateThread(	const char *name,							Name of the thread
										int (*entry)(SceSize, void *),				Entry address of the thread.
										int initPriority,							Priority when the thread is started up
										SceSize stackSize,							Stack size required by the thread
										SceUInt attr,								Thread attributes 
										const SceKernelThreadOptParam *optParam );	Reserved
	*/
	m_threadID = sceKernelCreateThread("sas thread", sasThread, SCE_KERNEL_USER_HIGHEST_PRIORITY, 4096, 0, NULL);

	/* Wait for the end of sound thread
		int sceKernelStartThread (	SceUID thid,				Thread ID
									SceSize argSize,			Size of the arguments to be passed to the thread
									const void *argBlock );		Argument data to be passed to the thread

	*/

	if (m_threadID < 0){
		printf("sceKernelCreateThread:%08X\n",m_threadID);

	}
	int thread_status = sceKernelStartThread(m_threadID, 0, NULL);
	if (thread_status != SCE_KERNEL_ERROR_OK) {
		printf("sceKernelStartThread:%08X\n",thread_status);

	}
}

void PSPSoundDevice::endThread() 
{
	/* Wait for the end of sound thread
		int sceKernelWaitThreadEnd (	SceUID thid,			Thread ID
										SceUInt *timeout );		Wait time   
	*/
	sceKernelWaitThreadEnd(m_threadID,NULL);

	// Delete the sound thread and free the thread management area
	sceKernelDeleteThread(m_threadID);
}

#endif
