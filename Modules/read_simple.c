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

#include "read.h"
#include "modules.h"

static char *version="$VER: read.module 44.14 (18.07.95)";
static struct IBox dims;
static short tab_size=8;
static short search_flags=SEARCHF_NOCASE;
static char *mode_string[]={"normal","ansi","hex"};
static char first;
static short use_screen;
static ULONG modeid;
static char fontname[40];
static short fontsize;

int __asm __saveds L_Module_Entry(
	register __a0 struct List *files,
	register __a1 struct Screen *screen,
	register __a2 IPCData *ipc,
	register __a3 IPCData *main_ipc,
	register __d0 ULONG mod_id,
	register __d1 ULONG mod_data)
{
	read_data *data;
	struct Node *node;

	// Allocate data and memory pool
	if (!(data=AllocVec(sizeof(read_data),MEMF_CLEAR)) ||
		!(data->memory=NewMemHandle(0,0,0)))
	{
		FreeVec(data);
		return 0;
	}

	// Store IPC pointer
	data->ipc=ipc;
	data->main_ipc=main_ipc;
	data->screen=screen;
	data->slider_div=1;
	data->initial_search=(char *)mod_id;

	// Initialise tab size and flags
	data->tab_size=tab_size;
	data->mode=0;
	data->search_flags=search_flags;

	// Initialise dimensions
	if (dims.Width==0)
	{
		if (screen)
		{
			dims.Top=screen->BarHeight+1;
			dims.Width=screen->Width;
			dims.Height=screen->Height-screen->BarHeight-1;
		}
		else
		{
			dims.Width=640;
			dims.Height=200;
		}
	}

	// Try for environment variable if first run
	if (!first)
	{
		if (GetVar("dopus_read",data->title,sizeof(data->title),GVF_GLOBAL_ONLY)>0)
		{
			char *ptr=data->title;
			unsigned short temp=0;

			// Parse settings
			read_parse_set(&ptr,(USHORT *)&dims.Left);
			read_parse_set(&ptr,(USHORT *)&dims.Top);
			read_parse_set(&ptr,(USHORT *)&dims.Width);
			read_parse_set(&ptr,(USHORT *)&dims.Height);
			read_parse_set(&ptr,(USHORT *)&data->tab_size);
			read_parse_set(&ptr,(USHORT *)&data->search_flags);
			read_parse_set(&ptr,(USHORT *)&use_screen);
			read_parse_set(&ptr,&temp); modeid=temp<<16;
			read_parse_set(&ptr,&temp); modeid|=temp;
			read_parse_set(&ptr,(USHORT *)&fontsize);
			stccpy(fontname,ptr,38);
		}
		first=1;
	}

	// Open view window
	if (read_open_window(data))
	{
		// Go through files
		for (node=files->lh_Head;node->ln_Succ;node=node->ln_Succ)
		{
			// Store file name pointer
			data->file=node->ln_Name;

			// Show title
			lsprintf(data->title,GetString(locale,MSG_READING_FILE),FilePart(data->file));
			SetWindowTitles(data->window,data->title,(char *)-1);

			// Set busy pointer
			SetBusyPointer(data->window);

			// If no more files, disable Next item
			if (!node->ln_Succ->ln_Succ)
			{
				OffMenu(data->window,FULLMENUNUM(0,0,0));
				data->no_next=1;
			}

			// Read file
			if (read_file(data,mod_data))
			{
				short ret;

				// Display file
				ret=read_view(data);

				// Delete file?
				if (node->ln_Pri) DeleteFile(node->ln_Name);

				// Aborted?
				if (!ret) break;
			}

			// Unable to open
			else
			{
				lsprintf(data->title,GetString(locale,MSG_CANT_OPEN_FILE),FilePart(data->file));
				SetWindowTitles(data->window,data->title,(char *)-1);
			}
		}
	}

	// Free data
	read_free(data);

	return 1;
}


// Free read data
void read_free(read_data *data)
{
	if (data)
	{
		// Close display
		read_close_window(data);

		// Save flags
		tab_size=data->tab_size;
		search_flags=data->search_flags;

		// Free stuff
		FreeMemHandle(data->memory);
		FreeVec(data);
	}
}


// Open display
struct Window *read_open_window(read_data *data)
{
	struct Screen *screen;
	struct TextAttr font;
	short a;

	// Initialise pen array
	for (a=0;a<PEN_COUNT;a++) data->ansi_pen_array[a]=a;

	// Use supplied screen by default
	screen=data->screen;

	// Open our own screen?
	if (use_screen)
	{
		USHORT pens[1];

		// Get mode ID to use
		if (!modeid || ModeNotAvailable(modeid))
			modeid=GetVPModeID(&screen->ViewPort);

		// Public screen name
		lsprintf(data->screen_name,"dopus text viewer - %lx",data);

		// Open screen
		pens[0]=(USHORT)~0;
		if (data->my_screen=my_OpenScreenTags(
			SA_Depth,(data->mode==MODE_ANSI)?4:2,
			SA_DisplayID,modeid,
			SA_AutoScroll,TRUE,
			SA_Pens,pens,
			SA_SysFont,1,
			SA_Title,GetString(locale,MSG_SCREEN_TITLE),
			SA_Interleaved,(data->mode==MODE_ANSI)?TRUE:FALSE,
			SA_SharePens,TRUE,
			SA_PubName,data->screen_name,
			TAG_END))
		{
			screen=data->my_screen;

			// Default dimensions
			dims.Left=0;
			dims.Top=screen->BarHeight+1;
			dims.Width=screen->Width;
			dims.Height=screen->Height-dims.Top;
		}
	}

	// Open window
	if (!(data->window=my_OpenWindowTags(
		WA_Top,dims.Top,
		WA_Left,dims.Left,
		WA_Width,dims.Width,
		WA_Height,dims.Height,
		WA_SizeGadget,TRUE,
		WA_DragBar,TRUE,
		WA_DepthGadget,TRUE,
		WA_CloseGadget,TRUE,
		WA_Activate,TRUE,
		WA_SizeBRight,TRUE,
		WA_SizeBBottom,TRUE,
		WA_NewLookMenus,TRUE,
		WA_IDCMP,
			IDCMP_CLOSEWINDOW|
			IDCMP_NEWSIZE|
			IDCMP_MENUPICK|
			IDCMP_IDCMPUPDATE|
			IDCMP_INACTIVEWINDOW|
			IDCMP_RAWKEY|
			IDCMP_REFRESHWINDOW|
			IDCMP_MOUSEBUTTONS|
			IDCMP_MOUSEMOVE,
		WA_PubScreen,screen,
		WA_PubScreenFallBack,TRUE,
		WA_SimpleRefresh,TRUE,
		WA_MinWidth,128,
		WA_MinHeight,64,
		WA_MaxWidth,-1,
		WA_MaxHeight,-1,
		TAG_END))) return 0;

	// Make window busy
	SetBusyPointer(data->window);

	// Want a custom font?
	if (fontname[0])
	{
		font.ta_Name=fontname+1;
		font.ta_YSize=fontsize;
		font.ta_Style=0;
		font.ta_Flags=0;
		if (data->font=OpenDiskFont(&font))
			SetFont(data->window->RPort,data->font);
	}

	// Get DrawInfo and visual info
	data->drawinfo=GetScreenDrawInfo(data->window->WScreen);
	data->vi=GetVisualInfoA(data->window->WScreen,0);

	// Initialise BOOPSI list and scrollers
	NewList(&data->boopsi_list);
	data->vert_scroller=AddScrollBars(data->window,&data->boopsi_list,data->drawinfo,FALSE);

	// Create menus
	if (data->menus=BuildMenuStrip(read_menus,locale))
	{
		struct MenuItem *item;

		// Lay menus out
		my_LayoutMenus(data->menus,data->vi,GTMN_NewLookMenus,TRUE,TAG_END);

		// If not using ASL 38+, disable Pick screen mode
		if (AslBase->lib_Version<38)
		{
			if (item=FindMenuItem(data->menus,MENU_SCREEN_MODE))
				item->Flags&=~ITEMENABLED;
		}

		// Attach menus
		SetMenuStrip(data->window,data->menus);

		// No next file?
		if (data->no_next)
		{
			OffMenu(data->window,FULLMENUNUM(0,0,0));
		}
	}

	// Got scrollers?
	if (data->vert_scroller)
	{
		// Get pointer to horizontal scroller
		data->horiz_scroller=FindBOOPSIGadget(&data->boopsi_list,GAD_HORIZ_SCROLLER);

		// Add scrollers
		AddGList(data->window,data->vert_scroller,-1,-1,0);
		RefreshGList(data->vert_scroller,data->window,0,-1);

		// Clear window busy
		ClearPointer(data->window);

		return data->window;
	}

	return 0;
}


// Close display
void read_close_window(read_data *data)
{
	// Close window
	if (data->window)
	{
		// Any pens allocated?
		if (GfxBase->lib_Version>=39 && data->pen_alloc)
		{
			short a;

			// Free pens
			for (a=0;a<PEN_COUNT;a++)
			{
				// Allocated?
				if (data->pen_alloc&(1<<a))
				{
					// Free pen
					ReleasePen(
						data->window->WScreen->ViewPort.ColorMap,
						data->ansi_pen_array[a]);
				}
			}
			data->pen_alloc=0;
		}

		// Store window dimensions
		dims=*((struct IBox *)&data->window->LeftEdge);

		// Free draw info and visual info
		if (data->drawinfo)
		{
			FreeScreenDrawInfo(data->window->WScreen,data->drawinfo);
			data->drawinfo=0;
		}
		if (data->vi)
		{
			FreeVisualInfo(data->vi);
			data->vi=0;
		}

		// Close window, free stuff
		ClearMenuStrip(data->window);
		CloseWindow(data->window);
		data->window=0;
		BOOPSIFree(&data->boopsi_list);

		// Close font
		if (data->font)
		{
			CloseFont(data->font);	
			data->font=0;
		}

		// Free menus
		FreeMenus(data->menus);
		data->menus=0;
	}

	// Close screen
	if (data->my_screen)
	{
		CloseScreen(data->my_screen);
		data->my_screen=0;
	}
}


// varargs OpenWindowTags()
struct Window *__stdargs my_OpenWindowTags(Tag tag,...)
{
	return OpenWindowTagList(0,(struct TagItem *)&tag);
}


// varargs OpenScreenTags()
struct Screen *__stdargs my_OpenScreenTags(Tag tag,...)
{
	return OpenScreenTagList(0,(struct TagItem *)&tag);
}


// Read text file
BOOL read_file(read_data *data,ULONG type)
{
	BPTR file;
	struct FileInfoBlock __aligned fib;
	struct DateTime dt;

	// Clear any existing file
	ClearMemHandle(data->memory);
	NewList((struct List *)&data->text);
	data->current_block=0;
	data->current_line=0;
	data->text_buffer=0;
	data->text_lines=0;
	data->top=0;
	data->left=0;
	data->top_line=0;
	data->top_position=0;
	data->search_line=0;
	data->search_last_line=0;
	data->flags=0;
	data->sel_top_pos=-1;

	// Initialise scrollers
	my_SetGadgetAttrs(data->vert_scroller,data->window,
		PGA_Total,0,
		PGA_Top,0,
		TAG_END);
	my_SetGadgetAttrs(data->horiz_scroller,data->window,
		PGA_Total,0,
		PGA_Top,0,
		TAG_END);

	// Clear window interior
	SetAPen(data->window->RPort,data->drawinfo->dri_Pens[BACKGROUNDPEN]);
	RectFill(data->window->RPort,
		data->window->BorderLeft,
		data->window->BorderTop,
		data->window->Width-data->window->BorderRight-1,
		data->window->Height-data->window->BorderBottom-1);

	// Lock file
	if (!(file=Lock(data->file,ACCESS_READ)) ||
		!(Examine(file,&fib)))
	{
		UnLock(file);
		return 0;
	}
	UnLock(file);

	// Store date and size
	dt.dat_Stamp=fib.fib_Date;
	dt.dat_Flags=0;
	dt.dat_StrDay=0;
	dt.dat_StrDate=data->date;
	dt.dat_StrTime=0;
	DateToStr(&dt);
	data->size=fib.fib_Size;

	// Open file
	if (!(file=Open(data->file,MODE_OLDFILE)))
	{
		return 0;
	}

	// Allocate text buffer
	if (!(data->text_buffer=AllocMemH(data->memory,fib.fib_Size)))
	{
		long size;

		// Try for partial size
		size=AvailMem(MEMF_LARGEST)-1024;
		if (size<fib.fib_Size && size>0)
		{
			data->text_buffer=AllocMemH(data->memory,fib.fib_Size);
		}
	}

	// No buffer?
	if (!data->text_buffer)
	{
		Close(file);
		return 0;
	}

	// Read file
	data->text_buffer_size=Read(file,data->text_buffer,fib.fib_Size);

	// Close file
	Close(file);

	// Count lines
	read_set_mode(data,type);
	return 1;
}


// Set up for a display mode
void read_set_mode(read_data *data,short mode)
{
	BOOL ansi_flag=0;

	// Clear some stuff
	data->top=0;
	data->left=0;
	data->top_line=0;
	data->top_position=0;
	data->search_line=0;
	data->search_last_line=0;

	// Which mode?
	switch (mode)
	{
		case MODE_ANSI:
		case MODE_NORMAL:
		case MODE_SMART:

			// Haven't counted lines yet?
			if (IsListEmpty((struct List *)&data->text))
			{
				register unsigned long bufpos;
				register short length=0;
				register unsigned char ch;
				long bufstart=0;
				short nonprint_count=0;

				// Search for lines
				for (bufpos=0;bufpos<data->text_buffer_size;bufpos++,length++)
				{
					// Get character
					ch=data->text_buffer[bufpos];

					// End of line?
					if (ch=='\n' || length==255 || bufpos==data->text_buffer_size-1)
					{
						register read_line *line;

						// Allocate line node
						if (!(line=read_alloc_node(data)))
						{
							break;
						}

						// If valid character, increment length
						if (length<255 && ch!='\n') ++length;

						// Store length and text pointer
						line->length=length;
						line->text=data->text_buffer+bufstart;

						// Add line to list and increment line count
						AddTail((struct List *)&data->text,(struct Node *)line);
						++data->text_lines;

						// Store position for start of next line
						bufstart=bufpos+1;
						length=-1;
					}

					// Escape sequence?
					else if (ch==0x1b) ansi_flag=1;

					// Otherwise, smart mode?
					else if (mode==MODE_SMART)
					{
						// Non-printable?
						if (ch<0x8 ||
							(ch>0xd && ch<0x20) ||
							(ch>0x7e && ch<0xc0))
						{
							// Increment non-print count; need 4 (arbitrary) together for hex
							if (++nonprint_count>4)
							{
								// Use hex mode (finish counting lines anyway)
								mode=MODE_HEX;
							}
						}

						// Reset nonprint count
						else nonprint_count=0;
					}
				}
			}

			// Store normal line count
			data->lines=data->text_lines;

			// If still smart mode, use normal
			if (mode==MODE_SMART)
			{
				if (ansi_flag) mode=MODE_ANSI;
				else mode=MODE_NORMAL;
			}

			// Unless in hex mode now, break out
			if (mode!=MODE_HEX) break;


		case MODE_HEX:

			// Calculate line count
			data->lines=UDivMod32(data->text_buffer_size+(HEX_DISPLAY_WIDTH-1),HEX_DISPLAY_WIDTH);
			break;
	}

	// Store mode
	data->mode=mode;

	// ANSI mode?
	if (mode==MODE_ANSI)
	{
		// Try to allocate pens?
		if (GfxBase->lib_Version>=39 && !data->pen_alloc)
		{
			// Don't try unless screen is deeper than 8 colours
			if (data->window->WScreen->RastPort.BitMap->Depth>3)
			{
				short a;
				long pen;

				// Allocate pens if possible
				for (a=1;a<PEN_COUNT;a++)
				{
					// Try to allocate a pen
					if ((pen=ObtainPen(
						data->window->WScreen->ViewPort.ColorMap,
						-1,
						(ansi_palette[a]&0xff0000)<<8,
						(ansi_palette[a]&0x00ff00)<<16,
						(ansi_palette[a]&0x0000ff)<<24,0))==-1)
					{
						// Try to share a pen
						pen=ObtainBestPenA(
							data->window->WScreen->ViewPort.ColorMap,
							(ansi_palette[a]&0xff0000)<<8,
							(ansi_palette[a]&0x00ff00)<<16,
							(ansi_palette[a]&0x0000ff)<<24,0);
					}

					// Get one?
					if (pen!=-1)
					{
						// Store pen, set alloc bit
						data->ansi_pen_array[a]=pen;
						data->pen_alloc|=1<<a;
					}
				}
			}
		}

		// 2.0 version
		else if (data->my_screen && data->my_screen->RastPort.BitMap->Depth>3)
		{
			short a;

			// Use pens 4-12, set colours
			for (a=0;a<PEN_COUNT;a++)
			{
				data->ansi_pen_array[a]=a+4;
				SetRGB4(&data->window->WScreen->ViewPort,
					a+4,
					(ansi_palette[a]&0xff0000)>>16,
					(ansi_palette[a]&0x00ff00)>>8,
					(ansi_palette[a]&0x0000ff));
			}
		}
	}
}


// Display file
BOOL read_view(read_data *data)
{
	short quit_flag=0;

	// Initialise display
	read_init(data);

	// Clear pointer
	ClearPointer(data->window);

	// Initial search?
	if (data->initial_search)
	{
		// Copy search string
		strcpy(data->search_text,data->initial_search);
		data->initial_search=0;

		// Initiate search
		read_search(data,1);
	}

	// Event loop
	FOREVER
	{
		struct IntuiMessage *msg;
		IPCMessage *imsg;

		// IPC messages?
		if (data->ipc)
		{
			while (imsg=(IPCMessage *)GetMsg(data->ipc->command_port))
			{
				// Abort?
				if (imsg->command==IPC_ABORT || imsg->command==IPC_QUIT)
				{
					quit_flag=2;
				}

				IPC_Reply(imsg);
			}
		}

		// Window messages
		if (data->window)
		{
			while (msg=(struct IntuiMessage *)GetMsg(data->window->UserPort))
			{
				struct IntuiMessage msg_copy;
				short sel_dx=0,sel_dy=0;

				// Copy message and reply
				msg_copy=*msg;
				ReplyMsg((struct Message *)msg);

				// Look at message
				switch (msg_copy.Class)
				{
					// Close window
					case IDCMP_CLOSEWINDOW:
						quit_flag=1;
						break;


					// Resized
					case IDCMP_NEWSIZE:
						read_calc_size(data);
						read_update_text(data,0,0,0);
						data->flags|=READF_RESIZED;
						break;


					// Refresh
					case IDCMP_REFRESHWINDOW:
						BeginRefresh(data->window);
						if (data->flags&READF_RESIZED)
							data->flags&=~READF_RESIZED;
						else read_show_text(data,0,0,0);
						EndRefresh(data->window,TRUE);
						break;


					// Menu
					case IDCMP_MENUPICK:
					{
						struct MenuItem *item;
						short itemid;

						// Loop while valid items
						while (item=ItemAddress(data->window->MenuStrip,(USHORT)msg_copy.Code))
						{
							// Get real ID
							itemid=(USHORT)(GTMENUITEM_USERDATA(item));

							switch (itemid)
							{
								// Next file
								case MENU_NEXT:
									quit_flag=1;
									break;

								// Quit
								case MENU_QUIT:
									quit_flag=2;
									break;

								// Tab size
								case MENU_TAB_1:
								case MENU_TAB_2:
								case MENU_TAB_4:
								case MENU_TAB_8:
									{
										short tab;

										// Get new tab size
										tab=itemid-MENU_TAB_1;
										tab=1<<tab;

										// Change?
										if (tab!=data->tab_size)
										{
											// Set busy pointer
											SetBusyPointer(data->window);

											// Update tab size
											data->tab_size=tab;

											// Get text width
											read_get_width(data);

											// Update scrollers
											read_calc_size(data);

											// Display text
											read_show_text(data,0,0,0);

											// Display title
											read_build_title(data);

											// Clear pointer
											ClearPointer(data->window);
										}
									}
									break;

								// Search
								case MENU_SEARCH:
									read_search(data,1);
									break;

								// Repeat search
								case MENU_REPEAT:
									read_search(data,0);
									break;

								// Save settings
								case MENU_SAVE:
								{
									char buf[80];

									// Set busy pointer
									SetBusyPointer(data->window);

									// Build variable string
									lsprintf(buf,"%ld/%ld/%ld/%ld/%ld/%ld/%ld/%ld/%ld/%ld/%s\n",
										data->window->LeftEdge,
										data->window->TopEdge,
										data->window->Width,
										data->window->Height,
										data->tab_size,
										data->search_flags,
										use_screen,
										(modeid>>16)&0xffff,
										modeid&0xffff,
										fontsize,
										fontname);

									// Set variable
									if (SetVar("dopus_read",buf,-1,GVF_GLOBAL_ONLY))
									{
										// Copy to ENVARC:
										SystemTagList("copy env:dopus_read envarc:",0);
									}

									// Clear busy pointer
									ClearPointer(data->window);
									break;
								}

								// Print
								case MENU_PRINT:
									read_print(data);
									break;


								// Mode
								case MENU_MODE_NORMAL:
								case MENU_MODE_ANSI:

									// Set busy pointer
									SetBusyPointer(data->window);

									// Change mode
									read_set_mode(data,
										(itemid==MENU_MODE_NORMAL)?
											MODE_NORMAL:MODE_ANSI);

									// Initialise display
									read_init(data);

									// Clear busy pointer
									ClearPointer(data->window);
									break;

								case MENU_MODE_HEX:

									// Already in hex mode?
									if (data->mode==MODE_HEX) break;

									// Change mode
									read_set_mode(data,MODE_HEX);

									// Initialise display
									read_init(data);
									break;


								// Use screen
								case MENU_USE_SCREEN:

									// Get state
									use_screen=(item->Flags&CHECKED)?1:0;
									item=0;

									// Close and re-open
									read_close_window(data);
									if (!(read_open_window(data))) break;
									read_set_mode(data,data->mode);
									read_init(data);
									break;


								// Pick screen mode
								case MENU_SCREEN_MODE:
									item=0;
									read_pick_screen_mode(data);
									break;

								// Pick font
								case MENU_SELECT_FONT:
									item=0;
									read_pick_font(data);
									break;
							}

							// Get next item
							if (item) msg_copy.Code=item->NextSelect;
							else break;

							// Check quit flag
							if (quit_flag) break;
						}
						break;
					}


					// BOOPSI gadget
					case IDCMP_IDCMPUPDATE:

						switch (GetTagData(GA_ID,0,(struct TagItem *)msg_copy.IAddress))
						{
							// Vertical slider
							case GAD_VERT_SCROLLER:
								{
									unsigned long top;

									// Get new top
									GetAttr(PGA_Top,data->vert_scroller,(ULONG *)&top);
									if (data->slider_div>1)
									{
										top=UMult32(top,data->slider_div);
										if (top+data->visible>data->lines)
											top=data->lines-data->visible;
									}

									// Scroll display
									if (top!=data->top) read_show_text(data,0,top-data->top,0);
								}
								break;

							// Scroll up
							case GAD_VERT_ARROW_UP:
								if (data->top>0)
									read_update_text(data,0,-1,0);
								break;

							// Scroll down
							case GAD_VERT_ARROW_DOWN:
								if (data->top+data->visible<data->lines)
									read_update_text(data,0,1,0);
								break;

							// Horizontal slider
							case GAD_HORIZ_SCROLLER:
								{
									long top;

									// Get new top
									GetAttr(PGA_Top,data->horiz_scroller,(ULONG *)&top);

									// Scroll display
									if (top!=data->left) read_show_text(data,top-data->left,0,0);
								}
								break;

							// Scroll left
							case GAD_HORIZ_ARROW_LEFT:
								if (data->left>0)
									read_update_text(data,-1,0,0);
								break;

							// Scroll right
							case GAD_HORIZ_ARROW_RIGHT:
								if (data->left+data->h_visible<data->columns)
									read_update_text(data,1,0,0);
								break;
						}
						break;


					// Key press
					case IDCMP_RAWKEY:

						switch (msg_copy.Code)
						{
							// Help?
							case 0x5f:

								// Valid main IPC?
								if (data->main_ipc &&
									!(msg_copy.Qualifier&VALID_QUALIFIERS))
								{
									// Set busy pointer
									SetBusyPointer(data->window);

									// Send help request
									IPC_Command(data->main_ipc,IPC_HELP,(1<<31),"Read",0,(struct MsgPort *)-1);

									// Clear busy pointer
									ClearPointer(data->window);
								}
								break;


							// Quit
							case 0x45:
							case 0x10:
								quit_flag=1;
								break;

							// Scroll up
							case CURSORUP:
							case 0x3e:

								// Ok to scroll up?
								if (data->top<=0) break;

								// Page up?
								if (msg_copy.Qualifier&(IEQUALIFIER_LSHIFT|IEQUALIFIER_RSHIFT))
									read_update_text(data,0,-(data->visible-1),0);

								// Top
								else if (msg_copy.Qualifier&IEQUALIFIER_CONTROL)
								{
									if (data->top>0)
										read_update_text(data,0,-data->top,0);
								}

								// Line up
								else read_update_text(data,0,-1,0);
								break;

							// Page up
							case 0x3f:
							case 0x41:
							case 0x16:

								// Ok to scroll up?
								if (data->top<=0) break;
								read_update_text(data,0,-(data->visible-1),0);
								break;

							// Home
							case 0x3d:
							case 0x14:
								if (data->top>0)
									read_update_text(data,0,-data->top,0);
								break;

							// Scroll down
							case CURSORDOWN:
							case 0x1e:

								// Ok to scroll down?
								if (data->top+data->visible>=data->lines) break;

								// Page down?
								if (msg_copy.Qualifier&(IEQUALIFIER_LSHIFT|IEQUALIFIER_RSHIFT))
									read_update_text(data,0,data->visible-1,0);

								// Bottom
								else if (msg_copy.Qualifier&IEQUALIFIER_CONTROL)
								{
									if (data->top<data->lines-data->visible)
										read_update_text(data,0,(data->lines-data->top)-data->visible,0);
								}

								// Line down
								else read_update_text(data,0,1,0);
								break;

							// Page down
							case 0x1f:
							case 0x40:
							case 0x22:

								// Ok to scroll down?
								if (data->top+data->visible>=data->lines) break;
								read_update_text(data,0,data->visible-1,0);
								break;

							// End
							case 0x1d:
							case 0x35:
								if (data->top<data->lines-data->visible)
									read_update_text(data,0,(data->lines-data->top)-data->visible,0);
								break;

							// Scroll left
							case CURSORLEFT:
							case 0x2d:

								// Ok to scroll left?
								if (data->left<=0) break;

								// Page left?
								if (msg_copy.Qualifier&(IEQUALIFIER_LSHIFT|IEQUALIFIER_RSHIFT))
									read_update_text(data,-data->h_visible,0,0);

								// Full left
								else if (msg_copy.Qualifier&IEQUALIFIER_CONTROL)
									read_update_text(data,-data->left,0,0);

								// Line up
								else read_update_text(data,-1,0,0);
								break;

							// Scroll right
							case CURSORRIGHT:
							case 0x2f:

								// Ok to scroll right?
								if (data->left+data->h_visible>=data->columns) break;

								// Page right?
								if (msg_copy.Qualifier&(IEQUALIFIER_LSHIFT|IEQUALIFIER_RSHIFT))
									read_update_text(data,data->h_visible,0,0);

								// Full right
								else if (msg_copy.Qualifier&IEQUALIFIER_CONTROL)
									read_update_text(data,(data->columns-data->left)-data->h_visible,0,0);

								// Line right
								else read_update_text(data,1,0,0);
								break;

							// Function keys
							case 0x50:
							case 0x51:
							case 0x52:
							case 0x53:
							case 0x54:
							case 0x55:
							case 0x56:
							case 0x57:
							case 0x58:
							case 0x59:
								{
									short percent;
									long line;

									// Can move?
									if (data->lines<=data->visible)
										break;

									// Get percentage
									percent=(msg_copy.Code-0x4f)*10;

									// Get line to jump to
									line=(data->lines*percent)/100;

									// Bounds check
									if (line+data->visible>data->lines)
										line=data->lines-data->visible;
									if (line<0) line=0;

									// Jump to mark
									if (line!=data->top)
										read_update_text(data,0,line-data->top,0);
								}
								break;


							// Search
							case 0x21:
								read_search(data,1);
								break;

							// Next
							case 0x36:
								read_search(data,0);
								break;

							// Print
							case 0x19:
								read_print(data);
								break;


							// C for copy
							case 0x33:

								// Right amiga must be down
								if (!(msg_copy.Qualifier&IEQUALIFIER_RCOMMAND))
									break;

								// Copy to clipboard
								read_clipboard_copy(data);
								break;
						}
						break;


					// Inactive window
					case IDCMP_INACTIVEWINDOW:

						// Turn into button up and fall through
						msg_copy.Code=SELECTUP;

					// Mouse button press
					case IDCMP_MOUSEBUTTONS:

						// Select down?
						if (msg_copy.Code==SELECTDOWN)
						{
							// Within text area and not in hex mode?
							if (msg_copy.MouseX>=data->text_box.MinX &&
								msg_copy.MouseY>=data->text_box.MinY &&
								msg_copy.MouseX<=data->text_box.MaxX &&
								msg_copy.MouseY<=data->text_box.MaxY &&
								data->mode!=MODE_HEX)
							{
								// Clear any old highlight
								if (data->sel_top_pos!=-1)
								{
									data->sel_top_pos=-1;
									read_update_text(data,1,1,0);
								}

								// Get new start position
								data->sel_top_pos=
									(msg_copy.MouseX-data->text_box.MinX)/
										data->window->RPort->TxWidth;
								data->sel_top_line=
									(msg_copy.MouseY-data->text_box.MinY)/
										data->window->RPort->TxHeight;

								// Add top position
								data->sel_top_pos+=data->left;
								data->sel_top_line+=data->top;

								// Copy to bottom position
								data->sel_bottom_pos=data->sel_top_pos;
								data->sel_bottom_line=data->sel_top_line;

								// Turn on mouse reporting and ticks and disable menus
								data->window->Flags|=WFLG_REPORTMOUSE|WFLG_RMBTRAP;
								ModifyIDCMP(data->window,
									data->window->IDCMPFlags|IDCMP_INTUITICKS);

								// Clear flag for ok
								data->flags&=~READF_HIGH_OK;
							}
						}

						// Select up?
						else if (msg_copy.Code==SELECTUP)
						{
							// Are we highlighting?
							if (data->window->Flags&WFLG_REPORTMOUSE)
							{
								// Turn off mouse reporting and ticks and enable menus
								data->window->Flags&=~(WFLG_REPORTMOUSE|WFLG_RMBTRAP);
								ModifyIDCMP(data->window,
									data->window->IDCMPFlags&~IDCMP_INTUITICKS);

								// Was the highlight ok?
								if (data->flags&READF_HIGH_OK)
								{
									// Check if end is before start
									if (data->sel_bottom_line<data->sel_top_line)
									{
										short pos,line;

										// Swap top and bottom
										pos=data->sel_top_pos;
										line=data->sel_top_line;
										data->sel_top_pos=data->sel_bottom_pos;
										data->sel_top_line=data->sel_bottom_line;
										data->sel_bottom_pos=pos;
										data->sel_bottom_line=line;
									}

									// Or on the same line
									else
									if (data->sel_bottom_line==data->sel_top_line &&
										data->sel_bottom_pos<data->sel_top_pos)
									{
										short pos;

										// Swap top and bottom
										pos=data->sel_top_pos;
										data->sel_top_pos=data->sel_bottom_pos;
										data->sel_bottom_pos=pos;
									}
								}

								// Otherwise, no highlight
								else data->sel_top_pos=-1;
							}
						}
						break;


					// Ticks
					case IDCMP_INTUITICKS:

						// Is mouse button down?
						if (!(msg_copy.Qualifier&IEQUALIFIER_LEFTBUTTON) ||
							!(data->window->Flags&WFLG_REPORTMOUSE))
							break;

						// Get scroll direction
						if (data->window->MouseY<data->text_box.MinY)
						{
							if (data->top==0) break;
							sel_dy=-1;
						}
						else if (data->window->MouseY>data->text_box.MaxY)
						{
							if (data->top+data->visible>=data->lines) break;
							sel_dy=1;
						}
						else if (data->window->MouseX<data->text_box.MinX)
						{
							if (data->left==0) break;
							sel_dx=-1;
						}
						else if (data->window->MouseX>data->text_box.MaxX)
						{
							if (data->left+data->h_visible>=data->columns) break;
							sel_dx=1;
						}
						else break;

						// Fall through

					// Mouse move
					case IDCMP_MOUSEMOVE:
						{
							short old_pos,old_line;

							// Is mouse button down?
							if (!(msg_copy.Qualifier&IEQUALIFIER_LEFTBUTTON) ||
								!(data->window->Flags&WFLG_REPORTMOUSE))
								break;

							// Save old end
							old_pos=data->sel_bottom_pos;
							old_line=data->sel_bottom_line;

							// Get end position
							data->sel_bottom_pos=
								(data->window->MouseX-data->text_box.MinX)/
										data->window->RPort->TxWidth;
							data->sel_bottom_line=
								(data->window->MouseY-data->text_box.MinY)/
									data->window->RPort->TxHeight;

							// Bounds check
							if (data->sel_bottom_pos<0)
								data->sel_bottom_pos=0;
							else if (data->sel_bottom_pos>=data->h_visible)
								data->sel_bottom_pos=data->h_visible-1;
							if (data->sel_bottom_line<0)
								data->sel_bottom_line=0;
							else if (data->sel_bottom_line>=data->visible)
								data->sel_bottom_line=data->visible-1;

							// Add top position
							data->sel_bottom_pos+=data->left;
							data->sel_bottom_line+=data->top;

							// Scrolling down?
							if (sel_dy==1) ++data->sel_bottom_line;

							// Scrolling up?
							else if (sel_dy==-1) --data->sel_bottom_line;

							// Scrolling right?
							else if (sel_dx==1) ++data->sel_bottom_pos;

							// Scrolling left?
							else if (sel_dx==-1) --data->sel_bottom_pos;

							// Has it changed?
							if (old_pos!=data->sel_bottom_pos ||
								old_line!=data->sel_bottom_line)
							{
								short show_two=0;

								// No scrolling?
								if (!sel_dx && !sel_dy)
								{
									// Redraw the whole screen	
									sel_dx=1;
									sel_dy=1;
								}
								else show_two=1;

								// Display text
								read_update_text(data,sel_dx,sel_dy,show_two);

								// Set flag for ok
								data->flags|=READF_HIGH_OK;
							}
						}
						break;
				}

				// If window is gone, quit
				if (!data->window)
				{
					quit_flag=1;
					break;
				}
			}
		}

		// Check quit flag
		if (quit_flag) break;

		// Wait for a message
		Wait(	((data->window)?(1<<data->window->UserPort->mp_SigBit):0)|
				((data->ipc)?(1<<data->ipc->command_port->mp_SigBit):0));
	}

	return (BOOL)((quit_flag==2)?0:1);
}


// Calculate window size and update scrollers
void read_calc_size(read_data *data)
{
	// Get text box size
	data->text_box.MinX=data->window->BorderLeft;
	data->text_box.MinY=data->window->BorderTop;
	data->text_box.MaxX=data->window->Width-data->window->BorderRight-1;
	data->text_box.MaxY=data->window->Height-data->window->BorderBottom-1;

	// Get visible lines and columns
	data->visible=data->window->GZZHeight/data->window->RPort->TxHeight;
	data->h_visible=data->window->GZZWidth/data->window->RPort->TxWidth;

	// Get division factor for slider
	data->slider_div=UDivMod32(data->lines,65535)+1;

	// Initialise scrollers
	my_SetGadgetAttrs(data->vert_scroller,data->window,
		PGA_Top,(data->slider_div>1)?UDivMod32(data->top,data->slider_div):data->top,
		PGA_Total,(data->slider_div>1)?UDivMod32(data->lines,data->slider_div):data->lines,
		PGA_Visible,(data->slider_div>1)?UDivMod32(data->visible,data->slider_div):data->visible,
		TAG_END);
	my_SetGadgetAttrs(data->horiz_scroller,data->window,
		PGA_Top,data->left,
		PGA_Total,data->columns,
		PGA_Visible,data->h_visible,
		TAG_END);

	// Get display rectangle
	data->disprect.MinX=data->window->BorderLeft;
	data->disprect.MinY=data->window->BorderTop;
	data->disprect.MaxX=(data->disprect.MinX+data->h_visible*data->window->RPort->TxWidth)-1;
	data->disprect.MaxY=(data->disprect.MinY+data->visible*data->window->RPort->TxHeight)-1;

	// Erase area outside of display
	if (data->disprect.MaxX<data->window->Width-data->window->BorderRight-1)
	{
		EraseRect(data->window->RPort,
			data->disprect.MaxX+1,
			data->disprect.MinY,
			data->window->Width-data->window->BorderRight-1,
			data->window->Height-data->window->BorderBottom-1);
	}
	if (data->disprect.MaxY<data->window->Height-data->window->BorderBottom-1)
	{
		EraseRect(data->window->RPort,
			data->disprect.MinX,
			data->disprect.MaxY+1,
			data->window->Width-data->window->BorderRight-1,
			data->window->Height-data->window->BorderBottom-1);
	}
}


// Initialise display
void read_init(read_data *data)
{
	// Get pen to use
	SetAPen(data->window->RPort,data->drawinfo->dri_Pens[TEXTPEN]);
	SetBPen(data->window->RPort,data->drawinfo->dri_Pens[BACKGROUNDPEN]);
	SetDrMd(data->window->RPort,JAM2);

	// Write mask
	if (data->mode==MODE_ANSI)
	{
		SetWrMsk(data->window->RPort,0xff);
	}
	else
	{
		SetWrMsk(data->window->RPort,data->drawinfo->dri_Pens[TEXTPEN]);
	}

	// Get text width
	read_get_width(data);

	// Update scrollers
	read_calc_size(data);

	// Display text
	read_show_text(data,0,0,0);

	// Display title
	read_build_title(data);
}


// Build title string
void read_build_title(read_data *data)
{
	struct MenuItem *item;
	short num;

	// Display title
	lsprintf(data->title,GetString(locale,MSG_FILE_TITLE),
		FilePart(data->file),
		data->date,
		data->lines,
		data->size,
		mode_string[data->mode],
		data->tab_size);
	SetWindowTitles(data->window,data->title,(char *)-1);

	// Remove menu
	ClearMenuStrip(data->window);

	// Fix tab checkmarks
	for (num=0;num<4;num++)
	{
		// Get item
		if (item=FindMenuItem(data->menus,MENU_TAB_1+num))
		{
			// Check or uncheck as appropriate
			if (data->tab_size==(1<<num)) item->Flags|=CHECKED;
			else item->Flags&=~CHECKED;
		}
	}

	// Fix mode checkmarks
	for (num=0;num<3;num++)
	{
		// Get item
		if (item=FindMenuItem(data->menus,MENU_MODE_NORMAL+num))
		{
			// Check or uncheck as appropriate
			if (data->mode==num) item->Flags|=CHECKED;
			else item->Flags&=~CHECKED;
		}
	}

	// Fix use screen
	if (item=FindMenuItem(data->menus,MENU_USE_SCREEN))
	{
		// Check, etc
		if (data->my_screen) item->Flags|=CHECKED;
		else item->Flags&=~CHECKED;
	}

	// If using ASL 38+, fix Pick screen mode
	if (AslBase->lib_Version>=38)
	{
		if (item=FindMenuItem(data->menus,MENU_SCREEN_MODE))
		{
			if (data->my_screen) item->Flags|=ITEMENABLED;
			else item->Flags&=~ITEMENABLED;
		}
	}

	// Reattach menus
	ResetMenuStrip(data->window,data->menus);
}


// Update text and scroller display
void read_update_text(read_data *data,long dx,long dy,short show_two)
{
	// Display text
	read_show_text(data,dx,dy,show_two);

	// Update scrollers
	if (dx==dy || dy)
		my_SetGadgetAttrs(data->vert_scroller,data->window,
			PGA_Top,(data->slider_div>1)?UDivMod32(data->top,data->slider_div):data->top,
			TAG_END);
	if (dx==dy || dx)
		my_SetGadgetAttrs(data->horiz_scroller,data->window,
			PGA_Top,data->left,
			TAG_END);
}


// Display text
void read_show_text(read_data *data,long dx,long dy,short show_two)
{
	short topline,botline;
	short old_left,old_top;
	long line;
	read_line *text_line;
	BOOL redisplay=0;

	// No lines?
	if (data->lines<1) return;

	// Display all lines by default
	topline=0;
	botline=data->visible-1;

	// Save old positions
	old_left=data->left;
	old_top=data->top;

	// If dx and dy are both set, just redisplay without clearing
	if (dx && dy)
	{
		dx=dy=0;
		redisplay=1;
	}

	// Store new positions	
	data->left+=dx;
	data->top+=dy;

	// Bounds check horizontal
	if (data->left+data->h_visible>data->columns)
		data->left=data->columns-data->h_visible;
	if (data->left<0) data->left=0;

	// Bounds check vertical
	if (data->top+data->visible>data->lines)
	{
		data->top=data->lines-data->visible;
		data->top_line=0;
	}
	if (data->top<0)
	{
		data->top=0;
		data->top_line=0;
	}

	// Get checked deltas
	dx=data->left-old_left;
	dy=data->top-old_top;

	// Scroll horizontally?
	if (dx && ABS(dx)<data->h_visible)
	{
		// Scroll
		ScrollRaster(data->window->RPort,
			dx*data->window->RPort->TxWidth,
			0,
			data->disprect.MinX,
			data->disprect.MinY,
			data->disprect.MaxX,
			data->disprect.MaxY);
	}

	// Scroll vertically
	else if (dy && ABS(dy)<data->visible)
	{
		// Scroll
		ScrollRaster(data->window->RPort,
			0,
			dy*data->window->RPort->TxHeight,
			data->disprect.MinX,
			data->disprect.MinY,
			data->disprect.MaxX,
			data->disprect.MaxY);

		// Scroll down?
		if (dy>0)
		{
			// Display bottom of view
			topline=data->visible-dy-show_two;
			botline=data->visible-1;

			// Get new top line
			if (data->top_line && data->mode!=MODE_HEX)
			{
				while (dy>0 && data->top_line->node.mln_Succ->mln_Succ)
				{
					data->top_line=(read_line *)data->top_line->node.mln_Succ;
					--dy;
				}
			}
		}

		// Scroll up
		else
		{
			// Display top of view
			topline=0;
			botline=(-dy-1)+show_two;

			// Get new top line
			if (data->top_line && data->mode!=MODE_HEX)
			{
				while (dy<0 && data->top_line->node.mln_Pred->mln_Pred)
				{
					data->top_line=(read_line *)data->top_line->node.mln_Pred;
					++dy;
				}
			}
		}
	}

	// Redraw full screen
	else if (!redisplay)
	{
		data->top_line=0;
		EraseRect(data->window->RPort,
			data->disprect.MinX,
			data->disprect.MinY,
			data->disprect.MaxX,
			data->disprect.MaxY);
	}

	// In hex mode, get top position
	if (data->mode==MODE_HEX)
	{
		data->top_position=data->text_buffer+data->top*HEX_DISPLAY_WIDTH;
		text_line=(read_line *)data->top_position;
	}

	// Normal text mode
	else
	{
		// No valid top line?
		if (!data->top_line)
		{
			for (line=0,text_line=(read_line *)data->text.mlh_Head;
				line<data->top && text_line->node.mln_Succ;
				line++,text_line=(read_line *)text_line->node.mln_Succ);
			data->top_line=text_line;
		}
		text_line=data->top_line;
	}

	// Display text
	for (line=0;line<data->visible;line++)
	{
		// Ok to display?
		if (line>=topline && line<=botline)
		{
			// Display text
			read_display_text(data,text_line,line,dx);

			// Search line?
			if (data->search_line && data->search_line==text_line)
			{
				// Show search text
				read_show_search(data,line,dx);
			}
		}

		// Get next line
		if (data->mode==MODE_HEX)
		{
			if (line+data->top>=data->lines-1) text_line=0;
			else text_line=(read_line *)(((char *)text_line)+HEX_DISPLAY_WIDTH);
		}
		else if (text_line) text_line=(read_line *)text_line->node.mln_Succ;
	}
}


// Display a line of text
void read_display_text(read_data *data,read_line *text,long line,short dx)
{
	short c_x,cp,start,len,length,left_start,left_end;
	short x_pos,y_pos,vispos=-1;
	short highlight=0,highlight_start_pos=-1,highlight_end_pos=-1;
	short real_line;
	char *textptr;
	unsigned char fpen,bpen,pen=0;
	struct Rectangle high_box;

	// Valid text?
	if (!text || (data->mode!=MODE_HEX && (!text->node.mln_Succ || text->length<1)))
		return;

	// Get position
	x_pos=data->disprect.MinX;
	y_pos=data->disprect.MinY+line*data->window->RPort->TxHeight;

	// Initial end positions
	left_start=data->left;
	left_end=data->left+data->h_visible;

	// Drawing end of line only?
	if (dx>0)
	{
		x_pos=data->disprect.MaxX-dx*data->window->RPort->TxWidth+1;
		if (x_pos<data->disprect.MinX) x_pos=data->disprect.MinX;
		left_start=left_end-dx;
		if (left_start<data->left) left_start=data->left;
	}

	// Or beginning of line?
	else if (dx<0)
	{
		left_end=left_start-dx;
		if (left_end>data->left+data->h_visible)
			left_end=data->left+data->h_visible;
	}

	// Position for text
	Move(data->window->RPort,
		x_pos,
		y_pos+data->window->RPort->TxBaseline);

	// Reset colour and style (if in ANSI mode)
	if (data->mode==MODE_ANSI)
	{
		// Get pens
		fpen=data->drawinfo->dri_Pens[TEXTPEN];
		bpen=data->drawinfo->dri_Pens[BACKGROUNDPEN];

		// Reset colour
		if (GfxBase->lib_Version>=39)
		{
			SetABPenDrMd(data->window->RPort,fpen,bpen,JAM2);
		}
		else
		{
			SetAPen(data->window->RPort,fpen);
			SetBPen(data->window->RPort,bpen);
		}

		// Style (if necessary)
		if (data->style)
		{
			SetSoftStyle(data->window->RPort,0,FSF_BOLD|FSF_ITALIC|FSF_UNDERLINED);
			data->style=0;
		}
	}

	// Hex display?
	if (data->mode==MODE_HEX)
	{
		short cp;
		char *ptr;

		// Get text pointer and length
		textptr=(char *)text;
		if (textptr+HEX_DISPLAY_WIDTH>data->text_buffer+data->text_buffer_size)
			length=data->text_buffer+data->text_buffer_size-textptr;
		else length=HEX_DISPLAY_WIDTH;

		// Start hex display
		lsprintf(data->hex_display,"%08lx:",(data->top+line)*HEX_DISPLAY_WIDTH);

		// Hex values
		ptr=data->hex_display+9;
		for (cp=0;cp<length;cp++)
		{
			// Space every four
			if (cp%4==0) *ptr++=' ';
			lsprintf(ptr,"%02lx",((unsigned char *)textptr)[cp]);
			ptr+=2;
		}

		// Fill with spaces
		for (;cp<HEX_DISPLAY_WIDTH;cp++)
		{
			// Extra space every four
			if (cp%4==0) *ptr++=' ';
			*ptr++=' ';
			*ptr++=' ';
		}

		// Space
		*ptr++=' ';

		// ASCII characters
		for (cp=0;cp<length;cp++)
		{
			unsigned char ch;

			// Non-printable?
			ch=textptr[cp];
			if (ch<0x20 || (ch>0x7e && ch<0xc0)) *ptr++='.';
			else *ptr++=ch;
		}

		// Get length and real text pointer
		length=ptr-data->hex_display;
		textptr=data->hex_display;
	}
	else
	{
		// Normal text display
		length=text->length;
		textptr=text->text;

		// Highlight?
		if (data->sel_top_pos!=-1)
		{
			// Get highlight box
			if (data->sel_bottom_line<data->sel_top_line)
			{
				high_box.MinX=data->sel_bottom_pos;
				high_box.MinY=data->sel_bottom_line;
				high_box.MaxX=data->sel_top_pos;
				high_box.MaxY=data->sel_top_line;
			}
			else if (data->sel_top_line<data->sel_bottom_line ||
				data->sel_top_pos<data->sel_bottom_pos)
			{
				high_box.MinX=data->sel_top_pos;
				high_box.MinY=data->sel_top_line;
				high_box.MaxX=data->sel_bottom_pos;
				high_box.MaxY=data->sel_bottom_line;
			}
			else
			{
				high_box.MinX=data->sel_bottom_pos;
				high_box.MinY=data->sel_top_line;
				high_box.MaxX=data->sel_top_pos;
				high_box.MaxY=data->sel_bottom_line;
			}

			// Is this within the highlight area?
			real_line=line+data->top;
			if (real_line>=high_box.MinY && real_line<=high_box.MaxY)
			{
				// Flag highlight on
				highlight=1;

				// First highlight line?
				if (real_line==high_box.MinY)
				{
					// Get position to highlight from
					highlight_start_pos=high_box.MinX;
				}

				// Last highlight line?
				if (real_line==high_box.MaxY)
				{
					// Get position to highlight to
					highlight_end_pos=high_box.MaxX+1;
				}

				// Highlight from start of line?
				if (real_line!=high_box.MinY)
				{
					// Set inverse mode
					SetDrMd(data->window->RPort,INVERSVID|JAM2);
					highlight=2;
				}
			}
		}
	}

	// Go through text
	for (cp=0,c_x=0,start=0,len=0;cp<=length;cp++)
	{
		// Need to output existing text?
		if (textptr[cp]=='\t' || cp==length || textptr[cp]=='\x1b' || textptr[cp]=='\r' ||
			c_x+len>=left_end ||
			(highlight &&
				((real_line==high_box.MinY && c_x+len==highlight_start_pos) ||
				 (real_line==high_box.MaxY && c_x+len==highlight_end_pos))))
		{
			struct TextExtent extent;
			BOOL ansi=0;

			// Make sure text is visible at left
			while (c_x<left_start && start<length)
			{
				// Tab?
				if (textptr[start]=='\t')
				{
					// Move text position to next tab stop
					c_x=((c_x+data->tab_size)/data->tab_size)*data->tab_size;

					// Now in view?
					if (c_x>left_start)
					{
						// Move across to tab stop
						Move(data->window->RPort,
							data->disprect.MinX+(c_x-data->left)*data->window->RPort->TxWidth,
							data->window->RPort->cp_y);
					}
				}

				// Escape sequence?
				else if (textptr[start]=='\x1b') ansi=1;

				// End of escape sequence?
				else if (ansi)
				{
					if ((textptr[start]>='A' && textptr[start]<='Z') ||
						(textptr[start]>='a' && textptr[start]<='z')) ansi=0;
				}

				// Normal character
				else
				{
					++c_x;
					--len;
				}

				++start;
			}

			// First visible character?
			if (vispos==-1) vispos=start;

			// Any text?
			if (len>0)
			{
				// Get length that will fit
				len=TextFit(
					data->window->RPort,
					textptr+start,
					len,
					&extent,
					0,1,
					(data->disprect.MaxX-data->window->RPort->cp_x)+1,
					data->window->RPort->TxHeight);

				// Output text
				Text(data->window->RPort,textptr+start,len);
				c_x+=len;
			}

			// Restart
			len=0;

			// Highlight?
			if (highlight)
			{
				// First line?
				if (real_line==high_box.MinY &&
					highlight==1 &&
					c_x>=highlight_start_pos)
				{
					// ANSI mode?
					if (data->mode==MODE_ANSI)
					{
						// Save pens
						fpen=data->window->RPort->FgPen;
						bpen=data->window->RPort->BgPen;
						pen=1;

						// Set pens
						SetAPen(data->window->RPort,data->drawinfo->dri_Pens[TEXTPEN]);
						SetBPen(data->window->RPort,data->drawinfo->dri_Pens[BACKGROUNDPEN]);

						// Clear styles
						SetSoftStyle(data->window->RPort,0,FSF_BOLD|FSF_ITALIC|FSF_UNDERLINED);
					}

					// Turn highlighting on
					SetDrMd(data->window->RPort,INVERSVID|JAM2);
					highlight=2;
				}

				// Last line?
				else
				if (real_line==high_box.MaxY &&
					highlight==2 &&
					c_x>=highlight_end_pos)
				{
					// Turn it off
					SetDrMd(data->window->RPort,JAM2);
					highlight=-1;

					// Fix pens and style
					if (pen)
					{
						SetAPen(data->window->RPort,fpen);
						SetBPen(data->window->RPort,bpen);

						SetSoftStyle(
							data->window->RPort,
							data->style,
							FSF_BOLD|FSF_ITALIC|FSF_UNDERLINED);
					}
				}
			}
		}

		// Escape sequence?
		if (textptr[cp]=='\x1b')
		{
			// In normal mode, skip to end of sequence
			if (data->mode==MODE_NORMAL)
			{
				// Look for end of sequence (or line)
				while (cp<=length &&
					(textptr[cp]<'A' ||
					(textptr[cp]>'Z' && textptr[cp]<'a') ||
					textptr[cp]>'z'))
				{
					++cp;
				}
			}

			// In ansi mode, parse to end of sequence
			else if (data->mode==MODE_ANSI)
			{
				char num_buf[8];
				short num_pos=0,num_vals[12],num_count=0;

				// Look for end of sequence (or line)
				while (cp<=length)
				{
					// Numeric?
					if (textptr[cp]>='0' && textptr[cp]<='9')
					{
						num_buf[num_pos++]=textptr[cp];
					}

					// End of a number?
					if (textptr[cp]<'0' || textptr[cp]>'9' || num_pos==7)
					{
						// Get value
						if (num_pos>0)
						{
							num_buf[num_pos]=0;
							if (num_count<12) num_vals[num_count++]=atoi(num_buf);
							num_pos=0;
						}
					}

					// End of sequence?
					if ((textptr[cp]>='A' && textptr[cp]<='Z') ||
						(textptr[cp]>='a' && textptr[cp]<='z')) break;
					++cp;
				}

				// Only understand 'm' (SGR)
				if (textptr[cp]=='m' && num_count>0)
				{
					short a;
					long style=data->style;

					// Look at values
					for (a=0;a<num_count;a++)
					{
						// Foreground colour?
						if (num_vals[a]>=30 && num_vals[a]<=37)
						{
							fpen=data->ansi_pen_array[num_vals[a]-30];
							if (highlight==2) pen=1;
							else
							SetAPen(
								data->window->RPort,
								data->ansi_pen_array[num_vals[a]-30]);
						}

						// Background colour?
						else if (num_vals[a]>=40 && num_vals[a]<=47)
						{
							bpen=data->ansi_pen_array[num_vals[a]-40];
							if (highlight==2) pen=1;
							else
							SetBPen(
								data->window->RPort,
								data->ansi_pen_array[num_vals[a]-40]);
						}

						// Style
						if (num_vals[a]==0)
						{
							fpen=data->drawinfo->dri_Pens[TEXTPEN];
							bpen=data->drawinfo->dri_Pens[BACKGROUNDPEN];
							if (highlight==2) pen=1;
							else
							{
								SetAPen(data->window->RPort,data->drawinfo->dri_Pens[TEXTPEN]);
								SetBPen(data->window->RPort,data->drawinfo->dri_Pens[BACKGROUNDPEN]);
							}
							style=0;
						}
						else if (num_vals[a]==1) style|=FSF_BOLD;
						else if (num_vals[a]==3) style|=FSF_ITALIC;
						else if (num_vals[a]==4) style|=FSF_UNDERLINED;
						else if (num_vals[a]==22) style&=~FSF_BOLD;
						else if (num_vals[a]==23) style&=~FSF_ITALIC;
						else if (num_vals[a]==24) style&=~FSF_UNDERLINED;

						// Need to change style?
						if (style!=data->style)
						{
							if (highlight==2) pen=1;
							else
							SetSoftStyle(
								data->window->RPort,
								style,
								FSF_BOLD|FSF_ITALIC|FSF_UNDERLINED);
							data->style=style;
						}
					}
				}
			}
		}

		// Visible?
		else if (textptr[cp]!='\r' && cp>=vispos)
		{
			// Tab?
			if (textptr[cp]=='\t')
			{
				short x;

				// Get next tab stop
				c_x=((c_x+data->tab_size)/data->tab_size)*data->tab_size;

				// Get new position
				x=data->disprect.MinX+(c_x-data->left)*data->window->RPort->TxWidth;
				if (x>=data->disprect.MaxX) x=data->disprect.MaxX;

				// Move across to tab stop
				Move(data->window->RPort,
					x,
					data->window->RPort->cp_y);
			}

			// Normal character
			else
			{
				// First in a run?
				if (len==0) start=cp;
				++len;
			}
		}

		// Reached end of display?
		if (c_x>=left_end) break;
	}

	// Fix draw mode if we were highlighting
	if (highlight) SetDrMd(data->window->RPort,JAM2);
}


// Get maximum text width
void read_get_width(read_data *data)
{
	short max=0;
	read_line *text;

	// Hex mode?
	if (data->mode==MODE_HEX)
	{
		max=10+HEX_DISPLAY_WIDTH*2+(HEX_DISPLAY_WIDTH/4)+HEX_DISPLAY_WIDTH;
	}

	// Normal text
	else
	{
		// Go through text
		for (text=(read_line *)data->text.mlh_Head;text->node.mln_Succ;text=(read_line *)text->node.mln_Succ)
		{
			short c_x,len;
			char *ptr;

			// Go through line
			for (len=0,c_x=0,ptr=text->text;len<text->length;len++,ptr++)
			{
				// Tab?
				if (*ptr=='\t')
				{
					// Move to next tab stop
					c_x=((c_x+data->tab_size)/data->tab_size)*data->tab_size;
				}

				// Ansi sequence?
				else if (*ptr=='\x1b')
				{
					// Look for end of sequence (or line)
					while (len<=text->length &&
						(*ptr<'A' || (*ptr>'Z' && *ptr<'a') || *ptr>'z'))
					{
						++len;
						++ptr;
					}
				}

				// Normal character
				else ++c_x;
			}

			// Longest line yet?
			if (c_x>max) max=c_x;
		}
	}

	// Store text width
	data->columns=max;
}


// Search
void read_search(read_data *data,BOOL prompt)
{
	read_line *line=0;
	long linepos;
	BOOL found=0;

	// Set busy pointer in parent
	SetBusyPointer(data->window);

	// Ask for search string?
	if (prompt || !data->search_text[0])
	{
		NewConfigWindow newwin;
		struct Window *window;
		ObjectList *objlist;
		BOOL cancel=1,reset=1;

		// Fill out new window
		newwin.parent=data->window;
		newwin.dims=&search_window;
		newwin.title=GetString(locale,MSG_MENU_SEARCH);
		newwin.locale=locale;
		newwin.port=0;
		newwin.flags=WINDOW_VISITOR|WINDOW_AUTO_KEYS|WINDOW_REQ_FILL;
		newwin.font=0;

		// Open window
		if (!(window=OpenConfigWindow(&newwin)) ||
			!(objlist=AddObjectList(window,search_objects)))
		{
			CloseConfigWindow(window);
			ClearPointer(data->window);
			return;
		}

		// Initial settings
		SetGadgetValue(objlist,GAD_SEARCH_TEXT,(ULONG)data->search_text);
		SetGadgetValue(objlist,GAD_SEARCH_CASE,data->search_flags&SEARCHF_NOCASE);
		SetGadgetValue(objlist,GAD_SEARCH_WILD,data->search_flags&SEARCHF_WILDCARD);
		SetGadgetValue(objlist,GAD_SEARCH_ONLYWORD,data->search_flags&SEARCHF_ONLYWORDS);
		SetGadgetValue(objlist,GAD_SEARCH_REVERSE,data->search_flags&SEARCHF_REVERSE);

		// Activate text field
		ActivateStrGad(GADGET(GetObject(objlist,GAD_SEARCH_TEXT)),window);

		// Event loop
		FOREVER
		{
			struct IntuiMessage *msg;
			BOOL break_flag=0;

			// Any Intuition messages?
			while (msg=GetWindowMsg(window->UserPort))
			{
				struct IntuiMessage copy_msg;

				// Copy message and reply
				copy_msg=*msg;
				ReplyWindowMsg(msg);

				// Gadget?
				if (copy_msg.Class==IDCMP_GADGETUP)
				{
					// Look at gadget ID
					switch (((struct Gadget *)copy_msg.IAddress)->GadgetID)
					{
						// Okay
						case GAD_SEARCH_TEXT:
						case GAD_SEARCH_OKAY:

							// Store flags
							data->search_flags=0;
							if (GetGadgetValue(objlist,GAD_SEARCH_CASE))
								data->search_flags|=SEARCHF_NOCASE;
							if (GetGadgetValue(objlist,GAD_SEARCH_WILD))
								data->search_flags|=SEARCHF_WILDCARD;
							if (GetGadgetValue(objlist,GAD_SEARCH_ONLYWORD))
								data->search_flags|=SEARCHF_ONLYWORDS;
							if (GetGadgetValue(objlist,GAD_SEARCH_REVERSE))
								data->search_flags|=SEARCHF_REVERSE;

							// Get search text
							if (strcmp(data->search_text,(char *)GetGadgetValue(objlist,GAD_SEARCH_TEXT)))
								strcpy(data->search_text,(char *)GetGadgetValue(objlist,GAD_SEARCH_TEXT));
							else reset=0;
							cancel=0;

						// Cancel
						case GAD_SEARCH_CANCEL:
							break_flag=1;
							break;
					}
				}

				// Close window?
				else if (copy_msg.Class==IDCMP_CLOSEWINDOW)
					break_flag=1;
			}

			// Check break flag
			if (break_flag) break;

			// Wait for an event
			Wait(1<<window->UserPort->mp_SigBit);
		}

		// Close window
		CloseConfigWindow(window);

		// Cancelled?
		if (cancel || !data->search_text[0])
		{
			// Clear busy pointer
			ClearPointer(data->window);
			return;
		}

		// No current selection if text changed
		if (reset)
		{
			data->search_line=0;
			data->search_char=0;
		}
	}

	// Get line to search from
	if (data->search_line)
	{
		read_line *test;

		// Old search line
		line=data->search_line;

		// Hex
		if (data->mode==MODE_HEX)
		{
			// See if it's visible
			if ((char *)line<data->top_position &&
				(char *)line>=data->top_position+(data->visible*HEX_DISPLAY_WIDTH)) line=0;
		}

		// Normal text
		else
		{
			// See if it's visible
			for (test=data->top_line,linepos=0;
				test!=line && linepos<data->visible-1;
				test=(read_line *)test->node.mln_Succ,linepos++);

			// Not visible?
			if (test!=line) line=0;
		}
	}

	// Start from top/bottom
	if (!line)
	{
		// Reverse; search from bottom
		if (data->search_flags&SEARCHF_REVERSE)
		{
			// Hex?
			if (data->mode==MODE_HEX) line=(read_line *)(data->text_buffer+(data->lines-1)*HEX_DISPLAY_WIDTH);

			// Normal text
			else
			{
				for (line=data->top_line,linepos=0;
					line->node.mln_Succ && line->node.mln_Succ->mln_Succ && linepos<data->visible-1;
					line=(read_line *)line->node.mln_Succ,linepos++);
			}
		}

		// Search from top
		else if (data->mode==MODE_HEX) line=(read_line *)data->text_buffer;
		else line=data->top_line;
	}

	// Hex search?
	if (data->mode==MODE_HEX)
	{
		// Search through file
		while ((char *)line>=data->text_buffer &&
			(char *)line<data->text_buffer+data->text_buffer_size)
		{
			// Search this line
			if (read_search_line(data,line,(line==data->search_line)?data->search_char+1:0))
			{
				// Found
				found=1;
				break;
			}

			// Next line
			if (data->search_flags&SEARCHF_REVERSE)
				line=(read_line *)(((char *)line)-16);
			else line=(read_line *)(((char *)line)+16);
		}
	}

	// Normal text
	else
	{
		// Go through lines
		while (line->node.mln_Succ && line->node.mln_Pred)
		{
			// Search this line
			if (read_search_line(data,line,(line==data->search_line)?data->search_char+1:0))
			{
				// Found
				found=1;
				break;
			}

			// Next line
			if (data->search_flags&SEARCHF_REVERSE)
				line=(read_line *)line->node.mln_Pred;
			else line=(read_line *)line->node.mln_Succ;
		}
	}

	// Remove current highlight
	read_remove_highlight(data);

	// Not found?
	if (!found)
	{
		// Display requester
		SimpleRequest(
			data->window,
			GetString(locale,MSG_MENU_SEARCH),
			GetString(locale,MSG_OK_BUTTON),
			GetString(locale,MSG_STRING_NOT_FOUND),0,0,0,0);

		// No current selection
		data->search_line=0;
		data->search_char=0;
	}

	// Found
	else
	{
		// Get line match is on
		if (data->mode==MODE_HEX)
		{
			linepos=((char *)data->search_line-data->text_buffer)/HEX_DISPLAY_WIDTH;
		}
		else
		{
			for (linepos=0,line=(read_line *)data->text.mlh_Head;
				line!=data->search_line && line->node.mln_Succ;
				++linepos,line=(read_line *)line->node.mln_Succ);
		}

		// Is line off-screen?
		if (linepos<data->top) read_update_text(data,0,linepos-data->top,0);
		else if (linepos>=data->top+data->visible) read_update_text(data,0,linepos+1-(data->top+data->visible),0);

		// No, highlight text
		else read_show_search(data,linepos-data->top,0);
	}

	// Clear busy pointer
	ClearPointer(data->window);
}


// Search a line of text
BOOL read_search_line(read_data *data,read_line *line,short start)
{
	short matchstart=-1,matchpos=0;
	short length;
	char *textptr;

	// Get length and text pointer
	if (data->mode==MODE_HEX)
	{
		textptr=(char *)line;
		if (textptr+HEX_DISPLAY_WIDTH>data->text_buffer+data->text_buffer_size)
			length=data->text_buffer+data->text_buffer_size-textptr;
		else length=HEX_DISPLAY_WIDTH;
	}
	else
	{
		textptr=line->text;
		length=line->length;
	}

	// Search line
	for (;start<length;start++)
	{
		BOOL match=0;

		// Match?
		if (data->search_flags&SEARCHF_WILDCARD && data->search_text[matchpos]=='?')
			match=1;
		else if (data->search_flags&SEARCHF_NOCASE)
		{
			if (toupper(textptr[start])==toupper(data->search_text[matchpos]))
				match=1;
		}
		else if (textptr[start]==data->search_text[matchpos])
			match=1;

		if (match)
		{
			// Start of match?
			if (matchstart==-1) matchstart=start;

			// Increment match position
			++matchpos;

			// End of match?
			if (data->search_text[matchpos]==0)
			{
				// Only words?
				if (data->search_flags&SEARCHF_ONLYWORDS)
				{
					match=0;

					// Character before match string must be valid (or start of line)
					if (matchstart==0 ||
						isspace(textptr[matchstart-1]) ||
						ispunct(textptr[matchstart-1]))
					{
						// Character after match string must be likewise
						if (matchstart+matchpos>length ||
							isspace(textptr[matchstart+matchpos]) ||
							ispunct(textptr[matchstart+matchpos])) match=1;
					}
				}

				// Still valid match?
				if (match)
				{
					// Store match location
					data->search_line=line;
					data->search_char=matchstart;
					data->search_len=matchpos;
					return 1;
				}

				// Failed only-words test, reset
				matchstart=-1;
				matchpos=0;
			}
		}

		// No match
		else if (matchpos)
		{
			matchstart=-1;
			matchpos=0;
		}
	}

	// No match
	return 0;
}


// Show search text
void read_show_search(read_data *data,long line,short dx)
{
	short c_x,c_xend,cp;
	short length,xoff;
	char *textptr;

	// Get length and text pointer
	if (data->mode==MODE_HEX)
	{
		textptr=(char *)data->search_line;
		if (textptr+HEX_DISPLAY_WIDTH>data->text_buffer+data->text_buffer_size)
			length=data->text_buffer+data->text_buffer_size-textptr;
		else length=HEX_DISPLAY_WIDTH;
	}
	else
	{
		textptr=data->search_line->text;
		length=data->search_line->length;
	}

	// Find horiztonal position of search text
	for (cp=0,c_x=0;cp<data->search_char && cp<length;cp++)
	{
		// Not hex mode?
		if (data->mode!=MODE_HEX)
		{
			// Tab?
			if (textptr[cp]=='\t')
			{
				// Move to next tab stop
				c_x=((c_x+data->tab_size)/data->tab_size)*data->tab_size;
			}

			// Ansi sequence
			else if (textptr[cp]=='\x1b')
			{
				// Look for end of sequence (or line)
				while (cp<=length &&
					(textptr[cp]<'A' ||
					(textptr[cp]>'Z' && textptr[cp]<'a') ||
					textptr[cp]>'z'))
				{
					++cp;
				}
			}

			// Normal character
			else ++c_x;
		}

		// Normal character
		else ++c_x;
	}

	// Get end of search text
	for (c_xend=c_x;cp<data->search_char+data->search_len-1 && cp<length;cp++)
	{
		// Not hex mode?
		if (data->mode!=MODE_HEX)
		{
			// Tab?
			if (textptr[cp]=='\t')
			{
				// Move to next tab stop
				c_xend=((c_xend+data->tab_size)/data->tab_size)*data->tab_size;
			}

			// Ansi sequence
			else if (textptr[cp]=='\x1b')
			{
				// Look for end of sequence (or line)
				while (cp<=length &&
					(textptr[cp]<'A' ||
					(textptr[cp]>'Z' && textptr[cp]<'a') ||
					textptr[cp]>'z'))
				{
					++cp;
				}
			}

			// Normal character
			else ++c_xend;
		}

		// Normal character
		else ++c_xend;
	}

	// Save for posterity's sake
	data->search_last_line=data->search_line;
	data->search_last_linepos=data->top+line;
	data->search_last_c_x=c_x;
	data->search_last_c_xend=c_xend;

	// Adjust position for left scroll
	c_x-=data->left;
	c_xend-=data->left;

	// Off screen completely?
	if (c_x>data->h_visible || c_xend<0) return;

	// Only draw end of line?
	if (dx>0 && dx<data->h_visible)
	{
		if (c_xend<data->h_visible-1) return;
		c_x=data->h_visible-dx;
	}

	// Or beginning of line?
	else if (dx<0 && dx>-data->h_visible)
	{
		if (c_x>0) return;
		c_xend=-dx-1;
	}

	// Bounds check
	if (c_x<0) c_x=0;
	if (c_xend>=data->h_visible) c_xend=data->h_visible-1;

	// Get x-offset for hex
	if (data->mode==MODE_HEX)
	{
		xoff=(46-data->left)*data->window->RPort->TxWidth;
	}
	else xoff=0;

	// Highlight text
	ClipBlit(data->window->RPort,
		0,0,
		data->window->RPort,
		data->disprect.MinX+c_x*data->window->RPort->TxWidth+xoff,
		data->disprect.MinY+line*data->window->RPort->TxHeight,
		((c_xend-c_x)+1)*data->window->RPort->TxWidth,
		data->window->RPort->TxHeight,
		0x50);
}


// Remove search highlight
void read_remove_highlight(read_data *data)
{
	// Valid line?	
	if (data->search_last_line)
	{
		// Is line visible?
		if (data->search_last_linepos>=data->top &&
			data->search_last_linepos<data->top+data->visible)
		{
			// Show line
			read_display_text(data,data->search_last_line,data->search_last_linepos-data->top,0);
		}
		data->search_last_line=0;
	}
}


// varargs SetGadgetAttrs()
ULONG __stdargs my_SetGadgetAttrs(struct Gadget *gadget,struct Window *window,Tag tag,...)
{
	return SetGadgetAttrsA(gadget,window,0,(struct TagItem *)&tag);
}


// Parse number out of string
void read_parse_set(char **ptr,unsigned short *val)
{
	// Digit?
	if (isdigit(*(*ptr)))
	{
		*val=atoi(*ptr);
		while (*(*ptr) && isdigit(*(*ptr))) ++*ptr;
		while (*(*ptr) && !isdigit(*(*ptr))) ++*ptr;
	}
}


// Pick a screen mode to use
BOOL read_pick_screen_mode(read_data *data)
{
	APTR request;

	// Allocate an ASL request
	if (!(request=my_AllocAslRequestTags(
		ASL_ScreenModeRequest,
		ASLSM_Window,data->window,
		ASLSM_SleepWindow,TRUE,
		ASLSM_InitialDisplayID,GetVPModeID(&data->window->WScreen->ViewPort),
		ASLSM_MinWidth,640,
		ASLSM_MinDepth,2,
		TAG_END))) return 1;

	// Show requester
	if (!(AslRequest(request,0)))
	{
		FreeAslRequest(request);
		return 1;
	}

	// Get mode ID
	modeid=((struct ScreenModeRequester *)request)->sm_DisplayID;

	// Free requester
	FreeAslRequest(request);

	// Close window
	read_close_window(data);

	// Re-open window
	if (read_open_window(data))
	{
		// Redraw text
		read_set_mode(data,data->mode);
		read_init(data);
		return 1;
	}

	// Failed
	return 0;
}


// Pick a font to use
void read_pick_font(read_data *data)
{
	APTR request;

	// Allocate an ASL request
	if (!(request=my_AllocAslRequestTags(
		ASL_FontRequest,
		ASLFO_Window,data->window,
		ASLFO_SleepWindow,TRUE,
		ASLFO_InitialName,(fontname[0])?fontname+1:"",
		ASLFO_InitialSize,(fontname[0])?fontsize:8,
		ASLFO_FixedWidthOnly,TRUE,
		TAG_END))) return;

	// Show requester
	if (!(AslRequest(request,0)))
	{
		FreeAslRequest(request);
		return;
	}

	// Free existing font
	SetBusyPointer(data->window);
	if (data->font)
	{
		SetFont(data->window->RPort,((struct GfxBase *)GfxBase)->DefaultFont);
		CloseFont(data->font);
	}

	// Get new font
	if (data->font=OpenDiskFont(&((struct FontRequester *)request)->fo_Attr))
		SetFont(data->window->RPort,data->font);

	// Store font information
	fontname[0]='0';
	strcpy(fontname+1,((struct FontRequester *)request)->fo_Attr.ta_Name);
	fontsize=((struct FontRequester *)request)->fo_Attr.ta_YSize;

	// Free requester
	FreeAslRequest(request);

	// Redraw text
	read_init(data);
	ClearPointer(data->window);
}


// Allocate a line node
read_line __asm *read_alloc_node(register __a0 read_data *data)
{
	register read_line *line;

	// Current line block?
	if (data->current_block)
	{
		// Get current line
		line=&data->current_block->lines[data->current_line++];

		// Time to get a new block?
		if (data->current_line>=LINES_PER_BLOCK)
			data->current_block=0;
	}

	// No block
	else
	{
		// Try and allocate a block
		if (data->current_block=AllocMemH(data->memory,sizeof(read_block)))
		{
			// Send back first line
			line=&data->current_block->lines[0];
			data->current_line=1;
		}

		// Block alloc failed; allocate a single line entry
		else line=AllocMemH(data->memory,sizeof(read_line));
	}

	// Return line pointer
	return line;
}


// varargs AllocAslRequest()
APTR __stdargs my_AllocAslRequestTags(ULONG type,Tag tag,...)
{
	return AllocAslRequest(type,(struct TagItem *)&tag);
}


// varargs LayoutMenus()
BOOL __stdargs my_LayoutMenus(struct Menu *menu,APTR vi,Tag tag,...)
{
	return LayoutMenusA(menu,vi,(struct TagItem *)&tag);
}


// Print
void read_print(read_data *data)
{
	struct Library *ModuleBase;

	// Set busy pointer
	SetBusyPointer(data->window);

	// Get print module
	if (ModuleBase=OpenLibrary("dopus5:modules/print.module",0))
	{
		struct List list;
		struct Node node;

		// Build list for this file
		NewList(&list);
		node.ln_Name=data->file;
		AddTail(&list,&node);

		// Print file
		Module_Entry(&list,data->window->WScreen,data->ipc,data->main_ipc,0,0);

		// Close library
		CloseLibrary(ModuleBase);
	}

	// Clear busy pointer
	ClearPointer(data->window);
}


// Copy highlighted area to clipboard
void read_clipboard_copy(read_data *data)
{
	read_line *line;
	short cp,pos,c_x;
	long l;
	APTR iff;

	// Got a selection?
	if (data->sel_top_pos==-1) return;

	// Open clipboard for IFF
	if (!(iff=IFFOpen(0,IFF_CLIP_WRITE,ID_FTXT)))
		return;

	// Set busy pointer
	SetBusyPointer(data->window);

	// Push text chunk
	if (IFFPushChunk(iff,ID_CHRS))
	{
		// Get top selection line
		for (l=0,line=(read_line *)data->text.mlh_Head;
			l<data->sel_top_line && line->node.mln_Succ;
			l++,line=(read_line *)line->node.mln_Succ);

		// Go through lines
		for (;l<=data->sel_bottom_line && line->node.mln_Succ;
			l++,line=(read_line *)line->node.mln_Succ)
		{
			char *ptr;
	
			// Build text line
			for (cp=0,c_x=0,pos=0;cp<=line->length;cp++)
			{
				// Escape sequence?
				if (line->text[cp]=='\x1b')
				{
					// Skip to end of sequence
					while (cp<=line->length &&
						(line->text[cp]<'A' ||
						(line->text[cp]>'Z' && line->text[cp]<'a') ||
						line->text[cp]>'z')) ++cp;
				}

				// Tab character?
				else if (line->text[cp]=='\t')
				{
					short x;

					// Get next tab stop
					x=c_x;
					c_x=((c_x+data->tab_size)/data->tab_size)*data->tab_size;

					// Get amount moved
					x-=c_x;

					// Add spaces
					while ((x--)>0) data->line_buffer[pos++]=' ';
				}

				// Normal character
				else if (line->text[cp]!='\r')
				{
					// Add to buffer
					data->line_buffer[pos++]=line->text[cp];
					++c_x;
				}
			}

			// Get string pointer
			ptr=data->line_buffer;

			// Last line?
			if (l==data->sel_bottom_line && pos>data->sel_bottom_pos)
				pos-=pos-data->sel_bottom_pos-1;

			// First line?
			if (l==data->sel_top_line)
			{
				pos-=data->sel_top_pos;
				ptr+=data->sel_top_pos;
			}

			// Write data
			if (pos>0)
			{
				if (!(IFFWriteChunkBytes(iff,ptr,pos)))
					break;
			}
		}

		// Pop the chunk
		IFFPopChunk(iff);
	}

	// Close clipboard file
	IFFClose(iff);

	// Clear busy pointer
	ClearPointer(data->window);
}
