#!/bin/bash
if [ x$ANDROID_NDK == x ]; then
   echo ANDROID_NDK variable was not set. Please set to your ndk path
   exit 1
fi

which cmake || (echo Could not find cmake ; exit 1)

if [ x$1 == x ]; then
  libprefix=`dirname $0`/../lib/android
else
  libprefix=$1
fi
mkdir -p $libprefix

cmakefolder=`dirname $0`/../cmake
cmakefolder=$(cd $cmakefolder; pwd)

libprefix=$(cd $libprefix; pwd)


for ARCH in armeabi armeabi-v7a x86
do

  cd $cmakefolder
  mkdir build-android-$ARCH
  cd build-android-$ARCH
  cmake \
  -DBUILD_ANDROID=TRUE \
  -DCMAKE_TOOLCHAIN_FILE="../hosts/host-android/android.toolchain.cmake" \
  -DCMAKE_BUILD_TYPE=Release \
  -DMOAI_LUAJIT=False \
  -DANDROID_ABI=$ARCH \
  -DCMAKE_INSTALL_PREFIX=$libprefix/$ARCH \
  -DLIBRARY_OUTPUT_PATH_ROOT=./build-android-$ARCH/ \
  ../

  cmake --build . --target install

done
