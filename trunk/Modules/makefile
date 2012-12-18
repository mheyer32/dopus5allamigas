#DEBUGLIB    =   lib:debug.lib
STDOBJS     =   libinit.o lsprintf.o

SHOWOBJS    =   show.o show_data.o show_strings.o
SHOWVER     =       68
SHOWREV     =       0

PLAYOBJS    =   play.o play_data.o play_strings.o
PLAYVER     =       68
PLAYREV     =       0

MISCOBJS    =   misc.o misc_data.o misc_strings.o
MISCVER     =       68
MISCREV     =       0

ICONOBJS    =   icon.o icon_data.o icon_strings.o
ICONVER     =       68
ICONREV     =       17

FORMATOBJS  =   format.o format_data.o format_strings.o
FORMATVER   =       68
FORMATREV   =       0

DISKCOPYOBJS    =   diskcopy.o diskcopy_data.o diskcopy_strings.o
DISKCOPYVER =       68
DISKCOPYREV =       0

READOBJS    =   read.o read_data.o read_strings.o
READVER     =       68
READREV     =       10

JOINOBJS    =   join.o join_data.o join_strings.o
JOINVER     =       68
JOINREV     =       0

PRINTOBJS   =   print.o print_data.o print_strings.o
PRINTVER    =       68
PRINTREV    =       0

REGOBJS     =   register.o register_data.o register_strings.o
REGVER      =       68
REGREV      =       0

LISTFORMATOBJS  =   listerformat.o listerformat_data.o listerformat_strings.o
LISTFORMATVER   =       68
LISTFORMATREV   =       0

DISKINFOOBJS    =   diskinfo.o diskinfo_data.o diskinfo_strings.o
DISKINFOVER =       68
DISKINFOREV =       10

FIXICONSOBJS   =   fixicons.o fixicons_data.o fixicons_strings.o
FIXICONSVER    =   68
FIXICONSREV    =   0

THEMESOBJS    =   themes.o themes_data.o themes_strings.o
THEMESVER =       68
THEMESREV =       10

ABOUTOBJS   =   about.o about_data.o about_jon.o about_greg.o about_leo.o about_andrew.o about_ben.o about_juggler.o about_coopers.o about_bill.o about_thomas.o about_john.o about_trevor.o about_ash.o about_frederic.o about_tick.o about_harv.o about_martin.o about_dave.o
ABOUTVER    =       68
ABOUTREV    =       10

UPDATEOBJS  =   update.o update_data.o update_strings.o
UPDATEVER   =   68
UPDATEREV   =   0

CLEANUPOBJS =   cleanup.o cleanup_data.o cleanup_strings.o
CLEANUPVER  =   68
CLEANUPREV  =   0

FILETYPEOBJS    =   filetype.o filetype_data.o filetype_strings.o
FILETYPEVER =       68
FILETYPEREV =       0

RECYCLEBINOBJS  =   recyclebin.o recyclebin_data.o recyclebin_strings.o
RECYCLEBINVER   =   44
RECYCLEBINREV   =   2

ICONCLOCKOBJS   =   iconclock.o iconclock_data.o iconclock_strings.o
ICONCLOCKVER    =   55
ICONCLOCKREV    =   1

FTPMYOBJS   = ftp/ftp_ver.o  ftp/ftp_main.o ftp/ftp_lister.o ftp/ftp_lister_list.o \
	      ftp/ftp_lister_xfer.o ftp/ftp_lister_connect.o ftp/ftp.o \
              ftp/ftp_arexx.o ftp/ftp_util.o ftp/ftp_recursive.o \
              ftp/ftp_addressbook.o ftp/ftp_addrsupp.o ftp/ftp_addrformat.o \
              ftp/ftp_protect.o

	
FTPOBJS	    = ftp/ftp_module.o ftp/ftp_data.o ftp/ftp_strings.o $(FTPMYOBJS)
FTPVER 	    =  68
FTPREV      =  14

ENVOYOBJS   =   envoy.o envoy_data.o envoy_strings.o

#########################################################################

#		ftp/ftp.strings ftp.module \

all:        modules_pragmas.h \
		show.strings show.module \
		play.strings play.module \
		misc.strings misc.module \
		icon.strings icon.module \
		format.strings format.module \
		diskcopy.strings diskcopy.module \
		read.strings read.module \
		join.strings join.module \
		print.strings print.module \
		register.strings register.module \
		listerformat.strings listerformat.module \
		diskinfo.strings diskinfo.module \
		fixicons.strings fixicons.module \
		themes.strings themes.module \
		filetype.strings filetype.module \
		update.strings update.module \
		cleanup.strings cleanup.module \
		about.module


#		envoy.strings envoy.module \
#		iconclock.strings iconclock.module \
#########################################################################

show_strings.o : show.strings
	delete >nil: show_strings.o quiet
	sc show_strings.c

play_strings.o : play.strings
	delete >nil: play_strings.o quiet
	sc play_strings.c

misc_strings.o : misc.strings
	delete >nil: misc_strings.o quiet
	sc misc_strings.c

icon_strings.o : icon.strings
	delete >nil: icon_strings.o quiet
	sc icon_strings.c

format_strings.o : format.strings
	delete >nil: format_strings.o quiet
	sc format_strings.c

diskcopy_strings.o : diskcopy.strings
	delete >nil: diskcopy_strings.o quiet
	sc diskcopy_strings.c

read_strings.o : read.strings
	delete >nil: read_strings.o quiet
	sc read_strings.c

join_strings.o : join.strings
	delete >nil: join_strings.o quiet
	sc join_strings.c

print_strings.o : print.strings
	delete >nil: print_strings.o quiet
	sc print_strings.c

register_strings.o : register.strings
	delete >nil: register_strings.o quiet
	sc register_strings.c

listerformat_strings.o : listerformat.strings
	delete >nil: listerformat_strings.o quiet
	sc listerformat_strings.c

diskinfo_strings.o : diskinfo.strings
	delete >nil: diskinfo_strings.o quiet
	sc diskinfo_strings.c

fixicons_strings.o : fixicons.strings
	delete >nil: fixicons_strings.o quiet
	sc fixicons_strings.c

themes_strings.o : themes.strings
	delete >nil: themes_strings.o quiet
	sc themes_strings.c

filetype_strings.o : filetype.strings
	delete >nil: filetype_strings.o quiet
	sc filetype_strings.c

ftp/ftp_strings.o : ftp/ftp.strings
	delete >nil: ftp/ftp_strings.o quiet
	sc ftp/ftp_strings.c

recyclebin_strings.o : recyclebin.strings
	delete >nil: recyclebin_strings.o quiet
	sc recyclebin_strings.c

iconclock_strings.o : iconclock.strings
	delete >nil: iconclock_strings.o quiet
	sc iconclock_strings.c

update_strings.o : update.strings
	delete >nil: update_strings.o quiet
	sc update_strings.c

cleanup_strings.o : cleanup.strings
	delete >nil: cleanup_strings.o quiet
	sc cleanup_strings.c

envoy_strings.o : envoy.strings
	delete >nil: envoy_strings.o quiet
	sc envoy_strings.c

modules_pragmas.h: modules.fd
	fd2pragma modules.fd modules_pragmas.h

#########################################################################

show.module: $(STDOBJS) $(SHOWOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(SHOWOBJS)
to show.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(SHOWVER)
librevision $(SHOWREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

play.module: $(STDOBJS) $(PLAYOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(PLAYOBJS)
to play.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(PLAYVER)
librevision $(PLAYREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

misc.module: $(STDOBJS) $(MISCOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(MISCOBJS)
to misc.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(MISCVER)
librevision $(MISCREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

icon.module: $(STDOBJS) $(ICONOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(ICONOBJS)
to icon.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(ICONVER)
librevision $(ICONREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

format.module: $(STDOBJS) $(FORMATOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(FORMATOBJS)
to format.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(FORMATVER)
librevision $(FORMATREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

diskcopy.module: $(STDOBJS) $(DISKCOPYOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(DISKCOPYOBJS)
to diskcopy.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(DISKCOPYVER)
librevision $(DISKCOPYREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

read.module: $(STDOBJS) $(READOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(READOBJS)
to read.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(READVER)
librevision $(READREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

join.module: $(STDOBJS) $(JOINOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(JOINOBJS)
to join.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(JOINVER)
librevision $(JOINREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

print.module: $(STDOBJS) $(PRINTOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(PRINTOBJS)
to print.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(PRINTVER)
librevision $(PRINTREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

register.module: $(STDOBJS) $(REGOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(REGOBJS)
to register.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(REGVER)
librevision $(REGREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	slink from $@ to dopus5:modules/register.module-release nd noicons
	flush

#########################################################################

listerformat.module: $(STDOBJS) $(LISTFORMATOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(LISTFORMATOBJS)
to listerformat.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(LISTFORMATVER)
librevision $(LISTFORMATREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

diskinfo.o: diskinfo.c
	sc $*.c math=ffp globalsymboltable=sas6:include30ffp.gst

diskinfo.module: $(STDOBJS) $(DISKINFOOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(DISKINFOOBJS)
to diskinfo.module
lib lib:scmffp.lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(DISKINFOVER)
librevision $(DISKINFOREV)
noicons
sc sd 
<
	slink from diskinfo.module to dopus5:modules/diskinfo.module nd noicons
	flush

#########################################################################

fixicons.module: $(STDOBJS) $(FIXICONSOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(FIXICONSOBJS)
to fixicons.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(FIXICONSVER)
librevision $(FIXICONSREV)
noicons
sc sd 
<
	slink from fixicons.module to dopus5:modules/fixicons.module nd noicons
	flush

#########################################################################

themes.module: $(STDOBJS) $(THEMESOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(THEMESOBJS)
to themes.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(THEMESVER)
librevision $(THEMESREV)
noicons
sc sd 
<
	slink from themes.module to dopus5:modules/themes.module nd noicons
	flush

#########################################################################

filetype.module: $(STDOBJS) $(FILETYPEOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(FILETYPEOBJS)
to filetype.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(FILETYPEVER)
librevision $(FILETYPEREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

ftp.module: $(STDOBJS) $(FTPOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(FTPOBJS)
to ftp.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(FTPVER)
librevision $(FTPREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	avail flush

#########################################################################

recyclebin.module: $(STDOBJS) $(RECYCLEBINOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(RECYCLEBINOBJS)
to recyclebin.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(RECYCLEBINVER)
librevision $(RECYCLEBINREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

iconclock.module: $(STDOBJS) $(ICONCLOCKOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(ICONCLOCKOBJS)
to iconclock.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(ICONCLOCKVER)
librevision $(ICONCLOCKREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

update.module: $(STDOBJS) $(UPDATEOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(UPDATEOBJS)
to update.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(UPDATEVER)
librevision $(UPDATEREV)
noicons
sc sd nd
<
	copy $@ to dopus5:modules
	flush

#########################################################################

cleanup.module: $(STDOBJS) $(CLEANUPOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(CLEANUPOBJS)
to cleanup.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(CLEANUPVER)
librevision $(CLEANUPREV)
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

about.module: $(STDOBJS) $(ABOUTOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(ABOUTOBJS)
to about.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion $(ABOUTVER)
librevision $(ABOUTREV)
noicons
sc 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

envoy.module: $(STDOBJS) $(ENVOYOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(ENVOYOBJS)
to envoy.module
lib lib:sc.lib lib:amiga.lib $(DEBUGLIB) dopuslib.lib
libversion 44
librevision 13
noicons
sc sd 
<
	slink from $@ to dopus5:modules/$@ nd noicons
	flush

#########################################################################

.c.o:
	sc $*.c
.asm.o:
	sc:c/asm -iASMINC: $*.asm
.cd.strings:
	catcomp descriptor=$*.cd cfile=$*.strings

#########################################################################

clean:
	delete ~(\#?_strings).o quiet
	touch >nil: \#?.cd
