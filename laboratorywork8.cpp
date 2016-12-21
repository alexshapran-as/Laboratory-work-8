/*
Лабораторная работа №8
Алексей Шапран 
Группа: ИУ8-14
*/
#include<windows.h>
#include<string.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szProgName[] = "Имя программы";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASS w;

	w.lpszClassName = szProgName; //имя программы - объявлено выше
	w.hInstance = hInstance; //идентификатор текущего приложения
	w.lpfnWndProc = WndProc; //указатель на функцию окна
	w.hCursor = LoadCursor(NULL, IDC_ARROW); //загружаем курсор
	w.hIcon = 0;
	w.lpszMenuName = 0;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //цвет фона окна
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;

	//Если не удалось зарегистрировать класс окна - выходим
	if (!RegisterClass(&w))
		return 0;
	//Создадим окно в памяти, заполнив аргументы CreateWindow
	hWnd = CreateWindow(szProgName, //Имя программы
		"Лабораторная работа №8 Вариант 23", //Заголовок окна
		WS_OVERLAPPEDWINDOW, //Стиль окна - перекрывающееся
		100, //положение окна на экране по х
		100, //положение по у
		500, //ширина
		300, //высота
		(HWND)NULL, //идентификатор родительского окна
		(HMENU)NULL, //идентификатор меню
		(HINSTANCE)hInstance, //идентификатор экземпляра программы
		(HINSTANCE)NULL); //отсутствие дополнительных параметров

						  //Выводим окно из памяти на экран
	ShowWindow(hWnd, nCmdShow);
	//Обновим содержимое окна
	UpdateWindow(hWnd);

	//Цикл обработки сообщений

	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return(lpMsg.wParam);
}

//Функция окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc; //создаём контекст устройства
	PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода
	LOGFONT lf;
	HFONT hFont;
	RECT r;
	HBRUSH hBrush;
	HPEN hPen;

	//Цикл обработки сообщений
	switch (messg)
	{
		//сообщение рисования
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//рисуем овал
		hBrush = CreateHatchBrush(HS_CROSS, RGB(8, 114, 255));
		hPen = CreatePen(PS_DASHDOT, 1, RGB(255, 38, 77));
		SelectObject(hdc, hBrush);
		SelectObject(hdc, hPen);
		Ellipse(hdc, 20, 100, 200, 200);
		ValidateRect(hWnd, NULL);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		if (wParam & MK_RBUTTON) // Нажата правая клавиша
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


		//сообщение выхода - разрушение окна
	case WM_DESTROY:
		PostQuitMessage(0); //Посылаем сообщение выхода с кодом 0 - нормальное завершение
		//DeleteObject(hPen);
		//DeleteObject(hBrush);
		break;

	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
	}
	return 0;
}
