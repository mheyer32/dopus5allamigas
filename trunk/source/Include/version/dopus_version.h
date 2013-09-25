// transforms a define into a string
#define STRI(x)  STRI2(x)
#define STRI2(x) #x

//set the compile date from the makefile date definition
#define DOPUSDATE STRI(COMPDATE)

// set the program version/revision
#define PROG_VERSION    5
#define PROG_REVISION   90

// set the library & modules version/revision
#define LIB_VERSION    68
#define LIB_REVISION   11

// set the commands version/revision (viewfont, dopusrt5, loadwb)
#define CMD_VERSION    63
#define CMD_REVISION   0

// set platform identification
#if defined(__amigaos3__)
	#define PLATFORM [OS3]
#elif defined(__amigaos4__)
	#define PLATFORM [OS4]
#elif defined(__MORPHOS__)
	#define PLATFORM [MOS]
#else
	#define PLATFORM [AROS]
#endif

// set the version/revision strings
#define PROG_STRING STRI(PROG_VERSION)"."STRI(PROG_REVISION)" "STRI(PLATFORM)" ("DOPUSDATE")"
#define LIB_STRING STRI(LIB_VERSION)"."STRI(LIB_REVISION)" "STRI(PLATFORM)" ("DOPUSDATE")"
#define CMD_STRING STRI(CMD_VERSION)"."STRI(CMD_REVISION)" "STRI(PLATFORM)" ("DOPUSDATE")"

#define COPYRIGHT  " Copyright (c) 2012-2013 dopus5 Open Source Team "

