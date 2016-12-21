#include<windows.h>
#include<string.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szProgName[] = "��� ���������";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASS w;

	w.lpszClassName = szProgName; //��� ��������� - ��������� ����
	w.hInstance = hInstance; //������������� �������� ����������
	w.lpfnWndProc = WndProc; //��������� �� ������� ����
	w.hCursor = LoadCursor(NULL, IDC_ARROW); //��������� ������
	w.hIcon = 0;
	w.lpszMenuName = 0;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //���� ���� ����
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;

	//���� �� ������� ���������������� ����� ���� - �������
	if (!RegisterClass(&w))
		return 0;
	//�������� ���� � ������, �������� ��������� CreateWindow
	hWnd = CreateWindow(szProgName, //��� ���������
		"������������ ������ �8 ������� 23", //��������� ����
		WS_OVERLAPPEDWINDOW, //����� ���� - ���������������
		100, //��������� ���� �� ������ �� �
		100, //��������� �� �
		500, //������
		300, //������
		(HWND)NULL, //������������� ������������� ����
		(HMENU)NULL, //������������� ����
		(HINSTANCE)hInstance, //������������� ���������� ���������
		(HINSTANCE)NULL); //���������� �������������� ����������

						  //������� ���� �� ������ �� �����
	ShowWindow(hWnd, nCmdShow);
	//������� ���������� ����
	UpdateWindow(hWnd);

	//���� ��������� ���������

	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return(lpMsg.wParam);
}

//������� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc; //������ �������� ����������
	PAINTSTRUCT ps; //������ ��������� ��������� ������������ ������
	LOGFONT lf;
	HFONT hFont;
	RECT r;
	HBRUSH hBrush;
	HPEN hPen;

	//���� ��������� ���������
	switch (messg)
	{
		//��������� ���������
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//������ ����
		hBrush = CreateHatchBrush(HS_CROSS, RGB(8, 114, 255));
		hPen = CreatePen(PS_DASHDOT, 1, RGB(255, 38, 77));
		SelectObject(hdc, hBrush);
		SelectObject(hdc, hPen);
		Ellipse(hdc, 20, 100, 200, 200);
		ValidateRect(hWnd, NULL);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		if (wParam & MK_RBUTTON) // ������ ������ �������
		{
			int x, y;
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			hdc = GetDC(hWnd);
			HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 66, 148));
			HBRUSH br = CreateSolidBrush(RGB(0, 243, 255));
			SelectObject(hdc, pen);
			SelectObject(hdc, br);
			Ellipse(hdc, x - 10, y - 10, x + 10, y + 10);
			DeleteObject(pen);
			DeleteObject(br);
			ReleaseDC(hWnd, hdc);
		}


		break;


		//��������� ������ - ���������� ����
	case WM_DESTROY:
		PostQuitMessage(0); //�������� ��������� ������ � ����� 0 - ���������� ����������
		//DeleteObject(hPen);
		//DeleteObject(hBrush);
		break;

	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam)); //����������� ������� ���������� �� �������������
	}
	return 0;
}