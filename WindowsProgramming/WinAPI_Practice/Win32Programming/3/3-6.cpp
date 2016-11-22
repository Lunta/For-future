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

#define Width 50
#define Height 50
#define FigureNum 20

HINSTANCE g_hInst;
LPCTSTR lpszClass = WIN_CLASSNAME;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL InCircle(RECT * rect, POINT * mpoint);
BOOL CheckCrashCircle(RECT * rect1, RECT * rect2);
float LengthPts(int x1, int y1, int x2, int y2);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG Message;
	WNDCLASS WndClass; //구조체 정의
	RECT rc = { 0, 0, WIN_Width, WIN_Height };
	DWORD dwStyle =
		WS_OVERLAPPED 	// 디폴트 윈도우. 타이틀 바와 크기 조절이 안되는 경계선을 가진다. 아무런 스타일도 주지 않으면 이 스타일이 적용된다.
		| WS_CAPTION 		// 타이틀 바를 가진 윈도우를 만들며 WS_BORDER 스타일을 포함한다.
		| WS_SYSMENU		// 시스템 메뉴를 가진 윈도우를 만든다.
		| WS_MINIMIZEBOX	// 최소화 버튼을 만든다.
		| WS_BORDER
		| WS_THICKFRAME
		;				/*====•윈도우 스타일============================================================
						•WS_HSCROLL / WS_VSCROLL: 수평/수직 스크롤 바
						•WS_MAXIMIZEBOX / WS_MINIMIZEBOX: 최대화/최소화 버튼
						•WS_SYSMENU: 시스템 메뉴
						•WS_THICKFRAME: 크기 조정이 가능한 두꺼운 경계선
						•WS_BORDER: 단선으로 된 경계선, 크기 조정 불가능
						•WS_POPUP: 팝업 윈도우 (WS_CHILD와 같이 쓸 수 없다)
						•WS_CHILD: 차일드 윈도우
						•WS_VISIBLE: 윈도우를 만들자마자 화면에 출력

						•WS_OVERLAPPEDWINDOW: 가장 일반적인 윈도우 스타일
						(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)

						•WS_POPUPWINDOW: 일반적인 팝업 윈도우 (WS_POPUP | WS_BORDER | WS_SYSMENU)
						*/
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

											  /*=======•윈도우 출력 스타일================================================================================
											  •윈도우 클래스의 스타일을 나타낸다. Bitwise OR ( | ) 연산자를 이용하여 여러 개의 스타일을 OR로 설정할 수 있다.
											  •CS_HREDRAW / CS_VREDRAW: 작업 영역의 폭/높이가 변경되면 윈도우를 다시 그린다.
											  •CS_DBCLKS: 마우스 더블 클릭 메시지를 보낸다
											  •CS_CLASSDC: 이 클래스로부터 만들어진 모든 윈도우가 하나의 DC를 공유한다.
											  •CS_OWNDC: 각 윈도우가 하나의 DC를 독점적으로 사용한다.
											  •CS_PARENTDC: 차일드 윈도우가 부모 윈도우의 DC를 사용한다.
											  */

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
	/*====•메시지 처리 루프를 만들기 위한 함수들========================================================
	•BOOL GetMessage (LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
	•메시지 큐로부터 메시지를 얻어오는 역할

	•BOOL TranslateMessage (CONST MSG *lpMsg);
	키보드 입력 이벤트 중 문자 입력을 처리하는 함수로 단축키 명령어를 기본적인 이벤트로 번역 또는 변환

	•LONG DispatchMessage (CONST MSG *lpmsg);
	•실제적인 이벤트 처리 역할
	•GetMessage 함수로부터 전달된 메시지를 윈도우 프로시저로 보낸다.
	*/

	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	RECT rc;
	TCHAR str[50];
	static RECT ellipse[FigureNum], e[FigureNum - 1];
	static POINT mpoint, startp;
	static int lX, tY, rX, bY, count; 
	static BOOL Drag, start, end;
	int i, j, ranX, ranY, randS;

	srand((unsigned)time(NULL));

	switch (iMessage) {
	case WM_CREATE:
		mpoint = { 0, 0 };
		startp = { 0, 0 };
		count = 0;
		lX = -Width / 2;
		tY = -Height / 2;
		rX = Width / 2;
		bY = Height / 2;
		end = Drag = start = FALSE;
		break;
	case WM_LBUTTONDOWN: // 버튺을 누르면 드래그 동작 시작
		startp.x = LOWORD(lParam);
		startp.y = HIWORD(lParam);
		if (InCircle(ellipse , &startp))
			Drag = TRUE;
			
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hWnd);
		if (Drag)
		{ // 흰 바탕
			mpoint.x = LOWORD(lParam);
			mpoint.y = HIWORD(lParam);
			ellipse[0].left = lX + mpoint.x - startp.x;
			ellipse[0].top = tY + mpoint.y - startp.y;
			ellipse[0].right = rX + mpoint.x - startp.x;
			ellipse[0].bottom = bY + mpoint.y - startp.y;

			for (i = 1; i < FigureNum; i++)
				if (CheckCrashCircle(ellipse, ellipse + i))
				{
					e[i - 1].left = ellipse[i].left;
					e[i - 1].top = ellipse[i].top;
					e[i - 1].right = ellipse[i].right;
					e[i - 1].bottom = ellipse[i].bottom;
					ellipse[i].left = 0;
					ellipse[i].top = 0;
					ellipse[i].right = 0;
					ellipse[i].bottom = 0;
					count++;
				}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_LBUTTONUP: // 버튺을 놓으면 드래그 종료
		Drag = FALSE;
		GetWindowRect(hWnd, &rc);
		if (ellipse[0].left < rc.right &&
			ellipse[0].right > rc.right - Width &&
			ellipse[0].top < rc.bottom &&
			ellipse[0].bottom > rc.bottom - Height)
		{
			end = TRUE;
		}
		lX += mpoint.x - startp.x;
		tY += mpoint.y - startp.y;
		rX += mpoint.x - startp.x;
		bY += mpoint.y - startp.y;
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			GetWindowRect(hWnd, &rc);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 2:
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		if (start == FALSE)
		{
			ellipse[0].left = -Width / 2;
			ellipse[0].top = -Height / 2;
			ellipse[0].right = Width / 2;
			ellipse[0].bottom = Height / 2;

			for (i = 1; i < FigureNum; i++)
			{
				randS = rand() % 100;
				ranX = rand() % 700;
				ranY = rand() % 500;
				ellipse[i].left = ranX;
				ellipse[i].top = ranY;
				ellipse[i].right = Width + ranX;
				ellipse[i].bottom = Width + ranY;
				InflateRect(ellipse + i, randS, randS);
				for (j = 0; j < i; j++)
					if (ellipse[i].left < ellipse[j].right &&
						ellipse[i].right > ellipse[j].left &&
						ellipse[i].top < ellipse[j].bottom &&
						ellipse[i].bottom > ellipse[j].top) i--;
				start = TRUE;
			}
		}
		Ellipse(hdc, ellipse[0].left, ellipse[0].top, ellipse[0].right, ellipse[0].bottom);
		if (Drag)
		{
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Ellipse(hdc, ellipse[0].left, ellipse[0].top, ellipse[0].right, ellipse[0].bottom);
		}
		oldPen = (HPEN)SelectObject(hdc, GetStockObject(BLACK_PEN));
		for (i = 1; i < FigureNum; i++)
		{
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, ellipse[i].left, ellipse[i].top, ellipse[i].right, ellipse[i].bottom);
			oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(GRAY_BRUSH));
			Ellipse(hdc, e[i - 1].left, e[i - 1].top, e[i - 1].right, e[i - 1].bottom);
		}
		
		if (end == TRUE)
		{
			wsprintf(str, L"Game Over! Score : %d", count);
			TextOut(hdc, WIN_Width / 2 - 50, WIN_Height / 2 - 50, str , lstrlen(str));
		}

		SelectObject(hdc, oldPen);
		SelectObject(hdc, oldBrush);
		DeleteObject(hPen);
		DeleteObject(hBrush);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		break;
	case WM_CHAR:
		break;
	case WM_DESTROY:
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
BOOL CheckCrashCircle(RECT * rect1, RECT * rect2)
{
	if (( (rect1->right - rect1->left) / 2 + (rect2->right - rect2->left) / 2) >
		LengthPts((rect1->left + rect1->right) / 2, (rect1->top + rect1->bottom) / 2,
			(rect2->left + rect2->right) / 2, (rect2->top + rect2->bottom) / 2))
		return TRUE;
	else
		return FALSE;
}
/*
3-6
장애물 피하며 이동하기

프로그램이 시작하면 화면에 장애물 역할을 할 크고 작은 원들이 많이 나타나고 
주인공 역할을 할 흰색 원이 중심좌표(0, 0) 반지름 50으로 나타난다.
마우스 드래그로 흰색원을 반대쪽 모서리까지 이동시키면 기록으로 부딪힌 장애물 숫자를 화면에 출력한다.
*/