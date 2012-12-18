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

struct LoginPkt
{
	struct Window	*window;
	char			*name;			// not used
	char			*password;		// not used
};

// Logout (must be called from DO_LAUNCHER process)
void do_mufs_logout(struct LoginPkt *pkt)
{
	struct Library *muBase;
	struct Process *proc;
	APTR wsave;

	// Set window pointer
	proc=(struct Process *)FindTask(0);
	wsave=proc->pr_WindowPtr;
	proc->pr_WindowPtr=pkt->window;

	// Open MUFS library
	if (muBase=OpenLibrary("multiuser.library",39))
	{
		struct muUserInfo *info;

		// Allocate user info
		if (info=muAllocUserInfo())
		{
			struct TagItem tags[6];

			// Fill out tags to logout DOpus
			tags[0].ti_Tag=muT_Global;
			tags[0].ti_Data=TRUE;
			tags[1].ti_Tag=muT_Quiet;
			tags[1].ti_Data=TRUE;
			tags[2].ti_Tag=muT_All;
			tags[2].ti_Data=TRUE;
			tags[3].ti_Tag=muT_Task;
			tags[3].ti_Data=(ULONG)FindTask("dopus");
			tags[4].ti_Tag=TAG_END;

			// Log out
			muLogoutA(tags);

			// Fill out tags to logout DO_LAUNCHER and log back in again
			tags[0].ti_Tag=muT_Graphical;
			tags[0].ti_Data=TRUE;
			tags[1].ti_Tag=muT_Global;
			tags[1].ti_Data=TRUE;
			tags[2].ti_Tag=TAG_END;

			// Log this task out
			info->uid=(muLogoutA(tags)>>16)&0xffff;
			muGetUserInfo(info,muKeyType_uid);

			// Log DOpus task in
			tags[0].ti_Tag=muT_Graphical;
			tags[0].ti_Data=TRUE;
			tags[1].ti_Tag=muT_Task;
			tags[1].ti_Data=(ULONG)FindTask("dopus");
			tags[2].ti_Tag=muT_Own;
			tags[2].ti_Data=TRUE;
			tags[3].ti_Tag=muT_Global;
			tags[3].ti_Data=TRUE;
			tags[4].ti_Tag=muT_UserID;
			tags[4].ti_Data=(ULONG)info->UserID;
			tags[5].ti_Tag=TAG_END;

			// Log in
			muLoginA(tags);

			// Free user info
			muFreeUserInfo(info);
		}

		// Close MUFS
		CloseLibrary(muBase);
	}

	// Restore window pointer
	proc->pr_WindowPtr=wsave;
}
