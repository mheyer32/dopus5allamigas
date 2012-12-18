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

short version_num=82;
char *version_string="Magellan II";

char *_version_str="$VER: DirectoryOpus 5.82 (8.11.99)";

/*
short version_num=1610;
char *version_string="MagBETA";

char *_version_str="$VER: DirectoryOpus 5.1610 (23.4.99)";
*/

/*
                           Directory Opus 5 history

-----------------------------------------------------------------------------
Note : anything marked with a ****** indicates that it needs serious testing.
-----------------------------------------------------------------------------

    2-Feb-95 - Beta 1 release.

    3-Feb-95 - Added PARENT/ROOT back as internal commands.
             - Fixed WBSTARTUP option to not run DOpus itself from WBStartup.
             - Path history in lister popup is now specific to that lister.
             - Removed DEVICELIST/BUFFERLIST commands (and associated requesters).
             - Added "Cache list" option to lister popup.
             - . on keypad now brings up cache list in listers
             - 0 on keypad in listers returns from device/cache list to previous
               buffer
             - Added "Disk Information" option to Icon menu.
               Moved DiskInfo code to external module (diskinfo.module).
             - "Icon/Information" menu option now works in listers.
               Removed IconInfo as an internal command.
             - Added lister Iconify function.
             - Kludged around a problem caused when MagicMenu is running.
               (MagicMenu's fault, as always!)
             - Some problems with SCANDIR fixed. Command template is now
               PATH/M,NEW/S. The NEW switch means always open a new lister.
               Other commands have argument templates, these will be
               revealed in due course :)

    4-Feb-95 - Now works with CD0: and other such filesystems (oops :)
             - Modified lister format editing, now uses drag & drop.
             - Added RESET button to palette editor..
               Can now drop ILBM files onto palette editor to load palettes.
             - Fixed to make sysihack compatible.

    5-Feb-95 - Now stores icon position (when you Snapshot icons) separately
               from Workbench, so you can have different icon positions under
               Opus and Workbench.
             - Fixed a problem with copy not respecting read-only status.
             - Fixed problem with CheckFit with no destination selected.
             - Requesters now have their text displayed in a RECESSED area
               (grumble style guide mumble compliant grumble).
             - Fixed problem setting new User/Lister menu filenames.
             - Dragging and dropping directories from one lister to another
               now COPIES them, unless either shift key is held down
               (in which case they will be read into the lister like before).
               You can also drag more than one directory at once to copy.
             - Added case-insensitive Match command to filetypes.
             - Fixed commodities problem under 37 (default hotkey wasn't
               specified correctly, and pressing any key would cause DOpus
               to activate).
             - Fixed problem with "Select icons automatically"
               (file/byte count was not being updated properly).
             - "Set source archive bit" wasn't updating the display
               to reflect the new protection bit.
             - Clock is now drawn directly to the screen's title bar (blech).
               YES, I KNOW THE CLOCK FLASHES ON AND OFF OCCASIONALLY!!! :)
             - Fixed problem converting old Opus4 functions with more than
               one line.
             - Fixed up palette management a bit (might still be a bit wacko).

    6-Feb-95 - Changed ambiguous "Ok" gadget to "Next" in IconInfo, only
               appears now if necessary. Also fixed locale problem with
               thousands separator.
             - Fixed small problem in menu editor with adding a new item
               while an old one was selected.
             - Icon leaving out is now more Workbench-like in that if you
               drag and drop a file from a lister to the main window the
               icon is only temporarily left-out - you need to actually
               select Leave Out from the Icon menu to make it permanent.
             - Text viewer now recognises space as page down and backspace
               as page up.

    7-Feb-95 - Added arrow button to scroll toolbar if window is too small
               (image from "dopus5:images/ToolbarArrow.image").
             - Fixed bug where last icon in the lister toolbar would not work
               if it fitted "exactly" (ie lister size==toolbar size).
             - Copy now deletes file copies that were unsuccessful
               (aborted, out of space, etc).
             - Fixed problem with "Display mode" list showing public screens
               that weren't actually in public mode. Also now shows proper
               "maximum depth" for public screens.
             - Fixed problem with lister key selection indicator disappearing
               when you resized the window.
             - Fixed ambiguous ghosting and checking in text viewer menus.
             - Fixed maximum comment length (was 80, should be 79).
             - Pressing a letter now scrolls to first FILE starting with that
               character. Pressing a letter with shift scrolls to first DIR.
             - Added requester warning if DOpus can't close its screen.
             - Changed Copy routines to use a variable buffer size, which
               should make aborting a copy more responsive.
    (3:30am) - Fixed problem with the listview boopsi class under 37
               (Enforcer hits, drag and drop didn't work).

    8-Feb-95 - Fixed problem with Print not closing the file.
             - Fixed problem where listers saved in the environment would
               not read their paths if the program was started iconified.
             - Added "Re-read Directory" option to lister path popup thingy.
             - Added "Paint Mode" to main button editor window.
             - The boundaries for horizontal "right mouse button" scrolling
               in listers were a bit small, so, now they're bigger.
             - Implemented keyboard equivalents for buttons and menus, etc.
               The order keys are matched in depends on which window is
               active when you press the key. If the main window is active,
               the order is : User menu, button banks, lister toolbar and
               lister menu. If a lister is active, then the toolbar and
               lister menu are searched first, followed by the user menu
               and button banks. If a button bank is active, then it is
               searched first, then the same order as for the main window
               is used.
             - "Execute Command" now remembers the last command you entered.
             - The "Create Icons" option now works. Appropriate icons should
               be placed in the DOpus5:Icons/ directory.
             - Holding SHIFT when clicking the parent button (window border)
               or choosing parent or root in the lister path popup thingy
               will open a new lister to read into (same as holding shift
               when double-clicking on a directory).

    9-Feb-95 - Holding down shift when the Opus LoadWB command is run will
               cause it to load the old Workbench. That is, if you elect to
               install Opus as a Workbench replacement, you can hold down
               the shift key when you boot to get the original Workbench
               loaded (the original LoadWB command must have been renamed
               as LoadWB_Old).
             - Changed the "Proceed" button to "Discard" when you cancel
               the toolbar/menu editor.. this was bugging some people.
             - Removed the "Replace" options in Settings configuration.
               This has always been rather useless, in my opinion. You
               are now always asked if you want to overwrite an existing
               file.
             - If you tell Opus to replace an existing file, and that file
               is delete-protected, you are now given an additional warning
               (before it would just delete the file).
             - Removed the "Ignore delete protection bit" option from
               the "Delete" settings configuration. This was a bit dangerous,
               and I doubt anyone ever used it (you have the option of
               Unprotect All anyway).
             - In the "Path formats" settings configuration, the format
               editor is now automatically displayed when you press return
               on a newly-entered path. Also, double-clicking on a path
               also brings up the editor.
             - Page up/down via the keyboard in the text viewer now actually
               moves one line less than a page (for consistency). Also
               the 'u' and 'd' keys are now supported for page up/down.
             - Abbreviation for kilobytes fixed in IconInfo ('K'). Also
               fixed some strings in IconInfo to be "style-guide compliant."
             - Starting drag & drop from a lister by pressing the right
               mouse button was broken in beta 1 - this works again.
             - MakeDir now defaults to no icon if the "Create Icons" option
               is turned off.
             - Toolbar buttons now size dynamically (why didn't they before?),
               so you can now have buttons up to 64x64 in size (should keep
               Picollo-64 users happy :)
             - Copying some files by drag&drop into a lister that didn't
               have a path would copy the files to FKW (actually to the
               "current directory"). This is fixed.
             - The correct decimal point for the current locale is now used
               in DiskInfo, etc.
             - Text viewer refreshing on home/end optimised (ie won't refresh
               if already at the top/bottom). Also, the vertical scroller now
               works properly if the file is more than 65535 lines long
               (before you couldn't get past line 65535 with the scroller).
               Note that while file listers will also have this problem, I
               am yet to encounter a directory with more than 64k files
               in it :)
             - If you MOVEd a file/directory, with the "Perform all actions on
               icons" option on, to somewhere on the same device (so that it
               could just be renamed instead of copied/deleted), the icon
               would not get moved. Fixed.
             - If you drag and drop to copy (or other action), you now get
               a progress indicator in the DESTINATION lister (for normal
               operations the indicator appears in the source). The source
               window is not locked for the operation.

   10-Feb-95 - Beta 2 release

   11-Feb-95 - If a file was Read protected and Opus examined it to find out
               its filetype (eg, if you were displaying filetypes in the
               lister), then Nasty Things would happen.
             - Protection bits are now shown in lowercase.
             - Device list format improved, more information now shown.

   12-Feb-95 - Implemented BOOPSI replacement for gadtools palette gadget.
               Rewrote palette management routines. Under the new system,
               you can set up to eight user-defined colours. Lister display
               and button colours can be set to either these user-defined
               colours, or the standard system colours (4 under v37, 8 under
               v39). When running on a custom screen, Opus inherits the
               standard system colours, and these can not be modified. The
               only colours you can change are the user-defined colours.
               This system still needs to be looked at further.
             - Under v39, 8 colour icons are mapped correctly to use the
               upper and lower 4 colours in the palette (ie they will look
               correct no matter what screen depth you are using).
             - Added "Key" field to Settings/Path formats.
             - If the icon of a disk was on top of another icon, and the
               disk was removed, the icon would be erased but the
               icon underneath would not get redrawn correctly.
             - Rescan directory would sometimes not re-read the correct
               directory.
             - Apparently ExamineFH() isn't reliable. Opus was using it
               to get information about files you copied, and the
               size was showing up wrong in some cases. Now re-Lock()s
               and Examine()s the destination file.
             - DEVICELIST and CACHELIST added back in as commands.. sigh...
             - User1 through User4 commands implemented.

   13-Feb-95 - Added "Duplicate" button in menu editor.
             - The "Match" command in filetypes now supports \xxx where
               xxx is a decimal value, as it did in Opus 4.
             - Rearranged the filetypes requester, added Edit button.
             - If you dropped an image into the button editor and clicked
               "Use" without editing the actual function, the new image
               could get lost.
             - Button banks, especially newly created ones, now have
               more logical sizes when they first open.
             - The text viewer would not allow more than one viewer to
               be open on its own screen (public screen name clash).
             - You can select your own backdrop pattern prefs file via the
               "Display Options" settings, and also choose to turn off
               the backdrop pattern. Note that the file you specify must
               be a valid workbench "wbpattern.prefs" type  file (as saved with
               the 3.0 WBPattern editor) or a valid "wb.pat" type file
               as saved with the 2.0 WBPattern editor.

   14-Feb-95 - Directory sorting (and reading) is slightly faster,
               especially on large directories (eg CDROMs).
             - Added "DoubleClick" and "DragNDrop" commands. These
               are like User1-4, but call the double-click and drag'n'drop
               filetypes for selected files.
             - Now uses ObtainPen() rather than ObtainBestPen(), so that
               it will allocate distinct, exclusive pens for the user
               colours (no more linking of pens together).
             - FindFile command now remembers the last search pattern.
             - Titles of some loading/saving requesters changed.
             - Assorted strings changed for consistent capitalisation.
             - The hide/show filters would also filter out directories;
               this was incorrect. Now, only files are tested against the
               filters (except for the Hidden bit filter).
             - Added "Un-Snapshot" option to Icon menu.
             - Hopefully fixed a bug that would cause icons to "jump"
               around the screen when you repositioned one.. needs
               further testing.

   15-Feb-95 - A very nasty bug, that would let you enter values <-128 or
               >127 for the filetype priority, has been fixed. Phew! :)
             - Disk icons could occasionally appear over the top of other
               icons; this has been fixed.
             - "Output results" option in Search works again (dunno what
               happened there - it used to work :)
             - The positioning of icons is now more logical; also, icons
               should never get "lost" off-screen if you switch to a
               backdrop window.
             - Now no longer re-reads the backdrop picture when switching
               from backdrop to non-backdrop window.
             - Programs launched from within Opus now inherit the path list
               correctly.
             - Toolbar buttons now show their right mouse button imagery
               correctly.
             - Fixed a problem where you sometimes couldn't access the
               right mouse button function of a button if the button had
               no left mouse button function defined.
             - The pop-up menus now display the name correctly under v37
               with a proportional font (the last character was being dropped
               before - this is a graphics.library bug!)
             - Wonderful new about requester (about.module) - pity about the
               hedgehog.
             - More requesters now have a recessed look, and thin borders
               in some parts (would like to make this consistent throughout
               but it would need a whole lot more boopsi classes since
               gadtools doesn't support thin borders).

   16-Feb-95 - ClearBuffers command now called FreeCaches.
             - The button to open a filerequester in the function editor now
               works.
             - The button to display a list of {} arguments in the function
               editor now works.
             - Replaced some "s with some 's in the catalog files.
             - If a directory had been changed (and you had the
               Re-read modified caches flag on), and you reactivated the
               lister by clicking on a slider, the lister would "freeze"
               until you released the slider.
             - You can now no longer enter invalid dates for the Datestamp
               function.
             - Diskcopy now selects a destination automatically for you
               (of course you can still pick a different one).
             - If you try to copy a directory into itself, Opus now displays
               an error requester instead of just silently failing.
             - Opus will now allow you to use the CopyAs and MoveAs functions
               with the source and destination the same (make sure you
               specify a different filename though! :)
             - You can now define button functions for the middle mouse button.
               These can be accessed even if you don't have a three button
               mouse by holding shift down and using the left button.
             - Button borders (except in the lister toolbar) now have
               "turned-over tabs" to indicate the presence of a right and/or
               middle mouse button function (as in Opus4).
             - The toolbar editor window would "double-up" (open a new
               window without closing the old one) if you changed the main
               window from backdrop to non-backdrop. The menu editors would
               also do the same thing.
             - If you hold down ALT and click with the left button in a
               lister, any files that were selected will immediately
               start dragging (no new selections will occur).
             - Implemented the Opus4 Verify command, though it's now called
               "Confirm".

   17-Feb-95 - Format now uses a bar graph instead of a textual status
               indication; this is much faster and probably just as
               informative.
             - Opus no longer keeps a lock on all devices it shows an icon
               for.. this means that "fake handlers" like EDGE: will be
               able to be removed while Opus is running. Opus still keeps
               locks on all left-out objects (drawers, programs, etc).
             - Alt now works on toolbar buttons (to jump straight to the
               editor).
             - Recursive file filter implemented (Settings menu). This is
               the same as the old "F" tiny button in Opus4.
             - If you tried to copy a file and there was not enough space
               in the destination, the half-copied file would get left behind.
               It is now deleted. Also fixed problem with move, so now it
               won't delete the original unless the file was copied
               successfully. (Sorry Edmund :)

   18-Feb-95 - File class definition editor tidied up; cycle button changed
               to pop-up list.
             - Changed "Date Format" section in Settings to "Locale" (still
               mis-named I think), added "Thousands separator" option.
             - Cleaned up the datestamp checking logic; should no longer
               occasionally re-read directories unnecessarily.
             - Implemented "Program Groups", accessed via the Icon menu.
               You will need to create a "Groups" subdirectory in your
               DOPUS5: directory. To add programs to a group just drag
               them into it. Note that some programs (DPaint4, for example),
               don't work properly when run from a group.. if this is the
               case, set the DOPUS_RUN_REAL tooltype in the program icon
               IN THE GROUP (local copies are made of the icons when they
               are added to the group). Setting this tooltype means that
               the program will refer to its original icon when reading
               tooltypes (so you will not be able to set specific
               tooltypes for the program group). This tooltype is set
               by default when you add a program to a group.
               If the OPEN tooltype is set in the icon for a group, that
               group will be opened automatically when DOpus starts up.
             - Changed position of Edit options in Settings menu
             - If you have a script file left out (or in a Program Group),
               and you double-click on it, DOpus will now execute it
               correctly if the S bit is set (if the S bit is not set it
               will be submitted to filetype testing as before).
             - If you have a program left out that is a CLI command (ie
               didn't have an icon), and you double-click on it, DOpus
               will now run it like Workbench does (as a CLI command,
               letting you enter arguments). Note that it is not possible
               to add programs without icons to Program Groups.

   20-Feb-95 - Icon viewing in listers implemented (sort of).

   21-Feb-95 - Fixed some quoting problems in conjunction with {O} or {F}.
             - Implemented the "Reload each file" flag.. no doubt this will
               break all sorts of things :( PLEASE test this and all
               of your custom functions (anything using {} sequences) to
               see if it's caused any problems.
             - Fixed DOpusRT to search the pathlist correctly for a given
               program.
             - Diskcopy now has a bit more room to show the device names.
             - Listers are now activated when you open them, and new listers
               automatically display the device list.
             - The current directory for "Execute Command" is now RAM:,
               like Workbench.
             - Delete confirmation requester now displays the number
               of files and dirs to be deleted (like Workbench).
             - Changed "Settings" to "Options" to keep Greg happy :)
             - Close gadget on the iconify window (clock) now displays
               "Do you want to quit" requester like Opus4 did.
             - Before, when you double-clicked on an icon to open a lister,
               if that icon had previous been opened (even if the lister
               now no longer showed the original path), the original
               lister would be re-used. Now, a new lister is opened,
               unless that actual path is currently visible.
             - You can now drop files onto buttons to execute the function
               on those files immediately. Note that there is no provision
               (as there was in Opus4) for running functions that require
               a destination directory this way (eg Copy), and I don't
               think there ever will be. You cannot drop onto toolbars.
             - Added "Output Window" settings to Environment configuration.

   22-Feb-95 - If you try to run a function that works only on a single
               destination (like Move), with multiple destinations locked,
               you are now given a list of current destinations from which
               you can pick the one you want to use.
             - Removed some old and now unused flags and {} sequences from the
               function editor lists.
             - If you try to rename a disk (via the Icon menu) and it
               fails you now get an error requester.

   23-Feb-95 - Beta 3 release

   24-Feb-95 - Drove 1500km
   25-Feb-95 - Drove 700km
   26-Feb-95 - Unpacked
   27-Feb-95 - Started Uni :)

   28-Feb-95 - The "View As" state of a volume or drawer (by name/by icon) is
               now saved when you snapshot the icon.
             - Icon dragging from one window to another now works properly
               (I think :) If the two windows are on the same physical device,
               the item will be moved; otherwise it will be copied. This is
               the same operation as Workbench. Also in icon view mode the
               icon of the file or directory is automatically copied (or
               moved), regardless of the "Perform actions..." setting.
             - "Remove Object" from program groups would leave a lock on the
               group directory, meaning you couldn't delete it.
             - If you had no lister toolbar selected, the lister status bar
               would have no bottom line.

    1-Mar-95 - The state of listers is now saved when you save the environment
               (source/dest/locked source/locked dest).
             - The correct "default" screen size is now shown (and used) when
               you pick default width or height in the display mode settings.
             - Fixed some strings.
             - "View Icons" option in the lister pop-up menu is no longer
               a checkmark option.
             - With some fonts the palette gadget in the User Colours section
               would overwrite the borders (this was a boopsi class problem).
             - The clock would overwrite the memory display on a 640-pixel
               wide screen in topaz 8.. with the clock it now uses a shorter
               string.

    3-Mar-95 - If you selected "New" from the toolbar editor menu and then
               "Open", the filename would be trashed.

             - Colours system changed (AGAIN! :). It is now essentially the
               same as in Opus4, in that you can set the colours for the
               "OS" pens (bottom four and under 39 top four). However the
               user colours system is still there in that you can still
               specify the number of pens to allocate for your own use.
               This hasn't been tested under 37 yet.

               There are multiple situations that need to be tested;
               please do this if possible. They are :

               OS        Screen       Screen colours     User pens
               ---------------------------------------------------
               37        Own               4               n/a
               37        Own               8              max 4
               37        Own               16+            max 8
               37        Public            4               n/a
               37        Public            8               n/a
               37        Public            16+             n/a
               39        Own               4               n/a
               39        Own               8               n/a
               39        Own               16+            max 8
               39        Public            4               n/a
               39        Public            8               n/a
               39        Public            16+            max 8

             - Added individual colour setting (in Lister display) for
               devices/volumes and assigns in devicelists (note that
               using an old environment will probably have null for
               the colour, so you will need to set this).

    4-Mar-95 - Added a path field to the "Select Destination" list that
               pops up (eg if you try to Move with multiple destinations
               selected), so you can enter a path that isn't currently
               displayed in a lister.
             - If you try to run a function (say Copy) without having
               a valid destination selected, you now get the same list
               appearing, allowing you to select (or enter) the
               destination you want.
             - Changed Icons/Snapshot menu to allow you to also snapshot
               the Window (saves window position only), and All (saves
               window position and positions of all icons within window).
               Icons/Snapshot/Icons snapshots just the selected icons
               as before.

    5-Mar-95 - The workbench.library patches have all been moved to the
               dopus5.library. This means that you will be able to quit
               DOpus irrespective of whether the patches are in use or
               not (there are also several other advantages to this).
               For the time being (at least) the WBPATCH tooltype makes
               no difference.
             - The close gadget in all configuration requesters now means
               cancel, rather than ok.

    6-Mar-95 - You can now officially not select the background colour of
               lister toolbar buttons. Also, you can not select the
               foreground colour of graphical buttons.
             - The play module will now play a sound as raw if it is
               rejected by iffparse.library (ie if it is 8svx but corrupt
               it will be played in raw mode).
             - The state of the "View as icons" setting of open listers is
               now saved in the environment.
             - Added flags to Display Options to control the display of
               AppIcons and the Tools menu.. these flags replace the
               WBPATCH tooltype.

    7-Mar-95 - U was used as a hotkey 3 times in the menu editor;
               this has been fixed.
             - Added a kludge for naughty programs that add AppIcons but
               don't put the image data in chip memory.
             - Added hotkeys for Environment and Options edit.

    8-Mar-95 - The memory monitor is now more "aesthetic"; it doesn't flash
               like it used to, and memory is now updated every second or so.
             - "Duplicate" in the menu editor now copies the name as well.
             - Fixed some problems with button bank sizing.
               Re-arranged the Add/Insert/Delete/Remove buttons.
               Added "Clear" button to clear the clipboard contents.
             - The free space display in lister title bars now uses
               thousands separators properly.

    9-Mar-95 - You can now drop files on icons in program groups.
             - Fixed (finally this time, I hope :) a bug that could
               lose files if, for instance, you tried to MOVE a file and
               it only just didn't fit in the destination.

   10-Mar-95 - Snapshot ALL now works on the main window.
             - Icon positioning is now smarter.
             - Fixed bug in Options config where if you hid the program
               and then reopened you would get two options windows.
             - Fixed bug setting colours when open on Workbench screen.
             - Removed {Ou} and {Fu} from list in config since these
               don't work any more (they never really did)
             - You can now drag and drop buttons onto the button editor window.

   11-Mar-95 - Added context-sensitive help for the main program; no help
               for configuration or modules yet.
             - You can now drop files on Opus when it is hidden (as a clock
               window or as an AppIcon, that is) to perform the doubleclick
               action on those files (like in Opus4).

   12-Mar-95 - Added "Save Layout" toggle to control whether the lister/buttons
               layout is saved when you save the environment or not.

   13-Mar-95 - Fixed some more palette stuff; in the colour selectors the
               top 4 OS pens were being shown at the bottom instead of after
               the first 4.

   14-Mar-95 - Added help to Environment and Options, more to come.

   15-Mar-95 - Fixed text not being cleared properly in the format window.
             - Extended-selection menu links are now followed correctly.
             - If you hid the program while the Environment editor was open,
               the editor would not come back when you returned to Opus.
             - You now must use '---' (without quotes) in the user and lister
               menus to get a separator bar.
             - Button windows now have a drag gadget in their left borders,
               in case they are too narrow to get to the normal drag bar.
             - DOpusRT is now called DOpusRT5.
             - The text viewer was losing the last character of a file if
               the last line did not end in a linefeed.
             - If the device list was displayed you would be unable to switch
               to the cache list (and vice versa).
             - If you (sneakily) load a textual button bank in as the lister
               toolbar, the first letter of each button will be displayed
               in said toolbar.
             - Changed "Remove" to "Xform" in button editor.

   1x-Mar-95 - The order of the top 4 OS colours in the palette editor
               were reversed.
             - Added hotkeys (1-7) for the main editors.
             - Fixed null character for text toolbars without a valid button
               name (note that text toolbars are NOT officially supported).

   19-Mar-95 - Changed the operation of the "Xform" button in the button
               editor. It now works by changing between rows/columns only
               in integer factors of the number of buttons (eg 18 buttons,
               the options are 1x18, 2x9, 3x6, 6x3, 9x2 and 18x1).
             - Fixed a bug in the clock that was causing enforcer hits.
             - Help added to remaining config windows and to modules.
             - The Print requester now has the ability to output to a file.
             - Removed the PrintDir module. The general Print requester
               now handles the bulk of the work in printing a directory.
               The PrintDir module should be removed from your Modules
               directory.

   20-Mar-95 - Print now saves its settings for next time.
             - Fixed some problems with the parsing of Key strings in
               the function editor.
             - A lock was being left on a directory if you showed it as
               icons.

   22-Mar-95 - Fixed problem with menus; if a menu operation caused the
               window to be closed and reopened (eg Backdrop), an invalid
               menu item NextSelect was being followed.
             - Implemented more (final?) ARexx commands.
             - Added command templates to most internal commands.

   25-Mar-95 - "Use defaults" from the toolbar and menu editors now looks
               for a file called xxx_default.
             - The pop-up menus now have help.
             - Implemented the display of Owners and Groups with Envoy.

   28-Mar-95 - Tidied up the library, removed some old functions no longer
               used. Did a complete recompile of everything as a result.
             - Added some more callback hooks for external modules.
             - Implemented the remaining command templates. Added RECURSE
               switch to Comment/DateStamp/Protect commands.
             - Fixed problem with the text viewer in hex mode; would show
               one line too many if window bigger than file.

   29-Mar-95 - Sped up the arrangement and reading of icons, especially when
               switching a lister into icon view mode (with lots of icons)
             - Dropping an icon in the filetype editor to set a filetype's
               icon would not be saved correctly.

   30-Mar-95 - Fixed bug that crept in that would crash if you cancelled a
               toolbar or menu edit.

   31-Mar-95 - Fixed enforcer hits with button editor. Dropping a button onto
               the button editor window now works properly (and doesn't
               crash). You can now not copy graphical buttons to textual
               banks and vice versa.
             - With a recursive filter turned on, the Delete and Move commands
               would complain a directory wasn't empty when it came to delete
               it, even though this was the desired situation. The requester
               no longer appears in this case.
             - Move would always try to rename first, which wasn't what you
               wanted if a recursive filter was set. Now, with a filter set,
               move always copies and deletes.
             - Changed internal usage of paths; before they were always expanded
               internally (c: would become dh0:c/ for example) - this caused
               problems with parnet and also with disks of the same name.
               Now paths are kept as they are supplied (ie if you enter c: it
               uses c:).

    1-Apr-95 - Added "dropfrom" custom handler rexx operation. This is the same
               as "drop" except it indicates a drop _from_ a lister rather
               than to.
             - Added "Expand paths" flag to Operation/Caching.
             - The hex viewer would output any character >7F as FF.
             - Changed the minimum size of a button bank.. before it was
               8 "character widths"; changes this to 1 character width + 32
               pixels (for fonts that have screwy widths).
             - Copied the code out of Opus 4 that does the "popup" when you
               press the hotkey (alt/shift/ctrl etc), so it now works
               like Opus 4 did.

    2-Apr-95 - Changed registration process.
             - Hopefully fixed the final problem with parnet that would cause
               it to show garbage volume names in the lister titles.
             - The 'lister remove' rexx command now works properly when you
               specify a file by number (with #xxx)
             - Fixed a problem with the command parser when you had an
               internal command and specified the name of a file. Too hard
               to explain really, just accept that I fixed something. :)
             - Added "GrabWB" button to palette editor to make it easy to
               grab the current workbench colours.

    3-Apr-95 - The "expand paths" flag was not able to be turned off.
             - You can no longer drop a device or directory icon on a
               lister in icon mode to read that directory (this is how it
               was always meant to work).

    4-Apr-95 - The paths produced by {s} and {d} in functions will now be
               enclosed in quotes (unless the No filename quote flag is
               turned on). This is smart enough to handle things like
               {d}{RsEnter archive name}
             - The string returned by "lister query selfiles" and similar
               commands was null-terminated.. it isn't any more. No idea
               why this was a bad thing, but oh well...
             - Fixed small problem in the text viewer; if you scrolled down
               a couple of lines from the top and then did a page up, the
               wrong line would be shown at the bottom of the display.

    5-Apr-95 - If a directory is reread due to the datestamp changing
               (ie when you activate the lister), any filetype descriptions in
               the lister are cached, and therefore do not need to be
               rescanned when the directory has been read.
             - There is now a little daemon that checks every 5 minutes to
               see if there are any dopus temp files in t:, and deletes them
               if so
             - An "inactive" rexx message is now sent to a custom handler
               if the lister that handler is associated with closes
               (as described in the docs)
             - Fixed some alignment problems in the lister display with
               the datestamp.
             - Fixed (I think) alignment problems with filetypes in the
               lister display.
             - Sometimes the filetype sniffer would "stop" at a certain
               file and not go any further. Again, fixed (I think).

    6-Apr-95 - The PopUp menus now scroll correctly if they're bigger than the
               screen.

   FIRST COMMERCIAL RELEASE

   10-Apr-95 - The string returned by "lister query selfiles" is now the
               correct length.
             - Mouse position was not being checked for a double-click to
               edit a button.

   12-Apr-95 - Fixed some problems with multiple-line functions. Too hard to
               explain, but as an example, a command like

                     AmigaDOS   makedir ram:temp
                     AmigaDOS   copy {f} ram:temp

               would fail. Now works.

             - Fixed problem with filename quoting in commands. For example,
               if you had {f}.old, this could come out as :

                     "ram:testfile".old

               It now correctly comes up as :

                     "ram:testfile.old"

             - Added new feature to the {f} and {o} sequences. If you specify a
               minus sign (-) after the letter, the filename will be stripped of
               any suffix. As an example,

                     AmigaDOS   rename {fu} {f-}.lzx

               would replace any suffix the selected file had with a .lzx suffix
               (eg   rename "ram:test.lha" "ram:test.lzx")

               This and the above changes makes possible the following
               (extremely tricky) function to convert LHA files to LZX
               automatically:

                     AmigaDOS   makedir t:lzxtemp
                     AmigaDOS   lha -x -M x {fu} t:lzxtemp/
                     AmigaDOS   cd t:lzxtemp
                     AmigaDOS   lzx -e -x -r a {fu-}.lzx #?
                     AmigaDOS   delete {f} quiet force
                     AmigaDOS   cd ram:
                     AmigaDOS   delete t:lzxtemp all quiet force

             - The "inactive" message when a lister is closed was sent prematurely,
               so that under some circumstances (high cpu load for instance), a
               "lister query" would indicate that the lister was still present even
               though it had been destroyed. Also, an "inactive" message was not
               being sent if the lister was empty when it was closed.

   13-Apr-95 - The "lister query selfiles" and similar commands can now return
               information in STEM variables. For example,

                     lister query handle selfiles stem files.

               Without the stem keyword, the names are returned in RESULT as before.
               The names are returned in slots from 0 to COUNT-1, and stem.COUNT gives
               the number of names.

   14-Apr-95 - The "Select Destination" requester would leave the lister list locked
               while it was open, meaning you wouldn't be able to open any new listers
               until the requester had been closed.

             - The "lister query all", "lister query source" and "lister query dest"
               commands now accept a STEM parameter. For example,

                     lister query all stem listers.

             - The "lister query entry" command now accepts a STEM parameter.
               For example,

                     lister query handle entry #0 stem fileinfo.

               The fields returned are:

                     NAME       - file name
                     SIZE       - file size
                     TYPE       - type (<0 = file, >0 = dir)
                     SELECTED   - 0 or 1
                     DATE       - seconds since 1/1/78
                     PROTECT    - protection bits (long value)
                     DATESTRING - datestamp in ascii form
                     PROTSTRING - protection bits in ascii form
                     COMMENT    - file comment (if any)
                     FILETYPE   - file type (if any)

   15-Apr-95 - The device list now shows the paths of any multiple-directory
               assignments in the system.
             - The "Selection Destination" requester is now an AppWindow.

   16-Apr-95 - There previously was no way to get the return value from a
               dopus getstring rexx command (ie which button was selected).
               This is due to the way rexx return values are specified
               (you can have either RESULT or RC, but not both, for some
               strange reason). The button value from this command is now
               returned in a variable called DOPUSRC. RC will always be
               0 from this command, and RESULT will contain the string
               entered unless cancel was selected, or no string was entered.
               The new DOPUSRC variable may be used by other commands in
               the future.

   23-Apr-95 - Projects with a default tool that included a relative path
               (eg "bin/installer") would not work.

   29-Apr-95 - If you deleted the right or middle button functions from a
               button the dog-ear imagery would not be erased correctly.
             - The "inactive" and "active" messages now always contain the
               path of the lister in Arg4; Arg2 will also contain the path
               unless a title has been set in which case it will contain
               the title.

   30-Apr-95 - Non-DOS disk icons are now shown (like in Workbench); a new
               option (Environment/Display Options/Hide bad disks) allows
               you to hide these icons again.
             - If you dropped a button or another menu item into one of the
               menu editors, the menu list display wasn't updated correctly
               (you could end up with two highlight bars).
             - When doing WBStartup, Opus would ignore any programs that
               were only icons (ie default tools).
             - Hotkeys using lcommand (lamiga) would not work from lister
               windows in file mode.
             - New listers opened with the scandir command or via hotkeys
               from the path formats configuration would always open at 0,0
               instead of under the mouse pointer.
             - You can now drag and drop within function editors; either to
               swap function lines around within the one editor or to copy
               function lines to another editor. If you hold down shift
               while you drag a function line from one editor to another,
               the entire function will be copied.

    1-May-95 - Added "Skip All" button to copy function; if a file exists
      #1001    you now get the option to skip all, meaning ALL files that
               already exist will be skipped.
             - You can now change item positions within the menu editors
               using drag and drop (instead of with the Move Up/Down buttons)

    2-May-95 - When DOpus runs WBStartup programs it now respects the
      #1003    STARTPRI and WAIT tooltypes (but not DONOTWAIT).
             - The way "Workbench" processes are launched has changed.
               All programs are now launched by the one process which is
               established by the library. This means that there is not
               a copy of dopusrt5 sitting around for each workbench process
               you have run.
             - Path inheritance should work properly when DOpus is run as
               a Workbench replacement (ie via LoadDB)

    3-May-95 - Fixed more path inheritance problems
      #1004  - You can now drop files on program group icons to add them to
               the group

    4-May-95 - "Replace All" in copy was broken, fixed.

    5-May-95 - Fixed problem with AppIcons; if their initial position was
      #1006    off-screen, DOpus would not update sliders properly.
             - DOpus now grabs a pathlist when it starts up, and uses
               that for all program launching.
             - If you had 12 hour clock turned on it was possible for the
               "file already exists" requester to overwrite a buffer.
             - Fixed sorting problems in the device list (multi-path
               assignments could be shown in the wrong place).
               The device list now shows the full path to all assigns.
             - Added "Lister Options" to Environment configuration.
               You can now turn the device list off in new listers,
               and can set the default size of new listers.
             - There was a problem using {s} in filetype functions.
             - Inserting {} sequences in a function string via the popup list
               in the function editor now inserts with spaces as necessary.
             - Filetype saving and refreshing method modified.

    6-May-95 - Bug on 68000 machines could cause address errors on functions
      #1007    with odd-length parameters (eg Confirm NOTEVEN)

    7-May-95 - Added "RMB double-click editing" flag to Environment/Lister Options.
      #1008  - Added FULL switch to DeviceList command (ie DeviceList FULL/S).
               If not specified, the device list will be in the old format
               (unexpanded assigns). If FULL is specified, assigns will be
               expanded and multi-directory assigns will be listed.

    8-May-95 - Will no longer open non-existant drawers in icon mode.
      #1009  - Fixed problem with SysIHack and the text viewer.
             - Cursor keys on the listview gadgets in Environment, Options
               and other places work again.
             - If you tried to replace an existing file (via Copy) and the
               existing file could not be deleted successfully, an error
               requester is now shown (before it would fail silently).
             - Added popup menu to button window (right mouse button over
               button window title bar), with Iconify feature.

   10-May-95 - Fixed some problems with the print module (blank pages, etc)
             - Text viewer now filters out CRs

   12-May-95 - The path field is no longer cleared if you enter an invalid
    5.1/43.1   directory to read in a lister.
             - Inverted the sense of the new lister options flags (so they'll
               be on by default in an old configuration)
             - Soundtracker module playing back in (inovamusic.library)
             - BEEP command is back in.

   13-May-95 - Can now leave out icons without associated files (eg Shell)

   14-May-95 - Pressing tab on path field in Path Formats config now moves
               to Key field properly. Key field is cleared correctly when
               you Add a new path format.
             - Help node names in config (Options and Environment) are
               now hardcoded (instead of from catalog).
             - Fixed "workbench" launcher so it now multitasks better
               (eg before when you double-clicked on an icon DOpus would be
               busy until the new program was running; it now returns
               instantly).

   15-May-95 - Modified IFF viewer, should show in proper screen modes
               more often.
             - Fixed so you can now delete, copy, etc. directories with
               wildcard characters in the name.

   16-May-95 - Fixed drag and drop problems, yaaaaaaaaaaaay!
             - Changed default arexx path in function editor to DOpus5:ARexx
             - {} button in function editor is disabled for Commands
             - Bug could cause a crash in the function editor when moving
               function lines around via drag and drop.
             - Dragging a command line from one function editor to another
               could lose the function type (AmigaDOS could become Command,
               for example)
             - Added SaveAs and Edit to the popup button bank menu.

   17-May-95 - Fixed IFF viewer for datatypes (back to how it was)
             - Added "Default PubScreen" menu item in Settings

   19-May-95 - If you specified a default string for {Rs} and used the
               sequence twice in the one function, the second requester
               would have garbage in it (buffer not being null-terminated)
             - Running WBStartup programs would show program name in
               double-quotes ('"name"')
             - Opus was not able to launch programs from listers in file mode
               or from wbstartup if the program had a space in the filename.

   22-May-95 - Fixed some drag and drop lockups (hopefully)
      #1012  - If an icon had an image that was larger than the icon itself,
               it could trash memory when you dragged it around the screen.
             - Changed LockDosList() to AttemptLockDosList() when Opus updates
               the main icon display (every 10 seconds or so), to see if this
               stops the occasional "freezes" that have been reported.
             - If you had a file (say FOO) and the file's icon was in a
               different case (eg foo.info), if you put the lister into
               icon mode and selected Show All, you would see two icons
               (the file's original icon and a dummy icon).
             - More path problems fixed; theoretically, all programs launched
               from Opus now should have the correct path. Also, local
               environment variables are now preserved properly. Note that
               ALL program launch (wbstartup, lister, lister in icon mode,
               functions, etc) has changed, and probably should be tested.

   23-May-95 - Requesters opened with the "dopus request" and "dopus getstring"
               rexx commands were not centered in the display clip properly.
             - If you had an icon defined for a filetype, and left a file of
               that type out on the main window, there could be problems
               opening that file when double-clicked on.

   24-May-95 - Fixed a couple of problems in the icon routines to do with
               list arbitration.

   25-May-95 - The icons for iconified listers and button banks now show up
      #1014    even if you have the display of AppIcons turned off.
             - The keyboard selection arrow is now erased properly when
               using a small font in the lister (<8 points).
             - Added key command to Remove program from group.
             - ClearSizes now updates the byte count in the lister
               correctly.

   26-May-95 - Lister/Snapshot and Icon/Snapshot/Window now snapshot the
      #1015    text/icon state of the lister properly.
             - Possibly fixed a problem that some people complained of,
               that meant listers they saved did not come up in the
               correct position (even with Save Layout turned on).
             - There was a problem with the menu and toolbar button
               editors when you did a SaveAs to a root directory
               (path ending in a colon).
             - Added error message when Opus is unable to launch a
               program (in icon mode, either default tool is not present
               or another error).
             - Leo's bug (mixing User1 and AmigaDOS functions causing a crash)
               seems to be fixed.
             - Leo's bug (swapping lines around in the function editor
               causing a crash) seems to be fixed.

   27-May-95 - Increased stack size on palette box to hopefully prevent
               crashes under CyberGfx.
             - Added "No Border" option to graphic buttons.

   28-May-95 - The filename sent in a "drop" or a "dropfrom" custom handler
      #1016    message no longer has an erroneous trailing space.
             - If you drag files from a lister with a custom handler, and
               drop them on another lister with a custom handler, you used
               to only receive a "dropfrom" from the first lister. You now
               receive both a "dropfrom" from the first lister, and a "drop"
               message from the second.
             - "dropfrom" now contains the source lister handle in Arg1 and
               the destination lister handle (if any) in Arg2.
             - An "inactive" message is now sent correctly when device or
               cache list is displayed in a lister with a custom handler.
             - The border parent gadget (and parent from the lister popup)
               now check caches correctly for parent directories.
             - Added error checking to several save configuration options
               that were lacking it
             - The search string is now carried over into the text viewer,
               when using the Search command.
             - Added a couple more key equivalents to the text viewer to
               make it more like Opus4 (t=top,b=bottom,q=quit,p=print,
               s=search,n=next search).
             - The "Select Destination" requester should now appear for
               external functions as necessary (this really should be
               tested lots)

    1-Jun-95 - Removed IsRexxMsg() check
      #1017  - If you deiconified two or more listers simultaneously using
               Icons/Open, it would often crash.
             - Added IsRexxMsg() check to "dopus request", etc, to stop
               enforcer hits if message wasn't from arexx
             - Messages sent to custom handlers had an argument count that
               was one too many (I was counting Arg0).

    2-Jun-95 - Alt-click on the toolbar in the blank area to the right of
               the actual buttons would open the editor unnecessarily (and
               incorrectly).
             - Copying a directory to a write protected disk would give the
               wrong error message
             - Copying a directory to a non-present disk would give the
               wrong error message

    3-Jun-95 - Alt-click on a button when the button bank editor was already
               open could open an editor for the wrong button (if you
               had scrolled the button bank)
             - With multiple button banks being edited, clicking Save on the
               bank editor would not save banks correctly (or at all)

    5-Jun-95 - Now only the Help key activates help (ie shift help, etc, will
      #1018    not do it).
             - The "lister clear" command no longer clears your custom handler
               name. The "lister empty" command still does, but you are now sent
               an "inactive" message correctly.
             - Dropping a directory to a lister with a custom handler would
               cause a mungwall hit (overwrite buffer).

    6-Jun-95 - Added kludge for ToolManger to prevent poor system performance when
      #1019    it updates its tool menu (the problem will still exist for anything
               else that adds lots of items to the tools menu at once).
             - Will no longer try to show palette files (or any ILBM with a
               tiny BODY consisting of zeroes) - this used to crash.
             - Fixed problem where iconified lister icons could be "relocated" but
               the display not updated correctly

    7-Jun-95 - Fixed problem in device list update (FreeVec used inappropriately)
      #1020  - Made some changes to lister icon routines; now, if you drag and drop
               an icon between two listers that are BOTH in icon mode, the copy/move
               that is performed is much more Workbench-like. More needs to be done
               on this.

    9-Jun-95 - Fixed long-standing problem that caused the checkmarked menu items
               (like Clock, etc) to come up as off initially even when they were
               really on.
             - Did some more work on drag-and-drop copying in icon mode.. icons now
               stay where you drop them (instead of keeping their old positions).
               You can also drop icons onto drawer icons to copy into that drawer.
               Still more to be done on this...

   10-Jun-95 - If you try to copy incompatible disks by dropping an icon onto
               another, the diskcopy window doesn't even try to open (you get
               the requester straight away)

   11-Jun-95 - Fixed problem deleting directories with ^ in the name
             - More work done on drag and drop copying in icon mode. You can
               now drop icons onto directory icons within the same window to
               move those files into a sub-directory. You can also drop
               device icons to copy the contents of the device.
               Still more to do on this.... :)

   12-Jun-95 - Added {Ql} sequence to get the source lister handle (for rexx)
             - Opus would crash if you tried to open a requester (dopus request
               command) with more than 1024 bytes of text in it.
             - 'Output results' in the Search function was broken.

   13-Jun-95 - Copying from CrossDos disks using the text filter/text translation
               now works fine.
             - Added "parent" and "root" custom handler messages (at the moment
               only sent when you use the side parent bar or press / or :)

   14-Jun-95 - Drag & drop didn't use to work if the path in the source lister
               didn't actually exist. This could cause problems for custom
               handlers (like FTP and LHA) that display "fake" directories in
               listers. This is now fixed.
             - Added 'dopus addtrap' and 'dopus remtrap' rexx commands.

   15-Jun-95 - Changed the {Ql} sequence so it implies the need for a source
               directory (ie it now works like you'd expect it to)
             - Fixed the janitor so that it won't (shouldn't) delete any
               temporary files that haven't actually been used yet.

   19-Jun-95 - If you specify the "quotes" flag after a "lister set custhandler"
               command, then any filenames sent to the handler as the result of
               a drop, dropfrom, trapped function, etc, will be enclosed in
               quotes.
             - A new action, "path", is sent if the user presses return on the
               path field of a lister with a custom handler active.
             - Messages sent as the result of a trapped function (eg Copy)
               will contain the argument portion of the function string as
               argument 5.
             - Trapped functions are now used when it is the destination of
               an operation that has a custom handler, as well as the source.
             - Fixed problem that would cause ` character to appear in the key
               field of path formats.

   20-Jun-95 - Even if the clock was turned off, the screen title bar would
      5.11     still be completely cleared each second, causing problems for
               third-party clock programs.


                                     ----


    8-Jul-95 - When you drag the highlight box around some icons, they are
               selected in real time (a la Mac/Win95)

   16-Jul-95 - Added configurable status bar text to Environment/Lister Display

   17-Jul-95 - Added three new call-backs for external modules (EXTCMD_GET_PORT,
               EXTCMD_GET_SCREEN,EXTCMD_REPLACE_REQ)
             - DOpus now notices when IPrefs tries to reset the Workbench
               screen (when it is open on the Workbench screen),
               and will shutdown all of its windows to allow this to happen
               (eg when you change ScreenMode or Font prefs).
               This should also work when any program calls CloseWorkBench(),
               although depending on the number of windows it has to close,
               the screen itself might not get closed. The IPrefs reset should
               always work though.

   18-Jul-95 - Added clipboard support to text viewer (drag to highlight,
      #1102    ramiga-c to copy to clipboard)
             - Added "Trap 'More' in default tool" option to Options/Icons
               (subtitutes Opus viewer whenever More is set as a default tool)

             - DOpus now saves window sizes and settings (eg when you
               SnapShot a lister) individually from Workbench. The information
               is kept in a file (currently dopus5:position-info, though this
               will probably change) and is completely separate from any
               Workbench position information.

               You can save sizes individually for file and icon mode.
               Swapping a window between file and icon mode will resize
               the window appropriately.

               The current path format is also stored in this file.
               The storing of path formats in this manner is somewhat
               incongruous with the Path Format configuration section.
               I think currently that any paths you have defined in
               Path Format will override the formats stored in this file.
               Conceivably though, this file could quite easily replace
               the entire Path Format section (the only thing that isn't
               duplicated currently is the optional hotkey for the path).

   ******      This whole area needs to be tested thoroughly for any
               problems (I have only done minimal testing so far).

   21-Jul-95 - Optimised refreshing of listers and the progress indicator
             - Added "reread" arexx message for custom handlers (when
               ReRead Directory is selected from the popup menu)
             - Added "abort" trap (dopus addtrap abort)
             - Added "port <name>" option for the "dopus addtrap" command
               This allows you to specify a different port for the
               message to be sent to (the default is the main lister
               custom handler). This is mainly designed to allow an
               "abort" function running as a separate process. The message
               that is sent is a standard DOpus rexx message.
               For example, "dopus addtrap abort port 'my_abort_port'".
             - Files or directories called "disk" are now shown
               when in icon mode

   22-Jul-95 - Rewrote the backdrop pattern routines. The display of
      #1103    pictures as a backdrop should be much faster on graphics
               boards now (the original bitmap is copied to a "friendly"
               one - should prevent lots of p2c conversions).
               You can now have patterns in listers (when in icon mode).

   26-Jul-95 - Occasionally when a lister refreshed itself (because of
               a datestamp change) automatically, the lister would
               lock up. This problem could date back to day one.
               Hopefully it is now fixed.
             - If you tried to Show or Play a single file using a button
               (rather than by doubleclick), the file would be
               deselected but the display would not be refreshed.

   29-Jul-95 - Redesigned the button bank editor. Added "Bank border" flag
               (not actually implemented yet).
               Clipboard is now shown in a separate window.

   30-Jul-95 - Changed the storage format of button banks (more flexible now).
   ******      Doesn't seem to have caused any problems, but this could
               potentially affect the use of any buttons, menus, toolbars,
               etc. Please just check that this all works as it should.

             - Sped up device list generation slightly (still a bit slow).
               Added new BRIEF keyword for the DeviceList command (does
               volume/device list only, no assigns).

   31-Jul-95 - Took the date checking out of the register module (so
      #1106    you won't need to reregister after a ReOrg, etc).

    1-Aug-95 - Format and Diskcopy no longer steal the focus from you when
               they finish.

    3-Aug-95 - Similar to the bug fixed on 26-Jul, there was a problem
               with listers in icon mode when they were activated and they
               decided to refresh. This has now been fixed.
             - Fixed a bug in the "lister copy" rexx function that would lose
               protection bits in both the source and destination listers. I'm
               pretty sure this isn't the same as the main "loses protection
               bits" bug, so that's probably still out there...

    4-Aug-95 - Leo reported a bug ages ago about User2 and an LHA function
               (check the guide for details). This was actually ANY filetype
               function (User, DoubleClick, etc) that caused a "Select
               Destination" requester to come up. The lister you selected was
               being locked but never unlocked afterwards. Now fixed.
             - Added "Simple-Refresh Window" option to Environment/Lister Options.
               While I far prefer simple-refresh windows (they use much less memory
               and are much quicker to move and resize), people with slower Amigas
               might prefer the faster refreshing of smart-refresh windows.
             - Wrote my own IFF writing routines (used when saving configuration
               etc) that should be a lot faster (and simpler) than iffparse.
               Also more reliable, I hope - this should fix the problems
               some people have been happening with 500k button banks and
               filetypes crashing when you save them.

    6-Aug-95 - Fixed a bug in the IconInfo module; if you had a tooltype selected
               for editing and closed the requester (Save, etc), it would crash.

    8-Aug-95 - Key equivalents for buttons and menus can now use the full range
      #1107    of qualifiers (ie lalt, ralt, lshift, rshift, control, lcommand,
               rcommand) as well as shift (any shift) and alt (any alt). It
               also supports the commodities sequences like "-lshift", meaning
               ignore the left shift key, etc. NYI for path formats.
             - added trap for "quit" (dopus addtrap quit)

    9-Aug-95 - Added "lister iconify" rexx command. To iconify a lister, use the
               command "lister iconify <handle>". To deiconify, use
               "lister iconify <handle> off".
             - Added "all" as a substitute for the lister handle for a few commands.
               You can now do "lister close all" to close all listers,
               "lister iconify all" to iconify all listers and
               "lister refresh all" to refresh all listers.
             - Added "dopus version" command to get the current version number.

   10-Aug-95 - Button banks are now simple refresh. Sped up the rendering and
               refreshing of buttons (especially image buttons). Removed the
               64x64 limit on image buttons.

   13-Aug-95 - Added new "Window Appearance" section to the button bank configuration.
   ******      This allows you to select a borderless window (a la ToolManger),
               the orientation of the drag bar (when using a borderless window, again
               a la ToolManger), and borderless buttons (funnily enough, also
               a la ToolManger). Hmmm.

               If a button window is borderless, it will have a small drag bar on either
               the left or top of the window. This drag bar can also be used to bring
               the window to front, by double-clicking on it. If you want to access
               the button menu, you must have the pointer over this dragbar when
               you press the right mouse button.

               Borderless windows are automatically sized to the necessary size to
               display the largest image (or text). If the window can not fit on the screen,
               it will be shrunk down and any buttons not visible are NOT ACCESSIBLE.
               Currently there is no way to access buttons that are hidden during this
               process. I don't think this is a big problem though.

               The toolbar orientation can be either Automatic (where it is dependant
               on the size of the window), Horizontal or Vertical. Nothing too tricky
               here.

               The ill-conceived "Button border" option in the button editor has been
               removed and replaced with a flag that is global for the whole bank.
               When turned on, the three-dimensional borders will not be drawn
               for the buttons in the bank. This means that if you want borders, the
               images you supply must have the border in them. Text buttons in this
               mode can not have borders at all (obviously).

               Button banks now support alternate select images for graphical buttons.
               That is, if you are using an icon for a button image, the "selected imagery"
               the icon will be shown when you click on the button. For IFF images, you can
               supply an AnimBrush, the second frame of which will be used for the
               selected imagery.

               If you have button borders turned off, and no alternate imagery (either
               a graphical button with no second image or a text button), the button
               will be complement rectfilled when you select it, just to provide some
               visual feedback.

               The "Window Appearance" editor also allows you to select simple or smart
               refresh windows (to be consistent with listers). This is selectable on
               a bank-by-bank basis, rather than globally, as some buttons banks may
               work better as simple refresh, and some as smart (eg, you might want
               a graphical button bank to be smart refresh but a text button bank to
               be simple). Personally, I use simple refresh all the time.

             - If you dragged a button using the right or middle mouse button, the
               "dog-ear" corners of the button would be lost. This is now fixed.

   16-Aug-95 - Removed "Path Format" section from Options configuration (it never
      #1108    really belonged there). The new Paths editor is now accessed from its
               own entry in the Settings menu. The editor works much the same way as
               the old one did. The paths you configure are now stored in the
               dopus5:position-info file along with any snapshotted listers, etc.
               This new editor comes in its own module (pathformat.module).

   17-Aug-95 - If the image specified for a button is not found, a default image
               is used.

   18-Aug-95 - If ALL the images for the lister toolbar could not be found, it would
               cause a crash.. this is now fixed.

   23-Aug-95 - Some interim bugs have been fixed over the past few days. These include
      #1109    - old & new file information swapped around in replace requester
               - borderless buttons were crashing under v37
               - image button with coloured background displayed incorrectly
               - image buttons were adopting the wrong size
               - if you tried to drag a button that was flashing it would drop off the mouse
               - simplerefresh buttons were not being refreshed properly if they were
                 covered by the SaveAs file requester
               - default image (for missing images) made a lot smaller and simpler

   24-Aug-95 - The in-built lister hotkeys (eg : for root, / for parent, etc) are now
      #1110    based on the current keymap rather than the rawkey code (for European
               keyboards).
             - User-defined keys will now override the in-built lister keys (eg you
               can now define 'delete' for the delete function, and this will override
               the default function which brings up the list format requester).
             - The button flashing when a button is selected has been slowed down. Also
               the flashing now works with simplerefresh windows properly.
             - The LoadEnvironment and LoadSettings commands didn't check the
               correct default directories when given a file with no pathname to load.
               LoadEnvironment would not open all button banks and listers
               associated with the environment correctly.

             - If a file called "nopools" is present in dopus5:libs when the
               dopus5.library is loaded, memory pools will not be used. This is for
               testing purposes only.

      #1111  - To test a theory DOpus now uses three separate memory pools where it
               used to use just one (for the main window icons, for groups and for
               the path format editor). Quite by concidence these are three areas
               that have all exhibited strange problems and/or crashes. Lets see if
               this fixes it...

   25-Aug-95 - Rubber-band icon selecting is now limited to the window rather than
               the screen.
             - Fixed long-standing bug in the lister format editor where if you
               dragged things in the selected list around you would wind up with
               checkmarks all over the place.

   28-Aug-95 - Added a locale catalog to the library.. only a few strings in it at
               the moment but it won't hurt for completeness.
             - Added an error requester when you try to launch a program by
               double-clicking an icon and it can't find the program.
             - Removed the code for the BEEP function from the main program and put
               it in a new module (misc.module) along with new FLASH and ALARM
               commands.

   29-Aug-95 - The Button Editor has been completely redesigned. The layout is
      #1112    now a lot clearer, and drag and drop has been added to facilitate
               the creation of buttons.

               The usage of the editor is fairly self explanatory; select the
               function (Left, Right or Middle) you wish to edit from the
               list. Functions now have both a Name and a Label. The Label is
               the text that is actually displayed in the button (or the name
               of an image file in the case of Image buttons). The Name field
               is not actually used for much at the moment, but may be in the
               future. It defaults to being the same as the Label.

               The button colours are selected from the Button Editor now instead of
               from a separate requester.

               You can drag from two places in the button editor; from the list
               of functions (Left, Right, Middle) or from the display of the 
               button in the bottom-right corner.

               Using drag & drop you can swap the three functions around (eg
               swap Left and Right). There was previously no way to do this.
               You can also drag an individual function from one button and
               copy it to another (eg copy the Left button function of one
               button to the Middle button function of another) by dropping it
               in the appropriate place.

               If you drag from the button display in the bottom right corner you
               are actually dragging the whole button. You can drop this in the
               clipboard, on another button editor, on a button bank, etc.

               If you drop a button onto this button display area it will replace
               the entire button contents.

               I've tried to implement as many drag & drop combinations as I could
               think of, but if anyone comes up with some others please let me know..
               we might as well try to make it as complete as possible.

             - Opening a path by hotkey (ie one configured in the Path Formats
               section) now always opens a new lister (before it would only open
               a new lister if there was no current source).

   30-Aug-95 - Added an iconify gadget to listers, buttons and the main window.

   31-Aug-95 - Added "Open new lister" flag to path formats; if this is set for a
      #1113    path, a new lister will be opened every time when the hotkey is
               pressed. Otherwise the path will read into the active source
               (unless there is no active source).

             - Changed operation of the path format requester to be more like the
               old system (you can edit entries, add entries for paths that don't
               exist, etc..)

             - The wrong filename was being shown in the "File exists - replace?"
               requester.

             - Images in the toolbar editor weren't being drawn correctly (the
               background wasn't being cleared, so you could have images
               drawn on top of others).

      #1114  - Module functions are now passed any user-supplied arguments in a0
               (char *).

             - Double-clicking on an environment file would result in a dead-lock

             - If you dragged a line in the function editor or menu editor the
               colour could be wrong (would show up in the background colour rather
               than the selected colour).

             - The button clipboard can now be opened and closed at the user's
               discretion.

             - You can now copy graphical buttons to text button banks, and vice
               versa.

    1-Sep-95 - DOpus requesters were treating underscore characters as if they
      #1115    were in button labels (rendering the underscore underneath the
               following letter) - eg, "File exists - replace?" requester with
               a filename that had an underscore character in it.

             - Added EXTCMD_REMOVE_ENTRY, EXTCMD_GET_SCREENDATA and
               EXTCMD_FREE_SCREENDATA callback functions.

    2-Sep-95 - If you iconified a button bank you were editing, and then cancelled
               the button bank editor, it would crash.

             - The Path Formats requester is now an AppWindow. There were some
               bugs in the editing of path formats that could cause some corrupted
               memory lists - now fixed.

             - Fixed a longstanding bug with the listview class (it arose if
               something set both the selection and the top of the list at
               once, and the effect was that you would get multiple lines
               selected and the incorrect things displayed).

    3-Sep-95 - If you selected a scroller arrow in a button bank and moved off the
               arrow and released the mouse button, the buttons would keep scrolling.

             - Selecting Disk Information from a lister would cause a couple
               of enforcer hits.

             - Changed the ScanDir command so that it can work on selected
               directories. That is, if you call ScanDir with no arguments, and
               have a directory selected in the source lister, it is the
               selected directory that will be read. Also, in this case, if
               you have a destination lister selected the directory will be
               read into that.

             - Added a new filetype matching command - Directory. This
               allows you to match a directory. It can work in conjunction with
               the Match Name, Match Comment, etc commands (but not Match Size,
               Match FORM, etc, for obvious reasons) or by itself. For example,
               you could set up a Directory filetype with ScanDir set as the
               Drag'n'Drop action. Then, when you dragged a directory and
               dropped it on another lister, it would be read rather than
               copied, which is the default action.

    4-Sep-95 - Added a new internal command - Set. This allows you to set
      #1116    certain things regarding the current lister or the operation
               of the current function :

                 Set Output <handle>   - allows you to change the output handle
                                         for the lifetime of this function
                 Set Sort <method>     - change the sort method for the current
                                         source lister
                 Set Display <items>   - change the display items
                 Set Separate <method> - change the file/directory separation
                 Set Hide <pattern>    - change the hide pattern
                 Set Show <pattern>    - change the show pattern
                 Set Flags <flags>     - set various flags (reverse, noicons, hidden)

             - Implemented global hotkeys (similar to the old Opus 4 system).
               Hotkeys are just buttons like everything else, and are configured
               using the standard menu editor. Unlike Opus 4, you can have any sort
               of function attached to a hotkey.

             - Listers can now have individual toolbars. This is only possible
               from ARexx with the "lister new" command - any other listers will
               use the shared global toolbar.

               You can only specify a toolbar when the lister is opened. The
               format, "lister new [toolbar <file>] [<path>]". For example,
               lister new toolbar lha_toolbar.

    5-Sep-95 - Right or Middle button functions in button banks stopped working
      #1117    briefly, all is ok now.

             - 'lister set <handle> progress' can now take -2 as a count.
               -1 opens with no bar graph or filename as before; -2 will open
               with no bar graph but with space for a filename.

             - The current lister format is no longer stored when you snapshot
               a lister. Only the lister position and mode (icon/text) is
               stored. To permanently set a path format you must use the
               Path Formats editor. This is consistent with the behaviour of
               Opus 5.11.

             - Added an additional Set command - Set ToolBar. This allows you
               to change a lister's toolbar on the fly.

             - Added "toolbar" to the "lister set" and "lister query" rexx
               commands. "lister set <handle> toolbar <name>" allows you to
               change a lister's toolbar on the fly.
               "lister query <handle> toolbar" will return the name of the
               current toolbar in RESULT, or RC=10 if the lister has no
               toolbar.

    6-Sep-95 - In filetypes, "MatchSize >" was not working.
      #1118
             - The state of the global "View As" setting is now respected.
               If you double-click on an icon to open a directory, and that
               directory has not previously been opened, its state will
               default to whatever is set in "View As" (in Opus 5.11 it
               would always open in text mode, and in earlier 5.2 betas it
               would always open in icon mode).

             - "lister query selfiles" and similar rexx commands now clear
               the RESULT variable correctly if there are no files to return.
               Also, "stem" rexx commands now initialise the COUNT field
               to zero correctly if there are no entries.

             - "lister new 0/0/w/h" now opens the lister at 0,0 correctly.
               You can specify -1/-1 to have the lister open under the pointer.

             - The hotkeys editor is now bigger and shows the actual key
               in question as well as the name. Also several strings
               pertaining to "menus" now say "hotkeys" as you would expect.

             - If, in the course of using the program, you used up all
               your directory buffers (as configured in Options/Caching),
               and you had also been using OpusFTP (or presumably LHADir),
               there was the possibility that old buffers from FTP would
               get "mixed up" with normal directories.

             - The function editor now checks the hotkey you give it for
               validity, and will complain about an invalid string.

    7-Sep-95 - "lister new" with no arguments was defaulting to opening at
               0,0 instead of under the mouse.

    8-Sep-95 - Output windows weren't waiting for the close gadget to be
               clicked with "Window close button" selected

   10-Sep-95 - If you had the button editor open, and were editing the
               function of a button, and you clicked Use on the button bank
               editor, the screen would flash... now it doesn't :)

   11-Sep-95 - Shift-Return is now a synonym for shift-tab (ie it activates
      #1120    the previous string gadget, if any). Return by itself will
               now activate the next string gadget, if any, except in
               certain requesters.

             - All string gadgets now support clipboard copy and paste
               (ramiga-c and ramiga-v). A few other editing commands
               have been added : control-x to clear, control-u and control-q
               to undo, shift left/right to move a page left/right,
               alt left/right to jump to the previous/next word,
               control left/right to move to the beginning or end.

             - The "Execute command" requester now has a history of
               commands you have entered (cursor up/down to move through it)

   13-Sep-95 - There was a horrible bug that as far as I can tell has always
      #1121    been present, although its effects were made far more visible
               by recent changes. You could produce it by typing the following
               in a shell :

                 rx 'address DOPUS.1 command doubleclick "s:user-startup"'

               Executing that command several times in a row almost always
               produced a crash. However, it could potentially have occurred
               whenever a rexx command "command" was sent (as well as in
               several other situations).

   15-Sep-95 - There was a one pixel gap underneath the "fill" in the
               progress indicator

   17-Sep-95 - Fixed one potential deadlock situation (I think).. more testing
      #1122    needed

   18-Sep-95 - The iconify gadget now doesn't refresh all the time, and is
      #1123    properly part of the window title bar.

             - Pressing escape when showing pictures now aborts completely

             - The text viewer is now an AppWindow, so you can drop files
               on the viewer window to read them.

             - The text viewer now has a Save option (Save As actually) to
               allow you to save the currently viewed file out to disk.
               This is really only useful in the case of temporary files
               (from Opus) that are deleted normally when the text viewer
               closes.

             - Functions from 5.11 that had ALT something as the hotkey
               were not converted correctly (it would come up as LALT + RALT
               rather than just ALT).

             - Hotkeys are now, by default, local to Opus (ie they are only
               activated if an Opus window is active when the key is pressed).
               You can choose to make each hotkey function global to the system,
               in which case they are accessable no matter what window is active.

   19-Sep-95 - The text viewer now has an option to send the currently viewed
      #1124    file to a text editor. To configure the editor you want to use,
               select Pick Editor... from the Settings menu.

             - The text viewer now recognises $9b as a valid synonym for ESC [.

             - If you clicked on an icon in some strange way using both mouse
               buttons (why you would want to do this is a bit of a mystery),
               it could occasionally cause a lock-up.

             - The function editor now has a pull-down menu. You can
               Copy, Cut and Paste functions from one function editor to
               another without having to drag and drop or go via the
               button clipboard. There is also an option in this menu
               to export the current function as ASCII text, for
               email, magazines, etc..

             - Added new set option (internal command and arexx) :

                 Set Mode [name | icon [showall]]
                 lister set <handle> mode [name | icon [showall]]
                 lister query <handle> mode

             - The "lister clear" rexx command was clearing the custom
               title of the lister, which was incorrect.

      #1125  - The filetype editor no longer allows you to select an IFF
               picture as a filetype's icon (it didn't actually work anyway)

             - The description for "And" in the file type definition editor
               needed an apiarist.

             - FindFile now uses the progress indicator to show how many
               directories have been searched and the name of the current
               directory

             - If you had filetypes displayed in a lister, and edited
               the definition of one of those filetypes, the description
               in the lister would show garbage (freed memory). The description
               is now copied rather than just referenced by pointer.

             - The "Window on Workbench" flag was broken temporarily

             - Listers now (finally) open in the correct mode. If you double-click
               on a disk icon in the main window, the state it will open in
               (icon or name) is dependent on the setting of the global "View As"
               flag, unless it has already been opened. Listers opened by
               double-clicking drawer icons in other listers will always open
               in icon mode (again, unless they have already been opened, in
               which case they remember their old state).

             - If you had a directory called "Disk" with an icon in the root
               of a device, the directory's icon would be used as the disk icon
               for that device (instead of using the default disk icon).

   20-Sep-95 - Added {Qd} command sequence to get the handle of the destination
               lister. For instance, for a drag'n'drop filetype, you might have :

                   AmigaDOS      echo "Drop from {Ql} to {Qd}!"

             - If you were viewing a file in the text editor, and were at the
               very bottom of the file, and you changed the font to a smaller
               one, the display would not be refreshed correctly.

             - The text in the text viewer is now set in one pixel, rather than
               being hard-up against the borders.

      #1126  - Output windows for functions were being opened with handles
               similar to : CON:0/0/640/200/Title/AUTO/SCREEN DOPUS.1/WAIT/CLOSE
               It turns out that the standard CON: device doesn't seem to like
               this, and so the SCREEN parameter is now last on the line.

             - The "zoom" dimensions of windows are now initialised to the
               smallest possible values (before they were just arbitrarily
               set to 320x200).

             - DiskInfo and IconInfo now know about and report AFS and PFS
               partitions, and CrossDOS (MSD0) disks correctly.

             - If a volume label had an underscore in it, DiskInfo would treat
               it like a gadget label (underscoring the letter rather than
               displaying a real underscore character).

             - The algorithm that SmartRead uses to distinguish between hex
               and ascii files has been improved (I think)

             - DOpus now clears the 'E' protection bit of any IFF files
               it writes (configuration files basically).

             - Added a new rexx command for greater control over the internal
               text viewer.

                   dopus read <filename>           --> returns handle in RESULT
                   dopus read <handle> <filename>  --> read new file into existing viewer
                   dopus read <handle> quit        --> close viewer

             - Order of the buttons changed in the "replace" requester.

             - Lister toolbars now support alternate-image buttons like normal
               button banks do.

             - If you edit the lister toolbar, any open listers are refreshed
               with the new toolbar without having to close and reopen.

             - Added a new command - CloseButtons NAME/F,ALL/S

                   CloseButtons        - closes button bank function was launched from
                   CloseButtons <name> - closes a named bank
                   CloseButtons all    - closes all button banks

             - If the name of an icon on disk didn't have the ".info" in lowercase,
               IconInfo wouldn't read the icon correctly (at all, in fact).

      #1127  - If you double-click on a project icon, and the default tool
               can not be found, the error requester now shows the correct name
               rather than garbage.

   22-Sep-95 - Added "dopus screen" rexx command to get information about the
               current screen. A string is returned in RESULT in the format

                       <screen name> <width> <height> <depth>

               If there is no screen (ie DOpus is iconified), RC will be set to 5.
               You can use this to check whether the program is currently iconified
               or not.

             - Added new internal commands : Quit, Hide, Reveal. The Quit command
               takes an optional FORCE parameter (Quit FORCE/S) to quit
               immediately without displaying the requester.

             - Added a couple of new lister set/query options :

                  lister set <handle> namelength <len>  - sets maximum filename length
                  lister set <handle> case [on|off]     - sets case-sensitivity on or off

      #1128  - When adding files with the "lister add" command, you can now
               specify -2 or 2 for the entry type to get a file or directory in
               a different colour

   23-Sep-95 - Added a kludge for when SysIHack is running to get the iconify
               gadgets positioned correctly.

             - Instead of the corner tabs on buttons with right or middle button
               functions being complemented, the tabs are now erased when the
               button is selected.

   25-Sep-95 - The horizontal drag bar on button banks without full borders is now
               size-adjusted for the current screen mode (ie it is half the
               height on a lo-res screen)

      #1129  - The 'lister set <handle> busy' rexx command is now synchronous -
               that is, it will not return until the lister's state actually
               changes.

             - If you had a lister with a custom handler and an empty path,
               "drop" and "dropfrom" events from that lister would not report
               directories correctly.

             - "doubleclick", "drop" and "dropfrom" events now allow you to
               detect the shift, alt and control keys being held down. A string
               containing the current qualifiers is passed in argument 6.

      #1130  - Lister toolbars now support borderless buttons. At this stage
               the only way to configure this is to set the button bank
               into borderless mode through the button editor.

      #1131  - If a button bank saved in the environment could not be opened
               when Directory Opus was run, it would crash (quite badly too)..
               no idea how long this has been in there.

   26-Sep-95 - The path fields in listers now support clipboard copy and paste
               like other string gadgets. They also allow you to access the
               lister path history using the up and down cursor keys.

             - Memory pooling is now used to allocated the Message structures
               that are used for all inter-process communication. Hopefully
               this should make the program quicker overall (please give me
               some feedback on this).

             - There was a problem where the listers could all lock up;
               this was only introduced a couple of days ago and has been
               fixed.

      #1132  - You can now define "script" functions that are called
               automatically at different times. Select "Scripts..." from the
               Settings menu to configure them. The scripts currently available
               are Startup (when the program is run), Shutdown (when the
               program quits), Hide (when you hide the display), Reveal
               (when you reveal the display after hiding it), and
               Disk Inserted (when a disk is inserted). The "Disk Inserted"
               script is not currently very useful as there is no way
               to find out what disk was changed, but this will eventually
               be the case. Scripts are a button bank like everything else;
               the default name is "dopus5:buttons/scripts".

             - "ScanDir New" with no path now opens a brand new lister,
               rather than a clone of the current source.

      #1133  - Requesters like "Makedir", "Copy As", "Rename", "Recursive Filter",
               etc.. now filter the path characters : and / to make it
               impossible for you to enter an illegal filename.

             - The "Export as ASCII" function in the function editor was
               outputting incorrect flags in some cases.

      #1134  - Directories created with Makedir are now automatically scrolled
               into view and selected.

   29-Sep-95 - "Re-read directory" from the lister pop-up menu now maintains
               the selection states of files.

             - If the device or cache list is visible and you select "re-read
               directory", the previous directory is just pulled out of the
               cache rather than being re-read.

             - The "Reselect" command is back, especially for Leo :)
               By default this command is assigned to the \ key (in listers only).

             - The "command" rexx command can now take a "wait" parameter, to
               indicate that the command should not return until the function
               has finished (the default is to return immediately). For
               example,

                   command wait doubleclick file
                   command wait copy

               The "command" command can now also take a "source" and a "dest"
               parameter, to explicitly specify the source and/or destination
               listers. By default, commands via this method operate on the
               current source and destination. This allows you to override it
               (multiple sources and destinations are not supported however).
               For example,

                   command source <handle> read file.txt
                   command source <shandle> dest <dhandle> wait copy file

             - Added two new Script events : Disk removed, and Double-click.
               The Double-click script is triggered when you double-click
               on the main Opus window (but not on an icon).

             - Added new function sequence - {Qa}, query argument. This
               allows you to access an argument string from a function.
               Its only use at the moment is with the Disk inserted and
               Disk removed scripts. For example, you could have the
               following function for the Disk inserted script :

                   Command    Confirm Disk inserted in {Qa}. Read it?
                   Command    Scandir new {Qa}

               Opus knows about CrossDOS, and so will return PCx: instead
               of DFx: if an ms-dos disk is inserted. For Disk removed,
               DFx: is always returned. Only diskchange on the four
               floppy drives is supported.

             - The Play command now has a QUIET option, to play a sound without
               displaying the status window. Eg,

                   Command    Play quiet data:sounds/doh.snd

             - The "Execute Command" history is now limited to 20 entries.

             - The Copy (CopyAs, Move, etc..) and Delete commands now have a
               QUIET option. If this is specified, no warning requesters will
               be displayed (error requesters still will though).

      #1135  - Dragging a button with dog-ears would make the dog-ears disappear
               from the display.

    1-Oct-95 - "Bad" disks (eg DF0:BAD, DF0:BUSY, etc) can no longer be dropped
               onto other windows (this would cause an enforcer hit if you dropped
               one onto a lister)

             - In the button editor, functions that have something assigned to
               them are shown in a different colour (eg if the Left button function
               is the only one filled out, Left is shown in white and
               Right and Middle are in black).

             - Added "Del" delete button to the button editor.. you can use
               this to completely delete a function from a button. The "Add"
               button next to it is not used yet....

             - If you iconified a lister that was showing a device list, the
               icon title would be "Cache list"

      #1136  - Added several more Scripts, for triggering events on the opening
               and closing of listers, buttons and groups. What practical use
               these have I'll leave up to your imagination, but if nothing
               else you could set up some sound effects.

               The lister handle of a newly opened lister is available to
               script functions in {Qa}, so this might be reasonably useful.
               The name of the button bank or group is also available via
               {Qa}, although this is probably of lesser use.

             - Double-clicking on entries in the path format requester now
               invokes the editor.

             - Added "dopus error <code>" rexx command to retrieve a meaningful
               description of a dopus arexx error code.

    2-Oct-95 - Buttons (in button banks only) now support multiple functions.
      #1137    What this means is that you can (using the button editor) add
               as many "functions" to a button as you like (additional to
               the standard Left, Right and Middle functions). To access
               these additional functions, press and hold the button with
               the left mouse button. After approximately a second
               (you must not move the mouse) a popup menu will appear,
               allowing you to select the function you want. The function
               you choose will become the new "default" function for that
               button, and can be accessed by clicking with the left
               mouse button as normal.

               Pressing the right mouse button while holding the left will
               also activate the popup menu.

               Note that while the Right and Middle button functions are
               also available from the list, their operation remains
               unchanged (pressing the right button will always execute
               the right button function, and the same for the middle
               button). The Left button function is therefore "lost"
               once you have selected a new default, until you bring up
               the list and reselect it.

               This functionality will _not_ be implemented for toolbar buttons,
               so don't bother asking for it :)

    7-Oct-95 - If you added or deleted functions in the button editor, the
               "change" flag was sometimes not set correctly (meaning it
               could lose the changes you had made)

             - If a button had no function defined for the Left mouse button,
               it was impossible to access the pop-up function list.

             - Image buttons now inherit their image from the Left button
               function if they don't have an image explicitly defined.

      #1138  - The Devicelist and Cachelist functions can now take a NEW
               parameter to force them to always open a new lister.

    8-Oct-95 - The lister history "<" popup was broken (selecting a
               directory from the popup would result in garbage in the
               path field).

    9-Oct-95 - If a custom handler trapped the Scandir, Devicelist or
               Cachelist commands, the trapped events were still being
               sent even if the NEW flag was specified (ie even though
               the lister wasn't actually involved).

      #1139  - If you clicked on a button that had no functions defined,
               it would "lock out" any further clicking on buttons in
               the bank.

             - If you had a button with no left function, and you clicked
               on it to bring up the pop-up menu of other functions, and
               then cancelled the menu operation, the first button
               in the bank would be redrawn with the image of the button
               you clicked on.

             - Added a new script - Bad disk inserted. This is triggered when
               you insert a non-DOS (and non-MSDOS if CrossDos is running)
               disk in any floppy. You might want a function like :

                   Command    Confirm Non-DOS disk inserted in {Qa}. Format?
                   Command    Format {Qa}

      #1140  - Especially with banks saved under older versions of Opus 5,
               the corner "tabs" would sometimes be shown even if there
               was no right or middle button function attached to the
               button.

   10-Oct-95 - The "dopus screen" rexx command now returns the BarHeight of
               the current screen (to enable you to open windows just
               beneath the title bar). The information returned by this command
               is now :    <name> <width> <height> <depth> <barheight>

             - Added two new commands - MakeLink and MakeLinkAs. These commands
               allow you to create HARD links to files. Hard links are only
               supported to files on the same volume - this is a limitation of
               the filesystem. Soft links are not properly supported by Opus
               and hence can not be created by this command (soft links are
               not well supported by the OS in general, especially under v39
               and earlier versions).

               Hard links are now displayed in listers in bold, to make it
               easy to distinguish them from plain files/directories.

             - The "lister add" rexx command supports a couple of new "type"
               values. The type values for this command are now :

                       0     device
                       1     plain directory
                      -1     plain file
                       2     directory in "assign" colour
                      -2     file in "device" colour
                       3     directory in bold (link)
                      -3     file in bold (link)
                       4     directory in "assign" colour and bold
                      -4     file in "device" colour and bold

             - The MakeDir command now defaults to scrolling the newly
               created directory into view, but does not select it. There
               is a new SELECT switch that causes the new directory to
               be selected automatically.

             - The kludge for SysIHack to get the iconify gadgets positioned
               correctly is now disabled for screens with fonts of less than 7
               points (can someone test this for me please?)

   11-Oct-95 - When a button bank is in edit mode, the "flashing button" used
               to indicate the currently selected button is now stipple-filled,
               rather than complemented (looks much nicer I think).

             - The "Enter password" requester for Encrypt now has a checkbox
               to select "decrypt" mode without having to prefix the password
               with a minus sign.

      #1141  - Made some changes to the way path formats are used (needs
               testing)

   12-Oct-95 - Nasty bug fixed, I'm surprised it hasn't caused more of a problem
               in the past. If you had a directory visible in a lister, with either
               a show or a hide filter set (so that there were files not displayed),
               and you then changed both the filter AND the sort method at the
               same time, it would trash memory, and depending on how many files
               were not visible before hand, would cause a crash.

             - Icon borders are now one pixel shorter (vertically) to make them
               the same as in Workbench.

             - Buttons, hotkeys, etc, now support the "numpad" qualifier to
               allow you to define functions for the keys in the numeric keypad.

             - If you had no font specifically configured in the text viewer,
               it would not reload your editor settings (Pick Editor).

             - When you query a file with the "lister query entry" rexx command,
               you now get back the correct type (in the case of entries you
               added with "lister add", the same type as you supplied). See
               notes above for the "lister add" command.

      #1142  - The "Rescan Source" and "Rescan Dest" switches in function
               defintions were only rereading the directory if the directory's
               datestamp had changed. The behavious is now the same as under
               Opus 4, where the directories are reread regardless of whether
               they have changed or not.

   13-Oct-95 - If you tried to drag borderless buttons around, there was
      #1143    a chance of Opus trying to do a negative RectFill() (which would
               cause a corruption of chip memory and probably a crash).

   16-Oct-95 - Added a new section and flag to the Options configuration -
      #1144    Miscellaneous/Mouse buttons over inactive banks.
               When this flag is turned on, mouse button events are recognised
               over button banks even when the button window is not active.
               This allows you to use right and middle button functions without
               first activating the window. Left button events are also trapped
               and if they occur within the window's borders (ie over a button)
               the window will not become active as it normally would. To
               activate the window, you need to click on the title bar (or
               anywhere in the window's border).

               You should leave this flag turned off if it causes problems with
               any commodities you are already running (MultiCX, MagicMenu, etc).

               This flag also allows you to use the right and middle buttons over
               a lister without the lister being active (to access toolbar buttons,
               or - with the right button - to scroll the lister display). The
               left button is not trapped over listers and will activate the window
               as normal.

             - The popup menu for buttons with multiple functions now uses
               checkmarks to indicate the current selection.

   17-Oct-95 - The "Cleanup" function in the Icon menu now arranges the icons
               closer together, and more intelligently (it actually seems to be
               exactly the same as Workbench now).

      #1145  - Started removing the toolbar editor. There is currently no way to
               select a new default toolbar.

             - The "Set Flags" command now allows you to add and subtract flags.
               For example, "Set Flags +hidden -noicons" to set the hidden flag,
               clear the noicons flag, and leave any other flags (reverse)
               untouched.

             - The "Set" command has several new parameters :

                    Set source        - Set lister into source mode
                    Set dest          - Set lister into destination mode
                    Set lock [on|off] - Lock or unlock lister as source/dest
                    Set off           - Turn lister off

               The main use for these commands is in toolbar buttons.

   18-Oct-95 - You can now specify the screen font when Opus is open on its own
               screen (Environment/Display mode/Font).

             - The progress bar now has a more 3D appearance (comments anyone?)

             - Made some more changes to the "path formats" system - there were
               problems where listers were losing the path format if you went
               into a sub-directory and back out again (or something like that).

             - The keyboard selection of icons has been improved. The left and
               right cursor keys now work as you would expect, and the display
               will scroll automatically to bring icons into view if necessary.

      #1146  - Added the ability to use AppIcons via ARexx. Two new commands
               are available for this :

                    dopus addappicon <port> <label> <id> [pos <x> <y>] [quotes] [<icon>]
                    dopus remappicon <handle>

               The parameters for the "addappicon" call are :

                    port   - the port name to send messages to
                    label  - the icon label
                    id     - your own ID for the icon
                    pos    - optional position for the icon
                    quotes - specify this keyword if you want filenames to be quoted
                    icon   - optional pathname of icon file (without the .info)

               The system default "tool" icon will for the AppIcon's image, unless
               you specify the name of an icon on disk to load.

               "dopus addappicon" returns an icon handle in RESULT if successful;
               you should keep this and pass it to "dopus remappicon" to remove
               the icon when you are finished.

               Messages from the AppIcon are sent to the port you specified.
               The messages are structured in much the same way as messages sent
               from listers, so there's no reason you shouldn't be able to use
               the same code for both. The arguments you are concerned with are :

                    Arg0  - event (doubleclick, dropfrom, snapshot, unsnapshot, removed)
                    Arg1  - icon ID
                    Arg2  - filenames (if applicable)
                    Arg3  - source lister handle (if applicable)
                    Arg4  - "icon" (to allow you to identify icon events easily)

               Arg2 and Arg3 are unused for "doubleclick" events. "dropfrom" events are
               much the same as "dropfrom" events in listers. If the drop originated
               from an Opus lister, Arg3 will contain the handle of it and only
               filenames will be supplied. If the drop originated from outside of Opus,
               Arg2 will contain the complete pathnames and Arg3 will be zero.
               "snapshot" and "unsnapshot" events are sent when the user snapshots or
               (funnily enough) unsnapshots your AppIcon. In the case of snapshot events,
               Arg2 contains the new coordinates of the icon (eg "203,20"). The "removed"
               event is only sent if Opus quits while your icon is still added.

   19-Oct-95 - AppIcons can now be dropped onto other AppIcons, AppWindows, etc, like
      #1147    other icons can (I honestly didn't know that Workbench supported this :)

             - If you iconified an empty lister, the icon would be erroneously labelled
               "Device List".

             - The rexx "lister set position" command no longer allows you to change
               listers that are locked in place.

             - The rexx "lister query position" command will return with the
               word "locked" at the end of the result string if the lister is
               locked in position. For example,

                           lister query <handle> position
                       --> 66/230/320/200 locked

             - "lister query all" was broken, it's working again.

             - If you opened a new lister, zoomed it, iconified it, uniconified it,
               and zoomed it again, it would fail to refresh itself properly.

   20-Oct-95 - The IconInfo requester now allows you to drop other icons on it to
               replace the imagery of the icon being edited.

             - Opus now intercepts PutDiskObject() calls and will refresh the display
               if any icons are added or changed.

   22-Oct-95 - The mysterious "mouse pausing" after drag'n'dropping, and
               "lister scroll for ever" bugs were traced to a Forbid() without a
               matching Permit() (tsk, tsk).

   23-Oct-95 - The filetype "Edit definition" requester now has a "View File" function,
      #1148    to automatically load the textviewer to view a file (in hex mode).

   24-Oct-95 - Started work on "Icon Action" mode, this does not work yet.

   25-Oct-95 - The "file progress bar" is now back for operations like Copy, Encrypt,
               etc.

             - "Rename" and "Select All" from the Icon menu now work on listers in
               name mode.

   26-Oct-95 - (Mark Allen 12-Oct) DnD'ing over left, middle and right button
               functions in the button editor should work properly now. DnD'ing
               over "custom" functions also had some problems.

   ******    - Opus should now work properly when using two or more disks with the
               same name (for example, copying from one floppy to another where both
               disks are labelled Empty).

               Please test this out, and be on the look out for anything this might
               have affected (user-configured Path Formats not being used, directories
               not being brought out of buffers properly, incorrect directories
               shown, etc).

               I am aware that the "Expand paths" flag is now ignored (paths are
               currently always expanded). This might change in the future.

             - Progress bar imagery has changed slightly, I'm still not sure about it.

   27-Oct-95 - If you paste a function into a filetype action, it now works properly.
               (It used to assign the function to the wrong action; eg double-click
                instead of User1, etc)

      #1150  - The iconify gadget in window title bars now has a 3D appearance if
               SysIHack is running, to blend in better (looks damn good if you ask me :)

   30-Oct-95 - Added "Priority" to Options configuration.

             - "Auto-select icons" was accidentally made case-sensitive, this has been fixed.

   31-Oct-95 - Added the option of "borderless" icons. This is set from within the
               IconInfo requester (via a pull-down menu), on a per-icon basis.

               Borderless icons are rendered without the bevelled border, and with no
               backfill surrounding them. This works better with some icons than with
               others, which is why it is optional for each icon (eg MagicWB icons
               don't generally look very good without borders, but other icons might).
               For icons with intricate designs, and a nice backdrop picture behind them,
               this can look very attractive.

               The icon image used when dragging icons around is now borderless in
               all cases.

               Note that rendering icons without borders requires constructing
               "masks" of the image, which both uses more chip memory and takes slightly
               longer to render. On a fast machine, or on a display without many colours,
               you probably won't notice, but if you're using 256 colours on a 1200 you
               might find the "flashing" unacceptable. In this case, don't use the
               borderless option :)

    1-Nov-95 - Fixed bug that could prevent DOpus from quitting completely (just the
               main process would be left behind, forever)

      #1151  - Added "Desktop" section to Environment configuration. This allows you to
               modify the appearance of the desktop (the icons in the main window, basically)
               and have distinct appearances for different environments.

               "Distinct icon positions", when turned on, causes all icon Snapshots to
               not affect the main icon position, but instead to be stored with the
               environment file. When turned off, the standard icon position (from the
               icon file) is used.

               "Font" allows you to select the font used to render icon labels. You
               can also select the colour and draw mode. The addition of this section
               means Opus no longer reads or uses the Workbench icon font preferences
               (although when coming from an old configuration, your current Workbench
               settings will be the default).

               "Hidden drives" allows you to specify certain drives that you do not want
               icons displayed for. For example, if you have lots of hard drive partitions,
               but you only actually use two of them regularly, you could disable all
               the others to keep your desktop tidy. Hidden drives can of course still
               be accessed via the device list, etc. If a drive is hidden, any "left-outs"
               for that drive are also not displayed.

    2-Nov-95 - The popup menus that are used in various places (listers, button banks, etc)
               now have a much nicer appearance

      #1152  - Added popup menu over icons - press right mouse button over any icon.
               I think this concept is really neat (thanks Bill :) so if I can think of
               anywhere else good to use it I will - any suggestions?

    3-Nov-95 - The icon popups now work even when the window isn't active

      #1153  - The spacing on the sides of popup menus is now font-sensitive

             - You can no longer copy files to listers that have no path in them
               (ie if a lister has no path displayed, it is not a valid destination).
               Before files would have gone to the current directory.

             - Icon refreshing optimised when you reposition an icon

             - GFLG_COMPLEMENT/GFLG_BACKFILL icons are now rendered in a new
               style when selected (sort of an inverse stipple-fill).. looks much nicer
               than boring old xor. This only affects icons that have no alternate image.

    4-Nov-95 - Fixed an enforcer hit that slipped in over the past few days (would
      #1154    show up in drag&drop operations, among others)

                           -- OPUS 95 WORLD TOUR --

    8-Dec-95 - Drag'n'drop directories was broken - copy wouldn't work, and if you
               set up a filetype to use scandir, it wouldn't work either.

             - Took the icon "stipple-fill" out, since greg complained too much.
               Non-alternate image icons are now highlighted as before.

   14-Dec-95 - You can now add your own items to the icon popup-menu (the menu
               you get if you press the right mouse button over an icon), via the
               filetypes system. The new "Icon Menu" section in the filetype editor
               allows you to define functions that are displayed in the popup
               menu. For example, you might have the following for the LHA
               filetype :

                         View archive...         AmigaDOS   lha v {f}
                         Extract to RAM:         AmigaDOS   lha -x -M x {f} RAM:

             - The old {Rf} sequence from Opus 4 is back. You can now use
               {Rf} for a file requester, {RF} for a file requester in save mode,
               and {Rd} for a directory requester. As an extension to the icon menu
               operations above, for example, you could have an additional item :

                         Extract to...

               With the function

                         AmigaDOS   lha -x -M x {f} {RdSelect Destination:RAM:}

   15-Dec-95 - Diskcopy now uses a progress bar instead of text information (like Format)
      #1155

   18-Dec-95 - The Icon Action mode now works, more or less.. obviously there are still
               some problems with it - if anyone wants to make a list of these I'd
               appreciate it :)

   20-Dec-95 - More work done on the Icon Action mode

             - The input trap to intercept mouse button clicks over gadgets would
               kick in if a button was under the mouse, even if it was covered
               by another screen. It now only works if the button is actually
               visible under the mouse.

             - You can now turn off an icon's label from the IconInfo requester
               (similar to the way you can turn off borders).

      #1156  - If you hold down the left-alt key while double-clicking on a
               directory icon, the parent window will be closed automatically
               when the new lister opens.

   21-Dec-95 - The rotating hedgehog in the about requester is now 4 colours
               (and remapped under 39!)

             - Cleanup icons now takes into account icons without labels and borders.

             - The show module was testing for Graphics >39 instead of Graphics >=39
               when using BestModeID(), so this would obviously not work properly
               under 39 (3.0)

   22-Dec-95 - DOpus now makes a local copy of any AppIcons that are added. This
      #1157    makes it work with MaxonTwist and other programs that free the
               DiskObject immediately after adding the icon.

   24-Dec-95 - Format now checks if a disk is write-protected properly. It used to
               go through the device interface, which is fine in most cases, but
               doesn't take in account dos-level locks (eg lock dh0: on)

   26-Dec-95 - Reorganised the Icon menu a bit. Removed the separate "Program Groups"
               item, and added a "New" item at the top. This allows you to create both
               drawers and groups. To delete programs from a group, use "Delete" instead
               of the old "Remove Program". You also use "Delete" to delete groups
               themselves.

             - "Delete" from the Icon menu and the popup over icons now works. Note
               that if you delete something that has been left-out on the main window,
               all it does is delete the left-out (ie, put away).

   27-Dec-95 - Added "Copy" option to icon popup menus.

                            *** Happy New Year ***

   10-Jan-96 - Implemented a new icon caching system. This caches the image data
               of all icons, using a checksum system. What this means is that if you
               have a drawer with lots of files, all using the same icon, only
               one copy of the icon image is stored in memory - this can result
               in a huge saving of chip memory. Icon loading time may be slightly
               slower (I haven't noticed it on an 040).

               Note that with the way the checksum system works, it is theoretically
               possible for the wrong icon image to be used (ie it is possible for
               two completely different images to have the same checksum), but in
               practice I believe the chances of this are remote. If anyone ever
               comes across two icons that exhibit this behaviour, please send
               them to me :)

             - There is a new popup menu in listers - if you press the right mouse
               button over the lister borders, or (for a lister in icon mode)
               anywhere there isn't an icon, the menu appears. It allows you to
               Iconify and Snapshot the lister, as well as change the View By
               setting. It also gives you access to a new function - Arrange Icons.
               This allows you to sort the icons by Name, Size, Date and Type.
               There is also a New Drawer function from this menu.

             - The management of left-out icons has changed. The old .dopusdrop
               files are no longer used - instead, information on left-out icons
               is kept in the position-info file. This should make Opus start up
               much quicker, as it no longer has to check all devices for
               .dopusdrop files. The other advantage to this is that left-out
               icons can now have their own positions, distinct from the position
               of the original icon.

             - There is a new module - update.module. This module will be
               included with all new DOpus releases, and is used to automatically
               update configuration files. These updates are performed the first
               time you run the new version of Opus. Once any updates have been
               completed, the module deletes itself (from dopus5:modules) to
               save memory and disk space.

               The update.module included with this archive will automatically
               convert your old .dopusdrop files to the new format for left-out
               icons.

             - Whenever Opus has to copy or delete an icon, it now uses the
               GetDiskObject()/PutDiskObject() and DeleteDiskObject() library
               calls, rather than copying the file byte by byte. This means that
               any programs which are looking for icon changes (for example,
               Opus itself, and Workbench) will see them.

             - Opus is now a lot smarter when copying or deleting files. For
               instance, if you have several listers open all showing the same
               directory, and you copy a file into that directory, all listers
               are now updated automatically. Also, any icons that are copied
               or deleted are now refreshed automatically in any open listers.

             - Any left-out icons now have a little 'arrow' image superimposed
               on them, to indicate that they are left-outs. The same image is
               shown on any icons of hard or soft links. Yes, this is blatantly
               stolen from Win95, I don't care :)

             - Popup menus can now be 'locked' open - if you press the button
               to pop them up, and then release it without moving the mouse
               very far, they will remain open, and can then be activated with
               the left mouse button. Popup menus now also support sub-menus -
               this feature is used in several places.

             - Opus now supports soft links, to the extent that they will be
               shown correctly in listers. The manipulation of soft links is
               still limited to some extent - this is more the fault of the
               filesystem (soft links are quite crap actually, another piece
               of half-finished work by Commodore).

      #1160  - Added "Leave Out" option to icon popup menus.

   24-Jan-96 - You can now put device and cache lists into icon mode. When in
      #1161    this mode, you can delete and rename assigns using the icon menu.

             - Checked and tightened up the operation when dragging and dropping
               things around. I am now fairly confident that the following
               operations work (they should work similarly to Workbench as well) :

                 * drop onto drawer icons (both in listers and left-out)
                 * drop onto disk icons
                 * drop disk icon into lister in text mode (reads directory)
                 * drop disk icon into lister in icon mode (copies entire disk)
                 * drop of an icon that has no corresponding file (eg Shell.info)
                 * drop from one lister to another on same disk (moves instead of copies)
                 * drop a directory with shift down (reads directory)
                 * "Directory" file type should work in all cases
                 * various combinations of these

               Please check these out. I'm not used to using Workbench so I'm not
               sure if these do work as they should (I think so :), also check for
               things I may have forgotten. There're so many different drag & drop
               combinations that it's hard to keep track of what's going on.

   25-Jan-96 - Opus would crash (or at least have problems) if the Images for the
               toolbar couldn't be found.

             - If you specify an icon for a Directory filetype, its image will now
               be used for directories (in Show All mode) or when creating new
               drawers.

             - Format in the icon popup menu is now enabled correctly for floppies
               and RAD.

             - Deleting a directory with nested sub-directories could sometimes fail
               with an 'object in use' error, if the sub-directories had icons.
               This has been fixed. As an added bonus, DOpus now no longer keeps open
               locks on directories that it has displayed in icon mode.

             - The 'Try again' option when deleting files was broken (DOpus would
               always skip over regardless)

             - If Workbench isn't running when DOpus loads, DOpus creates a dummy task
               called Workbench. This is so that programs like ToolManager that go
               looking for Workbench to grab the path list will be able to find it.

      #1162  - The right mouse button trapping no longer happens when the pointer is
               over the screen's title bar (to allow you to access the screen's menus)

   30-Jan-96 - The progress requester has been removed, and changed to a free-floating
      #1163    window. The file progress bar (in Copying, etc) has been changed to
               a byte count (xxx/yyy bytes).

               This has several advantages over the old "in-window" requester, namely

                 - it looks nicer
                 - the minimum size of listers is no longer determined by the size
                   of the progress requester
                 - system gadgets in the listers aren't blocked - you can resize and
                   zoom listers even when busy
                 - the iconify gadget in listers is not blocked - you can iconify
                   listers when busy!
                 - the close gadget is not blocked - it now acts as an 'abort' button
                   (even when loading icons)
                 - the scroll bars aren't blocked - you can scroll around in a lister
                   when it is busy (can't select files of course)

               If you iconify a busy lister, the progress window is hidden along
               with it.

               There is no progress window shown when reading directories. To abort
               the reading of a directory, click the window close gadget (or press
               escape).

   31-Jan-96 - Finished off lister toolbar editing - it should work properly now.
               To load a different toolbar, you select "Edit lister toolbar" from the
               menu, and then from the popup-menu over the button bank select "Load".
               Toolbar editing probably needs a lot of testing.

             - Fixed some problems with enforcer hits in Duplicate (result of the
               new progress window)

             - The xxx/yyy bytes display in the progress window has been changed to
               xxx% (a percentage display is much easier to read)

             - Pressing a key to move to the first item in the lister that begins
               with that letter was broken.

             - Fixed an enforcer hit to do with the "bad disk inserted" script.

      #1164  - When 'show all' in icon mode was turned on, every icon was shown
               initially in the top-left corner, then redrawn in its correct position.

             - Changed the order of items in the (third) lister popup menu.
               Also removed two unnecessary items (Iconify and View Icons - Iconify
               you can access from another popup menu and also the iconify gadget,
               and View Icons you can also get from the other popup menu).
               We really must start finding meaningful names for all these popup
               menus.

             - The names (including complete paths) of selected entries in a lister
               (in name mode) are copied to the clipboard when you press right-amiga c.

             - Fixed some more problems with toolbar editor (some enforcer hits, plus
               rendering problems). While you can load any button bank in as a toolbar,
               banks with more than one row of buttons will be automatically
               rearranged to a single row.

             - Device list in icon mode was temporarily broken.

             - Format, Diskcopy and Print now use the new-style progress indicator.

             - IconInfo now allows you to save an icon even if there was no icon
               loaded originally (ie if there is no real icon for the file, a new
               icon will be created).

      #1165  - Added a new "lister set" rexx command - "lister set newprogress".
               This is similar to the "lister set progress" command, but allows
               you to control the information displayed more easily.

               The command template is :

                 lister set newprogress [name] [file] [info] [bar] [abort]

                 name  - allocates space for filename display
                 file  - allocates space for file progress display
                 info  - allocates space for information line
                 bar   - allocates space for progress bar
                 abort - adds abort gadget

               To control the new progress indicator, use the following commands :

                 lister set newprogress name <filename>
                 lister set newprogress file <total> <count>
                 lister set newprogress info <text>
                 lister set newprogress bar <total> <count>
                 lister set newprogress title <text>

               You can use the old "lister set progress" commands on a 'newprogress'
               indicator, but obviously they can only change the filename and bar count.
               Use "lister clear progress" to remove either the 'old' or 'new'
               progress indicators.

   03-Feb-96 - The buttons in Opus requesters now size to fit the text in each one,
               rather than the size of the biggest button. What this means is that
               requesters with lots of buttons (like the 'file exists, replace?'
               requester) are no longer unnecessarily wide.

             - If you dropped a disk icon into a lister in Icon Action mode, 
               and then aborted it, a 'deadlock' error would result. If you didn't
               abort it, the copy would complete but the progress window would not
               be closed afterwards.

             - Alt-clicking on a lister toolbar button to edit it now works again.

             - You can now double-click on a filetype file to edit it (only if it is
               in dopus5:filetypes/).

   05-Feb-96 - Opus would crash if it couldn't find the toolbar file.

             - Fixed a problem that would cause occasional lockups. The problem
               occurred intermittently when aborting a function that had opened
               a requester over a lister (eg, Rename).

             - If you did a Parent, or read a new directory into a lister in icon
               action mode, and the directory came out of a buffer, the icons
               would not be cleared and you would end up with overlapping icon
               images.

             - Editing icon tooltypes could crash if you added a New tooltype, and
               then clicked on another one or pressed Delete on a blank string,
               or something like that.. (trust me, ok?)

      #1166  - The old 'lister progress' rexx commands weren't completely compatible
               with the new style progress requester; they now work better.
               It is suggested you update your scripts to use the 'newprogress'
               commands anyway.

             - If you iconified a busy lister with a progress window that was
               being sent rexx commands (eg with OpusFTP or LHADir), it could cause
               a lock up.

   06-Feb-96 - Fixed a bug that could cause a crash when you de-iconified a lister
               or button bank. The appicon would be removed but there was the
               chance that Opus would still try to access it after it had been freed
               (the icon removal message was being sent asynchronously).

             - Iconified listers are shown with a ghosted icon when busy.

             - You can change the label of an iconified lister from arexx using the
               new "set lister label" command.

             - If you dropped a disk icon onto a drawer that was on that disk,
               Opus would go into an infinite move loop.

      #1167  - Fixed button spacing in requesters.

             - Fixed a problem where really large icons would overwrite the
               border of the display in the IconInfo requester.

   07-Feb-96 - Fixed enforcer hit in the progress window with Duplicate.

             - Dropping a disk icon onto a directory icon now gives you a progress
               window for the copy, allowing you to abort it.

             - You can now open a progress window from ARexx without a lister
               to attach it to. Use the "dopus progress" command for this.

               eg,  dopus progress name file bar abort    - returns handle in RESULT
                    dopus progress <handle> name Filename - changes filename
                    dopus progress <handle> abort         - check abort status
                    dopus progress <handle> off           - turns indicator off

             - Added 'Close' items to the popup menus for iconified listers and
               buttons.

      #1168  - The 'dopus getstring' rexx command can now take a 'secure' keyword.
               If this is specified, the string you enter is displayed as
               asterisks (this is for things like entering passwords, etc).
               For example,

                    dopus getstring '"Enter password" secure 40'

             - Opus now supports multiple user menus, and items with sub-items.
               Unfortunately, the configuration editor doesn't work yet.
               If you build a button bank with multi-function buttons
               and use that as your user menu, the multiple functions will
               appear as sub-items.

             - The Protect, Comment and Datestamp commands now work from arexx
               properly again (no idea what happened to them).

   10-Feb-96 - Fixed problem in Show function when using datatypes - the title
               bar area of the picture would be erased (this is due to a bug in
               the OS!). Opus now keeps a backup of the title bar area and
               blits it back once the screen has been displayed.

   12-Feb-96 - The new menu editor is now more or less working. It supports
               the usual drag'n'drop operations. You can also drop a button file
               from an Opus lister onto one of the listviews to easily add
               to an existing menu.

      #1169  - Lister popup menus now support sub-items, and use the new menu
               editor.

   13-Feb-96 - Fixed a couple of problems with Delete. If a delete failed and
               the requester came up, Abort on the requester wouldn't work
               (it would just do a Skip). Unprotect All would clear the
               delete bit properly, but would only actually delete the
               first file.

             - Fixed another layout problem with requester buttons (should
               now work properly in all cases).

             - Copy the iconclock.module file to your dopus5:modules/
               directory if you want to see how tricky Opus can be :)

      #1170  - The new menu editor has the following 'features' :

                 Drag & drop moves the item
                 Drag & drop with shift held down copies it

                 Tab to change the 'active list' (indicated by a rectangle).
                 Cursor up/down to change selection in active list.
                 Cursor up/down with shift to move the selection up or down.
                 Return to edit the selection in the active list.
                 + to add an item
                 DEL to delete current item

             - The ToolbarArrow.image file can now be an animbrush (ie the
               alternate image will be shown correctly when the button is
               selected).

      #1171  - Fixed a couple more problems with the menu editor.

             - Progress windows that show both the bar graph, and the file
               progress (eg Copy) now have the graph and file displays
               swapped around. This means that instead of the graph
               showing the percentage of files copies, and a xx% display
               showing the progress of that file, the graph shows
               the file progress and a 'xxx of yyy' display gives
               overall information.

   16-Feb-96 - Fixed a problem that caused the double-click script to stop
               working under some circumstances.

             - You used to be able to click on an icon, click off the icon,
               and then click on the icon again, all within the double-click
               time, and have it recognised as a double-click. This has
               been changed.

             - If an icon was selected, moved, and then clicked on again,
               within the double-click time, it was treated as a double-click.
               This has also been changed. (ie, to double-click on an icon,
               you must not reposition it).

             - Added 'Middle double-click' and 'Right double-click' scripts.
               The right-button script is activated when you double-click the
               right button over the main Opus window ONLY. The middle-button
               script is activated when you double-click the middle button
               anywhere at all.

             - The Scripts editor now has Delete, Edit and Use buttons.

             - The button window that opens to edit the lister toolbar now
               has the normal 'editor' menus (Project and Edit). Also, selecting
               Save from the button editor window should now save the toolbar
               with the correct filename.

      #1172  - You can hold SHIFT in the menu editor when pressing Add or Copy,
               to insert the new item at the current position instead of at the
               end of the list.

             - If you changed the bar position on a borderless button bank
               (eg from horizontal to vertical) and then hit Cancel, it would not
               revert to the old state.

             - You can now clip just the name of a file from a lister (instead of
               the complete pathname) with right-amiga + shift + c.

   17-Feb-96 - Added 'Open Parent' option to Lister menu.

             - Added 'Empty Trash' option to the icon popup menu for Trashcans.
               It works, sorta....

      #1173  - Fixed problem with the menu editor; if you dropped a button from
               another bank into the item list, and then selected Use, the
               change you had made would be ignored.

   21-Feb-96 - The double-click testing for icons had been made too strict; it
               is now a bit more relaxed (specifically, you can move an icon up
               to 5 pixels in any direction and click again on it to still
               register a double-click).

             - The button editor, and the file requester for Open buttons, were
               coming up on the default public screen instead of the Opus screen.

             - Implemented my own boopsi string gadget class. This allows me to
               have thin-border string gadgets (which are used in some places),
               and also supports resizing.

             - The 'selection list' requester is now resizable (this is the requester
               that comes up with a list of functions in the function editor, etc..)

             - Now have my own boopsi checkbox class too. The only visible difference
               is that (currently) the image is an X rather than a checkmark, and in
               the button editor the checkboxes have thin borders. Whoopeee! :)

             - The diskinserted and diskremoved scripts are now blocked if Opus is
               iconified.

             - Maybe fixed a bug that could make Opus lock up when you delete a
               program group.

             - If you opened the button editor, and then selected more than 1 bank
               (so that at least 2 banks had been recognised by the editor), then
               closed the banks, the button editor would not notice that the
               non-currently selected one had been closed. If you then closed
               the button editor, it would probably crash.

             - If you closed the button editor, and as the window closed a button
               bank window became active automatically, it could sometimes trigger
               the button editor to open again.

      #1174  - Added 'normal' menus to the button editor window (not operational yet)

   23-Feb-96 - Maybe fixed a bug that could make Opus lock up when you delete a
               program group (take 2).

             - The button editor menus now work.

      #1175  - I added normal preferences menus to the Options editor. I have removed
               the Load, Save and Save As items from the Settings/Options menu in the
               main program, as these functions are all now available from the editor
               itself. The Environment editor has menus as well but they are not
               yet operational.

             - The command template for AddIcon is now :

                 NAME,BORDER/S,NOBORDER/S,LABEL/S,NOLABEL/S,CHANGE/S

               BORDER/NOBORDER let you turn the icon border on or off
               LABEL/NOLABEL allow you to turn the label on or off
               If CHANGE is specified, it allows you to change the border/label
               state of existing icons (no new icons will be created).

   24-Feb-96 - Menus are no longer blocked when listers are busy. The ghosting of
               items in the Lister and Icon menu is now smarter (only for listers,
               currently). Please keep an eye out to check that things are
               enabled or disabled when appropriate.

             - Added {Rf}, {RF} and {Rd} to the popup list in the function editor.

             - If you change the drag bar orientation of a borderless button bank,
               the bank is no longer closed and reopened - it just just
               resized accordingly (quicker).

             - If you had a borderless button bank with the dragbar set to
               Automatic, and you pressed the 'Xform' buttons, the dragbar's
               automatic position was not being updated properly.

             - It is now impossible to have a button bank with no buttons in it.
               You used to be able to create an empty button bank using, for example,
               the menu editor, and the load it a button bank. DOpus now checks
               before opening banks and if they are empty, it will add a blank
               button automatically.

   25-Feb-96 - Moved the 'appearance' controls from a separate window onto the main
               button bank editor window.

             - Added a button to delete events in the filetype editor.

             - Adding popup menu items to a filetype could overwrite or confuse
               the User1 (and possibly other) definitions.

             - Dropping a directory or a disk onto the function editor now creates
               a 'Command    ScanDir NEW <path>' entry.

             - Dropping a project with a default tool onto the function editor now
               creates a 'Workbench    <default tool> <project>' entry.

             - The command template for MakeDir is now :

                 NAME,NOICON/S,SELECT/S,NEW/S,READ/S

                 NAME   - directory name
                 NOICON - don't make an icon
                 SELECT - select new directory automatically
                 NEW    - read new directory into a new lister
                 READ   - read new directory into the current lister

             - When Opus creates a drawer icon (eg, by the MakeDir command), the
               drawer size in the new icon is now set to the user-specified
               default lister size.

             - The {} button in the function editor now brings up a list
               of the arguments in the function template, for internal commands.

   26-Feb-96 - You can now select the device used for output windows (defaults to CON:)
               in the Environment/Output Window section.

             - The rexx command 'lister query mode' did not report icon action mode
               correctly. The 'lister set mode' command (as well as the internal Set
               command) did not allow you to set icon action mode. Both these now use
               a new keyword ('action').

             - The horiztonal and vertical sliders in listers have always been
               improperly set (they were one 'pixel' out, so even when the lister
               was sized to show all icons, you could still move it a pixel).

             - If you ran commands on files with borderless icons, in icon action mode,
               the deselected icon imagery could be redrawn over the top of the
               selected image, without clearing it first (resulting in a double image).

             - Added 'Assign' command to make an assignment to the current
               source path. You can also do this by dropping a drawer icon onto
               the device list in icon mode.

      #1176  - Delete from the Icons menu now works on listers in name mode.

   27-Feb-96 - A new program, 'ViewFont', finally gives Opus5 a font viewer. Use
      #1177    the supplied Font filetype if you want to add the ability to double-click
               on a font to view it (you can doubleclick on either the .font file -
               eg courier.font - the font data file - eg courier/13).

             - Filetypes config window and filetype editor window now have the
               'okay' button in bold.

             - I seemed to have fixed the problem loading backdrop preferences files
               from AFS partitions. As usual, AFS fucked something up...

             - The method of opening multiple projects by clicking on a tool, holding
               shift and double-clicking on one or more projects now works properly.

   28-Feb-96 - Opus listers can now display a file's version information. The new
               'Version' item in the list format editor allows you to do this.
               DOpus searches the file for a version string in the standard
               $VER: format, and parses it if found. It does not currently understand
               library file formats, etc, and so won't return a version on some files that
               the c:version command might.

      #1178  - The 'file exists, replace?' request has changed (again!). The display is
               now more 'user friendly' - instead of showing the size and datestamp,
               you are now told what is different. This also now checks file versions.

             - You can now drop from button editors, the clipboard, menu editors, and
               button banks, etc, directly to the function editor. If you do this it
               is the left button function (only) of the button that is copied.

             - Fixed a small bug in the Font Viewer, when a font had no corresponding
               directory (probably on CGFonts).

   29-Feb-96 - Fixed a crashing bug. For fun and games with the previous version,
               open a button bank, edit it, and make a change to it (eg swap two
               buttons around). Then select close from the bank popup menu.
               A requester appears (this bank has changed, etc..). Before you select
               an option from the requester, click Cancel on the button bank editor.
               Then choose Discard from the requester.

             - Fixed a refresh problem with the listview in the popup command list, etc.

             - The show.module now tries to load the picture using datatypes, whether it
               is IFF or not. If it can't be loaded through datatypes (eg, running on a
               v37 system), the internal IFF code will be used. This will hopefully
               fix problems people have been having under CyberGfx, etc, where just
               a blank screen was coming up.

             - Swapped the 'skip' and 'abort' buttons around in the Rename requester.

             - The GetSizes command now has a FORCE option that forces it to scan
               all directories, even if they already have sizes displayed.
               The ClearSizes command has been made private, so it won't show up on
               function lists, but it still works for compatibility.

             - The text viewer, button bank editor, and several other windows now
               have the menu shortcut keys hardcoded (to the English defaults),
               rather than automatically generating them.

      #1179  - The display is now cleared when you regenerate the device list
               in icon action mode (so that you don't get double-images).

             - Shift-/ (? in other words) now works to read the parent directory
               into a new lister (just like shift-; for root).

             - Sorting by version now works properly when reading a directory for
               the first time.

   01-Mar-96 - The button editor is now brought up automatically when you create a
               new button bank.

             - When viewing pictures using the internal viewer, you can now
               press q to exit a picture but leave its entry selected, and delete
               to exit a picture and mark it for deletion. If any pictures
               are marked for deletion when the last picture has been shown,
               the delete function is automatically launched on them (you are
               given the usual warning first).

      #1180  - Added an option to Options/Miscellaneous - Verbose replace requester.
               With this turned off, the 'file exists, replace?' requester is
               shown in the old format with the addition of version numbers. When
               enabled, you get the new verbose sentence form (unless the dates,
               sizes and version numbers are identical, in which case you get
               the verbose form anyway).

   03-Mar-96 - Fixed problem with string gadgets that had a title above the
               gadget (eg in the Search requester) - the title was being shown
               to the left instead.

             - Fixed problem with the Path Format requester. If had no entries,
               added a new one and then selected the new, blank entry, you would
               no longer be able to add new entries.

             - The keys for parent and root in a lister have been changed slightly.
               It is now ; for root in the same window, : for root in a new window,
               / for parent in the same window, and ? for parent in a new window.
               These are the same no matter what keymap you are using (it used to
               be a bit confused for non-English keymaps where ; and : were on
               different keys).

             - The qualifier string is now passed to custom handlers for parent
               and root operations (if you get 'shift' you should open in a new
               window).

             - To set a button's image or label by dropping a file onto the button
               editor window, you now must drop it over the button display area
               itself. If you drop it anywhere else in the window it will be
               used to create a function for the button instead. The only exception
               to this rule is if there is currently no image, or no function (or
               both), in which case they will both be filled in.

             - When you create a new graphic button bank, the default size of
               the buttons is now much larger, so that you can access the close
               and drag gadgets of the window. As soon as you actually set an image
               in the new bank, the buttons will resize.

      #1181  - Pressing letter keys in a lister to skip to a file has changed.
               When you press a key, a string field appears at the top of the
               lister, and you can enter more than one character to match on.
               This should make it easier to find files in a big directory,
               for example, where all files start with 'mod.'. When you press
               return, escape, or click in or out of the lister, the gadget
               disappears again. Note that this only works for skipping to
               files - the old ability to skip to directories as well is gone.
               If anyone desperately needs this back, let me know, but I think
               that 99% of the time it's going to be a file you're looking for
               anyway.

   04-Mar-96 - The version routines were only checking the first 8k of a file
               for a $VER: string - they now check the whole file.

      #1182  - Under OS39 and above, Opus now performs colour remapping on toolbar
               and graphical button bank images. The remapping code does not
               perform any dithering or other operations - it simply tries to
               find the best pens. This should allow you to use simple images
               without having to try to match up the palettes yourself, but
               don't expect it to let you use 256 colour pictures as buttons
               and have it look nice on an 8 colour screen. This should also
               allow you to discard DIF or other programs to artificially increase
               the depth of your images.

               The code that does the remapping is very basic at the moment, and
               so it is fairly slow - once people have tested this a bit and
               it seems to be working, I'll look at improving the speed. Note that
               as icons do not have palette information, the remapping will not
               affect icon images used as buttons. Opus won't try to remap images
               that, as far as it can tell, don't need it (ie if the palette of
               an image is the same as the screen's palette).

               Colour remapping uses more chip memory - usually it will be
               at least twice as much as without remapping. Since toolbar images
               are usually pretty small this shouldn't be a problem - if there's
               not enough memory to remap the image, the original one will be
               used. I might add an option to disable remapping (on a per-button-bank
               basis) if people think it's a good idea.

   05-Mar-96 - The button editor and button clipboard now support palette remapping
               too (might still be some tidying up to do here).

             - The 'lister query entry' rexx command with the STEM parameter now
               returns version information, if it exists. The new fields are

                     VERSION    - version number
                     REVISION   - revision number
                     VERDATE    - date string (numerical dd.mm.yy format)

               This command also has two additional fields :

                     DATENUM    - file date in numerical dd.mm.yy format
                     TIME       - file time in hh:mm:ss 24 hour format

             - Listers are now refreshed properly if you resize them while they are
               reading a directory (sorry Edmund :)

             - Sorting by version is now based on the actual version and revision
               numbers (and on the date if applicable), rather than on a string
               comparision of the version display (eg 2.0 will now come before 10.0,
               rather than after it).

             - The verbose 'file exists, replace?' requester is now turned on by
               default in new configurations.

             - Added 'Quick quit' option to Options/Miscellaneous.

   06-Mar-96 - Multi-selection and double-clicking icons has changed. It is now the
               first tool selected that gets run; whether or not you select additional
               tools, projects, directories, whatever - it used to be the tool you
               actually double-clicked on. This is compatible with Workbench.
               Also, tools and drawers can now be passed as arguments, as well as
               projects. Hopefully this should make things like 'deficons' or
               other weird things work.

             - When the button bank editor is open, you can now drop a program from a
               lister onto a button directly, instead of having to open the button
               editor and drop onto that.

   07-Mar-96 - I've changed the show.module back to using its own IFF code in preference
               to datatypes IFF, since datatypes is slower and has more problems.
               You can force it to use datatypes first by setting an environment variable :

                  setenv dopus_show usedt

             - Fixed enforcer hit if you alt-clicked on a button in the toolbar when the
               toolbar editor was already open.

             - Buttons that run functions in paths containing international characters
               (specifically about ASCII 240 and over) should now work properly.

      #1183  - Fixed a couple of minor problems with image remapping.

             - If you drag a file onto the desktop it becomes a temporary left-out;
               the icon popup menu now has a 'Leave Out' item to enable to to make it
               a permanent left out. Also, the 'Delete' item in the popup menu for
               left-outs is now called 'Put Away' (it performs the same function).

             - Clicking on an already-selected icon no longer deselects all other
               icons. This is similar to the way Macs or Win95 work. This means that
               you can lasso a whole bunch of icons, then click on one of them to
               drag the whole lot, without needing to hold down shift.

             - Rearranged the buttons on the Delete error requester so that 'Abort'
               is at the end, and added a 'Skip All' button.

      #1184  - Fixed problem in the Options editor when saving the settings -
               there was the possibility for changes you had made to not be
               saved.

             - The remapping of backdrop pictures (via datatypes) is now performed
               asynchronously - I think this is how Workbench does it too.

      #1185  - Removed an unnecessary EraseRect() when refreshing icons - hopefully
               this was the problem of 'background is refreshed twice' that some
               people were complaining about.

             - If you double-click, in name mode, on a file that has a project icon,
               the icon's default tool (if any) will be used to launch the file.
               If there is no default tool, the 'smartread' command will be used.
               This behaviour is now the same as in icon mode.

   09-Mar-96 - Program groups no longer store the icons of the individual programs
               in the group directory. Program group files are now used entirely
               as references to the real program. This means that if you bring up
               the icon information requester on a program group file, it is
               the real program's icon you will be manipulating.

               The only exceptions to this are Rename and Delete - Rename on a group
               program allows you to change its name within the group, and Delete
               obviously removes it from the group. In effect, program groups are just
               like a collection of left-out icons.

               The latest update.module automatically deletes any .info files in
               your dopus5:groups directory and converts the group data files to the
               new format.

             - Selecting 'Add' or 'Late' in the Assign requester could cause a crash.

             - Key presses were not blocked properly when dragging an icon around -
               pressing space would cause a lock up, and pressing pageup/pagedown/etc
               would do all sorts of strange things.

             - Pressing keys in a lister to scroll to a file will now take
               you to a directory if the first letter in the 'match string' is
               in upper-case (ie this is now the same as the old behaviour).

             - Dragging multiple icons around (actually, the refresh that happens when
               you release them) may now be faster on CyberGfx systems (I can't tell).

   10-Mar-96 - 'lister visible off' no longer aborts any function in progress.

             - The state of the 'Listers/View As/Name' menu item was getting confused.

   11-Mar-96 - The Path Format system has changed, maybe it's more logical now.. who
      #1186    can say?

             - If you used the WBPattern editor to change the background pattern
               from a picture to an empty pattern, DOpus would not notice.

             - The loading of background pictures is now even more asynchronous.

             - If you did a Clean Up on a lister with no icons in it, it would
               generate a whole bunch of enforcer hits.

             - Error requesters for the Format program were coming up on the
               Workbench screen instead of on the DOpus screen.

   12-Mar-96 - A couple of shortcut keys were used twice in the button bank editor.

             - 'SimpleRefresh' was also spelt as 'Simple-Refresh' in one place.

             - The problem of items 'dropping off the mouse pointer' when dragging
               things in the menu editor may be fixed - please test.

      #1187  - 'Put Away' from the icon popup menu was doing a Delete instead of a
               Put Away (had the same effect, but gave you a warning requester first).

   13-Mar-96 - Fixed lock-up that could occur when you selected Put Away from the
               icon popup menu.

             - You can now Leave Out programs from within Groups (both via the
               popup and the Icon menu)

             - Entering a non-existant filename for an image button in the button
               editor now clears the image display correctly.

             - Some keyboard shortcuts work now that didn't before (like 'f' for the
               Font option in Environment/Desktop, and 'd' for Dragbar orientation
               in the button bank editor).

      #1188  - You can no longer create an assignment for ':' using the Assign
               command.

   14-Mar-96 - The ViewFont program now has a pulldown menu, and a Save Settings
               option, to let you save the window position.

             - The MakeDir command now limits names to 30 characters (instead
               of 31), and also will truncate names to 25 characters if you
               select the 'with icon' option.

             - It is now possible to delete directories with filenames of 30
               characters (this was due to a bug in the OS MatchFirst/MatchNext
               routines, which I have worked around). The OS seems to have
               several bugs when dealing with directories of 30 characters.

             - If you create a new button bank and then Cancel the bank editor,
               the new bank is now closed automatically.

             - Added some extra protection so that now, hopefully, Opus shouldn't
               crash if you iconify a lister while it is reading the icons in
               (was it Frederic who reported this?)

             - If the name of a file used as a button image ends in '.noremap',
               that image will not be colour remapped. This was the easiest way
               I could think of to allow you to disable remapping for certain
               images. I might look at making it a switch in the button editor,
               but this raises some problems with the way the internal image
               caching system works. So, to turn off image remapping for an
               image, simply rename the file and give it a .noremap suffix.

      #1189  - You can now use {RS} (as opposed to {Rs}) for a secure string
               requester (for passwords, etc).

      #1190  - Fixed enforcer hits if you had an iconified lister saved in the
               environment.

   15-Mar-96 - Fixed a bug that would make Opus hang when starting up, if you
      #1191    had a left-out icon with the same name as another icon (eg a
               group or device).

   16-Mar-96 - Fixed an illegal RectFill() in the button editor that caused a
               crash under 37 (under 39 this sort of thing is protected).

             - Fixed requester resizing (eg the pop-up function list) under 37.

             - 'd' was used as a hotkey twice in Options/Copy.

             - Removed the 'check free space' option from Options/Copy (since
               it doesn't actually work).

             - 'i' was used as a hotkey twice in the Edit Class requester.

             - Rearranged some hotkeys in the Filetype editor, so that
               'Del' action now has a hotkey.

      #1192  - If you have a hotkey set for any user menu item of rcommand +
               something, the hotkey will be displayed in the menu using the
               standard amiga symbol.

   17-Mar-96 - You can now drop files onto a tool icon within a lister to run
               that tool (this used to only work on tools that were left-out).

             - Several changes to IconInfo :

               You can now disable/enable tooltypes (by adding or removing
               parentheses) by double-clicking on the tooltype line.

               NewIcons image tooltypes are not displayed in the tooltype list
               (anything after a line reading *** DON'T EDIT THE FOLLOWING LINES!! ***
               is hidden).

               If there is a tooltype similar to »» Icon by Fred Bloggs ««, the
               author's name is extracted and displayed in the title bar of the
               window, and that tooltype is not shown in the list.

             - Opus now recognises changes to disk icons (eg turning the borders
               off) again - no idea when this stopped working.

             - Middle mouse button in text viewer now does copy to clipboard.

             - Text buttons now have a reasonable minimum size even when the
               window borders are turned off.

      #1193  - You can now hold shift when double-clicking on a file in name mode
               to ignore any default tool that might be set in the file's icon.

   18-Mar-96 - If you just changed the name of a button bank without modifying
      #1194    any buttons, Opus would not 'notice' it had been change and would
               not save it if you clicked the 'Save' gadget in the bank editor.

   21-Mar-96 - Fixed the underscore for the hotkey in the 'Dragbar Orientation'
               string in the button bank editor.

             - Removed the 'Expand paths' option from Options/Caching since it
               didn't work anyway.

             - Fixed bug in the string gadget class that would drop the last
               letter of the string if the string was the maximum length (this
               caused Leo's problem in the complex Select requester).

             - Fixed Leo's little bug where you could release the mouse button
               over the toolbar arrow and it would act as if you still had the
               button held down.

             - Icons/Reset now works on listers (in icon mode) and groups.

             - The update.module will now ask you if you want to copy Workbench
               left-outs (from .backdrop files) to Opus. This is mainly for
               people who are installing Opus for the first time. If you want
               to do this with Opus already installed (or just want to test it!)
               delete the update-history file from your dopus5: directory
               before running Opus with the new module.

               The update.module will also reorganise your dopus5:Storage
               directory slightly. Two sub-directories, Modules and Filetypes,
               will be created within it, and any filetypes you have in storage
               moved to the new sub-directory. The Modules sub-directory will be
               left empty, but it's a good place to put things like the
               iconclock.module.

             - Added 'Replace' section to the Options configuration. Moved the
               Verbose replace requester option to there, and added an option
               to turn off the checking of version numbers when a file exists.

             - The 'File exists, replace?' requester now has an additional button,
               only if the above option is turned off. The new button, 'Version',
               allows you to instigate the check for version numbers manually.

             - When checking for version numbers in an existing file, Opus now
               displays a progress window - this window allows you to cancel the
               version number check, which may be useful for long files.

             - Dropping a disk icon onto a lister in icon mode to copy the disk
               now works again.

      #1195  - Fixed a problem when deleting a directory in icon mode (eg
               from the icon popup menu) - the directory's icon would not be
               deleted properly.

   22-Mar-96 - Fixed bug in my custom IFF code that was setting the protection
               bits of any files it read to 'rwd' - it should have only been
               doing this when writing files. You would notice this when
               viewing pictures or playing sounds using the show and play modules.

             - Copy now preserves the datestamp, archive bits and comments of icons
               properly (subject to the flags you have set).

   25-Mar-96 - If you snapshot a lister when it is in icon mode (only - not text mode),
               its position and size are now saved to the icon (if the drawer has an
               icon) as well as the position-info file. This is so you can set up
               window positions with Opus, make an archive and give it to someone who
               doesn't use Opus. This happens all the time, I'm sure.

               Note that icon positions themselves are kept separately from Workbench,
               so even though the windows might be set up right, the icons will
               not necessarily be. The technical term for this is 'tough'.

               This will not change again for this version. Someone had the suggestion
               of using tooltypes to keep the position - this is quite a good idea,
               but it's too late in the development cycle to make this sort of change.
               I'll comment again that all the people complaining about window
               positions being wrong are the people who complained when Opus DID
               overwrite Workbench's position. You can't have it both ways, guys.

             - Wrote a little module (cleanup.module) with one command in it -
               CleanUp. This command will search your position-info and remove any
               directories or left-outs that no longer exist. It will only
               do this if the volume they are on is available (this will stop it
               removing entries for removable media).

             - The hotkey is now shown for menus that have rcommand-shift (eg
               it will distinguish between ramiga-4 and ramiga-$). Note that
               letters can only be uppercase (and case is actually ignored when
               you press the key) - this is the OS' limitation, not mine.

      #1196  - New module - join.module. This gives Opus the long-requested Join
               command. The Join requester allows you to add and remove files,
               and to specify the order they are concatenated in. Note that it
               needs to be run with some files initially selected in a lister
               (you can add and remove once the requester is open).

               The module also has a Split command in it; as yet, this does nothing.

             - Makedir with the READ switch now doesn't show a 'fake' directory
               within the new directory.

   27-Mar-96 - You can now drop palette prefs files (created by the Workbench Palette
               program) onto the Environment editor - when the Palette section is
               visible - to set the OS colours of the Opus screen. This will only
               affect the bottom 4 (and top 4 under v39) colours of the screen, and
               ONLY if Opus is open on its own screen. The User Pens are not affected
               at all by this. The GrabWB button has been replaced with a Load button
               to let you do this via file requester.

             - Added 'Extended lister key selection' option to Options/Miscellaneous.
               This allows you to turn off the field that pops up when you type
               a key in a lister, and restore the old behaviour of instantly scrolling
               to that letter.

             - Fixed problem Dave reported to do with filetypes - as an example, if
               you dragged and dropped 1.lha, 2.lzx and 3.lha (at once, in that order),
               it could fail to do all files correctly.

               The problem was actually caused by having the particular functions
               defined with the Run Asynchronously flag set - this caused them to be
               started async, and Opus was then overwriting the script file with the
               next function before it had had a chance to execute. The name of the
               temporary script file is now changed each time.

             - If you resized the Join requester, any text in the 'To' field would
               be rendered in bold.

             - Added help nodes for Lister/Open Parent and Settings/Scripts.

      #1197  - Format error requesters were appearing on the default public screen
               rather than the Opus screen.

   28-Mar-96 - The Print routine now automatically prints a form-feed after every
               file.

             - The 'Reload each file' flag now works properly (it was reloading files,
               but before they had been acted on - not very useful :)

      #1198  - Running a function with the 'Reload each file' set without a valid
               source directory would cause some hits.

             - If Copy needs to check version numbers, and both files are under 50k
               in size, it doesn't bother putting up the progress indicator when
               looking for the $VER string.

      #1199  - 'Close' from the icon popup menu for iconified buttons and listers
               now has a help node. Also, custom popup menu items for AppIcons
               (like the Colour? option for the icon clock) can now have help.

   29-Mar-96 - When a new disk is inserted, a separate process is now launched to
               examine it and read the icon. This stops the main process going busy
               when you insert a floppy (if it was a CrossDOS disk this could take
               several seconds).

             - Modifying the icon font in Environment/Desktop wouldn't update any
               listers that were currently open in icon mode.

             - Swapped the sense of the shift key around when double-clicking on
               files in name mode - now if you double-click without shift it will
               always go to filetypes; if you double-click with shift held down, it
               will use the default tool in the icon (if there is one).

             - DOpus now ignores disk insertions when the drive is busy (ie has
               been locked by another task - for example, when you are diskcopying).
               This is to stop the disk insertion script being run every time
               you change disks during a copy.

             - The WindowPtr field of programs launched as Workbench processes was
               set to -1, which turned off DOS requesters. This is now set to 0 as
               it should be. Launching of programs as AmigaDOS processes was ok.

      #1200  - Checkmarks are back by popular demand.

   30-Mar-96 - The 'lister wait' rexx command will now block until a lister has
               finished reading filetypes and/or versions (if these are selected
               for display).

             - Icons/Reset now has a shortcut key (T).

             - Listers/View As/Show All now has a shortcut key (;)

             - The 'lister set handle busy on' rexx command can now take a 'wait'
               parameter to force it to be synchronous.

             - Removed excess spaces from the version date display in listers
               (I think this may have only occurred under non-English locales).

             - If you try to open a lister by double-clicking on an icon, and
               that lister is already open, it is brought to the front rather
               than a new lister being created. If the lister is invisible,
               it is now made visible.

             - Added Listers/Un-Snapshot menu item, to remove a lister from
               the position-info file.

      #1201  - Left-amiga V and B are now synonyms for enter/escape in requesters.

   02-Apr-96 - The environment prefs will now load OS 2.0 palette files as well
               as 3.0 files (OS2 palette files are basically ILBMs without a BODY
               chunk, so you could in fact use any ILBM picture for a palette).

             - Popup submenus were coming up the wrong width if you had more than
               one in a menu.

   03-Apr-96 - 'Copy', 'Cut' and 'Export as ASCII' in the function editor would
               all use the _original_ function, and not reflect any changes you
               might have made to it.

             - PgUp/PgDn in a lister now scrolls one line less than one page.

             - Diskcopy now turns the drive light off when it prompts you to change
               disks.

             - The checks in checkbox gadgets are now sized differently, they should
               look a little better when scaled.

             - There is now an option in Options/Miscellenous, to invoke the
               CreateFiletype function automatically when you double-click on an
               unknown file. This replaces the 'Default' filetype, which the new
               update.module will delete from your filetypes directory automatically.

             - If you display filetypes in a lister, any files that can not be
               identified are now marked as "<unknown>" rather than having no
               description.

             - Holding shift while double-clicking on a file in name mode now forces
               the file's default tool (if there is one) to be used, irrespective
               of whether any filetypes are defined for that file.

             - Added help node for Listers/UnSnapshot.

   04-Apr-96 - The 'dopus getstring' rexx commands will now clear the RESULT field
               if an empty string is entered. ** PLEASE ** script writers, check your
               scripts to make sure this hasn't caused any problems.

             - The ScanDir command now has the template NEW/S,MODE/K,SHOWALL/S,PATH/F.
               MODE=icon and MODE=action are valid keywords to put the new lister
               into icon or icon action mode automatically. Without the MODE keyword,
               the lister will open in name mode.

               The code for the opening of listers with the ScanDir command has been
               reworked; hopefully this will solve the problems Leo has been complaining
               about regarding incorrect lister positions. Check it out anyway.

         ***   This should NOT affect the opening of listers in any other way;
               if you notice that listers appear in different positions in another
               circumstance, please report it.

             - The new update.module will reorganise your env: and envarc: directories
               slightly - all dopus environment variables will be moved into their
               own sub-directory. This is just to make it tidier.

             - If you have the environment variable 'dopus/NoIconCaching' set (to anything),
               the icon caching routines in the library will not be used, and each
               icon will remain in memory when it is loaded. This should fix the
               'colour cycling' problems some people have reported when using NewIcons.
               Keeping each icon in memory uses more chip ram, but that's life.

               This variable is only looked for when the dopus5.library is opened, so
               you will probably need to reboot after setting it to notice any change.

             - You can no longer Assign to a null directory.

      #1202  - Fixed a LONG standing bug that Edmund reported, where an incorrect number
               of User Pens would be shown in the palette editor under some circumstances.
               By magic, this also fixes the problem where cancelling the environment
               editor could cause the palette to be reset to the wrong colours.

   05-Apr-96 - Fixed enforcer hits when loading a certain lister menu as a button bank.

             - The update.module is now run as the first thing when Opus starts up,
               rather than later on when all the other modules are being examined. This
               is so that Opus will notice any changes the module might make (like
               renaming environment variables) without have to be re-run.

             - Icons used in button banks are now 'remapped' like icons in listers
               are; this is not true remapping, but the planes are shuffled around so
               that they use the top four colours in the palette, rather than colours
               4-7. This is for 8 colour icons on a screen with more than 8 colours.
               You should now be able to discard MWBD or other palette-changing hacks.

             - If a backdrop picture (specified through the WBPattern editor) has
               a .noremap suffix, it will not be remapped. The name of the picture
               itself must have the suffix, not the prefs file.

   07-Apr-96 - Re-arranged the command templates for copy, copyas, move, moveas,
               duplicate, encrypt, makelink and makelinkas.

             - Fixed bug where if you renamed a directory, and you had a lister
               open showing a directory that name of which started with the name
               of the directory you renamed, the path visible in the lister would
               be changed incorrectly. Confused? Good :) This was a bug of Leo's..

             - You can now drop programs on the menu editor (into the item or
               sub-item list) to automatically create entries (like you can in
               the button editor). The only thing you can drop onto the menu list
               in the menu editor is button files.

             - The position-info file is now kept in the dopus5:System directory,
               as is the ftp.config file. These will both be shifted automatically
               by the update.module.

             - The path format editor now has a cycle gadget rather than a check
               box, to allow you to specify what mode you want the lister to
               appear in.

             - Fixed ScanDir NEW so it uses snapshotted lister positions properly.
               This should solve the last of Leo's problems (ah, who am I kidding? :)

   08-Apr-96 - The version routines now understand binary file formats, and can
               get version information out of libraries, devices, etc. that don't
               have a $VER string (a $VER string has priority over the other format)

             - Fixed Edmund's drag'n'drop problem with custom handlers (Test.lha in
               RAM:, with his HandlerTest.dopus5 script).

             - The 'dopus_show' environment variable is renamed by the update.module
               to 'dopus/ShowUseDatatypesFirst'. The contents of this variable no
               longer matter. You will need to delete your update-history file to
               have this change made for you (or just do it yourself manually).

             - The 'dopus/NoIconCaching' environment variable has been replaced
               by a switch in Environment/Desktop. You can delete the variable.
               This setting is still only looked at when DOpus first runs, so you
               will need to re-run DOpus (or reboot) to notice any change.

             - If the variable 'dopus/3DLook' is set (to anything) the iconify gadget
               will be rendered in the 3d-sysihack type style (the check for sysihack
               is still performed so if this is what you are using you won't need to
               set the variable).

             - Added 'Store' button to filetype editor. This will remove the selected
               filetype from the list, and when you choose 'Save', the filetype will
               be moved to the Storage directory.

      #1203  - The 'Filetype Sniffer' option now calls FindFileType instead of
               CreateFileType, and a confirmation requester is shown beforehand.

   10-Apr-96 - You can no longer change lister modes while the lister is busy - this
               was just causing too many problems.

             - Set the 'dopus/UseWBInfo' environment variable, and the icon.module
               will call the OS WBInfo() routine to do icon information (this only
               works under v39, and may only work if you have Workbench running).
               This will let you use patches like SwazInfo.

             - If you double-clicked on a file that had a filetype defined, but had
               no double-click action set, it would trigger the filetype sniffer.
               Now it just falls through to SmartRead.

      #1204  - Added Amiga-W as a shortcut for Icons/Snapshot/Window.

   02-May-96 - Added 'Field Titles' flag to Environment/Lister Options. With this
               turned on, file lists have a title at the top of the lister.
               You can click on the fields in the title to change the sort
               mode of the lister.

             - The 'Key' field in the function editor now interprets your key
               presses and converts them to a string automatically.
               If the capslock key is down, this behaviour is bypassed and you can
               edit the string manually.

             - The names of the scripts can now be localised (configopus.cd).

             - It was possible to iconify an already-iconified lister through the
               'lister iconify' rexx command, an endless number of times.

   04-May-96 - The Path Formats configuration section has disappeared. The only
               two useful functions of this editor are replaced by the following :

                 - Saving lister formats (sort method, etc) is now done from the
                   pop-up format editor (Edit from the lister pop-up or right
                   double-click). This editor has a new 'Save' button that
                   allows you to permanently record the format of that path.

                 - Bringing up listers from hotkeys is now done through the
                   Hotkeys editor (it always could be). The update.module will
                   automatically add hotkey entries for any directories you
                   had configured under path formats.

               Hopefully this change will remove a lot of the confusion
               surrounding the path formats editor.

             - Listers now have a little lock symbol in the title bar (next to
               the iconify gadget). When this is selected, the list format in that
               lister will be locked - it will not change if you read in a path
               that has been defined as having a specific list format.

             - Might have fixed a problem that occurred with the FTP module (and
               some rexx scripts) when Opus filled all its buffers.. concerned
               parties please test.

   05-May-96 - If you pasted a function into the right or middle button function
               of a button, it would get lost when you pressed Use.

             - The CleanUp function now looks for position-info in the right place.

      #1205  - If an AppIcon was removed, or its imagery changed (in the case of
               an iconified lister going non-busy), while you were dragging it,
               Opus would lock up.

   08-May-96 - Fixed a couple of problems with the field titles

             - The lister format editor now has a 'Reset to Defaults' button.
               If you select this, and then Save, the format settings for this
               path will be removed from the position-info file, and the default
               settings (from Environment/Lister Display) will be used.

   09-May-96 - Added 'Always use Snapshot position' to Environment/Lister Options.
               With this flag turned on, new listers that are opened will always
               come up in the position and size they were snapshotted to, instead
               of in the last position you had them in.
               Note that when you turn this flag on, any listers that you have
               already opened and moved this session will not respect it until
               you do an Icons/Reset on the main window.

             - If you change the list format with the internal 'Set Sort', etc
               commands, the changes are now remembered when you change
               directories.

             - Opus now accepts the v36 diskfont.library instead of requiring v37.

             - Added some new {} sequences to commands :

                  {s!}       - uses source path if present, but doesn't require it
                  {d!}       - same for destination
                  {f!}       - first file if present, but not required
                  {o!}
                  {F!}
                  {O!}       - etc...

               This allows you to have, for example, a button to run DPaint with
               a filename if one is provided, or without a filename if not.. eg:

                  Workbench    Apps:Gfx/DPaint {f!}

               Using the old {f} command, the function would only be launched if
               there was a selected file.

   10-May-96 - Added 'Don't remap icons' flag to Environment/Desktop. This allows
      #1206    you to stop Opus from remapping 8 colour icons to the top and
               bottom 4 colours in the palette.

   11-May-96 - Implemented the Split command (part of the join.module). Its
               operation is fairly self-explanatory; you select the input file,
               the output directory, the 'stem' of the output files (to which
               .000, .001, etc.. is appended) and the size of each chunk.
               If the destination directory is a floppy (either a trackdisk.device
               or a mfm.device disk), it will prompt automatically for a new
               disk to be inserted as necessary.

   12-May-96 - Added 'ARexx modules' facility. See the test-command.dopus5 script
      #1207    in the modules directory for more information.

   13-May-96 - The clock now stops when the right mouse button is held down; let's
               see if this fixes the menu bar bug.

             - The keyword 'locked' in the result of a 'lister query position'
               command was not properly separated from the position information.

      #1208  - In fixing the 'inactive' message bug it seems the inactive message
               got broken; it should be fixed (hopefully this hasn't reintroduced
               the original bug) - Andrew please test.

   18-May-96 - Fixed a problem where if you were using a background pattern (not a
               picture), the rendering of the background could be offset by
               one pixel (and so the pattern wouldn't line up).

             - Rendering of background patterns and pictures should now be much
               faster, especially in the case of a small image that has to be tiled
               many times over the background.

             - Deleting a link to a directory now only deletes the link itself,
               rather than the contents of the directory.

             - CheckFit now gives a more meaningful result when used with RAM:
               as a destination (its probably not 100% accurate but should give an
               idea).

             - The lock gadget now moves to the right properly when a lister's position
               is locked.

             - If you created a new directory with an icon, the lister would scroll
               to bring the icon into view instead of the directory.

             - Enhanced the 'dopus addappicon' command. The new command template
               (which isn't fully compatible with the old, but since I don't think
               anyone has actually used it yet shouldn't matter) is as follows :

               dopus addappicon <port> <label> <id> [pos <x> <y>] [icon <filename>]
                                                    [quotes] [info] [snap] [close] [local]
                                                    [menu <stem>]

               The parameters are :

                   port    - the port name to send messages to
                   label   - the icon label
                   id      - your own ID for the icon
                   pos     - position for the icon
                   icon    - pathname of icon file (without the .info)
                   quotes  - specify this keyword if you want filenames to be quoted
                   info    - if you want Information to work on this icon
                   snap    - if you want snapshotting to work on this icon
                   close   - if you want "Close" instead of "Open" in the popup menu
                   local   - if you want the icon to be local to Opus (not appear on WB)
                   menu    - name of a stem variable containing your own menu items

               The stem variable must be in the following format :

                   stem.COUNT - number of items
                   stem.0     - item 1
                   stem.1     - item 2
                   etc..

               Messages you will get (string in Arg0) are :

                   doubleclick  - icon doubleclicked, or Open selected from menu
                   dropfrom     - drop from a lister (or elsewhere)
                   snapshot     - snapshot
                   unsnapshot   - unsnapshot
                   removed      - Opus has quit
                   info         - information
                   close        - Close selected from popup menu
                   menu         - User-supplied menu item selected in the popup
                   menuhelp     - User pressed help key on said item

               If one of your own menu items is selected, its number will be returned
               in Arg2.

               See the original section on the addappicon command in this history file
               for more information, plus the example script.

             - The filerequester for 'Select Icon' in the filetypes config had the
               wrong title.

             - Fixed an enforcer hit in the menu editor.

      #1209  - Added 'quick' option to the 'lister wait' command. If you do
               'lister wait <handle> quick', the command will return immediately if
               the lister is not busy, instead of waiting for 2 seconds.

   22-May-96 - (ViewFont 1.4) fixed a problem with ViewFont and fonts that only
               had characters in the range above 127 (it would go into an infinite loop)

             - I had changed the 'CD source' and 'CD destination' flags to not
               requiring a source or destination, only using one if it exists. This
               wasn't thought through properly, and the old behaviour has now
               been restored.

             - If you had 'Options/Locale/Thousands Separator' turned on, and the
               locale for your country specified a space as thousands separator,
               the field titles could be sized incorrectly. This has been fixed.

             - The problem when dragging from the menu editor, etc, with items
               dropping off the mouse pointer may have been fixed; please test.

             - Pressing + in the menu editor would allow you to add an item even
               if the 'Add' button itself was disabled (eg in the lister menu editor).

             - Changed the hotkey for Clear in the button clipboard to C.

             - There was a slight problem with the ARexx modules concept in that in
               a default system, ARexx isn't run on startup (it is also often in
               WBStartup). This meant that if you were running Opus as Workbench
               replacement, ARexx would not be around to initialise the modules.
               Opus now looks for ARexx when it starts up; if ARexx is already
               running it initialises the modules as normal. Otherwise, it sets
               up a hook and as soon as the REXX port appears for the first time
               it scans and initialises any ARexx modules.

      #1210  - Opus now also puts notification on the Modules directory. If you
               add a new module to the directory, or modify an existing one,
               Opus will re-initialise that module automatically.

             - Opus now warns you when you quit if the lister menu, user menu,
               scripts or hotkeys have been changed, and gives you a chance to
               save them.

             - Added 'lister request' and 'lister getstring' commands. These are
               identical to the 'dopus request' and 'dopus getstring' commands
               except they take a lister handle and will center the requester
               over the given lister.

             - The drag'n'drop bug with things falling off the mouse pointer
               seems to be fixed.

             - The buttons in the Assign requester were all out by one (so that
               'Assign' did 'Add', 'Add' did 'Path', etc..)

             - The 'Don't remap icons' option was not displaying the third plane
               of 8 colour icons.

             - The 'Abort' and 'xx of xx' strings in the progress indicator are
               now localised properly.

             - ViewFont now sets its PROGDIR: to be the dopus5: directory, so it
               should now find its catalog file properly. To clear up confusion,
               the catalog file is called 'viewfont.catalog'.

             - Localised Script names now work properly (that's what you get for
               not testing something)

             - If you created a pop-up menu function for a button, then drag'n'dropped
               it onto an empty mouse button item, the pop-up menu would only be
               cleared, rather than deleted altogether.

             - 'Command   Copy foo ram:' would cause an enforcer hit (ie if there               
               was no source selected)

      #1211  - Dragging and dropping from the device list was broken (somehow).

   27-May-96 - The show.module now works with CyberGfx screenmodes (it should also
               work with other graphics card software, but nothing else has been
               tested). Yes, it's very slow. No, I'm not going to do anything about it.

               It will also now show 24 bit ILBMs (well, it shows the one I tested it
               with). It tries to get a 24 bit screenmode (ie it helps if you have
               a graphics card that supports it); if not, it should just drop back
               and show as many planes as possible. Note that this will make pictures
               look pretty strange, but I guess its better than nothing.

   28-May-96 - The string you got back from 'lister query flags' was not properly
               formatted (the flag strings were not separated by spaces).

               Note (for Leo's benefit) that the 'lister set flags' command does
               work properly; any changes you make are not used until you
               execute a 'lister refresh' command on the same lister (this is
               in the manual :)

             - The ARexx requester functions would cause a whole heap of hits if
               executed while Opus was iconified. This has been fixed. The behaviour
               of Opus to Rexx commands while iconified is generally undefined;
               there's stuff that will work, and possibly stuff that won't. In
               general it's not encouraged - caveat programmer.

   29-May-96 - There is now an extra argument for rexx messages sent to trapped
               functions. Argument 7 in the message packet contains the destination
               path string (if any) for the function. This will be useful for
               commands that the user selects a destination for through the
               'Select Destination' requester (ie with no real destination lister
               open). The destination lister handle is still sent in argument 3,
               but if this is 0 you should use the string in arg 7.

               Adding this extra string required a significant change to the code;
               please check that anything you use with a custom handler still
               works (ie FTP, ArcDir, etc).

      #1212  - The format of ARexx modules has changed slightly; see the new
               test-command.dopus5 script for more information.

   30-May-96 - The print.module was looking for the "dopus_print" environment
               variable instead of one in the "dopus" sub-directory. The new
               update.module now renames "dopus_print" to "dopus/Print" (this
               is done with all the other environment variables so you will need
               to delete the update-history file to have this done automatically).

             - The "Create Icons?" option was broken as far as creating icons for
               configuration files goes (it was reading the old environment
               variable too).

             - Join and Split now have command templates;

                  Join  FILE=FROM/M/A,AS=TO/A
                  Split FILE=FROM/A,TO/A,CHUNK/N/A,STEM

      #1213  - Alt-click on a toolbar button when the toolbar has been changed
               via the Set command or from ARexx will no longer edit the toolbar
               (ie you can only edit the default system toolbar by this method).

      #1214  - Trevor, Fred et al, please check if 'mega-bug' is fixed.

    1-Jun-96 - Pressing a key in a device or cache list no longer does anything
               (its behaviour was strange and useless before).

             - Now uses 'env:sys/def_kick.info' for busy and bad disks like
               Workbench does.

             - Selecting a new toolbar through the 'Edit Lister Toolbar' function
               and then saving the environment did not record the name of the new
               toolbar (so you were unable to change it permanently from the
               default). This has been fixed.

      #1215  - "Add 'version' to the lister format in the middle somewhere. If a
                directory has no version information, then all sort buttons after
                the version position become nonfunctional" - fixed.

    2-Jun-96 - Enforcer hits if you ran the CleanUp command from ARexx while
               Opus was iconified.

             - If you repositioned an icon so it was partly off the screen
               (with Backdrop mode set) it would be redrawn incorrectly.

             - The minimum size of listers is now large enough to leave all the
               gadgets in the title bar of the window still visible.

    4-Jun-96 - If you try to execute a function that requires a module, and the
      #1216    module in question can't be opened, a requester now appears
               informing you of this.

    6-Jun-96 - The Hide and Reveal commands now allow any other commands following
               them to be executed.

             - When IPrefs wants to close the Workbench screen, Opus will now
               wait for up to 1 second to give other windows the chance to close
               themselves.

   10-Jun-96 - The Modules directory is now not searched for ARexx modules until
               Opus is up and running (it used to be searched during the startup
               procedure). Hopefully this will fix the enforcer hits a couple of
               people have been experiencing on startup, plus also solve the
               icon positioning problems Leo and others have been having with
               rexx scripts that add AppIcons.

             - Minimum lister sizes fixed for name mode.

      #1218  - The problem of enforcer hits when changing screen modes, font,
               etc.. seems to be fixed.

   11-Jun-96 - The lock gadget now has a border.

   12-Jun-96 - Fixed the illegal address errors Dave was getting (oops :-)

             - Improved the algorithm for placing of unsnapshotted icons.

             - The Scripts and Hotkeys editor windows are now resizeable.

             - When you toggled Backdrop on or off the lister toolbar was
               being needlessly remapped. This took some time and also
               caused the colours to go awry occasionally.

             - Sped up the image remapping routines.

   13-Jun-96 - Rewrote the ARexx routines, and fixed a potential problem;
      #1219    see if this fixes Troels' and Edmund's problems.

   14-Jun-96 - Fixed a couple more slight ARexx problems (probably nothing
               noticeable).

             - Tidied up the icon placement routines a bit more.

      #1220  - Fixed a bug that crept in which could make listers a random
               height when brought back from being iconified.

   15-Jun-96 - Lister/Close (or rcommand+k) can now be used to close a group,
               as can shift-escape.

             - Unsnapshotted name mode listers now use the default lister
               size rather than the size from the icon (if any).
               PLEASE check that all your listers now come up where you expect
               them to (Leo especially - please do a full test of double-click,
               ScanDir, etc.. if you can)

             - ScanDir command template is now more logical (PATH,NEW/S,MODE/K,SHOWALL/S)
             - Comment command template is now NAME,COMMENT,RECURSE/S
             - Delete command template is now NAME,QUIET/S
             - Play command template is now NAME,QUIET/S

             - The "Set Flags" command (and ARexx equivalent) now support
               /flag to toggle the flag value (eg /hidden)

             - The Snapshot message sent to ARexx AppIcons was out by a few
               pixels.

   16-Jun-96 - Fixed a bug where if you had a button editor open, with one or
               more function editors open, and you closed the button bank itself,
               the editor would lock up with a whole lot of hits.

             - If you use a picture for a backdrop pattern, and the picture name
               ends in a ".exact" suffix, Opus will tell datatypes to remap this
               picture using PRECISION_EXACT rather than PRECISION_IMAGE.

      #1221  - The Filetype icon menu (ie the configurable menu items for the right
               button popup over icons) now uses menus configured for all matching
               filetypes (it used to just stop at the first match).

               This means you can set up menu items that are to be used for
               all pictures (Match DT Group   pict), and still have individual
               filetypes for certain types of pictures.

               This also means that you can set up menu items for a default
               filetype (Match Name  #?) that will be used for all types of file.

               This icon menu is now also available from name mode - just press
               and hold the right button over a filename without moving the mouse
               for a short time. If you move the mouse before the menu has
               come up, the lister will scroll like before.

   17-Jun-96 - The RECURSE switch on the Comment command didn't work.

             - Opus now has a progress indicator when starting up instead of
               a boring message (wheeeeee!)

             - Now shows a warning requester if any of the required libraries
               can't be found.

             - Dropping button files or Opus filetypes on Opus when it was
               iconified would cause enforcer hits.

      #1222  - The conversion of Opus 4 configurations now handles hotkeys,
               and also now converts menus to the new multiple-menu format
               (instead of to multiple button files)

   18-Jun-96 - The 'lister refresh' command now takes a 'date' parameter.
      #1223    If this is specified the lister will update its directory
               datestamp, which will stop it rereading itself the next time
               it is activated. (eg lister refresh <handle> date)

   19-Jun-96 - New flag in Environment/Lister Options, allows you to disable
               the right-button popup in name mode.

      #1224  - The palette boxes in the button editor now show the correct
               number of colours if your screen only has 4 colours.

      #1225  - Name mode popups no longer work on the device list (they might
               in the future).

   21-Jun-96 - 'lister set <handle> header' works just like 'lister set title'
               except it changes the text in the 'Files x/y Dirs x/y' bar.

             - Oops :) Snapshotted sub-directory positions weren't being used
               (disks were fine). Fixed.

             - new 'lister addstem <handle> <stem>' command, adds files to a
               lister via a stem variable (you could pass the result of a
               'lister query <handle> entry' command directly to an 'addstem'
               for another lister). The fields that are used are :

                   NAME       - name of entry
                   SIZE       - file size
                   TYPE       - type of entry
                   PROTSTRING - protection string (rwed, etc)
                   PROTECT    - protection value (number, used if PROTSTRING not given)
                   COMMENT    - file comment
                   DATESTRING - creation date and time
                   DATE       - number of seconds since 1/1/78 (used if DATESTRING not given)
                   FILETYPE   - ascii string for filetype display
                   VERSION    - version number
                   REVISION   - revision number
                   VERDATE    - date string
                   USERDATA   - user data (value)
                   DISPLAY    - custom display string
                   MENU       - custom popup menu

               The DISPLAY string allows you to specify a completely custom string
               to display for the entry. None of the other information will be displayed
               if this string is supplied. The maximum length is 256 characters.

               The MENU field allows you to specify a stem variable containing custom
               items for the popup menu that appears when the user presses the right
               button on this entry. Its format is the same as for AppIcon popup menus;

                   stem.COUNT - number of entries
                   stem.BASE  - base ID
                   stem.0     - entry 1
                   stem.1     - entry 2

               If COUNT is set to 0, right-button popups will be disabled for this
               file.

               BASE is a new variable, and is also available for AppIcon menus.
               It specifies the base ID of the ID value sent in the rexx message
               when an item is selected. Ordinarily, the first item will return
               id 0, the second will return 1, etc. If, for example, you
               specify stem.BASE=100, the first item will return 100, the second
               101 and so on. This variable is optional.

               The message packet sent when a menu is selected is as follows :

                   Arg0  -  "menu"
                   Arg1  -  lister handle
                   Arg2  -  entry name
                   Arg3  -  menu item id
                   Arg4  -  "file"
                   Arg5  -  entry userdata

             - User-defined AppIcon and file popup menus now take separator
               bars into account when sending the item id to the rexx handler.
               Eg, if you have :

                               hello
                               ---
                               there

               In a menu, 'hello' will return 0 and 'there' will return 2.

             - Added 'original' parameter to 'command' rexx command. This allows
               you to run an "original" function if it has been replaced in the
               command list by an external modules (external modules which add
               commands to Opus override the internal list).

               This means you could have a module that replaced some Opus commands,
               did something special in some circumstances, and in others just
               called the original function.

               Usage eg,   command original delete ram:temp

             - Added 'lister set <handle> lock' command. This takes two
               parameters currently :

                  lister set <h> lock state [on|off]
                  lister set <h> lock format [on|off]

               'state' allows you to lock the lister to its current state -
               the user will be unable to change it until you unlock it.

               'format' allows you to lock the lister to its current
               display format. Currently this just prevents the user
               bringing up the format edit requester.

               You can string these commands on the one line, eg

                  lister set <h> lock state on format on

               There is also a 'lister query <handle> lock' command to get the
               current state - it takes either 'state' or 'format' as a
               parameter.

             - Added 'lister set <handle> field' command. This allows you to
               set your own strings to be used in the field titles. You can't
               change the nature of the columns in the lister - this just
               allows you to change the heading.

               eg, 'lister set <h> field 0 FileName 4 Notes'

               The number (0-9) specifies which string to replace; counting from 0
               they are : name, size, access, date, comment, type, owner, group,
                          net, version

               Set to an empty string to restore the default. You will need to
               do a 'lister refresh <h> full' to update the display once you
               have changed the titles.

               You can also do 'lister set <handle> field off' to turn field
               titles off altogether, and 'on' to turn them back on again.

             - If you opened a lister and read a directory, and then 1) configured
               the lister to show filetypes, and then 2) after the filetypes had
               been read, configured the lister to show versions, the versions
               would not be displayed until you re-read the lister.

             - There is a new 'fullpath' option for the 'lister set <handle> handler'
               command. If you specify 'fullpath', Arg2 will always contain
               the full path of a file, irrespective of whether it came from
               an Opus lister or not (usually, if the file is from a lister you
               only get the filename itself).

             - Added 'dopus setappicon' command. This allows you to do things to
               AppIcons added with the 'dopus addappicon' command.

               dopus setappicon <handle> text   <text>   - change icon label
               dopus setappicon <handle> busy   [on|off] - make icon busy or non-busy
               dopus setappicon <handle> locked [on|off] - make icon locked or unlocked

               All an icon does when it is 'busy' is change its image to be ghosted.
               When an icon is 'locked', its position can not be changed (ie it
               can not be moved manually, and a CleanUp will not affect it).

             - 'locked' is now also a valid keyword for the 'dopus addappicon' command,
               to make an icon start out as locked.

             - You can now snapshot normal AppIcons! Opus saves the position in the
               position-info file. Any icons that support snapshot (ie dopus-specific
               programs) receive the snapshot message as normal and are responsible
               for setting their own position. Note that Opus can only identify 
               AppIcons by their label, so if an AppIcon does not have a consistent
               label this will not work.

      #1226  - PopUp menus now don't react to a selection until you have moved the
               mouse at least 3 pixels in any direction from the starting position.

   22-Jun-96 - If you changed the pattern via WBPattern prefs while Opus was
               iconified, it would cause some enforcer hits.

             - If you selected Hide while Opus was reading the backdrop pattern,
               it would cause enforcer hits (Hide is now disabled until the
               pattern is displayed).

             - Patterns should now work under v37, and the pattern corruption that
               Andrew was getting might be fixed now. Patterns and pictures should
               now work properly under CyberGfx, and also be much faster.

   23-Jun-96 - If you had a Directory filetype with the drag'n'drop action set to
               ScanDir, and you dropped a directory onto an icon mode lister,
               the display wasn't being cleared before the new directory was
               read in, resulting in overwritten icons. This only happened if
               the new directory was already in a cache.

             - Show was cutting IFF pictures off prematurely.

             - You can now delete the hotkey of a button, menu, etc.. by
               activating the hotkey field and pressing backspace or delete
               twice in a row. The other way is to press caps lock to
               put the gadget into 'typing' mode and delete the string as
               normal.

             - For some reason, good old AFS was returning ERROR_OBJECT_IN_USE
               instead of ERROR_DIRECTORY_NOT_EMPTY when Opus tried to delete
               a non-empty directory (if the latter error code was received
               Opus would then enter that directory and delete the contents).
               Opus now enters all directories to delete the contents without
               trying to delete the directory itself first; this will be slightly
               slower when deleting empty directories, but shouldn't be really
               noticeable.

      #1227  - Fixed a bad bug that crept in that could cause a lock up if a
               lister needed to refresh itself, and you had SimpleRefresh listers
               turned on and Field Titles turned off.

   24-Jun-96 - Added Options/Hide Method/PopKey field to allow you to configure
               the Opus hotkey (the CX_POPKEY tooltype is no longer needed).

      #1228  - DiskCopy now manually serialises (updates the datestamp) of
               FFS and OFS disks it copies. This prevents the problems caused
               by having two identical disks in the drives at the same time
               (an OS bug). DiskCopy only knows about FFS and OFS disk structure,
               and relies on the ACTION_SERIALIZE_DISK packet for other
               filesystems (AFS seems to support this packet).

               The 'Bump Name' option in DiskCopy now works for single drive
               copies (although Bump Name is less useful now that DiskCopy
               can serialise disks itself).

      #1229  - 'Set Mode' was broken.

             - Making AppIcons busy with 'dopus setappicon busy' now stops
               the user from double-clicking or using the icon popup menu.

             - You can now use 'dopus setappicon' to remove the text label of an
               AppIcon.

             - As a special kludge, setting the lister header (with 'lister set header')
               to a hyphen will result in an empty header (too bad if you just wanted
               a hyphen! :)

             - 'lister set <handle> field' now works properly :)

             - The UserData field for the 'lister addstem' command now works
               properly. It is available in Arg5 for popup-menu actions on
               files, as well as for doubleclick messages.

   25-Jun-96 - The position of iconified listers and button banks is now saved when
               you save the Environment.

             - The lock gadget is now the same width as the other title bar gadgets.

      #1230  - Made some changes internally so that a rexx script can now do
               "lister set <handle> busy off" on a lister that it didn't actually
               lock - this is intended for something like Leo's Hotlist script,
               which asks for a source lister but doesn't actually use it if
               the NEW keyword is specified. If there is a source lister open
               and Hotlist NEW is executed, that lister would go busy automatically
               and remain busy until the new Hotlist lister was closed. Now, Leo's
               script can make the lister it is given unbusy if it isn't going to use it.

   27-Jun-96 - Added a new command : 'dopus send'. This command does nothing to DOpus
               itself, but instead makes it easy for you to send a string (of
               any length) to another rexx task (via a message). The format is :

                   dopus send <port name> <string>

               The string is supplied in Arg0 of the message sent to the named port.

             - Busy AppIcons now don't respond to dropping other icons on them.

             - The DOpus popup hotkey wasn't being reset to the default (lshift-lalt-ctrl)
               if you cleared the string in Options/Hide method.

             - If an Icon Action mode lister got the directory from a cache rather
               than off disk, the toolbar and path field would be erased from the
               display until the next refresh.

   02-Jul-96 - The CloseButtons command wasn't allowing any further functions to be
               executed (ie if you had CloseButtons on a button followed by another
               function, excution would stop at CloseButtons.)

   03-Jul-96 - Custom handlers now get 'snapshot' and 'unsnapshot' messages for
               their listers. Arg0 contains the message type, and Arg1 contains
               the lister handle.

             - FindFile now has a "New Lister" button in the requester.

   05-Jul-96 - Toolbars now display non-identically sized buttons correctly.
               This means you can have a toolbar with buttons of different widths
               (although the heights must still be the same). The button editor
               system doesn't support this, and won't (at least for 5.5) so
               editing these banks may be a bit strange, but they look and work
               fine once they are in the lister.

             - The 'dopus read' rexx command can now take a 'delete' parameter,
               specifying that the file is to be deleted once the user has
               finished reading it (this is good for temporary files).

               For example,

                   dopus read delete t:temp-file

   07-Jul-96 - Megabug seems to be fixed :)

   08-Jul-96 - Added a trial lister editing system. This allows you to perform
      #1232    Rename, Datestamp, Protect and Comment functions directly in
               the lister (name mode only!). To activate it, set the environment
               variable dopus/ListerEditing. To edit something, click and hold
               the left button over it without moving the mouse (or, if you have
               a three-button mouse, just click the middle mouse button over it).
               For example, to change a filename, click and hold over the name.
               A cursor will then appear which allows you to edit the item.
               Press return to keep changes or escape to abort. You can also use
               the cursor keys to move up and down lines, and tab/shift-tab to
               move between fields. Control-x and Control-q work to do cut and undo.
               Control-c and Control-v work for copy and paste.

             - The minimum size of toolbar buttons is now 2x2.

   09-Jul-96 - The Play requester now appears centered over the lister (if any)
               the play command came from. You can also now iconify the
               play requester.

             - Opus no longer looks for SoundTracker modules itself. The
               recognition method used by the inovamusic.library was causing
               problems with files being erroneously recognised, and it was
               also slowing down the recognition of other filetypes.

               If you want Opus to recognise mods now, you need to create
               a specific filetype for it. A sample one is including in this
               archive. The new filetype command "Sound Module" will match
               if the inovamusic.library recognises the file as a mod.

             - If you changed the colour for selected files and/or dirs,
               with a lister open, that lister would not notice the change
               for dragging files.

   10-Jul-96 - The 'dopus command' function now has a couple of additional parameters.

               The 'ext' in conjunction with the 'type' parameter allows you to add
               filetype-specific items to the object popup menus (these are now
               known as PopUpExtensions). The 'ext' parameter specifies the text
               to be displayed in the menu, and the 'type' parameter specifies the
               type of object this menu is displayed for. You may have multiple
               occurences of the 'type' parameter (but only one 'ext').

               You can specify either the filetype description or its ID for the
               'type' (the ID is checked first). You can also specify one of the
               following keywords : all, disk, drawer, tool, project, trash, baddisk.

               There is also a new 'private' keyword for the 'dopus command' function.
               If this is specified, the command is added as private, meaning it will
               not show up in the command list.

               Check out the 'arcbrowse.dopus5' and 'check.dopus5' modules for example usage.

   11-Jul-96 - Fixed a rounding error in the 'free space' display in the lister title bar.

             - There is a new 'editing' option for the 'lister set <handle> handler'
               command. If you specify 'editing', lister editing will be enabled
               for this lister. The message your handler will receive on completion of
               an edit is :

                   Arg0  - "edit"
                   Arg1  - lister handle
                   Arg2  - entry name
                   Arg3  - "name", "protect", "date", "comment"
                   Arg4  - new string
                   Arg5  - entry userdata

             - Tab/Shift-tab now wrap-around in from first to last (and vice versa)
               in lister editing.

             - Right-Amiga X, C, V and Q are now supported in lister editing, for
               cut, copy, paste and undo.

   15-Jul-96 - Fixed a bug that would lose memory every time you activated a
               popup menu when the underlying window was not active (eg, you
               pressed the right button on an icon when the window the icon
               was in was not active).

   16-Jul-96 - If you press the middle mouse button to enter lister editing mode
      #1234    over an inactive lister, the lister window will be activated
               automatically.

   17-Jul-96 - Increased slightly the time you have to hold down the left button
               to activate editing mode.

             - Right and Middle-button double-click scripts now do not activate if
               the mouse has been moved more than 5 pixels from the position of
               the first click.

             - Image remapping now uses WritePixelLine8() and is dramatically faster
               (for me anyway). Also, the About requester now uses my own remapping
               routines rather than datatypes and so should work even with the 24 bit
               picture.datatype.

   18-Jul-96 - If you had toolbar buttons with no images (ie empty buttons), they
               would increment in size from the previous button. They now size to
               the same size as the previous button.

   19-Jul-96 - Fixed a bug when deleting files that had drawer icons attached to them
               (in icon mode).

   20-Jul-96 - Iconified listers can no longer be a source or destination. Iconifying
               a lister will turn it off automatically. Uniconifying a lister has
               the same effect as opening a new lister - it will become the source or
               destination only if there isn't one already.

   23-Jul-96 - Fixed an enforcer hit if you changed screen modes while the lister format
               editor was open (Leo's bug).

      #1235  - The middle mouse button is now only trapped over the lister toolbar and,
               if lister editing is enabled, the text area. This should help mmb-shift
               commodities.

   25-Jul-96 - Shift-click can be used to deselect icons in a multiselect.

   27-Jul-96 - Fixed refresh problem if you resized a lister while you had a sticky
               popup menu open over it.

             - Image remapping in the About window now uses PRECISION_IMAGE for better
               results.

   29-Jul-96 - If you added a new item in the menu editor, edited it, and pressed
               "Save" directly without selecting "Use" in the function editor, the               
               new function definition would be lost.

             - The wrap-around function of the toolbar arrow gadget has been changed
               back to the old operation (it will now overlap the previous 'page' to
               ensure as many buttons are displayed at once as possible.)

   30-Jul-96 - Final 5.5 Beta release
      #1236

   02-Aug-96 - 5.5

                                     ----


   05-Nov-96 - The text viewer now doesn't set a bitplane mask when scrolling if
               the bitmap is non-standard. This should speed things on on CyberGfx
               and other chunky screens.

             - On a CyberGfx 16 bit (and greater probably) screen, the lister
               field titles would be invisible when you dragged them.

             - The backdrop pattern routines were using an OS39 call even under
               OS37 ---> BOOM.

             - The 'Filter Icons' flag is now ignored in the Icon modes.

             - The dopus5.library AsyncRequest() function was losing 32 bytes.

             - If you set the environment variable dopus/NoNoLabel, this will
               disable label-less icons. A couple of "real" users have been
               reporting that their icons are showing up with no labels -
               obviously the special bit that Opus uses is set.

             - If you set the environment variable dopus/NoIconBorders, all
               icons will be rendered without borders.

             - If you tried to Read a file that had the 'read' protection bit
               cleared, the text viewer would crash.

             - The text viewer was losing 96 bytes.

             - The IFFOpen() routine in the dopus5.library now fails in
               safe mode if the existing file is read-only. (SDK issue)

             - The command "Devicelist NEW FULL" would incorrectly fall back
               to a standard devicelist if there were any source listers open.

             - In functions like "FastView {O!} INFO" the end of the command line
               is no longer lost if there are many files selected.

             - You can now control the time delay for popup menus (ie the time
               it takes a sub-menu to open). Set the environment variable
               dopus/PopUpDelay to a value indicating the delay (this is
               roughly measured in 50ths of a second). The default is 10
               (or about a 5th of a second).

             - The 'CopyTo' menu has been expanded so you can now 'copy' to
               ARexx scripts. To do this,

                   a) Create an ARexx script in dopus5:system/CopyTo
                   b) Set the comment of the script file to be the name that
                      you want displayed in the menu
                   c) Set the Script protection bit of the script file

               eg,

               > list dopus5:system/copyto
               TestScript.dopus5            135 -s--rw-d Today     00:07:12
               : Test ARexx Script

               > type dopus5:system/copyto/testscript.dopus5
               /* A test of a CopyTo script */

               parse arg filename portname source
               options results

               str="'File : "||filename||"'"
               dopus request str "Ok"

             - DOpus now fully supports NewIcons when used in _button banks_.
               It uses the newicon.library if it is present to remap the buttons
               correctly.

             - DOpus now allocates the bitmaps for backdrop pictures as 'friend'
               bitmaps of the screen. On machines with graphics cards this will
               result in faster refreshing of the screen, and in some situations
               the use of fast memory instead of chip memory (basically it will
               use the same memory as the screen does). Note that this works with
               both the v43 24-bit datatype, and the old picture.datatype. This
               should also mean that you can now have full 24 bit backdrops
               using the v43 datatype, rather than a dithered 256 colour image.

             - The icon positioning algorithm has been rewritten AGAIN. I'm very
               happy with the new routine. It positions new icons horizontally
               rather than vertically, like it used to, and is MUCH quicker and
               smarter. Let me know what you think of it.

             - If the 'Prefs' field in Environment/Display Options was empty,
               and you clicked the ! gadget to edit the pattern, it would
               pass a bad filename which would result in an error requester.

             - The text viewer now lets you configure different editors for
               normal, ansi and hex modes.

             - The text viewer now loads files in chunks of about 64k, rather
               than one big allocation. There is also a progress indicator
               when loading files greater than 64k, which allows you to abort
               the load.

             - You can now add a trap for all internal commands using a *,
               eg   dopus addtrap * myhandler

             - There is a new filetype maching command - Disk. This allows
               you to match a disk (similar to Directory for directories).
               It can optionally take a filesystem ID to match a specific
               filesystem.

               Eg,      Disk               - matches any disk
                        Disk DOS1          - matches standard FFS disk
                        Disk DOS?          - matches any DOS disk
                        Disk MSD0          - matches a CrossDOS disk

               Currently, none of the events for Disk filetypes are used,
               but you can use this to add items to the icon popup menus,
               and also to set the default disk icon for a particular
               file system.

             - Added 'lister reload' command to reload (or load for the
               first time) a file in a lister. For example,

                     lister reload 12381928 'filename.lha'

               If the file previously existed in the lister, the user
               data, user menus and version information of the file is
               preserved (please test this someone - Leo!)

             - When dragging icons, the mouse now has to move at least 3
               pixels from the initial click position before the icon
               will start to move.

             - Added 'lister <handle> query window' command to get the
               window pointer of a lister. This is the address (in base 10)
               of the window structure, or 0 if the lister has no window.

             - There is a new flag for the ModuleInfo definition in Opus
               modules; MODULEF_CATALOG_VERSION. If this flag is set,
               the 'ver' field of the ModuleInfo structure is used to check
               the version of string catalogs. This only applies if the
               module uses the standard modinit.o code. (SDK issue)

             - Added routines to the dopus5.library that let you get and
               set stem variables for ARexx messages from C (see SDK).

             - DOpus 5.5 copied icons using GetDiskObject()/PutDiskObject().
               There turned out to be a few problems with this method, so
               now it copies icons like any other files (straight byte copy).
               However, if you set the dopus/SmartIconCopy flag, it will
               copy them with Get/PutDiskObject() like before.

             - The 'dopus command' rexx command now supports wildcards in the
               'type' field, allowing you to add menus to multiple filetypes
               at once. For example,

                   dopus command "Unpack" program "Unpacker" 'source'
                         ext 'Unpack..." type a*

               This would add the 'Unpack...' menu item to all filetypes
               with IDs starting with a. Full wildcards are supported.

             - In some circumstances DOpus would set a result string for
               an ARexx message even if it didn't request one.

    8-Nov-96 - The text viewer would crash if you tried to read a binary
               file (oops :)

             - Fixed the crashes with ArcDir, etc (it was related to the
               new rexx variable functions added to 5.1300)

             - The dopus5.library now monitors the device list itself, rather
               than relying on the system to generate disk change events.
               This means that the disk inserted/disk removed scripts now
               get notified when any disk is changed (eg cds, removable
               hard drives, etc), instead of just for floppies.
               It took some fiddling to make this work properly, and to also
               keep bad disk notification working as well. Please check all
               is as it should be.

      #1301  - The 'lister reload' command now has an 'update' flag, to make
               it update the lister datestamp (to save unnecessary reloading).
               eg, lister reload <handle> <name> update

   18-Dec-96 - Fixed problem that was stopping the MUI titlebar popup menu from
               working.

             - The iconify gadget in the text viewer now works.

             - If you selected a 24 bit screenmode in Environment/Display Mode
               and dragged the colours slider to the far right, Opus would
               crash.

             - The {Ql} parameter now works when used in a filetype popup
               menu function. {Ql} also now works through the filetype
               command system (eg "command source <handle> user4" - Frederic)

             - In some languages (eg Swedish) name substitution in the date
               field in listers resulted in incorrect padding between the date
               and time.

             - You can now configure areas on the main window screen in which 
               certain types of icons will appear, and the priority they will
               appear in. The Icon Positioning... option from the Settings
               menu enters a mode that allows you to create "icon positioning
               areas" by clicking and dragging on the main window. These
               areas (which are represented by windows) can be resized, re-
               positioned and closed as normal. The gadgets within the window
               allow you to configure which types of icons will appear in that
               area, and the priority (from 0 to 255). These areas are
               saved in the environment file.

             - Filename length limit increased from 30 to 31 characters.

             - The 'Disk Information' item in disk popup menus is now disabled
               for bad disks.

             - There is now a 'nopopups' keyword for the 'lister set handler'
               command to disable all file popups in that lister.

             - If you copied a whole function from the function editor, and
               then tried to paste it into a string gadget as a text string,
               it would cause the whole system to lock up (this was reported
               by Peter Schulz).

             - Fixed the problem where OpusFTP would complain about commands
               not being implemented (eg All, Configure, ...)

      #1302  - If you tried to drag an entry out of the cachelist by pressing
               the right button it would cause enforcer hits (reported by
               Peter Schulz)

   20-Dec-96 - Removed the extra space in the date column.

             - The Icon Positioning stuff now works properly for Disk icons.

             - The text viewer now maintains the position within the file when
               it is iconified (also when it is put on a new screen).

             - There was a bug in the EXTCMD_GET_ENTRY callback for modules;
               if there were multiple sources and you moved to the next source
               using EXTCMD_NEXT_SOURCE, EXTCMD_GET_ENTRY would stop returning
               filenames.

      #1303  - The 'nopopups' flag for 'lister set handler' now works. Also,
               if you have added your own popup menu to an entry it will
               be shown even if the nopopups flag is set.

   21-Dec-96 - {Ql} was broken which meant ArcDir in Getdir mode didn't work.

      #1304  - Fixed the date display in listers.

   22-Dec-96 - Fixed the bug where if you inserted a disk, opened its lister,
               removed the disk and then closed the lister, the disk icon would
               not disappear.

             - Also, if a disk was in the drive when Opus was run, and then you
               removed the disk, the icon would not go away.

             - Entering the date in the Datestamp requester, lister editing mode,
               or in a range for the complex Select requester now respects the
               date mode set in Options/Locale.

   23-Dec-96 - Fixed the problem where the first iconified lister would go to the
               extreme top left corner of the screen.

             - The icon position areas now have a minimum size of 40x40.

      #1305  - Fixed problem where the icons would get confused if you had two
               disks with the same names.

   25-Dec-96 - Directory Opus turns 7 today! :)

   26-Dec-96 - If you relabelled a disk, Opus would treat it as a disk change
               event and execute the disk removed and disk inserted scripts.

             - Added REMLISTF_FREEMEMH (4) flag to Att_RemList() function,
               when used in conjunction with REMLISTF_FREEDATA the node data
               will be freed with FreeMemH().

   27-Dec-96 - Added a couple of {} sequences;

                     {o'}, {O'}, {f'}, {F'} - same as {o}, etc, but with
                                              quotes all the time

                     {o~}, etc   - without quotes

               The use of ' or ~ overrides the setting of the 'No file quote'
               flag - without either, the flag setting is used.

               If you use the - to strip the file suffix, it must come after
               the ~ or ' (eg {o'-})

    1-Jan-97 - Happy New Year!

    2-Jan-97 - Fixed some problems with the AppIcon emulation. Hopefully this
      #1306    also fixes the enforcer hits that the iconclock could cause when
               changing screen modes.

             - Fixed final problem in lister icon positioning (Neil - note that
               Leo's idea of Unsnapshotting dopus5:icons/lister.info would have
               worked as well)

    3-Jan-97 - If you started a second copy of Opus running, and then cancelled
               the warning requester, it could cause a crash/enforcer hits.

      #1307  - Happy New Year

   24-Jan-97 - Double-clicking on a program in name mode now runs it as an
               AmigaDOS program (with arguments) even if the program has an icon.
               To run a program with an icon as a Workbench program, in name mode,
               you need to hold down the shift key when you double-click it.

             - Fixed the problem where clipping filenames from listers would
               occasionally stop working.

             - If you brought a popup menu up at the very top or left of the screen,
               the new shadowing could cause problems (enforcer hits under CyberGfx)

             - Fixed Peter Schulz's second function editor cut & paste bug (next? :-)

             - If an iconified lister in icon mode, show all, was saved in the
               environment, then when Opus started up and the icon was double-clicked
               on, the icons within the lister would not appear.

             - Fixed the wrap-around problem on the progress bar when copying files
               > 20mb.

             - Any text after a {O} or a {F} in a function was being lost (bug
               introduced when the {o'}, etc sequences were added)

             - Deleting a link to a directory now just deletes the link, instead of
               the contents of the directory.

      #1308  - Recompiled under SAS 6.57

   27-Jan-97 - The enforcer hits with the akJFIF, akGIF, etc datatypes was because
               Opus normally turns off DOS requesters by setting pr_WindowPtr=-1.
               The ak* datatypes weren't checking this properly and were trying
               to open the progress bar on an invalid screen. The show.module now
               sets pr_WindowPtr=0 when it tries to load a datatypes picture
               (the added bonus is that you now get the progress bar from ak*).

             - Hopefully now when you insert a disk in a drive that has multiple
               devices using it (eg mfm.device, trackdisk.device, etc) you will
               only get a 'good disk inserted' event for the good disk, and no
               'bad disk' events.

      #1309  - The screenmode that the show.module picks for datatypes pictures
               should now be more accurate.

             - GJP Added PORT command to the ftp.module. New templates are
               for the config line:-

                "ANONYMOUS=ANON/S,USERACCOUNT=ACCT/S,ALIAS/K,HOST,
                 ADDRESS=ADDR/K,PORT/N,PATH=DIR,USER/K,PASSWORD=PASS/K"

               so just use a line such as

                 acct alias=testy host=<.> port=1021 user=<name> pass=<pass>

               and for the FTPConnect template

                "HOST,PORT/N,USER,PASSWORD=PASS,DIR/K"

               I have NOT added the PORT option to the normal FTPConnect 
               interactive. If you want other than the normal system "ftp"
               port then you must specify it explicitly. I have also changed
               the way read/writes are done so program is roughly 4 times faster
               than AD's version and does not use up all available memory.

   02-Feb-97 - Fixed the 'Object in use' delete problem that Neil reported and Leo
               identified.

             - Fixed the problem with the disk inserted script where if you had
               a disk open in a lister and ejected the disk, it would trigger
               the script repeatedly until the lister was closed.

             - Added a 'SYNC/S' option to the PLAY command. This makes the command
               not return until the sound has finished, which is necessary if
               you want to then delete the file you are trying to play. Eg,

                     command       Play ram:playfile quiet sync
                     command       Delete ram:playfile quiet

             - Drag'n'drop in icon mode now ignores filetype settings and always
               copies (or moves) the dropped items.

   08-Feb-97 - The file requester for 'Save As' in the text viewer now has the
      #1310    filename filled in by default.

             - GJP: rewrite of FTP module completed. Some more code tidyups
               to speed and improve the whole module.

               A Cache of FTP directories is now available (via the CacheList
               command as usual) and is exclusive to each FTP lister. This is
               now handled by Opus callbacks directly so it has the same
               speed as normal listers. Try it.

               A full GUI front-end has been added to the address book.
               Use the FTPAddressbook command to invoke it as usual. This
               allows you to edit/add/connect to remote sites plus edit the
               general FTP options.

               Some new features added as well, including auto-Index download.
               This looks for files called 'INDEX' or 'Files.BBS' in the dir and
               according to settings will get the index file, cross match
               the comments with the files and add these in the comments field
               of the lister. Please TEST.

               FTP Proxy is not used, yet - anyone know how to do it?
               
   11-Feb-97 - Added page up/down and home/end to listviews.

             - Fixed enforcer hit when dragging from device list.

   12-Feb-97 - Fixed problem where NFS-mounted volumes would not show up as icons
               even though they would show up in the device list.

      #1311  - The Icon Positioning configuration has changed slightly; instead of
               gadgets on the windows, each window now has a popup menu (access with
               any mouse button) that allows you to configure it.

   13-Feb-97 - Added new 'Inline Editing' option to Environment/Lister Options. This
               replaces the old 'ListerEditing' environment variable. Also had to
               shift the lister default size setting to its own area for space reasons.

             - Made some icon positioning changes, should work better with Workbench-
               snapshotted icons now.

             - You can now drop .info files from a name mode lister onto the IconInfo
               requester.

             - Implemented the HFFS_MENU tag for the dc_FileSet() hook. See updated
               SDK docs.

             - In the Filetype editor, deleting the User1 function should no longer
               delete the popup menu entries for the filetype. If you had old (that is,
               really old) filetypes with User1 functions, it's possible the User1
               function will now be lost; sorry about that.

             - If you were in lister edit mode, had made a change and then closed the
               lister while edit was still active, Opus would make the change in its
               buffers but not on disk. The change is now discarded completely.

             - Added 'lister findcache' REXX command. This allows you to find a
               cached directory and display it in the lister, eg

                  lister findcache <handle> <path>

               When it returns, RESULT is set to 0 if the path was not found, or 1 if it
               was found. If the path is found, it will be automatically displayed
               in the lister and you don't need to do any more. If it is not found,
               you'll have to read the directory as normal.

             - Added 'lister clearcaches' REXX command. This command will flush any
               caches that were created by your lister, using your custom handler.
               No other caches will be affected.

             - Functions can now operate on listers that are in plain icon mode.
               However, for the lister to be recognised a source, the lister window
               has to be active when the function is executed. Icon mode listers
               can not be destinations.

               ***** PLEASE test this - you all fought so much for it. If it isn't
               tested properly I will probably remove this for the next release since
               I'm a bit unsure about how well it works. 

      #1312  - 'lister set visible 0' would cause enforcer hits, fixed.

             - Added check for possible divide-by-zero in progress bar calculation.
               Should fix the reported crashes when copying large files.

             - FTP changes:

               - No longer needs socket.library to open the GUI. Connect is ghosted
                 anon password may not be edited if the socket.library is not found.

               - No confirmation requesters - Save is no longer ghosted and it now
                 closes the requester as normal.

               - Changed layout of the GUI somewhat, to make it more like a standard
                 Preferences window. Added a Use button and moved the Options button.

               - Added immediate quit if AmiTCP sends control-C.

               - Fixed Leo's reading config problem problems of USER with no PASS,
                 and problems with ADDR with no HOST.

   20-Feb-97 - Added 'Use Workbench Icon Position' flag to Environment/Display Options.
               When set, this causes Opus to use the same fields in icons as the Workbench
               does to store and retrieve icon and window positioning information.

             - FTP 55.73:

                - Fixed alignment of Debug checkbox
                - Fixed problem with small OK requester - fixed in Opus
                - Fixed problem with config not being updated when Save/Use selected
                - Added NOOP timeouts to keep connection alive
                - Added buffered sgets() from socket routines with 1K buffer -
                  This has potential blocking problems - please test

             - 55.74

                - Fixed saveconfig - was saving then updating it ;-(

             - 55.75

                - Changed the way aborts (control-D) are handled in selectwait() so
                  it now aborts almost immediately and handles it in the correct Unix
                  socket style rather than using AD's SetSignal method

                - Added NOOP gadget

                - Added reporting of failed Write on Get (MikeL)

      #1313  - Unlucky version number or what? :)

   25-Feb-97 - Now supports DPaintV/PPaint AnimBrushes for use as buttons.

             - dopus5.library/FlushBuf() and CloseBuf() now return success/error code,
               prevents data being lost due to disk full, etc (ftp module)

             - Icon border now one pixel smaller vertically, to match Workbench.

             - Holding shift and double-clicking a disk icon now forces a lister to open
               for that disk, even if one was already open (this broke ages ago)

             - Added dc_ShowHelp() callback hook, and the new MODULEF_HELP_AVAILABLE
               flag for the ModuleInfo structure. Also added 'help <helpfile>' keyword
               to the 'dopus command' rexx function.

             - If you set the dopus/WorkbenchTitle environment flag to 1, DOpus will not
               generate its own clock/memory display in the screen title bar. Instead, it
               will call SetWindowTitles() every second with the string "Amiga Workbench".
               This lets it be intercepted by MCP, which allows you to configure the
               title bar display.

             - The old callback system for modules (EXTCMD_xxxx) has been re-implemented using
               the new dc_XXXX() hook system. While the old system of callbacks still works,
               the calls are simply passed to the new functions. Anyone using these callbacks,
               please check that everything is still ok.

   27-Feb-97 - Fixed bug in CleanUp module that was losing AppIcon and StartMenu positions.

             - Added the 'SetAsBackground' command. This works well on the popup menu of a
               "Match DT Group     picture" filetype (see the supplied filetype).

             - You can set the dopus/CenterPicture environment variable to make backdrop
               pictures centered instead of tiled. Set it to 1 for the main window, 2 for
               listers, or 3 for both. DOpus should also recognise the 'center picture'
               setting in FastIPrefs.

             - FTP 56.1 - Fixed timeout problem when getting a reply at the end of a list
                          command. Hopefully!

      #1314  - Might have fixed ARexx memory leak, Leo please test.

   28-Feb-97 - Ooopus.. the HFFS_NAME tag value was 0, the same as TAG_END. The HFFS_xxx tags
               now have new values.

             - Disabling name-mode popups via the ARexx call would also disable the lister
               pop-up menu.

             - Reorganised the Environment editor a bit more. 'Desktop' now just contains
               the hidden drives list (anyone got any ideas to refine this section a bit?).
               A new section, 'Icon Settings', offers the following options:

                    Cache icon images        (now a 'positive' rather than a 'negative' flag)
                    Remap icons              (now a 'positive' rather than a 'negative' flag)
                    Icon Borders             (turn off ALL icon borders, replaces the
                                              environment variable)
                    Show Left-out Arrow      (lets you turn off the little arrow on left-out icons)
                    Use Workbench Positions  (what it says)

                    Desktop...               (edit the font settings for icons on the desktop)
                    Windows...               (edit the font settings for icons in listers/groups)

               Also, the 'Distinct icon positions' flag has been removed. No one knew what it did,
               and I doubt anyone got any benefit out of it, so it's DEAD.

             - DOpus now inherently supports NewIcons. What this means is that you don't need
               to run the NewIcons patch; DOpus will use the newicon.library if it is present
               to remap the icons automatically. You can turn the 'Cache Icon Images' flag on
               in 'Environment/Icon Settings', as DOpus will sense that an icon is a NewIcon and
               will automatically not cache it. You can also use DOpus on its own screen,
               and the icons will be the correct colours.

               ************************** PLEASE TEST THIS!!!! ********************************
               ************************** PLEASE TEST THIS!!!! ********************************
               ************************** PLEASE TEST THIS!!!! ********************************

               Those people who are using NewIcons, please test this WITH the NewIcons patch
               still running, initially. Test Opus for a while like this, and if all seems ok
               with icons, REMOVE the NewIcons patch from your startup-sequence and
               make sure everything still works. Opus should function identically with or
               without the patch running.

               ************************** PLEASE TEST THIS!!!! ********************************
               ************************** PLEASE TEST THIS!!!! ********************************
               ************************** PLEASE TEST THIS!!!! ********************************

               Those who do not use NewIcons, please just keep an eye on your icons to make
               sure nothing weird happens.

             - If an icon's label is more than approximately 1.5 times the width of the icon
               itself (seems like a good ratio to me), it will be now split onto multiple lines.

             - The IconInfo module now has the ability to remove NewIcons image information
               from an icon - access this function from the popup menu.

   03-Mar-97 - The "Command/New" function in the icon menu now works. This allows you to create
               a "command" file, which is essentially a single Opus function in a file. The
               command you create is saved to the new "dopus5:Commands/" directory (which the
               new update.module) creates, and a left-out for it is automatically created on
               the desktop. Double-clicking the left-out command will run it, just like
               clicking a button in a button bank.

               You can edit a command file by right-clicking on it and selecting "Edit" from the
               popup menu. To remove the left-out from the desktop, choose "Put Away" as normal.
               This will not delete the command itself; you must delete it manually from the
               "dopus5:Commands/" directory if you want to get rid of it for good.

               Left-out commands use a default icon (dopus5:icons/command.info) which currently
               is pretty ugly (anyone want to improve on it?), but you can give individual
               commands their own icons by just adding an icon to the file in the "dopus5:Commands/"
               directory.

             - Groups can now contain items that don't have their own icons (this was added so you can
               add left-out commands to groups).

   04-Mar-97 - Start Menus are now much more user friendly. You can create a new Start Menu or
               load an existing Start Menu from the 'Buttons' pull-down menu.

               When a Start Menu is open, you can shift-click on it to toggle the drag bar on and off.
               Also, if you hold down control and right-click on it, it brings up the 'control' popup
               menu even if there is no drag bar.

               The 'control' popup (right button over the drag bar or with control) now lets you edit
               the Start Menu directly, and also set the Image and Label, turn Borders on or off and
               toggle the position of the drag bar. You can now put the drag bar on the right-hand side
               of the Start Menu, which lets you position the Start Menu hard up against the right
               side of the screen.

               There is also a 'Save' option in the control popup which appears whenever anything has
               changed. This also replaces the Snapshot/Unsnapshot options in the popup - when you
               reposition the Start Menu, the 'Save' option will be visible in the popup letting you
               save the new position. Unfortunately, your old snapshotted Start Menu positions will
               be lost.

               Start Menus are now also saved in the Environment file (if you have Save Layout turned
               on), and open automatically when the Environment is loaded.

             - Added the 'Move AppIcons to Tools Menu' option to Environment/Display Options. This
               allows you to redirect AppIcons to menu items in the Tools Menu. Note that changing
               the flag only affects AppIcons added after the change is made.

   05-Mar-97 - A few more changes to the Environment editor. "Lister Size" has been changed to
               "Lister Default", and now also contains the 'Default Format' configuration that was
               previously in "Lister Display". "Lister Display" has been rearranged as you can see
               (if anyone has suggestions for how to lay this section out better I'd appreciate it),
               and now contains 'Field Titles', which has been moved from "Lister Options", and a
               new 'Free Space Gauge' option.

             - The 'Free Space Gauge' option adds a fuel-gauge type thing to listers, showing the
               proportion of space free on the disk. You can set the colour for the 'bar' part of
               the gauge from the "Lister Display" section. The 'foreground' colour is used when
               the bar shows less than 90% full, and the 'background' colour is used when the bar is
               at 90% or above (this lets you have a warning colour when the disk is getting full).

               Gauges are turned off by default for custom handler listers; if you specify the
               'gauge' keyword for the 'lister set <handle> handler' rexx command you can enable
               them (note that the user may still have turned them off in the environment).

             - Added 'Open in New Window' to name mode popup for directories. Also added 'Clean Up'
               to lister popup.

   06-Mar-07 - The Palette sliders in Environment now work on a CyberGrafix screen (I didn't know
               that they didn't work before - maybe it's only CyberGrafix 3.0 that broke them)..
               also note that standard Workbench Palette prefs doesn't work either.

      #1315  - The colour settings in "Lister Display" now have an additional custom pen for each
               of the settings. This pen is completely separate from the standard user/system pens.
               It can be configured individually for each element, providing there are any free
               pens available. At the moment, the custom pen is only implemented by the free
               space gauge, but the other elements will be using it in the next version.

   07-Mar-97 - You can now type ftp:// in the lister path field to launch Opus FTP in that lister.

             - If you set the Output Window title to a string greater than about 28 characters
      #1316    you would get enforcer hits/crashes when a program opened an output window

   08-Mar-97 - Moved "New" and "New Start Menu" into a sub-menu in the Buttons menu, and from
               here you can now directly create graphics or text buttons, without having to go
               through the "Which type?" requester.

   12-Mar-97 - With the WorkbenchTitle environment variable set, the system would lock up when
      #1317    the menu button was pressed.

   17-Mar-97 - Added 'Space Gauge?' option to the lister status popup menu. This allows you to
               enable or disable the free space gauge on a per-lister basis.

             - Added 'Split Long Labels' option to Environment/Icon Settings, so you can now
               turn off the splitting of long icon labels (it's off by default).

             - Implemented a solution to the problem of icons 'moving' when you click them
               to select them. Opus now handles this similarly to Workbench; if the mouse
               button is down for less than a fixed period time (currently about a fifth of a
               second) then the icon is put back in its original position, if it has moved,
               when the button is released.

   23-Mar-97 - You can now press 'y' or 'n' in most requesters for ok/cancel (except where
               it would clash with the actual buttons)

             - You can press escape to kill the about requester.

             - Device list in Environment/Desktop now filters out non-disk devices correctly.

             - 'Store' in Filetypes now does not fail if the filetype already exists in
               the Storage directory.

             - Pressing return twice in an icon action mode lister would make the icons
               disappear.

   24-Mar-97 - Moved icon colour settings to new 'Icon Colours' section in Environment.
      #1318

   27-Mar-97 - If you left out an icon and then renamed it, you would not be able to access
               the object until the next reset (and from then on renaming it would work fine).

             - Renamed 'Environment/Output Window' to 'Environment/CLI Launching' (anyone got
               a better name?) and added 'Stack' setting to this section. This allows you
               to set the default stack for AmigaDOS programs that DOpus executes (the default
               is 4000 bytes).

             - Added 'Open With...' to the popup menu for projects.

             - If the 'Move AppIcons to Tools menu' option was enabled, items added to the
               Tools menu this way wouldn't be removed when RemoveAppIcon() was called.

             - The Hidden Drives list in Environment/Desktop now doesn't discard the entries
               of devices that aren't present. This means that if you have a device that you
               don't always have mounted, its entry won't get lost (or reset) if you go
               into Environment without it mounted.

             - You can now add your own separator bars in filetype popups by specifying a
               label of ---

             - The state of the 'Use Workbench Icon Positions' flag wasn't being remembered
               properly if you turned it on or off.

      #1319  - With 'Use Workbench Icon Positions' turned on, snapshotting an icon would
               actually save a position that was 4 pixels left and 2 pixels down from the
               correct position (so that if you did Select All/Snapshot/Reset the icons would
               appear to jump across).

   30-Mar-97 - The version routine now works a bit better (will find version information stored
               in a data hunk rather than just a code hunk).

    2-Apr-97 - Using a NewIcon for the Lister.info, Buttons.info, etc now works properly.

             - Implemented the underlying mechanism for a Desktop Folder concept. This is a
               directory, DOpus5:Desktop, the contents of which are shown on the desktop.
               The difference between these and left-outs (shortcuts) is that real files
               can be stored in the desktop folder.

               The new update.module will create the desktop folder, and Opus will automatically
               show any icons that are placed in it. As yet there is no user-interface to the
               desktop folder - you have to manually copy files into it using a lister.
               The problem is that we are not sure of a good way to implement this user interface.
               On Windows 95, dragging an icon to the desktop with the left button creates a
               shortcut (similar to Opus), while dragging an icon with the right button brings
               up a context menu that lets you choose 'Copy here' or 'Move here'. Opus doesn't
               have this feature - all we have is left button dragging. The question is how
               to enable the user to place files in the desktop folder easily, while still
               being able to create a shortcut by dragging to the desktop?

             - The icon popup menu now has a 'Create Shortcut' item as well as a 'Leave Out'
               item. 'Create Shortcut' will create an AmigaDOS link to the file, and store it
               in the desktop folder. The result is something that looks just like a left-out.
               If this proves to work it may replace left-outs all together in the future.

      #1320  - Hopefully the problem where the double-click script would stop working is fixed.

    7-Apr-97 - Fixed a problem with icon positioning/layout. As far as I can see, this is what
      #1321    caused John's AppIcon positioning problem, and might also have caused Trevor's
               icon layout problems.

   17-Apr-97 - Implemented custom icon dragging routines for Cybergraphics display modes. Icon
               dragging is much faster as a result.

             - Renaming a file in icon mode that has no .info file now does not complain that
               it can't find the icon.

             - The 'Use Workbench icon position' flag state is now not lost occasionally.

             - The 'Disk' filetype can now match a device name as well as a dos type. eg,

                   Disk   DOS0
                   Or
                   Disk   DH3:
                   Or
                   Disk   CD0:

             - Added 'Location' display to Icon Information requester.

             - Fixed lockups that could occur if you dragged or sized an Icon Action
               mode lister with MCP's solid window moving/sizing enabled.

             - Worked around the problem with Frederic's Install script that could prevent
               a lister from having it's source/destination state changed.

      #1322  - Fixed weirdness with sticky popup menus on the desktop.

             - Fixed some strangeness with the popup menus in icon positioning. Now you
               can only pop them up with the right button, but the window you pop them
               up for does not have to be active.

             - Added Groups and Leftouts to Icon Positioning (so you can define an area for
               groups and left-out icons)

      #1323  - Fixed a problem with the 'lister query entry' rexx command with filenames
               longer than 40 characters in length.

             - Added a cycle gadget to Environment/Desktop, which now allows you to
               set both hidden disks and hidden bad disks. This allows you to selectively
               hide devices that have bad disks in them (so if you had four filesystems
               mounted on the one drive, you could hide all of them for bad disks except
               for one).

   21-Apr-97 - The Desktop folder concept has been polished off some more. The
      #1324    Environment/Desktop configuration section now lets you specify the location
               of the desktop folder (defaults to DOpus5:Desktop/), and allows you to
               enable the pop-up menu that can appear when you drag something to the
               desktop.

               By default this menu is off, and dragging an object to the desktop
               creates a left-out like before. If you turn the menu off, you can choose
               whether you want to create a leftout, or move or copy the item to the
               desktop folder.

               The 'Default Action' allows you to set a default action for the drag
               and drop operation. If set to 'None' the menu will appear, giving you the
               choice of what to do. If you choose an action as the default, then the
               menu will only appear if you hold the shift key down when dragging.
               If not, the action you have selected as default will be performed.

               The 'Create Shortcut' on file popup menus has been removed, as there was
               no point in having both shortcuts and leftouts, and the Opus leftout
               system already works well.

             - Fixed the 'double-click stops working' bug

             - Fixed the icon layout problem (where icon labels would overwrite each
               other if 'Split icon labels' was turned off)

             - Modified the multi-line text routine to only split labels on spaces,
               punctuation characters or on a capital. If there is nowhere to split
               then the label won't be split at all. You can turn off this behaviour and
               force it to split by setting the dopus/LabelForceSplit environment
               variable to 1.

             - The IconInfo requester now shows the location for icons without files.

             - IconInfo will now show the correct icon for the file if the file has no
               icon of its own and one has been defined in the filetypes.

             - If a file is shown with a 'fake' icon (eg Show All Files) and the icon
               has "c:execute" as a default tool, this is now rerouted within Opus and
               run as a CLI process (since c:execute crashes if run from the Workbench)

      #1325  - Frederic's double-source bug seems to be fixed.

   22-Apr-97 - If you set the environment variable dopus/QuickIconDrag to 1, icons will
               no longer be masked when they are dragged. This results in an opaque
               background to the icon (like in Workbench) but is much quicker.

             - Listers now automatically resize themselves when switching between icon
               and icon action mode.

             - Icon Information now works on def_kick.info, def_BUSYdisk.info and other
               icons of type WBDISK.

             - The 'Strip NewIcon Image' option in the IconInfo popup menu now works.
               Also added 'Show NewIcon Image' and 'Show Original Image' to this popup,
               which allow you to toggle the display between the two images.

             - The 'No icon border' and 'No icon label' options in the IconInfo popup
               have been renamed to 'Icon Border' and 'Icon Label', and their sense
               reversed.

             - Added new 'Icon Colours' section to Environment which allows you to configure
               the NewIcons settings within Opus. Currently available options are:

                   Enable NewIcons     - turn NewIcons support on/off
                   Discourage NewIcons - only shows a NewIcon image if there is no
                                         'standard' image (ie if standard image is
                                         less than 5x5 in size)
                   Dither Image        - turns on dithering for NewIcons
                   Pen Precision       - sets the precision for NewIcons

               If you make a change to any of these settings you need to restart Opus for
               the change to become effective.

   25-Apr-97 - The MCP title clock should not flicker now.

             - The internal RENAME command now has a command template : NAME,NEWNAME

             - Thomas Tavoly reported on the public list a problem with the following function:

                   AmigaDOS      cd UUCP:Aminet
                   AmigaDOS      grep >T:INDEX-search {Rs} INDEX
                   Command       FinishSection
                   Command       Read T:INDEX-search
                   AmigaDOS      delete T:INDEX-search

               The problem with this function was caused by the internal 'Read' command
               being asynchronous. A race condition was generated, where quite often the
               file would be deleted by the subsequent AmigaDOS command, before the
               text viewer had a chance to open it.

               This is not so much a bug as a design flaw. The function would have
               worked fine if he had used the internal 'Delete' command instead of the
               AmigaDOS one. It also worked fine if 'Output to Reader' was turned on and
               Opus was allowed to handle the output completely.

               To get around this problem and allow the above sort of function to work,
               I have added a WAIT parameter to the AnsiRead, HexRead, Play, Print, Read,
               Show and SmartRead functions (the Play function already had a SYNC
               parameter which did the same thing). Specifying this option forces the
               function to wait until the command has returned.

             - The 'Directory' filetype no longer matches disks as well as directories.

             - The Desktop Folder now operates in 'View All Files' mode permanently, meaning
               all files are visible on the desktop, whether they have an icon or not.

             - Added 'Copy to Desktop' option to file popup menus.

             - You can now drop files and directories onto a start menu to have them
               added to the menu automatically.

             - The text viewer now uses SetMaxPen() under v39, which should result in faster
               (or at the very least, no slower) scrolling on graphics cards.

   26-Apr-97 - Fixed a problem with the CleanUp routine; icons without borders were not being
               given enough space and so were overwriting icons with borders immediately
               below them.

             - The 'Open With' menu in file popups now remembers up to the last 10 programs
               chosen, and puts them in the menu for you to select from.

      #1326  - Copy/Move to desktop now works with directories as well as files.

   27-Apr-97 - Ghosted icons (eg busy iconified listers) now appear ok if they are NewIcons,
               both with and without a border.

   28-Apr-97 - If you copied a file to the desktop, and the file was on the same partition
               as the desktop directory, the file would be moved instead of copied.

      #1327  - The 'Icon Borders' option in Environment/Icon Settings is now a global
               'default' rather than an override - if you set it, you can then turn borders
               back on selectively from the Icon Information editor.

   29-Apr-97 - Reorganised the Environment editor a bit; things look a bit neater now.

             - Enhanced the display of background pictures. There is a new 'Background'
               section in the Environment editor. You can now choose between using the
               WBPattern Prefs to set up the background picture or pattern, or specifying
               pictures directly. The latter method is only available under OS39 or
               greater, and you cannot specify a pattern, but it is much more convenient.

               As an added bonus, you can now set a background picture for requesters.

               The ? gadget and the end of each of the filename fields pops up a menu that
               allows you to select whether the picture is centered or tiled, and also
               set the remapping precision. The dopus/CenterPicture environment variable
               is no longer effective.

             - The old Display Options section has been renamed 'WB Emulation', as the
               backdrop picture settings are now in their own section.

             - The SetAsBackground command has been modified to load pictures directly
               through Opus without going through the WBPattern Prefs. To the end user the
               effect should be the same, and it will be slightly quicker. SetAsBackground
               now has the template:

                   NAME,DESKTOP/S,LISTER=WINDOW/S,REQ=REQUESTER/S,TILE/S,CENTER/S,PRECISION/K

               DESKTOP is the default and does not need to be explicity specified;
               LISTER and REQ allow you to set the background picture for listers/groups and
               requesters.
               TILE will tile the picture, CENTER will center it.
               PRECISION lets you specify the remapping precision; valid values are
               "none" (no remap), "gui", "icon", "image", "exact".

             - You can now use the internal Set command to modify icon label colours on
               the fly. You could use this ability in conjunction with the SetAsBackground
               command to implement a random background switcher script for Opus.

               Usage :   Set labelcolour [desktop|windows] <fg> <bg> <drawmode>

               Eg    :   Set labelcolour desktop 3 1 jam1
                         Set labelcolour desktop 7 0 jam2

             - Borderless icons accidentally became non-transparent in the last beta.

  30-Apr-97  - If the last file in the lister was the 'active' one in keyboard selection
               mode, and you deleted a file at the top of the lister using the mouse,
               the selection arrow would not be cleared properly as the list moved up.

             - With 'Use Workbench Icon Positions' turned on, the lister mode is now
               saved to the icon properly when you snapshot the window (could people please
               test with this mode turned on for a while?)

             - Fixed a bug that crept into the last version that would cause hits if you
               closed a Start Menu.

      #1328  - You can now specify the NOSCREENTOFRONT parameter on the command line or in the
               icon tooltype when Opus is started. This stops it moving its screen to the front
               of the display when it initialises.

    1-May-97 - Added 'Full Transparency' option to Environment/Icon Settings. This option
               makes Opus render its borderless icons with colour 0 transparent over the whole
               icon, rather than just colour 0 around the edge. This results in quite a large
               speed increase when loading icons.

             - Added the HookCheckDesktop() callback function, and the equivalent ARexx
               'dopus checkdesktop' function.

      #1329    This command is used when your program has just copied one or more files
               to a directory. You pass it the destination path that you copied the
               files to, and DOpus compares this path with the location of the Desktop
               folder. If they are the same, DOpus will then scan the Desktop folder and
               update the icons on-screen if necessary.
               This slightly clumsy method has been used because of problems in the
               system notification routines.

    2-May-97 - Thomas' problem with listers opening blank (no icons showing) seems to be fixed.
               Thomas please check.

      #1330  - The new custom dragging routines added a few versions back seem to cause
               problems with the Picasso software (they were only ever tested under CyberGfx).
               Therefore, they are bypassed automatically if the display is not a CyberGfx
               one.

               You can also set the dopus/NoCustomDrag environment variable to 1 to disable
               the new custom drag routines completely.

    4-May-97 - There was a bug in the palette BOOPSI gadget which would cause lines to be
               drawn outside of the gadget area; eg in Environment/Palette if you reduced
               the user pens to 0 and then increased the number again.

             - Fixed a problem in the file popup menu which caused PopUpExtensions (ie
               ARexx modules that add popup menus for filetypes) to be added incorrectly to
               FTP listers (if you had my arcbrowse.dopus5 module installed, the file popup
               for a file in an FTP site would have two Browse... entries, even if it wasn't
               an LHA archive).

    5-May-97 - 'Put Away' from the Icon menu no longer makes desktop folder icons disappear
               until the next reset (it should not affect them at all).

             - 'Delete' from the Icon menu now works on desktop folder icons.

             - Fixed problem that stopped AppIcons and AppMenus from showing (eg Organiser,
               Madhouse)

             - The 'lister findcache' rexx command now recognises if a lister has been
               set to case-sensitivity (eg the FTP module).

             - Fixed a refresh bug in lister editing.

      #1331  - Fixed a bug that could cause the palette to change mysteriously when you
               cancelled the Environment editor.

    6-May-97 - Requesters that open for a function without a lister (eg, selecting
               Delete from the popup menu of an item in the desktop folder) now
               position over the mouse pointer rather than in the center of the
               screen.

             - Pressing F5 on the main window will refresh the desktop folder (quicker
               than doing an Icon/Reset).

             - The NoCustomDrag variable and the automatic bypass for non-cybergraphics
               graphics systems was broken, so icon dragging would cause a crash.

      #1332  - Clicking on a borderless icon usually means you have to click on a part of
               the image rather than the background colour to select it. This behaviour
               has changed slightly; this is now true only if the icon is _not_ selected.
               If it is already selected, you can click anywhere within the image
               'rectangle' to select it again. This makes double-clicking on borderless
               icons easier.

    7-May-97 - Iconified listers were not using the icon positioning areas properly.

             - Listers now remember their position and state if you have the
               'Use Workbench Icon Positions' flag enabled, and the
               'Always Use Snapshot Position' flag disabled.

      #1333  - New help nodes added:

                   Desktop - Copy
                   Desktop - Move
                   Desktop - Left-Out
                   Desktop - Cancel

                   Icon Popup - Open With
                   Icon Popup - Open In New Lister

                   Buttons - New Gfx Buttons
                   Buttons - New Text Buttons

                   Lister - Space Gauge

    9-May-97 - If files displayed in a 'Show All Files' icon mode lister used a default
               icon set by Filetypes, and the icon had a default tool, Opus would try to
               start the file as a tool when you double-clicked on it. Opus will now use
               the default tool if there is one set in the icon; if not, it will use
               the double-click setting in filetypes.

             - Groups with NewIcons for their drawer icons would not be displayed properly
               when Opus started up (they would be fine after an Icons/Reset). Also, icons
               used for groups are now set to WBDRAWER by Opus automatically.

             - If you had a lister open with a given file in it, and you deleted a file of
               the same name in another directory by giving the pathname to the Delete
               command, the file would incorrectly disappear from the lister.

             - Arg5 of the 'dropfrom' custom handler message now contains the destination
               path; that is, the path that the file was dropped into. If the file was
               dropped onto an icon, the destination path will be that of the object it
               was dropped onto. For example, if a file from your custom lister is dropped
               onto the Prefs icon in the Workbench lister, Arg5 will contain
               "DH0:Prefs/", while Arg3 will contain the handle of the destination
               lister.

               If Arg3 is 0 the drop was probably to the desktop. If the file was
               dropped onto an icon on the desktop, Arg5 will contain the path. If
               the file was dropped onto empty space on the desktop, Arg5 will
               contain the string 'desktop'. If you get the string 'desktop' you can find
               the proper path to copy the file to (or whatever) using the 'getdesktop'
               command described below.

               Note that if the user drops a file onto an icon that is not a disk or a
               drawer, you will still get the full pathname of the icon in Arg5.
               It is up to you to determine whether the given destination path is a
               drawer or a file and act appropriately.

               Also note: the old Arg3 was a little bit confusing; it was the
               destination lister handle if there was one, otherwise it was the source
               lister handle. This has now been changed; Arg3 is ALWAYS the destination
               lister handle, and 0 if there is none. Arg1 is still the source
               lister handle.

      #1334  - A new hook and rexx command has been added; HookGetDesktop() and
               'dopus getdesktop'. This function allows you to find the path of the
               desktop folder. The ARexx command returns the path in RESULT, and
               returns a value in DOPUSRC that indicates the user's desktop settings:

                    0    desktop popup disabled
                    1    no default action
                    2    default : create leftout
                    3    default : move
                    4    default : copy

               See the SDK for information about the callback hook.

   10-May-97 - Fixed a little icon layout problem (it was possible for icons without
               a snapshot to be positioned out of the visible display on the main window
               in backdrop mode)

             - With 'Use Workbench Icon Positions' enabled, listers that hadn't been
               specifically snapshotted (in either Workbench or Opus) were defaulting to
               name mode instead of icon mode.

             - The Icons/New Drawer menu now works on the desktop as well as in listers.

             - Loading a new Environment would cause your group icons to be duplicated.

   11-May-97 - Fixed a divide by zero bug if you loaded a Start Menu as a normal button
               bank

   14-May-97 - Borderless text fields now fill the background with EraseRect() so that
               backfill hooks (like requesters with backgrounds in them) show properly.
               This fixes the display problems in the graphical Disk Information requester.

             - Opus now uses notification on the Desktop Folder to update the display
               automatically.

             - Requester backgrounds are now only used if the requester is opening on the
               DOpus screen, since the background is only remapped for this screen. For
               example, the text viewer on its own screen will not use the background
               picture in requesters.

             - Hopefully the Environment Megabug is now fixed.

      #1335  - Fixed the lockup when you tried to open multiple listers simultaneously
               from the Icon/Open menu.

   15-May-97 - If you had items in the desktop folder, and you then permanently left-out
               something else, left-outs would be created automatically for all the
               desktop folder items too. And even better, it was impossible to get rid
               of them!

             - Fixed the little quirk in the Function Editor for Filetype Menus, where
               pressing return in the label field would leave the field still active.

             - There was a chance that if you quit DOpus you would not be able to start
               another copy of it. You can no longer run multiple copies of DOpus
               simultaneously.

   15-May-97 - Final Magellan release version

                      ----------------------------------

   20-May-97 - The lister free space gauge is now configured from the Lister
               Format editor. The default setting is set in Environment/
               Lister Defaults, and can be configured and saved on a per-lister
               basis using the popup editor.

               The advantage of this system is that it truly lets you configure
               which listers you want the gauge to appear for (eg, if you only
               want it on the root directory of certain devices, turn it off
               in the default lister format and then turn it on for those
               directories).

   22-May-97 - Lister refresh routines rewritten in an attempt to eliminate
               the problem of icons and text overwriting the window borders
               when you resize listers.

             - Drag and drop into a sub-directory in name mode has been
               implemented. Moving the mouse when dragging files over a
               directory in a lister (either the same lister or a different
               one) will highlight the directory name; if you release the
               files over that directory, the defined filetype action will
               use that sub-directory as the destination path rather than
               the path of the lister itself.

               For ARexx users, the "drop" message now contains the full
               destination path in Arg5. You can compare this against the
               path of the destination lister (handle in Arg1) to see
               whether the drop was into a sub-directory or not.

               Note that this is not yet implemented when dragging icons,
               only files/directories from a name-mode lister.

             - Added MOVEWHENSAME switch to Copy and CopyAs commands. When
               specified, this switch changes the Copy function into the
               Move function when the source and destination paths are
               both on the same disk. This emulates the behaviour when
               dragging and dropping icons; within the same disk, the
               files are moved, when dropped on a different disk the
               files are copied.

      #1400  - The "drop" message sent when files were dropped into a lister
               with a custom handler did not, in some cases, contain the
               source lister handle in Arg3 as the Opus manual indicated.

   23-May-97 - The space gauge setting for individual directories is now
               respected when changing directories within the one lister
               (eg if you are in a directory that has a space gauge, and
               change to a directory that doesn't, the gauge will
               disappear automatically).

   27-May-97 - The GetSizes command now works from the filetype popup menu
               on directories.

             - Opus did not recognise that the DONOTWAIT tooltype was not
               set on objects in the WBStartup drawer, and always returned
               immediately. Opus now behaves properly if DONOTWAIT is not
               present, by waiting for about 5 seconds for the program to
               return, and then displaying a requester.

             - If you set the dopus/HidePadlock environment variable to 1,
               the padlock titlebar gadget will not be added to listers.

             - New Icon Clock module which always has an icon border, even
               if borders are turned off in the environment.

             - The scroll bars were not being updated when you switched an
               icon mode lister out of 'show all files' mode.

             - Moved the icon label font settings into Icon Display section
               (was Icon Colours). Added 'Remove Opus Icon Positions' to
               Environment/Icon Settings. Theoretically, setting this
               option along with the 'Use Workbench Icon Positions' flag
               enables you to move an Opus-ised system back to a Workbench
               position system without having to resnapshot all your icons.

               With the 'Remove...' flag set, Opus will use the Opus icon
               position set in the icons if there is one. When the icon
               is snapshotted, the Opus position will be removed, and the
               Workbench position will be saved. Next time the icon is
               read, it's the Workbench position that will be used.

      #1401  - The ScanDir command (and the equivalent ARexx command) now
               recognises ftp:// and launches the FTP module automatically.
               Previously, ftp:// was only recognised if you typed it
               in manually in the path field.

   28-May-97 - Clipping filenames from a lister to the clipboard now uses
               the volume name rather than the device name (eg
               Workbench:C/Info rather than DH0:C/Info)

             - Added additional filetype actions to the filetype editor.
               There are 6 new User actions (along with User1-4 making
               a total of 10), and qualified double-click and drag&drop
               actions. The filetype editor window has grown to accomodate
               these.

               The new User actions are accessed via a generic User command,
               which takes a number as a parameter. This was done to avoid
               having to add 6 new commands. For example,

                   Command      User 5

               instead of:

                   Command      User5

               Note that User1, User2, User3 and User4 still work for
               compatibility.

               You can now also have filetype actions defined for
               control and alt drag&drop, and control and alt
               double-click (shift is already used by Opus).
               The DoubleClick and DragNDrop internal commands
               have new templates:

                   DoubleClick ALT/S,CTRL=CONTROL/S,NAME/F
                   DragNDrop ALT/S,CTRL=CONTROL/S,SHIFT/S,NAME/F

   29-May-97 - The terms GUI, Icon, Image and Exact Precision were confusing
               some people, so they have been relabelled to be more descriptive
               (this is in the Environment/Backgrounds section).

      #1402  - Added 'Drag Into Sub-Directories' option to Environment/Lister
               Options. This lets you enable or disable the dropping into
               sub-directories in name mode listers that was added in 1400.
               If you have it switched off you can always activate it by
               holding down the shift key while dragging.

   31-May-97 - The bug that caused bad disk icons to not disappear when the
               disk was ejected has been fixed.

             - The F5 key can now be overridden by user settings (by default
               it causes a refresh of the desktop)

             - You can run two copies of Opus again, but the warning message
               is scarier.

      #1403  - Small bug slipped into 1402 that caused a crash when
               double-clicking on a file in an ArcDir lister.

    2-Jun-97 - There was a small problem with the 'Filter Icons' setting;
               if set for a directory or as the default format, and you
               opened a lister in icon mode (eg by double-clicking on an
               icon), no icons would appear. If you then switched to name
               mode and back to icon mode, the icons would be read.

             - The Icon Information requester wasn't saving the icon properly
               if you dropped a new icon in to replace the image (caused by
               NewIcons actually)

             - Fixed a bug that caused {Ql} to stop working in some situations,
               eg if the User4 command was called from ARexx with a full
               pathname instead of just a filename (Frederic's Show&Edit script)

    3-Jun-97 - If you dragged a directory to another lister or the desktop,
               and the directory was moved (because of filetype settings, etc),
               it would generate an 'object in use' error and not completely
               remove the directory from the source.

             - Added a new 'Inherit' option to the Lister Format editor. This
               flag has the same effect as the padlock gadget; if turned on,
               sub-directories will inherit the format of the parent directory
               (when double-clicking on them in name mode). When turned off,
               unless a directory has a format defined for it, it will use
               the default format. This fixes the problem Trevor was having
               with the fuel gauges not disappearing when he entered
               a sub-directory.

             - Arg5 of the 'dropfrom' message did not contain the correct
               path if the user dropped into a sub-directory; only the 'drop'
               message worked.

             - Dropping onto sub-directories is now disabled by default for
               custom handlers. You need to add the 'subdrop' keyword to the
               'lister set handler' command to enable dropping into
               sub-directories for your handler. Note that the user may
               still have sub-dropping turned off in the environment.

      #1404  - Renaming a link in a lister now works correctly.

    5-Jun-97 - The LoadDB command now supports the NEWPATH switch of the
               LoadWB command. If Opus is already running and you execute
               "LoadDB NEWPATH" (or LoadWB NEWPATH if running as WBR),
               Opus will not try to run again but instead will update its
               copy of the path list with the path in the current shell.

               LoadDB is smart enough to pass the NEWPATH command through
               to the original LoadWB command if Workbench is also
               running (or running instead of Opus).

      (5.61)

   11-Jun-97 - The Icon Information requester now supports image replacement
               by dropping NewIcons onto it.

             - Copy to clipboard in the text viewer now copies tabs correctly.

             - Under some locales, the Datestamp function did not display the
               current date/time string correctly (there were too many
               spaces separating the strings and the end of the time string
               was truncated).

   12-Jun-97 - The IconInfo command is now asynchronous from name mode listers.
               It also has a new WAIT parameter (like Show, Read, etc) so you
               can force it to be synchronous again.

             - The Disk Removed Script is now executed correctly when a disk is
               removed even if there is a lister open for that disk.

   13-Jun-97 - When an icon image is changed and updated on-screen, the mask is
               now automatically regenerated. This fixes the problem of icons
               not being properly transparent when the imagery is replaced
               or the border is turned off through the IconInfo requester.

      #1405  - IconInfo now has a 'Strip Original Image' function, which will
               remove the old-style image from a NewIcon (and replace it with
               a single pixel). Please test!

   17-Jun-97 - Device list/Diskchange routines modified again to fix a potential
               problem - please report any anomalous disk inserted/removal scripts,
               etc.

             - Added NEWER/S parameter to Copy command - similar to the UPDATE/S
               switch except will only copy files that either do not exist or
               which have a later datestamp than the existing file.

      #1406  - The CloseButtons command can now close Start Menus, with the use
               of the START/S switch. The name you provide is the name of the
               'menu' as set in the first column in the menu editor. You can
               also use the ALL/S switch to close all Start Menus.

   18-Jun-97 - Flushing the dopus5.library from memory (eg, with avail flush
               or flushlibs from loadwb -debug) could cause a crash and/or
               memory corruption.

             - 'New Drawer' in a name-mode lister popup menu is now available
               again.

      #1407  - Added partial support for images in popup menus; currently this is
               only available in Start Menus. The image file is set from the
               function editor when configuring the Start Menu (sorry, there is
               no preview available). You can use IFF images or icons; two-frame
               images are supported. The images are remapped and scaled
               automatically. You should only pick small (say < 20x20) images to
               use for this.

               I have really just added this to try it out; in my opinion the
               images are too small to be really useful. Let me know what you
               think though.

   19-Jun-97 - Fixed enforcer hits that occasionally appeared when displaying
               images in Start Menus.

             - You can now select the font to be used by a Start Menu, from the
               new Appearance/Change Font... in the control menu for the Start
               Menu.

             - Right Amiga-C now works in icon mode to copy the names of
               selected files to the clipboard.

   20-Jun-97 - Images in Start Menus now work on items that have sub-items.

             - Hotkeys assign to Start Menu functions now work.

             - Added 'Key Finder' to main Opus menu. This is a feature that
               allows you to find where you have used a given hotkey sequence.

      #1408  - Added 'Help!' to main Opus menu, mainly to flesh it out a bit.

   22-Jun-97 - Made some changes to hopefully prevent the cyclic backdrop menu
               bug.

             - There was a terrible, horrible, nasty bug in the text viewer, that
               <GASP> meant you could press alt P or control P as well as just
               P by itself if you wanted to print the file. OH NO!!!!! Luckily
               for civilisation, this dastardly menace has been thwarted.

   23-Jun-97 - If you Snapshot a file in icon mode (view all icons) that did not
      #1409    have an icon previously, the name mode buffer is now updated to
               reflect the new icon.

   24-Jun-97 - The Key Finder now correctly identifies global Hotkeys (it now
               traps the commodity event when it is open).

             - The 'Replace Image' function of AddIcon now works properly if
               the old image is a standard icon and the new one is a NewIcon.
               (Please test!)

             - There was an intermittent problem when switching from name mode
               to icon mode. If the lister resized because of the change, there
               was a possibility (race condition) that one or more icons would
               be drawn twice, overlapping. This should now be fixed but
               because the problem was so hard to reproduce it is difficult to
               be certain.

             - The problem with the keyboard mode selection arrow not being
               removed when deleting files was only partially fixed. The
               problem still existed in some circumstances for simple-refresh
               windows. Hopefully it is now gone for good. (Happy, Martin? :-)

             - The Start Menu control menu now has a 'Scale Images' option.
               This allows you to turn off image scaling. Images will be
               rendered in their full size, and the size of the menu items
               will be based on the size of the largest image.

               The 'Drag Bar' settings in the control menu have also been
               re-organised; they are more intuitive now.

      #1410  - Bad disk icons with labels like DH0:BUSY, etc, are now placed
               correctly (the text of the label was able to overlap other icons
               before).

   25-Jun-97 - Added several environment variables; none of these have been
               properly tested:

                   dopus/CommandLineLength

                   Set this variable to change the maximum length of command
                   lines in AmigaDOS functions (the default is 512)

                   dopus/IconSpaceX
                   dopus/IconSpaceY

                   Set these variables to change the default spacing between
                   icons (the default is x=3, y=5)

                   dopus/IconGridX
                   dopus/IconGridY

                   Set these variables to make DOpus align icons to a grid
                   when positioning them automatically (the default is 1
                   for both which means no grid).

   26-Jun-97 - If you hold down left shift and left alt together when you
               drop one icon onto another, the imagery from the first
      #1411    icon will be copied automatically to the second.

   03-Jul-97 - If you dropped a program with a NewIcon directly onto a button
               bank (in edit mode), the NewIcon would not be remapped and so
               the button would appear blank until you went into the button
               editor.

             - The 'Show All' option in the lister menu is no longer disabled
               in name mode; selecting it automatically shifts the lister
               into icon mode.

             - If you double-clicked a tool in a show-all-files icon mode
               lister, and the tool didn't have a real icon, Opus would run
               it in AmigaDOS mode, bringing up the Execute Command
               requester. This was fine, except that it wouldn't CD to the
               correct directory, and so wouldn't actually find the file to
               run.

             - You can now set the font for a Start Menu's label independently
               of the menu font.

             - When loading an environment, listers are now opened after
               buttons and start menus, instead of before. This is to stop the
               Start Menu windows appearing over the top of listers.

      #1412  - The 'icon paint mode' now works when the destination icon 
               doesn't exist (ie a fake icon in a 'Show All' icon mode lister)

   05-Jul-97 - If you created a command icon using {f} (or similar, eg
               AmigaDOS   echo {f}) and then dropped a file onto it, it would
               cause a crash.

             - Opus now updates the dopus/dopus environment variable whenever
               one of the menu items (file filter, defpubscreen, etc) is
               changed, instead of just when you save the environment.

             - In the Start Menu editor, dragging an item from the sub-item
               column to the item column now works properly.

             - The Menu Editor would crash if you dropped an icon into it
               (this broke when I fixed the dropping a NewIcon onto a button
               problem on 03-Jul).

      #1413  - The whole system of how a lister gets its format has been
               reworked. Hopefully it is logical now.

               1. If the Padlock gadget is ON, the format is NOT changed
                  when a new directory is read into the lister, else
               2. If the existing directory is rescanned, the format is
                  NOT changed, else
               3. If a format is saved for the path being read, that
                  format is used, else
               4. The format in the lister is NOT changed when a new path
                  is read into it, however
               5. If the 'Inherit' flag is NOT set then the Space Gauge
                  flag from the default lister format settings is used.

               I hope that makes sense. The 'Inherit' flag now ONLY affects
               whether the Space Gauge is on or not, which is the main
               reason it was added anyway.

               Please test this QUICKLY (Neil!) and let me know if a) it
               works as stated, and b) if you like it like this.

   08-Jul-97 - Added 'lister set <handle> default' arexx command. This is
      #1414    an easy way to set a lister back to the default list format
               (as defined in the environment).

   14-Jul-97 - The use of soft links (as opposed to hard links) was causing
               mungwall hits when more than 2 or so soft links appeared in
               the one directory.

             - 5.62 release

   23-Jul-97 - It was found that Opus (in Use Workbench Icon Positions mode)
               did not set the dd_CurrentX and dd_CurrentY fields of the
               DrawerData structure when snapshotting directories. This
               ordinarily didn't cause a problem, as Opus doesn't look
               at these fields at all. If you had a drawer icon that somehow
               had these fields set to strange values, and snapshotted it in
               Opus, these fields would not be set correctly. If you then
               loaded that drawer under Workbench, it would not look the
               same as it did under Opus (because Workbench uses these fields).

               Opus now sets the fields correctly when you snapshot a directory
               - it uses the current position of the scroll bars, as Workbench
               does. However, Opus still doesn't use these fields (whenever you
               open a new icon mode lister in Opus, the position of the
               scrollers is always 0,0).

   24-Jul-97 - There was an obscure problem that revealed itself if you had
               the 'Perform all actions on icons...' flag turned on. If you
               ran the Copy command (and possibly other commands like Move
               as well) with any of its arguments (eg NEWER, QUIET, etc),
               Opus would get the source and destination directories confused.

             - Fixed a crash in the AFC.

             - Dragging and dropping a file onto a button bank to automatically
               create a function now encloses the filename in quotes if there
               are spaces in it.

             - 5.63 version

   04-Aug-97 - Three different crashing bugs in the filetype.module were fixed.

   07-Aug-97 - If you had a >256 colour backdrop picture set in DOpus (and were
               using v43 picture.datatype), in some circumstances the picture
               would be corrupted when DOpus loaded the first time after a
               reset.

   08-Aug-97 - Changes made to device list routines to hopefully fix crashes
               a few people report when removing/inserting disks.

             - 5.64(1) version

   12-Aug-97 - Made more changes to the device list routines (library 62.3)

             - Icons added with "dopus addappicon" weren't being remapped
               if they were NewIcons.

   15-Aug-97 - The problems that some people were having when removing/inserting
               disks seem to be fixed

             - DOpus now adds commands in DOpus5:Commands to the internal
               function list.

             - The 'Format' option was unavailable in the popup menu for
               bad disk icons.

   16-Aug-97 - The resizeable configuration windows (Scripts, etc) could
      5.642    lock up if you resized them too quickly or something.

   21-Aug-97 - Deleting a tooltype in the IconInfo requester now automatically
               selects the following tooltype.

   22-Aug-97 - NewIcons icons weren't remapped properly in a lister that
      5.643    was saved in the layout as iconified.

    3-Sep-97 - Added OVERRIDE switch to the Disk filetype matching command. This
               lets you define an icon for a disk type that will override the
               icon on the disk if there is one. For example,

                    Disk       DF0: override

    5-Sep-97 - Start Menus no longer bring themselves to the front when they are
               clicked on.

    8-Sep-97 - Calling the internal delete command from ARexx would not work
      #1420    properly if you were trying to delete a pathname containing one or more
               sub-directories, and you specified the QUIET flag (this could also
               have affected other commands called from ARexx with a filename).

   11-Sep-97 - Start Menus now bring themselves to the front when they become
               active, but only if the mouse is over them at the time.

   15-Sep-97 - If the default tool of an icon was given without a path, so that Opus
               had to search the path list, then when the default tool was launched
               it's home directory (PROGDIR:) would be set incorrectly to the
               directory containing the icon, rather than the directory containing
               the default tool.

             - Hopefully Thomas's hits from the play.module will be fixed now
               (Thomas - please test)

      #1421  - Fixed mungwall hits that were caused by having more than one softlinks
               in a directory, with at least one softlink pointing a non-existing
               file.

   17-Sep-97 - When Opus saved an icon, it wasn't setting the DiskRevision field,
      #1422    which it turns out it needs to. This should fix the problems where
               listers don't remember the mode they have been snapshotted in with
               Use Workbench Icon Positions turned on.

   18-Sep-97 - It is now possible for umlauts and other >127 characters to be used
               as the shortcuts for requester buttons.

      #1423  - The internal command list is now updated automatically whenever a
               new user command is created in the dopus5:Commands directory.

   19-Sep-97 - Somehow the Bad Disk Insertion script broke; should now be working.

             - Changing a file's comment, date or protection bits would erase any
               network information it had from the lister display.

             - If you set the variable dopus/PatchWBInfo to 1, DOpus will intercept
               calls to the workbench.library WBInfo() function. If you are running
               Opus as a Workbench replacement, and have other programs that call
               the WBInfo() function (apparently Garshneblanker does), this setting
               should let them call the Opus IconInfo module.

             - The Output Window title string field in the Environment editor now
               allows up to 60 characters to be entered (P. Schulz, please test)

   20-Sep-97 - Changing the lister font in Environment/Lister Display now correctly
               updates any listers open at the time.

      #1424  - You can now only select a fixed-width font for listers in the font
               requester for Environment/Lister Display.

   22-Sep-97 - Fixed potential enforcer hits if you used the 'dopus command' rexx
               command with no 'type' specifier.

             - Fixed possible hits that could occur when switching a lister between
               icon and name mode (though it would only happen very rarely and in fact
               I think would have already been fixed by changes made in #1422).

             - When launching Workbench programs, Opus wasn't correctly passing
               any directory (or disk) arguments.

      #1425  - Happy birthday to me, Happy birthday to me, Happy birthday to meeeeee...
               Happy birthday to me :)

   23-Sep-97 - Added real-time scrolling in icon mode listers. Hopefully this will
      #1426    make Opus far more usable (it was really totally useless before now).

   24-Sep-97 - Dropping a directory or disk onto a button that launched a Workbench
               function would not submit the directory argument correctly (similar
               to the problem fixed in #1425).

   26-Sep-97 - MUFS owner/group information is now displayed.

             - Envoy owner/group information is now correctly displayed.

      #1430  - DiskInfo.module now recognises Envoy volumes.

    1-Oct-97 - Owner, group and network protection bits can be edited in inline lister editing.

      #1435  - Added 'RTG Mode' option to the NewIcons settings.

    2-Oct-97 - Added the option of Shadow text for icon labels; selected from the
               'Desktop' and 'Window' font requesters in Environment/Icon Display.

      #1436  - Fixed a couple of rendering problems with the real-time icon scrolling.

    3-Oct-97 - Added Outline text for icon labels.

      #1437  - Fixed final (?) rendering problems with icon scrolling.

    7-Oct-97 - Added space in use and percentage full display to lister title bars.

      #1438  - Added simple popup menu (Snapshot, Cleanup) to groups.

    8-Oct-97 - Added dopus/NoMUFS environment variable; set to 1 if you don't want DOpus to
               open the multiuser.library

             - Added 'Search Range' filetype matching command. This is similar to the
               'Search For' command, except that it lets you limit the range of the search.
               The first parameter on the line is the maximum number of bytes to search.
               This must be followed by a space, and then by the text to search for as
               normal. Searching takes places from the current position within the file.
               For example,

                   Move To        512
                   Search Range   1024 hello

               This would move to position 512 and then search the next 1024 bytes for the
               string 'hello'.

             - There is now a flag (in Environment/Icon Settings) to turn on real-time
               icon scrolling. There are a couple of problems with scrolling (eg, under 3.0
               or in an AGA screenmode with a backdrop picture), and this flag was added
               to allow people to disable scrolling if they need (or just want) to.

             - Opus will now hide bad disks if there is a "good" disk that it recognises as
               belonging to the same physical device. For example, if you insert an msdos
               disk you will get an icon for PC0 but no bad disk icon for DF0. At the
               moment Opus only recognises DFx:, PCx:, MCx:, DSx: and FSx:, with units from
               0 to 3. If anyone knows of any other filesystems we should be supporting
               please let me know. People with lots of filesystems mounted (I only have
               DFx and PCx) please test this feature.

               If the disk is not "good" for any device, a bad disk icon will be shown for
               all filesystems as before.

             - Fixed a problem in IconInfo, where if you dragged a NewIcon icon onto the
               requester to replace the existing icon image, the 'Strip Original Image' and
               associated menu items would be added to the popup menu, even if the new
               icon had no original image.

             - Fixed a problem with the dc_FileSet() hook function; setting the popup
               menu with the HFFS_MENU tag did not work properly.

      #1439  - Opus will now accept drawer (WBDRAWER) icons as disk.info - if you snapshot
               the icon it will be turned into a WBDISK type.

   10-Oct-97 - Small problem with the new Group popup fixed; pressing right-amiga for menu
      #1443    hotkeys didn't work.

   14-Oct-97 - Hopefully fixed occasional mungwall hits (from dopus_progressbar) on startup.

             - Fixed (thanks to Andrew) bug with real-time scrolling on AGA screens. Also
               disabled pattern centering (tiling is enforced) if real-time scrolling
               is enabled and the window is scrollable. The only problem left in real-time
               scrolling (that we know about) is caused by an OS39 bug in ScrollRasterBF().

   15-Oct-97 - Fixed the problem in the Scripts editor, where deleting a script entry
               would cause the entry to be doubled-up using a foreign language catalog.

      #1445  - There was a problem with the All/None/Toggle/Select commands in icon action
               mode; borderless icons would overwrite the existing imagery if their
               selection state was changed due to one of these commands.

   16-Oct-97 - AppIcons could erroneously have an "Open With..." item on the context menu.

             - Added 'Close' option to the context menu of iconified text viewers.

      #1446  - The Scripts delete bug should now be fixed (oops :-)

             - Fixed a possible negative EraseRect() in the progress bar.

      #1447  - Fixed an enforcer hit that crept into the last version.

   17-Oct-97 - The 'dopus command' rexx command can now be used to add items to the
               lister context menu. To do this, specify 'lister' for the 'type'
               parameter. Eg,

                   dopus command "Paste" program "paste" 'source' ext 'Paste' type lister private

   27-Oct-97 - The 'Split' requester now has default sizes for OFS floppy disks as well as
               FFS floppies.

             - Fixed the PROGDIR: problem for real now, I hope (Magnus please check)

             - Fixed some visual trashing in the status window when printing a picture from
               the picture information screen.

      #1448  - Using a drawer icon with the Disk filetype with the OVERRIDE parameter
               now works (the change in #1439 did not fix the problem if the override parameter
               was specified).

   28-Oct-97 - The 'lister new' rexx command now takes three new parameters:
      #1449
                   inactive    - don't activate the lister when it opens
                   invisible   - the lister is created but not shown, use 'lister set visible'
                                 to make it visible
                   iconify     - the lister is opened iconified

   29-Oct-97 - Fixed a problem in icon action mode where if you selected an icon that had
      #1450    no associated file and clicked CopyAs, you would not be prompted for a new name
               and the file would be copied as ".info". This could also affect other commands
               (like MoveAs, and possibly Rename).

   30-Oct-97 - If you had a (left-out) tool icon selected, and tried to drag and drop files
               from a lister onto a different tool icon in the same window, Opus would get
               confused and try to launch the wrong tool.

      #1451  - The fix in #1448 to fix trashing of the status window when printing a picture
               caused some text in requesters to be displayed with an opaque background (JAM2)
               instead of in JAM1 mode. Things should be back to normal now.

   31-Oct-97 - If for some strange reason you are using a project icon for a group, it will
      #1452    no longer cause enforcer hits.

    4-Nov-97 - Fixed enforcer hit that could occur on WBStartup if an error occurred launching
               a program.

             - Fixed enforcer hits caused by the last fix for enforcer hits (group icons)

             - The filetypes editor now shows a message if an error occurs during saving.

             - Fixed small rendering bug in icon complementing

        5.66 - The numbers are gone from the startup progress bar; if you want them back,
               set dopus/StartupNumbers to 1.

    8-Nov-97 - The 'Open With' function wasn't shown on the popup for files in a name mode
        5.661  lister.

   12-Dec-97 - If you copied an item in the start menu editor, then under some circumstances
               it wouldn't be displayed correctly until you exited and reentered the editor.

             - Added VOLUME parameter to internal PLAY command (takes a value from 0 to 64).

             - Fixed a problem if the length of the volume name of a disk plus the length
               of the directory on that disk that you were currently in was longer than
               about 45-50 characters (would cause hits and/or a crash).

             - If a lister showing the root of a volume is iconified, the label of the icon
               will now leave the colon after the volume name.

             - Fixed a potential problem with the use of ARexx scripts in the CopyTo
               directory (see TestScript.dopus5 in the System/_CopyTo directory on the
               installation disk/cd). If the comment you had given the Arexx script was
               shorter than the filename (or you had not given it a comment), it could
               cause a crash.

             - Opus now recognises PSx: (profilesystem on diskspare.device) as another
               device that can use the floppy drive, when it does its good disk/bad disk magic.

             - Added {QL} and {QD} command sequences to functions; these will insert the
               process address of the current source and destination listers (in hex).

             - Added 'lister query <handle> proc' rexx command to return the process address of the
               given lister (returned in RESULT in decimal).

      #1500  - Added 'lister query active' rexx command to return the handle of the currently
               active lister (ie the window is active, the lister is not necessarily source
               or destination).

   23-Dec-97 - Added 'leavegauge' option to 'lister set handler' rexx command. When specified,
               the fuel gauge (if present) will not be removed when the handler is added to
               the lister.

   17-Jan-98 - The dc_GetDesktop() callback now returns the correct value as documented in
               hooks.doc.

             - .info files without an associated file would not be accepted by {f}, etc,
               in functions.

             - 'Export to ASCII' from a filetype icon menu function would cause a lock up.

             - If the REPREQF_NOVERSION flag value is set for the 'flags' parameter in the
               dc_ReplaceReq() callback, the requester will not display a button to allow
               version checking.

             - Fixed enforcer hits when using inline editing in the FTP module.

      #1501  - Clipping filenames from an FTP lister to the clipboard could cause a buffer
               overrun.

    6-Feb-98 - Added the ability to define additional scripts, for integration with
               the Opus script interface.

               To add a script, create a file in the dopus5:system/scripts directory
               (you will need to create this directory first). The name of the file
               does not matter, but it must have a .scp suffix. The file can contain
               an unlimited number of script names, one on each line. The format of
               the file is:

                    <Script Name>,<Flags>

               Flags is optional. At the moment, the only flag defined is 1, which
               causes Opus not to lock the current source lister when the script
               is executed. For example,

                    FTP Finished,1
                    FTP Connect,1

               You will need to restart Opus for the new script definition file to
               be noticed. When you do, the names of your scripts will appear in
               the script configuration list.

               To trigger a script (either an internal script or a custom one),
               there is a new ARexx command:

                    dopus script <name> <data>

               <name> is the name of the script (not case sensitive), and <data>
               is an optional string that is passed to the script function in
               the {Qa} parameter.

      #1503    There is also a new callback function to trigger a script; dc_Script().

   12-Feb-98 - The rexx command "command doubleclick" will now correctly send a
      #1504    doubleclick message to the custom handler if the source lister has one.

   13-Feb-98 - Added dc_DesktopPopup() callback function, and "dopus desktoppopup"
      #1505    rexx command. These functions trigger the desktop popup menu at the
               current mouse position, and return a value indicating the user's
               selection.

               These functions are both called with a single value - a flags parameter
               which indicates which items in the menu are to be disabled (by default,
               all are available). Add the flag values as appropriate.

                    Add to disable      Item            Returns

                          2         Create Left-Out        1
                          4         Copy To Desktop        2
                          8         Move To Desktop        3

               The function returns 0 if the user cancels the operation.

   16-Feb-98 - Added the ability to have an additional 2 information lines in the
               progress requester.

   18-Feb-98 - Added 'info2' and 'info3' parameters to the rexx newprogress command
      #1506    to support the new information lines in the progress requester.

   19-Feb-98 - Rexx commands using the "command wait <cmd>" function now return a
               result code indicating success or failure.

   20-Feb-98 - Tweaked the icon positioning routines a bit; viewing a directory
      #1507    in 'show all' mode (or with lots of unsnapshotted icons) should now
               be a bit faster (it should also do a better job of positioning the
               icons).

   24-Feb-98 - If you used an Opus internal command that needs a destination
      #1509    and supplied the destination as a parameter to the command, Opus
               would erroneously display the 'Select Destination' requester if
               the command was combined with any other instruction.

   26-Feb-98 - Changes made to trapped functions to make them sychronous was
      #1510    found to cause problems with ArcDir, so by default trapped
               function messages are now asynchronous again. Use the 'synctraps'
               flag in the 'lister set handler' command to enable
               synchronous trap messages.

   27-Feb-98 - If the 'synctraps' flag is set, messages you get from trapped
      #1511    functions now have a new argument. Arg8 contains the address
               (in decimal) of the FunctionHandle structure for this function,
               for use with the Opus callback hooks. This handle is only valid
               until you have replied to the message.

    2-Mar-98 - Added dc_FirstEntry() callback hook. You need to call this
      #1513    before you call dc_GetEntry() for the first time.

      #1514  - If you used the LoadButtons command with the START parameter
               and specified the name of a start menu that didn't exist,
               it could cause enforcer hits and/or crashing.

    9-Mar-98 - Added 'pos' flag to the 'dopus read' rexx command. This lets you
               specify the position of the text viewer. For example,

                   dopus read pos 10/10/400/200 s:startup-sequence

               Note that the 'dopus read' rexx command already has a 'delete'
      #1515    flag to cause the file to be deleted once it has been read.

   10-Mar-98 - The CloseButtons command now looks for the name of the button
               file itself as well as the name of the button bank. This means
               that CloseButtons can now take exactly the same name as
               LoadButtons.

             - Icons used as arguments in a shift-doubleclick operation are now
               supplied in the order they were selected, instead of reverse
               order (to be compatible with Workbench).

             - If the Comment command is called from a filetype menu, it now
               correctly displays the original file comment in the requester.

   11-Mar-98 - The DeviceList now shows free and used space to one decimal
               place.

             - GetSizes should now be accurate on directories up to 4gb

             - The Disk filetype now allows you to specify a device name
               using ? as a wildcard (eg DF?:)

             - Copy to Clipboard now works correctly in the text viewer when
               there is a tab on the first or last line being copied.

             - The SRCE/DEST display in the lister status bar should now
               be properly font sensitive.

             - The "drop" and "dropfrom" custom handler messages now
               contain the word "subdrop" in the qualifier argument field
               if the drop was into a sub-directory.

             - The left and right edges of name mode listers are now filled
               with the appropriate background colour instead of being left
               clear (this removes the ugly 'borders' in name mode listers
               when the files have a background colour other than colour 0)

             - Iconified listers and some other types of icons were offset
               vertically by one pixel; if you repeatedly iconified and
               deiconified a lister you would see the icon move slowly down
               the screen.

             - It is now possible to select borderless icons by clicking anywhere
               within the icon rectangle (including transparent areas)

   13-Mar-98 - The 'dopus command' rexx command can now be used to add items to the
               lister popup menu (the one accessed by clicking on the SRCE/DEST
               display). context menu. To do this, specify 'lister2' for the 'type'
               parameter. Eg,

                   dopus command "Test" program "test" 'source' ext 'Test' type lister2 private

               If you use the new 'handler' parameter, the item will only be displayed
               if a custom handler matching the <command> name is present in the lister. Eg,

                   dopus command "my_handler_name" 'source' ext 'Test Menu' type lister2 private handler

               This command would cause the 'Test Menu' option to be added to the popup menu if
               the lister has a custom handler called 'my_handler_name' attached to it. When the
               item is selected, a message is sent to the namer with the name ('Test Menu') in Arg0
               and the lister handle in Arg1.

             - The 'dopus command' command also has a new 'remove' flag, which lets you remove
               a specified command. For example, to remove the above example:

                   dopus command "my_handler_name" remove

               This would remove all commands called 'my_handler_name'.

      #1516  - Started adding proportional font support to listers; works for the most part
               but a few graphical problems remain, and inline lister editing is currently
               broken.

   19-Mar-98 - Added MODPTR_DEFFORMAT to the dc_GetPointer() callback, to get a copy of the
               default lister format. You need to call dc_FreePointer() to free this when
               finished.

      #1517  - Custom script entries that have been removed from the dopus5:system/scripts
               directory are now really deleted when you click delete in the scripts editor.

   24-Mar-98 - Proportional fonts in listers generally seems to work now. Please keep an eye out
               for any graphical glitches when using both proportional and non-proportional fonts.

      #1518  - The 'subdrop' flag in the 'drop' and 'dropfrom' messages should now work.

   25-Mar-98 - Fixed a few glitches with proportional fonts in listers (only seemed to occur
               under AGA)

      #1519  - Fixed a problem with the cache list/device list and custom handlers - if you clicked
               the cachelist button in a lister with a custom handler, and then clicked it again,
               the custom handler would get "lost"

   29-Mar-98 - Fixed graphical problem with proportional fonts when dragging files in name mode.

    6-Apr-98 - All popup menus, including start menus, are now sticky even when the
               underlying window is not active.

             - Workbench commands in buttons, etc, can now be made asynchronous by simply
               inserting the word 'run' before the command, eg:

                    Workbench   sys:tools/calculator           <- synchronous
                    Workbench   run sys:tools/calculator       <- asynchronous

             - Added 'No File Selection..' option to Environment/Lister Options. If turned on,
               and you click on a file in a lister that is not the source lister, the lister
               will be set to source but the file will not be selected.

             - Added UNDERMOUSE/S and TOGGLE/S switches to the LoadButtons command. UNDERMOUSE causes
               the button bank to be opened under the mouse pointer, and TOGGLE will toggle the
               state of the button bank - if it is already opened, it will be closed, otherwise
               it will be opened.

             - Added 'Auto Close' and 'Auto Iconify' options to the button bank editor. When
               selected, they cause the button bank to be automatically closed or iconified
               whenever a button in the bank is chosen (saves you having to add CloseButtons
               commands to every button in the bank)

    8-Apr-98 - Added three new options to the dragbar orientation setting (now just called 'Drag')
               in the button bank editor Appearance section. This now lets you set the drag bar
               to be horizontal, vertical, horizontal on the bottom, vertical on the right, and
               to turn off the drag bar completely.

             - Area frames were not being redrawn properly on a resize event (FTPAddressbook)

             - The internal filetypes for Opus configuration files (buttons, environment, etc)
               have all been moved to priority 125 so they will be matched ahead of user-configured
               filetypes.

             - Added internal filetype for Start Menus - doubleclicking a start menu will now
               load it as a start menu and not as a normal button bank.

      #1525  - Added new filetype matching command - "Match Chunk". This is similar to "Find Chunk"
               except it only tests the NEXT chunk in the file for a match - it does not search
               the whole file. This can dramatically speed up matching of IFF files if you know
               the order in which chunks appear.

             - 'No File Select...' flag now has a less (?) confusing name, and is also a
               positive flag instead of a negative flag (Allow File Select On Source Activation)

             - Added several new script events: AnsiRead, HexRead, IconInfo, Play, Print, Read,
               Show, SmartRead. These let you override the internal commands of the same name.
               For instance, you could define a function for the Show event. Then, whenever
               the internal command Show is called, your function would be run instead.

             - Fixed a graphical problem with inline lister editing and proportional fonts;
               if you moved the cursor up or down with the cursor keys it would appear in the
               wrong position/size.

   11-Apr-98 - You can now click and drag on the separators between lister field titles to
               resize the fields. To restore a field that you have resized to dynamic sizing,
               double-click on the separator. There are still a couple of issues to be addressed
               with this feature (inline editing, and whether field widths should be saved in
               path formats)

             - Start Menus and Lister Menus can now have sub-items. In the menu editor, what were items
               and sub-items have been shifted one place to the left to allow an increased menu
               depth.

   13-Apr-98 - The Environment and Options settings sections have been unified, and the Options
               editor has been removed completely. The Environment sub-menu has been removed
               from the Settings menu - now there is just "Edit Environment...". Loading and
               saving of environments is done from the Environment editor just like all the other
               prefs-style editors. The 'Save Layout' option is now a function in the Settings
      #1526    menu that lets you save the current layout on demand.

   16-Apr-98 - The 'Icon handling' Environment section has been incorporated into 'Icon settings'.
               The checkboxes in the Icon Settings section have been replaced by a listview. Several
               environment variables have been turned into normal configuration items:

                    Allow icons with no labels        (NoNoLabel)
                    Smart icon copying                (SmartIconCopy)
                    Force split of long labels        (LabelForceSplit)
                    Quick icon dragging               (QuickIconDrag)
                    Use custom drag routines          (NoCustomDrag)

               Also, in the Miscellaneous section:

                    Enable MUFS support               (NoMUFS)

      #1527  - Added 'Path List' section to the Environment. This allows you to configure the path
               list used by Opus directly, without having to worry about where the path list is
               going to be inherited from.

   20-Apr-98 - You can now specify a directory or wildcard pattern for the background pictures in
               Environment/Backgrounds. If a directory or pattern is specified instead of a filename,
               DOpus will pick a picture at random from the supplied directory every time it is run.

             - Added new ARexx commands to manipulate background pictures:

                   dopus set background <file> [desktop|lister|req] [center|tile] [precision <precision>]

               This sets a new background picture for the specified place (desktop, lister or
               requesters). Precision, if supplied, can be: none, gui, icon, image or exact.

                   dopus refresh background

               Setting the background picture with the "dopus set background" command does NOT refresh
               the display. The display will not be updated until you call the "dopus refresh background"
               command.

                   dopus query background [desktop|lister|req]

               Lets you query the currently set background picture.

             - The screen title can now be customised using Opus. The setting is the Environment/Miscellaneous.
               You can choose from the following command sequences:

                   %dv     Directory Opus version
                   %kv     Kickstart version
                   %wv     Workbench version
                   %pr     Processor type
                   %cp     CoProcessor type
                   %cs     Graphics chip set
                   %tm     Total memory
                   %tc     Total chip memory
                   %tf     Total fast memory
                   %fm     Free memory
                   %fc     Free chip memory
                   %ff     Free fast memory
                   %um     Memory in use
                   %uc     Chip memory in use
                   %uf     Fast memory in use
                   %ta     Task count
                   %pu     Processor usage
                   %%      % character

               The memory fields can be further customised by following them with these codes:

                     K     Kilobytes, to one decimal place
                     k     Kilobytes, no decimal places
                     M     Megabytes, to one decimal place
                     m     Megabytes, no decimal places
                     S     "Smart" mode (bytes, kb, mb, depending on the actual amount), one decimal place
                     s     Smart mode, no decimal places
                     %     Percentage of total memory (free or in use memory only)

               For example,
               
                   Opus v%dv  Memory %fm%%% free, %um%%% in use  CPU %pu%%  %ta tasks

               If anyone has suggestions for other information they would like available, please
               let me know.

   21-Apr-98 - Holding down control while double-clicking on a directory in an Icon Action mode lister
               will cause the new directory to be read into the existing lister instead of opening
               a new one.

             - There is a new flag in the button bank editor: Active Popups. If this is enabled, buttons
               with multiple functions behave more like startmenus when you hold the mouse button down
               on them. Instead of letting you select the "default" function for the button, it activates
               the function you have selected immediately.

   22-Apr-98 - Button banks and Start Menus can now have background pictures (only under OS39+).
               For button banks, the background picture is configured through the Button Bank editor.
               For Start Menus, there is a new menu item in the control menu - Change Background.
               Both buttons and Start Menus support the use of a directory and/or wildcard pattern
               for random pictures.

      #1528  - The font requesters for the Change Font and Change Label Font functions in Start Menus now
               let you select the pen colour used to render the text.

             - Eliminated annoying flash of icons after reading icon mode lister.

             - If you hold the shift key down when pasting a string into a string gadget using
               Right-Amiga+V, the string will be inserted at the current cursor position instead of
               replacing the existing string completely.

             - It is now possible to bring up the popup menu for icons by clicking anywhere
               within the icon rectangle (including transparent areas for borderless icons)
               with the right mouse button.

   23-Apr-98 - Drag and drop to the parent directory of a lister is now possible in name mode only
               by dropping files on the left edge of the window (the hidden parent gadget). This is
               much easier if the fuel gauge is turned on.

             - Fixed a problem whereby the internal Select command would prevent any other commands
               that followed it in a function from working (eg ScanDir/Select/Delete - the Delete
               would not get executed).

             - If you doubleclick on an icon, all other icons in the window that were selected
               are now automatically deselected, unless the shift key is held down.

      #1529  - Moved a few more environment variables to the Environment editor:

                   Miscellaneous/Popup Delay                     PopupDelay
                   Miscellaneous/Maximum 'Open With' Entries     MaxOpenWith
                   CLI Launching/Max. CLL                        CommandLineLength

   26-Apr-98 - The 'Allow File Select On Source Activation' flag, when turned OFF, now only
               has effect if there is more than one lister currently open.

             - Added %sc (number of screens) and %fp (number of free pens) to the screen title bar.

             - Screen title bar now reports P96 for Picasso96 and CGX for Cybergfx screen modes
               (P96 people please check this works)

   27-Apr-98 - Fixed a problem that could cause programs doing a FindTask("Workbench") to fail
               when Opus was running

             - Right mouse button now aborts the resizing of lister field titles

   28-Apr-98 - A new option in Environment/Lister Options - "Window Zooms to Title Bar" causes
               the zoom gadget in listers to shrink the lister down to just a titlebar.

             - The 'Enable MUFS' option was broken - it would always open the multiuser.library
               even if turned off.

   29-Apr-98 - If the mouse is over the screen title bar, and you press the right mouse button,
               the button is never trapped by any objects (listers, startmenus, etc) underneath
               it - this is so you can always access the pull-down menus. However, this prevented
               you from accessing the edit menu in start menus. This has now been changed so that
               if you hold down control while pushing the right button, the event is trapped
               by start menus even if the mouse is in the screen title bar.

             - The label in a dragbar-less, borderless startmenu was rendered too far to the
               left.

             - Rearranging the field order in listers by drag and drop wasn't permanent; whenever
               the lister was refreshed or rescanned, the new field order would be lost.

             - The spacing of the 'Size' field was wrong, which would throw off the positioning
               of all subsequent fields (and also cause inline editing to be off by one
               character).

             - Add the new keyword 'custom' to both the 'dopus set background' and
               'dopus refresh background' commands. Using this keyword, you can change the
               background pictures internally without modifying the actual environment
               settings. You must use the 'custom' keyword on both the 'set' and 'refresh'
               commands for this to work. As soon as you do a 'refresh' without setting
               this keyword, the pictures will revert back to the environment settings.

      #1530  - New hooks added: dc_GetPointer() and dc_FreePointer(). These allow you to obtain
               a copy of the internal Opus command list. See the SDK hooks.doc and hooks.h for
               more information.

    1-May-98 - Fixed a problem that could cause icons not to be shown properly (Steigerbug).

             - Fixed a couple of other bugs

      #1532  - Added %pm to screen title bar.

    4-May-98 - Dragging icons from the button bank clipboard was broken (icon would be positioned
               off the mouse pointer)

             - The Lister Menu editor wouldn't let you edit things in the left hand list.

      #1533  - Added new 'Sound Events' section in the Environment. This section lets you configure
               a sound file to be played automatically for certain events. The event list is the
               same as for scripts, but it saves you having to configure a whole script just to
               play a sound file.

               New ARexx commands let you set and query the sound events. The format is:

                   dopus set sound <event> <file> <volume>
                   dopus query sound <event>

               For example,

                   dopus set sound "Open lister" dopus5:sounds/open_lister.snd 64
                   dopus query sound Startup

             - Changes for FTP ftp.module 63.33 (4.5.98)

              .31    Changed DnD function onto button. Now creates a name for the
                     button as well. (Martin)

                     Fixed problems with entering URL ftp:// in Device Lister
                     (ftp_lister_connect changed to use lst_empty instead of lst_clear)

                     Fixed problem with typing new path into path gadget which would
                     change path before comparing old/new and thus cause old cache entry
                     to be changed incorrectly. (should have been calling lister_list with
                     rescan=FALSE so as to call lst_empty and not lst_clear)

              .32    If Parent or Root failed the error was not being reported.    

                     A detached lister could be left open if NOOPs were enabled
                     and the connection timed out anyway.

              .33    Changed progress display to provide optional 3 line display with
                     %, time elapsed and estimated

                     Made some changes to fix problems with incorrect setting of
                     protection bits. NOTE: Does not always update the lister
                     correctly. Andrew to fix later.

            - Cool new features of cool new icon module:

               1.    You are now able to set the type of icon, and have
                     the window updated dynamically to accomodate the extra info.
    
               2.    There is now a popup button for default tool.
    
               3.    The title bar now indicates what kind (not type) of icon it is
                     (ie.  newicon or regular).
    
               4.    The icon author is now a regular tooltype so you can delete it.
    
               5.    Drag'n'Drop tooltypes between Icon windows.
    
               6.    Drag'n'Drop icons between Icon windows.
    
               7.    Drag'n'Drop icons to applications (eg IconEdit).
    
               8.    When you drag'n'drop an icon you are given a choice of copying
                     just the original image, the newicons image, or both.
    
               9.    You can edit the icon using IconEdit.
    
                     Note that IconEdit is particularly annoying in that it takes
                     neither command line arguments nor workbench style arguments -
                     try it.  To compensate for this problem, we have come up with an
                     ingeneous method for sending IconEdit an AppMessage as though an
                     icon had been dragged onto it.  Note also that IconEdit is
                     particularly annoying in more ways than one.  When the editor
                     starts, the mouse pointer must be within the large editing area
                     or it will not load your icon to edit it.
    
    5-May-98 - Some memory was accidentally being trashed in the Opus data section of which
               the only apparent effect was the display of a garbage string instead of the
               word "empty" for 0 byte files - probably had other side effects too.

      #1534  - dc_GetPointer() now works properly (for getting a list of commands).

    6-May-98 - Opus now has an internal filetype for system font prefs files. If you
               double-click on a font prefs file, Opus will set its own fonts
               (icon font, and screen font if on its own screen) to the settings in
               the prefs file.

    7-May-98 - Fixed erroneous space at the end of arguments in arexx messages.

             - When adding files to a lister via arexx/callbacks, the datestamp of the
               file is automatically set to the current date/time if it is passed in
               as 0.

      #1535  - Themes implemented (not quite finished yet). New themes.module adds
               SaveTheme, LoadTheme and BuildTheme commands.

               Themes currently consist of background picture, sound, pens and palette
               and font settings.

               Use the SaveTheme command while you are working on a theme, or to store
               multiple themes for your own use. The SaveTheme command generates
               a theme file using the actual locations of the component files on your
               system.

               The BuildTheme command is used when you want to prepare a theme for
               distribution. It will create a sub-directory in the DOpus5:Themes
               directory and copy all sound and picture files used in the theme to
               that directory automatically. The theme file it produces will refer
               to component files in the DOpus5:Themes directory. When you have
               used the BuildTheme command, you can theoretically LHA both the
               theme file and the sub-directory and distribute it to other users.

               The LoadTheme command is used to load a theme. You can select which
               elements of the theme to apply to your system.

             - New ftp module features:

                 .35  'Copy/Also Copy Source's xxx' and 'Copy/Set Source Archive
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

                 .36  With 'Copy/Set Source Archive Bit' enabled, the source lister
                      was being updated for downloads even though this options
                      is only possible for uploads.

             - New icon module features:

                      The popup button for default tool is fixed again.

                      IconEdit now opens under the mouse to better ensure
                      the fake app message is recognized.

                      Configurable icon editor support has been added.
                      If you select 'Pick Editor' from the popup menu you
                      can enter a command to edit which will be used instead
                      of IconEdit.  This requester has a tickbox marked
                      'Send AppMessage' - this must be on for IconEdit to
                      work, but it may also be useful for other programs.

                      When dragging from the icon window, the full icon will
                      now be dragged.  This was previously limited to the
                      size of the icon box in the window.

                      There was a hard-coded delay when using IconEdit to
                      wait for it to load before sending it the message.
                      The icon module is now notified by Opus when IconEdit
                      is ready for this.

       #1536 - More work on themes, fixed a couple of small problems.

   25-May-98 - Added 'Exclusive Startup/Shutdown Sounds' option to the
               Sound Events section. With this flag turned on, no sounds
               will be played until the Startup sound has been played,
               and no sounds other than the Shutdown sound will be played
               on shutdown.

             - Added %ev sequence to insert the value of an environment variable
               in the screen title bar. Usage is %ev<name>%, eg %evWorkbench%.

             - Icons without a 'selected' image, with borders turned off,
               would leave behind the bottom line of the image when they were
               moved or removed (eg XOper iconified icon).

             - A third-level startmenu would not be available if the second-level item
               had an image assigned to it.

             - Added a new keyword to the 'dopus command' rexx function: temp.
               Use this keyword to add a 'temporary' command, which doesn't have an
               external command file. This command will do nothing unless it is then
               trapped with the 'dopus addtrap' command. Use the 'remove' flag of the
               'dopus command' function to remove it when you are done.

               For example,

                   dopus command 'TestCommand' temp
                   dopus addtrap 'TestCommand' 'my_handler'
                   ...
                   dopus remtrap 'TestCommand' 'my_handler'
                   dopus command 'TestCommand' temp remove

               Use the 'private' flag of the 'dopus command' function to stop the
               temporary command from showing up in the command list.

             - The Disk filetype command can now match disk names as well as device
               names. For example,

                   Disk CD0: override                            (pri 0)
                   Disk CD0:CDDA override                        (pri 1)

               The first filetype would provide an icon for all data CDs, and the second
               would provide a different icon for audio CDs only (assuming audio CDs are
               labelled CDDA by the filesystem).

             - New icon module features:

                      Sometimes the module wasn't properly waiting for
                      IconEdit to start up.

                      When dropping an icon on an outside program's window,
                      a requester now appears allowing you to save the icon
                      if it has been modified.

                      There was a bug preventing an icon being saved if the
                      module was displaying a default icon for a file or
                      disk with no icon of its own.

                      There is now a file popup button in the "Pick Editor"
                      requester.

             - New fixicons module features:

                      Added new switch REPORT to output a report on the results.
                      Fixed SYNCOPUSTOWB option to save icons only if they have changed.

   26-May-98 - Redesigned the popup menu in the Environment/Backgrounds section. Added
               the ability to set the border colour for centered pictures (normal, black
       #1537   or white).

   27-May-98 - Fixed a bug that slipped through which would cause button banks _without_
       #1538   a background picture to crash when loading.

   29-May-98 - Problem with filetype identification fixed

   10-Jun-98 - If you edited a start menu it would no longer popup over the start menu
               button properly, but would instead popup underneath the mouse.

             - Fixed problem which could cause a lister opened by double-clicking on
               an icon, etc, to open empty.

             - Fixed print.module crash (just needed to be recompiled)

             - Shift delete and Shift backspace now do things in inline lister editing.

             - Shift-left click on a start menu to toggle the drag bar has been changed
               to control-left click.

             - Control-left click on a button bank now toggles the drag bar on or off.
               Control-right click on a button bank now brings up the bank popup
               menu (previously you could only access this by right-click on the drag
               bar).

             - The '0' key was actually predefined by listers, and so couldn't be used
               to scroll to a file beginning with a 0. This is now changed (the '=' key
               now does what the '0' used to do).

             - The 'dopus getdesktop' command now returns the full path of the desktop
               folder rather than the actual configured path (which could be an assign).
               Also added 'dopus matchdesktop' which will match a supplied path against
               the desktop folder for you. For example,

                   dopus matchdesktop 'dopus5:desktop'
                   --> 1

   11-Jun-98 - Added 'Load Environment' and 'Save Environment' commands to the Settings
               menu.

             - 'Thin Gadget Borders' option added to Environment/Miscellaneous. Turning this
               on will make all Opus gadgets (except the ones provided by GadTools) use
               single-pixel vertical borders, to improve the appearance on 1:1 ratio screens.
               To make room for this option in the Miscellaneous section, the 'Enable MUFS'
               option was movied to Caching (it doesn't really belong there but it's the
               best place I could find for it :-)

      #1539  - Added 'Test' button to Environment/Sound Events.

   12-Jun-98 - Added StopSniffer command to stop the filetype/version sniffer for the
               current lister. Add this to your toolbar if you want a way to interrupt
               the sniffer on large directories/files.

             - Changing the lister mode from arexx when the lister was iconified (or not
               visible) would cause enforcer hits.

             - Problem that snuck in last time with device list not appearing in new
               listers fixed.

   14-Jun-98 - The popup selection list requester in the file class editor was broken.
      #1540

   16-Jun-98 - The 'dopus getdesktop' command now terminates the returned path with a
               slash if appropriate.

             - Added a couple of parameters to the 'lister new' rexx command:

               'fromicon' will open the new lister using the size and position information
               from the specified directory's icon (only if a path is specified and an
               icon exists). Eg, lister new fromicon sys:tools

               'mode' lets you specify the initial mode of the new lister. Eg,

                   lister new icon
                   lister new action showall

      #1541  - The themes module now better supports loading themes from places other than
               D5THEMES:. There is a new field in Environment/Backgrounds that lets you
               configure the default theme location. Added themes submenu to Settings menu.

   17-Jun-98 - Fixed a couple of minor themes problems (the filerequester in LoadTheme was
               adding the word 'Themes' to the path when it shouldn't have), also hopefully
               fixed an enforcer hit.

      #1542  - Fixed resize problem with OD_AREA objects.

             - LoadTheme no longer locks the source lister.

   25-Jun-98 - Added "lister query title" and "lister query header" rexx commands to
               complement the "lister set" commands.

             - Added "lister set value" and "lister query value" rexx commands. These
               allow you to associate your own data with a lister in the form of name/value
               pairs. The lister will maintain the values until it is closed. For example,

                   lister set <handle> value MyName "Fred Bloggs"
                   lister query <handle> value MyName
                   lister clear <handle> value MyName

             - Fixed a problem with the new 'Thin Borders' flag in Environment/Misc.
               It was causing borders to appear for TEXT_KIND gadgets when they shouldn't
               have been (eg, DiskInfo).

   30-Jun-98 - Added limited support for long filenames. DOpus _should_ now support
               long filenames in listers and internal operations. However, it does no
               filename translation when copying to a short filename filesystem.

      #1543    Set the environment variable dopus/FilenameLen to the default length
               filename you wish to use (defaults to 34, you can set it to up to 255).

   13-Jul-98 - Added proper error checking to FixIcons command (previously it would just
               silently skip over errors)

             - Fixed problem with the requester function and long filenames (eg Rename).

             - The MakeDir command now supports long filenames

      #1548  - Fixed buffer overflow that could occur when double-clicking on a
               directory name longer than 30 characters (would cause a strange string
               to be displayed in the lister path field).

   22-Jul-98 - Lots of long filename problems fixed in previous versions

             - Triangles now displayed in lister title bar to indicate the current sort
               field and sort order.

             - The list of environment sections is now one character wider in the
               Environment editor to fix problems in some fonts.

             - Delete would fail if you tried to delete a .info file with a filename
               >30 characters

      #1556  - The 'to' display in the progress indicator for the Duplicate function was
               showing the wrong thing.

   23-Jul-98 - Fixed problem which would occur when resizing field titles that had
               been partially scrolled off the left hand side.

             - Fixed long filename problem which could occur in the ftp module with
               filenames greater than 108 characters.

             - Added 'Stretch' option to Environment/Backgrounds for the desktop background
               picture. Not properly tested, doesn't seem to work under Cgx.

   24-Jul-98 - Changed 'Snapshot' terminology
      #1558

   27-Jul-98 - Put lister drag and drop code back to how it was before the previous version;
               the changes didn't fix the drag and drop lock up problems reported by some
               people and in fact seemed to cause new ones.

      #1559  - Made some changes to the way filetypes and versions are displayed in the
               lister. Instead of being updated individually as each file is scanned,
               the changes are cached and updated in batches every few seconds. Also,
               the lister does not try to update the display if layers are locked (say
               due to a drag and drop problem). Hopefully this will help to prevent
               drag and drop lockups.

   29-Jul-98 - Made changes to icon size to make compatible with Workbench.
      #1562

   30-Jul-98 - The 'Caching' section in the Environment has been renamed to 'Directories'.
      #1561    The 'Enable MUFS' flag has been moved to this section, and a new field
               has also been added which lets you configure the maximum filename length.
               The FilenameLen environment variable has been removed.

   10-Aug-98 - Documentation for some previously undocumented ARexx functions:

             - dopus set <item> <parameters>

               Allows you to configure certain items of the DOpus environment.
               Primarily used at this stage for the themes system.

                   background      - previously documented
                   sound           - previously document

                   palette         - configure the DOpus palette

                      Accepts a string of up to 16 hex values;
                      the last 8 represent the Opus colours, and
                      the first 8 represent the system colours when
                      Opus is on its own screen.

                      For example,

                          dopus set palette 0xffaabb 0x000055

                   pens <type>     - configure the pens numbers used
                                     for various things

                      <type> is a string signifying the pen set to
                      alter, and is followed by a number of values
                      which represent which of the pens to use.

                      <type> can be:

                          icons    <dfg> <dbg> <dstyle> <wfg> <wbg> <wstyle>
                          files    <fg> <bg>
                          dirs     <fg> <bg>
                          selfiles <fg> <bg>
                          seldirs  <fg> <bg>
                          devices  <fg> <bg>
                          assigns  <fg> <bg>
                          source   <fg> <bg>
                          dest     <fg> <bg>
                          gauge    <normal> <full>
                          user     <count>

                      The pen number is mapped in the following way:

                          1-4      bottom four system colours
                          5-8      top four system colours
                          9-16     Opus user pens

                   font <type>     - configure the fonts

                      <type> is a string representing the font to
                      be configured.

                          screen   Screen font when Opus is on it's own screen
                          listers  Font used for file display in listers
                          iconsd   Icons on the desktop
                          iconsw   Icons in windows

                      <type> is followed by the font name and size, eg

                          dopus set font screen courier.font 13

             - dopus clear <item>

               Lets you clear a setting (equivalent to doing dopus set with a
               null string).

                   background [desktop|lister|req]
                   sound <event>

             - dopus query <item>

               'dopus query' is the partner of 'dopus set' and lets you
               query the current settings of the various items.

             - dopus refresh <item>

               Lets you refresh the display of certain items:

                   all           refresh the entire display of everything
                   background    already documented
                   icons         refresh icons in all listers and on the desktop
                   lister [full] refresh lister displays

               The various refresh commands are needed after modifying some
               settings with the 'dopus set' command.

             - dopus read

               'dopus read' is mostly previous documented, however there are
               three new flags - hex, ansi, smart - which control the text
               viewer mode. For example,

                   dopus read hex 's:startup-sequence'

               There are actually three already existing undocumented
               commands to achieve the same effect:

                   dopus hexread
                   dopus ansiread
                   dopus smartread

               However, the flag for the 'dopus read' command is more logical.

   29-Aug-98 - Add full snapshot options to groups

      #1563  - Problems with drag'n'drop onto start menus fixed.

    7-Sep-98 - Added 'lister set commentlength' rexx command to set the maximum
               comment length allowed in a lister (similar to 'lister set namelength').
               Note this does not affect the maximum comment length that can be saved
      #1564    to disk, which is fixed at 80 characters.

   16-Sep-98 - Added slider to the volume control in the Environment/Sound Events section.

   19-Sep-98 - Hopefully fixed a problem that was stopping some trapped commands reaching
      #1567    the custom handler (eg even if the Copy command was trapped, the custom handler
               would not be notified if the user specified a full pathname containing a colon
               in the argument string).

   21-Sep-98 - Removed spurious characters at the end of clipboard text when copying filenames
               from listers with ramiga c.

             - Made some changes, hopefully setting the volume of sounds played via sound.datatype
               will be more reliable.

             - Sound Events now supports random sounds by specifying either a directory or
               a wildcard pattern as the sound filename. Random sounds are only assigned when
               the environment is loaded, or when a sound setting is modified - they do not change
               every time they play. You can specify the volume you want a sound file to be played
               at by setting the comment of the sound file to the desired volume (ie a number
               from 1 to 64).

      #1568  - You can now use the file comment of background pictures to specify individual
               settings for that picture, which override the settings configured in the environment.
               This might be useful if you were using random background pictures, and had some
               pictures that needed to be tiled, some that needed to be centered, etc..

               To enable this, the file comment of the picture file must begin with the word "dopus "
               followed by a number of keywords:

                  dopus [tile|center|stretch] [precision <precision>] [border off|<colour>]

                     tile, center, stretch specify the layout of the picture.
                     precision lets you specify the remapping precision: none, gui, icon, image, exact
                     border lets you specify the colour for the border (when a picture is centered),
                     or turn the border off. The colour value is specified in hex.

               If any or all of this information is not provided, the current configuration settings
               will be used instead.

   22-Sep-98 - Added ConvertTheme command to the themes.module. This command can convert a Windows 95
      #1569    theme file to Opus format. This is the equivalent of the SaveTheme command in that the
               filename references are unchanged and the files are not copied. Only the wallpaper
               and sound settings are converted as no others make sense for the Amiga.

   23-Sep-98 - The DiskInfo.module was using signed arithmetic to draw the pie graph, resulting in
               errors for drives over 2gb.

   25-Sep-98 - Photos added to About module

      #1570  - BuildTheme progress bar was opening on defpubscr instead of Opus screen. BuildTheme
               command didn't correctly reference D5THEMES: in the theme file it created.

   28-Sep-98 - The background picture in requesters would be centered even if it was meant to be tiled
               if the desktop background picture was set to centering.

      #1571  - Horizontal slider in listers was not being sized correctly.

   19-Oct-98 - Themes now support random background pictures and sounds (the wildcard path is just
               written straight out to the .theme file - when doing BuildTheme no files will be copied,
               it is up to the theme author to copy the files they want).

   22-Feb-99 - Fixed problem with BuildTheme command which wrote sound files to the Screens directory.

             - Fix icon text problems; text was too close to the icon image, and also Outline mode
               text could leave some pixels behind when the icon was moved.

             - Fixed problem with clipboard copy filenames from lister; would lose the last character
               and cause hits/crashes in ftp listers.

             - Fixed problem with iconify to title bar when fuel gauge is turned on.

             - Fixed problem where Opus wouldn't correctly identify a startmenu if it had a 
               background picture set.

             - Fixed problem with lister memory not being cleared; when one lister was closed and
               a new one opened, some parts of the old lister could be left behind (like custom
               handler, header text, etc). Thanks Dave for finally helping me nail this one!

             - When dragging a lister field header the label displayed in the drag image could be
               wrong.

             - Fixed icon flickering problem when moving a lister.

             - Added support for newmouse wheel mouse (scroll up/down) in listers, not tested

             - Added %it% display item for screen title, shows Swatch Internet Time

      #1600  - Fixed a hit when you try to run Opus twice and then cancel the second copy.

    1-Mar-99 - Hopefully fixed the crash caused by having start menus/button banks with
      #1601    background pictures open on startup (note: seems to be fixed, problems may still
               exist with some particular datatypes, eg ilbm.datatype 44.15, this is a datatype
               problem and you should update to 44.17)

    9-Mar-99 - Fixed the proportional font problem (crashes/hits could result if you were using
               a prop font in a lister and a file beginning with 'j' was visible, maybe other
               situations -> caused by a font bug!!!!)

   12-Mar-99 - DOpus now supports the CX_PRIORITY tooltype to set the priority of its commodity.
               You may be able to use this to resolve conflicts with other commodities like
               MagicMenu.

   15-Mar-99 - Trying to use 24bit ILBM images in buttons/startmenus should no longer crash
               (it's still not supported, but at least it shouldn't crash)

             - The ConvertTheme command will now work if the filename you give it doesn't end
               in .theme

             - ConvertTheme now handles files containing apostrophes correctly.

             - The DiskInfo module pie chart should now be accurate for disks over 2gig
               (someone please test and report back)

             - The text viewer search function would get confused by double letters (eg
               it wouldn't successfully find "scan" in "sscanf")

             - Fixed scrolling bug in simple-refresh listers caused when the lister was
               partially obscured by another window.

             - The Disk filetype should now support volume names containing spaces (put quotes
               around it)

             - Fixed 'var' return option in lister query commands, this also fixes the problem of
               DOPUSRC not being set when it should. Also, the 'dopus getstring' and similar
               commands now return an empty string in RESULT if no string is entered. For
               functions that use DOPUSRC to return a result code, RC is ALWAYS 0 now.

             - Deleting files in icon action mode now correctly deletes the icon as well.

             - IconInfo will now show an error if you try to save an icon that is
               write protected.

             - Fixed start menu bug that caused graphical errors when moving from a sub-menu item
               back to a main menu item.

             - Various fields in the configuration editors now support drag'n'drop - The 'Image'
               field in Function Editors, and the Background picture fields and Sound Event path field
               in the Environment.

             - Drag-select of text in text viewer now selects the first character as soon as you
               click, rather than waiting for you to move and then selecting the first two characters.

             - Hopefully fixed the 'Object in use' when deleting bug.

             - The selection list (Select Command, Select Argument, etc) now remembers its size.

             - Added flags to the LoadButtons and CloseButtons commands.

                   LoadButtons <name> HIDDEN - this will load the button bank but not display it
                   LoadButtons <name> SHOW   - this will reveal a hidden button bank
                   CloseButtons <name> HIDE  - this will hide a visible button bank

             - 'command wait <cmd>' wasn't returning the correct result code in some circumstances.

      #1603  - Clicking the close gadget of a lister no longer acts as an abort for directory
               reads, but will now close the lister in all cases.

             - FTP module 68.4

               Fixed problems with logging into some sites such as freeserve and ftp.thule.no etc.
               Fixed problems with SHIFT DnD in Addressbook causing crash
               Fixed problems with HELP key in Options causing crash

   16-Mar-99 - Possibly may now load pictures into fast ram instead of chip (but I doubt it
               will make any difference). Incidentally, if you would use the v43 picture.datatype
               there would be no problem with this in the first place.

      #1604  - Test version, setenv dopus/testnewmouse 1 to test newmouse wheel stuff.

   18-Mar-99 - Removed the AllocBitMap() patch completely, which we suspect was causing the weird
               problems some people were having with the new version (note; all Picasso users.
               Coincidence? I think not :) The only way now for your background pictures to be
               loaded into fast ram is if you are using v43 picture.datatype or another version
               which supports it. Is this a problem? We can't remember why we added the
               AllocBitMap() patch in the first place, because when you think about it all
      #1605    graphics card users should be using v43 anyway so they get 24 bit support.

             - Fixed problem with selection list which would grow each time it was opened until it
               filled the screen.

             - NewMouse wheel support should work now. You can set the dopus/WheelScrollLines
               environment variable to control the number of lines each wheel turn corresponds
               to (default:3)

      #1606  - The 'dopus request' function now correctly returns RC, this broke when the change
               to 'dopus getstring' was made above (getstring still returns in DOPUSRC, RC will
               always be 0 for this call).

   26-Mar-99 - Hopefully the 'Object in use' bug is now fixed completely (please check, Dave)

             - Fixed the lister crash on close bug

             - Icon label outline fonts are now rendered correctly.

             - Fixed iconified lister icon creep problem.

      #1607  - GetSizes should now support >2GB correctly

    1-Apr-99 - Fixed GetSizes, hopefully for the last time (>2GB problem)

             - The selection list (Select Command, Select Argument, etc) can now be resized
               smaller if its size has previously been saved as larger than the default.

             - Shift + mouse wheel now scrolls in the lister by a page at a time, and ctrl +
               wheel will scroll to top or bottom

             - If you set the dopus/ReturnOfBenify environment variable to 1, then
               icons you leave out by dropping onto the desktop will automatically be
               saved as permanent rather than temporary leftouts.

      #1608  - DOpus would lose track of some changes caused by a filetype action on more
               than one type of file. For example, if you dragged files and folders
               together from one lister to another (or into a sub-directory), then
               both files and folders would be moved but only the files would be
               refreshed (Trevor's problem).

   15-Apr-99 - Fixed refresh bug in icon action smart refresh listers (status bar wasn't
               refreshed properly when lister was resized larger).

             - The ReturnOfBenify flag caused a problem with the display of free space
               in lister titles (which used to be controlled by the Benify flag). Too
               much Benification all round really.

      #1609  - Now uses sysinfo.library from Executive (if present) to do CPU usage
               calculation. Could someone please test this please, as I can't seem to
               get sysinfo.library (or any of the examples) to actually work, and I don't
               want to have to install Executive.

   23-Apr-99 - Fixed a problem with the 'perform all actions' flag and drag/drop copying
               of directories.

      #1610  - With 'perform all actions' flag enabled, DOpus will no longer complain
               about a file already existing if you drag/drop a file and icon to copy (it
               used to try to copy the icon twice).

   26-Oct-99 - Added changes in library for V44 icons and getdiskobject
	     - changes to library, icon.module, program

      #5.82  - Fixed problem with AppIcon changed to use DupDiskObject in library
               Fixed problem for LSHIFT LALT DnD for icon replacement
               Increased screen title text from 120 to 188 chars
	       New library, new icon and config modules, new program
	      	

*/
