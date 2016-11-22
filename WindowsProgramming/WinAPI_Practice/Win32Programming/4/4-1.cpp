#include <windows.h> 
#include <tchar.h>
#include <ctime>
#include <math.h>
#include "resource.h"

#define WIN_CLASSNAME TEXT("Menu")
#define WIN_TITLENAME TEXT("Menu")
#define WIN_Width 800
#define WIN_Height 600
#define WIN_XPOS 0
#define WIN_YPOS 0

#define Width 30
#define Height 30
#define BlockNum 10
#define BlockLine 2

enum RGB {
	R = 0, G = 1, B = 2
};

enum BLOCK_STATE
{
	DESTROY = 0, NEW = 2
};

typedef struct BLOCK
{
	RECT rc;
	int hp = NEW;
}Block;

typedef struct vector
{
	float x;
	float y;
	float speed;
}Ballvector;

HINSTANCE g_hInst;
LPCTSTR lpszClass = WIN_CLASSNAME;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

BOOL InCircle(RECT * rect, POINT * mpoint);
BOOL CheckCrash(float cx, float cy, float cr, int hp, const RECT * rect, Ballvector * bvector);
float LengthPts(int x1, int y1, int x2, int y2);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG Message;
	WNDCLASS WndClass; //구조체 정의
	RECT rc = { 0, 0, WIN_Width, WIN_Height };
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_BORDER | WS_THICKFRAME ;				
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0; // O/S 사용 여분 메모리(Class)
	WndClass.cbWndExtra = 0; // O/S 사용 여분 메모리(Window)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서 유형
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //아이콘유형 WndClass.hIconSM : 작은아이콘
	WndClass.hInstance = hInstance; //응용 프로그램 ID
	WndClass.lpfnWndProc = (WNDPROC)WndProc; // 프로시저 함수명
	WndClass.lpszClassName = lpszClass; // 클래스 이름
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU4_1); // 메뉴 이름
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
	HBRUSH hBrush, oldBrush;
	HPEN hPen[2], oldPen;
	static RECT rc;
	static HBITMAP memBit;
	static Block block[BlockLine][BlockNum];
	static Ballvector bvector;
	static RECT ball, bar;
	static POINT mpoint;
	static int crackcount, destroycount, oldX, oldY, startX, startY, count, color;
	static bool start, end, move, drag, grid;
	TCHAR str[50];
	int i, j, check = 0, endX, endY;

	srand((unsigned)time(NULL));
	GetWindowRect(hWnd, &rc);

	switch (iMessage) {
	case WM_CREATE:
		GetClientRect(hWnd, &rc);
		SetTimer(hWnd, 1, 50, NULL);
		crackcount = 0;
		destroycount = 0;
		drag = move = end = start= grid = FALSE;
		count = 0;
		color = R;
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_GAME_START:
			if (end == TRUE) SetTimer(hWnd, 1, 50, NULL);
			drag = move = end = start = FALSE;
			break;
		case ID_GAME_END:
			end = TRUE;
			break;
		case ID_SPEED_SLOW:
			bvector.speed = 4;
			break;
		case ID_SPEED_MIDIUM:
			bvector.speed = 15;
			break;
		case ID_SPEED_FAST:
			bvector.speed = 30;
			break;
		case ID_BALL_SMALL:
			ball.left += 5;
			ball.top += 5;
			ball.right -= 5;
			ball.bottom -= 5;
			break;
		case ID_BALL_BIG:
			ball.left -= 5;
			ball.top -= 5;
			ball.right += 5;
			ball.bottom += 5;
			break;
		case ID_COLOR_RED:
			color = R;
			break;
		case ID_COLOR_GREEN:
			color = G;
			break;
		case ID_COLOR_BLUE:
			color = B;
			break;
		case ID_GRID_ON:
			grid = true;
			break;
		case ID_GRID_OFF:
			grid = false;
			break;
		}
		break;
	case WM_LBUTTONDOWN: // 버튺을 누르면 드래그 동작 시작
		mpoint.x = LOWORD(lParam);
		mpoint.y = HIWORD(lParam);
		bar.left = mpoint.x - rc.right / (BlockNum * 2);
		bar.right = mpoint.x + rc.right / (BlockNum * 2);
		if (move == FALSE)
		{
			ball.left = (bar.left + bar.right) / 2 - Width / 2;
			ball.top = rc.bottom - Height * 2 - 50;
			ball.right = (bar.left + bar.right) / 2 + Width / 2;
			ball.bottom = rc.bottom - Height - 50;
			if (InCircle(&ball, &mpoint))
				drag = TRUE;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hWnd);
		if (drag)
		{ // 흰 바탕
			SetROP2(hdc, R2_XORPEN); // 펜의 XOR 연산
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN)); // 흰 펜
																// 흰 바탕 XOR 흰 펜 = 검은색 펜
			startX = mpoint.x;
			startY = mpoint.y;
			endX = LOWORD(lParam);
			endY = HIWORD(lParam);
			MoveToEx(hdc, startX, startY, NULL);
			LineTo(hdc, oldX, oldY); // 지우기 : 흰 바탕 XOR 검은 펜 = 흰 선
			MoveToEx(hdc, startX, startY, NULL);
			LineTo(hdc, endX, endY); // 그리기 : 흰 바탕 XOR 흰 펜 = 검은 선
			oldX = endX; oldY = endY; // 현 지점을 이젂 지점으로 설정
		}
		ReleaseDC(hWnd, hdc);
		break;
	case WM_LBUTTONUP: // 버튺을 놓으면 드래그 종료
		if (drag)
		{
			move = TRUE;
			mpoint.x = LOWORD(lParam);
			mpoint.y = HIWORD(lParam);
			bvector.speed = LengthPts(((ball.left + ball.right) / 2), ((ball.top + ball.bottom) / 2), mpoint.x, mpoint.y);
			bvector.x = (mpoint.x - ((ball.left + ball.right) / 2)) / bvector.speed;
			bvector.y = (mpoint.y - ((ball.top + ball.bottom) / 2)) / bvector.speed;
			bvector.speed = bvector.speed / 30;
			drag = FALSE;
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			InvalidateRect(hWnd, NULL, FALSE);
			if (move == TRUE)
			{
				OffsetRect(&ball, bvector.x * bvector.speed, bvector.y * bvector.speed);

				if (ball.right > rc.right || ball.left < rc.left)
					bvector.x = -bvector.x;
				if ((ball.top < rc.top) || (ball.bottom >= bar.top - (ball.right - ball.left) / 2 &&
					ball.right > bar.left - (ball.right - ball.left) / 2 &&
					ball.left < bar.right + (ball.right - ball.left) / 2 && bvector.y > 0))
					bvector.y = -bvector.y;

				for (i = 0; i < BlockLine; i++)
					for (j = 0; j < BlockNum; j++)
						if (CheckCrash((ball.left + ball.right) / 2, (ball.top + ball.bottom) / 2,
							(ball.right - ball.left) / 2, block[i][j].hp, &block[i][j].rc, &bvector))
						{
							block[i][j].hp--;
							break;
						}


				for (i = 0; i < BlockLine; i++)
					for (j = 0; j < BlockNum; j++)
						if (block[i][j].hp == 1) count++;
				crackcount = count;
				count = 0;

				for (i = 0; i < BlockLine; i++)
					for (j = 0; j < BlockNum; j++)
						if (block[i][j].hp == DESTROY) count++;
				destroycount = count;
				count = 0;

				if (destroycount == BlockLine * BlockNum) end = TRUE;
				if (bar.bottom < ball.bottom) end = TRUE;
			}

			break;
		case 2:
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		memBit = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		SelectObject(memdc, memBit);
		FillRect(memdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		//
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		hPen[0] = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		hPen[1] = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		if (start == FALSE)
		{
			bar.left = 0;
			bar.top = rc.bottom - Height - 50;
			bar.right = rc.right / BlockNum;
			bar.bottom = rc.bottom - 50;

			ball.left = (bar.left + bar.right) / 2 - Width / 2;
			ball.top = rc.bottom - Height * 2 - 50;
			ball.right = (bar.left + bar.right) / 2 + Width / 2;
			ball.bottom = rc.bottom - Height - 50;

			for (i = 0; i < BlockLine; i++)
				for (j = 0; j < BlockNum; j++)
				{
					block[i][j].rc.left = 0 + (rc.right / BlockNum) * j;
					block[i][j].rc.top = 0 + Height * i;
					block[i][j].rc.right = (rc.right / BlockNum) * (j + 1);
					block[i][j].rc.bottom = Height * (i + 1);
					block[i][j].hp = NEW;
				}
			start = TRUE;
		}
		for (i = 0; i < BlockLine; i++)
			for (j = 0; j < BlockNum; j++)
			{
				switch (block[i][j].hp)
				{
				case NEW:
					oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
					Rectangle(memdc, block[i][j].rc.left, block[i][j].rc.top, block[i][j].rc.right, block[i][j].rc.bottom);
					break;
				case 1: //Crack
					oldBrush = (HBRUSH)SelectObject(memdc, GetStockObject(GRAY_BRUSH));
					Rectangle(memdc, block[i][j].rc.left, block[i][j].rc.top, block[i][j].rc.right, block[i][j].rc.bottom);
					break;
				}
			}
		if (color == R)
		{
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(memdc, ball.left, ball.top, ball.right, ball.bottom);
		}
		else if (color == G)
		{
			oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));
			Ellipse(memdc, ball.left, ball.top, ball.right, ball.bottom);
		}
		else if (color == B)
		{
			oldBrush = (HBRUSH)SelectObject(memdc, GetStockObject(GRAY_BRUSH));
			Ellipse(memdc, ball.left, ball.top, ball.right, ball.bottom);
		}
		oldBrush = (HBRUSH)SelectObject(memdc, GetStockObject(WHITE_BRUSH));
		oldPen = (HPEN)SelectObject(memdc, hPen[0]);
		Rectangle(memdc, bar.left, bar.top, bar.right, bar.bottom);

		if (grid)
		{
			for(int i = 0; i < 30; i++)
				for (int j = 0; j < 40; j++)
				{
					RECT temp = { (rc.right / 40) * j, (rc.bottom / 30) * i, (rc.right / 40) *(j+1), (rc.bottom / 30)*(i + 1) };
					FrameRect(memdc, &temp, (HBRUSH)GetStockObject(BLACK_BRUSH));
				}
		}
		wsprintf(str, L"Crack : %d, Destroy : %d", crackcount, destroycount);
		TextOut(memdc, 0, 0, str, lstrlen(str));
		if (end == TRUE)
		{
			KillTimer(hWnd, 1);
			wsprintf(str, L"Game Over. Score : %d", destroycount);
			TextOut(memdc, WIN_Width / 2 - 50, WIN_Height / 2 - 50, str, lstrlen(str));
		}
		if (drag)
		{
			oldPen = (HPEN)SelectObject(hdc, hPen[1]);
			MoveToEx(memdc, startX, startY, NULL); // 이동하고 선으로 연결
			LineTo(memdc, oldX, oldY);
		}
		// hdc에 복사
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, memdc, 0, 0, SRCCOPY);

		SelectObject(hdc, oldPen);
		SelectObject(hdc, oldBrush);
		DeleteObject(hPen[0]);
		DeleteObject(hPen[1]);
		DeleteObject(hBrush);

		SelectObject(memdc, NULL);
		DeleteDC(memdc);
		DeleteObject(memBit);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		break;
	case WM_CHAR:
		if (wParam == ']') //+
			if (bvector.speed > 30) bvector.speed = 30;
			else bvector.speed += 2;
		else if (wParam == '[') //- 
			if (bvector.speed < 0) bvector.speed = 0;
			else bvector.speed -= 2;
		else if (wParam == 'r')
		{
			if (end == TRUE) SetTimer(hWnd, 1, 50, NULL);
			drag = move = end = start = FALSE;
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
BOOL InCircle(RECT * rect, POINT * mpoint)
{
	if (LengthPts((rect->left + rect->right) / 2, (rect->top + rect->bottom) / 2, mpoint->x, mpoint->y)
		< (rect->right - rect->left) / 2)
		return TRUE;
	else
		return FALSE;
}
BOOL CheckCrash(float cx, float cy, float cr, int hp, const RECT * rect, Ballvector * bvector)
{
	int nCenterX = static_cast<int> (cx);
	int nCenterY = static_cast<int> (cy);
	int nRadius = static_cast<int> (cr);
	float temp;

	if ((rect->left <= nCenterX && nCenterX <= rect->right) ||
		(rect->top <= nCenterY && nCenterY <= rect->bottom))
	{
		RECT rcEx = {
			rect->left - nRadius,
			rect->top - nRadius,
			rect->right + nRadius,
			rect->bottom + nRadius,
		};

		if ((rcEx.left < nCenterX && nCenterX < rcEx.right) &&
			(rcEx.top < nCenterY && nCenterY < rcEx.bottom) && hp != DESTROY)
		{
			if (rcEx.top < nCenterY && nCenterY < rcEx.bottom)
			{
				bvector->y = -bvector->y;
				return TRUE;
			}
			else if (rcEx.left < nCenterX && nCenterX < rcEx.right)
			{
				bvector->x = -bvector->x;
				return TRUE;
			}
		}
	}
	else if (hp != DESTROY)
	{
		if (LengthPts(cx, cy, (float)rect->left, (float)rect->top) < cr)
		{
			temp = bvector->x;
			bvector->x = bvector->y;
			bvector->y = -temp;
			return TRUE;
		}
		else if (LengthPts(cx, cy, (float)rect->left, (float)rect->bottom) < cr)
		{
			bvector->y = -bvector->y;
			return TRUE;
		}
		else if (LengthPts(cx, cy, (float)rect->right, (float)rect->top) < cr)
		{
			temp = bvector->x;
			bvector->x = -bvector->y;
			bvector->y = temp;
			return TRUE;
		}
		else if (LengthPts(cx, cy, (float)rect->right, (float)rect->bottom) < cr)
		{
			bvector->y = -bvector->y;
			return TRUE;
		}
	}
	return FALSE;
}
/*–Game: Start/End
•공이 이동하기 시작/끝낸다
–Speed: Slow/Medium/Fast
•원이 천천히/중간속도/빠르게 이동하면서 벽에 맞으면 튀어서 다른 방향으로 이동핚다.
–Ball: Small/Big
•공이 작거나/큰 크기로 그려짂다.
–Color: Red / Green / Blue
•공의 색상을 변경핚다.
–그리드: 켜기 / 끄기
•화면에 모눈 종이 형태의 그리드를 그리거나 지우기*/