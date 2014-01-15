#include "config_lib.h"

/*#ifdef __amigaos3__
extern struct ExecBase *SysBase;
#endif*/

// Generic IPC startup code

IPCData *SAVEDS Local_IPC_ProcStartup(
	ULONG *data,
	ULONG (*code)(IPCData *,APTR))
{
	struct Library *DOpusBase;

	// Find dopus library
	DOpusBase=(struct Library *)FindName(&((struct ExecBase *)SysBase)->LibList,"dopus5.library");
	
	// Call startup
	return IPC_ProcStartup(data,code);
}
