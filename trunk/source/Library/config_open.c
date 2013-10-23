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
#include <Program/dopus_config.h>

#pragma pack(2)

typedef struct {
	char				*buffer;
	char				*pointer;
	int					size;
	short				error;
} string_handle;

#pragma pack()


void init_config_string(struct _IFFHandle *iff,string_handle *handle);
char *read_config_string(APTR memory,string_handle *handle);
short read_config_short(string_handle *handle);
void free_config_string(string_handle *handle);
char *copy_string(APTR,char *);
void dump_button_info(Cfg_ButtonBank *);
void env_read_open_bank(APTR,struct OpenEnvironmentData *,ULONG);
void env_read_open_lister(APTR,struct OpenEnvironmentData *,ULONG);

short LIBFUNC L_ReadSettings(
	REG(a0, CFG_SETS *settings),
	REG(a1, char *name))
{
	struct _IFFHandle *iff;
	short success=READCFG_FAIL;

	// Try to open file to read
	if ((iff=L_IFFOpen(name,IFF_READ,ID_OPUS)))
	{
		ULONG chunk;
		BOOL ok=0;

		// Got file
		success=READCFG_OK;

		// Parse file
		while ((chunk=L_IFFNextChunk(iff,0)))
		{
			// Look at chunk type
			switch (chunk)
			{
				// Settings
				case ID_SETS:
					{
						short size;

						// Right type of file at least
						ok=1;

						// Get size to read
						size=L_IFFChunkSize(iff);
						if (size>sizeof(CFG_SETS)) size=sizeof(CFG_SETS);

						// Read info
						if ((L_IFFReadChunkBytes(iff,settings,size))!=size)
							success=READCFG_FAIL;
#ifdef __AROS__
						else
						{
							settings->copy_flags = AROS_BE2LONG(settings->copy_flags);
							settings->delete_flags = AROS_BE2LONG(settings->delete_flags);
							settings->error_flags = AROS_BE2LONG(settings->error_flags);
							settings->general_flags = AROS_BE2LONG(settings->general_flags);
							settings->icon_flags = AROS_BE2LONG(settings->icon_flags);
							settings->replace_method = AROS_BE2WORD(settings->replace_method);
							settings->replace_flags = AROS_BE2WORD(settings->replace_flags);
							settings->update_flags = AROS_BE2LONG(settings->update_flags);
							settings->dir_flags = AROS_BE2LONG(settings->dir_flags);
							settings->view_flags = AROS_BE2LONG(settings->view_flags);
							settings->max_buffer_count = AROS_BE2WORD(settings->max_buffer_count);
							settings->date_format = AROS_BE2WORD(settings->date_format);
							settings->date_flags = AROS_BE2WORD(settings->date_flags);
							settings->pop_code = AROS_BE2WORD(settings->pop_code);
							settings->pop_qual = AROS_BE2WORD(settings->pop_qual);
							settings->pop_qual_mask = AROS_BE2WORD(settings->pop_qual_mask);
							settings->pop_qual_same = AROS_BE2WORD(settings->pop_qual_same);
							settings->popup_delay = AROS_BE2WORD(settings->popup_delay);
							settings->max_openwith = AROS_BE2WORD(settings->max_openwith);
							settings->command_line_length = AROS_BE2WORD(settings->command_line_length);
							settings->max_filename = AROS_BE2WORD(settings->max_filename);
							settings->flags = AROS_BE2LONG(settings->flags);
						}
#endif
					}
					break;
			}
		}

		// Close file
		L_IFFClose(iff);

		// Wrong type of file?
		if (success==READCFG_OK && !ok)
			success=READCFG_WRONG;
	}

	// Wrong type?
	else
	if (IoErr()==ERROR_OBJECT_WRONG_TYPE) success=READCFG_WRONG;

	return success;
}


// Read a lister definition
Cfg_Lister *LIBFUNC L_ReadListerDef(
	REG(a0, struct _IFFHandle *iff),
	REG(d0, ULONG id))
{
	Cfg_Lister *lister;

	// Allocate lister structure
	if ((lister=L_NewLister(0)))
	{
		string_handle handle;
		CFG_DLST old;

		// Old style?
		if (id==ID_DLST)
		{
			// Read lister data
			L_IFFReadChunkBytes(iff,&old,sizeof(CFG_DLST));

			// Convert to new
			lister->lister.pos[0]=old.pos;
			lister->lister.pos[1]=old.pos;
			lister->lister.format=old.format;
			lister->lister.flags=old.flags;
			lister->lister.icon_x=NO_ICON_POSITION;
			lister->lister.icon_y=NO_ICON_POSITION;
		}

		// Read lister data
		else
		{
			L_IFFReadChunkBytes(iff,&lister->lister,sizeof(CFG_LSTR));
#ifdef __AROS__
			lister->lister.icon_x = AROS_BE2LONG(lister->lister.icon_x);
			lister->lister.icon_y = AROS_BE2LONG(lister->lister.icon_y);
#endif
		}

#ifdef __AROS__
		lister->lister.pos[0].Left = AROS_BE2WORD(lister->lister.pos[0].Left);
		lister->lister.pos[0].Top = AROS_BE2WORD(lister->lister.pos[0].Top);
		lister->lister.pos[0].Width = AROS_BE2WORD(lister->lister.pos[0].Width);
		lister->lister.pos[0].Height = AROS_BE2WORD(lister->lister.pos[0].Height);
		lister->lister.pos[1].Left = AROS_BE2WORD(lister->lister.pos[1].Left);
		lister->lister.pos[1].Top = AROS_BE2WORD(lister->lister.pos[1].Top);
		lister->lister.pos[1].Width = AROS_BE2WORD(lister->lister.pos[1].Width);
		lister->lister.pos[1].Height = AROS_BE2WORD(lister->lister.pos[1].Height);
		lister->lister.flags = AROS_BE2LONG(lister->lister.flags);
#endif

		// Read lister path
		init_config_string(iff,&handle);
		lister->path=read_config_string(0,&handle);
		free_config_string(&handle);
	}

	return lister;
}


// Read a button bank
Cfg_ButtonBank *LIBFUNC L_OpenButtonBank(
	REG(a0, char *name))
{
	Cfg_ButtonBank *current_bank=0;
	struct _IFFHandle *iff;
	BPTR lock,old=0;
	char *name_ptr=0;
	BOOL ok=0;

	// See if file exists as is
	if ((lock=Lock(name,ACCESS_READ)))
	{
		D_S(struct FileInfoBlock,fib)

		// Examine it
		Examine(lock,fib);
		UnLock(lock);

		// Check it's a file
		if (fib->fib_DirEntryType<0)
		{
			// It does
			name_ptr=name;
			ok=1;
		}
		lock=0;
	}

	// It doesn't
	if (!ok)
	{
		// Get filename only
		name_ptr=FilePart(name);

		// See if it's in the buttons drawer
		if ((lock=Lock("dopus5:buttons",ACCESS_READ)))
		{
			BPTR test;

			// Change directory
			old=CurrentDir(lock);

			// See if file is in there
			if ((test=Lock(name_ptr,ACCESS_READ)))
			{
				// It is
				UnLock(test);
			}

			// It's not in there
			else
			{
				// Restore directory
				CurrentDir(old);
				UnLock(lock);
				lock=0;
				name_ptr=0;
			}
		}
		else name_ptr=0;
	}

	// Try to open file to read
	if (name_ptr && (iff=L_IFFOpen(name_ptr,IFF_READ,ID_OPUS)))
	{
		APTR file;
		Cfg_Button *current_button;
		Cfg_ButtonFunction *current_func=0;
		ULONG chunk;

		// Get file handle
		file=L_IFFFileHandle(iff);

		// Parse file
		while ((chunk=L_IFFNextChunk(iff,0)))
		{
			// Look at chunk type
			switch (chunk)
			{
				// Window definition
				case ID_BTNW:

					// Allocate button bank
					if ((current_bank=L_NewButtonBank(0,0)))
					{
						// Get bank path name
						if (!(NameFromFH(L_FHFromBuf(file),current_bank->path,256)))
							strcpy(current_bank->path,name);

						// Read bank data
						L_IFFReadChunkBytes(iff,&current_bank->window,sizeof(CFG_BTNW));

#ifdef __AROS__
						current_bank->window.pos.Left = AROS_BE2WORD(current_bank->window.pos.Left);
						current_bank->window.pos.Top = AROS_BE2WORD(current_bank->window.pos.Top);
						current_bank->window.pos.Width = AROS_BE2WORD(current_bank->window.pos.Width);
						current_bank->window.pos.Height = AROS_BE2WORD(current_bank->window.pos.Height);
						current_bank->window.columns = AROS_BE2WORD(current_bank->window.columns);
						current_bank->window.rows = AROS_BE2WORD(current_bank->window.rows);
						current_bank->window.flags = AROS_BE2LONG(current_bank->window.flags);
#endif

						// Clear 'toolbar' flag
						current_bank->window.flags&=~BTNWF_TOOLBAR;
					}
					break;

				// Background picture
				case ID_BPIC:
					if (current_bank)
						L_IFFReadChunkBytes(iff,current_bank->backpic,sizeof(current_bank->backpic));
					break;

				// Button definition
				case ID_BUTN:

					// Do we have a current bank?
					if (!current_bank) break;

					// Read button
					if ((current_button=L_ReadButton(iff,current_bank->memory)))
					{
						// Add to button list
						AddTail(&current_bank->buttons,&current_button->node);

						// Get first function pointer
						current_func=(Cfg_ButtonFunction *)current_button->function_list.mlh_Head;
					}
					break;

				// Function definition
				case ID_FUNC:

					// Do we have something to read this in to?
					if (!current_func || !current_func->node.ln_Succ) break;

					// Read function
					L_ReadFunction(iff,current_bank->memory,0,(Cfg_Function *)current_func);

					// Get next function
					current_func=(Cfg_ButtonFunction *)current_func->node.ln_Succ;
					break;

				// Start menu info
				case ID_STRT:

					// Allocate information
					if ((current_bank->startmenu=L_AllocMemH(current_bank->memory,sizeof(CFG_STRT))))
					{
						// Read data
						L_IFFReadChunkBytes(iff,current_bank->startmenu,sizeof(CFG_STRT));

#ifdef __AROS__
						current_bank->startmenu->flags = AROS_BE2LONG(current_bank->startmenu->flags);
						current_bank->startmenu->fpen = AROS_BE2WORD(current_bank->startmenu->fpen);
						current_bank->startmenu->label_fpen = AROS_BE2WORD(current_bank->startmenu->label_fpen);
						current_bank->startmenu->sel_fpen = AROS_BE2WORD(current_bank->startmenu->sel_fpen);
						current_bank->startmenu->label_fontsize = AROS_BE2WORD(current_bank->startmenu->label_fontsize);
#endif
					}
					break;
			}
		}

		L_IFFClose(iff);
	}

	// Directory to unlock?
	if (lock)
	{
		// Restore cd
		CurrentDir(old);
		UnLock(lock);
	}

	// A version 1 startmenu that needs to be converted?
	if (current_bank && current_bank->startmenu && !(current_bank->startmenu->flags&STRTF_VERSION2))
	{
		L_ConvertStartMenu(current_bank);
		current_bank->startmenu->fpen=1;
		current_bank->startmenu->label_fpen=1;
		current_bank->startmenu->sel_fpen=2;
	}
	return current_bank;
}


// Read a button
Cfg_Button *LIBFUNC L_ReadButton(
	REG(a0, struct _IFFHandle *iff),
	REG(a1, APTR memory))
{
	Cfg_Button *button;

	// Allocate a new button
	if ((button=L_NewButton(memory)))
	{
		string_handle handle;
		short count,a;
		char *name,*label;

		// Read button data
		L_IFFReadChunkBytes(iff,&button->button,sizeof(CFG_BUTN));

#ifdef __AROS__
		button->button.flags = AROS_BE2LONG(button->button.flags);
		button->button.count = AROS_BE2WORD(button->button.count);
#endif

		// Old style button?
		if (!(button->button.flags&BUTNF_NEW_FORMAT)) count=3;
		else count=button->button.count;

		// Read button names
		init_config_string(iff,&handle);
		for (a=0;a<count;a++)
		{
			Cfg_ButtonFunction *func;

			// Read name
			if (!(name=read_config_string(memory,&handle)))
				break;

			// New style button?
			if (button->button.flags&BUTNF_NEW_FORMAT)
			{
				// Read label
				label=read_config_string(memory,&handle);

				// Special marker?
				if (label && label[0]==1 && label[1]==0)
				{
					// Free marker
					L_FreeMemH(label);

					// Copy the name
					label=copy_string(memory,name);
				}
			}

			// Otherwise, is button graphical?
			else
			if (button->button.flags&BUTNF_GRAPHIC)
			{
				char filename[40];
				char *ptr;

				// Use filename as label
				stccpy(filename,FilePart(name),39);

				// Strip any suffix (.small for instance)
				if ((ptr=strchr(filename,'.'))) *ptr=0;
				label=copy_string(memory,filename);
			}

			// Otherwise, copy name
			else label=copy_string(memory,name);

			// No label?
			if (!label)
			{
				L_FreeMemH(name);
				break;
			}

			// Allocate button function
			if ((func=L_NewButtonFunction(memory,0)))
			{
				// Store name as label
				func->label=name;

				// And store label as name (for some reason :)
				func->node.ln_Name=label;

				// If a graphic button, get image
				if (button->button.flags&BUTNF_GRAPHIC)
					func->image=L_OpenImage(name,0);

				// Add to button list
				AddTail((struct List *)&button->function_list,&func->node);
			}

			// Failed
			else
			{
				L_FreeMemH(name);
				L_FreeMemH(label);
				break;
			}
		}

		// Free string stuff
		free_config_string(&handle);
	}

	return button;
}



// Read some filetype definitions
Cfg_FiletypeList *LIBFUNC L_ReadFiletypes(
	REG(a0, char *name),
	REG(a1, APTR memory))
{
	struct _IFFHandle *iff;
	Cfg_FiletypeList *list=0;
	Cfg_Filetype *type=0;
	short count=0;

	// Try to open file to read
	if ((iff=L_IFFOpen(name,IFF_READ,ID_OPUS)))
	{
		ULONG chunk;

		// Parse file
		while ((chunk=L_IFFNextChunk(iff,0)))
		{
			// Look at chunk type
			switch (chunk)
			{
				// Filetype definition
				case ID_TYPE:

					// If we don't have a list, create one
					if (!list)
					{
						D_S(struct FileInfoBlock,fib)

						// Create list entry
						if (!(list=L_AllocMemH(memory,sizeof(Cfg_FiletypeList))))
							break;

						// Initialise filetype list
						NewList(&list->filetype_list);

						// Copy path
						strcpy(list->path,name);

						// Get file date
						if (L_ExamineBuf(L_IFFFileHandle(iff),fib))
							list->date=fib->fib_Date;
					}

					// Allocate a new filetype
					if ((type=L_NewFiletype(memory)))
					{
						string_handle handle;
						short a;

						// Read filetype data
						L_IFFReadChunkBytes(iff,&type->type,sizeof(CFG_TYPE));

#ifdef __AROS__
						type->type.flags = AROS_BE2WORD(type->type.flags);
						type->type.count = AROS_BE2WORD(type->type.count);
#endif

						// Initialise strings
						init_config_string(iff,&handle);

						// Read recognition string
						type->recognition=(unsigned char *)read_config_string(memory,&handle);

						// Read icon path
						type->icon_path=read_config_string(memory,&handle);

						// Read actions
						for (a=0;a<16;a++)
						{
							type->actions[a]=
								read_config_string(memory,&handle);
						}
						free_config_string(&handle);

						// Add to list
						type->node.ln_Pri=type->type.priority;
						Enqueue(&list->filetype_list,&type->node);

						// Store priority in list
						if (count==0 ||
							type->type.priority<list->node.ln_Pri)
							list->node.ln_Pri=type->type.priority;

						// Store pointer to list
						type->list=list;
						++count;
					}
					break;


				// Function definition
				case ID_FUNC:

					// Read function
					if (type)
						L_ReadFunction(iff,memory,&type->function_list,0);
					break;
			}
		}

		L_IFFClose(iff);
	}
	
	return list;
}


// Read a function
Cfg_Function *LIBFUNC L_ReadFunction(
	REG(a0, struct _IFFHandle *iff),
	REG(a1, APTR memory),
	REG(a2, struct List *func_list),
	REG(a3, Cfg_Function *function))
{
	Cfg_Function *func;
	string_handle handle;
	char *string;
	short type;

	// Function supplied?
	if (function) func=function;

	// Allocate a new function
	else if (!(func=L_NewFunction(memory,0)))
		return 0;

	// Add to function list
	else if (func_list) AddTail(func_list,&func->node);

	// Read function data
	L_IFFReadChunkBytes(iff,&func->function,sizeof(CFG_FUNC));

#ifdef __AROS__
	func->function.flags = AROS_BE2LONG(func->function.flags);
	func->function.flags2 = AROS_BE2LONG(func->function.flags2);
	func->function.code = AROS_BE2WORD(func->function.code);
	func->function.qual = AROS_BE2WORD(func->function.qual);
	func->function.func_type = AROS_BE2WORD(func->function.func_type);
	func->function.qual_mask = AROS_BE2WORD(func->function.qual_mask);
	func->function.qual_same = AROS_BE2WORD(func->function.qual_same);
#endif

	// Old-style function?
	if (!(func->function.flags2&FUNCF2_VALID_IX))
	{
		// Fix IX
		func->function.qual_mask=0xffff;
		func->function.qual_same=0;

		// Fix alt
		if (func->function.qual&(IEQUALIFIER_LALT|IEQUALIFIER_RALT))
			func->function.qual_same|=IXSYM_ALT;

		// Fix shift
		if (func->function.qual&(IEQUALIFIER_LSHIFT|IEQUALIFIER_RSHIFT))
			func->function.qual_same|=IXSYM_SHIFT;

		// Mark as a valid new function
		func->function.flags2|=FUNCF2_VALID_IX;
	}

	// Read function instructions
	init_config_string(iff,&handle);
	while ((string=read_config_string(memory,&handle)))
	{
		Cfg_Instruction *ins;

		// Read instruction type
		type=read_config_short(&handle);

		// Allocate new instruction
		if ((ins=L_NewInstruction(memory,type,0)))
		{
			// Initialise instruction
			ins->string=string;

			// Add to instruction list
			AddTail((struct List *)&func->instructions,(struct Node *)ins);
		}

		// Failed
		else
		{
			L_FreeMemH(string);
			break;
		}
	}
	free_config_string(&handle);

	return func;
}


void init_config_string(struct _IFFHandle *iff,string_handle *handle)
{
	long size;

	handle->buffer=0;
	handle->pointer=0;
	handle->size=0;
	handle->error=0;

	// See how much is left to read
	if ((handle->size=L_IFFChunkRemain(iff))<1)
	{
		handle->size=0;
		return;
	}

	// Allocate buffer
	if (!(handle->buffer=AllocVec(handle->size+1,MEMF_CLEAR)))
		return;

	// Read data
	if ((size=L_IFFReadChunkBytes(iff,handle->buffer,handle->size))<0)
	{
		handle->error=1;
		return;
	}
	handle->size=size;

	// Initialise pointer
	handle->pointer=handle->buffer;
}

char *read_config_string(APTR memory,string_handle *handle)
{
	int len;
	char *string;

	if (!handle->pointer || handle->size<1 || handle->error) return 0;

	// Find next null
	for (len=0;len<handle->size && handle->pointer[len];len++);

	// Allocate data for string
	if ((string=L_AllocMemH(memory,len+1)))

		// Copy string
		strcpy(string,handle->pointer);

	// Bump pointer, decrement size
	handle->pointer+=len+1;
	handle->size-=len+1;

	// Return string pointer
	return string;
}

short read_config_short(string_handle *handle)
{
	short value;

	// Valid buffer?
	if (!handle->pointer || handle->size<2) return 0;

	// Get value
	value=(handle->pointer[0]<<16)|handle->pointer[1];

	// Bump pointer, decrement size
	handle->pointer+=2;
	handle->size-=2;

	// Return value
	return value;
}

void free_config_string(string_handle *handle)
{
	FreeVec(handle->buffer);
}


/*
				// Path format
				case ID_PFMT:
					{
						Cfg_PathFormat *node;

						// Allocate new entry
						if (node=L_AllocMemH(environment->settings_memory,sizeof(Cfg_PathFormat)))
						{
							// Read flags
							ReadChunkBytes(iff,&node->flags,sizeof(ULONG));

							// Read format
							ReadChunkBytes(iff,&node->format,sizeof(ListFormatStorage));
							ParsePatternNoCase(node->format.show_pattern,node->format.show_pattern_p,40);
							ParsePatternNoCase(node->format.hide_pattern,node->format.hide_pattern_p,40);

							// Key code?
							if (node->flags&PATHFMTF_HOTKEY)
							{
								// Read key
								ReadChunkBytes(iff,&node->code,sizeof(unsigned short)*2);
							}

							// Read path
							ReadChunkBytes(iff,node->path,256);

							// Add to path format list
							AddTail((struct List *)&environment->path_formats,(struct Node *)node);
						}
					}
					break;
*/


// Convert start menu to version 2
void ASM L_ConvertStartMenu(REG(a0, Cfg_ButtonBank *bank))
{
	Cfg_Button *button,*prev=0,*next_but=0;

	// Find first button and remove it - no longer needed
	if ((button=(Cfg_Button *)RemHead(&bank->buttons)))
	{
		// Free button
		L_FreeButton(button);
	}

	// Go through remaining buttons
	for (button=(Cfg_Button *)bank->buttons.lh_Head;button->node.ln_Succ;button=next_but)
	{
		Cfg_ButtonFunction *func,*next=0;
		BOOL first=1;

		// Cache next button
		next_but=(Cfg_Button *)button->node.ln_Succ;

		// Go through all functions in the button
		for (func=(Cfg_ButtonFunction *)button->function_list.mlh_Head;func->node.ln_Succ;func=next)
		{
			Cfg_Button *newbut;

			// Cache next function
			next=(Cfg_ButtonFunction *)func->node.ln_Succ;

			// Set the type back to 0
			func->function.func_type=FTYPE_LEFT_BUTTON;

			// Remove the function
			Remove((struct Node *)func);

			// Empty function?
			if (IsListEmpty((struct List *)&func->instructions) &&
				(!func->node.ln_Name || !*func->node.ln_Name) &&
				(!func->label || !*func->label))
			{
				// Free function, don't add it
				L_FreeButtonFunction(func);
			}

			// Make a new button for the menu title
			else
			if ((newbut=L_NewButton(bank->memory)))
			{
				// First function in the button means it's a title
				if (first)
				{
					// Set flag in that button to say it's a menu title
					newbut->button.flags|=BUTNF_TITLE|BUTNF_NEW_FORMAT;
					first=0;
				}
				else newbut->button.flags|=BUTNF_NEW_FORMAT;

				// Add the function we removed to the new button
				AddHead((struct List *)&newbut->function_list,&func->node);

				// Add the new button to the button list before the current button
				Insert(&bank->buttons,&newbut->node,(struct Node *)prev);

				// Save button pointer for next time
				prev=newbut;
			}

			// Failed
			else L_FreeButtonFunction(func);
		}

		// Free the old button
		Remove((struct Node *)button);
		L_FreeButton(button);
	}

	// Set flag to say bank has been converted
	if (bank->startmenu) bank->startmenu->flags|=STRTF_VERSION2;
}

/*
void dump_button_info(Cfg_ButtonBank *bank)
{
	Cfg_Button *button;
	for (button=(Cfg_Button *)bank->buttons.lh_Head;button->node.ln_Succ;button=(Cfg_Button *)button->node.ln_Succ)
	{
		Cfg_ButtonFunction *func;
		D(bug("button flags %lx (title %lx item %lx sub %lx)\n",button->button.flags,
			button->button.flags&BUTNF_TITLE,button->button.flags&BUTNF_ITEM,button->button.flags&BUTNF_SUB));
		for (func=(Cfg_ButtonFunction *)button->function_list.mlh_Head;func->node.ln_Succ;func=(Cfg_ButtonFunction *)func->node.ln_Succ)
		{
			Cfg_Instruction *ins;

			D(bug("name %s label %s flags %lx type %ld\n",func->node.ln_Name,func->label,func->function.flags2,func->function.func_type));
			for (ins=(Cfg_Instruction *)func->instructions.mlh_Head;ins->node.mln_Succ;ins=(Cfg_Instruction *)ins->node.mln_Succ)
				D(bug("\t%ld %s\n",ins->type,ins->string));
		}
		D(bug("------------\n"));
	}
}
*/

BOOL LIBFUNC L_OpenEnvironment(
	REG(a0, char *name),
	REG(a1, struct OpenEnvironmentData *data))
{
	APTR iff;
	ULONG chunk;
	char buf[256];

	// Initialise
	NewList((struct List *)&data->desktop);
	NewList((struct List *)&data->pathlist);
	NewList((struct List *)&data->soundlist);
	NewList((struct List *)&data->startmenus);
	NewList((struct List *)&data->buttons);

	NewList((struct List *)&data->listers);
	data->toolbar_path[0]=0;
	data->menu_path[0]=0;
	data->user_menu_path[0]=0;
	data->scripts_path[0]=0;
	data->hotkeys_path[0]=0;

	// Try to open file to read
	if (!(iff=L_IFFOpen(name,IFF_READ,ID_OPUS)))
		return 0;

	// Parse file
	while ((chunk=L_IFFNextChunk(iff,0)))
	{
		// Look at chunk type
		switch (chunk)
		{
			// Environment settings
			case ID_ENVR:
				if (!(data->flags&OEDF_ENVR)) break;
				L_IFFReadChunkBytes(iff,&data->env,sizeof(CFG_ENVR));
#ifdef __AROS__
				{
					int i;
				
					data->env.screen_mode = AROS_BE2LONG(data->env.screen_mode);
					data->env.screen_flags = AROS_BE2WORD(data->env.screen_flags);
					data->env.screen_depth = AROS_BE2WORD(data->env.screen_depth);
					data->env.screen_width = AROS_BE2WORD(data->env.screen_width);
					data->env.screen_height = AROS_BE2WORD(data->env.screen_height);

					for (i=0; i<50; i++)
						data->env.palette[i] = AROS_BE2LONG(data->env.palette[i]);
					
					data->env.window_pos.Left = AROS_BE2WORD(data->env.window_pos.Left);
					data->env.window_pos.Top = AROS_BE2WORD(data->env.window_pos.Top);
					data->env.window_pos.Width = AROS_BE2WORD(data->env.window_pos.Width);
					data->env.window_pos.Height = AROS_BE2WORD(data->env.window_pos.Height);
					data->env.general_screen_flags = AROS_BE2LONG(data->env.general_screen_flags);
					data->env.palette_count = AROS_BE2WORD(data->env.palette_count);
					
					for (i=0; i<CUST_PENS; i++)
					{
						data->env.env_Colours[i][0][0] = AROS_BE2LONG(data->env.env_Colours[i][0][0]);
						data->env.env_Colours[i][0][1] = AROS_BE2LONG(data->env.env_Colours[i][0][1]);
						data->env.env_Colours[i][0][2] = AROS_BE2LONG(data->env.env_Colours[i][0][2]);
						data->env.env_Colours[i][1][0] = AROS_BE2LONG(data->env.env_Colours[i][1][0]);
						data->env.env_Colours[i][1][1] = AROS_BE2LONG(data->env.env_Colours[i][1][1]);
						data->env.env_Colours[i][1][2] = AROS_BE2LONG(data->env.env_Colours[i][1][2]);
					}
					
					data->env.env_ColourFlag = AROS_BE2LONG(data->env.env_ColourFlag);
					data->env.env_NewIconsFlags = AROS_BE2LONG(data->env.env_NewIconsFlags);
					data->env.display_options = AROS_BE2WORD(data->env.display_options);
					data->env.main_window_type = AROS_BE2WORD(data->env.main_window_type);
					data->env.hotkey_flags = AROS_BE2WORD(data->env.hotkey_flags);
					data->env.hotkey_code = AROS_BE2WORD(data->env.hotkey_code);
					data->env.hotkey_qual = AROS_BE2WORD(data->env.hotkey_qual);
					data->env.default_stack = AROS_BE2LONG(data->env.default_stack);
					data->env.lister_options = AROS_BE2WORD(data->env.lister_options);
					data->env.flags = AROS_BE2LONG(data->env.flags);
					data->env.lister_popup_code = AROS_BE2WORD(data->env.lister_popup_code);
					data->env.lister_popup_qual = AROS_BE2WORD(data->env.lister_popup_qual);
					data->env.env_flags = AROS_BE2LONG(data->env.env_flags);
					data->env.clock_left = AROS_BE2WORD(data->env.clock_left);
					data->env.clock_top = AROS_BE2WORD(data->env.clock_top);
					data->env.lister_width = AROS_BE2WORD(data->env.lister_width);
					data->env.lister_height = AROS_BE2WORD(data->env.lister_height);
					data->env.version = AROS_BE2WORD(data->env.version);
					data->env.desktop_flags = AROS_BE2LONG(data->env.desktop_flags);
					
					for (i=0; i<4; i++)
						data->env.env_BackgroundFlags[i] = AROS_BE2WORD(data->env.env_BackgroundFlags[i]);
				
					data->env.settings.copy_flags = AROS_BE2LONG(data->env.settings.copy_flags);
					data->env.settings.delete_flags = AROS_BE2LONG(data->env.settings.delete_flags);
					data->env.settings.error_flags = AROS_BE2LONG(data->env.settings.error_flags);
					data->env.settings.general_flags = AROS_BE2LONG(data->env.settings.general_flags);
					data->env.settings.icon_flags = AROS_BE2LONG(data->env.settings.icon_flags);
					data->env.settings.replace_method = AROS_BE2WORD(data->env.settings.replace_method);
					data->env.settings.replace_flags = AROS_BE2WORD(data->env.settings.replace_flags);
					data->env.settings.update_flags = AROS_BE2LONG(data->env.settings.update_flags);
					data->env.settings.dir_flags = AROS_BE2LONG(data->env.settings.dir_flags);
					data->env.settings.view_flags = AROS_BE2LONG(data->env.settings.view_flags);
					data->env.settings.max_buffer_count = AROS_BE2WORD(data->env.settings.max_buffer_count);
					data->env.settings.date_format = AROS_BE2WORD(data->env.settings.date_format);
					data->env.settings.date_flags = AROS_BE2WORD(data->env.settings.date_flags);
					data->env.settings.pop_code = AROS_BE2WORD(data->env.settings.pop_code);
					data->env.settings.pop_qual = AROS_BE2WORD(data->env.settings.pop_qual);
					data->env.settings.pop_qual_mask = AROS_BE2WORD(data->env.settings.pop_qual_mask);
					data->env.settings.pop_qual_same = AROS_BE2WORD(data->env.settings.pop_qual_same);
					data->env.settings.popup_delay = AROS_BE2WORD(data->env.settings.popup_delay);
					data->env.settings.max_openwith = AROS_BE2WORD(data->env.settings.max_openwith);
					data->env.settings.command_line_length = AROS_BE2WORD(data->env.settings.command_line_length);
					data->env.settings.max_filename = AROS_BE2WORD(data->env.settings.max_filename);
					data->env.settings.flags = AROS_BE2LONG(data->env.settings.flags);
					
					for (i=0; i<4; i++)
						data->env.env_BackgroundBorderColour[i] = AROS_BE2LONG(data->env.env_BackgroundBorderColour[i]);
				}
#endif
				break;

			// Settings file name
			case ID_SETS:
				if (!(data->flags&OEDF_SETS)) break;
				L_IFFReadChunkBytes(iff,buf,256);
				L_ReadSettings(&data->env.settings,buf);
				break;

			// Toolbar file name
			case ID_TBAR:
				if (!(data->flags&OEDF_TBAR)) break;
				L_IFFReadChunkBytes(iff,data->toolbar_path,256);
				break;

			// Lister menu file name
			case ID_LMEN:
				if (!(data->flags&OEDF_LMEN)) break;
				L_IFFReadChunkBytes(iff,data->menu_path,256);
				break;

			// Menu file name
			case ID_UMEN:
				if (!(data->flags&OEDF_UMEN)) break;
				L_IFFReadChunkBytes(iff,data->user_menu_path,256);
				break;

			// Scripts file name
			case ID_SCRP:
				if (!(data->flags&OEDF_SCRP)) break;
				L_IFFReadChunkBytes(iff,data->scripts_path,256);
				break;

			// Hotkeys name
			case ID_HKEY:
				if (!(data->flags&OEDF_HKEY)) break;
				L_IFFReadChunkBytes(iff,data->hotkeys_path,256);
				break;

			// Button bank to open
			case ID_BTBK:
			case ID_BANK:
			case ID_STRT:
				if (!(data->flags&OEDF_BANK)) break;
				env_read_open_bank(iff,data,chunk);
				break;

			// Lister to open
			case ID_LSTR:
			case ID_DLST:
				if (!(data->flags&OEDF_LSTR)) break;
				env_read_open_lister(iff,data,chunk);
				break;

			// Desktop information
			case ID_DESK:
				if (data->flags&OEDF_DESK)
				{
					Cfg_Desktop *desk;

					// Allocate desktop entry
					if ((desk=L_AllocMemH(data->memory,L_IFFChunkSize(iff)+sizeof(struct MinNode))))
					{
						// Read data
						L_IFFReadChunkBytes(iff,&desk->data,L_IFFChunkSize(iff));

#ifdef __AROS__
						desk->data.dt_Type = AROS_BE2WORD(desk->data.dt_Type);
						desk->data.dt_Size = AROS_BE2WORD(desk->data.dt_Size);
						desk->data.dt_Flags = AROS_BE2LONG(desk->data.dt_Flags);					
						desk->data.dt_Data = AROS_BE2LONG(desk->data.dt_Data);
#endif

						AddTail((struct List *)&data->desktop,(struct Node *)desk);
					}
				}
				break;


			// Path list entry
			case ID_PATH:
				if (data->flags&OEDF_PATH)
				{
					struct MinNode *node;

					// Allocate entry
					if ((node=L_AllocMemH(data->memory,L_IFFChunkSize(iff)+sizeof(struct MinNode)+1)))
					{
						// Read data, add to list
						L_IFFReadChunkBytes(iff,(char *)(node+1),L_IFFChunkSize(iff));
						AddTail((struct List *)&data->pathlist,(struct Node *)node);
					}
				}
				break;


			// Sound list entry
			case ID_SNDX:
				if (data->flags&OEDF_SNDX)
				{
					Cfg_SoundEntry *sound;

					// Allocate entry
					if ((sound=L_AllocMemH(data->memory,sizeof(Cfg_SoundEntry))))
					{
						// Read data, add to list
						L_IFFReadChunkBytes(iff,(char *)sound->dse_Name,L_IFFChunkSize(iff));

#ifdef __AROS__
						sound->dse_Volume = AROS_BE2WORD(sound->dse_Volume);
						sound->dse_Flags = AROS_BE2WORD(sound->dse_Flags);
						sound->dse_RandomVolume = AROS_BE2WORD(sound->dse_RandomVolume);
#endif	

						sound->dse_Node.ln_Name=sound->dse_Name;
						sound->dse_Flags&=~CFGSEF_CHANGED;
						AddTail((struct List *)&data->soundlist,(struct Node *)sound);
					}
				}
				break;
		}
	}

	// Close file
	L_IFFClose(iff);

	// Bring environment file up to date
	if ((data->flags&OEDF_ENVR) && (data->flags&OEDF_SETS))
		L_UpdateEnvironment(&data->env);
	return 1;
}


// Read info on a button bank to open
void env_read_open_bank(APTR iff,struct OpenEnvironmentData *data,ULONG id)
{
	ButtonBankNode *node;
	char path[256];

	// Allocate new node
	if ((node=L_AllocMemH(data->volatile_memory,sizeof(ButtonBankNode))))
	{
		ULONG pad[5];

		// Read padding if new version
		if (id==ID_BANK || id==ID_STRT)
		{
			L_IFFReadChunkBytes(iff,pad,sizeof(pad));
			node->icon_pos_x=pad[2];
			node->icon_pos_y=pad[3];
			node->flags=pad[4];
#ifdef __AROS__
			node->icon_pos_x = AROS_BE2LONG(node->icon_pos_x);					
			node->icon_pos_y = AROS_BE2LONG(node->icon_pos_y);
			node->flags = AROS_BE2LONG(node->flags);
#endif
		}
		else node->icon_pos_x=NO_ICON_POSITION;

		// Read position
		L_IFFReadChunkBytes(iff,&node->pos,sizeof(struct IBox));

#ifdef __AROS__
		node->pos.Left = AROS_BE2WORD(node->pos.Left);
		node->pos.Top = AROS_BE2WORD(node->pos.Top);
		node->pos.Width = AROS_BE2WORD(node->pos.Width);
		node->pos.Height = AROS_BE2WORD(node->pos.Height);
#endif

		// Get path of button bank
		L_IFFReadChunkBytes(iff,path,256);

		// Store in node
		if ((node->node.ln_Name=L_AllocMemH(data->volatile_memory,strlen(path)+1)))
			strcpy(node->node.ln_Name,path);

		// Link to list
		if (id==ID_STRT)
			AddTail((struct List *)&data->startmenus,(struct Node *)node);
		else
			AddTail((struct List *)&data->buttons,(struct Node *)node);
	}
}


// Read info on a lister to open
void env_read_open_lister(APTR iff,struct OpenEnvironmentData *data,ULONG id)
{
	OpenListerNode *node;

	// Allocate new node
	if ((node=L_AllocMemH(data->volatile_memory,sizeof(OpenListerNode))))
	{
		// Read definition
		node->lister=(APTR)L_ReadListerDef(iff,id);

		// Link to list
		AddTail((struct List *)&data->listers,(struct Node *)node);
	}
}
