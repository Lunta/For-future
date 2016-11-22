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

#define Width 40
#define Height 40
#define FigureSize 100

HINSTANCE g_hInst;
LPCTSTR lpszClass = WIN_CLASSNAME;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
float LengthPts(int x1, int y1, int x2, int y2);
BOOL InCircle(RECT * rect, POINT * mpoint);

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
	WndClass.style = CS_HREDRAW | CS_VREDRAW; // 윈도우 출력 스타일 -> 수직/수평의 변화시 다시 그림

	RegisterClass(&WndClass);// •ATOM RegisterClassEx ( CONST WNDCLASSEX *lpwcx );
							 // •&wndclass : 앞서 정의한 윈도우 클래스의 주소
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

	ShowWindow(hwnd, nCmdShow); // 윈도우의 화면 출력
								// nCmdShow : SW_HIDE, SW_SHOW, SW_MAXIMIZE, SW_MINIMIZE
	UpdateWindow(hwnd); // O/S에 WM_PAINT 메시지 전송

	while (GetMessage(&Message, NULL, 0, 0)) // WinProc()에서 PostQuitMessage() 호출 때까지 처리
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
	HBRUSH hBrush[3], oldBrush;
	HPEN hPen, dashPen, oldPen;
	static HBITMAP memBit;
	static RECT figure[4][2], sign[3], rc, load, crossrc, signboxrc;
	static CImage BK, cross, signbox, rightcar, leftcar;
	static bool signR, signB, signY, start;
	static POINT mpoint;
	static int x, y, speed[8];
	int i;

	switch (iMessage) {
	case WM_CREATE:
		srand((unsigned)time(NULL));
		GetWindowRect(hWnd, &rc);
		SetTimer(hWnd, 1, 50, NULL);
		BK.Load(L"5-8배경.png");
		cross.Load(L"cross.png");
		signbox.Load(L"신호등.PNG");
		rightcar.Load(L"차우.png");
		leftcar.Load(L"차좌.png");
		signR = signB = signY = start = FALSE;
		load = {0, 250, rc.right, 550};
		crossrc = { 300, 250, 500, 550 };
		sign[1] = { 250, 150, 250 + Width, 150 + Height};
		sign[2] = { 250 + Width, 150, 250 + 2 * Width, 150 + Height };
		sign[0] = { 250 + 2 * Width, 150, 250 + 3 * Width, 150 + Height };
		signboxrc = { 250, 150, 250 + 3 * Width, 150 + Height };
		for (i = 0; i < 2; i++)
			figure[0][i] = { 100 * i + 20 * i, 260, 100 * (i + 1) + 20 * i, 315 };
		for (i = 0; i < 2; i++)
			figure[1][i] = { 100 * i + 20 * i, 335, 100 * (i + 1) + 20 * i, 390 };
		for (i = 0; i < 2; i++)
			figure[2][i] = { 450 + 100 * i + 20 * i, 410, 450 + 100 * (i + 1) + 20 * i, 465 };
		for (i = 0; i < 2; i++)
			figure[3][i] = { 450 + 100 * i + 20 * i, 485, 450 + 100 * (i + 1) + 20 * i, 540 };
		for (i = 0; i < 8; i++)
			speed[i] = 10 + rand() % 20;
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			for (i = 0; i < 4; i++)
				for (int j = 0; j < 2; j++)
					if (i < 2) OffsetRect(&figure[i][j], speed[i * 2 + j], 0);
					else if (i < 4 && i >= 2) OffsetRect(&figure[i][j], -speed[i * 2 + j], 0);
			for (int j = 0; j < 2; j++)
				for (int x = 0; x < 2; x++) {
					if (crossrc.left > figure[0][j].right && crossrc.left > figure[0][j].left &&
						figure[0][j].right > figure[0][x].left - 20 && figure[0][j].left < figure[0][x].left)
					{
						figure[0][j].left = figure[0][x].left - 120;
						figure[0][j].right = figure[0][x].left - 20;
						speed[0 * 2 + j] = speed[0 * 2 + x];
					}
					if (crossrc.left > figure[1][j].right && crossrc.left > figure[1][j].left &&
						figure[1][j].right > figure[1][x].left - 20 && figure[1][j].left < figure[1][x].left)
					{
						figure[1][j].left = figure[1][x].left - 120;
						figure[1][j].right = figure[1][x].left - 20;
						speed[1 * 2 + j] = speed[1 * 2 + x];
					}
					if (crossrc.right < figure[2][j].left && crossrc.right < figure[2][j].right &&
						figure[2][j].left < figure[2][x].right + 20 && figure[2][j].right > figure[2][x].right)
					{
						figure[2][j].left = figure[2][x].right + 20;
						figure[2][j].right = figure[2][x].right + 120;
						speed[2 * 2 + j] = speed[2 * 2 + x];
					}
					if (crossrc.right < figure[3][j].left && crossrc.right < figure[3][j].right &&
						figure[3][j].left < figure[3][x].right + 20 && figure[3][j].right > figure[3][x].right)
					{
						figure[3][j].left = figure[3][x].right + 20;
						figure[3][j].right = figure[3][x].right + 120;
						speed[3 * 2 + j] = speed[3 * 2 + x];
					}
				}
			if (signR)
			{
				if (!start) {
					for (int s = 0; s < 8; s++)
						speed[s] = 10;
					start = true;
				}
				for (i = 0; i < 4; i++)
					for (int j = 0; j < 2; j++)
						if (crossrc.left < figure[i][j].right && crossrc.left > figure[i][j].left && i < 2) {
							figure[i][j].right = crossrc.left;
							figure[i][j].left = crossrc.left - 100;
							speed[i * 2 + j] = 0;
						}
						else if (crossrc.right > figure[i][j].left && crossrc.right < figure[i][j].right && i < 4 && i >= 2) {
							figure[i][j].right = crossrc.right + 100;
							figure[i][j].left = crossrc.right;
							speed[i * 2 + j] = 0;
						}
				for (int j = 0; j < 2; j++)
					for (int x = 0; x < 2; x++) {
						if (crossrc.left > figure[0][j].right && crossrc.left > figure[0][j].left &&
							figure[0][j].right > figure[0][x].left - 20 && figure[0][j].left < figure[0][x].left)
						{
							figure[0][j].left = figure[0][x].left - 120;
							figure[0][j].right = figure[0][x].left - 20;
							speed[0 * 2 + j] = 0;
						}
						if (crossrc.left > figure[1][j].right && crossrc.left > figure[1][j].left &&
							figure[1][j].right > figure[1][x].left - 20 && figure[1][j].left < figure[1][x].left)
						{
							figure[1][j].left = figure[1][x].left - 120;
							figure[1][j].right = figure[1][x].left - 20;
							speed[1 * 2 + j] = 0;
						}
						if (crossrc.right < figure[2][j].left && crossrc.right < figure[2][j].right &&
							figure[2][j].left < figure[2][x].right + 20 && figure[2][j].right > figure[2][x].right)
						{
							figure[2][j].left = figure[2][x].right + 20;
							figure[2][j].right = figure[2][x].right + 120;
							speed[2 * 2 + j] = 0;
						}
						if (crossrc.right < figure[3][j].left && crossrc.right < figure[3][j].right &&
							figure[3][j].left < figure[3][x].right + 20 && figure[3][j].right > figure[3][x].right)
						{
							figure[3][j].left = figure[3][x].right + 20;
							figure[3][j].right = figure[3][x].right + 120;
							speed[3 * 2 + j] = 0;
						}
					}
			}
			for (i = 0; i < 4; i++)
			{
				for (int j = 0; j < 2; j++)
					if (figure[i][j].left > rc.right)
					{
						figure[i][j].left = -100;
						figure[i][j].right = 0;
					}
					else if (figure[i][j].right < 0)
					{
						figure[i][j].left = rc.right;
						figure[i][j].right = rc.right + 100;
					}
			}
			break;
		case 3:
			signB = FALSE;
			signR = TRUE;
			signY = FALSE;
			KillTimer(hWnd, 3);
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
		hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		dashPen = CreatePen(PS_DASHDOTDOT, 1, RGB(0, 0, 0));
		hBrush[0] = CreateSolidBrush(RGB(255, 0, 0));  //R
		hBrush[1] = CreateSolidBrush(RGB(0, 0, 255));  //B
		hBrush[2] = CreateSolidBrush(RGB(255, 255, 0));//Y
		BK.Draw(memdc, 0, 0, WIN_Width, WIN_Height);
		FillRect(memdc, &load, (HBRUSH)GetStockObject(GRAY_BRUSH));
		oldPen = (HPEN)SelectObject(memdc, hPen);
		MoveToEx(memdc, 0, 250, NULL);
		LineTo(memdc, rc.right, 250);
		MoveToEx(memdc, 0, 400, NULL);
		LineTo(memdc, rc.right, 400);
		MoveToEx(memdc, 0, 550, NULL);
		LineTo(memdc, rc.right, 550);
		SelectObject(memdc, oldPen);
		oldPen = (HPEN)SelectObject(memdc, dashPen);
		MoveToEx(memdc, 0, 325, NULL);
		LineTo(memdc, rc.right, 325);
		MoveToEx(memdc, 0, 475, NULL);
		LineTo(memdc, rc.right, 475);
		SelectObject(memdc, oldPen);
		cross.Draw(memdc, crossrc.left, crossrc.top, cross.GetWidth(), cross.GetHeight());

		for (i = 0; i < 4; i++)
			for (int j = 0; j < 2; j++)
				if (i < 2) rightcar.TransparentBlt(memdc, figure[i][j].left, figure[i][j].top,
					figure[i][j].right - figure[i][j].left, figure[i][j].bottom - figure[i][j].top, RGB(255, 255, 255));
				else if (i < 4 && i >= 2) leftcar.TransparentBlt(memdc, figure[i][j].left, figure[i][j].top,
					figure[i][j].right - figure[i][j].left, figure[i][j].bottom - figure[i][j].top, RGB(255, 255, 255));

		signbox.TransparentBlt(memdc, signboxrc.left, signboxrc.top, 
			signboxrc.right - signboxrc.left, signboxrc.bottom - signboxrc.top, RGB(255, 255, 255));
		// hdc에 복사
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, memdc, 0, 0, SRCCOPY);

		SelectObject(memdc, oldPen);
		for (i = 0; i < 3; i++)
			DeleteObject(hBrush[i]);
		DeleteObject(hPen);
		DeleteObject(dashPen);
		SelectObject(memdc, NULL);
		DeleteDC(memdc);
		DeleteObject(memBit);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		mpoint.x = LOWORD(lParam);
		mpoint.y = HIWORD(lParam);
		if (InCircle(&sign[1], &mpoint)) // 이동시작
		{
			if (signB == TRUE) signB = FALSE;
			else
			{
				signB = TRUE;
				signR = FALSE;
				signY = FALSE;
				for (i = 0; i < 8; i++)
					speed[i] = 10 + rand() % 20;
				start = false;
			}
		}
		else if (InCircle(&sign[2], &mpoint)) //3초후 정지
		{
			if (signY == TRUE) signY = FALSE;
			else
			{
				signR = FALSE;
				signY = TRUE;
				signB = FALSE;
				SetTimer(hWnd, 3, 3000, NULL);
			}
		}
		else if (InCircle(&sign[0], &mpoint)) //정지
		{
			if (signR == TRUE) signR = FALSE;
			else
			{
				signR = TRUE;
				signY = FALSE;
				signB = FALSE;
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		for (i = 0; i < 3; i++)
			KillTimer(hWnd, i);

		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
float LengthPts(int x1, int y1, int x2, int y2)
{
	return (sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
}
BOOL InCircle(RECT * rect, POINT * mpoint)
{
	if (LengthPts((rect->left + rect->right) / 2, (rect->top + rect->bottom) / 2, mpoint->x, mpoint->y)
		< (rect->right - rect->left) / 2)
		return TRUE;
	else
		return FALSE;
}
/*
3-3에 이미지 사용
배경 이미지를 출력
도형대신 이미지(자동차)를 사용한다.
신호등 선택을 마우스로 한다.
도로는 4차선 좌2차선 우2차선으로 만들고 도로를 나타내는 직선을 그린다.
도로 가운데 건널목이 있고 건널목 앞에서 자동차는 일단 멈추고 다시 달린다.
*/