#define CATCOMP_BLOCK
#include "filetype.strings"
#include "dopuslib:dopusbase.h"

void init_locale_data(struct DOpusLocale *locale)
{
	locale->li_BuiltIn=(char *)CatCompBlock;
}
