#pragma once

#ifdef _SPSP

#include <kernel.h>
#include <psptypes.h>
#include <utility/utility_sysparam.h>

#include <pspnet.h>
#include <pspnet_error.h>
#include <pspnet_adhoc.h>
#include <pspnet_adhocctl.h>


class PSPPeer
{
public:
	PSPPeer();
	~PSPPeer();



	bool terminate();
	
private:
	static int socket_id;

};

#endif