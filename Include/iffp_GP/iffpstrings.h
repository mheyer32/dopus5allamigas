#ifndef LOCALESTR_IFFP_H
#define LOCALESTR_IFFP_H


/****************************************************************************/


/* This file was created automatically by CatComp.
 * Do NOT edit by hand!
 */


#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#ifdef CATCOMP_ARRAY
#undef CATCOMP_NUMBERS
#undef CATCOMP_STRINGS
#define CATCOMP_NUMBERS
#define CATCOMP_STRINGS
#endif

#ifdef CATCOMP_BLOCK
#undef CATCOMP_STRINGS
#define CATCOMP_STRINGS
#endif


/****************************************************************************/


#ifdef CATCOMP_NUMBERS

#define MSG_IFFP_STDFIRST 5000
#define MSG_IFFP_STD2 5001
#define MSG_IFFP_STD3 5002
#define MSG_IFFP_STD4 5003
#define MSG_IFFP_STD5 5004
#define MSG_IFFP_STD6 5005
#define MSG_IFFP_STD7 5006
#define MSG_IFFP_STD8 5007
#define MSG_IFFP_STD9 5008
#define MSG_IFFP_STD10 5009
#define MSG_IFFP_STD11 5010
#define MSG_IFFP_STDLAST 5011
#define MSG_IFFP_NOCLIP_D 5020
#define MSG_IFFP_NOFILE 5021
#define MSG_IFFP_NOFILE_S 5022
#define MSG_IFFP_NOTOP 5023
#define MSG_IFFP_CLIENTERR 5024
#define MSG_IFFP_NOIFFFILE 5025
#define MSG_IFFP_NOFORM 5026
#define MSG_IFFP_UNKNOWNERR_D 5027
#define MSG_IFFP_NOMEM 5050
#define MSG_IFFP_NOIFF 5051
#define MSG_IFFP_NOIFFPARSE 5052
#define MSG_IFFP_NOINTUITION 5053
#define MSG_IFFP_NOGRAPHICS 5054
#define MSG_ILBM_NOILBM 5100
#define MSG_ILBM_NOBMHD 5101
#define MSG_ILBM_NOBODY 5102
#define MSG_ILBM_NODISPLAY 5103
#define MSG_ILBM_NORASTER 5104
#define MSG_ILBM_NOCOLORS 5105
#define MSG_ILBM_HUNTED 5106
#define MSG_ILBM_TOODEEP 5107
#define MSG_ILBM_PRTTROUBLE_D 5108
#define MSG_OSCR_NOMEM 5180
#define MSG_OSCR_NOCHIPMEM 5181
#define MSG_OSCR_NOMONITOR 5182
#define MSG_OSCR_NOCHIPS 5183
#define MSG_OSCR_PUBNOTUNIQUE 5184
#define MSG_OSCR_UNKNOWNMODE 5185
#define MSG_OSCR_UNKNOWNERR_D 5186

#endif /* CATCOMP_NUMBERS */


/****************************************************************************/


#ifdef CATCOMP_STRINGS

#define MSG_IFFP_STDFIRST_STR "End of file (not an error)"
#define MSG_IFFP_STD2_STR "End of context (not an error)"
#define MSG_IFFP_STD3_STR "No lexical scope"
#define MSG_IFFP_STD4_STR "Insufficient memory"
#define MSG_IFFP_STD5_STR "Stream read error"
#define MSG_IFFP_STD6_STR "Stream write error"
#define MSG_IFFP_STD7_STR "Stream seek error"
#define MSG_IFFP_STD8_STR "File is corrupt"
#define MSG_IFFP_STD9_STR "IFF syntax error"
#define MSG_IFFP_STD10_STR "Not an IFF file"
#define MSG_IFFP_STD11_STR "Required hook vector missing"
#define MSG_IFFP_STDLAST_STR "Return to client"
#define MSG_IFFP_NOCLIP_D_STR "Clipboard open of unit %ld failed\n"
#define MSG_IFFP_NOFILE_STR "File not found\n"
#define MSG_IFFP_NOFILE_S_STR "%s: File open failed\n"
#define MSG_IFFP_NOTOP_STR "Parsing error; no top chunk\n"
#define MSG_IFFP_CLIENTERR_STR "Client error"
#define MSG_IFFP_NOIFFFILE_STR "File not found or wrong type"
#define MSG_IFFP_NOFORM_STR "No FORM"
#define MSG_IFFP_UNKNOWNERR_D_STR "Unknown parse error %ld"
#define MSG_IFFP_NOMEM_STR "Not enough memory\n"
#define MSG_IFFP_NOIFF_STR "Can't AllocIff"
#define MSG_IFFP_NOIFFPARSE_STR "Can't open iffparse.library"
#define MSG_IFFP_NOINTUITION_STR "Can't open intuition.library"
#define MSG_IFFP_NOGRAPHICS_STR "Can't open graphics.library"
#define MSG_ILBM_NOILBM_STR "Not an ILBM\n"
#define MSG_ILBM_NOBMHD_STR "No ILBM.BMHD chunk\n"
#define MSG_ILBM_NOBODY_STR "No ILBM.BODY chunk\n"
#define MSG_ILBM_NODISPLAY_STR "Failed to open display\n"
#define MSG_ILBM_NORASTER_STR "Failed to allocate raster\n"
#define MSG_ILBM_NOCOLORS_STR "No colortable allocated\n"
#define MSG_ILBM_HUNTED_STR "ILBM is embedded in complex file"
#define MSG_ILBM_TOODEEP_STR "planes, displaying initial planes"
#define MSG_ILBM_PRTTROUBLE_D_STR "Printer error %ld\n"
#define MSG_OSCR_NOMEM_STR "Not enough memory"
#define MSG_OSCR_NOCHIPMEM_STR "Not enough chip memory"
#define MSG_OSCR_NOMONITOR_STR "monitor not available"
#define MSG_OSCR_NOCHIPS_STR "required chipset not available"
#define MSG_OSCR_PUBNOTUNIQUE_STR "public screen already open"
#define MSG_OSCR_UNKNOWNMODE_STR "mode ID is unknown"
#define MSG_OSCR_UNKNOWNERR_D_STR "unknown OpenScreen error %ld"

#endif /* CATCOMP_STRINGS */


/****************************************************************************/


#ifdef CATCOMP_ARRAY

struct CatCompArrayType
{
    LONG   cca_ID;
    STRPTR cca_Str;
};

static const struct CatCompArrayType CatCompArray[] =
{
    {MSG_IFFP_STDFIRST,(STRPTR)MSG_IFFP_STDFIRST_STR},
    {MSG_IFFP_STD2,(STRPTR)MSG_IFFP_STD2_STR},
    {MSG_IFFP_STD3,(STRPTR)MSG_IFFP_STD3_STR},
    {MSG_IFFP_STD4,(STRPTR)MSG_IFFP_STD4_STR},
    {MSG_IFFP_STD5,(STRPTR)MSG_IFFP_STD5_STR},
    {MSG_IFFP_STD6,(STRPTR)MSG_IFFP_STD6_STR},
    {MSG_IFFP_STD7,(STRPTR)MSG_IFFP_STD7_STR},
    {MSG_IFFP_STD8,(STRPTR)MSG_IFFP_STD8_STR},
    {MSG_IFFP_STD9,(STRPTR)MSG_IFFP_STD9_STR},
    {MSG_IFFP_STD10,(STRPTR)MSG_IFFP_STD10_STR},
    {MSG_IFFP_STD11,(STRPTR)MSG_IFFP_STD11_STR},
    {MSG_IFFP_STDLAST,(STRPTR)MSG_IFFP_STDLAST_STR},
    {MSG_IFFP_NOCLIP_D,(STRPTR)MSG_IFFP_NOCLIP_D_STR},
    {MSG_IFFP_NOFILE,(STRPTR)MSG_IFFP_NOFILE_STR},
    {MSG_IFFP_NOFILE_S,(STRPTR)MSG_IFFP_NOFILE_S_STR},
    {MSG_IFFP_NOTOP,(STRPTR)MSG_IFFP_NOTOP_STR},
    {MSG_IFFP_CLIENTERR,(STRPTR)MSG_IFFP_CLIENTERR_STR},
    {MSG_IFFP_NOIFFFILE,(STRPTR)MSG_IFFP_NOIFFFILE_STR},
    {MSG_IFFP_NOFORM,(STRPTR)MSG_IFFP_NOFORM_STR},
    {MSG_IFFP_UNKNOWNERR_D,(STRPTR)MSG_IFFP_UNKNOWNERR_D_STR},
    {MSG_IFFP_NOMEM,(STRPTR)MSG_IFFP_NOMEM_STR},
    {MSG_IFFP_NOIFF,(STRPTR)MSG_IFFP_NOIFF_STR},
    {MSG_IFFP_NOIFFPARSE,(STRPTR)MSG_IFFP_NOIFFPARSE_STR},
    {MSG_IFFP_NOINTUITION,(STRPTR)MSG_IFFP_NOINTUITION_STR},
    {MSG_IFFP_NOGRAPHICS,(STRPTR)MSG_IFFP_NOGRAPHICS_STR},
    {MSG_ILBM_NOILBM,(STRPTR)MSG_ILBM_NOILBM_STR},
    {MSG_ILBM_NOBMHD,(STRPTR)MSG_ILBM_NOBMHD_STR},
    {MSG_ILBM_NOBODY,(STRPTR)MSG_ILBM_NOBODY_STR},
    {MSG_ILBM_NODISPLAY,(STRPTR)MSG_ILBM_NODISPLAY_STR},
    {MSG_ILBM_NORASTER,(STRPTR)MSG_ILBM_NORASTER_STR},
    {MSG_ILBM_NOCOLORS,(STRPTR)MSG_ILBM_NOCOLORS_STR},
    {MSG_ILBM_HUNTED,(STRPTR)MSG_ILBM_HUNTED_STR},
    {MSG_ILBM_TOODEEP,(STRPTR)MSG_ILBM_TOODEEP_STR},
    {MSG_ILBM_PRTTROUBLE_D,(STRPTR)MSG_ILBM_PRTTROUBLE_D_STR},
    {MSG_OSCR_NOMEM,(STRPTR)MSG_OSCR_NOMEM_STR},
    {MSG_OSCR_NOCHIPMEM,(STRPTR)MSG_OSCR_NOCHIPMEM_STR},
    {MSG_OSCR_NOMONITOR,(STRPTR)MSG_OSCR_NOMONITOR_STR},
    {MSG_OSCR_NOCHIPS,(STRPTR)MSG_OSCR_NOCHIPS_STR},
    {MSG_OSCR_PUBNOTUNIQUE,(STRPTR)MSG_OSCR_PUBNOTUNIQUE_STR},
    {MSG_OSCR_UNKNOWNMODE,(STRPTR)MSG_OSCR_UNKNOWNMODE_STR},
    {MSG_OSCR_UNKNOWNERR_D,(STRPTR)MSG_OSCR_UNKNOWNERR_D_STR},
};

#endif /* CATCOMP_ARRAY */


/****************************************************************************/


#ifdef CATCOMP_BLOCK

static const char CatCompBlock[] =
{
    "\x00\x00\x13\x88\x00\x1C"
    MSG_IFFP_STDFIRST_STR "\x00\x00"
    "\x00\x00\x13\x89\x00\x1E"
    MSG_IFFP_STD2_STR "\x00"
    "\x00\x00\x13\x8A\x00\x12"
    MSG_IFFP_STD3_STR "\x00\x00"
    "\x00\x00\x13\x8B\x00\x14"
    MSG_IFFP_STD4_STR "\x00"
    "\x00\x00\x13\x8C\x00\x12"
    MSG_IFFP_STD5_STR "\x00"
    "\x00\x00\x13\x8D\x00\x14"
    MSG_IFFP_STD6_STR "\x00\x00"
    "\x00\x00\x13\x8E\x00\x12"
    MSG_IFFP_STD7_STR "\x00"
    "\x00\x00\x13\x8F\x00\x10"
    MSG_IFFP_STD8_STR "\x00"
    "\x00\x00\x13\x90\x00\x12"
    MSG_IFFP_STD9_STR "\x00\x00"
    "\x00\x00\x13\x91\x00\x10"
    MSG_IFFP_STD10_STR "\x00"
    "\x00\x00\x13\x92\x00\x1E"
    MSG_IFFP_STD11_STR "\x00\x00"
    "\x00\x00\x13\x93\x00\x12"
    MSG_IFFP_STDLAST_STR "\x00\x00"
    "\x00\x00\x13\x9C\x00\x24"
    MSG_IFFP_NOCLIP_D_STR "\x00\x00"
    "\x00\x00\x13\x9D\x00\x10"
    MSG_IFFP_NOFILE_STR "\x00"
    "\x00\x00\x13\x9E\x00\x16"
    MSG_IFFP_NOFILE_S_STR "\x00"
    "\x00\x00\x13\x9F\x00\x1E"
    MSG_IFFP_NOTOP_STR "\x00\x00"
    "\x00\x00\x13\xA0\x00\x0E"
    MSG_IFFP_CLIENTERR_STR "\x00\x00"
    "\x00\x00\x13\xA1\x00\x1E"
    MSG_IFFP_NOIFFFILE_STR "\x00\x00"
    "\x00\x00\x13\xA2\x00\x08"
    MSG_IFFP_NOFORM_STR "\x00"
    "\x00\x00\x13\xA3\x00\x18"
    MSG_IFFP_UNKNOWNERR_D_STR "\x00"
    "\x00\x00\x13\xBA\x00\x14"
    MSG_IFFP_NOMEM_STR "\x00\x00"
    "\x00\x00\x13\xBB\x00\x10"
    MSG_IFFP_NOIFF_STR "\x00\x00"
    "\x00\x00\x13\xBC\x00\x1C"
    MSG_IFFP_NOIFFPARSE_STR "\x00"
    "\x00\x00\x13\xBD\x00\x1E"
    MSG_IFFP_NOINTUITION_STR "\x00\x00"
    "\x00\x00\x13\xBE\x00\x1C"
    MSG_IFFP_NOGRAPHICS_STR "\x00"
    "\x00\x00\x13\xEC\x00\x0E"
    MSG_ILBM_NOILBM_STR "\x00\x00"
    "\x00\x00\x13\xED\x00\x14"
    MSG_ILBM_NOBMHD_STR "\x00"
    "\x00\x00\x13\xEE\x00\x14"
    MSG_ILBM_NOBODY_STR "\x00"
    "\x00\x00\x13\xEF\x00\x18"
    MSG_ILBM_NODISPLAY_STR "\x00"
    "\x00\x00\x13\xF0\x00\x1C"
    MSG_ILBM_NORASTER_STR "\x00\x00"
    "\x00\x00\x13\xF1\x00\x1A"
    MSG_ILBM_NOCOLORS_STR "\x00\x00"
    "\x00\x00\x13\xF2\x00\x22"
    MSG_ILBM_HUNTED_STR "\x00\x00"
    "\x00\x00\x13\xF3\x00\x22"
    MSG_ILBM_TOODEEP_STR "\x00"
    "\x00\x00\x13\xF4\x00\x14"
    MSG_ILBM_PRTTROUBLE_D_STR "\x00\x00"
    "\x00\x00\x14\x3C\x00\x12"
    MSG_OSCR_NOMEM_STR "\x00"
    "\x00\x00\x14\x3D\x00\x18"
    MSG_OSCR_NOCHIPMEM_STR "\x00\x00"
    "\x00\x00\x14\x3E\x00\x16"
    MSG_OSCR_NOMONITOR_STR "\x00"
    "\x00\x00\x14\x3F\x00\x20"
    MSG_OSCR_NOCHIPS_STR "\x00\x00"
    "\x00\x00\x14\x40\x00\x1C"
    MSG_OSCR_PUBNOTUNIQUE_STR "\x00\x00"
    "\x00\x00\x14\x41\x00\x14"
    MSG_OSCR_UNKNOWNMODE_STR "\x00\x00"
    "\x00\x00\x14\x42\x00\x1E"
    MSG_OSCR_UNKNOWNERR_D_STR "\x00\x00"
};

#endif /* CATCOMP_BLOCK */


/****************************************************************************/


struct LocaleInfo
{
    APTR li_LocaleBase;
    APTR li_Catalog;
};


#ifdef CATCOMP_CODE

STRPTR GetString(struct LocaleInfo *li, LONG stringNum)
{
LONG   *l;
UWORD  *w;
STRPTR  builtIn;

    l = (LONG *)CatCompBlock;

    while (*l != stringNum)
    {
        w = (UWORD *)((ULONG)l + 4);
        l = (LONG *)((ULONG)l + (ULONG)*w + 6);
    }
    builtIn = (STRPTR)((ULONG)l + 6);

#define XLocaleBase LocaleBase
#define LocaleBase li->li_LocaleBase
    
    if (LocaleBase)
        return(GetCatalogStr(li->li_Catalog,stringNum,builtIn));
#define LocaleBase XLocaleBase
#undef XLocaleBase

    return(builtIn);
}


#endif /* CATCOMP_CODE */


/****************************************************************************/


#endif /* LOCALESTR_IFFP_H */
