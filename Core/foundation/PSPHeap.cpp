#include "foundation/PSPHeap.h"

// Flag indicating whether initialitation has been performed
static bool IsHeapInitialized = false;

//void *s_heap=0;

//--------------------------------------------------------------------------------
/**
	Initializes the OS, memory, video, audio and gamepads.
*/
void
PSPInit()
{
    if(IsHeapInitialized)
    {
        return;
    }

	s_heap=sceHeapCreateHeap("globalHeap",1048576,SCE_HEAP_AUTO_EXTEND,NULL);
	if (!s_heap){
		//couldn't create a heap with 100 MB
		return;
	}

    IsHeapInitialized = true;
}

//--------------------------------------------------------------------------------
void*
operator new(size_t blocksize)
{
    if(!IsHeapInitialized)
    {
        PSPInit();
    }

	return sceHeapAllocHeapMemory(s_heap, blocksize);

	//return OSAlloc(blocksize);
}

//--------------------------------------------------------------------------------
void*
operator new[](size_t blocksize)
{
    if(!IsHeapInitialized)
    {
       PSPInit();
    }
	return sceHeapAllocHeapMemory(s_heap, blocksize);
    //return OSAlloc(blocksize);
}

//--------------------------------------------------------------------------------
void
operator delete(void* block)
{
    sceHeapFreeHeapMemory(s_heap,block);
	//OSFree(block);
}

//--------------------------------------------------------------------------------
void
operator delete[](void* block)
{
	sceHeapFreeHeapMemory(s_heap,block);
    //OSFree(block);
}

//--------------------------------------------------------------------------------
//void
//free(void* block)
//{
//    sceHeapFreeHeapMemory(s_heap,block);
//}