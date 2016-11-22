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

#define Width 30
#define Height 30
#define Size 30
#define GREEN		RGB(0, 255, 0)
#define RED			RGB(255, 0, 0)
#define YELLOW		RGB(255, 228, 0)
#define RAINBOW		RGB(rand() % 256, rand() % 256, rand() % 256)
enum RGB {
	G = 0, R = 1, Y = 2, RAND = 3
};
enum Flag {
	line, rectangle, ellipse, on, off, shrink, expand, help
};

typedef struct DRAW {
	RECT rc;
	int shape;
	int color;
	int border;
	DRAW * next;
	DRAW * prev;
}Draw;

HINSTANCE g_hInst;
LPCTSTR lpszClass = WIN_CLASSNAME;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
Draw * New();
Draw * Delete(Draw * head);

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU4_3); // 메뉴 이름
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
	HPEN hPen, oldPen;
	HBRUSH hBrush[4], oldBrush;
	static HBITMAP memBit;
	static RECT rc;
	static int flag, color, shape, border, x, y;
	static bool drag, d;
	static Draw * head = nullptr, *tail = nullptr, *temp = head;
	srand((unsigned)time(NULL));
	switch (iMessage) {
	case WM_CREATE:
		GetClientRect(hWnd, &rc);
		SetTimer(hWnd, 1, 30, NULL);
		d = drag = false;
		tail = head;
		break;
	case WM_LBUTTONDOWN:
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
		break;
	case WM_MOUSEMOVE:
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
		break;
	case WM_LBUTTONUP:
		drag = false;
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
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
		hPen = CreatePen(PS_SOLID, 3, RAINBOW);
		hBrush[0] = CreateSolidBrush(GREEN);
		hBrush[1] = CreateSolidBrush(RED);
		hBrush[2] = CreateSolidBrush(YELLOW);
		hBrush[3] = CreateSolidBrush(RAINBOW);

		temp = head;
		while (temp != nullptr) {
			switch (temp->shape) {
			case line:
				if (temp->border == on) oldPen = (HPEN)SelectObject(memdc, hPen);
				else if (temp->border == off) oldPen = (HPEN)SelectObject(memdc, GetStockObject(BLACK_PEN));
				oldBrush = (HBRUSH)SelectObject(memdc, hBrush[temp->color]);
				MoveToEx(memdc, temp->rc.left, temp->rc.top, NULL);
				LineTo(memdc, temp->rc.right, temp->rc.bottom);
				break;
			case rectangle:
				if (temp->border == on) oldPen = (HPEN)SelectObject(memdc, hPen);
				else if (temp->border == off) oldPen = (HPEN)SelectObject(memdc, GetStockObject(BLACK_PEN));
				oldBrush = (HBRUSH)SelectObject(memdc, hBrush[temp->color]);
				Rectangle(memdc, temp->rc.left, temp->rc.top, temp->rc.right, temp->rc.bottom);
				break;
			case ellipse:
				if (temp->border == on) oldPen = (HPEN)SelectObject(memdc, hPen);
				else if (temp->border == off) oldPen = (HPEN)SelectObject(memdc, GetStockObject(BLACK_PEN));
				oldBrush = (HBRUSH)SelectObject(memdc, hBrush[temp->color]);
				Ellipse(memdc, temp->rc.left, temp->rc.top, temp->rc.right, temp->rc.bottom);
				break;
			}
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
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_SHAPE_LINE:
			shape = line;
			break;
		case ID_SHAPE_RECTANGLE:
			shape = rectangle;
			break;
		case ID_SHAPE_ELLIPSE:
			shape = ellipse;
			break;
		case ID_BORDER_ON:
			border = on;
			break;
		case ID_BORDER_OFF:
			border = off;
			break;
		case ID_CHANGE_SHRINK:
			temp = head;
			while (temp != nullptr) {
				if (temp->rc.left < temp->rc.right && temp->rc.top < temp->rc.bottom)
				{
					temp->rc.left += 10;
					temp->rc.top += 10;
					temp->rc.right -= 10;
					temp->rc.bottom -= 10;
				}
				else if (temp->rc.left > temp->rc.right && temp->rc.top > temp->rc.bottom)
				{
					temp->rc.left -= 10;
					temp->rc.top -= 10;
					temp->rc.right += 10;
					temp->rc.bottom += 10;
				}
				else if (temp->rc.left > temp->rc.right && temp->rc.top < temp->rc.bottom)
				{
					temp->rc.left -= 10;
					temp->rc.top += 10;
					temp->rc.right += 10;
					temp->rc.bottom -= 10;
				}
				else if (temp->rc.left < temp->rc.right && temp->rc.top > temp->rc.bottom)
				{
					temp->rc.left += 10;
					temp->rc.top -= 10;
					temp->rc.right -= 10;
					temp->rc.bottom += 10;
				}
				temp = temp->next;
			}
			break;
		case ID_CHANGE_EXPAND:
			temp = head;
			while (temp != nullptr) {
				if (temp->rc.left < temp->rc.right && temp->rc.top < temp->rc.bottom)
				{
					temp->rc.left -= 10;
					temp->rc.top -= 10;
					temp->rc.right += 10;
					temp->rc.bottom += 10;
				}
				else if (temp->rc.left > temp->rc.right && temp->rc.top > temp->rc.bottom)
				{
					temp->rc.left += 10;
					temp->rc.top += 10;
					temp->rc.right -= 10;
					temp->rc.bottom -= 10;
				}
				else if (temp->rc.left > temp->rc.right && temp->rc.top < temp->rc.bottom)
				{
					temp->rc.left += 10;
					temp->rc.top -= 10;
					temp->rc.right -= 10;
					temp->rc.bottom += 10;
				}
				else if (temp->rc.left < temp->rc.right && temp->rc.top > temp->rc.bottom)
				{
					temp->rc.left -= 10;
					temp->rc.top += 10;
					temp->rc.right += 10;
					temp->rc.bottom -= 10;
				}
				temp = temp->next;
			}
			break;
		case ID_HELP_HELP:
			flag = help;
			break;
		case ID_HELP_EXIT:
			KillTimer(hWnd, 1);
			PostQuitMessage(0);
			break;
		case ID_COLOR_GREEN3:
			color = G;
			break;
		case ID_COLOR_RED3:
			color = R;
			break;
		case ID_COLOR_YELLOW3:
			color = Y;
			break;
		case ID_COLOR_RANDOM3:
			color = RAND;
			break;
		}
		break;
	case WM_CHAR:
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		head = Delete(head);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
Draw * New()
{
	Draw * NEW = new Draw;
	NEW->rc = {0, 0, 0, 0};
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
/*
color G R Y Rand
shape LINE RECTangle Ellipse
그릴 도형의 색상을 설정한다.
자유그리기 선(마우스드래그) 고무줄효과를 가진 사각형과 원을 그린다
Border On off
도형의 외각선을 다른색으로 그린다/ 외각선 없이 도형을 그린다.
Change Shrink Expand
shrink: 10퍼축소 Expand: 10퍼 확대
help helpExit
help: 프로그램에 이름출력
*/