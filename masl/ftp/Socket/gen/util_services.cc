//
// File: util_services.cc
//
#include "Socket_OOA/__Socket_interface.hh"
#include "Socket_OOA/__Socket_services.hh"
#include "Socket_OOA/__Socket_types.hh"
#include "swa/Domain.hh"
#include "swa/Stack.hh"
#include "swa/String.hh"

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

}
