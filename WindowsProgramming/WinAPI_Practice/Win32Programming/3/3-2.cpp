#include <windows.h> 
#include <tchar.h>
#include <ctime>
#include <math.h>

#define WIN_CLASSNAME TEXT("Timer")
#define WIN_TITLENAME TEXT("Timer")
#define WIN_XPOS 0 
#define WIN_YPOS 0 
#define WIN_Width 800 
#define WIN_Height 600

#define Width 5
#define Height 5
#define FigureSize 100

HINSTANCE g_hInst;
LPCTSTR lpszClass = WIN_CLASSNAME;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
void inputrect(RECT * figure, int figureWH);

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
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hBrush[2], oldBrush;
	RECT rc;
	RECT figure[4];
	POINT triangle[4][3];
	static BOOL changec, changem, changer, changet;
	static int x, y;
	static float radian;
	int i;

	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 30, NULL);
		changec = changem = changer = changet = FALSE;
		radian = 0;
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			GetWindowRect(hWnd, &rc);
			switch(changec)
			{
			case FALSE: //changec == FALSE
				if (changer == FALSE && changet == FALSE)
				{
					x = (int)((FigureSize / 2) * cos(radian));
					y = (int)((FigureSize / 2) * sin(radian));
					radian += 0.1;
				}
				else if (changer == TRUE)
				{
					if (x <= -(FigureSize / 2) && y > -(FigureSize / 2)) y -= (FigureSize / 20);
					else if (x < (FigureSize / 2) && y <= -(FigureSize / 2)) x += (FigureSize / 20);
					else if (x >= (FigureSize / 2) && y < (FigureSize / 2)) y += (FigureSize / 20);
					else if (x > -(FigureSize / 2) && y >= (FigureSize / 2)) x -= (FigureSize / 20);
					else
					{
						x = (FigureSize / 2);
						y = (FigureSize / 2);
					}
				}
				else if (changet == TRUE)
				{ 
					if (x > -(FigureSize / 2) && y >= (FigureSize / 2)) x -= (FigureSize / 20);
					else if (x >= -(FigureSize / 2) && x < 0 && y > -(FigureSize / 2))
					{
						y -= (FigureSize / 10);
						x += (FigureSize / 20);
					}
					else if (x >= 0 && x < (FigureSize / 2) && y < (FigureSize / 2))
					{
						y += (FigureSize / 10);
						x += (FigureSize / 20);
					}
					else
					{
						x = (FigureSize / 2);
						y = (FigureSize / 2);
					}
				}
				break;
			case TRUE: // changec == TRUE
				if (changer == FALSE && changet == FALSE)
				{
					x = (int)((FigureSize / 2) * cos(radian));
					y = (int)((FigureSize / 2) * sin(radian));
					radian -= 0.1;
				}
				else if (changer == TRUE)
				{
					if (x <= -(FigureSize / 2) && y < (FigureSize / 2)) y += (FigureSize / 20);
					else if (x > -(FigureSize / 2) && y <= -(FigureSize / 2)) x -= (FigureSize / 20);
					else if (x >= (FigureSize / 2) && y > -(FigureSize / 2)) y -= (FigureSize / 20);
					else if (x < (FigureSize / 2) && y >= (FigureSize / 2)) x += (FigureSize / 20);
					else
					{
						x = (FigureSize / 2);
						y = (FigureSize / 2);
					}
				}
				else if (changet == TRUE)
				{
					if (x < (FigureSize / 2) && y >= (FigureSize / 2)) x += (FigureSize / 20);
					else if (x >= -(FigureSize / 2) && x <= 0 && y < (FigureSize / 2))
					{
						y += (FigureSize / 10);
						x -= (FigureSize / 20);
					}
					else if (x > 0 && x <= (FigureSize / 2) && y > -(FigureSize / 2))
					{
						y -= (FigureSize / 10);
						x -= (FigureSize / 20);
					}
					else
					{
						x = (FigureSize / 2);
						y = (FigureSize / 2);
					}
				}
				break;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 2: break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hBrush[0] = CreateSolidBrush(RGB(255, 0, 0));
		hBrush[1] = CreateSolidBrush(RGB(0, 255, 0));
	
		if (changer == FALSE && changet == FALSE)
		{
			inputrect(figure, FigureSize);
			for (i = 0; i < 4; i++)
				Ellipse(hdc, figure[i].left, figure[i].top, figure[i].right, figure[i].bottom);
		}
		else if (changer == TRUE)
		{
			inputrect(figure, FigureSize);
			for (i = 0; i < 4; i++)
				Rectangle(hdc, figure[i].left, figure[i].top, figure[i].right, figure[i].bottom);
		}
		else if (changet == TRUE)
		{
			inputrect(figure, FigureSize);
			for (i = 0; i < 4; i++)
			{
				triangle[i][0].x = figure[i].left + (figure[i].right - figure[i].left) / 2;
				triangle[i][0].y = figure[i].top;
				triangle[i][1].x = figure[i].left;
				triangle[i][1].y = figure[i].bottom;
				triangle[i][2].x = figure[i].right;
				triangle[i][2].y = figure[i].bottom;
			}
			for (i = 0; i < 4; i++)
				Polygon(hdc, triangle[i], 3);
		}
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush[0]);
		inputrect(figure, 10);
		for (i = 0; i < 4; i++)
			Ellipse(hdc, figure[i].left, figure[i].top, figure[i].right, figure[i].bottom);

		oldBrush = (HBRUSH)SelectObject(hdc, hBrush[1]);
		if (changem == TRUE)
		{
			for (i = 0; i < 4; i++)
				Rectangle(hdc, figure[i].left + x - Width / 2, figure[i].top + y - Height / 2,
					figure[i].right + x + Width / 2, figure[i].bottom + y + Height / 2);
		}
		else
		{
			for (i = 0; i < 4; i++)
				Ellipse(hdc, figure[i].left + x - Width / 2, figure[i].top + y - Height / 2,
					figure[i].right + x + Width / 2, figure[i].bottom + y + Height / 2);
		}

		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush[0]);
		DeleteObject(hBrush[1]);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RIGHT)
		{
			
		}
		
		break;
	case WM_CHAR:
		if (wParam == 'c' || wParam == 'C') // 회전방향 변경cmrtq
		{
			if (changec == TRUE) changec = FALSE;
			else changec = TRUE;
		}
		else if (wParam == 'm' || wParam == 'M') //회전원 변경
		{
			if(changem == TRUE) changem = FALSE;
			else changem = TRUE;
		}
		else if (wParam == 'r' || wParam == 'R') //사각형
		{
			if (changer == TRUE) changer = FALSE;
			else
			{
				changer = TRUE;
				changet = FALSE;
			}
		}
		else if (wParam == 't' || wParam == 'T') //삼각형
		{
			if (changet == TRUE) changet = FALSE;
			else
			{
				changet = TRUE;
				changer = FALSE;
			}
		}
		else if (wParam == 'q' || wParam == 'Q') //종료
		{
			KillTimer(hWnd, 1);
			PostQuitMessage(0);
			return 0;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void inputrect(RECT * figure, int figureWH)
{
	figure[0].left = WIN_Width / 4 - figureWH / 2;
	figure[0].top = WIN_Height / 4 - figureWH / 2;
	figure[0].right = WIN_Width / 4 + figureWH / 2;
	figure[0].bottom = WIN_Height / 4 + figureWH / 2;

	figure[1].left = 3 * WIN_Width / 4 - figureWH / 2;
	figure[1].top = WIN_Height / 4 - figureWH / 2;
	figure[1].right = 3 * WIN_Width / 4 + figureWH / 2;
	figure[1].bottom = WIN_Height / 4 + figureWH / 2;

	figure[2].left = WIN_Width / 4 - figureWH / 2;
	figure[2].top = 3 * WIN_Height / 4 - figureWH / 2;
	figure[2].right = WIN_Width / 4 + figureWH / 2;
	figure[2].bottom = 3 * WIN_Height / 4 + figureWH / 2;

	figure[3].left = 3 * WIN_Width / 4 - figureWH / 2;
	figure[3].top = 3 * WIN_Height / 4 - figureWH / 2;
	figure[3].right = 3 * WIN_Width / 4 + figureWH / 2;
	figure[3].bottom = 3 * WIN_Height / 4 + figureWH / 2;
}
/*
궤도를 따라 공전하는 원 만들기
화면을 사등분 하여 각 등분의 중앙에 빨갂색 원을 그린다.
•각각의 빨갂색 원을 중심으로 그 주위를 임의의 반지름을 가짂 원의 궤도를 그리고 그 궤도를 따라 다양핚 크기와 색의 원이 다양핚 타이머에 따라 회젂 핚다. 회젂 방향은 시계방향과 반시계방향이 모두 있다.
•다음의 명령어를 실행핚다.
•c/C: 방향을 거꾸로 이동핚다 (시계 → 반시계, 반시계 → 시계)
•m/M: 이동하는 회젂 도형이 사각형으로 바뀌어서 이동핚다.
•r/R: 배경 도형이 사각형이 된다.
•t/T: 배경 도형이 삼각형이 된다.
•q: 프로그램이 종료
•원의 좌표값 구하기
•sin(), cos()함수 사용 (#include <math.h>)
•위의 sin, cos 함수는 라디언 값을 인자로 받음
*/