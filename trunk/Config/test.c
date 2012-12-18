#include "dopuslib:dopusbase.h"
#include "dopuslib:dopuspragmas.h"
#include "configopus.h"

struct Library *DOpusBase;
struct Library *ConfigOpusBase;

void main(void);
void KPrintF __ARGS((char *,...));

void main(void)
{
//	Cfg_Config *config;
	Cfg_ButtonBank *bank;

	if (!(DOpusBase=OpenLibrary("dopus5:libs/dopus.library",40)))
		exit(0);
	if (ConfigOpusBase=OpenLibrary("configopus.library",0)) {
		if (bank=NewButtonBank(0))
		{
			Config_Buttons(bank,0,0,0);
			CloseButtonBank(bank);
		}
/*
		if (config=NewDefaultConfig()) {
			KPrintF("config returned %ld\n",Config_Lister(config,0));
			NewCloseConfig(config);
		}
*/
		CloseLibrary(ConfigOpusBase);
	}
	CloseLibrary(DOpusBase);
	exit(0);
}
