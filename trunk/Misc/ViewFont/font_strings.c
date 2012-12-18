#define CATCOMP_BLOCK
#include "font.strings"
#include "dopuslib:dopusbase.h"

void init_locale_data(struct DOpusLocale *locale)
{
	locale->li_BuiltIn=(char *)CatCompBlock;
}
