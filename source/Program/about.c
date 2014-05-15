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
#include <proto/module.h>

// version_num is actually revision number & used elsewhere in the program
short version_num = PROG_REVISION;
char *version_string="Magellan II  "STRI(PLATFORM);

char *_version_str="\0$VER: DirectoryOpus "PROG_STRING;

// Show about requester
void show_about(struct Screen *screen,IPCData *ipc)
{
	static const char about_1[] = COPYRIGHT;
	static const char about_2[] = "Written by Jonathan Potter";

	char buf[80],*buffer;
	struct Library *ModuleBase;
#ifdef __amigaos4__
	struct ModuleIFace *IModule;
#endif
	Att_List *list;
	Att_Node *node;

	// Create list of text
	if (!(list=Att_NewList(0)))
		return;

	// Build lines
	lsprintf(buf,"%s %ld.%ld %s",(IPTR)dopus_name,PROG_VERSION,PROG_REVISION,(IPTR)version_string);
	Att_NewNode(list,buf,2,0);
	Att_NewNode(list,about_1,2,0);
	Att_NewNode(list,about_2,2,0);

	// Name of the translator
	Att_NewNode(list,GetString(&locale,MSG_TRANSLATION_BY_YOUR_NAME),3,0);

#if 0
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
#endif
	
	// Build date
#warning Put this into the catalog!
	strcpy(buf,"Build date: ");
	strcat(buf,DOPUSDATE);
	Att_NewNode(list,"",1,0);
	Att_NewNode(list,buf,1,0);
	Att_NewNode(list,"",0,0);
	
	// Link on site
	strcpy(buf,"www.dopus5.org");
	Att_NewNode(list,buf,1,0);
	Att_NewNode(list,"",0,0);
	
	
	// Try for external about library
	if ((ModuleBase=OpenLibrary("dopus5:modules/about.module",LIB_VERSION)))
	{
		#ifdef __amigaos4__
		if (!(IModule = (struct ModuleIFace *)GetInterface(ModuleBase, "main", 1, NULL)))
		{
			CloseLibrary(ModuleBase);
			goto fallback;
		}
		#endif

		short ret;

		// Show about
		ret=Module_Entry((struct List *)list,screen,ipc,&main_ipc,0,0);
		#ifdef __amigaos4__
		DropInterface((struct Interface *)IModule);
		#endif		
		CloseLibrary(ModuleBase);

		// If it displayed ok, return
		if (ret)
		{
			Att_RemList(list,0);
			return;
		}
	}

	fallback:
	// Allocate buffer
	if ((buffer=AllocVec(512,0)))
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
