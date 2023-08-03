g++ -O3 -o core.exe colortest.cpp
@echo off
REM Get the parent folder (one level up)
for %%I in ("%~dp0.") do set "PARENT_FOLDER=%%~dpI"

REM Set the target folder where "scripts" exists
set "TARGET_FOLDER=%PARENT_FOLDER%scripts"

REM Check if the target folder exists, if not, create it
if not exist "%TARGET_FOLDER%" mkdir "%TARGET_FOLDER%"

REM Copy the file from the current folder to the target folder
copy "%~dp0core.exe" "%TARGET_FOLDER%"

REM Remove the original file after copying
del "%~dp0core.exe"

pause
