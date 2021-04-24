/* SCE CONFIDENTIAL
 PSP(TM) Programmer Tool Runtime Library Release 5.5.0
 *
 *      Copyright (C) 2005 Sony Computer Entertainment Inc.
 *                        All Rights Reserved.
 *
 */

#include <kernel.h>
#include <utility/utility_module.h>
#include <stdio.h>
#include <string.h>
#include "load_modules.h"

static SceUID libfont_modid = -1;

static SceUID
load_module(
	const char *path
	)
{
	SceUID modid = -1;
	int ret = 0, mresult;

	ret = sceKernelLoadModule(path, 0, NULL);
	if(ret < 0){
		printf("sceKernelLoadModule() failed. ret = 0x%x\n", ret);
		goto error;
	}
	modid = ret;

	ret = sceKernelStartModule(modid, 0, 0, &mresult, NULL);
	if(ret < 0){
		printf("sceKernelStartModule() failed. ret = 0x%x\n", ret);
		goto error;
	}
	ret = modid;

	return ret;

error:
	if (modid >= 0) {
		ret = sceKernelUnloadModule(modid);
		if (ret < 0)
			printf("sceKernelUnloadModule() failed. ret = 0x%x\n", ret);
	}
	return ret;
}

static int
unload_module(
	SceUID modid
	)
{
	int ret = 0;

	ret = sceKernelStopModule(modid, 0, NULL, NULL, NULL);
	if (ret < 0) {
		printf("sceKernelStopModule() failed. ret = 0x%x\n", ret);
		return ret;
	}

	ret = sceKernelUnloadModule(modid);
	if (ret < 0) {
		printf("sceKernelUnloadModule() failed. ret = 0x%x\n", ret);
		return ret;
	}

	return ret;
}

int
load_required_modules(
	void
	)
{
	int ret = 0;

	// Load libfont

	ret = load_module(LIBFONT_PRX);
	if(ret < 0){
		printf("load_module %s failed. ret = 0x%x\n", LIBFONT_PRX, ret);
		goto error;
	}
	libfont_modid = ret;

	//------------------------



	// Load PSP networking module

	ret = sceUtilityLoadModule(SCE_UTILITY_MODULE_NET_COMMON);
	if(ret < 0){
		printf("sceUtilityLoadModule(SCE_UTILITY_MODULE_NET_COMMON) failed. ret = 0x%x\n", ret);
		goto error;
	}

	ret = sceUtilityLoadModule(SCE_UTILITY_MODULE_NET_ADHOC);
	if(ret < 0){
		printf("sceUtilityLoadModule(SCE_UTILITY_MODULE_NET_ADHOC) failed. ret = 0x%x\n", ret);
		goto error;
	}

	//------------------------



	// Load SAS sound module

	ret = sceUtilityLoadModule(SCE_UTILITY_MODULE_AV_SASCORE);
	if (ret < 0) {
		printf("SasCore error\n");
	}

	//------------------------

	return ret;

error:
	(void)unload_required_modules();

	return ret;
}

int
unload_required_modules(
	void
	)
{
	int ret = 0;
	

	// Unload SAS sound module

	ret = sceUtilityUnloadModule(SCE_UTILITY_MODULE_AV_SASCORE);
	if (ret < 0) {
		printf("SasCore unload error\n");
	}

	//------------------------



	// Unload PSP networking module

	ret = sceUtilityUnloadModule(SCE_UTILITY_MODULE_NET_ADHOC);
	if (ret < 0) {
		printf("sceUtilityUnloadModule(SCE_UTILITY_MODULE_NET_ADHOC) failed. ret = 0x%x\n", ret);
	}

	ret = sceUtilityUnloadModule(SCE_UTILITY_MODULE_NET_COMMON);
	if (ret < 0) {
		printf("sceUtilityUnloadModule(SCE_UTILITY_MODULE_NET_COMMON) failed. ret = 0x%x\n", ret);
	}

	//------------------------



	// Unload libfont

	if (libfont_modid >= 0) {
		ret = unload_module(libfont_modid);
		if (ret < 0) {
			printf("unload_module() failed. ret = 0x%x\n", ret);
		}
		else {
			libfont_modid = -1;
		}
	}

	//------------------------

	return ret;
}
