#include <windows.h> 
#include <tchar.h>
#include <ctime>
#include <math.h>
#include <atlimage.h> // pragma coment "lib, msimg32" mfc cimage. load blt 
#include "resource.h"

#define WIN_CLASSNAME TEXT("Bitmap")
#define WIN_TITLENAME TEXT("Bitmap")
#define WIN_Width 800
#define WIN_Height 600
#define WIN_XPOS 0
#define WIN_YPOS 0

enum class KEYDOWN
{
	left = 1, right = 2, up = 3, down = 4
};

typedef struct PUZZLE
{
	POINT imgPos;
	RECT rc;
}Puzzle;

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
	HDC hdc, memdc;
	HBITMAP membit;
	PAINTSTRUCT ps;
	static BITMAP bmp;
	static CImage image, temp;
	static HBITMAP memBit;
	static RECT rc;
	static POINT mpoint;
	static Puzzle board[5][5], blank;
	static bool click, start, flag;
	static int timer, div, x, y, t;

	switch (iMessage) {
	case WM_CREATE:
		GetWindowRect(hWnd, &rc);
		srand((unsigned)time(NULL));
		SetTimer(hWnd, 1, 60, NULL);
		image.LoadFromResource(g_hInst, IDB_PUZZLE);
		temp.LoadFromResource(g_hInst, IDB_PUZZLE);
		timer = 0;
		div = 0;
		click = start = flag = false;
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				board[i][j].rc = {0, 0, 0, 0};
		break;
	case WM_LBUTTONDOWN:
		mpoint.x = LOWORD(lParam);
		mpoint.y = HIWORD(lParam);

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:

		break;
	case WM_LBUTTONUP:
		mpoint.x = LOWORD(lParam);
		mpoint.y = HIWORD(lParam);
		if(!click)
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
					if (board[i][j].rc.left < mpoint.x && board[i][j].rc.right > mpoint.x &&
						board[i][j].rc.top < mpoint.y && board[i][j].rc.bottom > mpoint.y &&
						((board[i][j].rc.left == board[0][0].rc.right || board[i][j].rc.right == board[0][0].rc.left) !=
						(board[i][j].rc.top == board[0][0].rc.bottom || board[i][j].rc.bottom == board[0][0].rc.top)))
					{
						x = j;
						y = i;
						blank.rc = { board[y][x].rc.left, board[y][x].rc.top, board[y][x].rc.right, board[y][x].rc.bottom};
						click = true;
					}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if (timer++ == 10000000) timer = 0;
			if (click)
			{
				t++;
				if (board[y][x].rc.top < board[0][0].rc.top) OffsetRect(&board[y][x].rc, 0, 5);
				else if (board[y][x].rc.top < board[0][0].rc.top) OffsetRect(&board[y][x].rc, 0, -5);
				if (board[y][x].rc.left < board[0][0].rc.left) OffsetRect(&board[y][x].rc, 5, 0);
				else if (board[y][x].rc.left > board[0][0].rc.left) OffsetRect(&board[y][x].rc, -5, 0);
				if (t == 20) {
					board[y][x].rc = { board[0][0].rc.left, board[0][0].rc.top, board[0][0].rc.right, board[0][0].rc.bottom };
					board[0][0].rc = { blank.rc.left, blank.rc.top, blank.rc.right, blank.rc.bottom };
					click = false;
					t = 0;
				}

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
		FillRect(memdc, &rc, WHITE_BRUSH);
		if (div == 3)
		{
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
				{
					image.BitBlt(memdc, board[i][j].rc.left, board[i][j].rc.top, 
						board[i][j].rc.right - board[i][j].rc.left, board[i][j].rc.bottom - board[i][j].rc.top, 
						(image.GetWidth() / 3) * board[i][j].imgPos.x, (image.GetHeight() / 3) * board[i][j].imgPos.y, 
						SRCCOPY);
					FrameRect(memdc, &board[i][j].rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
				}
		}
		else if (div == 4)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
				{
					image.BitBlt(memdc, board[i][j].rc.left, board[i][j].rc.top,
						board[i][j].rc.right - board[i][j].rc.left, board[i][j].rc.bottom - board[i][j].rc.top,
						(image.GetWidth() / 4) * board[i][j].imgPos.x, (image.GetHeight() / 4) * board[i][j].imgPos.y,
						SRCCOPY);
					FrameRect(memdc, &board[i][j].rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
				}
		}
		else if (div == 5)
		{
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
				{
					image.BitBlt(memdc, board[i][j].rc.left, board[i][j].rc.top,
						board[i][j].rc.right - board[i][j].rc.left, board[i][j].rc.bottom - board[i][j].rc.top,
						(image.GetWidth() / 5) * board[i][j].imgPos.x, (image.GetHeight() / 5) * board[i][j].imgPos.y,
						SRCCOPY);
					FrameRect(memdc, &board[i][j].rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
				}
		}
		if (flag)image.Draw(memdc, 0, 0, rc.right, rc.bottom);
		// hdc에 복사
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, memdc, 0, 0, SRCCOPY);

		SelectObject(memdc, NULL);
		DeleteDC(memdc);
		DeleteObject(memBit);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		if (wParam == 'S')
		{
			start = true;
			blank.imgPos = { board[0][0].imgPos.x, board[0][0].imgPos.y };
			board[0][0].imgPos = { -1, -1 };
		}
		else if (wParam == 'F') flag = true;
		else if (wParam == 'Q')
		{
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			PostQuitMessage(0);
			return 0;
		}
		else if (wParam == '3')
		{
			int random[9] = { 0 }, n = 0;
			for (int i = 0; i < 9; i++)
			{
				n = rand() % 9;
				for(int j = 0; j < i; j++)
					if (random[j] == n)
					{
						n = rand() % 9;
						j = 0;
					}
				random[i] = n;
			}
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
				{
					board[i][j].rc = { (rc.right / 3) * j, (rc.bottom / 3) * i,
					(rc.right / 3) * (j + 1), (rc.bottom / 3) * (i + 1) };
					board[i][j].imgPos.x = random[j + (3 * i)] % 3;
					board[i][j].imgPos.y = (int)(random[j + (3 * i)] / 3);
				}
			div = 3;
		}
		else if (wParam == '4')
		{
			int random[16] = { 0 }, n = 0;
			for (int i = 0; i < 16; i++)
			{
				n = rand() % 16;
				for (int j = 0; j < i; j++)
					if (random[j] == n)
					{
						n = rand() % 16;
						j = 0;
					}
				random[i] = n;
			}
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
				{
					board[i][j].rc = { (rc.right / 4) * j, (rc.bottom / 4) * i,
					(rc.right / 4) * (j + 1), (rc.bottom / 4) * (i + 1) };
					board[i][j].imgPos.x = random[j + (4 * i)] % 4;
					board[i][j].imgPos.y = (int)(random[j + (4 * i)] / 4);
				}
			div = 4;
		}
		else if (wParam == '5')
		{
			int random[25] = { 0 }, n = 0;
			for (int i = 0; i < 25; i++)
			{
				n = rand() % 25;
				for (int j = 0; j < i; j++)
					if (random[j] == n)
					{
						n = rand() % 25;
						j = 0;
					}
				random[i] = n;
			}
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
				{
					board[i][j].rc = { (rc.right / 5) * j, (rc.bottom / 5) * i,
					(rc.right / 5) * (j + 1), (rc.bottom / 5) * (i + 1) };
					board[i][j].imgPos.x = random[j + (5 * i)] % 5;
					board[i][j].imgPos.y = (int)(random[j + (5 * i)] / 5);
				}
			div = 5;
		}

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYUP:
		flag = false;
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
}/*
조각퍼즐 맞추기
3, 4, 5선택해서 그림을 숫자에 맞게 분할, 랜덤하게 화면에 배치
S를 선택하면 그림 하나가 비고 게임이 시작
마우스를 이용하여 주변의 조각을 클리하여 조각 그림을 이동한다.
이동은 단번에 이동하지않고 조금씩 이동
게임중에F을 선택하면 완성된 형태를 보여준다.
Q: 종료
*/