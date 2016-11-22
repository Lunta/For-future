#include <windows.h> 
#include <tchar.h>
#include <ctime>
#include <math.h>
#include "resource.h"

#define WIN_CLASSNAME TEXT("Bitmap")
#define WIN_TITLENAME TEXT("Bitmap")
#define WIN_Width 1020
#define WIN_Height 500
#define WIN_XPOS 0
#define WIN_YPOS 0

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
	PAINTSTRUCT ps;
	BITMAP bmp;
	POINT mpoint;
	static POINT bmppoint, Divpoint;
	static HBITMAP hBitmap;
	static RECT rc, rect, DivRc[5][5], bmpRc[3][3], bmptoDiv[5][5];
	static int flag;
	static bool drag, drawrc;

	srand((unsigned)time(NULL));

	switch (iMessage) {
	case WM_CREATE:
		GetWindowRect(hWnd, &rc);
		srand((unsigned)time(NULL));
		SetTimer(hWnd, 1, 10, NULL);
		SetTimer(hWnd, 2, 2000, NULL);
		hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
			{
				DivRc[i][j] = { 0, 0, 0, 0 };
				bmptoDiv[i][j] = { 0, 0, 0, 0 };
			}
		drawrc = false;
		flag = 0;
		drag = FALSE;
		break;
	case WM_LBUTTONDOWN: 
		if (LOWORD(lParam) > rc.right / 2 && !drawrc) 
		{
			rect.left = LOWORD(lParam);
			rect.top = HIWORD(lParam);
			rect.right = LOWORD(lParam);
			rect.bottom = HIWORD(lParam);
		}
		drag = TRUE;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		if (drag && LOWORD(lParam) > rc.right / 2 && !drawrc)
		{
			rect.right = LOWORD(lParam);
			rect.bottom = HIWORD(lParam);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP: 
		drag = FALSE;
		drawrc = true;
		mpoint.x = LOWORD(lParam);
		mpoint.y = HIWORD(lParam);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (bmpRc[i][j].left < mpoint.x && bmpRc[i][j].right > mpoint.x &&
					bmpRc[i][j].top < mpoint.y && bmpRc[i][j].bottom > mpoint.y)
				{
					bmppoint.x = j;
					bmppoint.y = i;
					break;
				}

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				if (DivRc[i][j].left < mpoint.x && DivRc[i][j].right > mpoint.x &&
					DivRc[i][j].top < mpoint.y && DivRc[i][j].bottom > mpoint.y)
				{
					Divpoint.x = j;
					Divpoint.y = i;
					bmptoDiv[i][j] = { bmpRc[bmppoint.y][bmppoint.x].left, bmpRc[bmppoint.y][bmppoint.x].top,
						bmpRc[bmppoint.y][bmppoint.x].right, bmpRc[bmppoint.y][bmppoint.x].bottom };
					break;
				}
		if (rect.left< mpoint.x && rect.top < mpoint.y && rect.right > mpoint.x && rect.bottom > mpoint.y)
			bmptoDiv[0][0] = { bmpRc[bmppoint.y][bmppoint.x].left, bmpRc[bmppoint.y][bmppoint.x].top,
				bmpRc[bmppoint.y][bmppoint.x].right, bmpRc[bmppoint.y][bmppoint.x].bottom };
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:


			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case 2:

			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		memdc = CreateCompatibleDC(hdc);
		bmpdc = CreateCompatibleDC(hdc);
		SelectObject(bmpdc, hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), &bmp);
		//StretchBlt(hdc, 0, 0, rc.right, rc.bottom, bmpdc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, bmpdc, 0, 0, SRCCOPY);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				bmpRc[i][j] = { (bmp.bmWidth / 3)*(j), (bmp.bmHeight / 3)*(i),
				(bmp.bmWidth / 3)*(j + 1), (bmp.bmHeight / 3)*(i + 1) };
				if (i == bmppoint.y && j == bmppoint.x)
				{
					HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
					FrameRect(hdc, &bmpRc[i][j], hBrush);
					DeleteObject(hBrush);
				}
				else FrameRect(hdc, &bmpRc[i][j], (HBRUSH)GetStockObject(BLACK_BRUSH));
			}
		if (flag == 0)
		{
			StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
				bmpdc, bmptoDiv[0][0].left, bmptoDiv[0][0].top,
				bmptoDiv[0][0].right - bmptoDiv[0][0].left, bmptoDiv[0][0].bottom - bmptoDiv[0][0].top, SRCCOPY);
			FrameRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
		else if (flag == 1)
		{
			StretchBlt(hdc, DivRc[0][0].left, DivRc[0][0].top, 
				DivRc[0][0].right - DivRc[0][0].left, DivRc[0][0].bottom - DivRc[0][0].top,
				bmpdc, bmptoDiv[0][0].left, bmptoDiv[0][0].top,
				bmptoDiv[0][0].right - bmptoDiv[0][0].left, bmptoDiv[0][0].bottom - bmptoDiv[0][0].top, SRCCOPY);
			FrameRect(hdc, &DivRc[0][0], (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
		else if (flag == 2)
		{
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
				{
					StretchBlt(hdc, DivRc[i][j].left, DivRc[i][j].top,
						DivRc[i][j].right - DivRc[i][j].left, DivRc[i][j].bottom - DivRc[i][j].top,
						bmpdc, bmptoDiv[i][j].left, bmptoDiv[i][j].top,
						bmptoDiv[i][j].right - bmptoDiv[i][j].left, bmptoDiv[i][j].bottom - bmptoDiv[i][j].top, SRCCOPY);
					FrameRect(hdc, &DivRc[i][j], (HBRUSH)GetStockObject(BLACK_BRUSH));
				}
		}
		else if (flag == 3)
		{
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
				{
					StretchBlt(hdc, DivRc[i][j].left, DivRc[i][j].top,
						DivRc[i][j].right - DivRc[i][j].left, DivRc[i][j].bottom - DivRc[i][j].top,
						bmpdc, bmptoDiv[i][j].left, bmptoDiv[i][j].top,
						bmptoDiv[i][j].right - bmptoDiv[i][j].left, bmptoDiv[i][j].bottom - bmptoDiv[i][j].top, SRCCOPY);
					FrameRect(hdc, &DivRc[i][j], (HBRUSH)GetStockObject(BLACK_BRUSH));
				}
		}
		else if (flag == 4)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
				{
					StretchBlt(hdc, DivRc[i][j].left, DivRc[i][j].top,
						DivRc[i][j].right - DivRc[i][j].left, DivRc[i][j].bottom - DivRc[i][j].top,
						bmpdc, bmptoDiv[i][j].left, bmptoDiv[i][j].top,
						bmptoDiv[i][j].right - bmptoDiv[i][j].left, bmptoDiv[i][j].bottom - bmptoDiv[i][j].top, SRCCOPY);
					FrameRect(hdc, &DivRc[i][j], (HBRUSH)GetStockObject(BLACK_BRUSH));
				}
		}
		else if (flag == 5)
		{
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
				{
					StretchBlt(hdc, DivRc[i][j].left, DivRc[i][j].top,
						DivRc[i][j].right - DivRc[i][j].left, DivRc[i][j].bottom - DivRc[i][j].top,
						bmpdc, bmptoDiv[i][j].left, bmptoDiv[i][j].top,
						bmptoDiv[i][j].right - bmptoDiv[i][j].left, bmptoDiv[i][j].bottom - bmptoDiv[i][j].top, SRCCOPY);
					FrameRect(hdc, &DivRc[i][j], (HBRUSH)GetStockObject(BLACK_BRUSH));
				}
		}
		//BitBlt(hdc, 0, 0, rc.right, rc.bottom, memdc, 0, 0, SRCCOPY);

		DeleteDC(memdc);
		DeleteDC(bmpdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		GetObject(hBitmap, sizeof(BITMAP), &bmp);
		if (wParam == '1')
		{
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
					bmptoDiv[i][j] = { 0, 0, 0, 0 };
			DivRc[0][0] = { (rc.right / 2) , 0, (rc.right / 2) + (bmp.bmWidth), (bmp.bmHeight) };
			flag = 1;
			drawrc = false;
		}
		else if (wParam == '2')
		{
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
					bmptoDiv[i][j] = { 0, 0, 0, 0 };
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
					DivRc[i][j] = { (rc.right / 2) + (bmp.bmWidth / 2)*(j), (bmp.bmHeight / 2)*(i),
					(rc.right / 2) + (bmp.bmWidth / 2)*(j + 1), (bmp.bmHeight / 2)*(i + 1) };
			flag = 2;
			drawrc = false;
		}
		else if (wParam == '3')
		{
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
					bmptoDiv[i][j] = { 0, 0, 0, 0 };
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					DivRc[i][j] = { (rc.right / 2) + (bmp.bmWidth / 3)*(j), (bmp.bmHeight / 3)*(i),
					(rc.right / 2) + (bmp.bmWidth / 3)*(j + 1), (bmp.bmHeight / 3)*(i + 1) };
			flag = 3;
			drawrc = false;
		}
		else if (wParam == '4')
		{
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
					bmptoDiv[i][j] = { 0, 0, 0, 0 };
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					DivRc[i][j] = { (rc.right / 2) + (bmp.bmWidth / 4)*(j), (bmp.bmHeight /4)*(i),
					(rc.right / 2) + (bmp.bmWidth / 4)*(j + 1), (bmp.bmHeight / 4)*(i + 1) };
			flag = 4;
			drawrc = false;
		}
		else if (wParam == '5')
		{
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
					bmptoDiv[i][j] = { 0, 0, 0, 0 };
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
					DivRc[i][j] = {(rc.right / 2) + (bmp.bmWidth / 5)*(j), (bmp.bmHeight / 5)*(i),
					(rc.right / 2) + (bmp.bmWidth / 5)*(j + 1), (bmp.bmHeight / 5)*(i + 1) };
			flag = 5;
			drawrc = false;
		}
		else if (wParam == '0')
		{
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
					bmptoDiv[i][j] = { 0, 0, 0, 0 };
			flag = 0;
			drawrc = false;
		}
		InvalidateRect(hWnd, NULL, TRUE);
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

/*
이미지 복사하기
한쪽면에 이미지를 그리고 가로와 세로를 각각 3등분한다.
다른쪽 면에 복샇ㄹ 그림판을 만들고 가로와 세로를 각각 3등분 한다.
이미지의 한 칸을 클릭하고 그림판 한 칸을 클릭하면 이미지가 그 칸에 복사된다.
그림판의 등분은 키보드 명령으로 바꿀 수 있다.

0: 그림판에 마우스/ 드래그를 이용하여 자유 칸 만들어 복사
1: 그림판 가로/ 세로 각각 1칸
~
5:그림판 가로/ 세로 각각 5칸
*/