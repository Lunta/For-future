#include <windows.h> 
#include <tchar.h>
#include <ctime>

#define WIN_CLASSNAME TEXT("Memo")
#define WIN_TITLENAME TEXT("Memo")
#define WIN_XPOS 0 
#define WIN_YPOS 0 
#define WIN_Width 800 
#define WIN_Height 600

#define FigureCount 5

HINSTANCE g_hInst;
LPCTSTR lpszClass = WIN_CLASSNAME;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

/*====WinMain()=============================================================================
•WINAPI: 윈도우 프로그램이라는 의미
•hInstance: 현재 실행중인 어플리케이션의 인스턴스 핸들
•hPrevInstance: 동일한 어플리케이션이 실행중일 경우 이전에 실행된 프로그램의 인스턴스 핸들.
Win32 어플리케이션의 경우 항상 NULL
•szCmdLine: 커멘드라인 상에서 프로그램 구동 시 전달된 문자열
•iCmdShow: 윈도우가 화면에 출력될 형태
*/


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG Message;
	WNDCLASS WndClass; //구조체 정의
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

	hwnd = CreateWindow( // 윈도우가 생성되면 핸들(hwnd)이 반환됨
		lpszClass, // 윈도우 클래스 이름
		lpszClass, // 윈도우 타이틀 이름
				   //윈도우 스타일 :
		(WS_VSCROLL | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
			WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX),
		WIN_XPOS, // 윈도우 위치, x좌표
		WIN_YPOS, // 윈도우 위치, y좌표
		WIN_Width, // 윈도우 폭
		WIN_Height, // 윈도우 높이
		NULL, // 부모 윈도우 핸들
		(HMENU)NULL, // 메뉴 핸들
		hInstance, // 응용 프로그램 ID
		NULL);	// 생성된 윈도우 정보


				/*====•윈도우 스타일============================================================
				•WS_OVERLAPPED: 디폴트 윈도우
				•WS_CAPTION: 타이틀 바를 가진 윈도우
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
/*
hWnd: 메시지를 보내는 윈도우의 핸들
Msg : 처리될 윈도우 메시지의 코드나 ID
wParam : 메시지 부가정보(숫자, ID, 분류 등)
lParam : 메시지 부가정보(숫자, ID, 분류 등)
LRESULT : win32환경에서 메시지 처리를 마친 후 OS에 신호를 주기 위한 값, long 타입
WPARAM : 핸들이나 정수값을 위해 사용하는 타입
LPARAM : 포인터 전달에 사용되는 타입*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc; //디바이스컨텍스트 핸들
	PAINTSTRUCT ps;

	static HBRUSH hBrush[FigureCount], oldBrush;
	static HPEN hPen, oldPen;
	static TCHAR switchnum[FigureCount+1] = { 0 };
	static int count, tempcount, check;
	static int xPos1[FigureCount] , yPos1[FigureCount], xPos2[FigureCount], yPos2[FigureCount];
	static int triA, triB, triC, R[FigureCount], G[FigureCount], B[FigureCount];
	static POINT triangle[FigureCount][3] = { 0 };
	int i;

	switch (iMessage)
	{
	case WM_CREATE:
		CreateCaret(hwnd, NULL, 0, 15);
		//ShowCaret(hwnd); // 빈 화면에 캐럿 표시
		srand((unsigned)time(NULL));
		for (i = 0; i < FigureCount; i++)
		{
			R[i] = rand() % 256;
			G[i] = rand() % 256;
			B[i] = rand() % 256;
		}
		count = 0;
		check = 0;
		return 0;
	
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		if ((wParam == 'e' || wParam == 'E') && check == 0) //ellipse
		{
			if (count == FigureCount) count = 0;
			xPos1[count] = rand() % 500;
			yPos1[count] = rand() % 500;
			xPos2[count] = rand() % 500;
			yPos2[count] = rand() % 500;
			switchnum[count++] = wParam;
			switchnum[count] = '\0';
		}
		else if ((wParam == 't' || wParam == 'T') && check == 0)//triangle
		{
			if (count == FigureCount) count = 0;
			triA = rand() % 500;
			triB = rand() % 500;
			triC = rand() % 500;
			triangle[count][0] = { triA, triB };
			triangle[count][1] = { triA, triC };
			triangle[count][2] = { triB, triC };
			switchnum[count++] = wParam;
			switchnum[count] = '\0';
		}
		else if ((wParam == 'r' || wParam == 'R') && check == 0)//rectangle
		{
			if (count == FigureCount)	count = 0;

			xPos1[count] = rand() % 500;
			yPos1[count] = rand() % 500;
			xPos2[count] = rand() % 500;
			yPos2[count] = rand() % 500;
			switchnum[count++] = wParam;
			switchnum[count] = '\0';
		}
		else if ((wParam >= '1' && wParam <= '5') && check == 0) //TODO: FigureCount가 바뀔경우 수정.
		{
			if(wParam == '1') tempcount = 0;
			else if (wParam == '2') tempcount = 1;
			else if (wParam == '3') tempcount = 2;
			else if (wParam == '4') tempcount = 3;
			else if (wParam == '5') tempcount = 4;
		}
		else if ((wParam == VK_DELETE) && check == 0)
		{
			switchnum[tempcount] = '\0';
			xPos1[tempcount] = 0;
			yPos1[tempcount] = 0;
			xPos2[tempcount] = 0;
			yPos2[tempcount] = 0;
			triangle[tempcount][0] = { 0, 0 };
			triangle[tempcount][1] = { 0, 0 };
			triangle[tempcount][2] = { 0, 0 };
		}
		check = 1;
		InvalidateRect(hwnd, NULL, TRUE);
		ReleaseDC(hwnd, hdc);

		break;
	case WM_KEYUP:
		check = 0;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (i = 0; i < FigureCount; i++)
			hBrush[i] = CreateSolidBrush(RGB(R[i], G[i], B[i]));
		hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		//이하 출력
		//SetTextColor(hdc, RGB(255, 0, 0));
		//TextOut(hdc, x, y, str[linecount], lstrlen(str[linecount]) );
		//DrawText(hdc, str[linecount], lstrlen(str[linecount]), &rect, DT_SINGLELINE);
		//HideCaret(hwnd);

		for (i = 0; i < FigureCount; i++)
		{
			switch (switchnum[i])
			{
			case 'e': case 'E':
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush[i]);
				Ellipse(hdc, xPos1[i], yPos1[i], xPos2[i], yPos2[i]);
				break;
			case 't': case 'T':
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush[i]);
				Polygon(hdc, triangle[i], 3);
				break;
			case 'r': case 'R':
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush[i]);
				Rectangle(hdc, xPos1[i], yPos1[i], xPos2[i], yPos2[i]);
				break;
			}
		}
		oldPen = (HPEN)SelectObject(hdc, hPen);
		switch (switchnum[tempcount])
		{
		case 'e': case 'E':
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[tempcount]);
			Ellipse(hdc, xPos1[tempcount], yPos1[tempcount], xPos2[tempcount], yPos2[tempcount]);
			break;
		case 't': case 'T':
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[tempcount]);
			Polygon(hdc, triangle[tempcount], 3);
			break;
		case 'r': case 'R':
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[tempcount]);
			Rectangle(hdc, xPos1[tempcount], yPos1[tempcount], xPos2[tempcount], yPos2[tempcount]);
			break;
		}
		SelectObject(hdc, oldPen);
		SelectObject(hdc, oldBrush);
		DeleteObject(hPen);
		for (i = 0; i < FigureCount; i++)
			DeleteObject(hBrush[i]);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hwnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	} //처리할 메시지만 case문에 나열
	return DefWindowProc(hwnd, iMessage, wParam, lParam);
	// CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}

/*
Penstyle
PS_SOLID
PS_DASH
PS_DOT
PS_DASHDOT
PS_DASHDOTDOT

•int DrawText(
HDC hdc,
LPCSTR lpString,
int nLength,
LPRECT lpRect,
//typedef struct tagRECT {
//	LONG left; // x1
//	LONG top; // y1
//	LONG right; // x2
//	LONG bottom; // y2
//} RECT;
UINT Flags
);
•HDC hdc: BeginPaint()나 GetDC()를 통해 얻어온 DC핸들
•LPCSTR lpString: 출력 문자열
•int nLength: 문자열 길이
•LPRECT lpRect: 문자열을 출력할 박스영역 구조체의 주소 (RECT *)
•UINT Flags: 출력 방법

•DrawText 함수의 Flag :
•DT_SINGLELINE : 박스 영역 안에 한 줄로 출력
•DT_LEFT : 박스 영역 내에서 왼쪽 정렬
•DT_CENTER : 박스 영역 내에서 가운데 정렬
•DT_RIGHT : 박스 영역 내에서 오른쪽 정렬
•DT_VCENTER : 박스 영역의 상하에서 가운데 출력
•DT_TOP : 박스 영역의 상하에서 위쪽에 출력
•DT_BOTTOM : 박스 영역의 상하에서 아래쪽에 출력
•DT_CALCRECT : 문자열을 출력한다면 차지할 공간의 크기 측정
•DT_WORDBREAK : 박스 영역의 끝에서 자동개행
•DT_NOCLIP : 박스 영역의 경계를 벗어나도 문자열을 자르지않고 그대로 출력

예 :
•DT_TOP | DT_CENTER | DT_SINGLELINE
•사각형 영역의 위쪽 가운데에 한 줄로 출력

- COLORREF SetBkColor (HDC hdc, COLORREF crColor);
•hdc: 디바이스 컨텍스트 핸들
•crColor: 배경색

- COLORREF SetTextColor (HDC hdc, COLORREF crColor);
•hdc: 디바이스 컨텍스트 핸들
•crColor: 문자색

- Int SetBkMode (HDC hdc, int iBkMode);
•hdc: 디바이스 컨텍스트 핸들
•iBkMode: 배경 모드 (OPAQUE/TRANSPARENT)

•사용 예) SetTextColor (hdc, RGB(255, 0, 0));
DrawText (hdc,"HelloWorld",10,&rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

-윈도우의 색 지정 : RGB(Red, Green, Blue) 삼원색 사용
COLORREF color;
COLORREF: DWORD 형태의 타입
COLORREF RGB{
BYTE byRed, // 색상 중 붉은 색
BYTE byGreen, // 색상 중 초록 색
BYTE byBlue // 색상 중 푸른 색
}
사용 예) COLORREF Color; Color = RGB (255, 0, 0);
*/