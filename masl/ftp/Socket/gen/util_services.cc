//
// File: util_services.cc
//
#include "Socket_OOA/__Socket_interface.hh"
#include "Socket_OOA/__Socket_services.hh"
#include "Socket_OOA/__Socket_types.hh"
#include "swa/Domain.hh"
#include "swa/Stack.hh"
#include "swa/String.hh"

#include <errno.h>
#include <string.h>
#include <sys/time.h>

#include <stdio.h>

namespace masld_Socket
{
  ::SWA::String masls_datatostring ( const maslt_data& maslp_data )
  {
    std::ostringstream oss;
    for ( maslt_data::const_iterator it = maslp_data.begin(); it != maslp_data.end(); it++ ) {
      oss << (char)*it;
    }
    return ::SWA::String( oss.str() );
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

  ::SWA::String masls_strerror ( )
  {
    return ::SWA::String( strerror( errno ) );
  }

  maslt_data masls_durationtotimeval ( const ::SWA::Duration& maslp_duration )
  {
    struct timeval tv = {};
    uint8_t *      dataptr = (uint8_t *)&tv;

    tv.tv_sec = maslp_duration.seconds();
    tv.tv_usec = maslp_duration.microOfSecond();

    return maslt_data( dataptr, dataptr + sizeof(struct timeval) );
  }

  maslt_data masls_stringtodata ( const ::SWA::String& maslp_s )
  {
    return maslt_data( maslp_s.begin(), maslp_s.end() );
  }

}
