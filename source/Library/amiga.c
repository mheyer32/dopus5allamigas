/* Replacement functions */

#include "amiga.h"

#if defined(__amigaos3__)
ULONG GlobalStuffChar = 0x16c04e75;
#endif

void LSprintf(char *buffer, char *string, APTR data)
{
	RawDoFmt(string, data, DOPUS_RAWFMTFUNC, buffer);
}

#if !defined(__MORPHOS__) && !defined(__AROS__)
int stccpy(char *p, const char *q, int n)
{
	char *t = p;

	while ((*p++ = *q++) && --n > 0);
		p[-1] = '\0';

	return p - t;
}
#endif

