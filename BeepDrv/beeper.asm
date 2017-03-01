.386
.model flat, stdcall
option casemap:none

include \masm32\include\w2k\ntstatus.inc
include \masm32\include\w2k\ntddk.inc
include \masm32\include\w2k\hal.inc
include \masm32\include\w2k\ntoskrnl.inc


includelib \masm32\lib\w2k\hal.lib


TIMER_FREQ	equ	1193167
OCTAVE		equ	2

PITCH_C		equ	523
PITCH_Cs	equ	554
PITCH_D		equ	587
PITCH_Ds	equ	622
PITCH_E		equ	659
PITCH_F		equ	698
PITCH_Fs	equ	740
PITCH_G		equ	784
PITCH_Gs	equ	831
PITCH_A		equ	880
PITCH_As	equ	988
PITCH_H		equ	1047

TONE_1		equ	TIMER_FREQ / (PITCH_C)
TONE_2		equ	TIMER_FREQ / (PITCH_Cs)
TONE_3		equ	TIMER_FREQ / (PITCH_D)
TONE_4		equ	TIMER_FREQ / (PITCH_Ds)
TONE_5		equ	TIMER_FREQ / (PITCH_E)
TONE_6		equ	TIMER_FREQ / (PITCH_F)
TONE_7		equ	TIMER_FREQ / (PITCH_Fs)
TONE_8		equ	TIMER_FREQ / (PITCH_G)
TONE_9		equ	TIMER_FREQ / (PITCH_Gs)
TONE_A		equ	TIMER_FREQ / (PITCH_A)
TONE_B		equ	TIMER_FREQ / (PITCH_As)
TONE_C		equ	TIMER_FREQ / (PITCH_H)




DELAY		equ	2000000h

DO_DELAY	MACRO
	mov	eax, DELAY
	.while	eax
		dec	eax
	.endw
ENDM


.code


MakeBeep	proc	uses ecx	dwPitch:DWORD, dwDuration:DWORD
	cli
	mov	al, 10110110b	; select timer 2, write LSB first then MSB, 
				; mode 3 (Square wave mode)
				; binary counter.
	
	out	43h, al		; write CWD (Control Word).
	mov	eax, dwPitch	; 
	out	42h, al		; write LSByte to timer 2.
	mov	al, ah
	out	42h, al		; write MSByte to timer 2.
	in	al, 61h
	or	al, 00000011b	; timer 2 enable, enable timer 2 output to drive SPKR pin.
	out	61h, al		; write to Misc Function and Speacer Conrol reg.
	sti
	
	mov	ecx, dwDuration
	
	.while	ecx
		dec	ecx
		DO_DELAY
	.endw
	
	cli
	in	al, 61h
	and	al, 11111100b
	out	61h, al
	sti
	ret
MakeBeep	endp

PlayMuzon	proc
	invoke	MakeBeep, TONE_1, 8
	invoke	MakeBeep, TONE_2, 8
	invoke	MakeBeep, TONE_3, 8
	invoke	MakeBeep, TONE_4, 8
	invoke	MakeBeep, TONE_5, 8
	invoke	MakeBeep, TONE_6, 8
	invoke	MakeBeep, TONE_7, 8
	invoke	MakeBeep, TONE_8, 8
	invoke	MakeBeep, TONE_9, 8
	invoke	MakeBeep, TONE_A, 8
	invoke	MakeBeep, TONE_B, 8
	invoke	MakeBeep, TONE_C, 8
	ret
PlayMuzon	endp



DriverEntry	proc	pDriverObject:PDRIVER_OBJECT, pusRegistryPath:PUNICODE_STRING

	invoke	PlayMuzon
	mov	eax, STATUS_DEVICE_CONFIGURATION_ERROR
	ret
DriverEntry	endp



	end DriverEntry
	
