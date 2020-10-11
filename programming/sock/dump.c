#define _XOPEN_SOURCE_EXTENDED 1
//#define _OE_SOCKETS
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#if !defined __APPLE__ && !defined __linux__
#include <sys/un.h>
//#endif
#include <unistd.h>

// to find out the wormhole names to start with
void fakecalls()
{
   socket(0,0,0);
   recv(0,0,0,0);
   send(0,0,0,0);
   unlink(0);
   bind(0,0,0);
   listen(0,0);
   connect(0,0,0);
   inet_addr(0);
   close(0);
}

int main( int argc, char ** argv )
{
if ( argc == 7 )
{
   fakecalls();
}

// send,recv parameters
#if defined MSG_CONNTERM
printf( "MSG_CONNTERM = %d\n", MSG_CONNTERM );
#endif
#if defined MSG_OOB
printf( "MSG_OOB = %d\n", MSG_OOB );
#endif
#if defined MSG_PEEK
printf( "MSG_PEEK = %d\n", MSG_PEEK );
#endif
#if defined MSG_WAITALL
printf( "MSG_WAITALL = %d\n", MSG_WAITALL );
#endif
#if defined MSG_DONTROUTE
printf( "MSG_DONTROUTE = %d\n", MSG_DONTROUTE );
#endif

// socket() parameters
#if defined SOMAXCONN
printf( "SOMAXCONN = %d\n", SOMAXCONN );
#endif
#if defined AF_UNIX
printf( "AF_UNIX = %d\n", AF_UNIX );
#endif
#if defined AF_RAW
printf( "AF_RAW = %d\n", AF_RAW );
#endif
#if defined AF_LOCAL
printf( "AF_LOCAL = %d\n", AF_LOCAL );
#endif
#if defined AF_INET
printf( "AF_INET = %d\n", AF_INET );
#endif
#if defined AF_INET6
printf( "AF_INET6 = %d\n", AF_INET6 );
#endif
#if defined AF_IPX
printf( "AF_IPX = %d\n", AF_IPX );
#endif
#if defined AF_NETLINK
printf( "AF_NETLINK = %d\n", AF_NETLINK );
#endif
#if defined AF_X25
printf( "AF_X25 = %d\n", AF_X25 );
#endif
#if defined AF_AX25
printf( "AF_AX25 = %d\n", AF_AX25 );
#endif
#if defined AF_ATMPVC
printf( "AF_ATMPVC = %d\n", AF_ATMPVC );
#endif
#if defined AF_APPLETALK
printf( "AF_APPLETALK = %d\n", AF_APPLETALK );
#endif
#if defined AF_PACKET
printf( "AF_PACKET = %d\n", AF_PACKET );
#endif

#if defined SOCK_DGRAM
printf( "SOCK_DGRAM = %d\n", SOCK_DGRAM );
#endif
#if defined SOCK_PACKET
printf( "SOCK_PACKET = %d\n", SOCK_PACKET );
#endif
#if defined SOCK_RAW
printf( "SOCK_RAW = %d\n", SOCK_RAW );
#endif
#if defined SOCK_RDM
printf( "SOCK_RDM = %d\n", SOCK_RDM );
#endif
#if defined SOCK_SEQPACKET
printf( "SOCK_SEQPACKET = %d\n", SOCK_SEQPACKET );
#endif
#if defined SOCK_STREAM
printf( "SOCK_STREAM = %d\n", SOCK_STREAM );
#endif

#if defined IPPROTO_UDP
printf( "IPPROTO_UDP = %d\n", IPPROTO_UDP );
#endif
#if defined IPPROTO_TCP
printf( "IPPROTO_TCP = %d\n", IPPROTO_TCP );
#endif

// bind related structures and constants:

#if defined INADDR_ANY
printf( "INADDR_ANY = %d\n", INADDR_ANY );
#endif
#if defined SIN6_LEN && !defined __APPLE__
printf( "SIN6_LEN = %d\n", (int)SIN6_LEN );
#endif

printf( "socklen_t: %lu\n", (unsigned long)sizeof(socklen_t) );
#if !defined __APPLE__ && !defined __linux__
printf( "ip_addr_t: %lu\n", (unsigned long)sizeof(ip_addr_t) );
#endif
printf( "in_port_t: %lu\n", (unsigned long)sizeof(in_port_t) );
printf( "struct in6_addr: %lu\n", (unsigned long)sizeof(struct in6_addr) );
printf( "sa_family_t: %lu\n", (unsigned long)sizeof(sa_family_t) );
printf( "struct in_addr: %lu\n", (unsigned long)sizeof(struct in_addr) );
printf( "struct sockaddr: %lu\n", (unsigned long)sizeof(struct sockaddr) );
printf( "struct sockaddr_in: %lu\n", (unsigned long)sizeof(struct sockaddr_in) );
struct sockaddr_in * in = 0;

#if !defined __linux__
printf("   %03lu: sin_len: %lu\n", (unsigned long)&in->sin_len, (unsigned long)sizeof(in->sin_len) );
#endif
printf("   %03lu: sin_family: %lu\n", (unsigned long)&in->sin_family, (unsigned long)sizeof(in->sin_family) );
printf("   %03lu: sin_port: %lu\n", (unsigned long)&in->sin_port, (unsigned long)sizeof(in->sin_port) );
printf("   %03lu: sin_addr: %lu\n", (unsigned long)&in->sin_addr, (unsigned long)sizeof(in->sin_addr) );
printf("   %03lu: sin_zero: %lu\n", (unsigned long)&in->sin_zero, (unsigned long)sizeof(in->sin_zero) );

struct sockaddr_in6 * in6 = 0;
printf( "struct sockaddr_in6: %lu\n", (unsigned long)sizeof(struct sockaddr_in6) );
#if !defined __linux__
printf("   %03lu: sin6_len: %lu\n", (unsigned long)&in6->sin6_len, (unsigned long)sizeof(in6->sin6_len) );
#endif
printf("   %03lu: sin6_family: %lu\n", (unsigned long)&in6->sin6_family, (unsigned long)sizeof(in6->sin6_family) );
printf("   %03lu: sin6_port: %lu\n", (unsigned long)&in6->sin6_port, (unsigned long)sizeof(in6->sin6_port) );
printf("   %03lu: sin6_flowinfo: %lu\n", (unsigned long)&in6->sin6_flowinfo, (unsigned long)sizeof(in6->sin6_flowinfo) );
printf("   %03lu: sin6_addr: %lu\n", (unsigned long)&in6->sin6_addr, (unsigned long)sizeof(in6->sin6_addr) );
printf("   %03lu: sin6_scope_id: %lu\n", (unsigned long)&in6->sin6_scope_id, (unsigned long)sizeof(in6->sin6_scope_id) );

#if !defined __APPLE__ && !defined __linux__
struct sockaddr_un * un = 0;
printf( "struct sockaddr_un: %lu\n", (unsigned long)sizeof(struct sockaddr_un) );
printf("   %03lu: sun_len: %lu\n", (unsigned long)&un->sun_len, (unsigned long)sizeof(un->sun_len) );
printf("   %03lu: sun_family: %lu\n", (unsigned long)&un->sun_family, (unsigned long)sizeof(un->sun_family) );
printf("   %03lu: sun_path: %lu\n", (unsigned long)&un->sun_path, (unsigned long)sizeof(un->sun_path) );
#endif

   return 0;
}
