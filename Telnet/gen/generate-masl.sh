#!/bin/bash
MASLMC=$HOME/git/masl/core-java/install/masl-core/bin/masl-core
CWD=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd .. && pwd )
if [[ "" == $GEN_Telnet_Socket_LOC ]]; then
  GEN_Telnet_Socket_LOC="$CWD/../Socket/masl/Socket"
fi
$MASLMC -domainpath $GEN_Telnet_Socket_LOC -mod $CWD/masl/Telnet/Telnet.mod -output $CWD/gen/code_generation/Telnet -copyright $CWD/../LICENSE.md
$MASLMC -mod $GEN_Telnet_Socket_LOC/Socket.int -output $CWD/gen/code_generation/Socket -copyright $CWD/../LICENSE.md
cmake $CWD -DCMAKE_INSTALL_PREFIX=$PWD
