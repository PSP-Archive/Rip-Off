#ifdef _SPSP

#include <kernel.h>
#include "psp/network/PSPPeer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int PSPPeer::socket_id = -1;

PSPPeer::PSPPeer()
{
}

//--------------------------------------------------------------------------------
PSPPeer::~PSPPeer()
{

}

//--------------------------------------------------------------------------------
bool
PSPPeer::createSocket(struct SceNetEtherAddr *local_addr)
{
	int ret = 0;

	//E Create PDP socket 
	ret = sceNetAdhocPdpCreate(local_addr, PORT, RXBUFLEN, 0);
	if (ret < 0) {
		printf("sceNetAdhocPdpCreate() failed. ret = 0x%x\n", ret);
		return false;
	}

	socket_id = ret;
	return true;
}

//--------------------------------------------------------------------------------
bool
PSPPeer::terminate()
{
	int ret = 0;
	
	if (socket_id >= 0) 
	{
		ret = sceNetAdhocPdpDelete(socket_id, 0);
		if (ret < 0) {
			printf("sceNetAdhocPdpDelete() failed. ret = 0x%x\n", ret);
			return false;
		}

		socket_id = -1;
		return true;
	}
	return false;
}

#endif
