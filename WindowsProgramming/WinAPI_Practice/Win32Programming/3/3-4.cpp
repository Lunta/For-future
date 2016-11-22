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
#define FigureNum 10

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
	HBRUSH hBrush[FigureNum], oldBrush;
	HPEN hPen, oldPen;
	RECT rc;
	static RECT ellipse[FigureNum];
	static POINT mpoint;
	static int select, count;
	static int startX, startY, oldX, oldY;
	static float X[FigureNum], Y[FigureNum];
	static Ballvector bvector[FigureNum];
	static BOOL Drag, start;
	static float lean[FigureNum], lineX[FigureNum], lineY[FigureNum];
	int ranX, ranY;
	int endX, endY;
	int i;

	srand((unsigned)time(NULL));

	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 10, NULL);
		SetTimer(hWnd, 2, 2000, NULL);
		mpoint.x = 0;
		mpoint.y = 0;
		select = 0;
		count = 0;
		startX = oldX = 20; startY = oldY = 20; // 시작 좌표
		for (i = 0; i < FigureNum; i++)
		{
			X[i] = 0; 
			Y[i] = 0;
			bvector[i].x = 0;
			bvector[i].y = 0;
			bvector[i].speed = 0;
		}
		Drag = start = FALSE;
		break;
	case WM_LBUTTONDOWN: // 버튺을 누르면 드래그 동작 시작
		mpoint.x = LOWORD(lParam);
		mpoint.y = HIWORD(lParam);
		for (i = 0; i < FigureNum; i++)
			if (InCircle(ellipse + i, &mpoint))
			{
				Drag = TRUE;
				select = i;
			}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hWnd);
		if (Drag)
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
		Drag = FALSE;
		if (select != -1)
		{
			X[select] = LOWORD(lParam);
			Y[select] = HIWORD(lParam);
			select = -1;
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			GetWindowRect(hWnd, &rc);
			if (Drag == FALSE)
			{
				for (i = 0; i < FigureNum; i++) 
				{
					bvector[i].speed = LengthPts(((ellipse[i].left + ellipse[i].right) / 2),
						((ellipse[i].top + ellipse[i].bottom) / 2), X[i], Y[i]);
					bvector[i].x = (X[i] - ((ellipse[i].left + ellipse[i].right) / 2)) / bvector[i].speed;
					bvector[i].y = (Y[i] - ((ellipse[i].top + ellipse[i].bottom) / 2)) / bvector[i].speed;
					bvector[i].speed = bvector[i].speed / 5;
					if (bvector[i].speed <= 0) bvector[i].speed = 5;
					OffsetRect(ellipse + i, bvector[i].x * bvector[i].speed, bvector[i].y * bvector[i].speed);
				}
			}

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 2:
			for (i = 0; i < FigureNum; i++)
				if (ellipse[i].right > ellipse[i].left)
					InflateRect(ellipse + i, -2, -2);
			if (count == 10) count = 0;
			ranX = rand() % 300 + rand() % 300;
			ranY = rand() % 300 + rand() % 300;
			X[count] = ranX + Width / 2;
			Y[count] = ranY + Height / 2;
			ellipse[count].left = ranX;
			ellipse[count].top = ranY;
			ellipse[count].right = Width + ranX;
			ellipse[count].bottom = Height + ranY;
			if (start == FALSE)
			{
				mpoint.x = (ellipse[0].right + ellipse[0].left) / 2;
				mpoint.y = (ellipse[0].bottom + ellipse[0].top) / 2;
				start = TRUE;
			}
			count++;
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		for (i = 0; i < FigureNum; i++)
		{
			hBrush[i] = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[i]);
			Ellipse(hdc, ellipse[i].left, ellipse[i].top, ellipse[i].right, ellipse[i].bottom);
		}
		if(select != -1)
		{
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Ellipse(hdc, ellipse[select].left, ellipse[select].top, ellipse[select].right, ellipse[select].bottom);
		}
		MoveToEx(hdc, startX, startY, NULL); // 이동하고 선으로 연결
		LineTo(hdc, oldX, oldY);
		SelectObject(hdc, oldPen);
		SelectObject(hdc, oldBrush);
		for (i = 0; i < FigureNum; i++)
			DeleteObject(hBrush[i]);
		DeleteObject(hPen);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		break;
	case WM_CHAR:
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
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
•제목
–직선을 따라 움직이는 원 그리기
–선택핚 원의 중심에서 마우스 커서까지 직선 그리기
•내용
–원은 임의의 위치에 특정 시갂에 따라 계속 그려지고, 점점 작아지다가 특정 시갂이 지나면 없어짂다.
–원 내부에 왼쪽 마우스 버튺을 눌러서 드래그 하여 직선을 그린다. (고무줄 효과)
–마우스 버튺을 놓으면 직선이 완성된다.
–원은 직선 위로 이동하고 선의 끝에서 멈춘다.
–새롭게 원을 선택핛 수 있다.*/

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