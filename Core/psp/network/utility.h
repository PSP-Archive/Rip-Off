/* SCE CONFIDENTIAL
 PSP(TM) Programmer Tool Runtime Library Release 5.5.0
 *
 *      Copyright (C) 2005 Sony Computer Entertainment Inc.
 *                        All Rights Reserved.
 *
 */

#include <kernel.h>
#include <utility/utility_msgdialog.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "moonball.h"

static SceUtilityMsgDialogParam msgdialogParam;

static char netconfirmStr[] = "Turn on WLAN switch to search a challenger. If you'd like to play 1P mode, turn off WLAN switch.";
static char discoveredStr[] = "Here comes a challenger !\n";
static char peererrorStr[] = "The peer has disappeared.";

int
utility_msgdialog_netconfirm(
	void
	)
{
	memset(&msgdialogParam, 0x00, sizeof(SceUtilityMsgDialogParam));
	msgdialogParam.base.size = sizeof(SceUtilityMsgDialogParam);
	msgdialogParam.base.ctrl_assign = BUTTON_SETTING;
	msgdialogParam.base.message_lang = LANG_SETTING;
	msgdialogParam.base.main_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY + 1;
	msgdialogParam.base.sub_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY + 3;
	msgdialogParam.base.font_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY + 2;
	msgdialogParam.base.sound_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY;
	memcpy(msgdialogParam.msgString, netconfirmStr, strlen(netconfirmStr));
	msgdialogParam.type = SCE_UTILITY_MSGDIALOG_TYPE_STRING;
	msgdialogParam.optionType = SCE_UTILITY_MSGDIALOG_DIALOG_TYPE_NORMAL;

	int ret = sceUtilityMsgDialogInitStart(&msgdialogParam);
	if(ret){
		printf("sceMsgDialogDialogInit() failed. ret = 0x%x\n", ret );
	}

	return ret;
}

int
utility_msgdialog_neterror(
	int error_code
	)
{
	memset(&msgdialogParam, 0x00, sizeof(SceUtilityMsgDialogParam));
	msgdialogParam.base.size = sizeof(SceUtilityMsgDialogParam);
	msgdialogParam.base.ctrl_assign = BUTTON_SETTING;
	msgdialogParam.base.message_lang = LANG_SETTING;
	msgdialogParam.base.main_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY + 1;
	msgdialogParam.base.sub_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY + 3;
	msgdialogParam.base.font_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY + 2;
	msgdialogParam.base.sound_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY;
	msgdialogParam.errorNum = error_code;
	msgdialogParam.type = SCE_UTILITY_MSGDIALOG_TYPE_NUMBER;

	int ret = sceUtilityMsgDialogInitStart(&msgdialogParam);
	if(ret){
		printf("sceMsgDialogDialogInit() failed. ret = 0x%x\n", ret );
	}

	return ret;
}

int
utility_msgdialog_discovered(
	void
	)
{
	memset(&msgdialogParam, 0x00, sizeof(SceUtilityMsgDialogParam));
	msgdialogParam.base.size = sizeof(SceUtilityMsgDialogParam);
	msgdialogParam.base.ctrl_assign = BUTTON_SETTING;
	msgdialogParam.base.message_lang = LANG_SETTING;
	msgdialogParam.base.main_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY + 1;
	msgdialogParam.base.sub_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY + 3;
	msgdialogParam.base.font_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY + 2;
	msgdialogParam.base.sound_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY;
	memcpy(msgdialogParam.msgString, discoveredStr, strlen(discoveredStr));
	memcpy(msgdialogParam.msgString + strlen(msgdialogParam.msgString),
		_info.peer_info.nickname.data, strlen(_info.peer_info.nickname.data));

	msgdialogParam.type = SCE_UTILITY_MSGDIALOG_TYPE_STRING;
	msgdialogParam.optionType = SCE_UTILITY_MSGDIALOG_DIALOG_TYPE_NORMAL;

	int ret = sceUtilityMsgDialogInitStart(&msgdialogParam);
	if(ret){
		printf("sceMsgDialogDialogInit() failed. ret = 0x%x\n", ret );
	}

	return ret;
}

int
utility_msgdialog_peererror(
	void
	)
{
	memset(&msgdialogParam, 0x00, sizeof(SceUtilityMsgDialogParam));
	msgdialogParam.base.size = sizeof(SceUtilityMsgDialogParam);
	msgdialogParam.base.ctrl_assign = BUTTON_SETTING;
	msgdialogParam.base.message_lang = LANG_SETTING;
	msgdialogParam.base.main_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY + 1;
	msgdialogParam.base.sub_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY + 3;
	msgdialogParam.base.font_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY + 2;
	msgdialogParam.base.sound_thread_priority = SCE_KERNEL_USER_HIGHEST_PRIORITY;
	memcpy(msgdialogParam.msgString, peererrorStr, strlen(peererrorStr));

	msgdialogParam.type = SCE_UTILITY_MSGDIALOG_TYPE_STRING;
	msgdialogParam.optionType = SCE_UTILITY_MSGDIALOG_DIALOG_TYPE_ERROR;

	int ret = sceUtilityMsgDialogInitStart(&msgdialogParam);
	if(ret){
		printf("sceMsgDialogDialogInit() failed. ret = 0x%x\n", ret );
	}

	return ret;
}

int
utility_update_msgdialog(
	void
	)
{
	int ret=0;
	int status = sceUtilityMsgDialogGetStatus();

	switch(status){
	case SCE_UTILITY_COMMON_STATUS_RUNNING:
		ret = sceUtilityMsgDialogUpdate(1);
		if(ret < 0)
			printf("sceUtilityMsgDialogUpdate() failed. ret = 0x%x\n", ret);
		break;
	default:
		break;
	}

	return ret;
}

int
utility_check_msgdialog_completed(
	int *done_flag,
	int *button_result
	)
{
	int ret = 0, status;

	ret = sceUtilityMsgDialogGetStatus();
	if(ret < 0)
		goto error;
	status = ret;

	switch(status){
	case SCE_UTILITY_COMMON_STATUS_FINISHED:
		ret = sceUtilityMsgDialogShutdownStart();
		if(ret < 0)
			printf("sceUtilityMsgDialogShutdownStart() failed. ret = 0x%x\n", ret);
		break;
	case SCE_UTILITY_COMMON_STATUS_NONE:
		if(msgdialogParam.base.result == 0){
			*done_flag = 1;
			*button_result = msgdialogParam.buttonResult;
		}
		else{
			*done_flag = -1;
		}
		break;
	default:
		break;
	}

error:
	return ret;
}
