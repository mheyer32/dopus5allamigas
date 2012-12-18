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

char *versionstring ="$VER: ftp.module 68.14 (31.05.99)";

/****************************************************************

24.1.97	gp	changed get routines to speed up.
07.2.97	gp	Added GUI to addressbook
13.02.97	changed opening of socket lib for addresbook	
		fixed dnd not updating lister
		changed gui layout to buttons under list view

19.02.97
		Fixed alignment of Debug checkbox
		Fixed problem with small OK requester - fixed in Opus
		Fixed problem with config not being updated when save/use
		Added NOOP timeouts to keep connection alive
		Added buffered sgets from socket routines with 1K buffer

	55.74	Fixed saveconfig - was saving then updating it ;-(
	55.75	Changed the way aborts SIGBREAK_CTRL_D are handled in selectwait
		Aborts now seem to work much better than AD's SetSignal method
		Fixed problem of Write disk failure not being reported
		Added NOOP gadget

	55.76	Added flush_socket_buffer() to try to stop the timeout on List
	55.77	Fixed timeout on List function - revc can return 0 for EOF
	55.78   Put back single char get for getreply to fix timeout problems.
		Compiling ftp_lister_xfer.c with Optimization caused prog to crash!!
		Was a stack problem so increased stack sizes to 8K

	55.81	Fixed enforcer hit with no entries in addressbook
		Added LISTER/K to template for FTPConnect to parse ftp://....

	55.82	Fixed addressbook freeing list before closewindow

	55.90	Added addressbook kept in flushable memory with low mem notification
		Added copy between FTP listers.


	55.91	Fixed problem with ftp-ftp copy removing handle at end of transfer
		Changed ftp.c method of sending ftp-ftp, now just uses the
		already open ctrl connection

	55.92	Added method of updating bar during ftp/ftp tranfers
		Fixed problem with incorrect files a of b update during deletes
	
	55.93	Increased file length from 40 to 108 Good idea? Maybe not
	
	55.94	Fixed problems with filelengths/case only aplying to 1st lister
		added settings to whenever lister clear is called.

	55.95	Added callback hook for desktop notification

	55.96	Added extra calls to handle DnD to Disk/desktop

	60.00	Released with Magellan

	60.1	Added DnD to Dirs
	
	60.11	Fixed abort on Puts not aborting complete list of files
		Fixed problem with ftp-ftp transfers and Failure of PORT command
		 to things such as Webraven NT box

	60.12	Fixed problem with multiple file transfer caused by above

	60.13   Changed ftp.c to not use getservbyport since not upported by TermiteTCP

	60.14	Fixed problem with resume on multiple selected files where a file did not
		exist in the dest.

	62.00	Release Opus 562


	62.01	Minor changes to comply with PatchWork.
		

	63.20	1998 version
		Re-write for recursive transfers
		new config/addressbook system etc and lots


	63.21	Fixed 	initial cd problem
			crash on recursive transfer
			anon settings
			
		----------------
	63.22	Added AMFTP import

	63.23	Prohibited site to site drag and drop into subdirectories
		File Transfer Progress display option was not correct

	63.24	Adressbook now remembers window positions
		If SHIFT DC on addressbook then does not close window

	63.25	DoubleClick and a few other functions weren't returning
		the correct result to ARexx.

		The wrong path could be displayed in the lister path gadget
		if the initial path was invalid on connecting.

	63.26	Added checking for correct Amftpprfile file
		Fixed problem with DC on linked files

	63.27	Fixed some memory leaks

	63.28	Changed site leftout icon to FTPSite.info
		Now uses FTPDirectory.info and FTPFile.info
		for leftout dirs and files respectively

		Changes to layout code for addressbook to solve font
		problems

	  .29	Fixed problem in ftp.c with not setting timeout for selectwait
		timeout which caused busywait type loop! (Various)

		Changed ftp_utils CreateFunctionFile() to add icon safety

	  .30	Changed connect requester so it is blank by default with a new
		gadget 'Last Site' to get last stored entry. (Thomas)

	  .31	Changed DnD function onto button. Now creates a name for the
		button as well. (Martin)

		Fixed problems with entering URL ftp:// in Device Lister
		(ftp_lister_connect changed to use lst_empty instead of lst_clear)

		Fixed problem with typing new path into path gadget which would
		change path before comparing old/new and thus cause old cache entry
		to be changed incorrectly. (should have been calling lister_list with
		rescan=FALSE so as to call lst_empty and not lst_clear)

	  .32	If Parent or Root failed the error was not being reported.	

		A detached lister could be left open if NOOPs were enabled
		and the connection timed out anyway.

	  .33	Changed progress display to provide optional 3 line display with
		%, time elapsed and estimated

		Made some changes to fix problems with incorrect setting of
		protection bits. NOTE: Does not always update the lister
		correctly. Andrew to fix later.

	  .34	Changes to progress and multiline display including 
			show details during index/DC etc

	  .35	'Copy/Also Copy Source's xxx' and 'Copy/Set Source Archive
			Bit' would use the local Opus settings if the source
			lister was a local one.  Now the ftp settings are
			always used.  For site-site copy, the source is used.

		When the above options were enabled, the resulting file
			would have the correct protection bits, date,
			and comment; but the lister didn't always reflect
			this.  When uploading files with 'Also Copy Source's
			Datestamp/Protection Bits' turned off, these fields
			are only approximated to save unnecessary network
			overhead.  You can always rescan the destination
			afterward if these fields are important.

		Site-site copy would always report file size as 0.  This is
			now fixed.  If you abort a transfer the resulting
			size is not actually known without a rescan so the
			size will be shown as 1/2 the total size.

	  .36	With 'Copy/Set Source Archive Bit' enabled, the source lister
			was being updated for downloads even though this options
			is only possible for uploads.
	
	  .37	The 'passive' option was broken.  Not any more.

	  .38	Implemented support for servers with broken ls command
			that breaks when a dirname contains spaces.
			Set Env:DOpus/ftp_broken_list for now.

	  .39	The above mentioned broken servers are now also supported
	  		for the remaining recursive operations of
	  		Delete, Protect, GetSizes, and FindFile.

	  .40	Fixed small problem with FTPOoptions description

	  .41	Added environment variable "DOpus/ftp_fred_hack" which
	  		allows OpusFTP to work with filenames which begin
	  		with spaces.  Note that there is potential for
	  		this to cause some servers to break.

			Aborted transfers now have a comment set indicating
			that they have been aborted and what their full size is.

			Colon ":" characters are now filtered to underscores "_".

	  .42	Fixed some problems with  recursive copy of long filename, incorrect
		CurrentDir(newlock) could lock SYS:, fixed SetComment writing too long a comment


	  .43	Fixed problems with leftout on desktop for known SITE where the
	 	full dir path was not accepted. Changed so ALL leftouts now ue
		the URL syntax instead of SITE

		Changed old fred_hack env var to config options special_dir
		and added new ui flag UI_SPECIAL_DIR to support this


26.9.98	68.0	release version

3.3.99  68.1	Fixed problem with send() command not having \r\n at the end
		which caused problems with some sites such as ftp.thule.no

	68.02	Fixed Trevor's bug with list in Addressbook
		Fixed problem with FTP:// in lister not scanning dir
		
	68.3	Really fixed Trevors ftpAddressbook problem.

	68.4	Fixed crash when HELP on Options windows
		(was incorrectly setting busy on wrong window)

19.3.99	68.5	Modified unix_line_to_entryinfo to account for foreign date strings
		Dates for these are set at 0 time 1/1/78


	68.10	Release version with 5.81 archive

	68.11	Fixed problems with lost connections 421 on passive and other
		modes. dopus/NoBeeGees will disable check

	68.12	Modified ftp( to eliminate extra 1K buffer

		Fixed problem with lst_server_err not having correct default
		string which could give blank msg string in requester

	68.13	Now preserves addressbook size via dopus/windows/ftp

	68.14	Fixed problem with update/newer and replaceall switches
		If replaceall was set then AD was not checking the replace
		requester for update/newer.





Still to do:




	Suggestions
	-----------	

	Not so important
	----------------
	*	Support Read, Play etc by calling modules directly with list of all temp files downloaded
	*	Doesn't work with VM/CMS, VAX/VMS, or OS/2
	*	Debugging switchable in debug version

	Systems tested
	----------------------------
	*	"VMS MultiNet V3.4"													(a.psc.edu)
			"LIST -alF" doesn't work
			"LIST" works
			list format not understood
	*	"VMS"																(ada.cenaath.cena.dgac.fr)
			"LIST -alF" works
			list format not understood
	*	[News-OS]															(alpha.gnu.ai.mit.edu)
			SYST not supported, no info in startup message
			"LIST -alF" works
	*	"VM is the operating system of this server."			(bitnic.educom.edu)
			"LIST -alF" doesn't work
			"LIST" works
			list format not understood
	*	'bwl FTP Server for NW 3.1x, 4.xx  (v1.10), (c) 1994 HellSoft.'	(bwl.bwl.th-darmstadt.de)
			SYST not supported
			"LIST -alF" works
			ABOR works - sort of
	*	"UNIX type:OS/2"													(ftp.ciw.uni-karlsruhe.de)
			works just like unix
	*	"Windows_NT version 3.50"											(ftpserv.interlan.com)
			SITE DIRSTYLE switches between dos/unix ls format
			"MSDOS-like directory output is off/on" is result
	*	"MACOS Peter's Server"												(sylva.for.ulaval.ca)
			no links field in LIST output
	
****************************************************************/

