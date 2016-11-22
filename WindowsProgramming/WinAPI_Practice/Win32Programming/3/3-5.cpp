#include <windows.h> 
#include <tchar.h>
#include <ctime>

#define WIN_CLASSNAME TEXT("Timer")
#define WIN_TITLENAME TEXT("Timer")
#define WIN_XPOS 0 
#define WIN_YPOS 0 
#define WIN_Width 800 
#define WIN_Height 600

#define Width 30
#define Height 30
#define Size 15

HINSTANCE g_hInst;
LPCTSTR lpszClass = WIN_CLASSNAME;


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


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
		;	
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
	HPEN hPen, oldPen;
	HBRUSH hBrush[3], oldBrush;
	RECT rc;
	static RECT larva[Size], boom[Size], item[Size];
	static POINT mpoint;
	static int ranX, ranY;
	static int speed, count, randboomnum, randitemnum, tail;
	static BOOL right, left, up, down, jump, start;
	int i, j, icY, revicY;

	srand((unsigned)time(NULL));
	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 100, NULL);
		speed = 100;
		count = 0;
		tail = 1;
		randboomnum = rand() % Size;
		randitemnum = rand() % Size;
		mpoint.x = 0;
		mpoint.y = 0;
		right = left = up = down = jump = start = FALSE;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:  
		mpoint.x = LOWORD(lParam);
		mpoint.y = HIWORD(lParam);
		icY = larva[0].top - larva[0].left;
		revicY = larva[0].top + larva[0].right;
		// mpoint.y = mpoint.x + icY //mpoint.y = -mpoint.x + revicY
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
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			GetWindowRect(hWnd, &rc);
			if (larva[0].right  > rc.right - Width )
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

			if (right == 1)		OffsetRect(larva, Width, 0);
			else if (left == 1) OffsetRect(larva, -Width, 0);
			else if (up == 1)	OffsetRect(larva, 0, -Height);
			else if (down == 1) OffsetRect(larva, 0, Height);

			for (i = tail + 1; i > 0; i--)
			{
				larva[i].left = larva[i - 1].left;
				larva[i].top = larva[i - 1].top;
				larva[i].right = larva[i - 1].right;
				larva[i].bottom = larva[i - 1].bottom;
			}


			for (i = 0; i < Size; i++)
				if(larva[0].left < item[i].right && 
					larva[0].right > item[i].left && 
					larva[0].top < item[i].bottom && 
					larva[0].bottom > item[i].top)
				{
					item[i].left = 0;
					item[i].top = 0;
					item[i].right = 0;
					item[i].bottom = 0;
					tail++;
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
						larva[tail].right = larva[tail - 1].right ;
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

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 2:
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		hBrush[0] = CreateSolidBrush(RGB(255, 0, 0));
		hBrush[1] = CreateSolidBrush(RGB(0, 255, 0));
		hBrush[2] = CreateSolidBrush(RGB(0, 0, 255));

		if (start == FALSE)
		{
			larva[0].left = 0;
			larva[0].top = 0;
			larva[0].right = Width;
			larva[0].bottom = Height;

			larva[1].left = -Width;
			larva[1].top = 0;
			larva[1].right = 0;
			larva[1].bottom = Height;

			for (i = 0; i < randitemnum + 1; i++)
			{
				ranX = rand() % 250 + rand() % 250;
				ranY = rand() % 250 + rand() % 250;
				item[i].left = ranX;
				item[i].top = ranY;
				item[i].right = Width + ranX;
				item[i].bottom = Height + ranY;
				for (j = 0; j < i; j++)
					if (item[i].left < item[j].right &&
						item[i].right > item[j].left &&
						item[i].top < item[j].bottom &&
						item[i].bottom > item[j].top) i--;

			}
			for (i = 0; i < randboomnum + 1; i++)
			{
				ranX = rand() % 250 + rand() % 250;
				ranY = rand() % 250 + rand() % 250;
				boom[i].left = ranX;
				boom[i].top = ranY;
				boom[i].right = Width + ranX;
				boom[i].bottom = Height + ranY;
				for (j = 0; j < i; j++)
					if (boom[i].left < boom[j].right &&
						boom[i].right > boom[j].left &&
						boom[i].top < boom[j].bottom &&
						boom[i].bottom > boom[j].top) i--;
			}

			start = TRUE;
		}

		oldBrush = (HBRUSH)SelectObject(hdc, hBrush[1]);
		for (i = 0; i < randitemnum + 1; i++)
			Ellipse(hdc, item[i].left, item[i].top, item[i].right, item[i].bottom);

		oldBrush = (HBRUSH)SelectObject(hdc, hBrush[0]);
		for (i = 0; i < randboomnum + 1; i++)
			Ellipse(hdc, boom[i].left, boom[i].top, boom[i].right, boom[i].bottom);

		(HBRUSH)SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
		for (i = 1; i < Size; i++)
			Ellipse(hdc, larva[i].left, larva[i].top, larva[i].right, larva[i].bottom);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush[2]);
		oldPen = (HPEN)SelectObject(hdc, hPen);
		Ellipse(hdc, larva[0].left, larva[0].top, larva[0].right, larva[0].bottom);
		if (start == TRUE)
		{
			for (i = 0; i < randitemnum + 1; i++)
				if (item[i].left == 0 && item[i].top == 0 && item[i].right == 0 && item[i].bottom == 0) count++;
			if(count == randitemnum + 1)
				if (item[0].left == 0 && item[0].top == 0 && item[0].right == 0 && item[0].bottom == 0)
				{
					KillTimer(hWnd, 1);
					TextOut(hdc, WIN_Width / 2, WIN_Height / 2, TEXT("You Win!"), lstrlen(TEXT("You Win!")));
				}
			
			if (larva[0].left == 0 && larva[0].top == 0 && larva[0].right == 0 && larva[0].bottom == 0)
			{
				KillTimer(hWnd, 1);
				TextOut(hdc, WIN_Width / 2, WIN_Height / 2, TEXT("GameOver!"), lstrlen(TEXT("GameOver!")));
			}

			count = 0;
		}
		SelectObject(hdc, oldPen);
		SelectObject(hdc, oldBrush);
		for (i = 0; i < 3; i++)
			DeleteObject(hBrush[i]);
		DeleteObject(hPen);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_CONTROL) //jump
		{
			jump = TRUE;
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
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
/*•제목
•연습문제 3-1에 마우스를 이용핚 기능 추가하기
•내용
•애벌레 (2개 원)가 자동으로 이동하고 있다.
•화면에는 임의의 개수의 먹이와 폭탄이 있다.
•먹이와 폭탄은 다른 색 또는 다른 모양으로 표시핚다.
•먹이를 먹으면 꼬리가 하나 추가된다
•폭탄을 먹으면 꼬리가 하나 사라짂다.
•왼쪽 마우스 버튺을 누르면 그 방향으로 애벌레의 이동 방향이 바뀐다.
•먹이를 다 먹거나 꼬리가 다 없어지면 종료*/

/*•BOOL OffsetRect(LPRECT lprc, int dx, int dy);
–주어진 Rect를 dx, dy만큼 이동한다.
•BOOL InflateRect(LPRECT lprc, int dx, int dy);
–주어진 Rect를 dx, dy만큼 늘이거나 줄인다.
•BOOL IntersectRect(LPRECT lprcDst, CONST RECT *lprcSrc1, CONST RECT(lprcSrc2);
–두 RECT가 교차되었는지 검사한다.
•BOOL UnionRect(LPRECT lprcDest, CONST RECT *lprcSrc1, CONST RECT *lprcSrc2);
–두 RECT 를 union 시킨다.
•BOOL PtInRect(CONST RECT *lprc, POINT pt);
–특정 좌표 pt가 lprc 영역 안에 있는지 검사한다.
*/