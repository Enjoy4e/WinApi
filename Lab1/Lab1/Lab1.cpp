#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hWnd, // дескриптор окошка
						 UINT , // сообщение, посылаемое ОС
						 WPARAM	, // параметры
						 LPARAM ); // сообщений, для последующего обращения

TCHAR WinName[] = _T("Lab1");

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы, где хранится информация о нашем окне, указатель на определенную область памяти в ядре
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// струкутра отвечает за характеристики окна
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = CreateSolidBrush(RGB(38, 201, 255));// Заполнение окна цветом


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("Lab1"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}

bool Left = false, Right = false;
int times_cl_l = 0, times_cl_r = 0;
int x_koord = 0, y_koord = 0;
LRESULT CALLBACK WndProc(HWND hWnd,//Дескриптор окна
	UINT message,//Код сообщения
	WPARAM wParam,//Указатели, где хранится информация для сообщения
	LPARAM lParam)//Указатели, где хранится информация для сообщения
{
	switch (message)		 // Обработчик сообщений
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;// содержит информации для приложения. Эта информация может быть использована для окраски клиентской области окна, которым владеет приложение.
		HDC hdc = BeginPaint(hWnd, &ps);//Определяет контекст устройства дисплея, используемый для рисования
		if (Left == false && Right == false) {
			//Функция извлекает дескриптор одного из предопределенных перьев, кистей, шрифтов или палитр.
			SelectObject(hdc, GetStockObject(DC_PEN));
			//Цвет пера
			SetDCPenColor(hdc, RGB(38, 201, 255));
			//создает логическую кисть, которая имеет заданный сплошной тон.
			SelectObject(hdc, CreateSolidBrush(RGB(255, 251, 0)));
			Ellipse(hdc, 300, 300, 500, 500);
		}


		if (Left) {
			SelectObject(hdc, GetStockObject(DC_PEN));
			SelectObject(hdc, CreateSolidBrush(RGB(38, 201, 255)));
			if (times_cl_l * 10 + x_koord <= 450) {
				SetDCPenColor(hdc, RGB(38, 201, 255));
				Ellipse(hdc, x_koord, y_koord, 80 + x_koord, 80 + y_koord);
			}
			Left = false;
		}

		if (Right) {
			SelectObject(hdc, GetStockObject(DC_PEN));
			SelectObject(hdc, CreateSolidBrush(RGB(38, 201, 255)));
			if (times_cl_l * 10 + x_koord >= 390) {
				SetDCPenColor(hdc, RGB(38, 201, 255));
				Ellipse(hdc, x_koord, y_koord, 80 + x_koord, 80 + y_koord);
			}
			Right = false;
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		Left = true;
		x_koord = LOWORD(lParam);//Ширина
		y_koord = HIWORD(lParam);//Высота
		if (times_cl_l != 10) {
			++times_cl_l;
		}
		InvalidateRect(hWnd, NULL, false);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		Right = true;
		x_koord = LOWORD(lParam);
		y_koord = HIWORD(lParam);
		if (times_cl_r != 10) {
			++times_cl_r;
		}
		InvalidateRect(hWnd, NULL, false);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);//Если сообщение никак не обрабатывается
	}

	return 0;
}
