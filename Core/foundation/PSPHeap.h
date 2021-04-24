#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <libheap.h>


static void* s_heap;

void PSPInit();
void* operator new(size_t blocksize);
void* operator new[](size_t blocksize);
void operator delete(void* block);
void operator delete[](void* block);
//void free(void* ptr);