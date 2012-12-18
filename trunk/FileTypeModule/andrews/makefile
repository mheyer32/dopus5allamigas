OPTIM		=	nooptim
#OPTIM		=	optim optimpeep optimglobal optimsched optiminline optiminlocal

STDOBJS		=	libinit.o lsprintf.o

FILETYPEOBJS	=	filetype.o filetype_data.o filetype_strings.o
FILETYPEVER	=	1
FILETYPEREV	=	22


filetype.o : filetype.c
	sc filetype.c DEFINE=VERSION="$(FILETYPEVER)" DEFINE=REVISION="$(FILETYPEREV)" $(OPTIM)

filetype_strings.o : filetype.strings
	sc filetype_strings.c

#modules_pragmas.h: modules.fd
#	fd2pragma modules.fd modules_pragmas.h

#########################################################################

filetype.module: $(STDOBJS) $(FILETYPEOBJS)
	slink with lib:utillib.with with <<
define __ctype=___ctype
libprefix _L_
libfd modules.fd
from lib:libent.o lib:libinit.o $(STDOBJS) $(FILETYPEOBJS)
to filetype.module
#lib lib:sc.lib lib:amiga.lib lib:debug.lib dopuslib:dopus.lib
lib lib:sc.lib lib:amiga.lib lib:debug.lib 
libversion $(FILETYPEVER)
librevision $(FILETYPEREV)
noicons
sc sd nd
<
	copy $@ dopus5:modules
	avail flush


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
