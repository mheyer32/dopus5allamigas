/*

Directory Opus 5
Original APL release version 5.82
Copyright 1993-2012 Jonathan Potter & GP Software

This program is free software; you can redistribute it and/or
modify it under the terms of the AROS Public License version 1.1.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
AROS Public License for more details.

The release of Directory Opus 5 under the GPL in NO WAY affects
the existing commercial status of Directory Opus for Windows.

For more information on Directory Opus for Windows please see:

                 http://www.gpsoft.com.au

*/

#ifndef AD_INTERNET_H
#define AD_INTERNET_H

/* sys/types.h */

/**

// These are already in Greg and Andrew's all.gst
// But they are not in Jon's include30.gst

   typedef unsigned short ubit16;
   typedef unsigned long  ubit32;

   typedef ubit16	  u_short;
   typedef ubit32	  u_long;

**/

/* netinet/in.h */

/*
 * Protocols
 */
#define	IPPROTO_IP		0		/* dummy for IP */

/*
 * Internet address (a structure for historical reasons)
 */
struct in_addr {
	u_long	s_addr;
};

/*
 * Socket address, internet style.
 */
struct sockaddr_in {
	short	sin_family;
	u_short	sin_port;
	struct	in_addr sin_addr;
	char	sin_zero[8];
};

/*
 * Options for use with [gs]etsockopt at the IP level.
 * First word of comment is data type; bool is stored in int.
 */
#define	IP_TOS		3	/* int; IP type of service and precedence */

/* Types, macros, etc. for select() */

#ifndef MAXFUPLIM
/*
 * MAXFUPLIM is the absolute limit of open files per process.  No process,
 * even super-user processes may increase u.u_maxof beyond MAXFUPLIM.
 * MAXFUPLIM means maximum files upper limit.
 * Important Note:  This definition should actually go into h/param.h, but
 * since it is needed by the select() macros which follow, it had to go here.
 * I did not put it in both files since h/param.h includes this file and that
 * would be error prone anyway.
 */
#define MAXFUPLIM 128/* Max SOCKETS allowed */
#endif

/*
 * These macros are used for select().  select() uses bit masks of file
 * descriptors in longs.  These macros manipulate such bit fields (the
 * file sysrem macros uses chars).  FD_SETSIZE may be defined by the user,
 * but must be >= u.u_highestfd + 1.  Since we know the absolute limit on
 * number of per process open files is 2048, we need to define FD_SETSIZE
 * to be large enough to accomodate this many file descriptors.  Unless the
 * user has this many files opened, he should redefine FD_SETSIZE to a
 * smaller number.
 */
#define FD_SETSIZE MAXFUPLIM

     typedef long fd_mask;

#define NFDBITS (sizeof(fd_mask) * 8)           /* 8 bits per byte */

#ifndef howmany
#define howmany(x,y) (((x)+((y)-1))/(y))
#endif

     typedef struct fd_set {
       fd_mask fds_bits[howmany(FD_SETSIZE, NFDBITS)];
     } fd_set;

#define FD_SET(n,p)  ((p)->fds_bits[(n)/NFDBITS] |= (1 << ((n) % NFDBITS)))
#define FD_CLR(n,p) ((p)->fds_bits[(n)/NFDBITS] &= ~(1 << ((n) % NFDBITS)))
#define FD_ISSET(n,p) ((p)->fds_bits[(n)/NFDBITS] & (1 << ((n) % NFDBITS)))
#define FD_ZERO(p) memset((p), 0, sizeof(*(p)))

/* netinet/ip.h */

/*
 * Definitions for IP type of service (ip_tos)
 */
#define	IPTOS_LOWDELAY		0x10
#define	IPTOS_THROUGHPUT	0x08

/* sys/socket.h */

/*
 * Types
 */
#define	SOCK_STREAM	1		/* stream socket */

/*
 * Option flags per-socket.
 */
#define	SO_REUSEADDR	0x0004		/* allow local address reuse */
#define	SO_LINGER	0x0080		/* linger on close if data present */
#define	SO_OOBINLINE	0x0100		/* leave received OOB data in line */

/*
 * Structure used for manipulating linger option.
 */
struct	linger {
	int	l_onoff;		/* option on/off */
	int	l_linger;		/* linger time */
};

/*
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
#define	SOL_SOCKET	0xffff		/* options for socket level */

/*
 * Address families.
 */
#define	AF_INET		2		/* internetwork: UDP, TCP, etc. */

#define	MSG_OOB		0x1		/* process out-of-band data */

/* arpa/internet/telnet.h */

#define	IAC	255		/* interpret as command: */
#define	DM	242		/* data mark--for connect. cleaning */
#define	IP	244		/* interrupt process--permanently */

/* arpa/internet/ftp.h */

/*
 * Reply codes.
 */
#define PRELIM		1	/* positive preliminary */
#define COMPLETE	2	/* positive completion */
#define CONTINUE	3	/* positive intermediate */
#define TRANSIENT	4	/* transient negative completion */
#define ERROR		5	/* permanent negative completion */

/* netdb.h */

/*
 * Structures returned by network data base library.  All addresses are
 * supplied in host order, and returned in network order (suitable for
 * use in system calls).
 */
struct	hostent {
	char	*h_name;	/* official name of host */
	char	**h_aliases;	/* alias list */
	int	h_addrtype;	/* host address type */
	int	h_length;	/* length of address */
	char	**h_addr_list;	/* list of addresses from name server */
#define	h_addr	h_addr_list[0]	/* address, for backward compatiblity */
};

struct	servent {
	char	*s_name;	/* official service name */
	char	**s_aliases;	/* alias list */
	int	s_port;		/* port # */
	char	*s_proto;	/* protocol to use */
};

#endif
