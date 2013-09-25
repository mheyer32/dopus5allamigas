/* Replacement functions */

#include "amiga.h"


#if defined(__amigaos3__)
ULONG GlobalStuffChar = 0x16c04e75;
#endif

int stccpy(char *p, const char *q, int n)
{
	char *t = p;

	while ((*p++ = *q++) && --n > 0);
		p[-1] = '\0';

	return p - t;
}
