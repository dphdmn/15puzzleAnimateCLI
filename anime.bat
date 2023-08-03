@echo off
setlocal enabledelayedexpansion

rem Save the argument input
set "argument=%*"

rem Run the command and capture the output in a variable
for /F "delims=" %%a in ('slidy invert %* ^| slidy apply-to-solved --size 4') do (
    set "output=%%a"
)

echo The input argument is: %argument%
echo The output is: %output%
call animate "%output%" "%argument%"