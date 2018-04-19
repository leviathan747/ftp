#!/bin/bash
MASLMC=$HOME/git/masl/core-java/install/masl-core/bin/masl-core
CWD=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd .. && pwd )
if [[ "" == $GEN_Telnet_Socket_LOC ]]; then
  GEN_Telnet_Socket_LOC="$CWD/../Socket"
fi
GEN_Telnet_Logger_LOC="$HOME/git/masl/examples/utils/Logger_OOA"
GEN_Telnet_BinaryIO_LOC="$HOME/git/masl/examples/utils/BinaryIO_OOA"
TEST=-test
if [[ $# > 0 && $1 == "notest" ]]; then
  TEST=
fi

$MASLMC -domainpath $GEN_Telnet_Socket_LOC/masl/Socket:$GEN_Telnet_Logger_LOC:$GEN_Telnet_BinaryIO_LOC \
        -mod $CWD/masl/Telnet/Telnet.mod \
        -output $CWD/gen/code_generation/Telnet \
        -copyright $CWD/../LICENSE.md \
        $TEST \
        -skiptranslator Sqlite
$MASLMC -mod $GEN_Telnet_Socket_LOC/masl/Socket/Socket.int \
        -output $CWD/gen/code_generation/Socket \
        -copyright $CWD/../LICENSE.md \
        -custombuildfile $GEN_Telnet_Socket_LOC/gen/custom.cmake \
        -skiptranslator Sqlite
$MASLMC -mod $GEN_Telnet_Logger_LOC/Logger.int \
        -output $CWD/gen/code_generation/Logger \
        -copyright $CWD/../LICENSE.md \
        -skiptranslator Sqlite
$MASLMC -mod $GEN_Telnet_BinaryIO_LOC/BinaryIO.int \
        -output $CWD/gen/code_generation/BinaryIO \
        -copyright $CWD/../LICENSE.md \
        -skiptranslator Sqlite

cmake $CWD -DCMAKE_INSTALL_PREFIX=$PWD
