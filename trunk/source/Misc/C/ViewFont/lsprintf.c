
#include "font.h"

void LSprintf(char *buffer, char *string, APTR data)
{
	void *stuffchar = "\x16\xc0\x4e\x75"; // MOVE.B D0,(A3)+ | RTS
#if defined(__amigaos4__) || defined(__MORPHOS__)
	stuffchar = NULL;
#endif
	RawDoFmt(string, data, stuffchar, buffer);
}

void VARARGS68K lsprintf(char *buf, char *fmt, ...)
{
	void *stuffchar = "\x16\xc0\x4e\x75"; // MOVE.B D0,(A3)+ | RTS
#if defined(__amigaos4__) || defined(__MORPHOS__)
	stuffchar = NULL;
#endif
	VA_LIST args;

	VA_START(args, fmt);
	RawDoFmt(fmt, VA_ARG(args, void *), stuffchar, buf);
	VA_END(args);
}
