#!/bin/bash
CWD=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd .. && pwd )
$HOME/git/masl/core-java/install/masl-core/bin/masl-core -domainpath $CWD/masl/Socket:$GEN_Socket_Logger_LOC:$GEN_Socket_Format_LOC -mod $CWD/masl/Socket/Socket.mod -output $CWD/gen/code_generation/Socket
cmake $CWD -DCMAKE_INSTALL_PREFIX=$PWD
