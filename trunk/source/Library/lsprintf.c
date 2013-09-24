#include "dopuslib.h"

#if defined(__amigaos3__)
ULONG GlobalStuffChar = 0x16c04e75;
#endif

void LSprintf(char *buffer, char *string, APTR data)
{
	RawDoFmt(string, data, DOPUS_RAWFMTFUNC, buffer);
}

#if 0
void VARARGS68K lsprintf(char *buf, char *fmt, ...)
{
#if defined(__amigaos4__) || defined(__MORPHOS__)
	void *stuffchar = "\x16\xc0\x4e\x75"; // MOVE.B D0,(A3)+ | RTS
#else
	void *stuffchar = NULL;
#endif
	VA_LIST args;

	VA_START(args, fmt);
	RawDoFmt(fmt, VA_ARG(args, void *), stuffchar, buf);
	VA_END(args);
}
#endif
