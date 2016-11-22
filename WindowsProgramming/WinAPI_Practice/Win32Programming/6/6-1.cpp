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
#define Size 30

enum RGB {
	G = 0, R = 1, Y = 2, RAND = 3
};
enum Shape {
	rectangle, ellipse
};

HINSTANCE g_hInst;
HWND g_hwnd;
bool DlgBound, WinBound, shape;
LPCTSTR lpszClass = WIN_CLASSNAME;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG Message;
	WNDCLASS WndClass; //구조체 정의
	RECT rc = { 0, 0, WIN_Width, WIN_Height };
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_BORDER | WS_THICKFRAME;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0; // O/S 사용 여분 메모리(Class)
	WndClass.cbWndExtra = 0; // O/S 사용 여분 메모리(Window)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서 유형
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //아이콘유형 WndClass.hIconSM : 작은아이콘
	WndClass.hInstance = hInstance; //응용 프로그램 ID
	WndClass.lpfnWndProc = (WNDPROC)WndProc; // 프로시저 함수명
	WndClass.lpszClassName = lpszClass; // 클래스 이름
	WndClass.lpszMenuName = NULL; // 메뉴 이름
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	AdjustWindowRect(&rc, dwStyle, FALSE);
	hwnd = CreateWindow( // 윈도우가 생성되면 핸들(hwnd)이 반환됨
		lpszClass,	// 윈도우 클래스 이름
		lpszClass,	 // 윈도우 타이틀 이름
		dwStyle,	 //윈도우 스타일
		WIN_XPOS,	// 윈도우 위치, x좌표
		WIN_YPOS,	// 윈도우 위치, y좌표
		rc.right - rc.left, // 윈도우 폭
		rc.bottom - rc.top, // 윈도우 높이
		NULL,		// 부모 윈도우 핸들
		(HMENU)NULL, // 메뉴 핸들
		hInstance,	 // 응용 프로그램 ID
		NULL);		// 생성된 윈도우 정보
	g_hwnd = hwnd;
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message); // Shift ‘a’ -> 대문자 ‘A’
		DispatchMessage(&Message); // WinMain -> WinProc
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc;
	PAINTSTRUCT ps;
	static HBITMAP memBit;
	static RECT rc;
	static RECT draw;
	static int x, y;

	switch (iMessage) {
	case WM_CREATE:
		GetClientRect(hWnd, &rc);
		srand((unsigned)time(NULL));
		SetTimer(hWnd, Wintimer, 30, NULL);
		draw = { 0, 0, Size, Size };
		x = y = 5;
		WinBound = false;
		shape = rectangle;
		break;
	case WM_LBUTTONDOWN:
		
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
		
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG6_1), hWnd, (DLGPROC)DlgProc);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case Wintimer:
			if (WinBound) 
				OffsetRect(&draw, x, y);
			if (rc.right < draw.right) x = -x;
			else if (rc.left > draw.left) x = -x;
			else if (rc.top > draw.top) y = -y;
			else if (rc.bottom < draw.bottom) y = -y;
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		memBit = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		SelectObject(memdc, memBit);
		FillRect(memdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		//
		switch (shape)
		{
		case rectangle:
			Rectangle(memdc, draw.left, draw.top, draw.right, draw.bottom);
			break;
		case ellipse:
			Ellipse(memdc, draw.left, draw.top, draw.right, draw.bottom);
			break;
		}
	
		// hdc에 복사
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, memdc, 0, 0, SRCCOPY);

		SelectObject(memdc, NULL);
		DeleteDC(memdc);
		DeleteObject(memBit);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		break;
		switch (LOWORD(wParam)) {
		break;
		}
		break;
	case WM_CHAR:
		break;
	case WM_DESTROY:
		KillTimer(g_hwnd, Wintimer);
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
	static RECT ddraw;
	static int x, y;

	switch (iMsg) {
	case WM_INITDIALOG:
		GetClientRect(g_hwnd, &drc);
		SetTimer(hDlg, Dlgtimer, 30, NULL);
		CheckRadioButton(hDlg, IDC_ELLIPSE, IDC_RECTANGLE, IDC_RECTANGLE);
		ddraw = { 0, 0, Size, Size };
		x = y = 5;
		DlgBound = false;
		break;
	case WM_PAINT:
		dhdc = BeginPaint(hDlg, &dps);
		dmemdc = CreateCompatibleDC(dhdc);
		memBit = CreateCompatibleBitmap(dhdc, drc.right, drc.bottom);
		SelectObject(dmemdc, memBit);
		FillRect(dmemdc, &drc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		
		switch (shape)
		{
		case rectangle:
			Rectangle(dmemdc, ddraw.left, ddraw.top, ddraw.right, ddraw.bottom);
			break;
		case ellipse:
			Ellipse(dmemdc, ddraw.left, ddraw.top, ddraw.right, ddraw.bottom);
			break;
		}
		// hdc에 복사
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
			if(DlgBound)
				OffsetRect(&ddraw, x, y);
			if (300 < ddraw.right) x = -x;
			else if(drc.left > ddraw.left) x = -x;
			else if (drc.top > ddraw.top) y = -y;
			else if(250 < ddraw.bottom) y = -y;
			break;
		}
		InvalidateRect(g_hwnd, NULL, FALSE);
		InvalidateRect(hDlg, NULL, FALSE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BOUND_DLG:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				DlgBound = true;
			}
			InvalidateRect(hDlg, NULL, FALSE);
			break;
		case IDC_STOP_DLG:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				DlgBound = false;
			}
			InvalidateRect(hDlg, NULL, FALSE);
			break;
		case IDC_EXIT_DLG:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				KillTimer(hDlg, Dlgtimer);
				EndDialog(hDlg, 0);
			}
			break;
		case IDC_BOUND_WIN:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				WinBound = true;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_STOP_WIN:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				WinBound = false;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_EXIT:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				KillTimer(g_hwnd, Wintimer);
				KillTimer(hDlg, Dlgtimer);
				PostQuitMessage(0);
			}
			break;
		case IDC_RECTANGLE:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				shape = rectangle;
			}
			InvalidateRect(hDlg, NULL, FALSE);
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_ELLIPSE:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				shape = ellipse;
			}
			InvalidateRect(hDlg, NULL, FALSE);
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		}
		break;
	}
	return false;
}