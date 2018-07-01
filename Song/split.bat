@echo off
setlocal enabledelayedexpansion

REM // Quit if it was run on its own with no audio file
IF [%1]==[] (
	echo Run this by dragging the full audio file onto it.
	pause
	GOTO:eof
)

echo %1
for /R . %%x IN (.) DO (
	rem echo %~dp0
	rem echo %%x
	set start=null
	set end=null

	IF EXIST %%x\meta.txt (
 		REM // Set start and end to the first and second lines of meta.txt
		FOR /F usebackq %%i IN ("%%x\meta.txt") DO (
			rem echo %%i
			IF !start!==null (set start=%%i) ELSE (set end=%%i)
		)
		echo !start!
		echo !end!
		REM // run the master audio file through ffmpeg cutting off the segment for the timecodes given without reencoding
		"ffmpeg-4.0-win64-static\bin\ffmpeg.exe" -y -i %1 -ss !start! -to !end! -acodec copy "%%x\output.ogg"
		copy "Set as active.bat" "%%x"

		IF NOT EXIST %%x\Expert.json (
			copy "Expert - Blank.json" "%%x\Expert.json"
		)
	)
)

pause