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
	char *filename = "work:internet/amftp/.AmFTPProfiles";
	FILE *f, *t;

	WORD a;
	LONG b;
	char buffer[589 * 2];
	struct amftp_profile *p = (struct amftp_profile *)buffer;

	if (argc > 1)
		filename = argv[1];

	if (f = fopen( filename, "r" ))
	{
		fread( &a, 2, 1, f );
		fread( &b, 4, 1, f );

		printf( "a = %ld\n", a );
		printf( "b = %ld\n", b );

		if (fread( buffer, 589, 2, f ) == 2)
		{
			int i;

			magic = 0 - 1;

			for (i = 0; i < 589; ++i)
				buffer[i] ^= encrypt();

			printf( "name:\t'%s'\n", p->amftp_name );
			printf( "host:\t'%s'\n", p->amftp_host );
			printf( "pass:\t'%s'\n", p->amftp_pass );
			printf( "remote:\t'%s'\n", p->amftp_remote );
			printf( "local:\t'%s'\n", p->amftp_local );
			printf( "port:\t'%s'\n", p->amftp_port );
			printf( "login:\t'%s'\n", p->amftp_login );

			printf( "adt server:\t%ld\n", buffer[524] );
			printf( "anon login:\t%ld\n", buffer[520] );
			printf( "quiet:\t%ld\n", buffer[523] );
			printf( "retries:\t%ld\n", buffer[521] );
			printf( "compression:\t%ld\n", buffer[518] );
			printf( "save local:\t%ld\n", buffer[519] );
			printf( "save remote:\t%ld\n", buffer[522] );

			magic = 0 - 1;

			for (i = 0; i < 589; ++i)
				buffer[589+i] ^= encrypt();

			p = (struct amftp_profile *)&buffer[589];

			printf( "name:\t'%s'\n", p->amftp_name );
			printf( "host:\t'%s'\n", p->amftp_host );
			printf( "pass:\t'%s'\n", p->amftp_pass );
			printf( "remote:\t'%s'\n", p->amftp_remote );
			printf( "local:\t'%s'\n", p->amftp_local );
			printf( "port:\t'%s'\n", p->amftp_port );
			printf( "login:\t'%s'\n", p->amftp_login );

			printf( "adt server:\t%ld\n", buffer[524] );
			printf( "anon login:\t%ld\n", buffer[520] );
			printf( "quiet:\t%ld\n", buffer[523] );
			printf( "retries:\t%ld\n", buffer[521] );
			printf( "compression:\t%ld\n", buffer[518] );
			printf( "save local:\t%ld\n", buffer[519] );
			printf( "save remote:\t%ld\n", buffer[522] );

			if (t = fopen( "ram:decrypted", "w" ))
			{
				fwrite( buffer, 598, 1, t );
				fclose( t );
			}
		}
		else printf( "didn't get buffer\n" );

		fclose( f );
	}
	else printf( "'%s' didn't open\n", filename );
}
