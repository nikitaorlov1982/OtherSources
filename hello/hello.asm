.486
.model flat, stdcall
option casemap: none

include c:\masm32\include\windows.inc
include c:\masm32\include\user32.inc
include c:\masm32\include\kernel32.inc

includelib c:\masm32\lib\user32.lib
includelib c:\masm32\lib\kernel32.lib

.data
	mess db "Hello World!.", 0
	capp db "Message:", 0

.code
EntryPoint	proc
	invoke	MessageBox, 0, ADDR mess, ADDR capp, MB_OK
	ret
EntryPoint	endp

	end EntryPoint
	
