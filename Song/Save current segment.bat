@echo off

set /p folder=< active.txt

copy "Expert.json" %folder%"\Expert.json"
echo %folder% saved!

pause