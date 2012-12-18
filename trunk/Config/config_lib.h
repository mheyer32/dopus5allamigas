#include "dopuslib:dopusbase.h"
#include "dopuslib:dopuspragmas.h"
#include "dopusprog:dopus_config.h"
#include "configopus.h"

#define CATCOMP_NUMBERS
#include "string_data.h"

extern struct Library		*DOpusBase;
extern struct Library		*LayersBase;
extern struct Library		*DiskfontBase;
extern struct Library		*GadToolsBase;
extern struct Library		*WorkbenchBase;
extern struct Library		*IconBase;
extern struct Library		*AslBase;
extern struct Library		*CxBase;
extern struct Library		*UtilityBase;
extern struct Library		*LocaleBase;
extern struct DOpusLocale	*locale;

typedef struct
{
	struct Library		*DOSBase;
	struct Library		*DOpusBase;
	struct Library		*IntuitionBase;
	struct Library		*GfxBase;
	struct Library		*LayersBase;
	struct Library		*DiskfontBase;
	struct Library		*GadToolsBase;
	struct Library		*WorkbenchBase;
	struct Library		*IconBase;
	struct Library		*AslBase;
	struct Library		*CxBase;
	struct Library		*UtilityBase;
	struct Library		*LocaleBase;
	struct DOpusLocale	locale;
} libdata;

// Config sub-option handles
typedef struct _SubOptionHandle {
	int num;		// Option number
	ULONG name;		// Option name ID
	ObjectDef *objects;	// Object list
} SubOptionHandle;

void init_locale_data(struct DOpusLocale *);
void KPrintF __ARGS((char *,...));
void lsprintf __ARGS((char *,...));

Att_List *build_sub_options(SubOptionHandle *);

IPCData *__saveds Local_IPC_ProcStartup(
	ULONG *data,
	ULONG (*code)(IPCData *,APTR));

#define VALID_QUALIFIERS (IEQUALIFIER_LCOMMAND|IEQUALIFIER_RCOMMAND|\
                         IEQUALIFIER_CONTROL|IEQUALIFIER_LSHIFT|\
                         IEQUALIFIER_RSHIFT|IEQUALIFIER_LALT|IEQUALIFIER_RALT)

typedef struct
{
	struct Window		*window;

	DragInfo		*drag;
	Att_Node		*drag_node;
	short			drag_x;
	short			drag_y;

	long			tick_count;
	long			last_tick;
	TimerHandle		*timer;

	unsigned long		old_flags;
	unsigned long		old_idcmp;

	short			lock_count;
	short			flags;
} CfgDragInfo;

BOOL config_drag_check(CfgDragInfo *drag);
void config_drag_move(CfgDragInfo *drag);
void config_drag_start(CfgDragInfo *,Att_List *,short,struct TagItem *,BOOL);
struct Window *config_drag_end(CfgDragInfo *,short);
BOOL config_drag_send_button(CfgDragInfo *,IPCData *,Cfg_Button *,Cfg_ButtonFunction *);
Cfg_Button *config_drag_get_button(Cfg_Button *button,Cfg_ButtonFunction *func);
void config_drag_start_window(CfgDragInfo *,struct Window *,struct Rectangle *,short,short);

char *function_label(Cfg_ButtonFunction *);
BOOL config_filereq(struct Window *window,ULONG title,char *path,char *defpath,short flags);
BOOL config_valid_path(char *path);

Cfg_Instruction *instruction_from_wbarg(struct WBArg *,APTR);
void parse_number(char **,unsigned short *);
void store_window_pos(struct Window *window,struct IBox *pos);

long __asm L_ShowPaletteBox(
	register __a0 struct Window *,
	register __a1 DOpusScreenData *,
	register __a2 short *,
	register __a3 short *,
	register __a4 struct TextAttr *,
	register __a5 ColourSpec32 *,
	register __d0 short *);

BOOL __asm L_FunctionExportASCII(
	register __a0 char *,
	register __a1 Cfg_Button *,
	register __a2 Cfg_Function *,
	register __d0 ULONG);

short error_saving(short,struct Window *);

#include "enums.h"
#include "config_data.h"
#include "function_export.h"
#include "function_editor.h"
#include "select_colours.h"
#include "button_editor.h"
