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

#ifndef _DOPUS_REQUESTERS
#define _DOPUS_REQUESTERS

#define CHECKERROR_ABORT		3
#define CHECKERROR_SKIP			2
#define CHECKERROR_TRY_AGAIN	1

#define EXISTREPLACE_LEAVE		0
#define EXISTREPLACE_REPLACE	1
#define EXISTREPLACE_ALL		2
#define EXISTREPLACE_ABORT		2
#define EXISTREPLACE_AGAIN		2
#define EXISTREPLACE_ABORT2		3

struct super_request_data
{
	struct DOpusSimpleRequest request;
	char *gad,*gadgets[11];
	int return_values[10];
	short ret_val,gad_count;
};



// Prototypes
short super_request_args(APTR,char *,ULONG,...);
short super_request(APTR,char *,IPCData *,ULONG *);
/*
unsigned short super_request_args(struct Window *,char *,char *,...);
unsigned short super_request_screen_args(struct Screen *,char *,Att_List *,char *,...);
unsigned short super_request_screen_args_ipc(struct Screen *,char *,IPCData *,Att_List *,char *,...);
unsigned short super_request(struct Window *,struct Screen *,char *,char **,IPCData *,Att_List *);
*/

short error_request(struct Window *window,short,char *text,...);
short error_request_a(struct Window *window,short,char **text);

#define ERF_ASYNC	(1<<0)
#define ERF_MOUSE	(1<<3)

APTR alloc_filereq(void);

void global_requester(char *text);
short request_font(struct Window *,char *,char *,short *,ULONG,unsigned short,unsigned char *,short *,short *);

#endif
