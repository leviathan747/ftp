//
// File: socket_services.cc
//
// "THE BEER-WARE LICENSE" (Revision 42): 
// 
// <levi@roxsoftware.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a beer in return.  Levi Starrett
//
#include "Socket_OOA/__Socket_services.hh"
#include <arpa/inet.h>

namespace masld_Socket
{

  maslt_socketfd masls_accept ( maslt_socketfd maslp_socket,
                                maslt_sockaddr& maslp_address )
  {
    struct sockaddr_in peeraddress     = {};
    socklen_t          peeraddress_len = sizeof(peeraddress);
    maslt_socketfd sock                = -1;

    sock = accept( maslp_socket, (struct sockaddr *)&peeraddress, &peeraddress_len );
    if ( sock >= 0 ) {

      maslp_address.set_masla_address() = ::SWA::String( inet_ntoa( peeraddress.sin_addr) );
      maslp_address.set_masla_port() = (int32_t)ntohs( peeraddress.sin_port );

    }
    return sock;
  }

  int32_t masls_bind ( maslt_socketfd        maslp_socket,
                       const maslt_sockaddr& maslp_address )
  {
    struct sockaddr_in localaddress = {};

    localaddress.sin_family = AF_INET;
    inet_aton( maslp_address.get_masla_address().c_str(), &(localaddress.sin_addr) );
    localaddress.sin_port = htons( maslp_address.get_masla_port() );

    return bind( maslp_socket, (struct sockaddr *)&localaddress, sizeof(localaddress) );
  }

  int32_t masls_connect ( maslt_socketfd        maslp_socket,
                          const maslt_sockaddr& maslp_address )
  {
    struct sockaddr_in peeraddress = {};

    peeraddress.sin_family = AF_INET;
    inet_aton( maslp_address.get_masla_address().c_str(), &(peeraddress.sin_addr) );
    peeraddress.sin_port = htons( maslp_address.get_masla_port() );

    return connect( maslp_socket, (struct sockaddr *)&peeraddress, sizeof(peeraddress) );
  }

  int32_t masls_getpeername ( maslt_socketfd  maslp_socket,
                              maslt_sockaddr& maslp_address )
  {
    struct sockaddr_in peeraddress     = {};
    socklen_t          peeraddress_len = sizeof(peeraddress);
    int32_t            retval          = -1;

    retval = getpeername( maslp_socket, (struct sockaddr *)&peeraddress, &peeraddress_len );
    if ( retval >= 0 ) {

      maslp_address.set_masla_address() = ::SWA::String( inet_ntoa( peeraddress.sin_addr) );
      maslp_address.set_masla_port() = (int32_t)ntohs( peeraddress.sin_port );

    }
    return retval;
  }

  int32_t masls_getsockname ( maslt_socketfd  maslp_socket,
                              maslt_sockaddr& maslp_address )
  {
    struct sockaddr_in localaddress     = {};
    socklen_t          localaddress_len = sizeof(localaddress);
    int32_t            retval          = -1;

    retval = getsockname( maslp_socket, (struct sockaddr *)&localaddress, &localaddress_len );
    if ( retval >= 0 ) {

      maslp_address.set_masla_address() = ::SWA::String( inet_ntoa( localaddress.sin_addr) );
      maslp_address.set_masla_port() = (int32_t)ntohs( localaddress.sin_port );

    }
    return retval;
  }

  int32_t masls_getsockopt ( maslt_socketfd          maslp_socket,
                             const maslt_optionname& maslp_option,
                             maslt_data&             maslp_value )
  {
    uint8_t buf[ 1024 ] = {};
    int32_t size        = 1024;
    int32_t retval      = -1;

    int32_t option = -1;
    if ( maslt_optionname::masle_SO_DEBUG == maslp_option ) option = SO_DEBUG;
    else if ( maslt_optionname::masle_SO_ACCEPTCONN == maslp_option ) option = SO_ACCEPTCONN;
    else if ( maslt_optionname::masle_SO_BROADCAST == maslp_option ) option = SO_BROADCAST;
    else if ( maslt_optionname::masle_SO_REUSEADDR == maslp_option ) option = SO_REUSEADDR;
    else if ( maslt_optionname::masle_SO_KEEPALIVE == maslp_option ) option = SO_KEEPALIVE;
    else if ( maslt_optionname::masle_SO_LINGER == maslp_option ) option = SO_LINGER;
    else if ( maslt_optionname::masle_SO_OOBINLINE == maslp_option ) option = SO_OOBINLINE;
    else if ( maslt_optionname::masle_SO_SNDBUF == maslp_option ) option = SO_SNDBUF;
    else if ( maslt_optionname::masle_SO_RCVBUF == maslp_option ) option = SO_RCVBUF;
    else if ( maslt_optionname::masle_SO_ERROR == maslp_option ) option = SO_ERROR;
    else if ( maslt_optionname::masle_SO_TYPE == maslp_option ) option = SO_TYPE;
    else if ( maslt_optionname::masle_SO_DONTROUTE == maslp_option ) option = SO_DONTROUTE;
    else if ( maslt_optionname::masle_SO_RCVLOWAT == maslp_option ) option = SO_RCVLOWAT;
    else if ( maslt_optionname::masle_SO_RCVTIMEO == maslp_option ) option = SO_RCVTIMEO;
    else if ( maslt_optionname::masle_SO_SNDLOWAT == maslp_option ) option = SO_SNDLOWAT;
    else if ( maslt_optionname::masle_SO_SNDTIMEO == maslp_option ) option = SO_SNDTIMEO;
    else option = -1;

    maslp_value.clear();

    retval = getsockopt( maslp_socket, SOL_SOCKET, option, buf, &size );
    if ( retval >= 0 ) {

      for ( int32_t i = 0; i < size; i++ ) {
        maslp_value += buf[i];
      }

    }

    return retval;
  }

  int32_t masls_listen ( maslt_socketfd maslp_socket,
                         int32_t        maslp_backlog )
  {
    return listen( maslp_socket, maslp_backlog );
  }

  int32_t masls_recv ( maslt_socketfd maslp_socket,
                       maslt_data&    maslp_buffer,
                       int32_t        maslp_length,
                       int32_t        maslp_flags )
  {
    uint8_t buf[ maslp_length ] = {};
    int32_t retval              = -1;

    maslp_buffer.clear();

    retval = recv( maslp_socket, buf, maslp_length, maslp_flags );
    if ( retval >= 0 ) {

      for ( int32_t i = 0; i < retval; i++ ) {
        maslp_buffer += buf[i];
      }

    }
    return retval;
  }

  int32_t masls_recvfrom ( maslt_socketfd  maslp_socket,
                           maslt_data&     maslp_buffer,
                           int32_t         maslp_length,
                           int32_t         maslp_flags,
                           maslt_sockaddr& maslp_address )
  {
    uint8_t buf[ maslp_length ]        = {};
    struct sockaddr_in peeraddress     = {};
    socklen_t          peeraddress_len = sizeof(peeraddress);
    int32_t retval                     = -1;

    maslp_buffer.clear();

    retval = recvfrom( maslp_socket, buf, maslp_length, maslp_flags, (struct sockaddr *)&peeraddress, &peeraddress_len );
    if ( retval >= 0 ) {

      for ( int32_t i = 0; i < retval; i++ ) {
        maslp_buffer += buf[i];
      }

      maslp_address.set_masla_address() = ::SWA::String( inet_ntoa( peeraddress.sin_addr) );
      maslp_address.set_masla_port() = (int32_t)ntohs( peeraddress.sin_port );

    }
    return retval;
  }

  int32_t masls_send ( maslt_socketfd    maslp_socket,
                       const maslt_data& maslp_message,
                       int32_t           maslp_length,
                       int32_t           maslp_flags )
  {
    return send( maslp_socket, maslp_message.getData().data(), maslp_length, maslp_flags );
  }

  int32_t masls_sendto ( maslt_socketfd        maslp_socket,
                         const maslt_data&     maslp_message,
                         int32_t               maslp_length,
                         int32_t               maslp_flags,
                         const maslt_sockaddr& maslp_address )
  {
    struct sockaddr_in peeraddress = {};

    peeraddress.sin_family = AF_INET;
    inet_aton( maslp_address.get_masla_address().c_str(), &(peeraddress.sin_addr) );
    peeraddress.sin_port = htons( maslp_address.get_masla_port() );

    return sendto( maslp_socket, maslp_message.getData().data(), maslp_length, maslp_flags, (struct sockaddr *)&peeraddress, sizeof(peeraddress) );
  }

  int32_t masls_setsockopt ( maslt_socketfd          maslp_socket,
                             const maslt_optionname& maslp_option,
                             const maslt_data&       maslp_value )
  {
    int32_t option = -1;
    if ( maslt_optionname::masle_SO_DEBUG == maslp_option ) option = SO_DEBUG;
    else if ( maslt_optionname::masle_SO_BROADCAST == maslp_option ) option = SO_BROADCAST;
    else if ( maslt_optionname::masle_SO_REUSEADDR == maslp_option ) option = SO_REUSEADDR;
    else if ( maslt_optionname::masle_SO_KEEPALIVE == maslp_option ) option = SO_KEEPALIVE;
    else if ( maslt_optionname::masle_SO_LINGER == maslp_option ) option = SO_LINGER;
    else if ( maslt_optionname::masle_SO_OOBINLINE == maslp_option ) option = SO_OOBINLINE;
    else if ( maslt_optionname::masle_SO_SNDBUF == maslp_option ) option = SO_SNDBUF;
    else if ( maslt_optionname::masle_SO_RCVBUF == maslp_option ) option = SO_RCVBUF;
    else if ( maslt_optionname::masle_SO_DONTROUTE == maslp_option ) option = SO_DONTROUTE;
    else if ( maslt_optionname::masle_SO_RCVLOWAT == maslp_option ) option = SO_RCVLOWAT;
    else if ( maslt_optionname::masle_SO_RCVTIMEO == maslp_option ) option = SO_RCVTIMEO;
    else if ( maslt_optionname::masle_SO_SNDLOWAT == maslp_option ) option = SO_SNDLOWAT;
    else if ( maslt_optionname::masle_SO_SNDTIMEO == maslp_option ) option = SO_SNDTIMEO;
    else option = -1;

    return setsockopt( maslp_socket, SOL_SOCKET, option, maslp_value.getData().data(), maslp_value.size() );
  }

  int32_t masls_shutdown ( maslt_socketfd            maslp_socket,
                           const maslt_shutdowntype& maslp_how )
  {
    int32_t how = -1;
    if ( maslt_shutdowntype::masle_SHUT_RD == maslp_how ) how = SHUT_RD;
    else if ( maslt_shutdowntype::masle_SHUT_WR == maslp_how ) how = SHUT_WR;
    else if ( maslt_shutdowntype::masle_SHUT_RDWR == maslp_how ) how = SHUT_RDWR;
    else how = -1;

    return shutdown( maslp_socket, how );
  }

  maslt_socketfd masls_socket ( const maslt_socktype&  maslp_socktype,
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
