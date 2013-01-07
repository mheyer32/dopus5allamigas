LIBVER = 68
LIBREV = 11
#DEBUGLIB = lib:debug.lib

OBJS =	libinit.o \
		config.o config_drag.o \
		config_settings.o \
		config_environment.o config_environment_data.o \
		config_environment_lister.o \
		config_environment_desktop.o \
		config_environment_palette.o \
		config_environment_output.o \
		config_environment_sounds.o \
		config_environment_display.o \
		config_environment_icons.o \
		config_environment_picture.o \
		config_environment_paths.o \
		config_buttons.o config_buttons_data.o config_buttons_god.o config_buttons_support.o \
		button_editor.o button_editor_data.o \
		function_editor.o function_editor_data.o \
		select_colours.o select_colours_data.o \
		config_convert.o config_convert_data.o old_config.o \
		config_filetypes.o config_filetypes_data.o \
		filetype_edit.o \
		filetype_editor.o fileclass_editor.o \
		lister_menu.o lister_menu_data.o \
		config_menus.o config_menus_data.o \
		config_menus_edit.o config_menus_io.o \
		config_menus_drag.o \
		function_export.o \
		edit.o \
		lsprintf.o \
		string_data.o \
		ipc.o

all: configopus_pragmas.h string_data.h configopus.module

string_data.h : configopus.cd
	catcomp descriptor=configopus.cd cfile=string_data.h

string_data.o : string_data.h
	delete >nil: string_data.o quiet
	sc string_data.c

configopus_pragmas.h: configopus.fd
	fd2pragma configopus.fd configopus_pragmas.h

configopus.module: $(OBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd configopus.fd
from lib:libent.o lib:libinit.o $(OBJS)
to configopus.module-debug
lib lib:sc.lib lib:amiga.lib dopuslib:dopuslib.lib $(DEBUGLIB)
libversion $(LIBVER)
librevision $(LIBREV)
noicons
sd sc
maxhunk 51200
<
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd configopus.fd
from lib:libent.o lib:libinit.o $(OBJS)
to dopus5:modules/configopus.module
lib lib:sc.lib lib:amiga.lib dopuslib:dopuslib.lib $(DEBUGLIB)
libversion $(LIBVER)
librevision $(LIBREV)
noicons
sd
nd
maxhunk 51200
<
	flush

test.o : test.c
	sc test.c nolibcode

test : test.o
	slink with lib:utillib.with with <<
from lib:c.o test.o
to test
lib lib:sc.lib lib:amiga.lib lib:debug.lib
noicons
sc sd nd
<

.c.o:
	sc $*.c
.asm.o:
	sc:c/asm -iASMINC: $*.asm

clean:
	delete ~(string_data).o quiet
	touch >nil: \#?.cd
