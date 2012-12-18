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

;/* DirComp.c - AmigaMail Directory Compare example using MatchFirst()/Next().
sc link GST=include:all.gst GSTIMMEDIATE a.c
quit
 *
 * Pure code if pragmas are used.
 * Monday, 15-Jul-91 16:07:31, Ewout
 *
 * Compiled with SAS/C 5.10a
 */
/*
Copyright (c) 1991 Commodore-Amiga, Inc.

This example is provided in electronic form by Commodore-Amiga,
Inc. for use with the Amiga Mail Volume II technical publication.
Amiga Mail Volume II contains additional information on the correct
usage of the techniques and operating system functions presented in
these examples.  The source and executable code of these examples may
only be distributed in free electronic form, via bulletin board or
as part of a fully non-commercial and freely redistributable
diskette.  Both the source and executable code (including comments)
must be included, without modification, in any copy.  This example
may not be published in printed form or distributed with any
commercial product. However, the programming techniques and support
routines set forth in these examples may be used in the development
of original executable software products for Commodore Amiga
computers.

All other rights reserved.

This example is provided "as-is" and is subject to change; no
warranties are made.  All use is at your own risk. No liability or
responsibility is assumed.
*/

#include <exec/memory.h>
#include <dos/dosextens.h>
#include <dos/rdargs.h>

#include <clib/exec_protos.h>
#include <clib/dos_protos.h>

/* undef PRAGMAS if you don't have them */
#include <pragmas/exec_pragmas.h>
#include <pragmas/dos_pragmas.h>

/* Default size of buffer to build full targetpaths in */
#define BUFFERSIZE 256

static UBYTE   *VersTag = "\0$VER: DirComp 37.1 (15.07.91)";

LONG            main(VOID);
LONG            GetPath(UBYTE * path, UBYTE * buffer, LONG buffersize);
UBYTE          *ItsWild(UBYTE * string);
UWORD           StrLen(UBYTE *);

LONG
main(VOID)
{
  struct DosLibrary *DOSBase;

  struct RDArgs  *readargs;
  LONG            rargs[5], vargs[5];
  UBYTE          *source, *target;
  ULONG           buffersize = 0;
  UBYTE          *sourcedir, *targetdir;
  UBYTE          *textbuffer, *tmp, *tmp1, *tmp2;
  struct AnchorPath *anchorpath;
  struct FileInfoBlock *fib, *targetfib;
  struct Process *process;
  APTR            wptr;
  BPTR            dirlock, filelock;
  BOOL            checkdatestamp, all;
  LONG            date, error, rc = 0;


  /* Fail silently if < 37 */
  if (DOSBase = (struct DosLibrary *) OpenLibrary("dos.library", 37))
  {
    rargs[0] = 0L;
    rargs[1] = 0L;
    rargs[2] = 0L;
    rargs[3] = 0L;
    rargs[4] = 0L;

    if (readargs = ReadArgs("SOURCE/A,TARGET/A,DATE/S,ALL/S,BUFFER/K/N", rargs, NULL))
    {

      source = (UBYTE *) rargs[0];
      target = (UBYTE *) rargs[1];
      checkdatestamp = (BOOL) rargs[2];
      all = (BOOL) rargs[3];

      if (!(sourcedir = AllocMem(StrLen(source) + 129, MEMF_CLEAR)))
        error = ERROR_NO_FREE_STORE;
      else
      {
        /* 128 bytes to print informative text */
        textbuffer = sourcedir + StrLen(source) + 1;

        /* use user specified buffersize if indicated */
        if (rargs[4])
          buffersize = *((LONG *) rargs[4]);
        if (buffersize < BUFFERSIZE || buffersize > 4096)
          buffersize = BUFFERSIZE;

        if (!(targetdir = AllocMem(buffersize, MEMF_CLEAR)))
          error = ERROR_NO_FREE_STORE;
        else
        {
          if (!(targetfib = AllocDosObject(DOS_FIB, NULL)))
            error = ERROR_NO_FREE_STORE;
          else
          {

            /*
             * Check if source and target are valid.
             *
             * Separate source path from pattern (if any). Use the source path figure
             * out what to append to the target.
             */

            /* No requesters */
            process = (struct Process *) FindTask(NULL);
            wptr = process->pr_WindowPtr;
            process->pr_WindowPtr = (APTR) - 1L;

            if ((error = GetPath(source, sourcedir, StrLen(source) + 1) == 0))
            {
              if (!(dirlock = Lock(sourcedir, SHARED_LOCK)))
                error = IoErr();
              else
              {
                UnLock(dirlock);
                if (!(dirlock = Lock(target, SHARED_LOCK)))
                  error = IoErr();
                else
                {
                  UnLock(dirlock);

                  if (anchorpath = AllocMem(sizeof(struct AnchorPath) + buffersize,
                                            MEMF_CLEAR))
                  {
                    anchorpath->ap_Strlen = buffersize;

                    /* Allow to break on CTRL-C */
                    anchorpath->ap_BreakBits = SIGBREAKF_CTRL_C;

                    if ((error = MatchFirst(source, anchorpath)) == 0)
                    {

                      do
                      {
                        fib = &(anchorpath->ap_Info);

                        /*
                         * APF_DIDDIR indicates that we used returned from a
                         * directory. In that case we clear both APF_DIDDIR and
                         * APF_DODIR, so we can start afresh with the next one.
                         */


                        if (anchorpath->ap_Flags & APF_DIDDIR)
                          anchorpath->ap_Flags &= ~(APF_DODIR | APF_DIDDIR);
                        else
                        {

                          /*
                           * Make a filename for the target directory. First copy
                           * targetname into buffer.
                           */
                          targetdir[0] = '\0';
                          tmp = targetdir;
                          tmp1 = target;
                          while (*tmp++ = *tmp1++);

                          /* Skip sourcename in ap_Buf */
                          tmp1 = sourcedir;
                          tmp2 = anchorpath->ap_Buf;
                          while (*tmp1++ == *tmp2++);
                          /* Skip back 1 if not after a separator */
                          if (*(tmp2 - 1) != '/')
                            tmp2--;

                          /*
                           * We hit the source itself, don't compare it, but enter
                           * it.
                           */
                          if (*tmp2 == 0)
                          {
                            anchorpath->ap_Flags |= APF_DODIR;
                            continue;
                          }

                          /* Build it */
                          if (AddPart(targetdir, tmp2, buffersize - 1))
                            vargs[0] = (LONG) targetdir;
                          else
                          {
                            PrintFault(ERROR_NO_FREE_STORE, NULL);
                            break;
                          }

                          /* Lock it and check it out */
                          if (filelock = Lock(targetdir, SHARED_LOCK))
                          {
                            if ((Examine(filelock, targetfib)) == DOSTRUE)
                            {
                              textbuffer[0] = '\0';

                              /*
                               * To get nice output without work I use AddPart() to
                               * add differences to the textbuffer.
                               */
                              if (targetfib->fib_DirEntryType
                                  != fib->fib_DirEntryType)
                                AddPart(textbuffer, "of different type", 128);
                              else
                              {
                                if (targetfib->fib_Size < fib->fib_Size)
                                  AddPart(textbuffer, "smaller", 128);
                                else if (targetfib->fib_Size > fib->fib_Size)
                                  AddPart(textbuffer, "larger", 128);

                                if (checkdatestamp)
                                {
                                  date = CompareDates((struct DateStamp *)
                                        & (fib->fib_Date),
                                      (struct DateStamp *) & (targetfib->fib_Date));
                                  if (date < 0)
                                    AddPart(textbuffer, "older", 128);
                                  else if (date > 0)
                                    AddPart(textbuffer, "newer", 128);
                                }
                              }


                              if (*textbuffer != NULL)
                              {
                                vargs[1] = (LONG) textbuffer;
                                VFPrintf(Output(), "%s: object %s\n", vargs);
                              }
                            }
                            else
                              PrintFault(IoErr(), targetdir);
                            UnLock(filelock);
                          }
                          else
                          {
                            PrintFault(IoErr(), targetdir);

                            /*
                             * If and error occured on a directory name, don't enter
                             * it.
                             */
                            if (fib->fib_DirEntryType > 0)
                              continue;

                          }

                          /*
                           * If the ALL keyword has been used and this is a directory
                           * enter it by setting the APF_DODIR flag.
                           */

                          if (fib->fib_DirEntryType > 0 && all != FALSE)
                            anchorpath->ap_Flags |= APF_DODIR;

                        }

                      } while ((error = MatchNext(anchorpath)) == 0);
                    }

                    MatchEnd(anchorpath);

                    if (error == ERROR_NO_MORE_ENTRIES)
                      error = 0;

                    FreeMem(anchorpath, sizeof(struct AnchorPath) + buffersize);
                  }
                }
              }
              /* Reset windowpointer */
              process->pr_WindowPtr = wptr;
            }
            else
              PrintFault(error, NULL);
            FreeDosObject(DOS_FIB, targetfib);
          }
          FreeMem(targetdir, buffersize);
        }
        FreeMem(sourcedir, StrLen(sourcedir) + 129);
      }
      FreeArgs(readargs);
    }
    else
      error = IoErr();

    SetIoErr(error);
    if (error)
    {
      PrintFault(error, NULL);
      if (error = ERROR_BREAK)
        rc = RETURN_WARN;
      else
        error = RETURN_FAIL;
    }
    CloseLibrary((struct Library *) DOSBase);
  }
  return (rc);
}

LONG
GetPath(UBYTE * path, UBYTE * buffer, LONG buffersize)
{
  UBYTE          *pathpart, *filepart;
  UBYTE          *tmp1, *tmp2;
  BPTR            lock;
  struct FileInfoBlock *fib;
  LONG            error = 0;

  /* Open own copy of dos.library if pragmas are used so it's standalone */
#ifdef PRAGMAS
  struct Library *DOSBase;

  if (!(DOSBase = OpenLibrary("dos.library", 36)))
    return (1);
#endif

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
  if (pathpart == path)
  {

    /*
     * There seems to be only one component. Copy it if it is not wild. Caller will
     * have to check whether if it exists and if it is a file or directory.
     */
    if (!(ItsWild(pathpart)))
      pathpart = NULL;
  }

  if (pathpart != path)
  {

    /*
     * If pathpart equals filepart (pointer wise) then there is only one component
     * (possible preceeded by a volume name).
     */
    if (pathpart == filepart)
    {
      if (!(ItsWild(pathpart)))
        pathpart = NULL;
    }
    else
    {
      /* Try to lock it to determine if the last component is a directory. */
      if (lock = Lock(path, SHARED_LOCK))
      {
        if (fib = AllocMem(sizeof(struct FileInfoBlock), MEMF_CLEAR))
        {
          if ((Examine(lock, fib)) == DOSTRUE)
          {
            /* Hey it's a directory after all */
            if (fib->fib_DirEntryType > 0)
              pathpart = NULL;
          }
          FreeMem(fib, sizeof(struct FileInfoBlock));
        }
        UnLock(lock);
      }                                          /* else treat it as a filename */
    }

    /* Copy the pathpart in the buffer */
    tmp1 = buffer;
    tmp2 = path;
    while ((*tmp1++ = *tmp2++) && (tmp2 != pathpart))
    {
      if (tmp1 == (buffer + buffersize))
      {
        error = ERROR_NO_FREE_STORE;
        break;
      }
    }
    *tmp1 = '\0';                                /* NULL terminate. */
  }

#ifdef PRAGMAS
  CloseLibrary(DOSBase);
#endif
  return (error);
}

UBYTE          *
ItsWild(UBYTE * string)
{
  static UBYTE   *special = "#?*%([|";
  UBYTE          *tmp = string;
  COUNT           i;

  do
  {
    for (i = 0; special[i] != '\0'; i++)
    {
      if (*tmp == special[i])
        return (tmp);
    }
    tmp++;
  } while (*tmp);

  return (NULL);
}

UWORD
StrLen(UBYTE * string)
{
  UBYTE          *length = string + 1;

  while (*string++ != '\0');
  return ((UWORD) (string - length));
}
