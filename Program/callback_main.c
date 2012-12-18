/*

Directory Opus 5
Original APL release version 5.82
Copyright 1993-2012 Jonathan Potter & GP Software

This program is free software; you can redistribute it and/or
modify it under the terms of the AROS Public License version 1.1.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
AROS Public License for more details.

The release of Directory Opus 5 under the GPL in NO WAY affects
the existing commercial status of Directory Opus for Windows.

For more information on Directory Opus for Windows please see:

                 http://www.gpsoft.com.au

*/

#include "dopus.h"

ULONG
	HookTable[DOPUS_HOOK_COUNT]={
		(ULONG)HookCreateFileEntry,
		(ULONG)HookFileSet,
		(ULONG)HookSortFileList,
		(ULONG)HookAddFileEntry,
		(ULONG)HookResortLister,
		(ULONG)HookRefreshLister,
		(ULONG)HookLockFileList,
		(ULONG)HookUnlockFileList,
		(ULONG)HookFindFileEntry,
		(ULONG)HookSetFileComment,
		(ULONG)HookRemoveFileEntry,
		(ULONG)HookFileQuery,
		(ULONG)HookShowHelp,
		(ULONG)HookConvertEntry,
		(ULONG)HookGetLister,
		(ULONG)HookGetSource,
		(ULONG)HookNextSource,
		(ULONG)HookUnlockSource,
		(ULONG)HookGetDest,
		(ULONG)HookEndSource,
		(ULONG)HookEndDest,
		(ULONG)HookGetEntry,
		(ULONG)HookExamineEntry,
		(ULONG)HookEndEntry,
		(ULONG)HookRemoveEntry,
		(ULONG)HookEntryCount,
		(ULONG)HookReloadEntry,
		(ULONG)HookAddFile,
		(ULONG)HookDelFile,
		(ULONG)HookLoadFile,
		(ULONG)HookDoChanges,
		(ULONG)HookCheckAbort,
		(ULONG)HookGetWindow,
		(ULONG)HookGetPort,
		(ULONG)HookGetScreen,
		(ULONG)HookGetScreenData,
		(ULONG)HookFreeScreenData,
		(ULONG)HookOpenProgress,
		(ULONG)HookUpdateProgress,
		(ULONG)HookCloseProgress,
		(ULONG)HookReplaceReq,
		(ULONG)HookGetPointer,
		(ULONG)HookFreePointer,
		(ULONG)HookSendCommand,
		(ULONG)HookCheckDesktop,
		(ULONG)HookGetDesktop,
		(ULONG)HookScript,
		(ULONG)HookDesktopPopup,
		(ULONG)HookFirstEntry,
		(ULONG)HookRexxCommand,
		(ULONG)HookFileRequest,
		(ULONG)HookGetThemes,
	};


long HookInitHooks(DOpusCallbackInfo *info)
{
	ULONG *srcptr,*dstptr;
	short num;

	// Get pointer to start of function table
	srcptr=(ULONG *)HookTable;

	// Get pointer to storage space in structure
	dstptr=(ULONG *)&info->dc_CreateFileEntry;

	// Fill it out, up to count entries
	for (num=0;num<info->dc_Count;num++,srcptr++,dstptr++)
	{
		// Copy entry if valid
		if (num<DOPUS_HOOK_COUNT) *dstptr=*srcptr;

		// Just clear entry in table
		else *dstptr=0;
	}

	return (num>DOPUS_HOOK_COUNT)?DOPUS_HOOK_COUNT:num;
}


// Run a script
BOOL __asm __saveds HookScript(
	register __a0 char *name,
	register __a1 char *data)
{
	// Run the script
	return RunScript_Name(name,data);
}


// Send an ARexx command
long __asm __saveds HookRexxCommand(
	register __a0 char *command,
	register __a1 char *result,
	register __d0 long length,
	register __a2 struct MsgPort *replyport,
	register __d1 ULONG flags)
{
	struct MsgPort *rexx,*reply;
	struct RexxMsg *msg;
	long rc=-1;

	// Clear result
	if (result) *result=0;

	// Get rexx port
	if (!GUI->rexx_proc || !(rexx=(struct MsgPort *)IPCDATA(GUI->rexx_proc)))
		return -1;

	// Create reply port if needed
	if ((reply=replyport) || (reply=CreateMsgPort()))
	{
		// Create message
		if (msg=BuildRexxMsgExTags(
					reply,
					".dopus5",
					rexx->mp_Node.ln_Name,
					RexxTag_Arg0,command,
					TAG_END))
		{
			// Initialise message
			msg->rm_Action|=1|RXCOMM;
			if (result) msg->rm_Action|=RXFF_RESULT;

			// Send the message and wait for reply
			PutMsg(rexx,(struct Message *)msg);
			WaitPort(reply);
			GetMsg(reply);

			// String reply?
			if (msg->rm_Result2 && result)
				stccpy(result,(char *)msg->rm_Result2,length);
			rc=msg->rm_Result1;

			// Free message
			FreeRexxMsgEx(msg);
		}

		// Free message port
		if (reply!=replyport) DeleteMsgPort(reply);
	}

	return rc;
}


// Request a file
long __asm __saveds HookFileRequest(
	register __a0 struct Window *parent,
	register __a1 char *title,
	register __a2 char *initial_path,
	register __a3 char *pathname,
	register __d0 ULONG flags,
	register __d1 char *pattern)
{
	return request_file(parent,title,pathname,initial_path,flags,pattern);
}
