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


HINSTANCE g_hInst;
LPCTSTR lpszClass = WIN_CLASSNAME;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

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
	HDC hdc, memdc;
	PAINTSTRUCT ps;
	static CImage cat, mouse, BK;
	static HBITMAP memBit;
	static RECT rc, catrc, br[3];
	static POINT mpoint;
	static bool crash, drag;
	static float x, y, s;
	static int timer, t;

	switch (iMessage) {
	case WM_CREATE:
		GetWindowRect(hWnd, &rc);
		srand((unsigned)time(NULL));
		SetTimer(hWnd, 1, 60, NULL);
		cat.Load(L"고양이 스프라이트.png");
		mouse.Load(L"쥐.PNG");
		BK.LoadFromResource(g_hInst, IDB_SKY);
		catrc = {0, 0, 70, 70};
		for (int i = 0; i < 3; i++)
			br[i] = {0, 0, 100, 100};
		OffsetRect(&br[0], 400, 100);
		OffsetRect(&br[1], 600, 400);
		OffsetRect(&br[2], 200, 300);
		timer = 0;
		t = 0;
		crash = drag = false;
		break;
	case WM_LBUTTONDOWN:
		mpoint.x = LOWORD(lParam);
		mpoint.y = HIWORD(lParam);
		drag = true;
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
		if (drag)
		{
			mpoint.x = LOWORD(lParam);
			mpoint.y = HIWORD(lParam);
			s = LengthPts(mpoint.x, mpoint.y, (catrc.right + catrc.left) / 2, (catrc.bottom + catrc.top) / 2);
			x = (mpoint.x - (catrc.right + catrc.left) / 2) / s;
			y = (mpoint.y - (catrc.bottom + catrc.top) / 2) / s;
		}
		break;
	case WM_LBUTTONUP:
		drag = false;
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if (timer++ == 10000000) timer = 0;
			if (drag)
			{
				for(int i = 0; i < 3; i++)
					if (catrc.right > br[i].left && catrc.left < br[i].right &&
						catrc.top < br[i].bottom && catrc.bottom > br[i].top) {
						crash = true;
						if (catrc.left < br[i].left)
						{
							catrc.left = br[i].left - 70;
							catrc.right = br[i].left;
							OffsetRect(&catrc, 0, 30);
						}
						else if (catrc.right > br[i].right)
						{
							catrc.left = br[i].right;
							catrc.right = br[i].right + 70;
							OffsetRect(&catrc, 0, -30);
						}
						else if (catrc.top < br[i].top)
						{
							catrc.top = br[i].top - 70;
							catrc.bottom = br[i].top;
							OffsetRect(&catrc, -30, 0);
						}
						else if (catrc.bottom > br[i].bottom)
						{
							catrc.top = br[i].bottom;
							catrc.bottom = br[i].bottom + 70;
							OffsetRect(&catrc, 30, 0);
						}

					}
				if (!crash)
				{
					OffsetRect(&catrc, x * 30, y * 30);
				}
				else if (crash)
				{
					crash = false;
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
		//
		BK.Draw(memdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
		for (int i = 0; i < 3; i++)
			Rectangle(memdc, br[i].left, br[i].top, br[i].right, br[i].bottom);
		if (drag) mouse.TransparentBlt(memdc, mpoint.x - (mouse.GetWidth() / 2), mpoint.y - (mouse.GetHeight() / 2), 
			mouse.GetWidth(), mouse.GetHeight(), RGB(255, 255, 255));
		cat.TransparentBlt(memdc, catrc.left, catrc.top, catrc.right - catrc.left, catrc.bottom - catrc.top,
			(cat.GetWidth() / 4) * (timer % 4), 0, cat.GetWidth() / 4, cat.GetHeight(), RGB(0, 0, 0));
		// hdc에 복사
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, memdc, 0, 0, SRCCOPY);

		SelectObject(memdc, NULL);
		DeleteDC(memdc);
		DeleteObject(memBit);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYUP:
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
/*
쥐 쫓아가는 고양이
배경이미지 그려지고 중간중간에 장애물이 있다.
임의의 위치에서 고양이 애니메이션 진행
임의의 위치에 마우스를 클릭하면 쥐 애니멩션이 나타나고 마우스를 드래그하면 쥐 애니메이션이 이동
쥐를 향하여 고양이가 쫓아온다.
마우스는 장애물 위로는 움직일 수 없고, 고양이도 장애무을 만나면 임의의 방향으로 움직이고 계속 쫓아온다.
마우스를 떼면 쥐애니메이션은 없어진다.
*/