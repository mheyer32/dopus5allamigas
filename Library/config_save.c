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
#include "config.h"
#include "dopusprog:dopus_config.h"

write_string(struct _IFFHandle *iff,char *string);
write_button_list(struct _IFFHandle *iff,struct List *list,long flags);
write_function_list(struct _IFFHandle *iff,struct List *list);

__asm __saveds L_SaveSettings(
	register __a0 CFG_SETS *settings,
	register __a1 char *name,
	register __a6 struct MyLibrary *libbase)
{
	struct _IFFHandle *iff;
	int success=0;

	// Check valid config and name
	if (!settings || !name || !name[0]) return -1;

	// Try to open file to write
	if (iff=L_IFFOpen(name,MODE_NEWFILE,ID_OPUS))
	{
		char buf[40];

		// Write header chunk
		if (L_IFFWriteChunk(iff,(char *)settings,ID_SETS,sizeof(CFG_SETS)))
		{
			// Succeeded
			success=1;

			// Write icons?
			if ((GetVar("dopus/dopus",buf,sizeof(buf),GVF_GLOBAL_ONLY)>0) &&
				strstr(buf,"-icons-"))
			{
				// Write icon file
				L_WriteFileIcon("dopus5:icons/Settings",name,libbase);
			}
		}
	}

	if (!success) success=IoErr();
	else success=0;

	L_IFFClose(iff);

	return success;
}


__asm __saveds L_SaveListerDef(
	register __a0 struct _IFFHandle *iff,
	register __a1 Cfg_Lister *lister)
{
	if (!iff || !lister) return 0;

	// Write lister information
	if (!(L_IFFPushChunk(iff,ID_LSTR)) ||
		!(L_IFFWriteChunkBytes(iff,(char *)&lister->lister,sizeof(CFG_LSTR))))
		return 0;

	// Write lister path
	if (lister->path && lister->path[0] &&
		!(write_string(iff,lister->path))) return 0;

	// Pop chunk
	return L_IFFPopChunk(iff);
}


__asm __saveds L_SaveButtonBank(
	register __a0 Cfg_ButtonBank *bank,
	register __a1 char *name,
	register __a6 struct MyLibrary *libbase)
{
	struct _IFFHandle *iff;
	short success=0;

	// Check valid bank and name
	if (!bank || !name || !name[0]) return -1;
	
	// Try to open file to write
	while (iff=L_IFFOpen(name,MODE_NEWFILE,ID_OPUS))
	{
		char buf[40];

		// Clear change flag
		bank->window.flags&=~BTNWF_CHANGED;

		// Check columns/rows for zero
		if (bank->window.columns==0)
			bank->window.columns=1;
		if (bank->window.rows==0)
			bank->window.rows=1;

		// Get bank path name
		if (!(NameFromFH(L_FHFromBuf(L_IFFFileHandle(iff)),bank->path,256)))
			strcpy(bank->path,name);

		// Write header chunk
		if (!(L_IFFWriteChunk(iff,(char *)&bank->window,ID_BTNW,sizeof(CFG_BTNW))))
			break;

		// Write background picture
		if (bank->backpic[0] &&
			!(L_IFFWriteChunk(iff,bank->backpic,ID_BPIC,strlen(bank->backpic)+1)))
			break;

		// Start menu?
		if (bank->startmenu)
		{
			// Write STRT chunk
			bank->startmenu->flags|=STRTF_VERSION2;
			if (!(L_IFFWriteChunk(iff,(char *)bank->startmenu,ID_STRT,sizeof(CFG_STRT))))
				break;
		}

		// Write button list
		if (!(write_button_list(iff,&bank->buttons,bank->window.flags)))
			break;

		// Succeeded
		success=1;

		// Write icons?
		if ((GetVar("dopus/dopus",buf,sizeof(buf),GVF_GLOBAL_ONLY)>0) &&
			strstr(buf,"-icons-"))
		{
			// Write icon file
			L_WriteFileIcon("dopus5:icons/Buttons",name,libbase);
		}
		break;
	}

	if (!success) success=IoErr();
	else success=0;

	L_IFFClose(iff);

	return success;
}


__asm __saveds L_SaveFiletypeList(
	register __a0 Cfg_FiletypeList *list,
	register __a1 char *name,
	register __a6 struct MyLibrary *libbase)
{
	struct _IFFHandle *iff;
	Cfg_Filetype *type;
	int success=0;

	// Check valid list and name
	if (!list || list->flags&FTLISTF_INTERNAL || !name || !name[0]) return -1;

	// Try to open file to write
	while (iff=L_IFFOpen(name,MODE_NEWFILE,ID_OPUS))
	{
		char buf[40];

		// Go through filetypes in list
		for (type=(Cfg_Filetype *)list->filetype_list.lh_Head;
			type->node.ln_Succ;
			type=(Cfg_Filetype *)type->node.ln_Succ)
		{
			short a;

			// Write filetype data
			if (!(L_IFFPushChunk(iff,ID_TYPE)) ||
				!(L_IFFWriteChunkBytes(iff,(char *)&type->type,sizeof(CFG_TYPE))))
				break;

			// Write recognition and icon path
			if (!(write_string(iff,type->recognition)) ||
				!(write_string(iff,type->icon_path)))
				break;

			// Write actions
			for (a=0;a<16;a++)
			{
				if (!(write_string(iff,(type->actions)?type->actions[a]:0)))
					break;
			}
			if (a<type->type.count || !(L_IFFPopChunk(iff))) break;

			// Write function list
			if (!(write_function_list(iff,&type->function_list)))
				break;
		}

		// Failure?
		if (type->node.ln_Succ) break;

		// Succeeded
		success=1;

		// Write icons?
		if ((GetVar("dopus/dopus",buf,sizeof(buf),GVF_GLOBAL_ONLY)>0) &&
			strstr(buf,"-icons-"))
		{
			// Write icon file
			L_WriteFileIcon("dopus5:icons/Filetype",name,libbase);
		}
		break;
	}

	L_IFFClose(iff);

	if (success) return 0;
	return IoErr();
}


__asm __saveds L_SaveButton(
	register __a0 struct _IFFHandle *iff,
	register __a1 Cfg_Button *button)
{
	Cfg_ButtonFunction *func;

	// Count number of functions
	button->button.count=L_Att_NodeCount((Att_List *)&button->function_list);

	// Set "new style" flag
	button->button.flags|=BUTNF_NEW_FORMAT;

	// Write button data
	if (!(L_IFFPushChunk(iff,ID_BUTN)) ||
		!(L_IFFWriteChunkBytes(iff,(char *)&button->button,sizeof(CFG_BUTN))))
		return 0;

	// Go through button functions
	for (func=(Cfg_ButtonFunction *)button->function_list.mlh_Head;
		func->node.ln_Succ;
		func=(Cfg_ButtonFunction *)func->node.ln_Succ)
	{
		// Write label
		if (!(write_string(iff,func->label))) break;

		// Is the name the same as the label?
		if (!func->node.ln_Name ||
			(func->label && strcmp(func->label,func->node.ln_Name)==0 && *func->label))
		{
			char special[2];

			// Special marker
			special[0]=1;
			special[1]=0;
			if (!(write_string(iff,special))) break;
		}
		else if (!(write_string(iff,func->node.ln_Name))) break;
	}

	// Failed?
	if (func->node.ln_Succ || !(L_IFFPopChunk(iff))) return 0;

	// Write functions
	return write_function_list(iff,(struct List *)&button->function_list);
}


write_string(struct _IFFHandle *iff,char *string)
{
	int len;

	if (!string) string="";
	len=strlen(string)+1;
	return L_IFFWriteChunkBytes(iff,string,len);
}

write_button_list(struct _IFFHandle *iff,struct List *list,long flags)
{
	Cfg_Button *button;

	// Go through button list
	for (button=(Cfg_Button *)list->lh_Head;
		button->node.ln_Succ;
		button=(Cfg_Button *)button->node.ln_Succ)
	{
		// Write button
		if (!(L_SaveButton(iff,button)))
			break;
	}

	// Fail?
	if (button->node.ln_Succ) return 0;
	return 1;
}

write_function_list(struct _IFFHandle *iff,struct List *list)
{
	Cfg_Function *function;

	// Go through function list
	for (function=(Cfg_Function *)list->lh_Head;
		function->node.ln_Succ;
		function=(Cfg_Function *)function->node.ln_Succ)
	{
		// Write function data
		if (!(L_SaveFunction(iff,function)))
			break;
	}

	// Fail?
	if (function->node.ln_Succ) return 0;
	return 1;
}

__asm __saveds L_SaveFunction(
	register __a0 struct _IFFHandle *iff,
	register __a1 Cfg_Function *function)
{
	Cfg_Instruction *ins;

	if (!(L_IFFPushChunk(iff,ID_FUNC)) ||
		!(L_IFFWriteChunkBytes(iff,(char *)&function->function,sizeof(CFG_FUNC))))
		return 0;

	// Go through instruction list
	for (ins=(Cfg_Instruction *)function->instructions.mlh_Head;
		ins->node.mln_Succ;
		ins=(Cfg_Instruction *)ins->node.mln_Succ)
	{
		// Write function string
		if (!(write_string(iff,ins->string)) ||
			!(L_IFFWriteChunkBytes(iff,(char *)&ins->type,sizeof(short))))
			return 0;
	}

	// Fail?
	if (ins->node.mln_Succ || !(L_IFFPopChunk(iff)))
		return 0;

	return 1;
}
