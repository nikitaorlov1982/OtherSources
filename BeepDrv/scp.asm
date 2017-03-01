.386
.model flat, stdcall
option casemap: none

include \masm32\include\windows.inc
include \masm32\include\kernel32.inc
include \masm32\include\user32.inc
include \masm32\include\advapi32.inc
include \masm32\macros\macros.asm

includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\user32.lib
includelib \masm32\lib\advapi32.lib

.code

Start	proc
	LOCAL	hSCManager		:HANDLE
	LOCAL	hService		:HANDLE
	LOCAL	drvPathName[MAX_PATH]	:CHAR
	
	; Open SCM database.
	invoke	OpenSCManager, NULL, NULL, SC_MANAGER_CREATE_SERVICE
	.if	eax == NULL
		invoke	MessageBox, NULL, SADD("Error: Can't connect to SCM manager!"), \
			SADD("Fatal:"), MB_ICONERROR
		mov	eax, -1
		ret
	.endif	
	mov	hSCManager, eax
	
	push	eax
	invoke	GetFullPathName, SADD("beeper.sys"), sizeof drvPathName, \
		ADDR drvPathName, esp
	pop	eax
	
	; Create new service.
	invoke	CreateService, hSCManager, SADD("Beeper"), SADD("Nice melody beeper."), \
		SERVICE_START + DELETE, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, \
		SERVICE_ERROR_NORMAL, ADDR drvPathName, NULL, NULL, NULL, NULL, NULL
	.if	eax == NULL
		invoke	MessageBox, NULL, SADD("Error: Can't create new Service!"), \
			SADD("Fatal:"), MB_ICONERROR
		invoke	CloseServiceHandle, hSCManager
		mov	eax, -1
		ret
	.endif
	mov	hService, eax
	
	invoke	StartService, hService, 0, NULL

	invoke	DeleteService, hService
	invoke	CloseServiceHandle, hService
	invoke	CloseServiceHandle, hSCManager	
	
	mov	eax, 0
	ret
Start	endp

	end	Start
		

