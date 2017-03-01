.386
.model flat,stdcall
option casemap:none

WinMain proto :DWORD,:DWORD,:DWORD,:DWORD
DrawGrid proto :DWORD
Random proto :DWORD


include c:\masm32\include\windows.inc
include c:\masm32\include\user32.inc
include c:\masm32\include\kernel32.inc
include c:\masm32\include\gdi32.inc
includelib c:\masm32\lib\user32.lib
includelib c:\masm32\lib\kernel32.lib
includelib c:\masm32\lib\gdi32.lib


.data
ClassName db "SuDoKuWinClass",0
AppName  db "SuDoKu v0.1",0
MouseClick db 0         ; 0=no click yet
WindowWidth dd 300	; window width and height.
WindowHeight dd 320
TimerInterval dd 500
hInstance HINSTANCE 0
hBrush HBRUSH 0
CommandLine LPSTR NULL

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
	;LOCAL trect:RECT

	.IF uMsg==WM_DESTROY
		invoke PostQuitMessage,NULL
		
	; отслеживаем нажатие клавиш клавиатуры.		
	.ELSEIF uMsg==WM_KEYDOWN
		.IF wParam==VK_UP
		.ELSEIF wParam==VK_DOWN
		.ELSEIF wParam==VK_LEFT
		.ELSEIF wParam==VK_RIGHT
		.ELSEIF wParam==VK_ADD
		.ELSEIF wParam==VK_SUBTRACT
		.ELSEIF wParam==VK_A
		.ELSEIF wParam==VK_S
		.ENDIF
		
	.ELSEIF uMsg==WM_MOUSEMOVE
		
		
		
	; прорисовка экрана.
	.ELSEIF uMsg==WM_PAINT
		invoke	DrawGrid, hWnd
	; функция таймера.
	.ELSEIF uMsg==WM_TIMER
		invoke InvalidateRect, hWnd, NULL, TRUE
	.ELSE
		invoke DefWindowProc,hWnd,uMsg,wParam,lParam
		ret
	.ENDIF
	xor    eax,eax
	ret
WndProc endp

DrawGrid proc hWnd:HWND
	LOCAL	tpoint: POINT	
	LOCAL	hPen: HGDIOBJ
	LOCAL	hdc:HDC
	LOCAL	ps:PAINTSTRUCT

	invoke BeginPaint,hWnd, ADDR ps
	mov    hdc,eax
		
	invoke CreatePen, PS_SOLID, 2, 0ff0000h
	mov hPen, eax
	invoke SelectObject, hdc, hPen
		
	invoke MoveToEx, hdc, 10, 10, ADDR tpoint
	invoke LineTo, hdc, 280, 10
	invoke LineTo, hdc, 280, 280
	invoke LineTo, hdc, 10, 280
	invoke LineTo, hdc, 10, 10
		
	invoke MoveToEx, hdc, 10, 100, ADDR tpoint
	invoke LineTo, hdc, 280, 100
			
	invoke MoveToEx, hdc, 10, 190, ADDR tpoint
	invoke LineTo, hdc, 280, 190
		
	invoke MoveToEx, hdc, 100, 10, ADDR tpoint
	invoke LineTo, hdc, 100, 280
		
	invoke MoveToEx, hdc, 190, 10, ADDR tpoint
	invoke LineTo, hdc, 190, 280	
		
	invoke DeleteObject, hPen	
		
	invoke CreatePen, PS_DOT, 1, 0ff0000h
	mov hPen, eax
	invoke SelectObject, hdc, hPen
		
	invoke MoveToEx, hdc, 40, 10, ADDR tpoint
	invoke LineTo, hdc, 40, 280		
				
	invoke MoveToEx, hdc, 70, 10, ADDR tpoint
	invoke LineTo, hdc, 70, 280	
		
	invoke MoveToEx, hdc, 130, 10, ADDR tpoint
	invoke LineTo, hdc, 130, 280	
			
	invoke MoveToEx, hdc, 160, 10, ADDR tpoint
	invoke LineTo, hdc, 160, 280	

	invoke MoveToEx, hdc, 220, 10, ADDR tpoint
	invoke LineTo, hdc, 220, 280		
			
	invoke MoveToEx, hdc, 250, 10, ADDR tpoint
	invoke LineTo, hdc, 250, 280
		
	invoke MoveToEx, hdc, 10, 40, ADDR tpoint
	invoke LineTo, hdc, 280, 40
		
	invoke MoveToEx, hdc, 10, 70, ADDR tpoint
	invoke LineTo, hdc, 280, 70		
				
	invoke MoveToEx, hdc, 10, 130, ADDR tpoint
	invoke LineTo, hdc, 280, 130		
				
	invoke MoveToEx, hdc, 10, 160, ADDR tpoint
	invoke LineTo, hdc, 280, 160		
					
	invoke MoveToEx, hdc, 10, 220, ADDR tpoint
	invoke LineTo, hdc, 280, 220
		
	invoke MoveToEx, hdc, 10, 250, ADDR tpoint
	invoke LineTo, hdc, 280, 250

	invoke DeleteObject, hPen
	invoke EndPaint,hWnd, ADDR ps

	ret
DrawGrid	endp


end start
