LIBVER = 68
LIBREV = 16
#DEBUGLIB = lib:debug.lib

OBJS = libinit.o data.o string_data.o \
	timer.o pathlist.o \
	functions.o gui.o list_management.o \
	misc.o simplerequest.o selection_list.o strings.o \
	drag_routines.o palette_routines.o \
	layout_routines.o layout_support.o layout_utils.o \
	layout_resize.o \
	boopsi.o image_class.o button_class.o listview_class.o palette_class.o \
	dos_patch.o \
	notify.o \
	menu_routines.o \
	bitmap.o \
	args.o \
	rexx.o \
	popup_menus.o ipc.o images.o memory.o popup_support.o \
	config_new.o config_open.o config_default.o config_save.o \
	config_close.o config_copy.o config_misc.o \
	status_window.o read_ilbm.o \
	anim.o \
	buffered_io.o diskio.o wb.o launcher.o iff.o \
	string_hook.o clipboard.o semaphores.o \
	requesters.o \
	progress_win.o \
	appmsg.o \
	search.o \
	dates.o \
	filetypes.o \
	icons.o \
	icon_cache.o \
	devices.o \
	removed.o \
	varargs.o \
	version.o \
	getusage.o \
	savepos.o \
	lsprintf.o

all: string_data.h dopuspragmas.h dopus5.library dopus.lib dopuslib.lib test

string_data.h : dopuslib.cd
	catcomp descriptor=dopuslib.cd cfile=string_data.h

string_data.o : string_data.h string_data.c
	delete >nil: string_data.o quiet
	sc string_data.c

dopuspragmas.h: dopus_lib.fd
	fd2pragma dopus_lib.fd dopuspragmas.h

dopus5.library: $(OBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd dopus_lib.fd
from lib:libent.o lib:libinit.o $(OBJS)
to dopus5.library
lib lib:sc.lib lib:pools.lib lib:amiga.lib lib:asyncio.lib $(DEBUGLIB)
libversion $(LIBVER)
librevision $(LIBREV)
noicons
maxhunk 51200
sc sd
<
	slink from dopus5.library to dopus5:libs/dopus5.library nd noicons
	flush

test: test.c
	slink with lib:utillib.with with <<
define __ctype=___ctype
from lib:c.o test.o
to test
lib lib:sc.lib lib:pools.lib lib:amiga.lib lib:asyncio.lib $(DEBUGLIB)
noicons
sc sd
<

dopuslib.o : dopuslib.c
	sc dopuslib.c nolibcode

dopusliblib.o : dopuslib.c
	copy dopuslib.c dopusliblib.c
	sc dopusliblib.c libcode
	delete >nil: dopusliblib.c

dopuslib.lib: dopusliblib.o lsprintf.o
	oml dopuslib.lib r dopusliblib.o lsprintf.o
	copy dopuslib.lib dopusmod:

dopus.lib: dopuslib.o lsprintf.o
	oml dopus.lib r dopuslib.o lsprintf.o
	copy dopus.lib lib:

.c.o:
	sc $*.c
.asm.o:
	sc:c/asm -iASMINC: $*.asm

#########################################################################

clean:
	delete ~(string_data).o quiet
	touch >nil: \#?.cd
