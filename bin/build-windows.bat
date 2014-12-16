@echo off
rem :: Determine target directory and cmake generator
setlocal enableextensions

lib /NOLOGO
if ERRORLEVEL 1 goto hasnolib
GOTO haslib
:hasnolib
echo "Could not find lib.exe (are you in your VS developer tools prompt?)"
GOTO:EOF


:haslib
set arg1=%1
if "%arg1%"=="" set arg1=vs2012
set generator=
if "%arg1%"=="vs2008" set generator=Visual Studio 9 2008
if "%arg1%"=="vs2010" set generator=Visual Studio 10
if "%arg1%"=="vs2012" set generator=Visual Studio 11
if "%arg1%"=="vs2013" set generator=Visual Studio 12
if "%generator%"=="" (
	@echo Unknown argument "%1". Valid values are vs2008, vs2010, vs2012, vs2013. Exiting.
	goto end
)
set rootpath=%~dp0%..
set defaultprefix=%rootpath%\lib\windows\%arg1%
set libprefix=%2
if "%libprefix%"=="" set libprefix=%defaultprefix%

md "%~dp0%..\build"
cd "%~dp0%..\build"
md build-%arg1%
cd build-%arg1%

echo Creating Release Libs
cmake -G "%generator%" ^
-DBUILD_WINDOWS=true ^
-DCMAKE_INSTALL_PREFIX=%libprefix%\Release ^
%rootpath%\cmake\hosts\host-win-sdl

cmake --build . --target INSTALL --config Release

erase  libmoai\third-party\luajit\luajit\src\lua51.lib

echo Creating Debug Libs
cmake -DCMAKE_INSTALL_PREFIX=%libprefix%\Debug %rootpath%\cmake\hosts\host-win-sdl

cmake --build . --target INSTALL --config Debug 

echo Creating Distribute Libs
rmdir /S/Q %libprefix%\Distribute\lib

md %libprefix%\Distribute\lib
lib /OUT:%libprefix%\Distribute\lib\moai.LIB %libprefix%\Release\lib\*.lib

lib /OUT:%libprefix%\Distribute\lib\moai_d.LIB %libprefix%\Debug\lib\*.lib
xcopy /S/I/Y %libprefix%\Release\include %libprefix%\Distribute\include
copy /Y %libprefix%\Release\bin\moai.exe %libprefix%\Distribute\bin\moai.exe


if NOT EXIST %rootpath%\util\moai.exe copy /Y %libprefix%\Release\bin\moai.exe %rootpath%\util\moai.exe
rem rd /S/Q %libprefix%\Release
rem rd /S/Q %libprefix%\Debug

echo "Build complete"