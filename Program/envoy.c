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

#include "dopus.h"

// Send an envoy command
EnvoyPacket(char *device,ULONG action,ULONG action2,UWORD data,APTR buffer)
{
	struct DevProc *handler;
	long res;

	// Get handler to send message to
	if (!(handler=GetDeviceProc(device,0))) return 0;

	// Try to send with first action
	res=DoPkt(handler->dvp_Port,action,(ULONG)data,(ULONG)buffer,0,0,0);

	// If that failed, send second action
	if (!res) res=DoPkt(handler->dvp_Port,action2,(ULONG)data,(ULONG)buffer,0,0,0);

	// Free handler
	FreeDeviceProc(handler);
	return res;
}
