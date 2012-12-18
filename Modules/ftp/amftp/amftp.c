#include <stdio.h>

struct amftp_profile
{
	char amftp_name[39 + 1];
	char amftp_host[127 + 1];
	int  amftp_pad1[8];
	char amftp_pass[63 + 1];
	char amftp_remote[123 + 1];
	int  amftp_pad2;
	char amftp_local[119 + 1];	// Length is 124 - causes errors
	char amftp_port[4 + 1];
	char amftp_pad3[8];
	char amftp_login[63 + 1];
	// more...
};

ULONG magic;

ULONG encrypt( void )
{
	ULONG d0, d1;

	d0 = magic; 

	d1 = ((((((((d0 << 3 - d0) << 3) + d0) << 1) + d0) << 4) - d0) << 1) - d0;
	d1 = (d1 + 0xe60) & 0x7fffffff;
	magic = d1 - 1;

	return d1;
}

int main( int argc, char **argv )
{
	char *filename = ".AmFTPProfiles";
	BPTR f;

	WORD a;
	LONG b;
	char buffer[589 * 2];
	struct amftp_profile *p = (struct amftp_profile *)buffer;

	if (argc > 1)
		filename = argv[1];

	if	(f = Open( filename, MODE_OLDFILE))
		{
		Read(f,&a, 2);
		Read(f, &b, 4);

		printf( "a = %ld\n", a );
		printf( "b = %ld\n", b );

		while	(589==Read(f, buffer, 589))
			{
			int i;

			magic = 0 - 1;

			for (i = 0; i < 589; ++i)
				buffer[i] ^= encrypt();

			printf( "name:\t'%s'\n", p->amftp_name );
			printf( "host:\t'%s'\n", p->amftp_host );
			printf( "port:\t'%s'\n", p->amftp_port );

			printf( "anon login:\t%ld\n", buffer[520] );
			printf( "user:\t'%s'\n", p->amftp_login );
			printf( "pass:\t'%s'\n", p->amftp_pass );

			printf( "remote dir :\t'%s'\n", p->amftp_remote );

			printf( "retries:\t%ld\n", buffer[521] );

			printf( "save remote:\t%ld\n", buffer[522] );

			printf("========================================\n");

			}


		Close( f );
		}
	else printf( "'%s' didn't open\n", filename );
}
