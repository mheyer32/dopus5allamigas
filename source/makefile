# Main Dopus5 makefile

###########################################################
# Enter debug=no on "Make" command line to disable debug output.
export debug
###########################################################
# Example Commands:

# make os4
# Compiles debug version of dopus5 components for OS4.

# make MOS debug=no
# Compiles normal (non-debug) version of dopus5 components for MorphOS.

# make OS3 release
# Compiles debug version of dopus5 components for OS3 & creates
# release archive.

# make i386-aros release debug=no
# Compiles normal version of dopus5 components for AROS & creates
# release archive.
###########################################################
# Read platform arguments from the "Make" command line:
# Acceptable platform arguments are os3, os4, or mos.
PLATFORM:= none
COUNT:=
ifeq ($(findstring os3, $(MAKECMDGOALS)),os3)
	PLATFORM:= os3
	COUNT:= $(COUNT) num
endif
ifeq ($(findstring os4, $(MAKECMDGOALS)),os4)
	PLATFORM:= os4
	COUNT:= $(COUNT) num
endif
ifeq ($(findstring mos, $(MAKECMDGOALS)),mos)
	PLATFORM:= mos
	COUNT:= $(COUNT) num
endif
ifeq ($(findstring i386-aros, $(MAKECMDGOALS)),i386-aros)
	PLATFORM:= i386-aros
	COUNT:= $(COUNT) num
endif

# Generate error if no platform entered on "Make" command line.
ifeq ($(PLATFORM), none)
$(error Error: Enter a platform (os3, os4, i386-aros, or mos).)
endif

#Generate error if multiple platforms entered on "Make" command line.
ifneq ($(words $(COUNT)), 1)
$(error Error: Enter only one platform (os3, os4, i386-aros, or mos))
endif

# Compile all if only a platform is entered on "Make" command line.
ifeq ($(strip $(filter-out $(PLATFORM), $(MAKECMDGOALS))),)
$(PLATFORM) : all
endif
###########################################################
# Sets archive filename platform name & version.
#NAME := $(shell echo $(PLATFORM) | tr '[:lower:]' '[:upper:]')
ifeq ($(debug), no)
TYPE :=
VERSION := _90_
else
TYPE := _debug
VERSION := _90_dev_
endif
###########################################################
# Sets compile system
HOST := $(shell uname)
ifeq ($(HOST), AmigaOS)
	SYSTEM := amiga
endif
ifeq ($(HOST), MorphOS)
	SYSTEM := amiga
endif
ifeq ($(HOST), AROS)
	SYSTEM := amiga
endif
###########################################################
# Sets destination directory and lha command
DEST := ../releases/
ifeq ($(SYSTEM), amiga)
ARCDEST := /releases/
LHA := lha a -a -r -q
else
ARCDEST := $(DEST)
LHA := lha ao5q
endif
###########################################################
# Commands
REMOVE := rm -rf
COPY := cp -p
MAKEDIR := mkdir -p
###########################################################

#.PHONY : all
all : program library modules commands

.PHONY : program
program:
	@echo " "
	@echo "<<<<<<<<<<<<<<<<<< program >>>>>>>>>>>>>>>>>>"
	@$(MAKE) -C Program -f makefile.$(PLATFORM)

.PHONY : library
library:
	@echo " "
	@echo "<<<<<<<<<<<<<<<<<< library >>>>>>>>>>>>>>>>>>"
	@$(MAKE) -C Library -f makefile.$(PLATFORM)

.PHONY : modules
modules:
	@echo " "
	@echo "<<<<<<<<<<<<<<<<<< modules >>>>>>>>>>>>>>>>>>"
	@$(MAKE) -C Modules $(PLATFORM)

.PHONY : commands
commands:
	@echo " "
	@echo "<<<<<<<<<<<<<<<<<< commands >>>>>>>>>>>>>>>>>"
	@$(MAKE) -C Misc/C $(PLATFORM)

###########################################################

.PHONY : clean
clean : clean-program clean-library clean-modules clean-commands

.PHONY : cleanall
cleanall : clean
	@echo " "
	@echo "++++++++++++++ clean binaries ++++++++++++++"
	@$(REMOVE) bin.$(PLATFORM)

.PHONY : clean-program
clean-program:
	@echo " "
	@echo "++++++++++++++ clean program +++++++++++++++"
	@$(MAKE) -C Program -s -f makefile.$(PLATFORM) clean

.PHONY : clean-library
clean-library:
	@echo " "
	@echo "++++++++++++++ clean library +++++++++++++++"
	@$(MAKE) -C Library -s -f makefile.$(PLATFORM) clean

.PHONY : clean-modules
clean-modules:
	@echo " "
	@echo "++++++++++++++ clean modules +++++++++++++++"
	@$(MAKE) -C Modules -s $(PLATFORM) clean

.PHONY : clean-commands
clean-commands:
	@echo " "
	@echo "++++++++++++++ clean commands ++++++++++++++"
	@$(MAKE) -C Misc/C -s $(PLATFORM) clean

###########################################################

.PHONY : release
release: cleanall all
	@echo " "
	@echo ">>>>>Creating release archive: Dopus5$(VERSION)$(PLATFORM)$(TYPE).lha"
	@$(MAKEDIR) Dopus5/Libs
	@$(MAKEDIR) Dopus5/Modules
	@$(MAKEDIR) Dopus5/C
	@$(MAKEDIR) $(DEST)
	@$(COPY) bin.$(PLATFORM)/dopus5.library Dopus5/Libs
	@$(COPY) bin.$(PLATFORM)/*.module Dopus5/Modules
	@$(COPY) bin.$(PLATFORM)/DirectoryOpus Dopus5
# Temporary change until DOpusRT5 is fixed
#	@$(COPY) bin.$(PLATFORM)/DOpusRT5 Dopus5/C
	@$(COPY) ../archive/DOpusRT5  Dopus5/C
	@$(COPY) bin.$(PLATFORM)/LoadDB Dopus5/C
	@$(COPY) bin.$(PLATFORM)/viewfont Dopus5/C
	@$(COPY) ../archive/basedata.lha $(DEST)Dopus5$(VERSION)$(PLATFORM)$(TYPE).lha
	@$(LHA) $(ARCDEST)Dopus5$(VERSION)$(PLATFORM)$(TYPE).lha Dopus5
	@$(REMOVE) Dopus5

###########################################################

.PHONY : clean-release
clean-release: cleanall
	@echo " "
	@echo "++++++++++++++ clean release +++++++++++++++"
	@$(REMOVE) $(DEST)

###########################################################

# Dummy targets to quietly dispose of platform
# commands when entered as a goal for "make"
# on the command line (like: make os3).

.PHONY : os3 os4 mos i386-aros
os3: mos
os4: mos
i386-aros: mos
mos:
	-@sh -c "echo -n"
