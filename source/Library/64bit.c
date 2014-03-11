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

void LIBFUNC L_DivideU64(
	REG(a0, UQUAD *num),
	REG(d0, ULONG div),
	REG(a1, UQUAD *rem),
	REG(a2, UQUAD *quo))
{
	UQUAD quotient = *num / div;
	*rem = *num - (div * quotient);
	*quo = quotient;
}

// Convert unsigned integer to a string
void LIBFUNC L_ItoaU64(
	REG(a0, UQUAD *num),
	REG(a1, char *str),
	REG(d0, int str_size),
	REG(d1, char sep))
{
	char *result;
	char *s;
	int pos = 1;
	UQUAD number = *num;
	UQUAD remainder;

	s = &str[str_size - 1];
	(*s--) = '\0';

	do
	{
		result = s;
		L_DivideU64(&number, 10, &remainder, &number);
		(*s--) = '0' + (remainder % 10);
		if (sep && (pos % 3) == 0)
			(*s--) = sep;
		pos++;
	}
	while (number>0);

	if (str < result)
	{
		for (pos = 0; pos < str_size; pos++)
			str[pos] = result[pos];
	}
}

// Do division (fake float) into a string
void LIBFUNC L_DivideToString64(
	REG(a0, char *string),
	REG(d0, int str_size),
	REG(a1, UQUAD *bytes),
	REG(d1, ULONG div),
	REG(d2, int places),
	REG(d3, char sep))
{
	UQUAD whole;
	//ULONG remainder;
	UQUAD remainder;

	// Zero?
	if (div==0)
	{
		string[0]='0';
		string[1]=0;
		return;
	}

	// Do division
	L_DivideU64(bytes,div,&remainder,&whole);

	// Get whole number string
	L_ItoaU64(&whole,string,str_size,sep);

	// Want remainder?
	if (places>0)
	{
		char rem_buf[20],form_buf[10];
		unsigned long rem100;

		// Convert to fraction
		rem100=remainder*100/div;

		// Round up
		if (places==1) rem100+=5;

		// Rounded up to next whole number?
		if (rem100>99)
		{
			// Move to next whole number
			rem100-=100;
			whole++;

			// Get whole number string again
			L_ItoaU64(&whole,string,str_size,sep);
		}	

		// Build formatting string
		lsprintf(form_buf,"%%0%ldld",places+1);

		// Convert remainder to a string, chop to desired decimal places
		lsprintf(rem_buf,form_buf,rem100);
		rem_buf[places]=0;

		// Not zero?
		if (atoi(rem_buf)!=0)
		{
			char *ptr=string+strlen(string);
			lsprintf(ptr,"%lc%s",decimal_point,(IPTR)&rem_buf);
		}
	}
}

// Return a disk size as a string
void LIBFUNC L_BytesToString64(
	REG(a0, UQUAD *bytes),
	REG(a1, char *string),
	REG(d0, int str_size),
	REG(d1, int places),
	REG(d2, char sep))
{
	UQUAD numbytes=*bytes;
	ULONG div=0;
	char *size_str="K";

	// Less than a kilobyte?
	if (numbytes<1024)
	{
		// Nothing?
		if (numbytes<1024) strncpy(string,"0K",str_size);
		else
		{
			L_ItoaU64(&numbytes,string,str_size,sep);
			strncat(string,"b",str_size);
		}
		return;
	}

	// Convert to kilobytes
	numbytes>>=10;

	// Fucking huge?
	if (numbytes>1073741824) strncpy(string,"HUGE",str_size);

	// Gigabyte range?
	else
	if (numbytes>1048576)
	{
		div=1048576;
		size_str="G";
	}

	// Megabyte range?
	else if (numbytes>4096)
	{
		div=1024;
		size_str="M";
	}

	// Kilobytes
	else
	{
		L_ItoaU64(&numbytes,string,str_size,sep);
		strncat(string,"K",str_size);
	}

	// Need to do a division?
	if (div)
	{
		// Do division to string
		L_DivideToString64(string,str_size,&numbytes,div,places,sep);

		// Tack on character
		strncat(string,size_str,str_size);
	}
}
