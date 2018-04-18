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
  ::SWA::Sequence<uint8_t> masls_durationtotimeval ( const ::SWA::Duration& maslp_duration )
  {
    struct timeval tv = {};
    uint8_t *      dataptr = (uint8_t *)&tv;

    tv.tv_sec = maslp_duration.seconds();
    tv.tv_usec = maslp_duration.microOfSecond();

    return ::SWA::Sequence<uint8_t>( dataptr, dataptr + sizeof(struct timeval) );
  }
}
