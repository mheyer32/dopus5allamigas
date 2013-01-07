STDOBJS			=	libinit.o lsprintf.o
REGOBJS			=	register.o register_data.o register_strings.o

#########################################################################

all:		modules_pragmas.h \
		register.strings register.module

#########################################################################

register_strings.o : register.strings
	delete >nil: register_strings.o quiet
	sc register_strings.c

register.module: $(STDOBJS) $(REGOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(REGOBJS)
to register.module
lib lib:sc.lib lib:amiga.lib lib:debug.lib 
libversion 55
librevision 99
noicons
sc sd nd
<

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
