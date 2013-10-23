# Dopus5 commands makefile

###########################################################
# Enter debug=no on "Make" command line to disable debug output.
export debug
###########################################################
# Enter arch=<i386|arm> on "Make" command line to select the AROS architecture
export arch
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
ifeq ($(findstring aros, $(MAKECMDGOALS)),aros)
	PLATFORM:= aros
	COUNT:= $(COUNT) num
endif

#Generate error if multiple platforms entered on "Make" command line.
ifneq ($(words $(COUNT)), 1)
$(error Error: Enter only one platform (os3, os4, aros, or mos))
endif

# Generate error if no platform entered on "Make" command line.
ifeq ($(PLATFORM), none)
$(error Error: Enter a platform (os3, os4, aros, or mos).)
endif

# Compile all if only a platform is entered on "Make" command line.
ifeq ($(strip $(filter-out $(PLATFORM), $(MAKECMDGOALS))),)
$(PLATFORM) : all
endif
###########################################################


.PHONY : all
all : dopusrt loaddb viewfont

.PHONY : dopusrt
dopusrt:
	@echo " "
	@echo "================== dopusrt ================="
	@$(MAKE) -C dopusrt -f makefile.$(PLATFORM)

.PHONY : loaddb
loaddb:
	@echo " "
	@echo "================== loaddb =================="
	@$(MAKE) -C loadwb -f makefile.$(PLATFORM)

.PHONY : viewfont
viewfont:
	@echo " "
	@echo "================= viewfont ================="
	@$(MAKE) -C ViewFont -f makefile.$(PLATFORM)


###########################################################

.PHONY : clean
clean:	clean-dopusrt clean-loaddb clean-viewfont

.PHONY : clean-dopusrt
clean-dopusrt:
	@echo " "
	@echo "--------------- clean dopusrt --------------"
	@$(MAKE) -C dopusrt -f makefile.$(PLATFORM) clean
	
.PHONY : clean-loaddb
clean-loaddb:
	@echo " "
	@echo "--------------- clean loaddb ---------------"
	@$(MAKE) -C loadwb -f makefile.$(PLATFORM) clean

.PHONY : clean-viewfont
clean-viewfont:
	@echo " "
	@echo "-------------- clean viewfont --------------"
	@$(MAKE) -C ViewFont -f makefile.$(PLATFORM) clean


###########################################################

# Dummy targets to quietly dispose of platform
# commands when entered as a goal for "make"
# on the command line (like: make os3).

.PHONY : os3 os4 mos aros
os3: mos
os4: mos
aros: mos
mos:
	-@sh -c "echo -n"

