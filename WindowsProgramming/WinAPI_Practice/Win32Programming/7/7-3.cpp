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

enum RGB {
	G = 0, R = 1, Y = 2, RAND = 3
};
enum Flag {
	line, rectangle, ellipse, on, off, shrink, expand, help
};

typedef struct {
	TCHAR str[10][100] = { 0 };
	SIZE size;
	int count, linecount, wp;
}Data;

typedef struct DRAW {
	RECT rc;
	int shape;
	int color;
	int border;
	DRAW * next;
	DRAW * prev;
}Draw;

Draw * New();
Draw * Delete(Draw * head);

HINSTANCE g_hInst;
HWND g_hwnd;
HWND hwndChild[2];
int idx;
CImage img;
LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
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
	WndClass.lpfnWndProc = FrameWndProc; // 프로시저 함수명
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

LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndClient; // 클라이언트 윈도우
	CLIENTCREATESTRUCT clientcreate; // 차일드 생성을 관리하기 위핚 구조체
	TCHAR childwindow[50];
	static RECT rc;
	RECT rectView;

	switch (iMessage) {
	case WM_CREATE:
		GetWindowRect(hWnd, &rc);
		img.LoadFromResource(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		srand((unsigned)time(0));
		idx = 0;
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
			0, 0, rectView.right / 2 - 1, rectView.bottom,
			hWnd, NULL, g_hInst, NULL);
		hwndChild[1] = CreateWindowEx(WS_EX_CLIENTEDGE,
			WIN_CHILDCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			rectView.right / 2 + 1, 0, rectView.right, rectView.bottom,
			hWnd, NULL, g_hInst, NULL);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:

		break;
	case WM_TIMER:
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_NEW:

			break;
		}
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rcl, rcr, rect;
	static bool o, t, flag, drag;
	static POINT mpoint;
	switch (iMessage)
	{
	case WM_CREATE:
		GetClientRect(hwndChild[0], &rcl);
		GetClientRect(hwndChild[1], &rcr);
		o = false;
		t = false;
		flag = false;
		drag = false;
		break;
	case WM_CHAR:
		if (wParam == 'c')
		{
			flag = true;
		}
		break;
	case WM_TIMER:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwndChild[0], &ps);
		img.Draw(hdc, rcl.left, rcl.top, rcl.right - rcl.left, rcl.bottom - rcl.top, 0, 0, img.GetWidth(), img.GetHeight());
		FrameRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));

		EndPaint(hwndChild[0], &ps);
		hdc = BeginPaint(hwndChild[1], &ps);
		if(flag)
			img.StretchBlt(hdc, 0, 0, rcr.right - rcr.left, rcr.bottom - rcr.top, 
				rect.right - 50, rect.top - 50, rect.right - rect.left, rect.bottom - rect.top, SRCCOPY);


		EndPaint(hwndChild[1], &ps);
		break;
	case WM_LBUTTONDOWN:
		if (!drag && idx == 0) {
			if (rect.left < LOWORD(lParam) && rect.right > LOWORD(lParam) &&
				rect.top < HIWORD(lParam) && rect.bottom >HIWORD(lParam))
			{
				mpoint.x = LOWORD(lParam);
				mpoint.y = HIWORD(lParam);
			}
			else
			{
				rect = { LOWORD(lParam), HIWORD(lParam) ,LOWORD(lParam), HIWORD(lParam) };
			}
			drag = true;
		}
		LOWORD(lParam);
		HIWORD(lParam);

		InvalidateRect(hwndChild[0], nullptr, false);
		break;
	case WM_MOUSEMOVE:
		if (drag)
		{
			if (rect.left < LOWORD(lParam) && rect.right > LOWORD(lParam) &&
				rect.top < HIWORD(lParam) && rect.bottom >HIWORD(lParam))
			{
				OffsetRect(&rect, LOWORD(lParam) - mpoint.x, HIWORD(lParam) - mpoint.y);
				mpoint.x = LOWORD(lParam);
				mpoint.y = HIWORD(lParam);
			}
			else
			{
				rect.right = LOWORD(lParam);
				rect.bottom = HIWORD(lParam);
			}
		}
		InvalidateRect(hwndChild[0], nullptr, true);
		InvalidateRect(hwndChild[1], nullptr, true);
		break;
	case WM_LBUTTONUP:
		drag = false;
		if (hWnd == hwndChild[0])
		{
			idx = 0;
			SetFocus(hwndChild[0]);
			if (!o) {
				GetClientRect(hwndChild[0], &rcl);
				o = true;
			}
		}
		if (hWnd == hwndChild[1])
		{
			idx = 1;
			SetFocus(hwndChild[1]);
			if (!t) {
				GetClientRect(hwndChild[1], &rcr);
				t = true;
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

/*
실습7-3
2개의 윈도우에 그림 그리기

윈도우를 좌/우로 나눈다
좌측의 윈도우에 이미지를 띄우고, 마우스를 이용하여 사각형을 그린다.
키보드 'c'를 입력하면 사각형 내의 그림이 우측의 윈도우에 그려진다
좌측 윈도우의 사각형을 마우스로 선택하고 드래그하면 이동되고
이동되는 위치의 그림이 우측에도 바뀌어서 그려진다
*/