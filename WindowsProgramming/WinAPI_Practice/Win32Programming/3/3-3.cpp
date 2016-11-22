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

#define Width 40
#define Height 40
#define FigureSize 100

HINSTANCE g_hInst;
LPCTSTR lpszClass = WIN_CLASSNAME;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

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
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hBrush[3], oldBrush;
	HPEN hPen, oldPen;
	RECT rc;
	static RECT figure[2][3];
	static BOOL signR, signB, signY, start;
	static int x, y, speed[3];
	int i;
	srand((unsigned)time(NULL));

	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd, 0, 100, NULL);
		SetTimer(hWnd, 1, 50, NULL);
		SetTimer(hWnd, 2, 30, NULL);
		signR = signB = signY = start = FALSE;

		break;
	case WM_TIMER:
		if (signR == FALSE) {
			GetWindowRect(hWnd, &rc);
			switch (wParam)
			{
			case 0:
				OffsetRect(figure[0], 5, 0);

				figure[1][0].top = figure[0][0].top;
				figure[1][0].bottom = figure[0][0].bottom;
				figure[1][0].left = 0;
				if (rc.right < figure[0][0].right)
				{
					figure[1][0].right = figure[0][0].right - rc.right;

					if (rc.right < figure[0][0].left)
					{
						figure[0][0].right = figure[1][0].right - 1;
						figure[0][0].left = 0;
						figure[1][0].right = 0;
					}
				}
				break;
			case 1: 
				OffsetRect(figure[0] + 1, -5, 0);
				figure[1][1].top = figure[0][1].top;
				figure[1][1].bottom = figure[0][1].bottom;
				figure[1][1].right = rc.right;
				if (0 > figure[0][1].left)
				{
					figure[1][1].left = rc.right + figure[0][1].left;

					if (0 > figure[0][1].right)
					{
						figure[0][1].right = rc.right;
						figure[0][1].left = figure[1][1].left;
						figure[1][1].left = rc.right;
					}
				}
				break;
			case 2: 
				OffsetRect(figure[0] + 2, 5, 0);
				figure[1][2].top = figure[0][2].top;
				figure[1][2].bottom = figure[0][2].bottom;
				figure[1][2].left = 0;
				if (rc.right < figure[0][2].right)
				{
					figure[1][2].right = figure[0][2].right - rc.right;

					if (rc.right < figure[0][2].left)
					{
						figure[0][2].right = figure[1][2].right - 1;
						figure[0][2].left = 0;
						figure[1][2].right = 0;
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
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		hBrush[0] = CreateSolidBrush(RGB(255, 0, 0));  //R
		hBrush[1] = CreateSolidBrush(RGB(0, 0, 255));  //B
		hBrush[2] = CreateSolidBrush(RGB(255, 255, 0));//Y

		if (start == FALSE)
		{
			for (i = 0; i < 3; i++)
			{
				KillTimer(hWnd, i);
				speed[i] = rand() % 100;
				SetTimer(hWnd, i, speed[i], NULL);

				figure[0][i].left = 0;
				figure[0][i].top = 100 + i * 200;
				figure[0][i].right = 20 + (rand() & 100);
				figure[0][i].bottom = i * 200 + (rand() & 100);
			}
			start = TRUE;
		}
		oldBrush = (HBRUSH)SelectObject(hdc, (HBRUSH)GetStockObject(GRAY_BRUSH));
		for (i = 0; i < 3; i++)
		{
			Rectangle(hdc, figure[1][i].left, figure[1][i].top, figure[1][i].right, figure[1][i].bottom);
			Rectangle(hdc, figure[0][i].left, figure[0][i].top, figure[0][i].right, figure[0][i].bottom);
		}
		Rectangle(hdc, 0, 0, 3*Width, Height);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush[1]);
		Ellipse(hdc, 0, 0, Width, Height);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush[2]);
		Ellipse(hdc, Width, 0, 2 * Width, Height);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush[0]);
		Ellipse(hdc, 2 * Width, 0, 3 * Width, Height);

		if (signB == TRUE)
		{
			oldPen = (HPEN)SelectObject(hdc, hPen);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[1]);
			Ellipse(hdc, 0, 0, Width, Height);
		}
		else if (signY == TRUE)
		{
			oldPen = (HPEN)SelectObject(hdc, hPen);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[2]);
			Ellipse(hdc, Width, 0, 2*Width, Height);
		}
		else if (signR == TRUE)
		{
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[0]);
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Ellipse(hdc, 2*Width, 0, 3*Width, Height);
		}

		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		for (i = 0; i < 3; i++)
			DeleteObject(hBrush[i]);
		DeleteObject(hPen);

		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RIGHT)
		{

		}

		break;
	case WM_CHAR:
		if (wParam == 'b' || wParam == 'B') // 이동시작
		{
			if (signB == TRUE) signB = FALSE;
			else
			{
				signB = TRUE;
				signR = FALSE;
				signY = FALSE;
			}
		}
		else if (wParam == 'y' || wParam == 'Y') //3초후 정지
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
		else if (wParam == 'r' || wParam == 'R') //정지
		{
			if (signR == TRUE) signR = FALSE;
			else
			{
				signR = TRUE;
				signY = FALSE;
				signB = FALSE;
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		for (i = 0; i < 3; i ++)
			KillTimer(hWnd, i);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
/*
3-3
신호등.
화면을 y값으로 3등분, 각 등분에 임의의 크기 사각형을 그린다.
각 도형의 이동속도는 다르다.
맨 위의 사각형은 ->이동 중간은 <- 아래는 ->
파노빨신호등
b/B 이동시작
y/Y 3초후 정지
r/R 바로정지
이동속도는 각각 다름
가장자리에 도달하면 반대편에서 나타난다. 화면에 안그려지는 일부분의 사각형을 반대편에 출력
*/