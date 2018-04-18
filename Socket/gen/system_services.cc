//
// File: system_services.cc
//
// "THE BEER-WARE LICENSE" (Revision 42): 
// 
// <levi@roxsoftware.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a beer in return.  Levi Starrett
//
#include "Socket_OOA/__Socket_services.hh"
#include "swa/Bag.hh"

namespace masld_Socket
{
  int32_t masls_close ( int32_t maslp_fd )
  {
    return close( maslp_fd );
  }

  maslt_error masls_geterror ( )
  {
    maslt_error error_code;

    if ( EACCES == errno ) error_code = maslt_error::masle_EACCES;
    else if ( EADDRINUSE == errno ) error_code = maslt_error::masle_EADDRINUSE;
    else if ( EADDRNOTAVAIL == errno ) error_code = maslt_error::masle_EADDRNOTAVAIL;
    else if ( EAFNOSUPPORT == errno ) error_code = maslt_error::masle_EAFNOSUPPORT;
    else if ( EAGAIN == errno ) error_code = maslt_error::masle_EAGAIN;
    else if ( EALREADY == errno ) error_code = maslt_error::masle_EALREADY;
    else if ( EBADF == errno ) error_code = maslt_error::masle_EBADF;
    else if ( ECONNABORTED == errno ) error_code = maslt_error::masle_ECONNABORTED;
    else if ( ECONNREFUSED == errno ) error_code = maslt_error::masle_ECONNREFUSED;
    else if ( ECONNRESET == errno ) error_code = maslt_error::masle_ECONNRESET;
    else if ( EDESTADDRREQ == errno ) error_code = maslt_error::masle_EDESTADDRREQ;
    else if ( EDOM == errno ) error_code = maslt_error::masle_EDOM;
    else if ( EFAULT == errno ) error_code = maslt_error::masle_EFAULT;
    else if ( EHOSTUNREACH == errno ) error_code = maslt_error::masle_EHOSTUNREACH;
    else if ( EINPROGRESS == errno ) error_code = maslt_error::masle_EINPROGRESS;
    else if ( EINTR == errno ) error_code = maslt_error::masle_EINTR;
    else if ( EINVAL == errno ) error_code = maslt_error::masle_EINVAL;
    else if ( EIO == errno ) error_code = maslt_error::masle_EIO;
    else if ( EISCONN == errno ) error_code = maslt_error::masle_EISCONN;
    else if ( EISDIR == errno ) error_code = maslt_error::masle_EISDIR;
    else if ( ELOOP == errno ) error_code = maslt_error::masle_ELOOP;
    else if ( EMFILE == errno ) error_code = maslt_error::masle_EMFILE;
    else if ( EMSGSIZE == errno ) error_code = maslt_error::masle_EMSGSIZE;
    else if ( ENAMETOOLONG == errno ) error_code = maslt_error::masle_ENAMETOOLONG;
    else if ( ENETDOWN == errno ) error_code = maslt_error::masle_ENETDOWN;
    else if ( ENETUNREACH == errno ) error_code = maslt_error::masle_ENETUNREACH;
    else if ( ENFILE == errno ) error_code = maslt_error::masle_ENFILE;
    else if ( ENOBUFS == errno ) error_code = maslt_error::masle_ENOBUFS;
    else if ( ENOENT == errno ) error_code = maslt_error::masle_ENOENT;
    else if ( ENOMEM == errno ) error_code = maslt_error::masle_ENOMEM;
    else if ( ENOPROTOOPT == errno ) error_code = maslt_error::masle_ENOPROTOOPT;
    else if ( ENOSR == errno ) error_code = maslt_error::masle_ENOSR;
    else if ( ENOTCONN == errno ) error_code = maslt_error::masle_ENOTCONN;
    else if ( ENOTDIR == errno ) error_code = maslt_error::masle_ENOTDIR;
    else if ( ENOTSOCK == errno ) error_code = maslt_error::masle_ENOTSOCK;
    else if ( EOPNOTSUPP == errno ) error_code = maslt_error::masle_EOPNOTSUPP;
    else if ( EPIPE == errno ) error_code = maslt_error::masle_EPIPE;
    else if ( EPROTO == errno ) error_code = maslt_error::masle_EPROTO;
    else if ( EPROTONOSUPPORT == errno ) error_code = maslt_error::masle_EPROTONOSUPPORT;
    else if ( EPROTOTYPE == errno ) error_code = maslt_error::masle_EPROTOTYPE;
    else if ( EROFS == errno ) error_code = maslt_error::masle_EROFS;
    else if ( ETIMEDOUT == errno ) error_code = maslt_error::masle_ETIMEDOUT;
    else error_code = maslt_error::masle_EUNKNOWN;

    return error_code;
  }

  int32_t masls_select ( ::SWA::Set<int32_t>&            maslp_readfds,
                         ::SWA::Set<int32_t>&            maslp_writefds,
                         ::SWA::Set<int32_t>&            maslp_exceptfds,
                         const ::SWA::Sequence<uint8_t>& maslp_timeout )
  {
    
    fd_set                   readset;
    fd_set                   writeset;
    fd_set                   exceptset;

    ::SWA::Sequence<int32_t> allfds;
    int32_t                  nfds;
    int32_t                  retval;

    ::SWA::Set<int32_t>      new_readfds;
    ::SWA::Set<int32_t>      new_writefds;
    ::SWA::Set<int32_t>      new_exceptfds;

    timeval                  timeout = {};

    // clear file descriptor sets
    FD_ZERO( &readset );
    FD_ZERO( &writeset );
    FD_ZERO( &exceptset );

    // set read descriptors
    for ( ::SWA::Set<int32_t>::const_iterator i = maslp_readfds.begin(); i != maslp_readfds.end(); ++i ) {
      FD_SET( *i, &readset );
    }

    // set write descriptors
    for ( ::SWA::Set<int32_t>::const_iterator i = maslp_writefds.begin(); i != maslp_writefds.end(); ++i ) {
      FD_SET( *i, &writeset );
    }

    // set except descriptors
    for ( ::SWA::Set<int32_t>::const_iterator i = maslp_exceptfds.begin(); i != maslp_exceptfds.end(); ++i ) {
      FD_SET( *i, &exceptset );
    }
    
    // calculate nfds
    allfds = ::SWA::Bag<int32_t>( maslp_readfds ).set_union( ::SWA::Bag<int32_t>( maslp_writefds ) ).set_union( ::SWA::Bag<int32_t>( maslp_exceptfds ) ).ordered_by();
    nfds = allfds.size() > 0 ? allfds.getData().back() + 1 : 0;

    // set timeout
    memcpy( &timeout, maslp_timeout.getData().data(), sizeof(timeout) );

    // invoke select
    retval = select( nfds, &readset, &writeset, &exceptset, &timeout );

    // set available read descriptors
    new_readfds = ::SWA::Set<int32_t>();
    for ( ::SWA::Set<int32_t>::const_iterator i = maslp_readfds.begin(); i != maslp_readfds.end(); ++i ) {
      if ( FD_ISSET( *i, &readset ) ) new_readfds += *i;
    }
    maslp_readfds = new_readfds;

    // set available write descriptors
    new_writefds = ::SWA::Set<int32_t>();
    for ( ::SWA::Set<int32_t>::const_iterator i = maslp_writefds.begin(); i != maslp_writefds.end(); ++i ) {
      if ( FD_ISSET( *i, &writeset ) ) new_writefds += *i;
    }
    maslp_writefds = new_writefds;

    // set available except descriptors
    new_exceptfds = ::SWA::Set<int32_t>();
    for ( ::SWA::Set<int32_t>::const_iterator i = maslp_exceptfds.begin(); i != maslp_exceptfds.end(); ++i ) {
      if ( FD_ISSET( *i, &exceptset ) ) new_exceptfds += *i;
    }
    maslp_exceptfds = new_exceptfds;

    return retval;

  }

  ::SWA::String masls_strerror ( )
  {
    return ::SWA::String( strerror( errno ) );
  }

}
