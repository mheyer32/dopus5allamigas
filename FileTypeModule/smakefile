#OPTIM		=	nooptim
OPTIM		=	optim optimpeep optimglobal optimsched optiminline optiminlocal

STDOBJS		=	libinit.o lsprintf.o

FILETYPEOBJS	=	filetype.o filetype_data.o filetype_strings.o
FILETYPEVER	=	1
FILETYPEREV	=	22

SHOWOBJS	=	show.o show_data.o show_strings.o
SHOWVER		=       44
SHOWREV		=       16

FONTOBJS	=	font.o font_data.o font_strings.o
FONTVER		=       44
FONTREV		=       1

PLAYOBJS	=	play.o play_data.o play_strings.o
PLAYVER		=       44
PLAYREV		=       15

MISCOBJS	=	misc.o misc_data.o misc_strings.o
MISCVER		=       44
MISCREV		=       12

ICONOBJS	=	icon.o icon_data.o icon_strings.o
ICONVER		=       44
ICONREV		=       26

FORMATOBJS	=	format.o format_data.o format_strings.o
FORMATVER	=       44
FORMATREV	=       20

DISKCOPYOBJS	=	diskcopy.o diskcopy_data.o diskcopy_strings.o
DISKCOPYVER	=       44
DISKCOPYREV	=       22

READOBJS	=	read.o read_data.o read_strings.o
READVER		=       44
READREV		=       18

PRINTOBJS	=	print.o print_data.o print_strings.o
PRINTVER	=       44
PRINTREV	=       12

REGOBJS		=	register.o register_data.o register_strings.o
REGVER		=       44
REGREV		=       18

LISTFORMATOBJS	=	listerformat.o listerformat_data.o listerformat_strings.o
LISTFORMATVER	=       44
LISTFORMATREV	=       14

DISKINFOOBJS	=	diskinfo.o diskinfo_data.o diskinfo_strings.o
DISKINFOVER	=       44
DISKINFOREV	=       18

PATHFORMATOBJS	=	pathformat.o pathformat_data.o pathformat_strings.o
PATHFORMATVER	=       45
PATHFORMATREV	=       10

ABOUTOBJS	=	about.o about_data.o
ABOUTVER	=       44
ABOUTREV	=       16

RECYCLEBINOBJS	=	recyclebin.o recyclebin_data.o recyclebin_strings.o
RECYCLEBINVER	=	44
RECYCLEBINREV	=	1

ICONCLOCKOBJS	=	iconclock.o iconclock_data.o iconclock_strings.o
ICONCLOCKVER	=	44
ICONCLOCKREV	=	1

UPDATEOBJS	=	update.o update_data.o update_strings.o
UPDATEVER	=	44
UPDATEREV	=	1

ICON39OBJS	=	icon39.o icon39_data.o icon39_strings.o
ENVOYOBJS	=	envoy.o envoy_data.o envoy_strings.o

#########################################################################

all:		modules_pragmas.h \
		filetype.strings filetype.module \
		show.strings show.module \
		play.strings play.module \
		misc.strings misc.module \
		icon.strings icon.module \
		format.strings format.module \
		diskcopy.strings diskcopy.module \
		read.strings read.module \
		print.strings print.module \
		register.strings register.module \
		listerformat.strings listerformat.module \
		pathformat.strings pathformat.module \
		diskinfo.strings diskinfo.module \
		recyclebin.strings recyclebin.module \
		iconclock.strings iconclock.module \
		update.strings update.module \
		envoy.strings envoy.module \
		about.module

#########################################################################

filetype.o : filetype.c
	sc filetype.c DEFINE=VERSION="$(FILETYPEVER)" DEFINE=REVISION="$(FILETYPEREV)" $(OPTIM)

filetype_strings.o : filetype.strings
#	delete >nil: filetype_strings.o quiet
	sc filetype_strings.c

show_strings.o : show.strings
	delete >nil: show_strings.o quiet
	sc show_strings.c

font_strings.o : font.strings
	delete >nil: font_strings.o quiet
	sc font_strings.c

play_strings.o : play.strings
	delete >nil: play_strings.o quiet
	sc play_strings.c

misc_strings.o : misc.strings
	delete >nil: misc_strings.o quiet
	sc misc_strings.c

icon_strings.o : icon.strings
	delete >nil: icon_strings.o quiet
	sc icon_strings.c

icon39_strings.o : icon39.strings
	delete >nil: icon39_strings.o quiet
	sc icon39_strings.c

format_strings.o : format.strings
	delete >nil: format_strings.o quiet
	sc format_strings.c

diskcopy_strings.o : diskcopy.strings
	delete >nil: diskcopy_strings.o quiet
	sc diskcopy_strings.c

read_strings.o : read.strings
	delete >nil: read_strings.o quiet
	sc read_strings.c

print_strings.o : print.strings
	delete >nil: print_strings.o quiet
	sc print_strings.c

register_strings.o : register.strings
	delete >nil: register_strings.o quiet
	sc register_strings.c

listerformat_strings.o : listerformat.strings
	delete >nil: listerformat_strings.o quiet
	sc listerformat_strings.c

pathformat_strings.o : pathformat.strings
	delete >nil: pathformat_strings.o quiet
	sc pathformat_strings.c

diskinfo_strings.o : diskinfo.strings
	delete >nil: diskinfo_strings.o quiet
	sc diskinfo_strings.c

recyclebin_strings.o : recyclebin.strings
	delete >nil: recyclebin_strings.o quiet
	sc recyclebin_strings.c

iconclock_strings.o : iconclock.strings
	delete >nil: iconclock_strings.o quiet
	sc iconclock_strings.c

update_strings.o : update.strings
	delete >nil: update_strings.o quiet
	sc update_strings.c

envoy_strings.o : envoy.strings
	delete >nil: envoy_strings.o quiet
	sc envoy_strings.c

modules_pragmas.h: modules.fd
	fd2pragma modules.fd modules_pragmas.h

#########################################################################

filetype.module: $(STDOBJS) $(FILETYPEOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(FILETYPEOBJS)
to filetype.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(FILETYPEVER)
librevision $(FILETYPEREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

show.module: $(STDOBJS) $(SHOWOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(SHOWOBJS)
to show.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(SHOWVER)
librevision $(SHOWREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

font.module: $(STDOBJS) $(FONTOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(FONTOBJS)
to font.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(FONTVER)
librevision $(FONTREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

play.module: $(STDOBJS) $(PLAYOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(PLAYOBJS)
to play.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(PLAYVER)
librevision $(PLAYREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

misc.module: $(STDOBJS) $(MISCOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(MISCOBJS)
to misc.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(MISCVER)
librevision $(MISCREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

icon.module: $(STDOBJS) $(ICONOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(ICONOBJS)
to icon.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(ICONVER)
librevision $(ICONREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

icon39.module: $(STDOBJS) $(ICON39OBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(ICON39OBJS)
to icon39.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion 44
librevision 12
noicons
sc sd nd
<


#########################################################################

format.module: $(STDOBJS) $(FORMATOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(FORMATOBJS)
to format.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(FORMATVER)
librevision $(FORMATREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

diskcopy.module: $(STDOBJS) $(DISKCOPYOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(DISKCOPYOBJS)
to diskcopy.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(DISKCOPYVER)
librevision $(DISKCOPYREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

read.module: $(STDOBJS) $(READOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(READOBJS)
to read.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(READVER)
librevision $(READREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

print.module: $(STDOBJS) $(PRINTOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(PRINTOBJS)
to print.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(PRINTVER)
librevision $(PRINTREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

register.module: $(STDOBJS) $(REGOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(REGOBJS)
to register.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(REGVER)
librevision $(REGREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

listerformat.module: $(STDOBJS) $(LISTFORMATOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(LISTFORMATOBJS)
to listerformat.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(LISTFORMATVER)
librevision $(LISTFORMATREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

pathformat.module: $(STDOBJS) $(PATHFORMATOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(PATHFORMATOBJS)
to pathformat.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(PATHFORMATVER)
librevision $(PATHFORMATREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

diskinfo.module: $(STDOBJS) $(DISKINFOOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(DISKINFOOBJS)
to diskinfo.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(DISKINFOVER)
librevision $(DISKINFOREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

recyclebin.module: $(STDOBJS) $(RECYCLEBINOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(RECYCLEBINOBJS)
to recyclebin.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(RECYCLEBINVER)
librevision $(RECYCLEBINREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

iconclock.module: $(STDOBJS) $(ICONCLOCKOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(ICONCLOCKOBJS)
to iconclock.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(ICONCLOCKVER)
librevision $(ICONCLOCKREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

update.module: $(STDOBJS) $(UPDATEOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(UPDATEOBJS)
to update.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(UPDATEVER)
librevision $(UPDATEREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

about.module: $(STDOBJS) $(ABOUTOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(ABOUTOBJS)
to about.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion $(ABOUTVER)
librevision $(ABOUTREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	flush

#########################################################################

envoy.module: $(STDOBJS) $(ENVOYOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(ENVOYOBJS)
to envoy.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
libversion 44
librevision 13
noicons
sc sd nd
<
#	copy $@ dopus5:modules
	avail flush

#########################################################################

test.o : test.c
	sc test.c nolibcode

test : test.o
	slink with lib:utillib.with with <<
from lib:c.o test.o
to test
lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
noicons
sc sd nd
<


#########################################################################

.c.o:
	sc $*.c $(OPTIM)
.asm.o:
	sc:c/asm -iASMINC: $*.asm
.cd.strings:
	catcomp descriptor=$*.cd cfile=$*.strings

#########################################################################

clean:
	delete ~(\#?_strings).o quiet
	touch >nil: \#?.cd
