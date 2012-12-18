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

void main(int,char **);
void lsprintf __ARGS((char *,char *,...));

struct Library *DOpusBase;
extern struct Library *IntuitionBase;

void main(int argc,char **argv)
{
	long xxxx,AAAAA,yyyy,nnnnn,temp;
	char buf[16],buf2[40];
	long seed,seed2;
	serial_data data;

	if (!(DOpusBase=OpenLibrary("dopus5:libs/dopus5.library",40)))
		exit(0);

	// Get serial number
	nnnnn=atoi(argv[1]);

	// Seed random generator
	CurrentTime((unsigned long *)&seed,(unsigned long *)&seed2);
	Seed(AvailMem(MEMF_ANY)*seed+seed2);

	// Get random key
	xxxx=Random(10000);
	if (xxxx>9999) xxxx=9999;

	// Calculate yyyy
	temp=xxxx+nnnnn;
	yyyy=temp*temp*temp;

	// Calculate AAAAA
	AAAAA=xxxx+yyyy;
	AAAAA*=AAAAA;
	temp=nnnnn*nnnnn*nnnnn;
	AAAAA*=temp;

	// Build serial number
	lsprintf(buf2,"%04ld",xxxx);

	// Get AAAAA string, pad with A's to 5 digits
	Ito26(AAAAA,buf);
	temp=strlen(buf);
	while (temp++<5) strcat(buf,"A");
	temp=strlen(buf);
	if (temp>5) temp-=5;
	else temp=0;
	strcat(buf2,buf+temp);
	strcpy(data.serial_check_1,buf+temp);

	// Get yyyy string
	lsprintf(buf,"%04ld",yyyy);
	temp=strlen(buf);
	if (temp>4) temp-=4;
	else temp=0;
	strcat(buf2,buf+temp);
	strcpy(data.serial_check_2,buf+temp);

	// Build remainder
	lsprintf(buf,"%06ld",nnnnn);
	strcat(buf2,buf);

	// Print serial number
	printf("%s\n",buf2);
	CloseLibrary(DOpusBase);
}
