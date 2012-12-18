#include "dopuslib:dopusbase.h"
#include "dopuslib:dopuspragmas.h"

void main(int,char **);

struct Library *DOpusBase;

void main(int argc,char **argv)
{
	ULONG checksum;

	if (!(DOpusBase=OpenLibrary("dopus5:libs/dopus5.library",0)))
		exit(0);
	checksum=ChecksumFile((argc<2)?"dopusmod:register.module":argv[1],22091973);
	checksum--;
	checksum=~checksum;
	printf("%lx\n",checksum);
	CloseLibrary(DOpusBase);
}
