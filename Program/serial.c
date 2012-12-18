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
#include "dopusmod:modules.h"

extern short version_num;
extern char *version_string;

// Show about requester
void show_about(struct Screen *screen,IPCData *ipc)
{
	char buf[80],*buffer;
	struct Library *ModuleBase;
	Att_List *list;
	Att_Node *node;

	// Create list of text
	if (!(list=Att_NewList(0)))
		return;

	// Build lines
	lsprintf(buf,"%s %ld.%ld %s",dopus_name,5,version_num,version_string);
	Att_NewNode(list,buf,2,0);
	Att_NewNode(list,about_1,2,0);
	Att_NewNode(list,about_2,2,0);

	// Name of the translator
	Att_NewNode(list,GetString(&locale,MSG_TRANSLATION_BY_YOUR_NAME),3,0);

	// Registered?
	if (GUI->rego.name[0] &&
		GUI->rego.serial_number[0] &&
		atoi(GUI->rego.serial_number)!=(ULONG)GUI->backdrop)
	{
		Att_NewNode(list,GetString(&locale,MSG_REGISTERED_TO),1,0);
		Att_NewNode(list,"",1,0);
		Att_NewNode(list,GUI->rego.name,1,0);
		if (GUI->rego.company[0]) Att_NewNode(list,GUI->rego.company,1,0);
		if (GUI->rego.address1[0]) Att_NewNode(list,GUI->rego.address1,1,0);
		if (GUI->rego.address2[0]) Att_NewNode(list,GUI->rego.address2,1,0);
		if (GUI->rego.address3[0]) Att_NewNode(list,GUI->rego.address3,1,0);
		Att_NewNode(list,"",1,0);
		strcpy(buf,GetString(&locale,MSG_SERIAL_NUMBER));
		strcat(buf,GUI->rego.serial_number);
		Att_NewNode(list,buf,0,0);
	}

	// Unregistered
	else
	{
		Att_NewNode(list,"",1,0);
		Att_NewNode(list,GetString(&locale,MSG_UNREGISTERED),1,0);
		Att_NewNode(list,"",0,0);
	}

	// Try for external about library
	if ((ModuleBase=OpenLibrary("dopus5:modules/about.module",0)))
	{
		short ret;

		// Show about
		ret=Module_Entry((struct List *)list,screen,ipc,&main_ipc,0,0);
		CloseLibrary(ModuleBase);

		// If it displayed ok, return
		if (ret)
		{
			Att_RemList(list,0);
			return;
		}
	}

	// Allocate buffer
	if (buffer=AllocVec(512,0))
	{
		// Clear buffer
		buffer[0]=0;

		// Build about text
		for (node=(Att_Node *)list->list.lh_Head;
			node->node.ln_Succ;
			node=(Att_Node *)node->node.ln_Succ)
		{
			// Skip?
			if (node->data==3) continue;

			// Add to string
			strcat(buffer,node->node.ln_Name);
			if (node->data>0)
			{
				strcat(buffer,(node->data==2)?"\n\n":"\n");
			}
		}

		// Display about text
		super_request_args(
			screen,
			buffer,
			SRF_SCREEN_PARENT|SRF_IPC,
			ipc,
			GetString(&locale,MSG_OKAY),0);

		// Free buffer
		FreeVec(buffer);
	}

	// Free list
	Att_RemList(list,0);
}


BOOL __asm __saveds rego_callback_2(
	register __a0 char *name,
	register __a1 rego_data *dest,
	register __a2 rego_data *source,
	register __a3 unsigned long **zero,
	register __d0 unsigned long checksum)
{
	// Clear pointer
	*zero=0;

	// Copy source to dest
	CopyMem((char *)source,(char *)dest,sizeof(rego_data));

	// Fix screen pointer (set to 1 earlier to crash if register.module not called)
	GUI->screen=0;
	return 1;

/*
	unsigned long sum;

	// Clear pointer
	*zero=(unsigned long *)(~checksum+(sum=(~ChecksumFile(name,22091973))+1)+1);

	// Checksum file
	if (sum==checksum)
	{
		// Copy source to dest
		*dest=*source;
		GUI->screen=(struct Screen *)*zero;
		return 1;
	}

	return 0;
*/
}
