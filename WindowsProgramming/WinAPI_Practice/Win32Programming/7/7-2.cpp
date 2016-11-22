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
HWND hwndChild[4];
int idx;

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
	MDICREATESTRUCT mdicreate[5];
	TCHAR childwindow[50];
	static RECT rc;
	RECT rectView;

	switch (iMessage) {
	case WM_CREATE:
		GetWindowRect(hWnd, &rc);
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
			0, 0, rectView.right / 2 - 1, rectView.bottom / 2 - 1,
			hWnd, NULL, g_hInst, NULL);
		hwndChild[1] = CreateWindowEx(WS_EX_CLIENTEDGE,
			WIN_CHILDCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			rectView.right / 2 + 1, 0, rectView.right, rectView.bottom / 2 - 1,
			hWnd, NULL, g_hInst, NULL);
		hwndChild[2] = CreateWindowEx(WS_EX_CLIENTEDGE,
			WIN_CHILDCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			0, rectView.bottom / 2 + 1, rectView.right / 2 - 1, rectView.bottom ,
			hWnd, NULL, g_hInst, NULL);
		hwndChild[3] = CreateWindowEx(WS_EX_CLIENTEDGE,
			WIN_CHILDCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			rectView.right / 2 + 1, rectView.bottom / 2 + 1, rectView.right, rectView.bottom ,
			hWnd, NULL, g_hInst, NULL);
		break;
	case WM_LBUTTONUP:
		LOWORD(lParam);
		HIWORD(lParam);

		InvalidateRect(hWnd, nullptr, false);
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
	HDC hdc, memdc;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush[4], oldBrush;
	static HBITMAP memBit;
	static RECT rc, rcc, ball;
	static int flag, color, shape, border, x, y;
	static bool drag, d, fl, o, t, th, f;
	static Data data[4];
	static Draw * head = nullptr, *tail = nullptr, *temp = head;
	int i;

	switch (iMessage)
	{
	case WM_CREATE:
		GetClientRect(hwndChild[2], &rcc);
		ball = { rcc.left, rcc.top, rcc.left + 30, rcc.top + 30 };
		x = 10;
		y = 10;
		o = false;
		t = false;
		th = false;
		f = false;
		break;
	case WM_CHAR:
		if (idx == 0 || idx == 3)
		{
			if (wParam == VK_BACK) {
				if (data[idx].count == 0 && data[idx].linecount != 0) {
					data[idx].count = lstrlen(data[idx].str[--data[idx].linecount]);
				}
				else data[idx].str[data[idx].linecount][--data[idx].count] = '\0';
				InvalidateRect(hWnd, NULL, TRUE);
			}
			else if (wParam == VK_RETURN) {
				data[idx].linecount++;
				data[idx].count = 0;
			}
			else if (wParam == VK_TAB)
			{
				data[idx].str[data[idx].linecount][data[idx].count++] = ' ';
				data[idx].str[data[idx].linecount][data[idx].count++] = ' ';
				data[idx].str[data[idx].linecount][data[idx].count++] = ' ';
				data[idx].str[data[idx].linecount][data[idx].count++] = ' ';
				data[idx].str[data[idx].linecount][data[idx].count] = '\0';
			}
			else if (wParam == '\\')
			{
				data[idx].wp = '\\';

			}
			else if (wParam == VK_ESCAPE)
			{
				for (data[idx].linecount = 0; data[idx].linecount < 10; data[idx].linecount++)
					for (data[idx].count = 0; data[idx].count < 100; data[idx].count++) {
						data[idx].str[data[idx].linecount][data[idx].count] = '\0';
					}
				data[idx].linecount = 0;
				data[idx].count = 0;
				InvalidateRect(hwndChild[idx], NULL, TRUE);
			}
			else {
				data[idx].str[data[idx].linecount][data[idx].count++] = wParam;
				data[idx].str[data[idx].linecount][data[idx].count] = '\0';
			}
			InvalidateRect(hwndChild[idx], NULL, TRUE);
		}
		break;
	case WM_TIMER:
		OffsetRect(&ball, x, y);
		if (rcc.left > ball.left) x = -x;
		if (rcc.right < ball.right) x = -x;
		if (rcc.top > ball.top) y = -y;
		if (rcc.top + 300 < ball.bottom) y = -y;
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_PAINT:
		if (idx == 0 || idx == 3)
		{
			hdc = BeginPaint(hwndChild[idx], &ps);
			//이하 출력
			CreateCaret(hwndChild[idx], NULL, 5, 15);
			//ShowCaret(hwndChild[idx]); // 빈 화면에 캐럿 표시
			GetTextExtentPoint(hdc, data[idx].str[data[idx].linecount], lstrlen(data[idx].str[data[idx].linecount]), &data[idx].size);
			SetCaretPos(data[idx].size.cx, data[idx].linecount * 20);
			if (data[idx].wp == '\\')
			{
				TextOut(hdc, 0, data[idx].linecount * 20, data[idx].str[data[idx].linecount], lstrlen(data[idx].str[data[idx].linecount]));
				SetCaretPos(0, data[idx].linecount * 20);
				data[idx].wp = 0;
			}
			else for (i = 0; i < data[idx].linecount + 1; i++) {
				TextOut(hdc, 0, i * 20, data[idx].str[i], lstrlen(data[idx].str[i]));
			}

			EndPaint(hwndChild[idx], &ps);
		}
		if (idx == 1)
		{
			hdc = BeginPaint(hwndChild[1], &ps);
			memdc = CreateCompatibleDC(hdc);
			memBit = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
			SelectObject(memdc, memBit);
			FillRect(memdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
			//
			hPen = CreatePen(PS_SOLID, 3, RGB(rand() % 256, rand() % 256, rand() % 256));
			hBrush[0] = CreateSolidBrush(RGB(0, 255, 0));
			hBrush[1] = CreateSolidBrush(RGB(255, 0, 0));
			hBrush[2] = CreateSolidBrush(RGB(0, 255, 255));
			hBrush[3] = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));

			temp = head;
			while (temp != nullptr) {
				if (temp->border == on) oldPen = (HPEN)SelectObject(memdc, hPen);
				else if (temp->border == off) oldPen = (HPEN)SelectObject(memdc, GetStockObject(BLACK_PEN));
				oldBrush = (HBRUSH)SelectObject(memdc, hBrush[temp->color]);
				MoveToEx(memdc, temp->rc.left, temp->rc.top, NULL);
				LineTo(memdc, temp->rc.right, temp->rc.bottom);
				temp = temp->next;
			}
			if (flag == help) TextOut(memdc, rc.right / 2, rc.bottom / 2, L"예제 4-3", sizeof(L"예 "));
			// hdc에 복사
			BitBlt(hdc, 0, 0, rc.right, rc.bottom, memdc, 0, 0, SRCCOPY);

			SelectObject(hdc, oldPen);
			SelectObject(hdc, oldBrush);
			for (int i = 0; i < 4; i++)
				DeleteObject(hBrush[i]);
			DeleteObject(hPen);

			SelectObject(memdc, NULL);
			DeleteDC(memdc);
			DeleteObject(memBit);
			EndPaint(hwndChild[1], &ps);
		}

		hdc = BeginPaint(hwndChild[2], &ps);
		Ellipse(hdc, ball.left, ball.top, ball.right, ball.bottom);
		EndPaint(hwndChild[2], &ps);
		break;
	case WM_LBUTTONDOWN:
		if (idx == 1) {
			if (!drag)
			{
				if (head == nullptr)
				{
					head = new Draw;
					head->next = nullptr;
					head->prev = nullptr;
					head->rc.left = LOWORD(lParam);
					head->rc.top = HIWORD(lParam);
					head->rc.right = LOWORD(lParam);
					head->rc.bottom = HIWORD(lParam);
					head->shape = shape;
					head->color = color;
					head->border = border;
					tail = head;
				}
				else
				{
					tail->next = New();
					tail->next->prev = tail;
					tail = tail->next;
					tail->rc.left = LOWORD(lParam);
					tail->rc.top = HIWORD(lParam);
					tail->rc.right = LOWORD(lParam);
					tail->rc.bottom = HIWORD(lParam);
					tail->shape = shape;
					tail->color = color;
					tail->border = border;
				}
				drag = true;
				d = true;
			}
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	case WM_MOUSEMOVE:
		if (idx == 1)
		{
			if (drag)
			{
				if (shape != line)
				{
					tail->rc.right = LOWORD(lParam);
					tail->rc.bottom = HIWORD(lParam);
				}
				if (shape == line)
				{
					if (d) {
						tail->rc.right = LOWORD(lParam);
						tail->rc.bottom = HIWORD(lParam);
						d = false;
					}
					else
					{
						tail->next = New();
						tail->next->prev = tail;
						tail = tail->next;
						tail->shape = line;
						tail->color = color;
						tail->border = border;
						tail->rc.left = tail->prev->rc.right;
						tail->rc.top = tail->prev->rc.bottom;
						tail->rc.right = LOWORD(lParam);
						tail->rc.bottom = HIWORD(lParam);
					}
				}
			}
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	case WM_LBUTTONUP:
		if(idx == 1) drag = false;
		if (hWnd == hwndChild[0])
		{
			idx = 0;
			SetFocus(hwndChild[0]);
			if (!o) {
				data[idx].count = 0;
				data[idx].linecount = 0;
				i = 0;
				o = true;
			}
		}
		if (hWnd == hwndChild[1])
		{
			idx = 1;
			SetFocus(hwndChild[1]);
			if (!t) {
				fl = false;
				GetClientRect(hWnd, &rc);
				d = drag = false;
				tail = head;
				shape = line;
				border = off;
				t = true;
			}
		}
		if (hWnd == hwndChild[2])
		{
			idx = 2;
			if(!fl) SetTimer(hWnd, 2, 100, NULL);
			else KillTimer(hWnd, 2);
			SetFocus(hwndChild[2]);
			if (!th)
			{
				th = true;
			}
		}
		if (hWnd == hwndChild[3])
		{
			idx = 3;
			SetFocus(hwndChild[3]);
			if (!f) {
				data[idx].count = 0;
				data[idx].linecount = 0;
				i = 0;
				f = true;
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		if (idx == 0 || idx == 3)
		{
			HideCaret(hwndChild[idx]);
			DestroyCaret();
		}
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

Draw * New()
{
	Draw * NEW = new Draw;
	NEW->rc = { 0, 0, 0, 0 };
	NEW->next = nullptr;
	NEW->prev = nullptr;
	return NEW;
}
Draw * Delete(Draw * head)
{
	Draw * temp = head, *del = nullptr;
	while (temp != nullptr)
	{
		del = temp;
		temp = temp->next;
		delete del;
	}
	return nullptr;
}