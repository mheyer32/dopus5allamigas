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

#include "dopuslib:dopusbase.h"
#include "dopuslib:dopuspragmas.h"

char *version="$VER: DOpusRT 62.0 (14.7.97)";

void __stdargs __main(char *command)
{
	struct Library *DOpusBase;
	char *ptr,*lfptr=0;
	BOOL quote=0;

	// Skip to first argument
	if (*command=='\"')
	{
		quote=1;
		++command;
	}
	while (*command)
	{
		if (*command==' ' && !quote) break;
		else if (*command=='\"' && quote)
		{
			++command;
			break;
		}
		++command;
	}
	while (*command==' ') ++command;

	// Strip linefeed
	ptr=command;
	while (*ptr)
	{
		if (*ptr=='\n')
		{
			*ptr=0;
			lfptr=ptr;
			break;
		}
		++ptr;
	}

	// Valid arguments?
	if (*command)
	{
		// Open dopus library
		if (!(DOpusBase=OpenLibrary("dopus5:libs/dopus5.library",43)))
			exit(0);

		// Launch program
		WB_Launch(command,0,LAUNCH_WAIT);

		// Close library
		CloseLibrary(DOpusBase);
	}

	// Put linefeed back
	if (lfptr) *lfptr='\n';

	exit(0);
}
