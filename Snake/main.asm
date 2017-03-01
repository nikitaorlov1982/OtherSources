.386
.model flat,stdcall
option casemap:none

WinMain proto :DWORD,:DWORD,:DWORD,:DWORD
Random proto :DWORD

include c:\masm32\include\windows.inc
include c:\masm32\include\user32.inc
include c:\masm32\include\kernel32.inc
include c:\masm32\include\gdi32.inc
includelib c:\masm32\lib\user32.lib
includelib c:\masm32\lib\kernel32.lib
includelib c:\masm32\lib\gdi32.lib


.data
ClassName db "SnakeWinClass",0
AppName  db "Snake v0.1",0
MouseClick db 0         ; 0=no click yet
WindowWidth dd CW_USEDEFAULT	; window width and height.
WindowHeight dd CW_USEDEFAULT
TimerInterval dd 500
hInstance HINSTANCE 0
hBrush HBRUSH 0
CommandLine LPSTR NULL
numpoints dd 5	; длина змейки.
spoint POINT 10 dup(<100,100>,<80,100>,<60,100>,<40,100>,<20,100>) 
vel POINT <20,0> ; скорость змейки.
tpoint POINT <0,0> ; временная переменная.
addPoint db FALSE ; змейка растет.

.code
start:
	invoke GetModuleHandle, NULL
	mov    hInstance,eax
	invoke GetCommandLine
	invoke WinMain, hInstance,NULL,CommandLine, SW_SHOWDEFAULT
	invoke ExitProcess,eax
WinMain proc hInst:HINSTANCE,hPrevInst:HINSTANCE,CmdLine:LPSTR,CmdShow:DWORD
	LOCAL wc:WNDCLASSEX
	LOCAL msg:MSG
	LOCAL hwnd:HWND
	LOCAL color:DWORD
	
	; создаём класс окна.
	mov   wc.cbSize,SIZEOF WNDCLASSEX
	mov   wc.style, CS_HREDRAW or CS_VREDRAW
	mov   wc.lpfnWndProc, OFFSET WndProc
	mov   wc.cbClsExtra,NULL
	mov   wc.cbWndExtra,NULL
	nop
	nop
	push  hInst
	pop   wc.hInstance
	mov   wc.hbrBackground,COLOR_WINDOW+1
	mov   wc.lpszMenuName,NULL
	mov   wc.lpszClassName,OFFSET ClassName
	invoke LoadIcon,NULL,IDI_APPLICATION
	mov   wc.hIcon,eax
	mov   wc.hIconSm,eax
	invoke LoadCursor,NULL,IDC_ARROW
	mov   wc.hCursor,eax
	invoke RegisterClassEx, addr wc
	
	; создаём окно с определёнными параметрами.
	INVOKE CreateWindowEx,NULL,ADDR ClassName,ADDR AppName,\
           WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
           CW_USEDEFAULT,WindowWidth,WindowHeight,NULL,NULL,\
           hInst,NULL           
	mov   hwnd,eax
	
	; определяем цвет прорисовки.
	mov color, 0000FF00h	; 00bbggrr
	invoke CreateSolidBrush, color
	mov hBrush, eax
	
	; создаём таймер.
	invoke SetTimer, hwnd, 0, TimerInterval, NULL 
	
	INVOKE ShowWindow, hwnd,SW_SHOWNORMAL
	INVOKE UpdateWindow, hwnd
	.WHILE TRUE
                INVOKE GetMessage, ADDR msg,NULL,0,0
                .BREAK .IF (!eax)
                INVOKE DispatchMessage, ADDR msg
	.ENDW
	mov     eax,msg.wParam
	ret
WinMain endp



WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
	LOCAL hdc:HDC
	LOCAL ps:PAINTSTRUCT
	LOCAL trect:RECT

	.IF uMsg==WM_DESTROY
		invoke PostQuitMessage,NULL
		
	; отслеживаем нажатие клавиш клавиатуры.		
	.ELSEIF uMsg==WM_KEYDOWN
		.IF wParam==VK_UP
			mov vel.y, -20
			mov vel.x, 0
		.ELSEIF wParam==VK_DOWN
			mov vel.y, 20
			mov vel.x, 0
		.ELSEIF wParam==VK_LEFT
			mov vel.x, -20
			mov vel.y, 0
		.ELSEIF wParam==VK_RIGHT
			mov vel.x, 20
			mov vel.y, 0
		.ELSEIF wParam==VK_ADD
			sub TimerInterval, 100
			invoke SetTimer, hWnd, 0, TimerInterval, NULL
		.ELSEIF wParam==VK_SUBTRACT
			add TimerInterval, 100			
			invoke SetTimer, hWnd, 0, TimerInterval, NULL
		.ELSEIF wParam==VK_A
			dec numpoints
		.ELSEIF wParam==VK_S
			mov addPoint, TRUE
		.ENDIF
		
	; прорисовка экрана.
	.ELSEIF uMsg==WM_PAINT
		invoke BeginPaint,hWnd, ADDR ps
		mov    hdc,eax
		
		; начинаем рисовать отсюда.
		mov ecx, numpoints
		lea edx, spoint
		ASSUME edx: PTR POINT		
		again:
			mov eax, [edx].x
			sub eax, 10			
			mov trect.left, eax
			mov eax, [edx].y
			sub eax, 10
			mov trect.top, eax
			mov eax, [edx].x
			add eax, 10
			mov trect.right, eax
			mov eax, [edx].y
			add eax, 10
			mov trect.bottom, eax	
			push ecx
			push edx	
			invoke FillRect, hdc, ADDR trect, hBrush
			pop edx
			pop ecx
			add edx, SIZEOF POINT
			loop again
		ASSUME edx: NOTHING		
			
		invoke EndPaint,hWnd, ADDR ps
		
	; функция таймера.
	.ELSEIF uMsg==WM_TIMER
		mov ecx, numpoints		
		lea edx, spoint	; начало змейки.
		ASSUME edx: PTR POINT ; адрес указывает на начало структуры.
		
		; двигаем сначало голову.
		mov eax, [edx].x
		; сохраняем старое значение координаты X.
		mov tpoint.x, eax		
		add eax, vel.x		
		mov [edx].x, eax
		
		mov eax, [edx].y
		mov tpoint.y, eax
		add eax, vel.y
		mov [edx].y, eax
		
		; проверяем есть ли у головы хвост.
		dec ecx		
		jz done_move
		
		
		; двигаем хвост.
		add edx, sizeof POINT
		again_move:
			push [edx].x
			push tpoint.x
			pop [edx].x
			pop tpoint.x
			
			push [edx].y
			push tpoint.y
			pop [edx].y
			pop tpoint.y
		
			add edx, sizeof POINT
			loop again_move
		 
		done_move:
		
		; хвост расёт.
		.IF addPoint 
			inc numpoints
			add edx, sizeof POINT
			mov eax, tpoint.x
			mov [edx].x, eax
			mov eax, tpoint.y
			mov [edx].y, eax
			mov addPoint, FALSE
			invoke Random, 0					
		.ENDIF
		
		assume edx: NOTHING
		invoke InvalidateRect, hWnd, NULL, TRUE
	.ELSE
		invoke DefWindowProc,hWnd,uMsg,wParam,lParam
		ret
	.ENDIF
	xor    eax,eax
	ret
WndProc endp
end start
