#include <windows.h> 
#include <tchar.h>
#include <ctime>
#include <math.h>
#include "resource.h"

#define WIN_CLASSNAME TEXT("Bitmap")
#define WIN_TITLENAME TEXT("Bitmap")
#define WIN_Width 1024
#define WIN_Height 640
#define WIN_XPOS 0
#define WIN_YPOS 0

enum class KEYDOWN
{
	left = 1, right = 2, up = 3, down = 4
};

typedef struct vector
{
	float x;
	float y;
	float speed;
}Ballvector;

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
	HDC hdc, memdc, bmpdc;
	HBITMAP membit;
	PAINTSTRUCT ps;
	BITMAP bmp;
	static HDC memDC, bitDC;
	static HBITMAP hBitmap, sprite, spriteM, memBit, oldbit;
	static RECT rc, chara;
	static bool inputkey, click, jump;
	static int flag, timer, sp, msp;

	srand((unsigned)time(NULL));

	switch (iMessage) {
	case WM_CREATE:
		GetWindowRect(hWnd, &rc);
		srand((unsigned)time(NULL));
		SetTimer(hWnd, 1, 60, NULL);
		SetTimer(hWnd, 2, 300, NULL);
		hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_SKY));
		sprite = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_SPRITE));
		spriteM = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_SPRITEM));
		chara = { (rc.right / 2) - 20, (rc.bottom / 2) - 15, (rc.right / 2) + 20, (rc.bottom / 2) + 15};
		inputkey = click = jump = false;
		flag = -1;
		timer = 0;
		sp = msp = 0;
		break;
	case WM_LBUTTONDOWN: 
		LOWORD(lParam);
		HIWORD(lParam);

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:

		break;
	case WM_LBUTTONUP: 
		if (chara.left < LOWORD(lParam) && chara.right > LOWORD(lParam) &&
			chara.top < HIWORD(lParam) && chara.bottom > HIWORD(lParam))
		{
			click = true;
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if(timer++ == 1000000) timer = 0;

			if (flag == (int)KEYDOWN::left && inputkey) OffsetRect(&chara, -10, 0);
			else if (flag == (int)KEYDOWN::up& inputkey) OffsetRect(&chara, 0, -10);
			else if (flag == (int)KEYDOWN::right && inputkey) OffsetRect(&chara, 10, 0);
			else if (flag == (int)KEYDOWN::down && inputkey) OffsetRect(&chara, 0, 10);
			if (jump)
			{
				if (msp == 10)
				{
					jump = false;
					msp = 0;
					break;
				}
				if (msp < 5)
				{
					OffsetRect(&chara, 0, -10);
					msp++;
				}
				else if (msp < 10)
				{
					OffsetRect(&chara, 0, 10);
					msp++;
				}
			}
			break;
		case 2:
			if (click)
			{
				if (msp == 2)
				{
					msp = 0;
					click = false;
					if (sp == 1) sp = 0;
					else if (sp == 0) sp = 1;
					break;
				}
				OffsetRect(&chara, 0, 10);
				msp++;
			}
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memDC = CreateCompatibleDC(hdc);
		bitDC = CreateCompatibleDC(memDC);
		memBit = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		oldbit = (HBITMAP)SelectObject(bitDC, hBitmap);
		SelectObject(memDC, memBit);
		FillRect(memDC, &rc, WHITE_BRUSH);
		BitBlt(memDC, 0, 0, rc.right, rc.bottom, bitDC, 0, 0, SRCCOPY);

		if (!click)
		{
			oldbit = (HBITMAP)SelectObject(bitDC, sprite);
			TransparentBlt(memDC, chara.left, chara.top, 40, 30, bitDC, 40 * (timer % 4), 30 * sp, 40, 30, RGB(0, 0, 0));
		}
		else if (click)
		{
			oldbit = (HBITMAP)SelectObject(bitDC, spriteM);
			TransparentBlt(memDC, chara.left, chara.top, 40, 30, bitDC, 40 * msp, 30 * sp, 40, 30, RGB(0, 0, 0));
		}

		// hdc에 복사
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, memDC, 0, 0, SRCCOPY);

		DeleteDC(memDC);
		DeleteDC(bitDC);
		DeleteObject(memBit);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		if (wParam == 'J') jump = true;
		if (wParam == VK_LEFT)
		{
			flag = (int)KEYDOWN::left;
			sp = 1;
		}
		if (wParam == VK_UP) flag = (int)KEYDOWN::up;
		if (wParam == VK_RIGHT) 
		{
			flag = (int)KEYDOWN::right;
			sp = 0;
		}
		if (wParam == VK_DOWN) flag = (int)KEYDOWN::down;
		inputkey = true;
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYUP:
		inputkey = false;
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