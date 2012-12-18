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

#define DECR_COL0 0L
#define DECR_COL1 1L
#define DECR_POINTER 2L
#define DECR_SCROLL 3L
#define DECR_NONE 4L
#define PP_OPENERR -1L
#define PP_READERR -2L
#define PP_NOMEMORY -3L
#define PP_CRYPTED -4L
#define PP_PASSERR -5L
#define PP_UNKNOWNPP -6L

ULONG ppLoadData(char *,ULONG,ULONG,char **,ULONG *,BOOL(*)());

#pragma libcall PPBase ppLoadData 1E BA910806
