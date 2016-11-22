#include <windows.h> 
#include <tchar.h>
#include <ctime>
#include <math.h>
#include <atlimage.h> 
#include "resource.h"

#define WIN_CLASSNAME TEXT("Timer")
#define WIN_TITLENAME TEXT("Timer")
#define WIN_XPOS 0 
#define WIN_YPOS 0 
#define WIN_Width 800 
#define WIN_Height 600

#define Dlgtimer 1
#define Wintimer 2
#define XPivot 400
#define YPivot 300


enum Fucn
{
	NON, SIN, COS, TAN
};
enum FLAG
{
	wmove, hmove, stop
};

HINSTANCE g_hInst;
HWND g_hwnd;
int R, G, B, w, h;
int flag, f;

LPCTSTR lpszClass = WIN_CLASSNAME;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG Message;
	WNDCLASS WndClass; //����ü ����
	RECT rc = { 0, 0, WIN_Width, WIN_Height };
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_BORDER | WS_THICKFRAME;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0; // O/S ��� ���� �޸�(Class)
	WndClass.cbWndExtra = 0; // O/S ��� ���� �޸�(Window)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ�� ����
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //���������� WndClass.hIconSM : ����������
	WndClass.hInstance = hInstance; //���� ���α׷� ID
	WndClass.lpfnWndProc = (WNDPROC)WndProc; // ���ν��� �Լ���
	WndClass.lpszClassName = lpszClass; // Ŭ���� �̸�
	WndClass.lpszMenuName = NULL; // �޴� �̸�
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	AdjustWindowRect(&rc, dwStyle, FALSE);
	hwnd = CreateWindow( // �����찡 �����Ǹ� �ڵ�(hwnd)�� ��ȯ��
		lpszClass,	// ������ Ŭ���� �̸�
		lpszClass,	 // ������ Ÿ��Ʋ �̸�
		dwStyle,	 //������ ��Ÿ��
		WIN_XPOS,	// ������ ��ġ, x��ǥ
		WIN_YPOS,	// ������ ��ġ, y��ǥ
		rc.right - rc.left, // ������ ��
		rc.bottom - rc.top, // ������ ����
		NULL,		// �θ� ������ �ڵ�
		(HMENU)NULL, // �޴� �ڵ�
		hInstance,	 // ���� ���α׷� ID
		NULL);		// ������ ������ ����
	g_hwnd = hwnd;
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message); // Shift ��a�� -> �빮�� ��A��
		DispatchMessage(&Message); // WinMain -> WinProc
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc, bmpdc;
	HBITMAP memBit;
	PAINTSTRUCT ps;
	static RECT rc;
	srand((unsigned)time(NULL));

	switch (iMessage) {
	case WM_CREATE:
		GetWindowRect(hWnd, &rc);
		srand((unsigned)time(NULL));
		SetTimer(hWnd, 1, 60, NULL);
		SetTimer(hWnd, 2, 300, NULL);
		R = G = B = 0;
		flag = stop;
		f = NON;
		w = h = 0;
		break;
	case WM_LBUTTONDOWN:
		LOWORD(lParam);
		HIWORD(lParam);

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:

		break;
	case WM_LBUTTONUP:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG6_3), hWnd, (DLGPROC)DlgProc);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if (flag == wmove)
			{
				w++;
				if (w == 400) w = 0;
			}
			else if (flag == hmove)
			{
				h++;
				if (h == 200) h = 0;
			}
			break;
		case 2:
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		memBit = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		SelectObject(memdc, memBit);
		FillRect(memdc, &rc, WHITE_BRUSH);
		//

		MoveToEx(memdc, XPivot, rc.bottom, nullptr);
		LineTo(memdc, XPivot, 0);
		MoveToEx(memdc, 0, YPivot, nullptr);
		LineTo(memdc, rc.right, YPivot);

		//SetMapMode(memdc, MM_LOENGLISH);   // exchange coodinate
		//SetViewportOrgEx(memdc, 300, 300, NULL);  // exchange orgion
		
		if (f == SIN)
			for (int i = -400; i < 1200; i++)
			{
				int y = (int)(sin(i*3.14 / 180) * (100 - h)) ;
				SetPixel(memdc, i + w + 40, y + YPivot, RGB(R, G, B));
			}
		if (f == COS)
			for (int i = -400; i < 1200; i++)
			{
				int y = (int)(cos(i*3.14 / 180) * (100 - h));
				SetPixel(memdc, i + w + 40, y + YPivot, RGB(R, G, B));
			}
		if (f == TAN)
			for (int i = -400; i < 1200; i++)
			{
				int y = (int)(tan(i*3.14 / 180) * (100 - h));
				SetPixel(memdc, i + w + 40, y + YPivot, RGB(R, G, B));
			}

		// hdc�� ����
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, memdc, 0, 0, SRCCOPY);

		SelectObject(memdc, NULL);
		DeleteDC(memdc);
		DeleteObject(memBit);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYUP:
		break;
	case WM_CHAR:
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC dhdc, dmemdc;
	PAINTSTRUCT dps;
	static HBITMAP memBit;
	static RECT drc;

	switch (iMsg) {
	case WM_INITDIALOG:
		GetClientRect(hDlg, &drc);
		SetTimer(hDlg, Dlgtimer, 30, NULL);
		CheckRadioButton(hDlg, IDC_SIN, IDC_TAN, NULL);
		break;
	case WM_PAINT:
		dhdc = BeginPaint(hDlg, &dps);
		dmemdc = CreateCompatibleDC(dhdc);
		memBit = CreateCompatibleBitmap(dhdc, drc.right, drc.bottom);
		SelectObject(dmemdc, memBit);
		FillRect(dmemdc, &drc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		//

		// hdc�� ����
		BitBlt(dhdc, 0, 0, drc.right, drc.bottom, dmemdc, 0, 0, SRCCOPY);

		SelectObject(dmemdc, NULL);
		DeleteDC(dmemdc);
		DeleteObject(memBit);
		EndPaint(hDlg, &dps);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case Dlgtimer:

			break;
		}
		//InvalidateRect(g_hwnd, NULL, FALSE);
		InvalidateRect(hDlg, NULL, FALSE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_WMOVE:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				flag = wmove;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_HMOVE:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				flag = hmove;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_STOP:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				flag = stop;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_RESET:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				flag = stop;
				f = NON;
				w = h = 0;
				CheckRadioButton(hDlg, IDC_SIN, IDC_TAN, NULL);
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_EXIT:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				KillTimer(g_hwnd, 1);
				KillTimer(g_hwnd, 2);
				PostQuitMessage(0);
			}
			break;
		case IDC_SIN:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				f = SIN;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_COS:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				f = COS;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_TAN:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				f = TAN;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_RED:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				if (R) R = 0;
				else R = 255;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_GREEN:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				if (G) G = 0;
				else G = 255;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_BLUE:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				if (B) B = 0;
				else B = 255;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		}
		break;
	}
	return false;
}
/*
��Ʈ�� ����ϱ�
��ư
1: � �������� �̵�
2: � �� �Ǵ� �Ʒ��� �����̱�
3: ���߱�
4: ����
5: ���α׷�����

������ư
1. ���ΰ
2. �ڻ��ΰ
3. ź��Ʈ�׸���

üũ��ư (1���̻����̸� �� �ռ�)
1. ���� ���� ����
2. ���� ���� �ʷ�
3. ���� ���� �Ķ�
*/