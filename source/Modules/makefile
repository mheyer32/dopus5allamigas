# Dopus5 modules makefile

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

#Generate error if multiple platforms entered on "Make" command line.
ifneq ($(words $(COUNT)), 1)
$(error Error: Enter only one platform (os3, os4, i386-aros, or mos))
endif

# Generate error if no platform entered on "Make" command line.
ifeq ($(PLATFORM), none)
$(error Error: Enter a platform (os3, os4, i386-aros, or mos).)
endif

# Compile all if only a platform is entered on "Make" command line.
ifeq ($(strip $(filter-out $(PLATFORM), $(MAKECMDGOALS))),)
$(PLATFORM) : all
endif
###########################################################


.PHONY : all
all : about cleanup configopus diskcopy diskinfo filetype fixicons format ftp icon join listerformat misc pathformat play print read show themes xadopus

.PHONY : about
about:
	@echo " "
	@echo "############### about_module ###############"
	@$(MAKE) -C about -f makefile.$(PLATFORM)

.PHONY : cleanup
cleanup:
	@echo " "
	@echo "############## cleanup_module ##############"
	@$(MAKE) -C cleanup -f makefile.$(PLATFORM)

.PHONY : configopus
configopus:
	@echo " "
	@echo "############## configopus_module ##############"
	@$(MAKE) -C configopus -f makefile.$(PLATFORM)

.PHONY : diskcopy
diskcopy:
	@echo " "
	@echo "############## diskcopy_module ##############"
	@$(MAKE) -C diskcopy -f makefile.$(PLATFORM)

.PHONY : diskinfo
diskinfo:
	@echo " "
	@echo "############## diskinfo_module ##############"
	@$(MAKE) -C diskinfo -f makefile.$(PLATFORM)
		
.PHONY : filetype
filetype:
	@echo " "
	@echo "############## filetype_module #############"
	@$(MAKE) -C filetype -f makefile.$(PLATFORM)

.PHONY : fixicons
fixicons:
	@echo " "
	@echo "############## fixicons_module #############"
	@$(MAKE) -C fixicons -f makefile.$(PLATFORM)

.PHONY : format
format:
	@echo " "
	@echo "############## format_module #############"
	@$(MAKE) -C format -f makefile.$(PLATFORM)
	
.PHONY : ftp
ftp:
	@echo " "
	@echo "############## ftp_module #############"
	@$(MAKE) -C ftp -f makefile.$(PLATFORM)

.PHONY : icon
icon:
	@echo " "
	@echo "############## icon_module #############"
	@$(MAKE) -C icon -f makefile.$(PLATFORM)
	
.PHONY : join
join:
	@echo " "
	@echo "############## join_module #############"
	@$(MAKE) -C join -f makefile.$(PLATFORM)

.PHONY : listerformat
listerformat:
	@echo " "
	@echo "############## listerformat_module #############"
	@$(MAKE) -C listerformat -f makefile.$(PLATFORM)
	
.PHONY : misc
misc:
	@echo " "
	@echo "############## misc_module #############"
	@$(MAKE) -C misc -f makefile.$(PLATFORM)

.PHONY : pathformat
pathformat:
	@echo " "
	@echo "############## pathformat_module #############"
	@$(MAKE) -C pathformat -f makefile.$(PLATFORM)

.PHONY : play
play:
	@echo " "
	@echo "############## play_module #############"
	@$(MAKE) -C play -f makefile.$(PLATFORM)

.PHONY : print
print:
	@echo " "
	@echo "############## print_module #############"
	@$(MAKE) -C print -f makefile.$(PLATFORM)

.PHONY : read
read:
	@echo " "
	@echo "############## read_module #############"
	@$(MAKE) -C read -f makefile.$(PLATFORM)

.PHONY : show
show:
	@echo " "
	@echo "############## show_module #############"
	@$(MAKE) -C show -f makefile.$(PLATFORM)

.PHONY : themes
themes:
	@echo " "
	@echo "############## themes_module #############"
	@$(MAKE) -C themes -f makefile.$(PLATFORM)

.PHONY : xadopus
xadopus:
	@echo " "
	@echo "############## xadopus_module #############"
	@$(MAKE) -C xadopus -f makefile.$(PLATFORM)
	
	
###########################################################

.PHONY : clean
clean:	clean-about clean-cleanup clean-configopus clean-diskcopy clean-diskinfo clean-filetype clean-fixicons \
		clean-format clean-ftp clean-icon clean-join clean-listerformat clean-misc clean-pathformat clean-play \
		clean-print clean-read clean-show clean-themes clean-xadopus


.PHONY : clean-about
clean-about:
	@echo " "
	@echo "############ clean about_module ############"
	@$(MAKE) -C about -f makefile.$(PLATFORM) clean
	
.PHONY : clean-cleanup
clean-cleanup:
	@echo " "
	@echo "########### clean cleanup_module ###########"
	@$(MAKE) -C cleanup -f makefile.$(PLATFORM) clean

.PHONY : clean-configopus
clean-configopus:
	@echo " "
	@echo "########### clean configopus_module ###########"
	@$(MAKE) -C configopus -f makefile.$(PLATFORM) clean

.PHONY : clean-diskcopy
clean-diskcopy:
	@echo " "
	@echo "########### clean diskcopy_module ###########"
	@$(MAKE) -C diskcopy -f makefile.$(PLATFORM) clean

.PHONY : clean-diskinfo
clean-diskinfo:
	@echo " "
	@echo "########### clean diskinfo_module ###########"
	@$(MAKE) -C diskinfo -f makefile.$(PLATFORM) clean
	
.PHONY : clean-filetype
clean-filetype:
	@echo " "
	@echo "########### clean filetype_module ##########"
	@$(MAKE) -C filetype -f makefile.$(PLATFORM) clean

.PHONY : clean-fixicons
clean-fixicons:
	@echo " "
	@echo "########### clean fixicons_module ##########"
	@$(MAKE) -C fixicons -f makefile.$(PLATFORM) clean
	
.PHONY : clean-format
clean-format:
	@echo " "
	@echo "########### clean format_module ##########"
	@$(MAKE) -C format -f makefile.$(PLATFORM) clean

.PHONY : clean-ftp
clean-ftp:
	@echo " "
	@echo "########### clean ftp_module ##########"
	@$(MAKE) -C ftp -f makefile.$(PLATFORM) clean

.PHONY : clean-icon
clean-icon:
	@echo " "
	@echo "########### clean icon_module ##########"
	@$(MAKE) -C icon -f makefile.$(PLATFORM) clean
	
.PHONY : clean-join
clean-join:
	@echo " "
	@echo "########### clean join_module ##########"
	@$(MAKE) -C join -f makefile.$(PLATFORM) clean

.PHONY : clean-listerformat
clean-listerformat:
	@echo " "
	@echo "########### clean listerformat_module ##########"
	@$(MAKE) -C listerformat -f makefile.$(PLATFORM) clean
	
.PHONY : clean-misc
clean-misc:
	@echo " "
	@echo "########### clean misc_module ##########"
	@$(MAKE) -C misc -f makefile.$(PLATFORM) clean
	
.PHONY : clean-pathformat
clean-pathformat:
	@echo " "
	@echo "########### clean pathformat_module ##########"
	@$(MAKE) -C pathformat -f makefile.$(PLATFORM) clean

.PHONY : clean-play
clean-play:
	@echo " "
	@echo "########### clean play_module ##########"
	@$(MAKE) -C play -f makefile.$(PLATFORM) clean
	
.PHONY : clean-print
clean-print:
	@echo " "
	@echo "########### clean print_module ##########"
	@$(MAKE) -C print -f makefile.$(PLATFORM) clean

.PHONY : clean-read
clean-read:
	@echo " "
	@echo "########### clean read_module ##########"
	@$(MAKE) -C read -f makefile.$(PLATFORM) clean
	
.PHONY : clean-show
clean-show:
	@echo " "
	@echo "########### clean show_module ##########"
	@$(MAKE) -C show -f makefile.$(PLATFORM) clean
	
.PHONY : clean-themes
clean-themes:
	@echo " "
	@echo "########### clean themes_module ##########"
	@$(MAKE) -C themes -f makefile.$(PLATFORM) clean

.PHONY : clean-xadopus
clean-xadopus:
	@echo " "
	@echo "########### clean xadopus_module ##########"
	@$(MAKE) -C xadopus -f makefile.$(PLATFORM) clean
	
	
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

