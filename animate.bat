@echo off
setlocal
set "arg1=%~1"
set "arg2=%~2"
generate "%arg1%" "%arg2%" | core.exe
endlocal