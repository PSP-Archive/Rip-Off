#ifdef _SPSP

#include "PSPNetwork.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "engine/Game.h"
/* lib files to be include :

*/

#define BUFFER_FRAGMENT 1444

struct _info PSPNetworkBase::_info;
SceUtilityMsgDialogParam PSPNetworkBase::msgdialogParam;

char PSPNetworkBase::exchange_buf[BUFSIZE];

int PSPNetworkBase::handler_id = -1;
int PSPNetworkBase::evf = 0;
int PSPNetworkBase::error_code = 0;
int PSPNetworkBase::matching_tid = -1;
int PSPNetworkBase::socket_id0 = -1;
int PSPNetworkBase::socket_id = -1;
int PSPNetworkBase::lastCode = 3;

char PSPNetworkBase::netconfirmStr[] = "Turn on WLAN switch to search a challenger. If you'd like to play 1P mode, turn off WLAN switch.";
char PSPNetworkBase::discoveredStr[] = "Here comes a challenger !\n";
char PSPNetworkBase::peererrorStr[] = "The peer has disappeared.";

char PSPNetworkBase::event_str[][16] =
	{"ERROR", "CONNECTED", "DISCONNECT", "SCANNING", "(obsolete)",
     "INFO", "HOST_DISCOVER", "WOL", "WOL_ABORT"};

char* PSPNetworkBase::status = "Waiting...";

SceNetAdhocctlAdhocId adhoc_id = {
	/* .type = */ SCE_NET_ADHOCCTL_ADHOCTYPE_RESERVED,		// Debug use ID
	/* .data = */ {'S','C','E','S','M','P','L','0','7'},	/* "SCESMPL07" */
	/* .padding*/ {0, 0, 0}
};

SceNetAdhocDiscoverParam param = {
	/* .mode =         */ 0,
	/* .group_name = */ {
		/* .data = */{'\0','\0','\0','\0','\0','\0','\0','\0'}	/* "" */
	},
	/* .timeout =      */ 0,
	/* .result =       */ 0

	
};

//--------------------------------------------------------------------------------
PSPNetworkBase::PSPNetworkBase()
{

}

//--------------------------------------------------------------------------------
PSPNetworkBase::~PSPNetworkBase()
{
	// empty
}

//--------------------------------------------------------------------------------
bool 
PSPNetworkBase::init()
{
	int ret = sceNetInit(PSPNET_POOLSIZE, CALLOUT_TPL, 0, NETINTR_TPL, 0);
	if(ret < 0){
		printf("sceNetInit() failed. ret = 0x%x\n", ret);
		return false;
	}

	ret = sceNetAdhocInit();
	if(ret < 0){
		printf("sceNetAdhocInit() failed. ret = 0x%x\n", ret);
		return false;
	}

	ret = sceNetAdhocctlInit(ADHOCCTL_STACKSIZE, ADHOCCTL_TPL, &adhoc_id);
	if (ret < 0) {
		printf("sceNetAdhocctlInit() failed. ret = 0x%x\n", ret);
		return false;
	}

	ret = sceNetAdhocctlAddHandler(adhocctl_handler, NULL);
	if (ret < 0) {
		printf("sceNetAdhocctlAddHandler() failed. ret = 0x%x\n", ret);
		return false;
	}
	handler_id = ret;



	return true;
}

//--------------------------------------------------------------------------------
void 
PSPNetworkBase::cleanUp()
{
}

//--------------------------------------------------------------------------------

char* 
PSPNetworkBase::getLastMessage(void)
{
	return  status; // event_str[lastCode];
}

//--------------------------------------------------------------------------------
void 
PSPNetworkBase::adhocctl_handler(int event, int error, void *arg)
{
	printf("event: [%s] error_code = 0x%x\n", event_str[event], error);
	lastCode = event;

	(void)(arg);

	if (event == SCE_NET_ADHOCCTL_EVENT_ERROR) {
		error_code = error;
		evf |= EVF_ERROR;
	}
	else if (event == SCE_NET_ADHOCCTL_EVENT_CONNECT) {
		error_code = 0;
		evf |= EVF_CONNECT;
	}
	else if (event == SCE_NET_ADHOCCTL_EVENT_DISCONNECT) {
		error_code = 0;
		evf |= EVF_DISCONNECT;
	}
	else if (event == SCE_NET_ADHOCCTL_EVENT_SCAN) {
		error_code = 0;
		evf |= EVF_SCAN;
	}
	else if (event == SCE_NET_ADHOCCTL_EVENT_HOSTDISCOVER) {
		error_code = 0;
		evf |= EVF_HOSTDISCOVER;
	}
	else if (event == SCE_NET_ADHOCCTL_EVENT_WOL) {
		error_code = 0;
		evf |= EVF_WOL;
	}
	else if (event == SCE_NET_ADHOCCTL_EVENT_WOL_ABORT) {
		error_code = 0;
		evf |= EVF_WOL_ABORT;
	}

	return;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::net_discover_start(void)
{
    param.mode = SCE_NET_ADHOC_DISCOVER_MODE_HOSTDISCOVER;
    param.timeout = RIPOFF_DISCOVER_TIMEOUT;
	param.result = 0;
	int ret = sceNetAdhocDiscoverInitStart(&param);
	if (ret < 0) {
		printf("sceNetAdhocDiscoverInitStart() failed. ret = 0x%x\n", ret);
		change_state(STATE_NET_REINIT);
	}
	else {
		printf("sceNetAdhocDiscoverInitStart() succeeded\n");
		change_state(STATE_NET_DISCOVER_RUNNING);
	}
	
	struct SceNetEtherAddr n;
	ret = sceNetGetLocalEtherAddr(&n);
	if(ret < 0){
		/* Error handling */
	}

	char str[sizeof("XX:XX:XX:XX:XX:XX")];
	sceNetEtherNtostr(&n, str);

	printf("Local MAC Addr: %s\n", str);


	return 0;
}

//--------------------------------------------------------------------------------
void
PSPNetworkBase::change_state(enum network_state state)
{
	_info.state = state;

	if (state == STATE_NET_NONE) {
		memset(&_info.peer_info, 0, sizeof(struct SceNetAdhocctlPeerInfo));
		memset(&_info.group_name, 0, sizeof(struct SceNetAdhocctlGroupName));
		_info.flags = 0;
	}
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::net_discover_running(void)
{
	/* check stop request */
	if(evf & EVF_CANCEL){
		evf &= ~EVF_CANCEL;
		sceNetAdhocDiscoverStop();
	}

	int status = sceNetAdhocDiscoverGetStatus();

	switch (status) {
	case SCE_NET_ADHOC_DISCOVER_STATUS_RUNNING:
		sceNetAdhocDiscoverUpdate();
		break;
	case SCE_NET_ADHOC_DISCOVER_STATUS_FINISHED:
		sceNetAdhocDiscoverTerm();
		change_state(STATE_NET_DISCOVER_FINISHED);
		break;
	default:
		break;
	}

	return 0;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::net_discover_finished(void)
{
	switch (param.result) {
	case SCE_NET_ADHOC_DISCOVER_RESULT_OK:
		change_state(STATE_NET_DISCOVER_CONNECTED);
		break;
	case SCE_NET_ADHOC_DISCOVER_RESULT_CANCELED:
		change_state(STATE_NET_NONE);
		break;
	case SCE_NET_ADHOC_DISCOVER_RESULT_TRY_AGAIN:
		change_state(STATE_NET_DISCOVER_START);
		break;
	case SCE_NET_ADHOC_DISCOVER_RESULT_ABORTED_SEARCH_BY_NORMAL_RESUME:
		/* never be here in HostDiscover mode */
		break;
	default:
		
		evf &= ~EVF_ERROR;
		/*ret = utility_msgdialog_neterror(error_code);
		if (ret < 0) {
			change_state(STATE_NET_NONE);
		}
		else {
			_info.flags |= NETWORK_FLAG_PAUSE;
			change_state(STATE_NET_DISCOVER_ERROR_DIALOG);
		}*/
		change_state(STATE_NET_DISCOVER_ERROR_DIALOG);

		error_code = 0;
		break;
	}

	return 0;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::net_confirm_start(void)
{
	//int ret;

	//ret = utility_msgdialog_netconfirm();
	//if (ret == 0) {
	//	_info.flags |= NETWORK_FLAG_PAUSE;
		change_state(STATE_NET_CONFIRM);
	//}

	return 0;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::net_update(void)
{
	switch(_info.state) {
		case STATE_TOP:
			net_confirm_start();
			status = "Waiting...";
			break;
		case STATE_NET_DISCOVER_START:
			net_discover_start();
			status = "Discovering";
			break;
		case STATE_NET_DISCOVER_RUNNING:
			net_discover_running();
			break;
		case STATE_NET_DISCOVER_FINISHED:
			net_discover_finished();
			break;
		case STATE_NET_DISCOVER_CONNECTED:
			net_discover_connected();
			status = "Found";
			break;
		case STATE_NET_MATCHING:
			net_matching();
			break;
		case STATE_NET_REINIT:
			cleanUp();
			init();
			change_state(STATE_NET_NONE);
			break;
		case STATE_NET_DISCONNECT:
			net_disconnect();
			break;
		case STATE_NET_DISCONNECTING:
			check_disconnect_completed();
			break;
		case STATE_NET_RECONNECT:
			net_reconnect();
			break;
		case STATE_NET_SCAN:
			net_scan();
			status = "Scanning";
			break;
		case STATE_NET_SCANNING:
			check_scan_completed();
			//static_cast<RipOffApplication&>(getApp()).networkGameState();
			break;
		case STATE_NET_CONNECT:
			net_connect();
			status = "Connecting";
			break;
		case STATE_NET_CONNECTING:
			check_connect_completed();
			//static_cast<RipOffApplication&>(getApp()).networkGameState();
			break;
		case STATE_NET_CONNECTED:
			net_connected();
			send_recv_game_data();
			break;
		case STATE_NET_CONFIRM:
		case STATE_NET_ERROR_DIALOG:
		case STATE_NET_DISCOVER_ERROR_DIALOG:
		case STATE_NET_DISCOVER_SUCCESS_DIALOG:
		case STATE_NET_PEER_ERROR_DIALOG:
			check_dialog_completed();
			break;
		default:
			break;
	}

	/* check Wlan Switch state */	
	int switch_state = sceWlanGetSwitchState();

	switch(_info.state) {
		case STATE_NET_NONE:
			if(switch_state == SCE_WLAN_SWITCH_STATE_ON){
				/* start adhoc_discover */
				change_state(STATE_NET_DISCOVER_START);
			}
			break;
		default:
			break;
	}

	return 0;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::net_disconnect(void)
{
	if (_info.disconnect_state == STATE_NET_DISCONNECTED){
		//game_net_term();

		//TODO: END THE GAME
	}

	evf &= ~EVF_DISCONNECT;
	int ret = sceNetAdhocctlDisconnect();
	if(ret < 0){
		printf("sceNetAdhocctlDisconnect() failed. ret = 0x%x\n", ret);
	}

	change_state(STATE_NET_DISCONNECTING);

	return 0;
}

//--------------------------------------------------------------------------------
void PSPNetworkBase::Disconnect()
{
	int ret = sceNetAdhocPdpDelete(socket_id, 0);
	if(ret < 0){
		printf("sceNetAdhocPdpDelete() failed. ret = 0x%x\n", ret);
	}

	_info.disconnect_state = STATE_NET_DISCONNECTED;
	net_disconnect();
	_info.disconnect_state = STATE_TOP;

}

//--------------------------------------------------------------------------------
int 
PSPNetworkBase::check_dialog_completed(void)
{
	int ret = 0;

	//ret = utility_check_msgdialog_completed(&done_flag, &button_result);
	//if (ret < 0 || done_flag != 0) 

	switch (_info.state) {
		case STATE_NET_CONFIRM:
			_info.flags &= ~NETWORK_FLAG_PAUSE;
			change_state(STATE_NET_NONE);
			break;
		case STATE_NET_DISCOVER_SUCCESS_DIALOG:
			_info.flags &= ~NETWORK_FLAG_PAUSE;
			//game_reset();
			_info.flags |= NETWORK_FLAG_2PMODE;
			_info.disconnect_state = STATE_NET_RECONNECT;
			change_state(STATE_NET_DISCONNECT);

			break;
		case STATE_NET_DISCOVER_ERROR_DIALOG:
			_info.flags &= ~NETWORK_FLAG_PAUSE;
			change_state(STATE_NET_NONE);
			break;
		case STATE_NET_PEER_ERROR_DIALOG:
			_info.disconnect_state = STATE_NET_DISCONNECTED;
			/* fall through */
		case STATE_NET_ERROR_DIALOG:
			_info.flags &= ~NETWORK_FLAG_PAUSE;
			change_state(STATE_NET_DISCONNECT);
			break;
		default:
			break;
	}

	return ret;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::net_connect(void)
{
	int ret = 0;
	if (is_parent(&_info.local_addr, &_info.peer_info.mac_addr) == SCE_TRUE) {
		_info.flags |= NETWORK_FLAG_SERVER;
		ret = sceNetAdhocctlCreate(&_info.group_name);
	}
	else {
		_info.flags &= ~NETWORK_FLAG_SERVER;
		ret = sceNetAdhocctlJoin(&_info.scan_info);
	}

	if(ret < 0){
		//game_quit();
		change_state(STATE_NET_REINIT);
	}
	else{
		change_state(STATE_NET_CONNECTING);
	}

	return ret;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::check_connect_completed(void)
{
	int ret = 0;

	/* error check */
	//if(evf & EVF_ERROR){
	//	//game_quit();
	//	evf &= ~EVF_ERROR;
	//	ret = utility_msgdialog_neterror(error_code);
	//	if (ret < 0) {
	//		change_state(STATE_NET_NONE);
	//	}
	//	else {
	//		_info.flags |= NETWORK_FLAG_PAUSE;
	//		change_state(STATE_NET_DISCOVER_ERROR_DIALOG);
	//	}
	//	error_code = 0;
	//	goto leave;
	//}

	/* connect check */
	if (evf & EVF_CONNECT) {
		evf &= ~EVF_CONNECT;
				
		if (is_parent(&_info.local_addr, &_info.peer_info.mac_addr) == SCE_TRUE)
		{
			_info.flags |= NETWORK_FLAG_SERVER;
		}
		else
		{
			_info.flags &= ~NETWORK_FLAG_SERVER;
		}


		change_state(STATE_NET_CONNECTED);
		createSocket(&_info.local_addr);
	}

	return ret;
}

//--------------------------------------------------------------------------------
SceBool
PSPNetworkBase::is_parent(struct SceNetEtherAddr *local_addr, struct SceNetEtherAddr *peer_addr)
{
	int i;
	for (i = 0; i < SCE_NET_ETHER_ADDR_LEN; i++) {
		if (local_addr->data[i] < peer_addr->data[i]) {
			return SCE_TRUE;
		}
		else if (local_addr->data[i] > peer_addr->data[i]) {
			return SCE_FALSE;
		}
	}

	return SCE_FALSE;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::net_discover_connected(void)
{
	int ret = 0, buflen = 0;
	void *buf = NULL;

	ret = sceNetAdhocctlGetPeerList(&buflen, 0);
	if (ret < 0) {
		goto leave;
	}
	if (buflen == 0) {
		goto leave;
	}
	buf = malloc((size_t)buflen);
	if (buf == NULL) {
		goto leave;
	}
	ret = sceNetAdhocctlGetPeerList(&buflen, buf);
	if (ret < 0) {
		goto leave;
	}
	if (buflen == 0) {
		goto leave;
	}
	memcpy(&_info.peer_info, buf, sizeof(struct SceNetAdhocctlPeerInfo));

	socket_id = socket_id0 = -1;
	ret = sceKernelCreateThread("NetMatching", net_matching_thread,
			NET_MATCHING_TPL, NET_MATCHING_STACKSIZE, 0, NULL);
	if (ret < 0) {
		goto leave;
	}
	matching_tid = ret;

	ret = sceKernelStartThread(matching_tid, 0, NULL);
	if (ret < 0) {
		sceKernelDeleteThread(matching_tid);
		matching_tid = -1;
		goto leave;
	}

leave:
	if (matching_tid >= 0) {
		change_state(STATE_NET_MATCHING);
	}
	else {
		change_state(STATE_NET_DISCOVER_START);
	}
	if (buf != NULL) {
		free(buf);
		buf = NULL;
	}
	return 0;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::net_matching_thread(SceSize argSize,void *argBlock)
{
	printf("Thread start socket_id = %d, socket_id0 = %d\n", socket_id, socket_id0);

	int ret = 0, exit_status = SCE_KERNEL_EXIT_SUCCESS;
	struct SceNetEtherAddr peer_addr;
	SceUShort16 peer_port;
	SceUInt64 timeout;

	(void)(argSize);
	(void)(argBlock);

	timeout = sceKernelGetSystemTimeWide() + NET_TIMEOUT;

	ret = sceNetGetLocalEtherAddr(&_info.local_addr);
	if (ret < 0) {
		exit_status = SCE_KERNEL_EXIT_FAILURE;
		goto bad;
	}

	if (is_parent(&_info.local_addr, &_info.peer_info.mac_addr) == SCE_TRUE) {

		randomize_group_name(&_info.group_name);

		ret = sceNetAdhocPtpListen(&_info.local_addr, SERVER_PORT,
				BUFLEN, REXMT_INTERVAL, REXMT_COUNT, 1, 0);
		if (ret < 0) {
			printf("sceNetAdhocPtpListen() failed. ret = 0x%x\n", ret);
			exit_status = SCE_KERNEL_EXIT_FAILURE;
			goto bad;
		}
		socket_id0 = ret;

again:\
		if (timeout <= sceKernelGetSystemTimeWide()) {
			exit_status = SCE_KERNEL_EXIT_FAILURE;
			goto bad;
		}
		ret = sceNetAdhocPtpAccept(socket_id0, &peer_addr, &peer_port, 0, SCE_NET_ADHOC_F_NONBLOCK);
		if (ret < 0 && ret != (int)SCE_ERROR_NET_ADHOC_WOULD_BLOCK) {
			printf("sceNetAdhocPtpAccept() failed. ret = 0x%x\n", ret);
			exit_status = SCE_KERNEL_EXIT_FAILURE;
			goto bad;
		}
		if (ret == (int)SCE_ERROR_NET_ADHOC_WOULD_BLOCK) {
			sceKernelDelayThread(200*1000);
			goto again;
		}
		socket_id = ret;
		if (memcmp(&peer_addr, &_info.peer_info.mac_addr, sizeof(struct SceNetEtherAddr)) != 0) {
			sceNetAdhocPtpClose(socket_id, 0);
			socket_id = -1;
			goto again;
		}

		ret = data_send(&_info.peer_info.mac_addr, socket_id, (void *)&_info.group_name, sizeof(struct SceNetAdhocctlGroupName), timeout);
		if (ret < 0) {
			exit_status = SCE_KERNEL_EXIT_FAILURE;
			goto bad;
		}

	}
	else {
retry:
		ret = sceNetAdhocPtpOpen(&_info.local_addr, 0, &_info.peer_info.mac_addr, SERVER_PORT,
				BUFLEN, REXMT_INTERVAL, REXMT_COUNT, 0);
		if (ret < 0) {
			printf("sceNetAdhocPtpOpen() failed. ret = 0x%x\n", ret);
			exit_status = SCE_KERNEL_EXIT_FAILURE;
			goto bad;
		}
		socket_id = ret;

again2:
		if (timeout <= sceKernelGetSystemTimeWide()) {
			exit_status = SCE_KERNEL_EXIT_FAILURE;
			goto bad;
		}
		ret = sceNetAdhocPtpConnect(socket_id, 0, SCE_NET_ADHOC_F_NONBLOCK);
		if (ret < 0
			&& ret != (int)SCE_ERROR_NET_ADHOC_WOULD_BLOCK
			&& ret != (int)SCE_ERROR_NET_ADHOC_CONNECTION_REFUSED) {
			printf("sceNetAdhocPtpConnect() failed. ret = 0x%x\n", ret);
			exit_status = SCE_KERNEL_EXIT_FAILURE;
			goto bad;
		}
		if (ret == (int)SCE_ERROR_NET_ADHOC_CONNECTION_REFUSED) {
			sceNetAdhocPtpClose(socket_id, 0);
			socket_id = -1;
			sceKernelDelayThread(1*1000*1000);
			goto retry;
		}
		if (ret == (int)SCE_ERROR_NET_ADHOC_WOULD_BLOCK) {
			sceKernelDelayThread(200*1000);
			goto again2;
		}

		ret = data_recv(&_info.peer_info.mac_addr, socket_id, (void *)&_info.group_name, sizeof(struct SceNetAdhocctlGroupName), timeout);
		if (ret < 0) {
			exit_status = SCE_KERNEL_EXIT_FAILURE;
			goto bad;
		}
	}

	printf("Thread end socket_id = %d, socket_id0 = %d\n", socket_id, socket_id0);

bad:
	if (socket_id >= 0) {
		sceNetAdhocPtpClose(socket_id, 0);
		socket_id = -1;
	}
	if (socket_id0 >= 0) {
		sceNetAdhocPtpClose(socket_id0, 0);
		socket_id0 = -1;
	}

	sceNetFreeThreadinfo(sceKernelGetThreadId());

	return exit_status;
}

//--------------------------------------------------------------------------------
SceBool
is_peer_existence(struct SceNetEtherAddr *peer_addr)
{
	struct SceNetAdhocctlPeerInfo peer_info;
	int ret = sceNetAdhocctlGetPeerInfo(peer_addr, sizeof(peer_info), &peer_info);
	if (ret < 0 && ret != (int)SCE_ERROR_NET_ADHOC_NO_ENTRY) {
		printf("sceNetAdhocctlGetPeerInfo() failed. ret = 0x%x\n", ret);
		return SCE_FALSE;
	}
	else if (ret == (int)SCE_ERROR_NET_ADHOC_NO_ENTRY) {
		printf("peer has gone.\n");
		return SCE_FALSE;
	}

	return SCE_TRUE;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::randomize_group_name(struct SceNetAdhocctlGroupName *group_name)
{
	unsigned int len;

	len = get_random_num(1, 8);

	memset(group_name, 0, sizeof(struct SceNetAdhocctlGroupName));
	int i;
	for(i = 0; i < (int)len; i++){
		group_name->data[i] = get_random_num('A', 'Z');
	}
	return 0;
}

//--------------------------------------------------------------------------------
unsigned int
PSPNetworkBase::get_random_num(unsigned int min,unsigned int max)
{
	if(max == min)
		return min;

	u_int num = rand() / (RAND_MAX / ((max - min) + 1) + 1);
	num += min;
	return num;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::data_recv(struct SceNetEtherAddr *peer_addr,int id,	void *ptr,unsigned int size,SceUInt64 timeout)
{
	int ret = 0, resid, datalen;

	resid = size;
	while (resid > 0) {
		if (timeout <= sceKernelGetSystemTimeWide()) {
			return -1;
		}
		datalen = resid < BUFSIZE ? resid : BUFSIZE;
		ret = sceNetAdhocPtpRecv(id, exchange_buf, &datalen, 0, SCE_NET_ADHOC_F_NONBLOCK);
		if (ret < 0 && ret != (int)SCE_ERROR_NET_ADHOC_WOULD_BLOCK) {
			printf("sceNetAdhocPtpRecv() failed. ret = 0x%x\n", ret);
			return ret;
		}
		if (ret == (int)SCE_ERROR_NET_ADHOC_WOULD_BLOCK) {
			if (!is_peer_existence(peer_addr)) {
				return -1;
			}
			sceKernelDelayThread(200*1000);
			continue;
		}
		memcpy((char *)ptr + (size - resid), exchange_buf, datalen);
		resid -= datalen;
	}

	return 0;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::data_send(struct SceNetEtherAddr *peer_addr,int id,void *ptr,unsigned int size,	SceUInt64 timeout)
{
	int ret = 0, resid, datalen;

	resid = size;
	while (resid > 0) {
		if (timeout <= sceKernelGetSystemTimeWide()) {
			return -1;
		}
		datalen = resid < BUFSIZE ? resid : BUFSIZE;
		memcpy(exchange_buf, (char *)ptr + (size - resid), datalen);
		ret = sceNetAdhocPtpSend(id, exchange_buf, &datalen, 0, SCE_NET_ADHOC_F_NONBLOCK);

		if (ret < 0 && ret != (int)SCE_ERROR_NET_ADHOC_WOULD_BLOCK) {
			printf("sceNetAdhocPtpRecv() failed. ret = 0x%x\n", ret);
			return ret;
		}
		if (ret == (int)SCE_ERROR_NET_ADHOC_WOULD_BLOCK) {
			if (!is_peer_existence(peer_addr)) {
				return -1;
			}
			continue;
		}
		resid -= datalen;
	}

	while (true)
	{
		if (timeout <= sceKernelGetSystemTimeWide()) {
			return SCE_ERROR_NET_ADHOC_TIMEOUT;
		}
		ret = sceNetAdhocPtpFlush(id, 0, SCE_NET_ADHOC_F_NONBLOCK);
		if (ret < 0 && ret != (int)SCE_ERROR_NET_ADHOC_WOULD_BLOCK) {
			printf("sceNetAdhocPtpFlush() failed. ret = 0x%x\n", ret);
			return ret;
		}
		if (ret == (int)SCE_ERROR_NET_ADHOC_WOULD_BLOCK) {
			if (!is_peer_existence(peer_addr)) {
				return -1;
			}
			sceKernelDelayThread(200*1000);
		}
		else
		{
			break;
		}
	}

	return 0;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::check_disconnect_completed(void)
{
	if (evf & EVF_DISCONNECT) {
		evf &= ~EVF_DISCONNECT;
		change_state(_info.disconnect_state);
	}

	return 0;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::net_reconnect(void)
{
	if (is_parent(&_info.local_addr, &_info.peer_info.mac_addr) == SCE_TRUE) {
		change_state(STATE_NET_CONNECT);
	}
	else {
		change_state(STATE_NET_SCAN);
	}
	return 0;
}

int
PSPNetworkBase::net_matching(void)
{
	int ret = 0;

	ret = sceKernelGetThreadExitStatus(matching_tid);
	if (ret == (int)SCE_KERNEL_ERROR_NOT_DORMANT) {
		if(evf & EVF_ERROR){
			if(0 <= socket_id0)
				ret = sceNetAdhocSetSocketAlert(socket_id0,
				    SCE_NET_ADHOC_F_ALERTALL);
			if(0 <= socket_id)
				ret = sceNetAdhocSetSocketAlert(socket_id,
				    SCE_NET_ADHOC_F_ALERTALL);
		}
		return 0;
	}

	sceKernelDeleteThread(matching_tid);
	matching_tid = -1;

	switch (ret) {
	case SCE_KERNEL_EXIT_SUCCESS:
		///ret = utility_msgdialog_discovered();
		//if (ret < 0) {
		//	_info.disconnect_state = STATE_NET_DISCOVER_START;
		//	change_state(STATE_NET_DISCONNECT);
		//}
		//else {
			_info.flags |= NETWORK_FLAG_PAUSE;
			change_state(STATE_NET_DISCOVER_SUCCESS_DIALOG);
		//}
		break;
	case SCE_KERNEL_EXIT_FAILURE:
		/* error check */
		if(evf & EVF_ERROR){
			break;
		}

		/* fall through */
	default:
		_info.disconnect_state = STATE_NET_DISCOVER_START;
		change_state(STATE_NET_DISCONNECT);
		break;
	}

	return 0;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::net_scan(void)
{
	int ret = 0;

	evf = 0;
	error_code = 0;
	ret = sceNetAdhocctlScan();
	if (ret < 0) {
		//game_quit();
		//TODO: QUIT GAME
		change_state(STATE_NET_NONE);
	}
	else {
		change_state(STATE_NET_SCANNING);
	}

	return ret;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::check_scan_completed(void)
{
	int ret = 0, buflen = 0;
	void *buf = NULL;
	struct SceNetAdhocctlScanInfo *scan_info;

	/* error check */
	if(evf & EVF_ERROR){
		//game_quit();
		//TODO: QUIT GAME

		evf &= ~EVF_ERROR;
		//ret = utility_msgdialog_neterror(error_code);
		if (ret < 0) {
			change_state(STATE_NET_NONE);
		}
		else {
			_info.flags |= NETWORK_FLAG_PAUSE;
			change_state(STATE_NET_DISCOVER_ERROR_DIALOG);
		}
		error_code = 0;
		goto leave;
	}

	/* scan check */
	if (evf & EVF_SCAN) {
		evf &= ~EVF_SCAN;
		/* check stop request */
		if(evf & EVF_CANCEL){
			evf &= ~EVF_CANCEL;
			change_state(STATE_NET_DISCONNECTED);
			goto leave;
		}
		ret = sceNetAdhocctlGetScanInfo(&buflen, NULL);
		if (ret < 0) {
			//game_quit();
			//TODO: QUIT GAME
			change_state(STATE_NET_NONE);
			goto leave;
		}
		if (buflen == 0) {
			change_state(STATE_NET_SCAN);
			goto leave;
		}
		buf = malloc((size_t)buflen);
		if (buf == NULL) {
			//game_quit();
			//TODO: QUIT GAME
			change_state(STATE_NET_NONE);
			goto leave;
		}
		ret = sceNetAdhocctlGetScanInfo(&buflen, buf);
		if (ret < 0) {
			//game_quit();
			//TODO: QUIT GAME
			change_state(STATE_NET_NONE);
			goto leave;
		}
		if (buflen == 0) {
			change_state(STATE_NET_SCAN);
			goto leave;
		}
		for (scan_info = (struct SceNetAdhocctlScanInfo *)buf;
			scan_info != NULL; scan_info = scan_info->next) {
			if (memcmp(&_info.group_name, &scan_info->group_name, sizeof(struct SceNetAdhocctlGroupName)) == 0) {
				memcpy(&_info.scan_info, scan_info, sizeof(struct SceNetAdhocctlScanInfo));
				change_state(STATE_NET_CONNECT);
				goto leave;
			}
		}
		change_state(STATE_NET_SCAN);
	}

leave:
	if (buf != NULL) {
		free(buf);
	}

	return 0;
}

//--------------------------------------------------------------------------------
int
PSPNetworkBase::net_connected(void)
{
	int ret = 0;

	/* check stop request */
	if(evf & EVF_CANCEL){
		evf &= ~EVF_CANCEL;
		_info.disconnect_state = STATE_NET_DISCONNECTED;
		change_state(STATE_NET_DISCONNECT);
		return ret;
	}

	/* error check */
	if(evf & EVF_ERROR){
		//game_quit();
	}

	return ret;
}

//--------------------------------------------------------------------------------
bool
PSPNetworkBase::createSocket(struct SceNetEtherAddr *local_addr)
{	
	struct SceNetEtherAddr n;
	char str[sizeof("XX:XX:XX:XX:XX:XX")];

	int ret = sceNetGetLocalEtherAddr(&n);
	if(ret < 0){
		/* Error handling */
	}
	sceNetEtherNtostr(&n, str);

	printf("Local MAC Addr: %s\n", str);

	//E Create PDP socket 
	ret = sceNetAdhocPdpCreate(local_addr, PORT, RXBUFLEN, 0);
	if (ret < 0) 
	{
		printf("sceNetAdhocPdpCreate() failed. ret = 0x%x\n", ret);
		return false;
	}

	
	socket_id = ret;
	printf("Socket created. ret = 0x%x\n", ret);

	return true;
}

//--------------------------------------------------------------------------------
void
PSPNetworkBase::sendMessage(char* buffer, const int length)
{
	printf("Send message >> %s\n", buffer);
	
	struct SceNetEtherAddr addr;
	memset(addr.data, 0xff, SCE_NET_ETHER_ADDR_LEN);

	int ret = sceNetAdhocPdpSend(socket_id, &addr, PORT, buffer, length, 0, SCE_NET_ADHOC_F_NONBLOCK);

	if (ret != 0)
	{
		printf("sceNetAdhocPdpSend() failed. ret = 0x%x\n", ret);
	}
	else
	{
		printf("Message sent. ret = 0x%x\n", ret);
	}
}

//--------------------------------------------------------------------------------
void
PSPNetworkBase::recieveMessage(char* buffer, int length)
{
	struct SceNetEtherAddr addr;
	SceUShort16 port;
	while (1)
	{
		int ret = sceNetAdhocPdpRecv(socket_id, &addr, &port, buffer, &length, 0, SCE_NET_ADHOC_F_NONBLOCK);
		
		if (ret < 0)
		{
			printf("sceNetAdhocPdpRecv() failed. ret = 0x%x\n", ret);
		}

		unsigned int id;
		memcpy(&id, buffer, sizeof(unsigned int));
		if(id == 0)
		{
			ret = SCE_OK;
			break;
		}

		if (ret == (int)SCE_ERROR_NET_ADHOC_WOULD_BLOCK){
			ret = SCE_OK;
			break;
		}
	}
		
	printf("Recv message >> %s\n", buffer);
}

//--------------------------------------------------------------------------------
void 
PSPNetworkBase::send_recv_game_data()
{
	struct SceNetEtherAddr addr;

	int totalBuffer = sizeof(EntityMessage) * 40;
	char* sendBuffer = new char[totalBuffer];
	memset(sendBuffer, 0, totalBuffer);
	
	/* broadcast my data */
	memset(addr.data, 0xff, SCE_NET_ETHER_ADDR_LEN);
		
	//len = get_game_data(buf);
	//int len = sizeof(EntityMessage);

	int len = GameEngine::get()->packMessage(sendBuffer);

	if(len > totalBuffer || len > BUFFER_FRAGMENT)
	{
		printf("Overflow!");
	}

	int ret = sceNetAdhocPdpSend(socket_id, &addr, PORT, sendBuffer, len, 0, SCE_NET_ADHOC_F_NONBLOCK);
	//delete[] sendBuffer;

	if (ret != 0)
	{
		//printf("sceNetAdhocPdpSend() failed. ret = 0x%x\n", ret);
	}
	else
	{
		//printf("Message sent = %s\n", buf);
	}
	
	if (ret == (int)SCE_ERROR_NET_ADHOC_WOULD_BLOCK)
		ret = SCE_OK;


	len = totalBuffer;//sizeof(EntityMessage);
	char* recvBuffer = new char[totalBuffer];
	while(1){

		//len = RXBUFLEN;
		memset(recvBuffer, 0, totalBuffer);
	
		SceUShort16 port;
		ret = sceNetAdhocPdpRecv(socket_id, &addr, &port, recvBuffer, &len, 0, SCE_NET_ADHOC_F_NONBLOCK);
	
		if (ret != 0)
		{
			//printf("sceNetAdhocPdpRecv() failed. ret = 0x%x\n", ret);
		}

		if (ret == (int)SCE_ERROR_NET_ADHOC_WOULD_BLOCK){
			ret = SCE_OK;
			break;
		}
		if (memcmp(&_info.local_addr, &addr, SCE_NET_ETHER_ADDR_LEN) == 0)
			continue;
		if (port != PORT)
			continue;

		GameEngine::get()->updateNetworkData(recvBuffer, totalBuffer);
	}

	delete[] sendBuffer;
	delete[] recvBuffer;

	/* check timeout */
	//check_peer_existence();
}

//--------------------------------------------------------------------------------
int PSPNetworkBase::check_peer_existence(void)
{
	/*int ret;
	struct SceNetAdhocctlPeerInfo peer_info;
	u_int64 current_time;

	current_time = sceKernelGetSystemTimeWide();
	ret = sceNetAdhocctlGetPeerInfo(&scope[1].addr, sizeof(peer_info), &peer_info);

	if (ret < 0 || current_time - peer_info.last_recv >= PEER_TIMEOUT) {
		scope[1].state = FALSE;
	}
	else {
		scope[1].last_recv = peer_info.last_recv;
	}

	if((_info.flags & MOONBALL_FLAG_PEER_READY)
		&& (current_time - scope[1].last_recv >= PEER_TIMEOUT)
		&& game.state < GAME_END) {
		QuitGame();
		ret = utility_msgdialog_peererror();
		if (ret < 0) {
			change_state(STATE_NET_DISCONNECT);
		}
		else {
			_info.flags |= MOONBALL_FLAG_PAUSE;
			change_state(STATE_NET_PEER_ERROR_DIALOG);
		}
	}*/

	return 0;
}



#endif