////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) SN Systems Ltd 2003, 2004
//
//  Description: Sample 'hello world' program.
//
//
//  Change History:
//
//  Vers    Date            Author        Changes
//  1.00    12-Jan-2004     David         First release
//
////////////////////////////////////////////////////////////////////////////////

#include "application/OS.h"
#include "application/RipOffApplication.h"

#include "network/PSPNetwork.h"

#include <stdio.h>
#include <moduleexport.h>
#include <libgu.h>
#include <libgum.h>
#include <kernel.h>

#include "load_modules.h"
#include "foundation/PSPHeap.h"

SCE_MODULE_INFO( hello_world, 0, 1, 1 );


int main(int argc, char **argv)
{
	load_required_modules();

	OS os = OS("PSP RipOff");

	RipOffApplication app = RipOffApplication(os);

	bool loaded;

	//printf("start at %f sec\n", GlobalTimer::get()->getTime());

	loaded = app.loadConfig("host0:assets/config/psp.txt");
	assert(loaded);
	//printf("finish parsing psp.txt at %f sec\n", GlobalTimer::get()->getTime());

	loaded = app.loadConfig("host0:assets/config/game.txt");
	assert(loaded);
	//printf("finish parsing game.txt at %f sec\n", GlobalTimer::get()->getTime());

#ifdef _VECTOR
	loaded = app.loadConfig("host0:assets/config/vector.txt");
	assert(loaded);
	//printf("finish parsing vector.txt at %f sec\n", GlobalTimer::get()->getTime());
#elif _3D
	//#ifdef _DEBUG
	//	loaded=app.loadConfig("host0:assets/config/3D_debug.txt");
	//#else
		loaded=app.loadConfig("host0:assets/config/3D.txt");
		assert(loaded);
		//printf("finish parsing 3D.txt at %f sec\n", GlobalTimer::get()->getTime());
	//#endif
#endif
	//assert(loaded);
	//printf("finish parsing vector.txt at %f sec\n", GlobalTimer::get()->getTime());

	if(app.init())
	{
		if (PSPNetwork::get()->init())
		{
			//printf("PSP networking initialized.\n");
		}

		//printf("finish app.init at %f sec\n", GlobalTimer::get()->getTime());
		app.run();
	}

	unload_required_modules();

	return 0;
}

