# Dopus5 archive creation makefile

###########################################################
# Enter debug=no on "Make" command line to disable debug output.
export debug
###########################################################
# Sets archive filename addition for debug version.
ifeq ($(debug), no)
TYPE := 
else
TYPE := dev
endif
###########################################################
# Sets destination directory and lha command
DEST := ../
ifeq ($(os), amiga)
ARCDEST := /
LHA := lha a -a -r
else
ARCDEST := ../../
LHA := lha -aro5
endif
###########################################################
# Commands
REMOVE := rm -rf
COPY := cp
MAKEDIR := mkdir -p
###########################################################

all : os4 os3 mos aros

os4 : amigaos4
	@$(MAKEDIR) dopus5/Libs
	@$(MAKEDIR) dopus5/Modules
	@$(MAKEDIR) dopus5/C
	@$(COPY) source/bin.os4/dopus5.library dopus5/Libs
	@$(COPY) source/bin.os4/*.module dopus5/Modules
	@$(COPY) source/bin.os4/DirectoryOpus dopus5
	@$(COPY) source/bin.os4/DOpusRT5 dopus5/C
	@$(COPY) source/bin.os4/LoadDB dopus5/C
	@$(COPY) source/bin.os4/viewfont dopus5/C
	@$(COPY) release/archive.lha $(DEST)dopus5-OS4$(TYPE).lha
	@$(LHA) $(ARCDEST)dopus5-OS4$(TYPE).lha dopus5
	@$(REMOVE) dopus5

.PHONY : amigaos4
amigaos4:
#	@$(MAKE) -C source os4 cleanall
	@$(MAKE) -C source os4

#####

os3 : amigaos3
	@$(MAKEDIR) dopus5/Libs
	@$(MAKEDIR) dopus5/Modules
	@$(MAKEDIR) dopus5/C
	@$(COPY) source/bin.os3/dopus5.library dopus5/Libs
	@$(COPY) source/bin.os3/*.module dopus5/Modules
	@$(COPY) source/bin.os3/DirectoryOpus dopus5
	@$(COPY) source/bin.os3/DOpusRT5 dopus5/C
	@$(COPY) source/bin.os3/LoadDB dopus5/C
	@$(COPY) source/bin.os3/viewfont dopus5/C
	@$(COPY) release/archive.lha $(DEST)dopus5-OS3$(TYPE).lha
	@$(LHA) $(ARCDEST)dopus5-OS3$(TYPE).lha dopus5
	@$(REMOVE) dopus5

.PHONY : amigaos3
amigaos3:
	@$(MAKE) -C source os3 cleanall
	@$(MAKE) -C source os3

#####

mos : morphos
	@$(MAKEDIR) dopus5/Libs
	@$(MAKEDIR) dopus5/Modules
	@$(MAKEDIR) dopus5/C
	@$(COPY) source/bin.mos/dopus5.library dopus5/Libs
	@$(COPY) source/bin.mos/*.module dopus5/Modules
	@$(COPY) source/bin.mos/DirectoryOpus dopus5
	@$(COPY) source/bin.mos/DOpusRT5 dopus5/C
	@$(COPY) source/bin.mos/LoadDB dopus5/C
	@$(COPY) source/bin.mos/viewfont dopus5/C
	@$(COPY) release/archive.lha $(DEST)dopus5-MOS$(TYPE).lha
	@$(LHA) $(ARCDEST)dopus5-MOS$(TYPE).lha dopus5
	@$(REMOVE) dopus5

.PHONY : morphos
morphos:
	@$(MAKE) -C source mos cleanall
	@$(MAKE) -C source mos

#####

aros : aros-bin
	@$(MAKEDIR) dopus5/Libs
	@$(MAKEDIR) dopus5/Modules
	@$(MAKEDIR) dopus5/C
	@$(COPY) source/bin.aros/dopus5.library dopus5/Libs
	@$(COPY) source/bin.aros/*.module dopus5/Modules
	@$(COPY) source/bin.aros/DirectoryOpus dopus5
	@$(COPY) source/bin.aros/DOpusRT5 dopus5/C
	@$(COPY) source/bin.aros/LoadDB dopus5/C
	@$(COPY) source/bin.aros/viewfont dopus5/C
	@$(COPY) release/archive.lha $(DEST)dopus5-AROS$(TYPE).lha
	@$(LHA) $(ARCDEST)dopus5-AROS$(TYPE).lha dopus5
	@$(REMOVE) dopus5

.PHONY : aros-bin
aros-bin:
	@$(MAKE) -C source aros cleanall
	@$(MAKE) -C source aros
