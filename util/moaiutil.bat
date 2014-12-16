@echo off
set SCRIPT_DIR=%~dp0%
set INVOKE_DIR=%CD%

set SCRIPT=%SCRIPT_DIR%%1.lua


set args=%SCRIPT_DIR% %INVOKE_DIR%

shift

:parse
if "%~1" neq "" (
   set args=%args% %1
   shift 
   goto :parse
)
pushd %SCRIPT_DIR% 
moai %SCRIPT% %args%
popd 
