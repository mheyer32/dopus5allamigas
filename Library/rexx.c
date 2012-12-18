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

#include "dopuslib.h"
#include "rexx.h"

static char *RexxMsgIdentifier="DOPUS";

// Free an ARexx message
void __asm __saveds L_FreeRexxMsgEx(register __a0 struct RexxMsg *msg)
{
	short args;

	// Need rexx library
	if (!RexxSysBase) return;

	// Get argument count
	args=msg->rm_Action&RXARGMASK;

	// If this says there are no arguments, but Arg0 is non-null, we'll free it anyway
	if (args==0 && msg->rm_Args[0]) args=1;

	// Free all arguments
	ClearRexxMsg(msg,args);

	// Is this a DOpus message?
	if (msg->rm_Node.mn_Node.ln_Name==RexxMsgIdentifier)
	{
		struct List *list;

		// Get list pointer
		if (list=(struct List *)msg->rm_avail)
		{
			struct RexxStem *node,*next;

			// Go through list
			for (node=(struct RexxStem *)list->lh_Head;
				node->rs_Node.ln_Succ;
				node=next)
			{
				// Cache next
				next=(struct RexxStem *)node->rs_Node.ln_Succ;

				// Free this node
				FreeVec(node);
			}

			// Free list
			FreeVec(list);
		}
	}

	// Delete the message
	DeleteRexxMsg(msg);
}


// Allocate an ARexx message with space for stem variables
struct RexxMsg *__asm __saveds L_CreateRexxMsgEx(
	register __a0 struct MsgPort *port,
	register __a1 UBYTE *extension,
	register __d0 UBYTE *host)
{
	struct RexxMsg *msg;
	struct List *list;

	// Need rexx library
	if (!RexxSysBase) return 0;

	// Create message
	if (!(msg=CreateRexxMsg(port,extension,host)))
		return 0;

	// Allocate list
	if (!(list=AllocVec(sizeof(struct List),MEMF_CLEAR)))
		return msg;

	// Turn message into a special Opus one
	msg->rm_Node.mn_Node.ln_Name=RexxMsgIdentifier;
	msg->rm_avail=(ULONG)list;

	// Initialise list
	NewList(list);
	
	return msg;
}


// Set variable for a REXX message
long __asm __saveds L_SetRexxVarEx(
	register __a0 struct RexxMsg *msg,
	register __a1 char *varname,
	register __d0 char *value,
	register __d1 long length)
{
	struct RexxStem *var;
	struct List *list;
	short namelen;

	// Invalid varname or message?
	if (!msg || !varname) return 10;

	// Valid value?
	if (value)
	{
		// Need string length?
		if (length==-1) length=strlen(value);
	}
	else length=0;

	// Standard ARexx message?
	if (IsRexxMsg(msg))
	{
		// Pass through to amiga.lib call
		return SetRexxVar((struct Message *)msg,varname,value,length);
	}

	// Check for valid DOpus ARexx message
	if (msg->rm_Node.mn_Node.ln_Name!=RexxMsgIdentifier) return 10;

	// Get list pointer
	if (!(list=(struct List *)msg->rm_avail)) return 10;

	// See if variable already exists
	if ((var=(struct RexxStem *)L_FindNameI(list,varname)))
	{
		// Remove and free it
		Remove((struct Node *)var);
		FreeVec(var);
	}

	// Invalid value?
	if (!value) return 0;

	// Get variable name length
	namelen=strlen(varname)+1;

	// Allocate variable
	if (!(var=AllocVec(sizeof(struct RexxStem)+namelen+length,MEMF_CLEAR)))
		return 3;

	// Initialise variable
	var->rs_Node.ln_Name=(char *)(var+1)+length;

	// Copy name and value
	strcpy(var->rs_Node.ln_Name,varname);
	strcpy(var->rs_Value,value);

	// Add to list
	AddTail(list,(struct Node *)var);

	return 0;
}


// Get variable from a REXX message
long __asm __saveds L_GetRexxVarEx(
	register __a0 struct RexxMsg *msg,
	register __a1 char *varname,
	register __a2 char **bufpointer)
{
	struct RexxStem *var;
	struct List *list;

	// Clear pointer
	if (bufpointer) *bufpointer=0;

	// Invalid pointer, varname or message?
	if (!msg || !varname || !bufpointer) return 10;

	// Standard ARexx message?
	if (IsRexxMsg(msg)) return GetRexxVar((struct Message *)msg,varname,bufpointer);

	// Check for valid DOpus ARexx message
	if (msg->rm_Node.mn_Node.ln_Name!=RexxMsgIdentifier) return 10;

	// Get list pointer
	if (!(list=(struct List *)msg->rm_avail)) return 10;

	// See if variable exists
	if ((var=(struct RexxStem *)L_FindNameI(list,varname)))
	{
		// Return pointer to value
		*bufpointer=var->rs_Value;
		return 0;
	}

	// Not found
	return 3;
}


// Allocate an ARexx message, and set arguments and stem values automatically
struct RexxMsg *__asm __saveds L_BuildRexxMsgEx(
	register __a0 struct MsgPort *port,
	register __a1 UBYTE *extension,
	register __d0 UBYTE *host,
	register __a2 struct TagItem *tags)
{
	struct RexxMsg *msg;
	struct TagItem *tag,*tstate;
	char *varname=0;

	// Create message
	if (!(msg=L_CreateRexxMsgEx(port,extension,host)))
		return 0;

	// Go through tags
	tstate=tags;
	while (tag=NextTagItem(&tstate))
	{
		// Argument string?
		if (tag->ti_Tag>=RexxTag_Arg0 &&
			tag->ti_Tag<=RexxTag_Arg15)
		{
			short arg;

			// Get argument number
			arg=tag->ti_Tag-RexxTag_Arg0;

			// Create argument string
			msg->rm_Args[arg]=CreateArgstring((UBYTE *)tag->ti_Data,strlen((char *)tag->ti_Data)+1);
		}

		// Variable name?
		else
		if (tag->ti_Tag==RexxTag_VarName)
		{
			// Store pointer to variable name
			varname=(char *)tag->ti_Data;
		}

		// Variable value?
		else
		if (tag->ti_Tag==RexxTag_VarValue)
		{
			// Got valid name pointer?
			if (varname)
			{
				// Set value
				L_SetRexxVarEx(msg,varname,(char *)tag->ti_Data,-1);
				varname=0;
			}
		}
	}

	// Return message
	return msg;
}
