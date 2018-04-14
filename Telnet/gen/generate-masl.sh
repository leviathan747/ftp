#!/bin/bash
MASLMC=$HOME/git/masl/core-java/install/masl-core/bin/masl-core
CWD=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd .. && pwd )
if [[ "" == $GEN_Telnet_Socket_LOC ]]; then
  GEN_Telnet_Socket_LOC="$CWD/../Socket"
fi
TEST=-test
if [[ $# > 0 && $1 == "notest" ]]; then
  TEST=
fi

$MASLMC -domainpath $GEN_Telnet_Socket_LOC/masl/Socket \
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

cmake $CWD -DCMAKE_INSTALL_PREFIX=$PWD
