/*
Лабораторная работа №8
Алексей Шапран 
Группа: ИУ8-14
*/
#include <windows.h>
#include <string.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szProgName[] = "Имя программы";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASS w;

	w.lpszClassName = szProgName;
	w.hInstance = hInstance; 
	w.lpfnWndProc = WndProc; 
	w.hCursor = LoadCursor(NULL, IDC_ARROW); 
	w.hIcon = 0;
	w.lpszMenuName = 0;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); 
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;
	
	if (!RegisterClass(&w))
		return 0;
	hWnd = CreateWindow(szProgName, 
		"Лабораторная работа №8 Вариант 23", 
		WS_OVERLAPPEDWINDOW, 
		50, 
		50, 
		1200, 
		500, 
		(HWND)NULL, 
		(HMENU)NULL, 
		(HINSTANCE)hInstance, 
		(HINSTANCE)NULL); 

					
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	
	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return(lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc; 
	PAINTSTRUCT ps; 
	LOGFONT lf;
	HFONT hFont;
	RECT r;
	HBRUSH hBrush;
	HPEN hPen;
	
	switch (messg)
	{
	case WM_MOUSEMOVE:
		static int x, y, x1, y1;
		
		if (wParam & MK_RBUTTON) 
		{
			hdc = GetDC(hWnd);
			x1 = LOWORD(lParam);
			y1 = HIWORD(lParam);
			x = x1 + 1;
			y = y1 + 1;
			hdc = GetDC(hWnd);
			hBrush = CreateHatchBrush(HS_CROSS, RGB(8, 114, 255));
			hPen = CreatePen(PS_DASHDOT, 1, RGB(255, 38, 77));
			SelectObject(hdc, hBrush);
			SelectObject(hdc, hPen);
			Ellipse(hdc, x1, y1, 0, 0);
			DeleteObject(hPen);
			DeleteObject(hBrush);
		}
		else if (wParam & MK_LBUTTON) InvalidateRect(hWnd, NULL, TRUE);
		
		break;

	case WM_DESTROY:
		PostQuitMessage(0); 
		break;

	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam));
	}
	return 0;
}
