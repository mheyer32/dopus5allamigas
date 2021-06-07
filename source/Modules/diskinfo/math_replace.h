// by Thomas and Salas00 from amigans.net

#include <math.h>

#ifndef PI
	#define PI M_PI
#endif

float SPFlt(int inum)
{
	return (inum);
}

int SPFix(float fnum)
{
	return (fnum);
}

float SPSub(float fnum1, float fnum2)
{
	return (fnum2 - fnum1);
}

float SPMul(float fnum1, float fnum2)
{
	return (fnum1 * fnum2);
}

float SPDiv(float fnum1, float fnum2)
{
	return (fnum2 / fnum1);
}

float SPSincos(float *pfnum2, float fnum1)
{
	*pfnum2 = cos(fnum1);
	return (sin(fnum1));
}
