#include "config_lib.h"

// Generic IPC startup code
#warning We already have a global DOpusbase libbase, remove this!
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
