#!/bin/bash
MASLMC=$HOME/git/masl/core-java/install/masl-core/bin/masl-core
CWD=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd .. && pwd )
TEST=-test
if [[ $# > 0 && $1 == "notest" ]]; then
  TEST=
fi
$MASLMC -mod $CWD/masl/Socket/Socket.mod -output $CWD/gen/code_generation $TEST -copyright $CWD/../LICENSE.md -custombuildfile $CWD/gen/custom.cmake
cmake $CWD -DCMAKE_INSTALL_PREFIX=$PWD
