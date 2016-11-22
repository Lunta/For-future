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
#define IDC_W1_WMOVE_BUTTON 100
#define IDC_W1_HMOVE_BUTTON 101
#define IDC_W1_JUMP_BUTTON 102
#define IDC_W2_WMOVE_BUTTON 103
#define IDC_W2_HMOVE_BUTTON 104
#define IDC_W2_JUMP_BUTTON 105
#define IDC_STOP_BUTTON 106
#define IDC_CHANGE_BUTTON 107
#define IDC_EXIT_BUTTON 108

typedef enum {
	wmove = 0, hmove, jump, stop
}KindofMove;

HINSTANCE g_hInst;
HWND g_hwnd;
HWND hwndChild[2];

HWND hButton[9];
bool move, change;
int w1move, w2move;
int idx, size;
int xv1, yv1, xv2, yv2;

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
	TCHAR childwindow[50];
	static RECT rc;
	RECT rectView;

	switch (iMessage) {
	case WM_CREATE:
		GetWindowRect(hWnd, &rc);
		srand((unsigned)time(0));
		idx = 0;
		move = true;
		xv1 = 0;
		yv1 = 0;
		xv2 = 0;
		yv2 = 0;

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
		hwndChild[0] = CreateWindowEx(WS_EX_CLIENTEDGE,
			WIN_CHILDCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			0, 0, rectView.right / 2 - 1, rectView.bottom * 2 / 3,
			hWnd, NULL, g_hInst, NULL);
		hwndChild[1] = CreateWindowEx(WS_EX_CLIENTEDGE,
			WIN_CHILDCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			rectView.right / 2 + 1, 0, rectView.right / 2 - 1, rectView.bottom * 2 / 3,
			hWnd, NULL, g_hInst, NULL);

		hButton[0] = CreateWindow(L"button", L"W1 WMove",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10, rectView.bottom - 50, BUTTON_SIZE * 3, BUTTON_SIZE, hWnd,
			(HMENU)IDC_W1_WMOVE_BUTTON, g_hInst, NULL);
		hButton[1] = CreateWindow(L"button", L"W1 HMove",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10 + (BUTTON_SIZE * 3 + 1), rectView.bottom - 50, BUTTON_SIZE * 3, BUTTON_SIZE, hWnd,
			(HMENU)IDC_W1_HMOVE_BUTTON, g_hInst, NULL);
		hButton[2] = CreateWindow(L"button", L"W1 Jump",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10 + (BUTTON_SIZE * 3 + 1) * 2, rectView.bottom - 50, BUTTON_SIZE * 3, BUTTON_SIZE, hWnd,
			(HMENU)IDC_W1_JUMP_BUTTON, g_hInst, NULL);
		hButton[3] = CreateWindow(L"button", L"W2 WMove",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10 + (BUTTON_SIZE * 3 + 1) * 3, rectView.bottom - 50, BUTTON_SIZE * 3, BUTTON_SIZE, hWnd,
			(HMENU)IDC_W2_WMOVE_BUTTON, g_hInst, NULL);
		hButton[4] = CreateWindow(L"button", L"W2 HMove",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10 + (BUTTON_SIZE * 3 + 1) * 4, rectView.bottom - 50, BUTTON_SIZE * 3, BUTTON_SIZE, hWnd,
			(HMENU)IDC_W2_HMOVE_BUTTON, g_hInst, NULL);
		hButton[5] = CreateWindow(L"button", L"W2 Jump",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10 + (BUTTON_SIZE * 3 + 1) * 5, rectView.bottom - 50, BUTTON_SIZE * 3, BUTTON_SIZE, hWnd,
			(HMENU)IDC_W2_JUMP_BUTTON, g_hInst, NULL);
		hButton[6] = CreateWindow(L"button", L"Stop",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10 + (BUTTON_SIZE * 3 + 1) * 6, rectView.bottom - 50, BUTTON_SIZE * 3, BUTTON_SIZE, hWnd,
			(HMENU)IDC_STOP_BUTTON, g_hInst, NULL);
		hButton[7] = CreateWindow(L"button", L"Change",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10 + (BUTTON_SIZE * 3 + 1) * 7, rectView.bottom - 50, BUTTON_SIZE * 3, BUTTON_SIZE, hWnd,
			(HMENU)IDC_CHANGE_BUTTON, g_hInst, NULL);
		hButton[8] = CreateWindow(L"button", L"Exit",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10 + (BUTTON_SIZE * 3 + 1) * 8, rectView.bottom - 50, BUTTON_SIZE * 3, BUTTON_SIZE, hWnd,
			(HMENU)IDC_EXIT_BUTTON, g_hInst, NULL);

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_W1_WMOVE_BUTTON:
			w1move = KindofMove::wmove;
			xv1 = 10;
			yv1 = 0;
			break;
		case IDC_W1_HMOVE_BUTTON:
			w1move = KindofMove::hmove;
			xv1 = 0;
			yv1 = 10;
			break;
		case IDC_W1_JUMP_BUTTON:
			w1move = KindofMove::jump;
			xv1 = 0;
			yv1 = -10;
			break;
		case IDC_W2_WMOVE_BUTTON:
			w2move = KindofMove::wmove;
			xv2 = 10;
			yv2 = 0;
			break;
		case IDC_W2_HMOVE_BUTTON:
			w2move = KindofMove::hmove;
			xv2 = 0;
			yv2 = 10;
			break;
		case IDC_W2_JUMP_BUTTON:
			w2move = KindofMove::jump;
			xv2 = 0;
			yv2 = -10;
			break;
		case IDC_STOP_BUTTON:
			w1move = KindofMove::stop;
			w2move = KindofMove::stop;
			break;
		case IDC_CHANGE_BUTTON:
			if (!change) change = true;
			else if (change) change = false;
			break;
		case IDC_EXIT_BUTTON:
			PostQuitMessage(0);
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
	static RECT rc1, rc2, e1, e2;
	static int timer1, timer2;
	switch (iMessage)
	{
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if (timer1++ == 100000000) timer1 = 0;
			switch (w1move)
			{
			case KindofMove::wmove:
				if (rc1.left > e1.left || rc1.right < e1.right) xv1 = -xv1;
				OffsetRect(&e1, xv1, yv1);
				break;
			case KindofMove::hmove:
				if (rc1.top > e1.top || rc1.bottom < e1.bottom) yv1 = -yv1;
				OffsetRect(&e1, xv1, yv1);
				break;
			case KindofMove::jump:
				if (timer1 % 10 == 0) yv1 = -yv1;
				OffsetRect(&e1, xv1, yv1);
				break;
			}
			break;
		case 2:
			if (timer2++ == 100000000) timer2 = 0;
			switch (w2move)
			{
			case KindofMove::wmove:
				if (rc2.left > e2.left || rc2.right < e2.right) xv2 = -xv2;
				OffsetRect(&e2, xv2, yv2);
				break;
			case KindofMove::hmove:
				if (rc2.top > e2.top || rc2.bottom < e2.bottom) yv2 = -yv2;
				OffsetRect(&e2, xv2, yv2);
				break;
			case KindofMove::jump:
				if (timer2 % 20 == 0) yv2 = -yv2;
				OffsetRect(&e2, xv2, yv2);
				break;
			}
			break;
		}
		InvalidateRect(hwndChild[0], nullptr, true);
		InvalidateRect(hwndChild[1], nullptr, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwndChild[0], &ps);

		if (change) Rectangle(hdc, e1.left, e1.top, e1.right, e1.bottom);
		else Ellipse(hdc, e1.left, e1.top, e1.right, e1.bottom);

		EndPaint(hwndChild[0], &ps);
		hdc = BeginPaint(hwndChild[1], &ps);

		if(change) Ellipse(hdc, e2.left, e2.top, e2.right, e2.bottom);
		else Rectangle(hdc, e2.left, e2.top, e2.right, e2.bottom);

		EndPaint(hwndChild[1], &ps);
		break;
	case WM_LBUTTONDOWN:

		break;
	case WM_MOUSEMOVE:

		InvalidateRect(hwndChild[0], nullptr, true);
		break;
	case WM_LBUTTONUP:
		if (hWnd == hwndChild[0])
		{
			SetTimer(hwndChild[0], 1, 60, nullptr);
			SetFocus(hwndChild[0]);
			GetClientRect(hwndChild[0], &rc1);
			e1 = { rc1.right / 2 - 50, rc1.bottom / 2 - 50, rc1.right / 2 + 50, rc1.bottom / 2 + 50 };
		}
		if (hWnd == hwndChild[1])
		{
			SetTimer(hwndChild[1], 2, 30, nullptr);
			SetFocus(hwndChild[1]);
			GetClientRect(hwndChild[1], &rc2);
			e2 = { rc2.right / 2 - 50, rc2.bottom / 2 - 50, rc2.right / 2 + 50, rc2.bottom / 2 + 50 };
		}
		InvalidateRect(hwndChild[1], NULL, FALSE);
		InvalidateRect(hwndChild[0], NULL, FALSE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}