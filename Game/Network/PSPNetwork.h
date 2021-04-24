/* VERSION HISTORY


*/
#pragma once

#include <utility/utility_msgdialog.h>

#include <kernel.h>
#include <psptypes.h>
#include <wlan.h>
#include <pspnet.h>
#include <pspnet_error.h>
#include <pspnet_adhoc.h>
#include <pspnet_adhocctl.h>
#include <pspnet_adhoc_discover.h>

#include "foundation/Singleton.h"

//#include "utility.h"
#define LANG_SETTING    SCE_UTILITY_LANG_JAPANESE
#define BUTTON_SETTING  SCE_UTILITY_CTRL_ASSIGN_CIRCLE_IS_ENTER

#define RIPOFF_DISCOVER_TIMEOUT	(60)	/* 60sec */

#define PSPNET_POOLSIZE (128 * 1024)
#define CALLOUT_TPL 40
#define NETINTR_TPL 40
#define ADHOCCTL_TPL		48
#define ADHOCCTL_STACKSIZE 	(8*1024)

#define NET_MATCHING_TPL		48
#define NET_MATCHING_STACKSIZE	(8*1024)

#define SERVER_PORT			1
#define BUFLEN				(SCE_NET_ADHOC_PTP_MSS*4)		/* PTP_MSS x 4 */
#define REXMT_INTERVAL		(200*1000)		/* 200ms */
#define REXMT_COUNT			(300)			/* 60sec */
#define NET_TIMEOUT			(60*1000*1000)	/* 60sec */
#define BUFSIZE				(SCE_NET_ADHOC_PTP_MSS)

#define EVF_ERROR			0x0001
#define EVF_CONNECT			0x0002
#define EVF_DISCONNECT		0x0004
#define EVF_SCAN			0x0008
#define EVF_CANCEL			0x0020
#define EVF_HOSTDISCOVER	0x0040
#define EVF_WOL				0x0080
#define EVF_WOL_ABORT		0x0100

#define NETWORK_FLAG_2PMODE		0x01
#define NETWORK_FLAG_SERVER		0x02
#define NETWORK_FLAG_PEER_READY	0x04
#define NETWORK_FLAG_PAUSE			0x08


#define PORT 777
#define RXBUFLEN 1024

enum network_state {
	STATE_TOP						= 0,
	STATE_NET_NONE					= 1,
	STATE_NET_CONFIRM				= 2,
	STATE_NET_DISCOVER_START		= 3,
	STATE_NET_DISCOVER_RUNNING		= 4,
	STATE_NET_DISCOVER_FINISHED		= 5,
	STATE_NET_DISCOVER_CONNECTED	= 6,
	STATE_NET_MATCHING				= 7,
	STATE_NET_REINIT				= 8,
	STATE_NET_RECONNECT				= 9,
	STATE_NET_DISCONNECT			= 10,
	STATE_NET_DISCONNECTING			= 11,
	STATE_NET_DISCONNECTED  		= 12,
	STATE_NET_SCAN					= 13,
	STATE_NET_SCANNING				= 14,
	STATE_NET_CONNECT				= 15,
	STATE_NET_CONNECTING			= 16,
	STATE_NET_CONNECTED				= 17,
	STATE_NET_ERROR_DIALOG			= 18,
	STATE_NET_DISCOVER_ERROR_DIALOG = 19,
	STATE_NET_DISCOVER_SUCCESS_DIALOG = 20,
	STATE_NET_PEER_ERROR_DIALOG		= 21
};

struct _info {
	enum network_state state;
	int flags;
	struct SceNetEtherAddr local_addr;
	struct SceNetAdhocctlPeerInfo peer_info;
	struct SceNetAdhocctlGroupName group_name;
	struct SceNetAdhocctlScanInfo scan_info;
	enum network_state disconnect_state;
};


class PSPNetworkBase 
{
public:
	PSPNetworkBase();
	~PSPNetworkBase();

	// Initialize the PSP networking.
	bool init();

	// Release the PSP networking. 
	void cleanUp();

	static void adhocctl_handler(int event, int error, void *arg);

	static void change_state(enum network_state);

	// net update flow
	int net_update(void);

	// Net discovering process
	int net_discover_start(void);
	int net_discover_running(void);
	int net_discover_finished(void);

	// Net actual connection
	int net_confirm_start(void);
	int net_connect(void);
	int check_connect_completed(void);
	static int net_disconnect(void);	
	static int net_discover_connected(void);
	static int net_reconnect(void);
	static int net_scan(void);
	static int check_scan_completed(void);
	static int net_connected(void);
	
	static char *getLastMessage(void);
	static int net_matching(void);
	static int net_matching_thread(SceSize argSize,void *argBlock);
	static SceBool is_parent(struct SceNetEtherAddr *local_addr,struct SceNetEtherAddr *peer_addr);

	static int data_recv(struct SceNetEtherAddr *peer_addr,int id,	void *ptr,unsigned int size,SceUInt64 timeout);
	static int data_send(struct SceNetEtherAddr *peer_addr,int id,void *ptr,unsigned int size,	SceUInt64 timeout);
	static int randomize_group_name(struct SceNetAdhocctlGroupName *group_name);
	static unsigned int get_random_num(unsigned int min,unsigned int max);
	static int check_disconnect_completed(void);
	static void Disconnect();

	int check_dialog_completed(void);
	
	bool isConnectCompleted() const { return (_info.state == STATE_NET_CONNECTED); }

	static bool isHost() { return (_info.flags & NETWORK_FLAG_SERVER); }

	// Create Socket and send & recv msg
	static bool createSocket(struct SceNetEtherAddr *local_addr);
	static void send_recv_game_data();
	static void sendMessage(char* buffer, const int length);
	static void recieveMessage(char* buffer, int length);

	int check_peer_existence(void);


private:
	static int lastCode;

	static SceUtilityMsgDialogParam msgdialogParam;
	static char netconfirmStr[];
	static char discoveredStr[];
	static char peererrorStr[];

	static int handler_id;
	static int evf;
	static int error_code;
	static int matching_tid;
	static int socket_id0;
	static int socket_id;

	struct SceNetAdhocctlAdhocId;

	struct SceNetAdhocDiscoverParam;

	static char event_str[][16];

	static char* status;

	static char exchange_buf[BUFSIZE];

	static struct _info _info;

};

typedef Singleton<PSPNetworkBase> PSPNetwork;