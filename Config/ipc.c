#include "config_lib.h"

// Generic IPC startup code
IPCData *__saveds Local_IPC_ProcStartup(
	ULONG *data,
	ULONG (*code)(IPCData *,APTR))
{
	struct Library *DOpusBase;
	struct ExecBase *Exec=(struct ExecBase *)*((ULONG *)4);

	// Find dopus library
	DOpusBase=(struct Library *)FindName(&Exec->LibList,"dopus5.library");

	// Call startup
	return IPC_ProcStartup(data,code);
}


// varargs CreateNewProcTags
struct Process *CreateNewProcTags(Tag tag1,...)
{
	struct Library *DOSBase;
	struct ExecBase *Exec=(struct ExecBase *)*((ULONG *)4);

	// Find dos
	DOSBase=(struct Library *)FindName(&Exec->LibList,"dos.library");

	// Create process
	return CreateNewProc((struct TagItem *)&tag1);
}
