//
// File: socket_services.cc
//
#include "Socket_OOA/__Socket_interface.hh"
#include "Socket_OOA/__Socket_services.hh"
#include "Socket_OOA/__Socket_types.hh"
#include <stdint.h>
#include "swa/Domain.hh"
#include "swa/Stack.hh"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

namespace masld_Socket
{

  maslt_sockethandle masls_accept ( maslt_sockethandle maslp_socket,
                                    maslt_sockaddr&    maslp_address )
  {
    struct sockaddr_in peeraddress     = {};
    socklen_t          peeraddress_len = sizeof(peeraddress);
    int32_t            retval          = -1;

    retval = accept( maslp_socket, (struct sockaddr *)&peeraddress, &peeraddress_len );
    if ( retval >= 0 ) {

      maslp_address.set_masla_address() = ::SWA::String( inet_ntoa( peeraddress.sin_addr) );
      maslp_address.set_masla_port() = (int32_t)ntohs( peeraddress.sin_port );

    }
    else {
      int opt = 12345;
      int32_t retval2;
      retval2 = getsockopt( maslp_socket, SOL_SOCKET, SO_ACCEPTCONN, &opt, sizeof(int) );
      printf( "retval2: %d, error code: %d, errno: %d, msg: %s\n", retval2, opt, errno, strerror( errno ) );
    }
    return retval;
  }

  int32_t masls_bind ( maslt_sockethandle    maslp_socket,
                       const maslt_sockaddr& maslp_address )
  {
    struct sockaddr_in localaddress = {};

    localaddress.sin_family = AF_INET;
    inet_aton( maslp_address.get_masla_address().c_str(), &(localaddress.sin_addr) );
    localaddress.sin_port = htons( maslp_address.get_masla_port() );

    return bind( maslp_socket, (struct sockaddr *)&localaddress, sizeof(localaddress) );
  }

  int32_t masls_connect ( maslt_sockethandle    maslp_socket,
                          const maslt_sockaddr& maslp_address )
  {
    printf( "executing connect\n");
    return 0;
  }

  int32_t masls_getpeername ( maslt_sockethandle maslp_socket,
                              maslt_sockaddr&    maslp_address )
  {
    printf( "executing getpeername\n");
    return 0;
  }

  int32_t masls_getsockname ( maslt_sockethandle maslp_socket,
                              maslt_sockaddr&    maslp_address )
  {
    printf( "executing getsockname\n");
    return 0;
  }

  int32_t masls_getsockopt ( maslt_sockethandle      maslp_socket,
                             const maslt_optionname& maslp_option,
                             maslt_data&             maslp_value )
  {
    printf( "executing getsockopt\n");
    return 0;
  }

  int32_t masls_listen ( maslt_sockethandle maslp_socket,
                         int32_t            maslp_backlog )
  {
    return listen( maslp_socket, maslp_backlog );
  }

  int32_t masls_recv ( maslt_sockethandle maslp_socket,
                       maslt_data&        maslp_buffer,
                       int32_t            maslp_length,
                       int32_t            maslp_flags )
  {
    uint8_t buf[ maslp_length ] = {};
    int32_t retval              = -1;

    printf( "waiting for data...\n" );
    retval = recv( maslp_socket, buf, maslp_length, maslp_flags );
    if ( retval >= 0 ) {

      for ( int32_t i = 0; i < retval; i++ ) {
        maslp_buffer += buf[i];
      }

    }
    return retval;
  }

  int32_t masls_recvfrom ( maslt_sockethandle maslp_socket,
                           maslt_data&        maslp_buffer,
                           int32_t            maslp_length,
                           int32_t            maslp_flags,
                           maslt_sockaddr&    maslp_address )
  {
    printf( "executing recvfrom\n");
    return 0;
  }

  int32_t masls_send ( maslt_sockethandle maslp_socket,
                       const maslt_data&  maslp_message,
                       int32_t            maslp_length,
                       int32_t            maslp_flags )
  {
    printf( "executing send\n");
    return 0;
  }

  int32_t masls_sendto ( maslt_sockethandle    maslp_socket,
                         const maslt_data&     maslp_message,
                         int32_t               maslp_length,
                         int32_t               maslp_flags,
                         const maslt_sockaddr& maslp_address )
  {
    printf( "executing sendto\n");
    return 0;
  }

  int32_t masls_setsockopt ( maslt_sockethandle      maslp_socket,
                             const maslt_optionname& maslp_option,
                             const maslt_data&       maslp_value )
  {
    printf( "executing setsockopt\n");
    return 0;
  }

  int32_t masls_shutdown ( maslt_sockethandle maslp_socket,
                           int32_t            maslp_how )
  {
    printf( "executing shutdown\n");
    return 0;
  }

  maslt_sockethandle masls_socket ( const maslt_socktype&  maslp_socktype,
                                    const maslt_sockproto& maslp_protocol )
  {
    int32_t type  = -1;
    int32_t proto = -1;

    if ( maslt_socktype::masle_SOCK_STREAM == maslp_socktype )
      type = SOCK_STREAM;
    else if ( maslt_socktype::masle_SOCK_DGRAM == maslp_socktype )
      type = SOCK_DGRAM;
    else
      type = -1;

    if ( maslt_sockproto::masle_IPPROTO_TCP == maslp_protocol )
      proto = IPPROTO_TCP;
    else if ( maslt_sockproto::masle_IPPROTO_UDP == maslp_protocol )
      proto = IPPROTO_UDP;
    else
      proto = -1;

    return socket( AF_INET, type, proto );
  }

}
