/* Replacement functions */

#include "dopus.h"

int stccpy(char *p, const char *q, int n)
{
	char *t = p;

	while ((*p++ = *q++) && --n > 0);
		p[-1] = '\0';

	return p - t;
}


/**********************************************************/
/******** Remove this when added to dopus5.library ********/

LONG MatchFirst64(STRPTR pat, struct AnchorPath *panchor)
{
	// MatchFirst() returns 0 for success, errorcode for error
	LONG error = 0;
	BPTR lock = 0;
	FileInfoBlock64 *anchorfib = (FileInfoBlock64 *)&panchor->ap_Info;

	if ((error=MatchFirst(pat, panchor))) return error;
	anchorfib->fib_Size64 = (UQUAD)panchor->ap_Info.fib_Size;

	if (((struct Library *)SysBase)->lib_Version >= 50)
#ifdef __amigaos4__
	{
		struct ExamineData *exdata;

		if (!(lock = Lock(panchor->ap_Info.fib_FileName, MODE_OLDFILE)))
			return error;
		if ((exdata=ExamineObjectTags(EX_FileLockInput, lock, TAG_END)))
		{
			anchorfib->fib_Size64 = (UQUAD)exdata->FileSize;
			FreeDosObject(DOS_EXAMINEDATA, exdata);
		}
	}
#elif defined(__MORPHOS__)
	{
		D_S(FileInfoBlock, fib)

		if (!(lock = Lock(panchor->ap_Info.fib_FileName, MODE_OLDFILE)))
			return error;
		if (Examine64(lock, fib, TAG_DONE))
			anchorfib->fib_Size64 = fib->fib_Size64;
	}
#endif

	if (lock) UnLock(lock);
	return error;
}

LONG MatchNext64(struct AnchorPath *panchor)
{
	// MatchNext() returns 0 for success, errorcode for error
	LONG error = 0;
	BPTR lock = 0;
	FileInfoBlock64 *anchorfib = (FileInfoBlock64 *)&panchor->ap_Info;

	if ((error=MatchNext(panchor))) return error;
	anchorfib->fib_Size64 = (UQUAD)panchor->ap_Info.fib_Size;

	if (((struct Library *)SysBase)->lib_Version >= 50)
#ifdef __amigaos4__
	{
		struct ExamineData *exdata;

		if (!(lock = Lock(panchor->ap_Info.fib_FileName, MODE_OLDFILE)))
			return error;
		if ((exdata=ExamineObjectTags(EX_FileLockInput, lock, TAG_END)))
		{
			anchorfib->fib_Size64 = (UQUAD)exdata->FileSize;
			FreeDosObject(DOS_EXAMINEDATA, exdata);
		}
	}
#elif defined(__MORPHOS__)
	{
		D_S(FileInfoBlock, fib)

		if (!(lock = Lock(panchor->ap_Info.fib_FileName, MODE_OLDFILE)))
			return error;
		if (Examine64(lock, fib, TAG_DONE))
			anchorfib->fib_Size64 = fib->fib_Size64;
	}
#endif

	if (lock) UnLock(lock);
	return error;
}

// Returns file size from FIB
#ifdef USE_64BIT
VOID getfibsize(struct FileInfoBlock *fib, UQUAD *size)
{
	UQUAD fibsize = (UQUAD)((FileInfoBlock64 *)fib)->fib_Size64;
	*size = fibsize;
}
#else
VOID getfibsize(struct FileInfoBlock *fib, LONG *size)
{
	*size = fib->fib_Size;
}
#endif

/**********************************************************/

