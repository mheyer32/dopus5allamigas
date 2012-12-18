#define CATCOMP_BLOCK
#include "string_data.h"
#include "dopuslib:dopusbase.h"

void init_locale_data(struct DOpusLocale *locale)
{
	locale->li_BuiltIn=(char *)CatCompBlock;
}
