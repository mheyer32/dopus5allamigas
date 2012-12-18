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

void config_free_functions(struct List *);
void config_free_hotkeys(struct List *list);

void __asm __saveds L_CloseButtonBank(
	register __a0 Cfg_ButtonBank *bank)
{
	if (bank)
	{
		L_FreeButtonImages(&bank->buttons);
		L_FreeMemH(bank->startmenu);
		L_FreeMemHandle(bank->memory);
		FreeVec(bank);
	}
}

void __asm __saveds L_FreeListerDef(
	register __a0 Cfg_Lister *lister)
{
	if (lister)
	{
		L_FreeMemH(lister->path);
		FreeVec(lister);
	}
}

void __asm __saveds L_FreeButton(
	register __a0 Cfg_Button *button)
{
	if (button)
	{
		Cfg_ButtonFunction *func;

		// Go through functions attached to button
		for (func=(Cfg_ButtonFunction *)button->function_list.mlh_Head;
			func->node.ln_Succ;)
		{
			Cfg_ButtonFunction *next=(Cfg_ButtonFunction *)func->node.ln_Succ;

			// Free function
			L_FreeButtonFunction(func);

			// Get next
			func=next;
		}

		// Free button
		L_FreeMemH(button);
	}
}

void __asm __saveds L_FreeFunction(
	register __a0 Cfg_Function *function)
{
	if (function)
	{
		L_FreeInstructionList(function);
		L_FreeMemH(function);
	}
}

void __asm __saveds L_FreeButtonFunction(
	register __a0 Cfg_ButtonFunction *func)
{
	if (func)
	{
		// Free names and images
		L_FreeMemH(func->node.ln_Name);
		L_FreeMemH(func->label);
		L_CloseImage(func->image);

		// Free function
		L_FreeFunction((Cfg_Function *)func);
	}
}


void __asm __saveds L_FreeButtonList(
	register __a0 struct List *list)
{
	struct Node *node,*next;

	// Free buttons
	for (node=list->lh_Head;node->ln_Succ;)
	{
		next=node->ln_Succ;
		L_FreeButton((Cfg_Button *)node);
		node=next;
	}
}

void __asm __saveds L_FreeInstruction(
	register __a0 Cfg_Instruction *ins)
{
	if (ins)
	{
		L_FreeMemH(ins->string);
		L_FreeMemH(ins);
	}
}

void __asm __saveds L_FreeButtonImages(
	register __a0 struct List *list)
{
	Cfg_Button *button;

	// Go through button list
	for (button=(Cfg_Button *)list->lh_Head;
		button->node.ln_Succ;
		button=(Cfg_Button *)button->node.ln_Succ)
	{
		Cfg_ButtonFunction *func;

		// Go through button functions	
		for (func=(Cfg_ButtonFunction *)button->function_list.mlh_Head;
			func->node.ln_Succ;
			func=(Cfg_ButtonFunction *)func->node.ln_Succ)
		{
			// Free image
			L_CloseImage(func->image);
			func->image=0;
		}
	}
}


void config_free_functions(struct List *list)
{
	Cfg_Function *node,*next;

	// Free functions
	for (node=(Cfg_Function *)list->lh_Head;node->node.ln_Succ;)
	{
		next=(Cfg_Function *)node->node.ln_Succ;
		L_FreeFunction((Cfg_Function *)node);
		node=next;
	}
}

void __asm __saveds L_FreeInstructionList(register __a0 Cfg_Function *func)
{
	Cfg_Instruction *node,*next;

	// Free instructions
	for (node=(Cfg_Instruction *)func->instructions.mlh_Head;
		node->node.mln_Succ;)
	{
		next=(Cfg_Instruction *)node->node.mln_Succ;
		L_FreeInstruction((Cfg_Instruction *)node);
		node=next;
	}
	NewList((struct List *)&func->instructions);
}

void __asm __saveds L_FreeFiletypeList(register __a0 Cfg_FiletypeList *list)
{
	struct Node *node,*next;

	if (!list || (list->flags&FTLISTF_INTERNAL))
		return;

	// Free filetypes in list
	for (node=list->filetype_list.lh_Head;node->ln_Succ;)
	{
		next=node->ln_Succ;
		L_FreeFiletype((Cfg_Filetype *)node);
		node=next;
	}

	// Free list
	L_FreeMemH(list);
}

void __asm __saveds L_FreeFiletype(register __a0 Cfg_Filetype *type)
{
	short a;

	if (!type) return;

	// Remove filetype from list
	if (type->node.ln_Succ && type->node.ln_Pred)
		Remove(&type->node);

	// Free data
	L_FreeMemH(type->recognition);
	L_FreeMemH(type->icon_path);
	if (type->actions)
	{
		for (a=0;a<16;a++)
			L_FreeMemH(type->actions[a]);
		L_FreeMemH(type->actions);
	}
	config_free_functions(&type->function_list);
	L_FreeMemH(type);
}


void config_free_hotkeys(struct List *list)
{
	struct Node *node,*next;

	// Free hotkeys
	for (node=list->lh_Head;node->ln_Succ;) {

		next=node->ln_Succ;
		L_FreeMemH(((Cfg_Hotkey *)node)->name);
		config_free_functions(&((Cfg_Hotkey *)node)->function_list);
		L_FreeMemH(node);
		node=next;
	}
}
