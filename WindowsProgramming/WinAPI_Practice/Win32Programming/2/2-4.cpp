#include <windows.h> 
#include <tchar.h>
#include <cstdlib>
#include <ctime>

#define RectWidth 40
#define RectHeight 30

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("window program 1-2");

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

void DrawTextRect(HDC hdc, RECT rect, int xcount, int ycount, int num);

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

	RegisterClass(&WndClass);// •ATOM RegisterClassEx ( CONST WNDCLASSEX *lpwcx );
							 // •&wndclass : 앞서 정의한 윈도우 클래스의 주소

	hwnd = CreateWindow( // 윈도우가 생성되면 핸들(hwnd)이 반환됨
		lpszClass, // 윈도우 클래스 이름
		lpszClass, // 윈도우 타이틀 이름
		(WS_VSCROLL | WS_OVERLAPPED | WS_CAPTION |
			WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX), // 윈도우 스타일
		0, // 윈도우 위치, x좌표
		0, // 윈도우 위치, y좌표
		850, // 윈도우 폭
		650, // 윈도우 높이
		NULL, // 부모 윈도우 핸들
		(HMENU)NULL, // 메뉴 핸들
		hInstance, // 응용 프로그램 ID
		NULL); // 생성된 윈도우 정보

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
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc; //디바이스컨텍스트 핸들
	PAINTSTRUCT ps;
	RECT rect = { 0 };
	int xcount = 0, ycount = 0, num = 0;
	int switchnum = 0;

	srand((unsigned int)time(NULL));

	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//이하 출력
		SetTextColor(hdc, RGB(255, 0, 0));
		//TextOut(hdc, x, y, _T(str), _tcslen(_T(str) )  );
		//DrawText(hdc, _T(str), _tcslen(_T(str) ), &rect, DT_Flag);

		num = rand() % 6;
		for (ycount = 0; ycount < 20; ycount++)
		{
			for (xcount = 0; xcount < 20; xcount++)
			{
				if(switchnum%2 == 0)
					DrawTextRect(hdc, rect, xcount, ycount, num);
				else if(num == 0)
					DrawTextRect(hdc, rect, xcount, ycount, num);
				switchnum++;
			}
			if(ycount%(num+1) == num)
				switchnum++;
		}

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	} //처리할 메시지만 case문에 나열
	return DefWindowProc(hwnd, iMessage, wParam, lParam);
	// CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}

void DrawTextRect(HDC hdc, RECT rect, int xcount, int ycount, int num)
{
	TCHAR str[10] = { 0 };
	wsprintf(str,TEXT("(%d, %d) "),ycount, xcount);
	rect = { RectWidth*xcount, RectHeight*ycount,RectWidth + RectWidth*xcount, RectHeight + RectHeight*ycount };
	DrawText(hdc, str, lstrlen(str), &rect, DT_CENTER | DT_VCENTER | DT_NOCLIP);
}