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

void * __asm AsmCreatePool(register __d0 ULONG,register __d1 ULONG,register __d2 ULONG,register __a6 struct Library *);
void __asm AsmDeletePool(register __a0 void *,register __a6 struct Library *);
void * __asm AsmAllocPooled(register __a0 void *,register __d0 ULONG,register __a6 struct Library *);
void __asm AsmFreePooled(register __a0 void *,register __a1 void *,register __d0 ULONG,register __a6 struct Library *);

typedef struct
{
	APTR			pool_header;	// Header for pooling
	struct MinList		memory_list;	// List if not pooling
	struct SignalSemaphore	lock;		// Lock for task protection
	ULONG			puddle_size;	// Size of puddles for pooling
	ULONG			thresh_size;	// Threshold for pooling
	ULONG			type;		// Type of memory
	ULONG			flags;		// Flags
	ULONG			total;		// Total memory allocated under this handle
	ULONG			check_val;	// Header check value
} MemHandle;

#define	MEMHF_CLEAR		(1<<0)		// Clear memory
#define MEMHF_LOCK		(1<<1)		// Want locking
