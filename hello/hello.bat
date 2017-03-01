@echo off


c:\MASM32\BIN\Ml.exe /c /Zi /coff hello.asm
if errorlevel 1 goto errasm

: -----------------------
: link the main OBJ file
: -----------------------
c:\MASM32\BIN\Link.exe /SUBSYSTEM:WINDOWS /DEBUG /DEBUGTYPE:CV /PDB:NONE hello.obj
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
