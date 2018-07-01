@echo off
setlocal enabledelayedexpansion

REM // Quit if it was run on its own with no audio file
IF [%1]==[] (
	echo Run this by dragging the full audio file onto it.
	pause
	GOTO:eof
)

copy "Expert - Blank.json" "Expert.json"
for /R . %%x IN (.) DO (
	echo %~dp0Expert.json
	echo %%x
	set start=null
	FOR /F usebackq %%i IN ("%%x\meta.txt") DO IF !start!==null set start=%%i
	REM set /p start=<"%%x\meta.txt"
	echo !start!
	"bsss.exe" m "%~dp0Expert.json" "%%x\Expert.json" !start! "%~dp0temp.json"
	copy "temp.json" "Expert.json"
)

rem for %%F in (%1) do set audio=%%~nxF
"bsss.exe" s "%~dp0info.json" "%~dp0temp.json" "%~nx1"
copy "temp.json" "info.json"

pause