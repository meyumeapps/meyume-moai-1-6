
@echo off
setlocal enableextensions


set rootpath=%~dp0%..
set defaultprefix=%rootpath%\lib\android
set libprefix=%1
if "%libprefix%"=="" set libprefix=%defaultprefix%

set cmake_folder="%~dp0%..\cmake"

for %%G in (armeabi,armeabi-v7a,x86) DO (
cd %cmake_folder%
md build-android-%%G
cd build-android-%%G


cmake ^
-DBUILD_ANDROID=TRUE ^
-DCMAKE_TOOLCHAIN_FILE="..\hosts\host-android\android.toolchain.cmake" ^
-DCMAKE_BUILD_TYPE=Release ^
-DMOAI_LUAJIT=False ^
-DANDROID_ABI=%%G ^
-DCMAKE_INSTALL_PREFIX=%libprefix%\%%G ^
-DLIBRARY_OUTPUT_PATH_ROOT=.\build-android-%%G\ ^
-G"MinGW Makefiles" ^
-DCMAKE_MAKE_PROGRAM="%ANDROID_NDK%\prebuilt\windows\bin\make.exe" ^
..\

cmake --build . --target install 
)

