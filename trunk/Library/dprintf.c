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

extern struct Library *LocaleBase;
void __asm LSprintf(register __a3 char *,register __a0 char *,register __a1 APTR);

// printf routine, calls locale if available
unsigned long __asm printf_hook(
	register __a0 struct Hook *hook,
	register __a1 char ch)
{
	char *ptr=(char *)hook->h_Data;
	*ptr++=ch;
	hook->h_Data=(APTR)ptr;
	return 0;
}

void __stdargs __saveds DPrintF(char *buffer,char *string,long data,...)
{
	// Locale library available?
	if (LocaleBase)
	{
		struct Hook hook;

		// Fill out hook
		hook.h_Entry=(unsigned long (*)())printf_hook;
		hook.h_Data=(APTR)buffer;
		FormatString(0,string,(APTR)&data,&hook);
	}

	// Otherwise, use lsprintf()
	else LSprintf(buffer,string,(APTR)&data);
}
