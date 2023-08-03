@echo off
setlocal enabledelayedexpansion

REM Check if both arguments are provided
if "%~2"=="" (
    echo Usage: generate_states "arg1" "arg2"
    exit /b 1
)

REM Save arguments to variables with quotes
set "arg1=%~1"
set "arg2=%~2"

REM Calculate the length of the second argument
call :strlen length_arg2 "%arg2%"
set /A "length_arg2-=1"

REM Loop through each character of arg2
for /L %%i in (0,1,%length_arg2%) do (
    REM Get the current character of arg2 at position %%i
    set "current_char=!arg2:~%%i,1!"

    REM Form the command with the latest output and the current character of arg2
    set "command=slidy apply --state "!arg1!" --alg !current_char!"

    REM Execute the command and save the latest output to arg1
    for /F "delims=" %%o in ('!command!') do set "arg1=%%o"

    REM Print the latest output directly
    echo !arg1!
)

endlocal
exit /b

:strlen <result_var> <string>
setlocal enabledelayedexpansion
set "str=%~2"
set "len=0"
:loop
if defined str (
    set "str=!str:~1!"
    set /A "len+=1"
    goto :loop
)
( 
    endlocal
    set "%~1=%len%"
    exit /b
)
