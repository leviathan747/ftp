//
// File: util_services.cc
//
// "THE BEER-WARE LICENSE" (Revision 42): 
// 
// <levi@roxsoftware.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a beer in return.  Levi Starrett
//
#include "Socket_OOA/__Socket_services.hh"

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
