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

#define Width 30
#define Height 30
#define BlockNum 10
#define BlockLine 2

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
	HPEN hPen[2], oldPen;
	RECT rc;
	TCHAR str[50];
	static Block block[BlockLine][BlockNum];
	static Ballvector bvector;
	static RECT ball, bar;
	static POINT mpoint;
	static int crackcount, destroycount, oldX, oldY, startX, startY, count;
	static BOOL start, end, move, drag;
	int i, j, check = 0, endX, endY;

	srand((unsigned)time(NULL));
	GetWindowRect(hWnd, &rc);

	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 50, NULL);
		crackcount = 0;
		destroycount = 0;
		drag = move = end = start = FALSE;
		count = 0;
		InvalidateRect(hWnd, NULL, TRUE);
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
		InvalidateRect(hWnd, NULL, TRUE);
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
			bvector.y = (mpoint.y - ((ball.top + ball.bottom) / 2) )/ bvector.speed;
			bvector.speed = bvector.speed / 30;
			drag = FALSE;
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			InvalidateRect(hWnd, NULL, TRUE);
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
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, block[i][j].rc.left, block[i][j].rc.top, block[i][j].rc.right, block[i][j].rc.bottom);
					break;
				case 1: //Crack
					oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(GRAY_BRUSH));
					Rectangle(hdc, block[i][j].rc.left, block[i][j].rc.top, block[i][j].rc.right, block[i][j].rc.bottom);
					break;
				}
			}
		oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		Ellipse(hdc, ball.left, ball.top, ball.right, ball.bottom);
		oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		oldPen = (HPEN)SelectObject(hdc, hPen[0]);
		Rectangle(hdc, bar.left, bar.top, bar.right, bar.bottom);

		wsprintf(str, L"Crack : %d, Destroy : %d", crackcount, destroycount);
		TextOut(hdc, 0, 0, str, lstrlen(str));
		if (end == TRUE)
		{
			KillTimer(hWnd, 1);
			wsprintf(str, L"Game Over. Score : %d", destroycount);
			TextOut(hdc, WIN_Width / 2 - 50, WIN_Height / 2 - 50, str, lstrlen(str));
		}
		if (drag)
		{
			oldPen = (HPEN)SelectObject(hdc, hPen[1]);
			MoveToEx(hdc, startX, startY, NULL); // 이동하고 선으로 연결
			LineTo(hdc, oldX, oldY);
		}
		SelectObject(hdc, oldPen);
		SelectObject(hdc, oldBrush);
		DeleteObject(hPen[0]);
		DeleteObject(hPen[1]);
		DeleteObject(hBrush);
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
			if(end == TRUE) SetTimer(hWnd, 1, 50, NULL);
			drag = move = end = start = FALSE;
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
	else if(hp != DESTROY)
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
/*3 - 7
벽돌깨기 게임만들기
화면의 상단에 2 * 10개의 벽돌이 있다.
화면의 하단에 바가 있고 마우스를 이용하여 바를 움직인다.
마우스를 누르면 마우스의 x위치로 이동한다.
공이 튀기면서 벽돌에 한번 닿으면 벽돌의 색이 바뀐다.
공이 투기면서 벽돌에 2번 닿으면 벽돌이 없어진다.
색이 변한 벽돌의 개수와 없어진 개수를 화면에 출력한다.
명령어 입력 : 공의 이동속도가 늘어난다.
벽돌이 모두 업어지면 게임이 종료된다.*/