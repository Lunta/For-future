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
	WNDCLASS WndClass; //����ü ����
	RECT rc = { 0, 0, WIN_Width, WIN_Height };
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX |
		WS_BORDER | WS_MAXIMIZEBOX; //WS_HSCROLL | WS_VSCROLL | WS_THICKFRAME
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0; // O/S ��� ���� �޸�(Class)
	WndClass.cbWndExtra = 0; // O/S ��� ���� �޸�(Window)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ�� ����
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //���������� WndClass.hIconSM : ����������
	WndClass.lpfnWndProc = FrameWndProc; // ���ν��� �Լ���
	WndClass.hInstance = hInstance; //���� ���α׷� ID
	WndClass.lpszClassName = WIN_FRAMECLASSNAME; // Ŭ���� �̸�
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU7_1); // �޴� �̸�
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = ChildWndProc; // ���ν��� �Լ���
	WndClass.lpszClassName = WIN_CHILDCLASSNAME; // Ŭ���� �̸�

	RegisterClass(&WndClass);

	AdjustWindowRect(&rc, dwStyle, FALSE);
	hwnd = CreateWindow( // �����찡 �����Ǹ� �ڵ�(hwnd)�� ��ȯ��
		WIN_FRAMECLASSNAME,	// ������ Ŭ���� �̸�
		WIN_TITLENAME,	 // ������ Ÿ��Ʋ �̸�
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

LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndClient; // Ŭ���̾�Ʈ ������
	CLIENTCREATESTRUCT clientcreate; // ���ϵ� ������ �����ϱ� ���� ����ü
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
		clientcreate.idFirstChild = 100; // ù ��° ���ϵ� ID
		hwndClient = CreateWindow(TEXT("MDICLIENT"),
			NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, // ������ ��Ÿ��
			0, 0, 0, 0, // ��ǥ
			hWnd, NULL,
			g_hInst, (LPSTR)&clientcreate);
		ShowWindow(hwndClient, SW_SHOW); // Ŭ���̾�Ʈ ������ ���

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
�ǽ�7-3
2���� �����쿡 �׸� �׸���

�����츦 ��/��� ������
������ �����쿡 �̹����� ����, ���콺�� �̿��Ͽ� �簢���� �׸���.
Ű���� 'c'�� �Է��ϸ� �簢�� ���� �׸��� ������ �����쿡 �׷�����
���� �������� �簢���� ���콺�� �����ϰ� �巡���ϸ� �̵��ǰ�
�̵��Ǵ� ��ġ�� �׸��� �������� �ٲ� �׷�����
*/