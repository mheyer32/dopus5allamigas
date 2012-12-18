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
	struct Task	*task;
	char		operation[40];
	long		data;
	long		flags;
	char		string_data[128];
} DebugPacket;

typedef struct
{
	struct Node	node;
	struct Task	*task;
	char		task_name[40];
	char		operation[40];
	long		data;
	long		flags;
	char		string_data[128];
} DebugNode;

#define IPC_SETDEBUG	1000
#define IPC_CLEARDEBUG	1001
#define IPC_SHOWDEBUG	1002

void __asm L_SetDebug(
	register __a0 char *operation,
	register __a1 char *string_data,
	register __d0 ULONG data,
	register __d1 ULONG flags);
void __asm L_ClearDebug(void);
void __asm L_ShowDebug(register __a0 char *name);
void debug_proc(void);
