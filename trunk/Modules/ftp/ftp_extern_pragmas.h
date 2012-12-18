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

#ifndef AD_INTERNET_EXTERN_H
#define AD_INTERNET_EXTERN_H


/* AS225 */

int as225_accept (int, struct sockaddr *, int *);
int as225_bind (int, struct sockaddr *, int );
void as225_cleanup_sockets ( void ) ;
int as225_connect (int, struct sockaddr *, int);
struct hostent *as225_gethostbyname ( char * );
int as225_gethostname (char *, int);
struct servent *as225_getservbyname ( char *, char * );
struct servent *as225_getservbyport ( int, char * );
int as225_getsockname ( int, struct sockaddr *, int * );
u_long as225_inet_addr ( char * );
int as225_listen (int , int);
int as225_recv(int, char *, int, int );
int as225_s_close ( int ) ;
int as225_selectwait (int, fd_set *, fd_set *, fd_set *, struct timeval *, long *);
int as225_send (int, char *, int, int );
int as225_setsockopt( int, int, int, char *, int );
ULONG as225_setup_sockets ( UWORD, int * );
int as225_shutdown (int, int);
int as225_socket( int, int, int );

#pragma libcall SocketBase as225_setup_sockets 1e 8102
#pragma libcall SocketBase as225_cleanup_sockets 24 0
#pragma libcall SocketBase as225_socket 2a 21003
#pragma libcall SocketBase as225_s_close 30 001
#pragma libcall SocketBase as225_gethostname 72 0802
#pragma libcall SocketBase as225_gethostbyname 8a 801
#pragma libcall SocketBase as225_inet_addr 96 901
#pragma libcall SocketBase as225_accept ba 98003
#pragma libcall SocketBase as225_bind c0 19003
#pragma libcall SocketBase as225_connect c6 19003
#pragma libcall SocketBase as225_listen d2 1002
#pragma libcall SocketBase as225_recv d8 218004
#pragma libcall SocketBase as225_selectwait f0 21A98006
#pragma libcall SocketBase as225_send f6 918004
#pragma libcall SocketBase as225_shutdown 108 1002
#pragma libcall SocketBase as225_setsockopt 10e 3821005
#pragma libcall SocketBase as225_getservbyname 168 9802
#pragma libcall SocketBase as225_getservbyport 16e 8002
#pragma libcall SocketBase as225_getsockname 19e 98003

/* AMITCTP */

LONG amitcp_Accept(LONG s, struct sockaddr *addr, LONG *addrlen);
LONG amitcp_Bind(LONG s,  struct sockaddr *name, LONG namelen);
LONG amitcp_CloseSocket(LONG d);
LONG amitcp_Connect(LONG s,  struct sockaddr *name, LONG namelen);
struct hostent  *amitcp_GetHostByName( UBYTE *name);
LONG amitcp_GetHostName(STRPTR hostname, LONG size);          /* V3 */
struct servent  *amitcp_GetServByName( UBYTE *name,  UBYTE *proto);
struct servent  *amitcp_GetServByPort( LONG,  UBYTE *proto);
LONG amitcp_GetSockName(LONG s, struct sockaddr *name, LONG *namelen);
ULONG amitcp_Inet_Addr( UBYTE *);
LONG amitcp_Listen(LONG s, LONG backlog);
LONG amitcp_Recv(LONG s, UBYTE *buf, LONG len, LONG flags);	/* V3 */
LONG amitcp_Send(LONG s,  UBYTE *msg, LONG len, LONG flags);
LONG amitcp_SetErrnoPtr(void *errno_p, LONG size);
LONG amitcp_SetSockOpt(LONG s, LONG level, LONG optname,
		const void *optval, LONG optlen);
LONG amitcp_Socket(LONG domain, LONG type, LONG protocol);
LONG amitcp_Shutdown(LONG s, LONG how);
LONG amitcp_WaitSelect(LONG nfds, fd_set *readfds, fd_set *writefds, fd_set *exeptfds,
		struct timeval *timeout, ULONG *maskp);

#pragma libcall SocketBase amitcp_Socket 1E 21003
#pragma libcall SocketBase amitcp_Bind 24 18003
#pragma libcall SocketBase amitcp_Listen 2A 1002
#pragma libcall SocketBase amitcp_Accept 30 98003
#pragma libcall SocketBase amitcp_Connect 36 18003
#pragma libcall SocketBase amitcp_Send 42 218004
#pragma libcall SocketBase amitcp_Recv 4E 218004
#pragma libcall SocketBase amitcp_Shutdown 54 1002
#pragma libcall SocketBase amitcp_SetSockOpt 5A 3821005
#pragma libcall SocketBase amitcp_GetSockName 66 98003
#pragma libcall SocketBase amitcp_CloseSocket 78 001
#pragma libcall SocketBase amitcp_WaitSelect 7E 1BA98006
#pragma libcall SocketBase amitcp_SetErrnoPtr A8 0802
#pragma libcall SocketBase amitcp_Inet_Addr B4 801
#pragma libcall SocketBase amitcp_GetHostByName D2 801
#pragma libcall SocketBase amitcp_GetServByName EA 9802
#pragma libcall SocketBase amitcp_GetServByPort F0 8002
#pragma libcall SocketBase amitcp_GetHostName 11A 0802

/* GENERIC */

int accept (int, struct sockaddr *, int *);
int bind (int, struct sockaddr *, int );
void cleanup_sockets ( void ) ;
int connect (int, struct sockaddr *, int);
struct hostent *gethostbyname ( char * );
int gethostname (char *, int);
struct servent *getservbyname ( char *, char * );
struct servent *getservbyport ( int, char * );
int getsockname ( int, struct sockaddr *, int * );
u_long inet_addr ( char * );
int listen (int , int);
int recv(int, char *, int, int );
int s_close ( int ) ;
int selectwait (int, fd_set *, fd_set *, fd_set *, struct timeval *, long *);
int send (int, char *, int, int );
ULONG setup_sockets ( UWORD, int * );
int shutdown (int, int);
int socket( int, int, int );

#endif
