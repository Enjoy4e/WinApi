#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("Lab1");

int WINAPI _tWinMain(HINSTANCE This,		 // ���������� �������� ���������� 
	HINSTANCE Prev, 	// � ����������� �������� ������ 0 
	LPTSTR cmd, 		// ��������� ������ 
	int mode) 		// ����� ����������� ����
{
	HWND hWnd;		// ���������� �������� ���� ��������� 
	MSG msg; 		// ��������� ��� �������� ��������� 
	WNDCLASS wc; 	// ����� ����
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// ��� ������ ���� 
	wc.lpfnWndProc = WndProc; 					// ������� ���� 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// ����� ���� 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// ����������� ������ 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// ����������� ������ 
	wc.lpszMenuName = NULL; 					// ��� ���� 
	wc.cbClsExtra = 0; 						// ��� �������������� ������ ������ 
	wc.cbWndExtra = 0; 						// ��� �������������� ������ ���� 
	wc.hbrBackground = CreateSolidBrush(RGB(38, 201, 255));// ���������� ���� ������


	// ����������� ������ ����
	if (!RegisterClass(&wc)) return 0;

	// �������� ���� 
	hWnd = CreateWindow(WinName,			// ��� ������ ���� 
		_T("Lab1"), 		// ��������� ���� 
		WS_OVERLAPPEDWINDOW, 		// ����� ���� 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 ������� ���� 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// ���������� ������������� ���� 
		NULL, 						// ��� ���� 
		This, 						// ���������� ���������� 
		NULL); 					// �������������� ���������� ��� 

	ShowWindow(hWnd, mode); 				// �������� ����

	// ���� ��������� ��������� 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// ������� ���������� ����� ������� ������� 
		DispatchMessage(&msg); 		// �������� ��������� ������� WndProc() 
	}
	return 0;
}

bool Left = false, Right = false;
int times_cl_l = 0, times_cl_r = 0;
int x_koord = 0, y_koord = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)		 // ���������� ���������
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		if (Left == false && Right == false) {
			SelectObject(hdc, GetStockObject(DC_PEN));
			SetDCPenColor(hdc, RGB(38, 201, 255));
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
		x_koord = LOWORD(lParam);
		y_koord = HIWORD(lParam);
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
		break; 			// ���������� ��������� 
	default: 			// ��������� ��������� �� ��������� 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
