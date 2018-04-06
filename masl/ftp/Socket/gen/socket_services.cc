//
// File: socket_services.cc
//
#include "Socket_OOA/__Socket_interface.hh"
#include "Socket_OOA/__Socket_services.hh"
#include "Socket_OOA/__Socket_types.hh"
#include <stdint.h>
#include "swa/Domain.hh"
#include "swa/Stack.hh"
#include <stdio.h>

namespace masld_Socket
{

  int32_t masls_accept ( maslt_sockethandle maslp_socket,
                         maslt_sockaddr&    maslp_address )
  {
    printf( "executing accept\n");
    return 0;
  }

  int32_t masls_bind ( maslt_sockethandle    maslp_socket,
                       const maslt_sockaddr& maslp_address )
  {
    printf( "executing bind\n");
    return 0;
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

  int32_t masls_getsockopt ( maslt_sockethandle       maslp_socket,
                             const maslt_optionlevel& maslp_level,
                             const maslt_optionname&  maslp_option,
                             maslt_data&              maslp_option_value )
  {
    printf( "executing getsockopt\n");
    return 0;
  }

  int32_t masls_listen ( maslt_sockethandle maslp_socket,
                         int32_t            maslp_backlog )
  {
    printf( "executing listen\n");
    return 0;
  }

  int32_t masls_recv ( maslt_sockethandle maslp_socket,
                       maslt_data&        maslp_buffer,
                       int32_t            maslp_length,
                       int32_t            maslp_flags )
  {
    printf( "executing recv\n");
    return 0;
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

  int32_t masls_setsockopt ( maslt_sockethandle       maslp_socket,
                             const maslt_optionlevel& maslp_level,
                             const maslt_optionname&  maslp_option,
                             const maslt_data&        maslp_option_value )
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

  maslt_sockethandle masls_socket ( const maslt_sockfamily& maslp_family,
                                    const maslt_socktype&   maslp_socktype,
                                    const maslt_sockproto&  maslp_protocol )
  {
    printf( "executing socket\n");
    return 0;
  }

}
