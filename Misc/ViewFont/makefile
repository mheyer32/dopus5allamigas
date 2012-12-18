OBJS =	font_data.o font.o font_strings.o

all : font_strings.o ViewFont

font_strings.o : font.strings
	delete >nil: font_strings.o quiet
	sc font_strings.c

ViewFont : $(OBJS)
	slink with <<
define __ctype=___ctype
from lib:c.o $(OBJS)
to ViewFont
lib lib:sc.lib lib:amiga.lib lib:debug.lib lib:dopus.lib
noicons
nd
sd
sc
<
	copy ViewFont dopus5:c

################

.c.o:
	sc $*.c
.asm.o:
	sc:c/asm -iASMINC: $*.asm
.cd.strings:
	catcomp descriptor=$*.cd cfile=$*.strings
