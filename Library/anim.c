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

#include "dopuslib.h"

void __asm __saveds L_AnimDecodeRIFFXor(
	register __a0 unsigned char *delta,
	register __a1 char *plane,
	register __d0 unsigned short rowbytes,
	register __d1 unsigned short sourcebytes)
{
	register unsigned char ch,*data;
	register unsigned short opcount;
	unsigned short column;

	// Go through image columns
	for (column=0;column<sourcebytes;column++)
	{
		// Get pointer to delta column
		data=plane+column;

		// Number of operations in this column
		opcount=*delta++;

		// Perform operations
		while (opcount--)
		{
			// Get delta code
			ch=*delta++;

			// !=0 means a run
			if (ch)
			{
				// High bit not set means skip
				if (!(ch&128)) data+=rowbytes*(unsigned short)ch;

				// High bit set
				else
				{
					// Mask out high bit
					ch&=127;

					// Run of data
					while (ch--)
					{
						*data^=*delta++;
						data+=rowbytes;
					}
				}
			}

			// ==0 means a repeated byte
			else
			{
				// Get count
				ch=*delta++;

				// Do count
				while (ch--)
				{
					*data^=*delta;
					data+=rowbytes;
				}
				++delta;
			}
		}
	}
}

void __asm __saveds L_AnimDecodeRIFFSet(
	register __a0 unsigned char *delta,
	register __a1 char *plane,
	register __d0 unsigned short rowbytes,
	register __d1 unsigned short sourcebytes)
{
	register unsigned char ch,*data;
	register unsigned short opcount;
	unsigned short column;

	// Go through image columns
	for (column=0;column<sourcebytes;column++)
	{
		// Get pointer to delta column
		data=plane+column;

		// Number of operations in this column
		opcount=*delta++;

		// Perform operations
		while (opcount--)
		{
			// Get delta code
			ch=*delta++;

			// !=0 means a run
			if (ch)
			{
				// High bit not set means skip
				if (!(ch&128)) data+=rowbytes*(unsigned short)ch;

				// High bit set
				else
				{
					// Mask out high bit
					ch&=127;

					// Run of data
					while (ch--)
					{
						*data=*delta++;
						data+=rowbytes;
					}
				}
			}

			// ==0 means a repeated byte
			else
			{
				// Get count
				ch=*delta++;

				// Do count
				while (ch--)
				{
					*data=*delta;
					data+=rowbytes;
				}
				++delta;
			}
		}
	}
}
