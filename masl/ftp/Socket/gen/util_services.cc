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

  int32_t masls_errno ( )
  {
    return errno;
  }

  ::SWA::String masls_strerror ( int32_t maslp_errno )
  {
    return ::SWA::String( strerror( maslp_errno ) );
  }

  maslt_data masls_durationtotimeval ( const ::SWA::Duration& maslp_duration )
  {
    struct timeval tv = {};
    uint8_t *      dataptr = (uint8_t *)&tv;

    tv.tv_sec = maslp_duration.seconds();
    tv.tv_usec = maslp_duration.microOfSecond();

    return maslt_data( dataptr, dataptr + sizeof(struct timeval) );
  }

}
