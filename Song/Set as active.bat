@echo off

copy "Expert.json" "../Expert.json"
copy "output.ogg" "../output.ogg"

rem FOR /F %%i IN (meta.txt) DO set start=%%i
set /p start=< meta.txt

"..\bsss.exe" a "%~dp0..\info.json" %start% "%~dp0..\temp.json" "output.ogg"
copy "..\temp.json" "..\info.json"

for %%I in (.) do set CurrDirName=%%~nxI
echo "%CurrDirName%"> "../Active.txt"

pause