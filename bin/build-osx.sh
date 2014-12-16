#!/bin/bash

#
# Build script for Mac OSX
# Usage: Run from Moai SDK's root directory:
#
# build-osx-sdl.sh
#
# You can change the CMake options using -DOPTION=VALUE
# Check moai-dev/cmake/CMakeLists.txt for all the available options.
#
if [ x$1 == x ]; then
  libprefix=`dirname $0`/../lib/osx
else
  libprefix=$1
fi
mkdir -p $libprefix

libprefix=$(cd $libprefix; pwd)

cd `dirname $0`/..
cd cmake

mkdir build
cd build
cmake -G "Xcode" \
-DBUILD_OSX=TRUE \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX=$libprefix \
../hosts/host-osx-sdl

cmake --build . --target install --config Release

if [ ! -e "../../util/moai" ]; then
   cp $libprefix/bin/moai ../../util/moai
fi

