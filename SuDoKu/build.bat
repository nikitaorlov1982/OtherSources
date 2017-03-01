@echo off
set TARGET=sudoku
set SRC=main.asm random.asm
if exist %TARGET%.exe del %TARGET%.exe
if exist %TARGET%.obj del %TARGET%.obj
if exist random.obj del random.obj

c:\masm32\bin\ml /c /coff %SRC%
if errorlevel 1 echo "Error compile" & goto end
c:\masm32\bin\link /out:%TARGET%.exe /subsystem:windows *.obj
if errorlevel 1 echo "Error linking." & goto end
goto rrrr
:end
pause
:rrrr
