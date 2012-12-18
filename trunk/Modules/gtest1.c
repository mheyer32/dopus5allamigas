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

#define BUFFERSIZE 256


LONG main(VOID);
LONG GetPath(UBYTE * path, UBYTE * buffer, LONG buffersize);
UBYTE *ItsWild(UBYTE * string);

LONG main(VOID)
{
  struct RDArgs  *readargs;
  LONG            rargs[5];
  UBYTE          *source;
  ULONG           buffersize = 0;
  UBYTE          *sourcedir;
  UBYTE          *textbuffer;
  struct AnchorPath *anchorpath;
  struct FileInfoBlock *fib;
  BPTR            dirlock, filelock;
  LONG            error, rc = 0;


    rargs[0] = 0L;

if	(readargs = ReadArgs("SOURCE/A", rargs, NULL))
	{

	  source = (UBYTE *) rargs[0];


	  if	(!(sourcedir = AllocVec(strlen(source) + 129, MEMF_CLEAR)))
		error = ERROR_NO_FREE_STORE;
	  else
		{
		/* 128 bytes to print informative text */
		textbuffer = sourcedir + strlen(source) + 1;

		buffersize = BUFFERSIZE;
		
		if	((error = GetPath(source, sourcedir, strlen(source) + 1) == 0))
			{
			if	(!(dirlock = Lock(sourcedir, SHARED_LOCK)))
				error = IoErr();
			else
			  	{
				UnLock(dirlock);

if	(anchorpath = AllocVec(sizeof(struct AnchorPath) + buffersize,MEMF_CLEAR))
	{
	anchorpath->ap_Strlen = buffersize;

	if	((error = MatchFirst(source, anchorpath)) == 0)
		{
		do
			{
			char *path;

			fib = &(anchorpath->ap_Info);
		
			path=anchorpath->ap_Buf;

			/*
			 * APF_DIDDIR indicates that we used returned from a
			 * directory. In that case we clear both APF_DIDDIR and
			 * APF_DODIR, so we can start afresh with the next one.
			 */
	
			printf("path %s - %lx ",anchorpath->ap_Buf,anchorpath->ap_Flags);
		
			
			if	(anchorpath->ap_Flags & APF_DIDDIR)
				{
				anchorpath->ap_Flags &= ~(APF_DODIR | APF_DIDDIR);
				//printf(" Returned --- SKIP\n");
				}
			else
				{

				if	(fib->fib_DirEntryType > 0 )
					{
					anchorpath->ap_Flags |= APF_DODIR;
					printf("=============================");
					}
				else
					{
					// Trim .info if needed
					if	(strlen(path) >= 5
						&& !stricmp( path + strlen(path) - 5, ".info" ))
						{
						printf("ICON ");
						
						}
	
					else
						printf("NOT ICON");
					}
				}
				
			printf("\n");

			} while ((error = MatchNext(anchorpath)) == 0);
		}
		
	MatchEnd(anchorpath);

	if	(error == ERROR_NO_MORE_ENTRIES)
		error = 0;
	
	FreeVec(anchorpath);
	}
				}
			}
		
		
		FreeVec(sourcedir);
		}
	FreeArgs(readargs);
	}

return (rc);
}

LONG GetPath(UBYTE * path, UBYTE * buffer, LONG buffersize)
{
  UBYTE	*pathpart, *filepart;
  UBYTE	*tmp1, *tmp2;
  BPTR	lock;
  struct FileInfoBlock *fib;
  LONG	error = 0;


  /*
   * If there seems to be no path, the pathpart will point to the filepart too, so we
   * need to check for that.
   */
  filepart = FilePart(path);
  pathpart = PathPart(path);

  /*
   * This also handles cases where there is only a volume/device name, only a
   * directory name or a combo of those.
   */
  if	(pathpart == path)
  {

	/*
	 * There seems to be only one component. Copy it if it is not wild. Caller will
	 * have to check whether if it exists and if it is a file or directory.
	 */
	if	(!(ItsWild(pathpart)))
	  pathpart = NULL;
  }

  if	(pathpart != path)
  {

	/*
	 * If pathpart equals filepart (pointer wise) then there is only one component
	 * (possible preceeded by a volume name).
	 */
	if	(pathpart == filepart)
	{
	  if	(!(ItsWild(pathpart)))
		pathpart = NULL;
	}
	else
	{
	  /* Try to lock it to determine if the last component is a directory. */
	  if	(lock = Lock(path, SHARED_LOCK))
	  {
		if	(fib = AllocVec(sizeof(struct FileInfoBlock), MEMF_CLEAR))
		{
		  if	((Examine(lock, fib)) == DOSTRUE)
		  {
			/* Hey it's a directory after all */
			if	(fib->fib_DirEntryType > 0)
			  pathpart = NULL;
		  }
		  FreeVec(fib);
		}
		UnLock(lock);
	  }										  /* else treat it as a filename */
	}

	/* Copy the pathpart in the buffer */
	tmp1 = buffer;
	tmp2 = path;
	while ((*tmp1++ = *tmp2++) && (tmp2 != pathpart))
	{
	  if	(tmp1 == (buffer + buffersize))
	  {
		error = ERROR_NO_FREE_STORE;
		break;
	  }
	}
	*tmp1 = '\0';								/* NULL terminate. */
  }

  return (error);
}

UBYTE * ItsWild(UBYTE * string)
{
  static UBYTE   *special = "#?*%([|";
  UBYTE		  *tmp = string;
  COUNT		   i;

  do
  {
	for (i = 0; special[i] != '\0'; i++)
	{
	  if	(*tmp == special[i])
		return (tmp);
	}
	tmp++;
  } while (*tmp);

  return (NULL);
}
