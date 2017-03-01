// glscelet.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <gl\gl.h>

HINSTANCE	g_hInstance;
HWND		g_hWnd;
HDC			g_hDC;
HGLRC		g_hRC;

#define FPS_TIMER		1
#define FPS_INTERVAL	1000

/*	������� ������������� OpenGL ���������� �������������
	����� ���� ��� ���� ������� ���� � ���������
	�������� OpenGL. ���� ������� ��������� �� ����
	���������� ������������� ���������� */
int InitGL() {
	return 0;
}

int RenderGL() {
	return 0;
}


/* ===================================================================================
 *		��� ����� ������ ��������!
 * ===================================================================================
 */

/*	��� �� ��� ����� ��� ������ ���������.
	��� �������� ���� � �������� �������� OpenGL...	*/

/*	���� ������� ������...	*/
int ZoidError(char *str) {
	LPVOID lpMsgBuf;
 
	if(FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
		) == 0) 
	{
		MessageBox( NULL, "Error in Error! Have fun!", str, MB_OK|MB_ICONERROR);
		return -1;
	}
	// Display the string.
	MessageBox( NULL, (char *)lpMsgBuf, str, MB_OK|MB_ICONERROR);

	// Free the buffer.
	LocalFree( lpMsgBuf );
	return 0;
}

/*	�������� �����...	*/
int CleanAll() {
	UnregisterClass("opengl_app", g_hInstance);
	if(g_hRC != NULL) {
		wglMakeCurrent (NULL, NULL) ; 
		wglDeleteContext (g_hRC); 
	}
	return 0;
}

/*	������� ���������� ����	*/
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wPara, LPARAM lPara) {
	switch(uMsg) {
	case WM_QUIT:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_TIMER:
		if(wPara == FPS_TIMER) {
			RenderGL();
		}
		return 0;
	case WM_PAINT:
		RenderGL();
		return 0;
	default:
		return DefWindowProc(hWnd, uMsg, wPara, lPara);
	}
}

/*	Entry point...	*/
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	/*	������������� ���������� ����������...	*/
	g_hInstance = hInstance;
	/*	������������ ����� ����...	*/	
	WNDCLASS wnd = {CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
		WindowProc, 0L, 0L, hInstance, NULL, NULL, 
		(HBRUSH) GetStockObject(BLACK_BRUSH), NULL, "opengl_app" };
	if(RegisterClass(&wnd) == 0) {
		MessageBox(NULL, "Error: RegisterClass()!", "Error:", MB_ICONERROR);
		return -1;
	}

	/*	������ ����...	*/
	g_hWnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, 
		"opengl_app", "Sceleton", WS_OVERLAPPEDWINDOW | 
		WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, 300, 300, 
		NULL, NULL, hInstance, NULL);
	if(g_hWnd == NULL) {
		MessageBox(NULL, "Error: CreateWindow()!", "Error:", MB_ICONERROR);
		CleanAll();
		return -1;
	}

	/*	���������� ��������...	*/
	g_hDC = GetDC(g_hWnd);
	if(g_hDC == NULL) {
		MessageBox(NULL, "Error: GetDC()!", "Error:", MB_ICONERROR);
		CleanAll();
		return -1;
	}
 
	/*	��������� ��� OpenGL...	*/
	PIXELFORMATDESCRIPTOR pfd = {  
		sizeof(PIXELFORMATDESCRIPTOR),  //  size of this pfd  
		1,                     // version number 
		PFD_DRAW_TO_WINDOW |   // support window 
		PFD_SUPPORT_OPENGL |   // support OpenGL 
		PFD_DOUBLEBUFFER,      // double buffered 
		PFD_TYPE_RGBA,         // RGBA type 
		24,                    // 24-bit color depth 
		0, 0, 0, 0, 0, 0,      // color bits ignored 
		0,                     // no alpha buffer 
		0,                     // shift bit ignored 

		0,                     // no accumulation buffer 
		0, 0, 0, 0,            // accum bits ignored 
		32,                    // 32-bit z-buffer	 
		0,                     // no stencil buffer 
		0,                     // no auxiliary buffer 
		PFD_MAIN_PLANE,        // main layer 
		0,                     // reserved 
		0, 0, 0                // layer masks ignored 
    }; 

	int iPixelFormat = ChoosePixelFormat(g_hDC, &pfd);
	if(iPixelFormat == 0) {
		ZoidError("Error: ChoosePixelFormat()");
		CleanAll();
		return -1;
	}

	if(!SetPixelFormat(g_hDC, iPixelFormat, &pfd)) {
		MessageBox(NULL, "Error: SetPixelFormat()!", "Error:", MB_ICONERROR);
		CleanAll();
		return -1;
	}

	/*	Create OpenGL render context	*/
	g_hRC = wglCreateContext(g_hDC);
	if(g_hRC == NULL) {
		ZoidError("wglCreateContext()!");
		CleanAll();
		return -1;
	}

	if(!wglMakeCurrent(g_hDC, g_hRC)) {
		ZoidError("wglMakeCurrent()!");
		CleanAll();
		return -1;
	}

	/*	�� ���������������� ����� ��������� �������
		OpenGL � ��� ���� ��������...	
		������ ����� ��� ����� ��� ����!!!!!!!!!!!!!!	*/

	if(InitGL()) {
		CleanAll();
		return -1;
	}

	SetTimer(g_hWnd, FPS_TIMER, FPS_INTERVAL, NULL);

	/*	�������� ����	*/
	ShowWindow(g_hWnd, nCmdShow);
	SetForegroundWindow(g_hWnd);
	SetFocus(g_hWnd);
	/*	���� ������ ����	*/
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	KillTimer(g_hWnd, FPS_TIMER);
	CleanAll();
	return 0;
}



