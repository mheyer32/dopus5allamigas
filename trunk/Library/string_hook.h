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

typedef struct
{
	struct Hook	hook;
	Att_List	*history;
	ULONG		type;
	ULONG		flags;
	ULONG		a4;
	ULONG		a6;
	struct Task	*change_task;
	short		change_bit;
} HookData;

ULONG __asm string_edit_hook(
	register __a0 HookData *hook,
	register __a1 ULONG *msg,
	register __a2 struct SGWork *work);

HookData *__asm L_GetEditHook(
	register __d0 ULONG type,
	register __d1 ULONG flags,
	register __a0 struct TagItem *tags);
void __asm L_FreeEditHook(register __a0 APTR hook);
