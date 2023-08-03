@echo off
setlocal
set "arg1=%~1"
set "arg2=%~2"
set "scripts_folder=%~dp0scripts"
for /f "delims=" %%a in ('slidy format -l "%arg2%"') do set "temp_arg2=%%a"
%scripts_folder%\generate "%arg1%" "%temp_arg2%" | %scripts_folder%\core.exe
endlocal