#include <windows.h> 
#include <tchar.h>
#include <ctime>
#include <math.h>
#include <atlimage.h> 
#include "resource.h"

#define WIN_FRAMECLASSNAME TEXT("FrameWindow")
#define WIN_CHILDCLASSNAME TEXT("ChildWindow")
#define WIN_TITLENAME TEXT("MDI")
#define WIN_XPOS 0 
#define WIN_YPOS 0 
#define WIN_Width 800 
#define WIN_Height 600

#define Dlgtimer 1
#define Wintimer 2

#define BUTTON_SIZE 25
#define IDC_REV_MOVE_BUTTON 100
#define IDC_EXIT_BUTTON 101
#define ID_CSIZE_SMALL 40001
#define ID_CSIZE_MIDDLE 40002
#define ID_CSIZE_BIG 40003
#define ID_ESPEED1 40004
#define ID_ESPEED2 40005

HINSTANCE g_hInst;
HWND g_hwnd;
HWND hwndChild;

HWND hButton[2], hRButton[3], espeed1, espeed2;
bool move;
double speed1, speed2, TempPos;
int idx, size;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG Message;
	WNDCLASS WndClass; //구조체 정의
	RECT rc = { 0, 0, WIN_Width, WIN_Height };
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX |
		WS_BORDER | WS_MAXIMIZEBOX; //WS_HSCROLL | WS_VSCROLL | WS_THICKFRAME
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0; // O/S 사용 여분 메모리(Class)
	WndClass.cbWndExtra = 0; // O/S 사용 여분 메모리(Window)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서 유형
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //아이콘유형 WndClass.hIconSM : 작은아이콘
	WndClass.lpfnWndProc = WndProc; // 프로시저 함수명
	WndClass.hInstance = hInstance; //응용 프로그램 ID
	WndClass.lpszClassName = WIN_FRAMECLASSNAME; // 클래스 이름
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU7_1); // 메뉴 이름
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = ChildWndProc; // 프로시저 함수명
	WndClass.lpszClassName = WIN_CHILDCLASSNAME; // 클래스 이름

	RegisterClass(&WndClass);

	AdjustWindowRect(&rc, dwStyle, FALSE);
	hwnd = CreateWindow( // 윈도우가 생성되면 핸들(hwnd)이 반환됨
		WIN_FRAMECLASSNAME,	// 윈도우 클래스 이름
		WIN_TITLENAME,	 // 윈도우 타이틀 이름
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
	static HWND hwndClient; // 클라이언트 윈도우
	CLIENTCREATESTRUCT clientcreate; // 차일드 생성을 관리하기 위핚 구조체
	static RECT rc;
	RECT rectView;

	switch (iMessage) {
	case WM_CREATE:
		GetWindowRect(hWnd, &rc);
		srand((unsigned)time(0));
		idx = 0;
		size = 0;
		move = false;
		speed1 = 0.1;
		speed2 = 0.1;
		clientcreate.hWindowMenu = GetSubMenu(GetMenu(hWnd), 0);
		clientcreate.idFirstChild = 100; // 첫 번째 차일드 ID
		hwndClient = CreateWindow(TEXT("MDICLIENT"),
			NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, // 윈도우 스타일
			0, 0, 0, 0, // 좌표
			hWnd, NULL,
			g_hInst, (LPSTR)&clientcreate);
		ShowWindow(hwndClient, SW_SHOW); // 클라이언트 윈도우 출력

		GetClientRect(hWnd, &rectView);
		hwndChild = CreateWindowEx(WS_EX_CLIENTEDGE,
			WIN_CHILDCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			0, 0, (rectView.right * 2) / 3, (rectView.bottom * 2) / 3,
			hWnd, NULL, g_hInst, NULL);

		hButton[0] = CreateWindow(L"button", L"Rev_Move",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			((rectView.right * 2) / 3) + 50, BUTTON_SIZE, BUTTON_SIZE * 3, BUTTON_SIZE, hWnd,
			(HMENU)IDC_REV_MOVE_BUTTON, g_hInst, NULL);
		hButton[1] = CreateWindow(L"button", L"Exit",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			((rectView.right * 2) / 3) + 50, BUTTON_SIZE * 2, BUTTON_SIZE * 3, BUTTON_SIZE, hWnd,
			(HMENU)IDC_EXIT_BUTTON, g_hInst, NULL);

		CreateWindow(L"button", L"Circle Size", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 
			((rectView.right * 2) / 3) + 40, 80, 120, 110, hWnd, (HMENU)0, g_hInst, NULL);
		// 버튺 맊들기: 그룹 1
		hRButton[0] = CreateWindow(L"button", L"Small",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			((rectView.right * 2) / 3) + 50, 100, 100, 30, hWnd, (HMENU)ID_CSIZE_SMALL, g_hInst, NULL);
		hRButton[1] = CreateWindow(L"button", L"Middle",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			((rectView.right * 2) / 3) + 50, 130, 100, 30, hWnd, (HMENU)ID_CSIZE_MIDDLE, g_hInst, NULL);
		hRButton[2] = CreateWindow(L"button", L"Big",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			((rectView.right * 2) / 3) + 50, 160, 100, 30, hWnd, (HMENU)ID_CSIZE_BIG, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_CSIZE_SMALL, ID_CSIZE_BIG, ID_CSIZE_SMALL);

		espeed1 = CreateWindow(L"scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
			((rectView.right * 2) / 3) + 10, 200, 200, 20, hWnd, (HMENU)ID_ESPEED1, g_hInst, NULL);
		espeed2 = CreateWindow(L"scrollbar", NULL,WS_CHILD | WS_VISIBLE | SBS_HORZ,
			((rectView.right * 2) / 3) + 10, 220, 200, 20, hWnd, (HMENU)ID_ESPEED2, g_hInst, NULL);
		SetScrollRange(espeed1, SB_CTL, 0, 10, TRUE);
		SetScrollPos(espeed1, SB_CTL, 0, TRUE);
		SetScrollRange(espeed2, SB_CTL, 0, 10, TRUE);
		SetScrollPos(espeed2, SB_CTL, 0, TRUE);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_TIMER:
		break;
	case WM_HSCROLL:
		if ((HWND)lParam == espeed1) TempPos = speed1;
		if ((HWND)lParam == espeed2) TempPos = speed2;
		switch (LOWORD(wParam)) {
		case SB_LINELEFT: TempPos = max(0, TempPos - 0.01); break;
		case SB_LINERIGHT: TempPos = min(255, TempPos + 0.01); break;
		case SB_PAGELEFT: TempPos = max(0, TempPos - 0.1); break;
		case SB_PAGERIGHT: TempPos = min(255, TempPos + 0.1); break;
		case SB_THUMBTRACK: TempPos = HIWORD(wParam); break;
		}
		if ((HWND)lParam == espeed1) speed1 = TempPos;
		if ((HWND)lParam == espeed2) speed2 = TempPos;
		SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);
		InvalidateRect(hwndChild, NULL, FALSE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_REV_MOVE_BUTTON:
			if (!move) move = true;
			else if (move) move = false;
			break;
		case IDC_EXIT_BUTTON:
			PostQuitMessage(0);
			break;
		case ID_CSIZE_SMALL:
			size = 0;
			break;
		case ID_CSIZE_MIDDLE:
			size = 5;
			break;
		case ID_CSIZE_BIG:
			size = 10;
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rcc, e1, e2, oe1, oe2;
	static double x1, y1, x2, y2, radian1, radian2;
	switch (iMessage)
	{
	case WM_CREATE:
		
		break;
	case WM_CHAR:
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			x1 = 50 * cos(radian1);
			y1 = 50 * sin(radian1);
			if(!move) radian1 += speed1;
			else if (move) radian1 -= speed1;
			break;
		case 2:
			x2 = 100 * cos(radian2);
			y2 = 100 * sin(radian2);
			if (!move) radian2 += speed2;
			else if (move) radian2 -= speed2;
			break;
		}
		InvalidateRect(hwndChild, nullptr, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwndChild, &ps);

		Ellipse(hdc, e2.left, e2.top, e2.right, e2.bottom);
		Ellipse(hdc, e1.left, e1.top, e1.right, e1.bottom);
		MoveToEx(hdc, rcc.right / 2, 0, nullptr);
		LineTo(hdc, rcc.right / 2, rcc.bottom);
		MoveToEx(hdc, 0, rcc.bottom / 2, nullptr);
		LineTo(hdc, rcc.right, rcc.bottom / 2);
		Ellipse(hdc, oe2.left + x2 - 10 - size, oe2.top + y2 - 10 - size, oe2.right + x2 + 10 + size, oe2.bottom + y2 + 10 + size);
		Ellipse(hdc, oe1.left + x1 - 5 - size, oe1.top + y1 - 5 - size, oe1.right + x1 + 5 + size, oe1.bottom + y1 + 5 + size);

		EndPaint(hwndChild, &ps);
		break;
	case WM_LBUTTONDOWN:
		
		break;
	case WM_MOUSEMOVE:
		
		InvalidateRect(hwndChild, nullptr, true);
		break;
	case WM_LBUTTONUP:
		if (hWnd == hwndChild)
		{
			SetTimer(hwndChild, 1, 60, nullptr);
			SetTimer(hwndChild, 2, 30, nullptr);
			SetFocus(hwndChild);
			e1 = { rcc.right / 2 - 50, rcc.bottom / 2 - 50, rcc.right / 2 + 50, rcc.bottom / 2 + 50 };
			e2 = { rcc.right / 2 - 100, rcc.bottom / 2 - 100, rcc.right / 2 + 100, rcc.bottom / 2 + 100 };
			oe1 = { rcc.right / 2, rcc.bottom / 2, rcc.right / 2, rcc.bottom / 2 };
			oe2 = { rcc.right / 2, rcc.bottom / 2, rcc.right / 2, rcc.bottom / 2 };
			GetClientRect(hwndChild, &rcc);
		}
		
		InvalidateRect(hwndChild, NULL, FALSE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}