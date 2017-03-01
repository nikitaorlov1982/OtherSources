@echo off

if exist beeper.sys del beeper.sys
if exist beeper.obj del beeper.obj

\MASM32\BIN\Ml.exe /c /coff beeper.asm
if errorlevel 1 goto errasm

: -----------------------
: link the main OBJ file
: -----------------------
\MASM32\BIN\Link.exe /driver /base:0x10000 /align:32 /out:beeper.sys /SUBSYSTEM:NATIVE beeper.obj
if errorlevel 1 goto errlink
goto TheEnd

:errlink
: ----------------------------------------------------
: display message if there is an error during linking
: ----------------------------------------------------
echo.
echo There has been an error while linking this file.
echo.
goto TheEnd

:errasm
: -----------------------------------------------------
: display message if there is an error during assembly
: -----------------------------------------------------
echo.
echo There has been an error while assembling this file.
echo.
goto TheEnd

:TheEnd

pause
