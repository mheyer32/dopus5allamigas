#ifndef CONFIGOPUS_INTERFACE_DEF_H
#define CONFIGOPUS_INTERFACE_DEF_H

/*
** This file was machine generated by idltool 53.5.
** Do not edit
*/

#ifndef EXEC_TYPES_H
	#include <exec/types.h>
#endif
#ifndef EXEC_EXEC_H
	#include <exec/exec.h>
#endif
#ifndef EXEC_INTERFACES_H
	#include <exec/interfaces.h>
#endif

#ifdef __cplusplus
	#ifdef __USE_AMIGAOS_NAMESPACE__
namespace AmigaOS {
	#endif
extern "C" {
#endif

struct ConfigOpusIFace
{
	struct InterfaceData Data;

	uint32 APICALL (*Obtain)(struct ConfigOpusIFace *Self);
	uint32 APICALL (*Release)(struct ConfigOpusIFace *Self);
	void APICALL (*Expunge)(struct ConfigOpusIFace *Self);
	struct Interface *APICALL (*Clone)(struct ConfigOpusIFace *Self);
	int APICALL (*Config_Settings)(struct ConfigOpusIFace *Self,
								   Cfg_Environment *env,
								   struct Screen *screen,
								   IPCData *ipc,
								   IPCData *mainipc,
								   char *name);
	unsigned long APICALL (*Config_Environment)(struct ConfigOpusIFace *Self,
												Cfg_Environment *env,
												struct Screen *screen,
												UWORD *table,
												IPCData *ipc,
												IPCData *mainipc,
												UWORD alloc,
												ULONG *change,
												char *name,
												Att_List *scripts);
	int APICALL (*Config_removed)(struct ConfigOpusIFace *Self);
	int APICALL (*Config_Buttons)(struct ConfigOpusIFace *Self,
								  ButtonsStartup *bank,
								  IPCData *ipc,
								  IPCData *owner,
								  struct Screen *screen,
								  ULONG cmdlist);
	BOOL APICALL (*ConvertConfig)(struct ConfigOpusIFace *Self, char *name, struct Screen *screen, IPCData *owner);
	short APICALL (*Config_Filetypes)(struct ConfigOpusIFace *Self,
									  struct Screen *screen,
									  IPCData *ipc,
									  IPCData *owner,
									  ULONG cmdlist,
									  char *name);
	ULONG APICALL (*Config_ListerButtons)(struct ConfigOpusIFace *Self,
										  char *name,
										  IPCData *ipc,
										  IPCData *owner,
										  struct Screen *screen,
										  Cfg_ButtonBank *bank,
										  ULONG cmdlist,
										  LONG init);
	ULONG APICALL (*Config_Menu)(struct ConfigOpusIFace *Self,
								 char *name,
								 IPCData *ipc,
								 IPCData *owner,
								 struct Screen *screen,
								 Cfg_ButtonBank *bank,
								 char *title,
								 ULONG cmdlist,
								 char *def,
								 short hotkeys,
								 Att_List *scripts);
	ULONG APICALL (*Config_Menus)(struct ConfigOpusIFace *Self,
								  IPCData *ipc,
								  IPCData *owner,
								  struct Screen *screen,
								  Cfg_ButtonBank *menu,
								  ULONG cmdlist,
								  ULONG type,
								  char *name);
	Cfg_Filetype *APICALL (*EditFiletype)(struct ConfigOpusIFace *Self,
										  Cfg_Filetype *type,
										  struct Window *window,
										  IPCData *ipc,
										  IPCData *dopus,
										  ULONG flags);
	Cfg_Function *APICALL (*Config_EditFunction)(struct ConfigOpusIFace *Self,
												 IPCData *ipc,
												 IPCData *opus,
												 struct Window *window,
												 Cfg_Function *func,
												 APTR memory,
												 ULONG cmdlist);
	long APICALL (*ShowPaletteBox)(struct ConfigOpusIFace *Self,
								   struct Window *window,
								   DOpusScreenData *data,
								   short *fgpen,
								   short *bgpen,
								   struct TextAttr *font,
								   ColourSpec32 *spec,
								   short *pen);
	BOOL APICALL (*FunctionExportASCII)(struct ConfigOpusIFace *Self,
										char *name,
										Cfg_Button *button,
										Cfg_Function *func,
										ULONG type);
};

#ifdef __cplusplus
}
	#ifdef __USE_AMIGAOS_NAMESPACE__
}
	#endif
#endif

#endif /* CONFIGOPUS_INTERFACE_DEF_H */
