#include "font.h"

void main(int argc,char **argv)
{
	font_data *data;

	// Need dopus library
	if (!(DOpusBase=OpenLibrary("dopus5:libs/dopus5.library",55)))
		exit(10);

	// Allocate data
	if (!(data=AllocVec(sizeof(font_data),MEMF_CLEAR)))
	{
		font_free(0);
		exit(5);
	}

	// Parse arguments
	data->args=
		ReadArgs(
			"FONT,SIZE/N,B=BOLD/S,I=ITALIC/S,U=ULINE/S,PUBSCREEN/K",
			(long *)data->arg_array,
			0);

	// Default to topaz 8
	strcpy(data->font_name,"topaz.font");
	data->font_size=8;

	// Got font name?
	if (data->arg_array[ARG_FONT])
		font_get_name(data,(char *)data->arg_array[ARG_FONT]);

	// Got a font size?
	if (data->arg_array[ARG_SIZE] && *((long *)data->arg_array[ARG_SIZE]))
	{
		data->font_size=*((long *)data->arg_array[ARG_SIZE]);
		data->first=1;
	}

	// Initialise locale
	init_locale_data(&data->locale);

	// Got locale library?
	if (LocaleBase)
	{
		BPTR lock;

		// Change PROGDIR: to dopus5:
		if (lock=Lock("dopus5:",ACCESS_READ))
			UnLock(SetProgramDir(lock));

		// Initialise
		data->locale.li_LocaleBase=LocaleBase;
		data->locale.li_Catalog=OpenCatalogA(0,"viewfont.catalog",0);
		data->locale.li_Locale=OpenLocale(0);
	}

	// Create message port
	data->appport=CreateMsgPort();

	// Open window
	if (!(font_open(data)))
	{
		font_free(data);
		exit(5);
	}

	// Initial gadget settings
	if (data->arg_array[ARG_BOLD]) SetGadgetValue(data->list,GAD_FONT_BOLD,1);
	if (data->arg_array[ARG_ITALIC]) SetGadgetValue(data->list,GAD_FONT_ITALIC,1);
	if (data->arg_array[ARG_ULINE]) SetGadgetValue(data->list,GAD_FONT_ULINE,1);

	// Show font
	font_show_font(data,0);

	// Initialise refresh hook
	data->refresh_hook.h_Entry=(ULONG (*)())font_refresh;
	data->refresh_hook.h_Data=data;

	// Event loop
	FOREVER
	{
		struct IntuiMessage *msg;
		BOOL quit_flag=0;

		// AppWindow?
		if (data->appwindow)
		{
			struct AppMessage *amsg;

			// Get messages
			while (amsg=(struct AppMessage *)GetMsg(data->appport))
			{
				// Got file?
				if (amsg->am_NumArgs>0)
				{
					char buf[256];

					// Get name
					DevNameFromLock(amsg->am_ArgList[0].wa_Lock,buf,256);
					if (amsg->am_ArgList[0].wa_Name && *amsg->am_ArgList[0].wa_Name)
						AddPart(buf,amsg->am_ArgList[0].wa_Name,256);

					// Get font name
					font_get_name(data,buf);

					// Get new font
					font_get_font(data);
					font_show_font(data,0);
				}

				// Reply to message
				ReplyMsg((struct Message *)amsg);
			}
		}

		// Requester?
		if (data->about)
		{
			// Handle requester
			if (SysReqHandler(data->about,0,0)>=0)
			{
				// Close requester
				FreeSysRequest(data->about);
				data->about=0;
			}
		}

		// Intuition messages
		if (data->window)
		{
			while (msg=GetWindowMsg(data->window->UserPort))
			{
				struct IntuiMessage msg_copy;
				USHORT id=0;

				// Copy message and reply
				msg_copy=*msg;
				ReplyWindowMsg(msg);

				// Get gadget ID
				if (msg_copy.Class==IDCMP_GADGETUP)
					id=((struct Gadget *)msg_copy.IAddress)->GadgetID;

				// Look at message
				switch (msg_copy.Class)
				{
					// Close window
					case IDCMP_CLOSEWINDOW:
						quit_flag=1;
						break;


					// New size
					case IDCMP_NEWSIZE:

						// Redraw font
						font_show_font(data,0);

						// Set flag to say we resized
						data->resized=1;
						break;


					// Menu
					case IDCMP_MENUPICK:
						{
							struct MenuItem *item;

							// Get item
							if (!(item=ItemAddress(data->window->MenuStrip,msg_copy.Code)))
								break;

							// Get ID
							id=(USHORT)GTMENUITEM_USERDATA(item);

							// Fall through
						}

					// Gadget
					case IDCMP_GADGETUP:
						switch (id)
						{
							// Show requester
							case GAD_FONT_FONT_POPUP:
							case MENU_OPEN_FONT:

								// Ask for name
								font_ask_name(data);
								break;


							// Font name typed
							case GAD_FONT_FONT:

								// Get name
								font_get_name(data,(char *)GetGadgetValue(data->list,GAD_FONT_FONT));

								// Get new font
								font_get_font(data);
								font_show_font(data,0);
								break;


							// Font size up/down
							case GAD_FONT_UP:
							case GAD_FONT_DOWN:
								{
									short size;

									// Get next size
									size=font_get_size(data,(id==GAD_FONT_UP)?1:-1);

									// No change?
									if (size==data->font_size) break;

									// Use this size
									data->font_size=size;
									SetGadgetValue(data->list,GAD_FONT_SIZE,size);
								}

							// Font size given
							case GAD_FONT_CYCLE:

								// Check id
								if (id==GAD_FONT_CYCLE)
								{
									short size;

									// Get size
									if (!(size=atoi(data->size_labels[msg_copy.Code])))
										break;

									// Refresh gadget
									data->font_size=size;
									SetGadgetValue(data->list,GAD_FONT_SIZE,data->font_size);
								}

							// Font size
							case GAD_FONT_SIZE:

								// Entered size
								if (id==GAD_FONT_SIZE)
								{
									// Bounds check gadget
									data->font_size=
										BoundsCheckGadget(
											data->list,
											GAD_FONT_SIZE,
											4,
											255);
								}

								// Get new font
								font_get_font(data);
								font_show_font(data,0);
								break;

							// Styles changed
							case GAD_FONT_BOLD:
							case GAD_FONT_ITALIC:
							case GAD_FONT_ULINE:

								// Redraw font
								font_show_font(data,0);
								break;


							// Save settings
							case MENU_SAVE_SETTINGS:
								font_save_settings(data);
								break;


							// Quit
							case MENU_QUIT:
								quit_flag=1;
								break;


							// About
							case MENU_ABOUT:
								font_show_about(data);
								break;
						}
						break;


					// Rawkey
					case IDCMP_RAWKEY:

						// Help?
						if (msg_copy.Code==0x5f)
							font_show_about(data);

					// Key
					case IDCMP_VANILLAKEY:

						// Escape does quit
						if (msg_copy.Code==0x1b) quit_flag=1;
						break;


					// Refresh
					case IDCMP_REFRESHWINDOW:

						// Have we just resized?
						if (data->resized)
						{
							// Don't need to refresh
							BeginRefresh(data->window);
							EndRefresh(data->window,TRUE);
							data->resized=0;
							break;
						}

						// Refresh font display
						font_show_font(data,1);
						break;
				}

				// Check window is still valid
				if (!data->window) break;
			}
		}

		if (quit_flag) break;

		// Wait for signal (ctrl-c breaks)
		if ((Wait(SIGBREAKF_CTRL_C|
					((data->window)?(1<<data->window->UserPort->mp_SigBit):0)|
					((data->about)?(1<<data->about->UserPort->mp_SigBit):0)|
					((data->appwindow)?(1<<data->appport->mp_SigBit):0)))&SIGBREAKF_CTRL_C) break;
	}

	// Free stuff
	font_free(data);
	exit(0);
}


// Open font window
BOOL font_open(font_data *data)
{
	struct Screen *screen=0;

	// Screen supplied?
	if (data->arg_array[ARG_SCREEN])
		screen=LockPubScreen((char *)data->arg_array[ARG_SCREEN]);	

	// Fill out new window
	data->new_win.parent=screen;
	data->new_win.dims=&data->win_dims;
	data->new_win.title=GetString(&data->locale,MSG_FONT_TITLE);
	data->new_win.locale=&data->locale;
	data->new_win.flags=WINDOW_SCREEN_PARENT|WINDOW_VISITOR|WINDOW_AUTO_KEYS|WINDOW_SIZE_BOTTOM|WINDOW_SIMPLE;

	// Default dimensions
	data->win_dims=font_window;

	// Read settings
	font_read_settings(data);

	// Open window
	if (data->window=OpenConfigWindow(&data->new_win))
		data->list=AddObjectList(data->window,font_objects);

	// Unlock screen
	UnlockPubScreen(0,screen);

	// Failed to open?
	if (!data->list) return 0;

	// Fix sizing limits
	WindowLimits(data->window,
		(font_window.char_dim.Width*data->window->RPort->TxWidth)+font_window.fine_dim.Width,
		(font_window.char_dim.Height*data->window->RPort->TxHeight)+font_window.fine_dim.Height,
		~0,~0);

	// Add menus
	AddWindowMenus(data->window,font_menus);

	// Add AppWindow
	if (data->appport)
		data->appwindow=AddAppWindowA(0,0,data->window,data->appport,0);

	// Get the font
	font_get_font(data);
	return 1;
}


// Close font display
void font_close(font_data *data)
{
	// Window open?
	if (data->window)
	{
		// Remove AppWindow
		RemoveAppWindow(data->appwindow);
		data->appwindow=0;

		// Close requester
		FreeSysRequest(data->about);
		data->about=0;

		// Close window
		CloseConfigWindow(data->window);
		data->window=0;
	}
}


// Free font data
void font_free(font_data *data)
{
	if (data)
	{
		// Close stuff
		font_close(data);

		// Free font
		if (data->font) CloseFont(data->font);

		// Free port
		DeleteMsgPort(data->appport);

		// Close locale stuff
		if (data->locale.li_Locale)
		{
			CloseLocale(data->locale.li_Locale);
			CloseCatalog(data->locale.li_Catalog);
		}

		// Free args
		FreeArgs(data->args);

		// Free labels
		FreeVec(data->size_labels);

		// Free data
		FreeVec(data);
	}

	// Close library
	CloseLibrary(DOpusBase);
}


// Get font
void font_get_font(font_data *data)
{
	// Make window busy
	SetWindowBusy(data->window);

	// Existing font?
	if (data->font)
	{
		// Free font
		CloseFont(data->font);
		data->font=0;
	}

	// Has the font name changed?
	if (stricmp(data->font_name,data->last_font_name))
	{
		struct FontContentsHeader *fch;
		BPTR lock;

		// Empty labels
		font_build_labels(data,0);

		// Is the name a full path?
		if (strchr(data->font_name,'/') || strchr(data->font_name,':'))
		{
			// Lock font
			if (lock=Lock(data->font_name,ACCESS_READ))
			{
				BPTR parent;

				// Get lock on parent
				parent=ParentDir(lock);

				// Unlock lock on file
				UnLock(lock);
				lock=parent;
			}
		}

		// Lock fonts: directory
		else lock=Lock("fonts:",ACCESS_READ);

		// Got lock?
		if (lock)
		{
			// Get font contents
			if (fch=NewFontContents(lock,FilePart(data->font_name)))
			{
				// Build labels
				font_build_labels(data,fch);

				// Free contents
				DisposeFontContents(fch);
			}

			// Unlock drawer
			UnLock(lock);
		}
	}

	// Fill out TextAttr
	data->attr.ta_Name=data->font_name;
	data->attr.ta_YSize=data->font_size;
	data->attr.ta_Style=0;
	data->attr.ta_Flags=0;

	// Open font
	data->font=OpenDiskFont(&data->attr);

	// Show font name and size
	SetGadgetValue(data->list,GAD_FONT_FONT,(ULONG)FilePart(data->font_name));
	SetGadgetValue(data->list,GAD_FONT_SIZE,data->font_size);

	// Got font?
	if (data->font)
	{
		short ch,pos,hi;

		// First character
		ch=data->font->tf_LoChar;
		if (ch<33) ch=33;

		// Hi character
		hi=data->font->tf_HiChar;
		if (hi>126 && ch<127) hi=127;

		// Build display text
		for (pos=0;ch<hi;ch++,pos++)
			data->font_text[pos]=ch;
		data->font_text[pos]=0;

		// Got labels?
		if (data->size_labels)
		{
			// Find label corresponding to this size
			for (pos=0;data->size_labels[pos];pos++)
			{
				if (atoi(data->size_labels[pos])==data->font_size)
				{
					// Set cycle gadget
					SetGadgetValue(data->list,GAD_FONT_CYCLE,pos);
					break;
				}
			}
		}
	}

	// Empty labels
	else font_build_labels(data,0);

	// Copy name
	strcpy(data->last_font_name,data->font_name);

	// Clear 'first' flag
	data->first=0;

	// Clear window busy
	ClearWindowBusy(data->window);
}


// Show font example
void font_show_font(font_data *data,BOOL refresh)
{
	struct Rectangle rect;
	struct Region *region;
	struct RastPort rp;

	// Get display rectangle
	GetObjectRect(data->list,GAD_FONT_DISPLAY,&rect);

	// Move rectangle in
	rect.MinX+=3;
	rect.MinY+=3;
	rect.MaxX-=3;
	rect.MaxY-=3;

	// Copy rastport
	rp=*data->window->RPort;

	// Refresh?
	if (refresh)
	{
		LockLayerInfo(&data->window->WScreen->LayerInfo);
		BeginRefresh(data->window);
	}

	// Clear background
	SetAPen(&rp,DRAWINFO(data->window)->dri_Pens[SHINEPEN]);
	RectFill(&rp,rect.MinX-1,rect.MinY-1,rect.MaxX+1,rect.MaxY+1);

	// Refreshing?
	if (refresh) EndRefresh(data->window,FALSE);

	// Create region
	if (region=NewRegion())
	{
		// Set rectangle
		OrRectRegion(region,&rect);

		// Install region
		InstallClipRegion(data->window->WLayer,region);
	}

	// Refreshing?
	if (refresh) BeginRefresh(data->window);

	// Got a font?
	if (data->font)
	{
		ULONG flags;
		short y;
		struct TextExtent extent;
		char *ptr,*end;

		// Set pen and font
		SetAPen(&rp,DRAWINFO(data->window)->dri_Pens[TEXTPEN]);
		SetDrMd(&rp,JAM1);
		SetFont(&rp,data->font);

		// Get style flags
		flags=0;
		if (GetGadgetValue(data->list,GAD_FONT_BOLD)) flags|=FSF_BOLD;
		if (GetGadgetValue(data->list,GAD_FONT_ITALIC)) flags|=FSF_ITALIC;
		if (GetGadgetValue(data->list,GAD_FONT_ULINE)) flags|=FSF_UNDERLINED;

		// Set styles
		SetSoftStyle(&rp,flags,FSF_BOLD|FSF_ITALIC|FSF_UNDERLINED);

		// Valid font to draw?
		if (data->font_text[0])
		{
			// Get end of the string
			end=data->font_text+strlen(data->font_text);

			// Initial coordinates
			y=rect.MinY;

			// Initialise position
			if (!(ptr=strchr(data->font_text,'A')))
				ptr=data->font_text;
			Move(&rp,rect.MinX,y+rp.TxBaseline);

			// Draw until we reach the bottom
			while (y<rect.MaxY)
			{
				// New line
				if (rp.cp_x>rect.MaxX)
				{
					// Bump position
					y+=rp.TxHeight+1;
					Move(&rp,rect.MinX,y+rp.TxBaseline);
				}

				// Otherwise
				else
				{
					short len,maxlen;

					// Get text that will fit
					len=
						TextFit(
							&rp,
							ptr,
							(maxlen=strlen(ptr)),
							&extent,
							0,1,
							rect.MaxX-rp.cp_x+1,
							rp.TxHeight);

					// Check against length, add extra character if ok
					if (len<maxlen) ++len;

					// Draw text
					Text(&rp,ptr,len);

					// Bump text position
					ptr+=len;

					// End of the string?
					if (ptr>=end) ptr=data->font_text;
				}
			}
		}
	}

	// Finished refreshing?
	if (refresh) EndRefresh(data->window,TRUE);

	// Remove region
	if (region)
	{
		InstallClipRegion(data->window->WLayer,0);
		DisposeRegion(region);
	}

	// Unlock layers if we refreshed
	if (refresh) UnlockLayerInfo(&data->window->WScreen->LayerInfo);
}


// Get font name from string
void font_get_name(font_data *data,char *name)
{
	short len;

	// .font suffix?
	if ((len=strlen(name))>5 &&
		stricmp(name+len-5,".font")==0)
	{
		// Use name as given
		strcpy(data->font_name,name);
	}

	// Numeric name?
	else
	if (len=atoi(FilePart(name)))
	{
		// Strip filename
		*(PathPart(name))=0;

		// Store name
		strcpy(data->font_name,name);
		strcat(data->font_name,".font");

		// Store size
		data->font_size=len;
		data->first=1;
	}

	// Name specified without .font
	else
	{
		// Store name
		strcpy(data->font_name,name);
		strcat(data->font_name,".font");
	}
}


// Ask for font name
void font_ask_name(font_data *data)
{
	char file[40],path[256],*fileptr;

	// Copy path
	strcpy(path,data->font_name);

	// Split filename
	if (fileptr=FilePart(path))
	{
		strcpy(file,fileptr);
		*fileptr=0;
	}
	else file[0]=0;

	// Empty path?
	if (!path[0]) strcpy(path,"fonts:");

	// Busy window
	SetWindowBusy(data->window);

	// Display requester
	if (AslRequestTags(((WindowData *)data->window->UserData)->request,
		ASLFR_Window,data->window,
		ASLFR_TitleText,GetString(&data->locale,MSG_FONT_SELECT),
		ASLFR_InitialFile,file,
		ASLFR_InitialDrawer,path,
		ASLFR_IntuiMsgFunc,&data->refresh_hook,
		TAG_END))
	{
		// Get pathname
		strcpy(path,((WindowData *)data->window->UserData)->request->fr_Drawer);
		AddPart(path,((WindowData *)data->window->UserData)->request->fr_File,256);

		// Get font name
		font_get_name(data,path);

		// Get new font
		font_get_font(data);
		font_show_font(data,0);
	}

	// Unbusy window
	else ClearWindowBusy(data->window);
}


// varargs AslRequestTags
BOOL __stdargs AslRequestTags(
	APTR req,
	Tag tag1,...)
{
	return AslRequest(req,(struct TagItem *)&tag1);
}


// Refresh hook
ULONG __asm __saveds font_refresh(
	register __a0 struct Hook *hook,
	register __a1 struct IntuiMessage *msg)
{
	font_data *data=(font_data *)hook->h_Data;

	// Refresh message?
	if (msg->Class==IDCMP_REFRESHWINDOW)
	{
		// Do the refresh
		font_show_font(data,1);
	}

	// New size?
	else
	if (msg->Class==IDCMP_NEWSIZE)
	{
		// Handle resize
		LayoutResize(data->window);

		// Redraw font
		font_show_font(data,0);

		// Set flag to say we resized
		data->resized=1;
	}

	return (ULONG)msg;
}


// Get next font size
short font_get_size(font_data *data,short dir)
{
	short size;

	// Current size
	size=data->font_size;

	// Increment it
	size+=dir;

	// Bounds check
	if (size<2) size=2;
	else
	if (size>254) size=254;

	return size;
}


// Build size labels
void font_build_labels(font_data *data,struct FontContentsHeader *fch)
{
	char **labels,*ptr;
	short num=0,a,smallest=0;
	struct FontContents *fc=0;
	BOOL topaz=0;

	// Get number
	if (fch) num=fch->fch_NumEntries;
	if (num<1)
	{
		num=1;
		fch=0;
	}

	// Kludge for topaz
	if (fch)
	{
		// Get first contents pointer
		fc=(struct FontContents *)(fch+1);

		// Topaz?
		if (strnicmp(fc->fc_FileName,"topaz/",6)==0)
		{
			// Add 8 and 9
			num+=2;
			topaz=1;
		}
	}

	// Allocate array and buffer
	if (!(ptr=AllocVec((sizeof(char *)+8)*(num+1),MEMF_CLEAR)))
		return;

	// Get label array, bump pointer
	labels=(char **)ptr;
	ptr+=sizeof(char *)*(num+1);

	// No font contents?
	if (!fc)
	{
		// Null label
		labels[0]=ptr;
		labels[1]=0;
	}

	// Get label pointers, build labels
	else
	for (a=0;a<num;a++,ptr+=8)
	{
		// Get pointer
		labels[a]=ptr;

		// Topaz kludge?
		if (topaz && a<2)
		{
			short val=8+a;

			// Add 8 or 9
			labels[a][0]='0'+val;
			labels[a][1]=0;

			// Is this the smallest?
			if (!smallest || val<smallest)
				smallest=val;
		}

		// Normal font
		else
		{
			// Add size
			lsprintf(labels[a],"%ld",fc->fc_YSize);

			// Is this the smallest?
			if (!smallest || fc->fc_YSize<smallest)
				smallest=fc->fc_YSize;

			// Bump contents pointer
			fc++;
		}
	}

	// Use smallest as first size to show
	if (!data->first && smallest) data->font_size=smallest;

	// Use new labels
	SetGadgetChoices(data->list,GAD_FONT_CYCLE,labels);

	// Disable if no labels
	DisableObject(data->list,GAD_FONT_CYCLE,(BOOL)!labels[1]);

	// Free old labels, store pointer
	FreeVec(data->size_labels);
	data->size_labels=labels;
}


// Show about requester
void font_show_about(font_data *data)
{
	struct EasyStruct easy;

	// Window open?
	if (data->about)
	{
		WindowToFront(data->about);
		ActivateWindow(data->about);
		return;
	}

	// Fill out easy struct
	easy.es_StructSize=sizeof(easy);
	easy.es_Flags=0;
	easy.es_Title=0;
	easy.es_TextFormat="Directory Opus 5 Font Viewer\nv55.0 (01.08.96)\n\n© 1996 Jonathan Potter";
	easy.es_GadgetFormat=GetString(&data->locale,MSG_OK);

	// Open requester
	data->about=BuildEasyRequest(data->window,&easy,0,0);
}


// Save settings
void font_save_settings(font_data *data)
{
	char buf[80];

	// Set busy pointer
	SetWindowBusy(data->window);

	// Build settings string
	lsprintf(buf,"%ld/%ld/%ld/%ld\n",
		data->window->LeftEdge,
		data->window->TopEdge,
		data->window->GZZWidth,
		data->window->Height-data->window->BorderTop-2);

	// Set variable
	if (SetVar("dopus/Font Viewer",buf,-1,GVF_GLOBAL_ONLY))
	{
		// Copy to ENVARC:
		SystemTagList("copy \"env:dopus/Font Viewer\" envarc:dopus",0);
	}

	// Clear busy pointer
	ClearWindowBusy(data->window);
}


// Read settings
void font_read_settings(font_data *data)
{
	char buf[80],*ptr;
	struct IBox dims;

	// Get environment variable
	if (GetVar("dopus/Font Viewer",buf,sizeof(buf),GVF_GLOBAL_ONLY)<=0)
		return;

	// Get pointer to buffer
	ptr=buf;

	// Parse settings
	read_parse_set(&ptr,(USHORT *)&dims.Left);
	read_parse_set(&ptr,(USHORT *)&dims.Top);
	read_parse_set(&ptr,(USHORT *)&dims.Width);
	read_parse_set(&ptr,(USHORT *)&dims.Height);

	// Got valid size?
	if (dims.Height>0)
	{
		// Clear character coordinates
		data->win_dims.char_dim.Top=0;
		data->win_dims.char_dim.Left=0;
		data->win_dims.char_dim.Width=0;
		data->win_dims.char_dim.Height=0;

		// Set absolute coordinates
		data->win_dims.fine_dim=dims;
	}
}


// Parse number out of string, leave pointer at one character after end of number
void read_parse_set(char **ptr,unsigned short *val)
{
	// Digit?
	if (isdigit(*(*ptr)))
	{
		*val=atoi(*ptr);
		while (*(*ptr) && isdigit(*(*ptr))) ++*ptr;
		++*ptr;
	}
}
