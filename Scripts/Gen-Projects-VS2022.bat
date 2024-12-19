@echo off

set PREMAKE_FILE=premake5.lua

if NOT "%1"=="" (
	set PREMAKE_FILE=%1
)

..\ThirdParty\premake5\premake5.exe vs2022 --file=%PREMAKE_FILE%

pause
