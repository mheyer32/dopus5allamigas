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

#include "dopusbase.h"
#include "dopuspragmas.h"

struct Library *DOpusBase;

void main(void);

void main(void)
{
	if (DOpusBase=OpenLibrary("dopus5.library",0))
	{
		ULONG original;
		APTR handle;
		void **mem;
		int a;

		mem=AllocMemH(0,512*4);

		printf("\navail mem : %ld\n\n",(original=AvailMem(MEMF_ANY)));

		handle=NewMemHandle(4096,256,MEMF_CLEAR);
		printf("handle %lx allocating 128x4096 using pools (puddle 4096)...\n",handle);
		for (a=0;a<4096;a++)
			if (!(AllocMemH(handle,128)))
			{
				printf("failed at %ld\n",a);
				break;
			}
		printf("allocating 128x512\n");
		for (a=0;a<512;a++)
			if (!(mem[a]=AllocMemH(handle,128)))
			{
				printf("failed at %ld\n",a);
				break;
			}
		printf("used : %ld\n",original-AvailMem(MEMF_ANY));
		printf("freeing 128x512\n");
		for (a=0;a<512;a++)
			if (mem[a])
			{
				FreeMemH(mem[a]);
				mem[a]=0;
			}
		printf("freeing memory\n");
		ClearMemHandle(handle);
		printf("lost: %ld\n",original-AvailMem(MEMF_ANY));
		printf("allocate 1024 : %lx\n",AllocMemH(handle,1024));
		FreeMemHandle(handle);
		printf("lost: %ld\n",original-AvailMem(MEMF_ANY));

		printf("\navail mem : %ld\n\n",(original=AvailMem(MEMF_ANY)));

		handle=NewMemHandle(0,0,MEMF_CLEAR);
		printf("handle %lx allocating 128x4096 without pools...\n",handle);
		for (a=0;a<4096;a++)
			if (!(AllocMemH(handle,128)))
			{
				printf("failed at %ld\n",a);
				break;
			}
		printf("allocating 128x512\n");
		for (a=0;a<512;a++)
			if (!(mem[a]=AllocMemH(handle,128)))
			{
				printf("failed at %ld\n",a);
				break;
			}
		printf("used : %ld\n",original-AvailMem(MEMF_ANY));
		printf("freeing 128x512\n");
		for (a=0;a<512;a++)
			if (mem[a])
			{
				FreeMemH(mem[a]);
				mem[a]=0;
			}
		printf("freeing memory\n");
		ClearMemHandle(handle);
		printf("lost: %ld\n",original-AvailMem(MEMF_ANY));
		printf("allocate 1024 : %lx\n",AllocMemH(handle,1024));
		FreeMemHandle(handle);
		printf("lost: %ld\n",original-AvailMem(MEMF_ANY));

		printf("\navail mem : %ld\n\n",(original=AvailMem(MEMF_ANY)));

		printf("allocate 131072 bytes without a handle : %lx\n",
			(handle=AllocMemH(0,128*1024)));
		printf("used : %ld\n",original-AvailMem(MEMF_ANY));
		printf("freeing memory\n");
		FreeMemH(handle);

		printf("allocating 128x512\n");
		for (a=0;a<512;a++)
			if (!(mem[a]=AllocMemH(0,128)))
			{
				printf("failed at %ld\n",a);
				break;
			}
		printf("used : %ld\n",original-AvailMem(MEMF_ANY));
		printf("freeing 128x512\n");
		for (a=0;a<512;a++)
			if (mem[a])
			{
				FreeMemH(mem[a]);
				mem[a]=0;
			}
		printf("lost: %ld\n",original-AvailMem(MEMF_ANY));

		printf("\navail mem : %ld\n\n",(original=AvailMem(MEMF_ANY)));

		FreeMemH(mem);

		CloseLibrary(DOpusBase);
	}
}
