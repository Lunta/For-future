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
#define CYAN		RGB(0, 255, 255)
#define YELLOW		RGB(255, 228, 0)
#define MAGENTA		RGB(255, 0, 255)
#define RAINBOW		RGB(rand() % 256, rand() % 256, rand() % 256)
enum RGB {
	C = 0, M = 1, Y = 2, RAND = 3
};
HINSTANCE g_hInst;
LPCTSTR lpszClass = WIN_CLASSNAME;


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
float LengthPts(int x1, int y1, int x2, int y2);

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU4_2); // 메뉴 이름
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
	HBRUSH hBrush[6], oldBrush;
	static HBITMAP memBit;
	static RECT rc;
	static RECT larva[Size], boom[Size], item[Size], poprc;
	static POINT mpoint;
	static int ranX, ranY;
	static int color, speed, count, food, tail, timer, ic;
	static bool right, left, up, down, jump, start, grid, create, pop;
	static float x, y, s, r[Size];
	int i, j, icY, revicY;

	srand((unsigned)time(NULL));
	switch (iMessage) {
	case WM_CREATE:
		GetClientRect(hWnd, &rc);
		SetTimer(hWnd, 1, 30, NULL);
		SetTimer(hWnd, 2, 1500, NULL);
		speed = 30;
		poprc = {0, 0, Size, Size};
		ic = 0;
		count = 0;
		timer = 0;
		tail = 1;
		food = rand() % Size;
		mpoint.x = 0;
		mpoint.y = 0;
		color = C;
		right = left = up = down = jump = start = create = pop = FALSE;
		break;
	case WM_LBUTTONUP:
		mpoint.x = LOWORD(lParam);
		mpoint.y = HIWORD(lParam);
		icY = larva[0].top - larva[0].left;
		revicY = larva[0].top + larva[0].right;
		if (mpoint.y < mpoint.x + icY && mpoint.y > -mpoint.x + revicY) //right
		{
			right = TRUE;
			left = FALSE;
			up = FALSE;
			down = FALSE;
		}
		if (mpoint.y > mpoint.x + icY && mpoint.y < -mpoint.x + revicY) //left
		{
			right = FALSE;
			left = TRUE;
			up = FALSE;
			down = FALSE;
		}
		if (mpoint.y < mpoint.x + icY && mpoint.y < -mpoint.x + revicY) //up
		{
			right = FALSE;
			left = FALSE;
			up = TRUE;
			down = FALSE;
		}
		if (mpoint.y > mpoint.x + icY && mpoint.y > -mpoint.x + revicY) //down
		{
			right = FALSE;
			left = FALSE;
			up = FALSE;
			down = TRUE;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if (timer++ == 100000) timer = 0;
			if (larva[0].right  > rc.right - Width)
			{
				right = FALSE;
				left = TRUE;
			}
			else if (larva[0].left < rc.left)
			{
				left = FALSE;
				right = TRUE;
			}
			else if (larva[0].top < rc.top)
			{
				up = FALSE;
				down = TRUE;
			}
			else if (larva[0].bottom + Height > rc.bottom)
			{
				down = FALSE;
				up = TRUE;
			}

			if (right == 1)		OffsetRect(larva, speed, 0);
			else if (left == 1) OffsetRect(larva, -speed, 0);
			else if (up == 1)	OffsetRect(larva, 0, -speed);
			else if (down == 1) OffsetRect(larva, 0, speed);

			for (i = tail + 1; i > 0; i--)
			{
				larva[i].left = larva[i - 1].left;
				larva[i].top = larva[i - 1].top;
				larva[i].right = larva[i - 1].right;
				larva[i].bottom = larva[i - 1].bottom;
			}

			if (pop)
			{
				s = LengthPts(((larva[0].left + larva[0].right) / 2), ((larva[0].top + larva[0].bottom) / 2),
					((poprc.left + poprc.right) / 2), ((poprc.top + poprc.bottom) / 2));
				x = (((larva[0].left + larva[0].right) / 2) - ((poprc.left + poprc.right) / 2)) / s;
				y = (((larva[0].top + larva[0].bottom) / 2) - ((poprc.top + poprc.bottom) / 2)) / s;
				OffsetRect(&poprc, x * 15, y * 15);
			}

			for (i = 0; i < Size; i++)
				if (larva[0].left < item[i].right &&
					larva[0].right > item[i].left &&
					larva[0].top < item[i].bottom &&
					larva[0].bottom > item[i].top)
				{
					item[i].left = 0;
					item[i].top = 0;
					item[i].right = 0;
					item[i].bottom = 0;
					tail++;
					InflateRect(&larva[0], 1, 1);
					if (right == 1)
					{
						larva[tail].left = larva[tail - 1].left - Width;
						larva[tail].top = larva[tail - 1].top;
						larva[tail].right = larva[tail - 1].right - Width;
						larva[tail].bottom = larva[tail - 1].bottom;
					}
					else if (left == 1)
					{
						larva[tail].left = larva[tail - 1].left + Width;
						larva[tail].top = larva[tail - 1].top;
						larva[tail].right = larva[tail - 1].right + Width;
						larva[tail].bottom = larva[tail - 1].bottom;
					}
					else if (up == 1)
					{
						larva[tail].left = larva[tail - 1].left;
						larva[tail].top = larva[tail - 1].top - Height;
						larva[tail].right = larva[tail - 1].right;
						larva[tail].bottom = larva[tail - 1].bottom - Height;
					}
					else if (down == 1)
					{
						larva[tail].left = larva[tail - 1].left;
						larva[tail].top = larva[tail - 1].top + Height;
						larva[tail].right = larva[tail - 1].right;
						larva[tail].bottom = larva[tail - 1].bottom + Height;
					}
				}
			for (i = 0; i < Size; i++)
				if (larva[0].left < boom[i].right &&
					larva[0].right > boom[i].left &&
					larva[0].top < boom[i].bottom &&
					larva[0].bottom > boom[i].top)
				{
					boom[i].left = 0;
					boom[i].top = 0;
					boom[i].right = 0;
					boom[i].bottom = 0;
					larva[tail + 1].left = 0;
					larva[tail + 1].top = 0;
					larva[tail + 1].right = 0;
					larva[tail + 1].bottom = 0;
					larva[tail].left = 0;
					larva[tail].top = 0;
					larva[tail].right = 0;
					larva[tail].bottom = 0;
					tail--;
				}

			if (jump == TRUE && right == TRUE)
			{
				if (count < 3) OffsetRect(larva, 0, -Height);
				else if (count < 5) OffsetRect(larva, 0, Height);
				else if (count == 5)
				{
					jump = FALSE;
					count = 0;
				}
				count++;
			}
			else if (jump == TRUE && left == TRUE)
			{
				if (count < 3) OffsetRect(larva, 0, Height);
				else if (count < 5) OffsetRect(larva, 0, -Height);
				else if (count == 5)
				{
					jump = FALSE;
					count = 0;
				}
				count++;
			}
			else if (jump == TRUE && up == TRUE)
			{
				if (count < 3) OffsetRect(larva, Width, 0);
				else if (count < 5) OffsetRect(larva, -Width, 0);
				else if (count == 5)
				{
					jump = FALSE;
					count = 0;
				}
				count++;
			}
			else if (jump == TRUE && down == TRUE)
			{
				if (count < 3) OffsetRect(larva, -Width, 0);
				else if (count < 5) OffsetRect(larva, Width, 0);
				else if (count == 5)
				{
					jump = FALSE;
					count = 0;
				}
				count++;
			}
			break;
		case 2:
			if (create)
			{
				if (ic == food)
				{
					create = FALSE;
					break;
				}
				ranX = rand() % 300 + rand() % 300;
				ranY = rand() % 250 + rand() % 250;
				item[ic].left = ranX;
				item[ic].top = ranY;
				item[ic].right = Width + ranX;
				item[ic].bottom = Height + ranY;
			
				ranX = rand() % 300 + rand() % 300;
				ranY = rand() % 250 + rand() % 250;
				boom[ic].left = ranX;
				boom[ic].top = ranY;
				boom[ic].right = Width + ranX;
				boom[ic].bottom = Height + ranY;
				
				ic++;
				if (ic == 3) pop = true;
			}
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
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		hBrush[0] = CreateSolidBrush(RGB(255, 0, 0));
		hBrush[1] = CreateSolidBrush(RGB(0, 255, 0));
		hBrush[2] = CreateSolidBrush(CYAN);
		hBrush[3] = CreateSolidBrush(MAGENTA);
		hBrush[4] = CreateSolidBrush(YELLOW);
		hBrush[5] = CreateSolidBrush(RAINBOW);

		oldBrush = (HBRUSH)SelectObject(memdc, hBrush[1]);
		for (i = 0; i < food ; i++)
			Ellipse(memdc, item[i].left, item[i].top, item[i].right, item[i].bottom);

		oldBrush = (HBRUSH)SelectObject(memdc, hBrush[0]);
		for (i = 0; i < food ; i++)
			Ellipse(memdc, boom[i].left, boom[i].top, boom[i].right, boom[i].bottom);

		oldBrush = (HBRUSH)SelectObject(memdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
		for (i = 1; i < Size; i++) 
			Ellipse(memdc, larva[i].left, larva[i].top, larva[i].right, larva[i].bottom);

		if (color == C) oldBrush = (HBRUSH)SelectObject(memdc, hBrush[2]);
		else if (color == M) oldBrush = (HBRUSH)SelectObject(memdc, hBrush[3]);
		else if (color == Y) oldBrush = (HBRUSH)SelectObject(memdc, hBrush[4]);
		else if (color == RAND) oldBrush = (HBRUSH)SelectObject(memdc, hBrush[5]);
		Ellipse(memdc, larva[0].left, larva[0].top, larva[0].right, larva[0].bottom);
		oldBrush = (HBRUSH)SelectObject(memdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
		oldPen = (HPEN)SelectObject(memdc, hPen);
		if(left)
			Pie(memdc, larva[0].left, larva[0].top, larva[0].right, larva[0].bottom,
				((larva[0].left + larva[0].right) / 2) + ((larva[0].right - larva[0].left) / 2) * cos(1 - 0.7 * (timer % 2) + 3.14),
				((larva[0].top + larva[0].bottom) / 2) + ((larva[0].bottom - larva[0].top) / 2) * sin(1 - 0.7 * (timer % 2) + 3.14),
				((larva[0].left + larva[0].right) / 2) + ((larva[0].right - larva[0].left) / 2) * cos(-1 + 0.7 * (timer % 2) + 3.14),
				((larva[0].top + larva[0].bottom) / 2) + ((larva[0].bottom - larva[0].top) / 2) * sin(-1 + 0.7 * (timer % 2) + 3.14));
		else if (right)
			Pie(memdc, larva[0].left, larva[0].top, larva[0].right, larva[0].bottom,
			((larva[0].left + larva[0].right) / 2) + ((larva[0].right - larva[0].left) / 2) * cos(1 - 0.7 * (timer % 2)),
				((larva[0].top + larva[0].bottom) / 2) + ((larva[0].bottom - larva[0].top) / 2) * sin(1 - 0.7 * (timer % 2)),
				((larva[0].left + larva[0].right) / 2) + ((larva[0].right - larva[0].left) / 2) * cos(-1 + 0.7 * (timer % 2)),
				((larva[0].top + larva[0].bottom) / 2) + ((larva[0].bottom - larva[0].top) / 2) * sin(-1 + 0.7 * (timer % 2)));
		else if (up)
			Pie(memdc, larva[0].left, larva[0].top, larva[0].right, larva[0].bottom,
			((larva[0].left + larva[0].right) / 2) + ((larva[0].right - larva[0].left) / 2) * cos(1 - 0.7 * (timer % 2) - 1.57),
				((larva[0].top + larva[0].bottom) / 2) + ((larva[0].bottom - larva[0].top) / 2) * sin(1 - 0.7 * (timer % 2) - 1.57),
				((larva[0].left + larva[0].right) / 2) + ((larva[0].right - larva[0].left) / 2) * cos(-1 + 0.7 * (timer % 2) - 1.57),
				((larva[0].top + larva[0].bottom) / 2) + ((larva[0].bottom - larva[0].top) / 2) * sin(-1 + 0.7 * (timer % 2) - 1.57));
		else if (down)
			Pie(memdc, larva[0].left, larva[0].top, larva[0].right, larva[0].bottom,
			((larva[0].left + larva[0].right) / 2) + ((larva[0].right - larva[0].left) / 2) * cos(1 - 0.7 * (timer % 2) + 1.57),
				((larva[0].top + larva[0].bottom) / 2) + ((larva[0].bottom - larva[0].top) / 2) * sin(1 - 0.7 * (timer % 2) + 1.57),
				((larva[0].left + larva[0].right) / 2) + ((larva[0].right - larva[0].left) / 2) * cos(-1 + 0.7 * (timer % 2) + 1.57),
				((larva[0].top + larva[0].bottom) / 2) + ((larva[0].bottom - larva[0].top) / 2) * sin(-1 + 0.7 * (timer % 2) + 1.57));
		
		if (pop)
		{
			oldBrush = (HBRUSH)SelectObject(memdc, (HBRUSH)GetStockObject(GRAY_BRUSH));
			Ellipse(memdc, poprc.left, poprc.top, poprc.right, poprc.bottom);
			oldBrush = (HBRUSH)SelectObject(memdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
			Pie(memdc, poprc.left, poprc.top, poprc.right, poprc.bottom,
				((poprc.left + poprc.right) / 2) + ((poprc.right - poprc.left) / 2) * cos(1 - 0.7 * (timer % 2) + atan2(y, x)),
				((poprc.top + poprc.bottom) / 2) + ((poprc.bottom - poprc.top) / 2) * sin(1 - 0.7 * (timer % 2) + atan2(y, x)),
				((poprc.left + poprc.right) / 2) + ((poprc.right - poprc.left) / 2) * cos(-1 + 0.7 * (timer % 2) + atan2(y, x)),
				((poprc.top + poprc.bottom) / 2) + ((poprc.bottom - poprc.top) / 2) * sin(-1 + 0.7 * (timer % 2) + atan2(y, x)));
		}

		if (start && !create)
		{
			for (i = 0; i < food; i++)
				if (item[i].left == 0 && item[i].top == 0 && item[i].right == 0 && item[i].bottom == 0) count++;
			if (count == food)
				if (item[0].left == 0 && item[0].top == 0 && item[0].right == 0 && item[0].bottom == 0)
				{
					KillTimer(hWnd, 1);
					TextOut(memdc, WIN_Width / 2, WIN_Height / 2, TEXT("You Win!"), lstrlen(TEXT("You Win!")));
					int answer = MessageBox(hWnd, L"게임을 끝내겠습니까 ? ", L"끝내기 선택", MB_YESNOCANCEL);
					if (answer == IDYES)
						PostQuitMessage(0);
				}
			count = 0;
		}
		if (start)
		{
			if (larva[0].left == 0 && larva[0].top == 0 && larva[0].right == 0 && larva[0].bottom == 0)
			{
				KillTimer(hWnd, 1);
				TextOut(memdc, WIN_Width / 2, WIN_Height / 2, TEXT("GameOver!"), lstrlen(TEXT("GameOver!")));
				int answer = MessageBox(hWnd, L"게임을 끝내겠습니까 ? ", L"끝내기 선택", MB_YESNOCANCEL);
				if (answer == IDYES)
					PostQuitMessage(0);
			}
		}
		if (grid)
		{
			for (int i = 0; i < 30; i++)
				for (int j = 0; j < 40; j++)
				{
					RECT temp = { (rc.right / 40) * j, (rc.bottom / 30) * i, (rc.right / 40) *(j + 1), (rc.bottom / 30)*(i + 1) };
					FrameRect(memdc, &temp, (HBRUSH)GetStockObject(BLACK_BRUSH));
				}
		}
		// hdc에 복사
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, memdc, 0, 0, SRCCOPY);

		SelectObject(hdc, oldPen);
		SelectObject(hdc, oldBrush);
		for (i = 0; i < 6; i++)
			DeleteObject(hBrush[i]);
		DeleteObject(hPen);

		SelectObject(memdc, NULL);
		DeleteDC(memdc);
		DeleteObject(memBit);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_CONTROL) //jump
		{
			jump = TRUE;
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_GAME_START2:
			SetTimer(hWnd, 1, 100, NULL);
			larva[0].left = 0;
			larva[0].top = 0;
			larva[0].right = Width;
			larva[0].bottom = Height;

			larva[1].left = -Width;
			larva[1].top = 0;
			larva[1].right = 0;
			larva[1].bottom = Height;
			count = 0;
			tail = 1;
			
			right = left = up = down = jump = start = pop = FALSE;
			start = create = TRUE;
			break;
		case ID_GAME_END2:
			KillTimer(hWnd, 1);
			PostQuitMessage(0);
			return 0;
			break;
		case ID_FOOD_10:
			food = 10;
			break;
		case ID_FOOD_20:
			food = 20;
			break;
		case ID_FOOD_30:
			food = 30;
			break;
		case ID_COLOR_CYAN:
			color = C;
			break;
		case ID_COLOR_MAGENTA:
			color = M;
			break;
		case ID_COLOR_YELLOW:
			color = Y;
			break;
		case ID_COLOR_RANDOM:
			color = RAND;
			break;
		case ID_GRID_ON2:
			grid = true;
			break;
		case ID_GRID_OFF2:
			grid = false;
			break;
		}
		break;
	case WM_CHAR:
		if (wParam == ']') //+
		{
			KillTimer(hWnd, 1);
			if (speed > 10) speed -= 10;
			SetTimer(hWnd, 1, speed, NULL);
		}
		else if (wParam == '[') //-
		{
			KillTimer(hWnd, 1);
			speed += 10;
			SetTimer(hWnd, 1, speed, NULL);
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
float LengthPts(int x1, int y1, int x2, int y2)
{
	return (sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
}
/*
–연습 문제 3-5를 이용하여 팩맨 만들기
•내용
–함수 Pie (hdc, left, top, right, bottom, xStart, yStart, xEnd, yEnd)를 사용하여 애벌레를 그릮다.
–애벌레의 머리가 팩맨 형태이다.
•Pie (hdc, 100, 100, 200, 200, 200, 110, 200, 190);
•Pie (hdc, 200, 200, 300, 300, 300, 240, 300, 260);
•팩맨은 입을 움직이며 계속 이동핚다.
내용
–메뉴를 만든다.
•Game: Start / End
–팩맨의 이동을 시작핚다.
•Color: Cyan/Magenta/Yellow/Random
–팩맨의 색상을 결정핚다.
•먹이/폭탄: 10 / 20 / 30 (먹이와 폭탄의 개수 결정)
–먹이의 개수를 정핚다.
•Grid: On / Off
–바탕 화면에 그리드를 그릮다.
–게임을 시작하면 팩맨이 이동하고 화살표 키보드를 이용하여 팩맨의 방향을 좌우상하로 이동핚다.
–특정시간에 먹이가 임의의 위치에 나타난다.
–팩맨이 먹이나 폭탄을 먹으면 변화가 생긴다.
•예를들면, 팩맨의 이동 속도가 빨라짂다.
•팩맨의 크기가 커짂다.
•팩맨이 입을 크게 벌릮다.
-새로운 팩맨이 나타나면 기존의 팩맨을 향하여 이동핚다.
–먹이를 다 먹으면 프로그램 종료 메시지 박스가 뜬다.
*/