# Main Dopus5 makefile

###########################################################
# Enter debug=no on "Make" command line to disable debug output.
export debug
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


.PHONY : all
all : program library modules

.PHONY : program
program:
	@echo " "
	@echo "+++++++++++++++++ program ++++++++++++++++++"
	@$(MAKE) -C Program -f makefile.$(PLATFORM)

.PHONY : library
library:
	@echo " "
	@echo "+++++++++++++++++ library ++++++++++++++++++"
	@$(MAKE) -C Library -f makefile.$(PLATFORM)

.PHONY : modules
modules:
	@echo " "
	@echo "+++++++++++++++++ modules ++++++++++++++++++"
	@$(MAKE) -C Modules $(PLATFORM)

###########################################################

.PHONY : clean
clean : clean-program clean-library clean-modules

.PHONY : clean-program
clean-program:
	@echo " "
	@echo "++++++++++++++ clean program +++++++++++++++"
	@$(MAKE) -C Program -f makefile.$(PLATFORM) clean

.PHONY : clean-library
clean-library:
	@echo " "
	@echo "++++++++++++++ clean library +++++++++++++++"
	@$(MAKE) -C Library -f makefile.$(PLATFORM) clean

.PHONY : clean-modules
clean-modules:
	@echo " "
	@echo "++++++++++++++ clean modules +++++++++++++++"
	@$(MAKE) -C Modules $(PLATFORM) clean

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
