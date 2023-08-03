@echo off
setlocal
set "arg1=%~1"
set "arg2=%~2"

REM Run the "slidy format" command and store the output in a temporary variable
for /f "delims=" %%a in ('slidy format -l "%arg2%"') do set "temp_arg2=%%a"

REM Run "generate" with the updated "arg2"
generate "%arg1%" "%temp_arg2%" | core.exe
endlocal