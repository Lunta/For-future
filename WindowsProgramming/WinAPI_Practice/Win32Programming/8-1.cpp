#include <windows.h> 
#include <tchar.h>
#include <ctime>
#include <math.h>
#include <atlimage.h> 
#include "resource.h"

#define WIN_FRAMECLASSNAME TEXT("FrameWindow")
#define WIN_CHILDCLASSNAME TEXT("ChildWindow")
#define WIN_TITLENAME TEXT("MDI")
#define WIN_XPOS 0 
#define WIN_YPOS 0 
#define WIN_Width 800 
#define WIN_Height 600
#define STRMAX 100
#define Dlgtimer 1
#define Wintimer 2

typedef struct {
	TCHAR str[10][STRMAX] = { 0 };
	SIZE size;
	int count, linecount, wp;
}Data;

HINSTANCE g_hInst;
HWND g_hwnd;
HWND hwndClient;
HWND hwndChild[5];
int idx, midx;
Data data[5];
HANDLE hFile;
OPENFILENAME OFN;
char buff[1000];

LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG Message;
	WNDCLASS WndClass; //구조체 정의
	RECT rc = { 0, 0, WIN_Width, WIN_Height };
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX |
		WS_BORDER | WS_MAXIMIZEBOX; //WS_HSCROLL | WS_VSCROLL | WS_THICKFRAME
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0; // O/S 사용 여분 메모리(Class)
	WndClass.cbWndExtra = 0; // O/S 사용 여분 메모리(Window)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서 유형
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //아이콘유형 WndClass.hIconSM : 작은아이콘
	WndClass.lpfnWndProc = FrameWndProc; // 프로시저 함수명
	WndClass.hInstance = hInstance; //응용 프로그램 ID
	WndClass.lpszClassName = WIN_FRAMECLASSNAME; // 클래스 이름
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU7_1); // 메뉴 이름
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = ChildWndProc; // 프로시저 함수명
	WndClass.lpszClassName = WIN_CHILDCLASSNAME; // 클래스 이름

	RegisterClass(&WndClass);

	AdjustWindowRect(&rc, dwStyle, FALSE);
	hwnd = CreateWindow( // 윈도우가 생성되면 핸들(hwnd)이 반환됨
		WIN_FRAMECLASSNAME,	// 윈도우 클래스 이름
		WIN_TITLENAME,	 // 윈도우 타이틀 이름
		dwStyle,	 //윈도우 스타일
		WIN_XPOS,	// 윈도우 위치, x좌표
		WIN_YPOS,	// 윈도우 위치, y좌표
		rc.right - rc.left, // 윈도우 폭
		rc.bottom - rc.top, // 윈도우 높이
		NULL,		// 부모 윈도우 핸들
		(HMENU)NULL, // 메뉴 핸들
		hInstance,	 // 응용 프로그램 ID
		NULL);		// 생성된 윈도우 정보
	g_hwnd = hwnd;
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message); // Shift ‘a’ -> 대문자 ‘A’
		DispatchMessage(&Message); // WinMain -> WinProc
	}
	return Message.wParam;
}

LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	CLIENTCREATESTRUCT clientcreate; // 차일드 생성을 관리하기 위핚 구조체
	MDICREATESTRUCT mdicreate[5];
	static RECT rc;
	static TCHAR str[STRMAX], lpstrFile[STRMAX] = L"";
	static DWORD size = 1000;

	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 30, nullptr);
		GetWindowRect(hWnd, &rc);
		srand((unsigned)time(0));
		idx = 0;
		midx = 0;
		clientcreate.hWindowMenu = GetSubMenu(GetMenu(hWnd), 0);
		clientcreate.idFirstChild = 100; // 첫 번째 차일드 ID
		hwndClient = CreateWindow(TEXT("MDICLIENT"),
			NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, // 윈도우 스타일
			0, 0, 0, 0, // 좌표
			hWnd, NULL,
			g_hInst, (LPSTR)&clientcreate);
		ShowWindow(hwndClient, SW_SHOW); // 클라이언트 윈도우 출력
		break;
	case WM_LBUTTONDOWN:
		LOWORD(lParam);
		HIWORD(lParam);

		InvalidateRect(hWnd, nullptr, false);
		break;
	case WM_MOUSEMOVE:

		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_NEW:
			mdicreate[midx].szClass = WIN_CHILDCLASSNAME;
			mdicreate[midx].szTitle = WIN_TITLENAME;
			mdicreate[midx].hOwner = g_hInst; // 프로그램 인스턴스 핶들
			mdicreate[midx].x = 0; // 자식 윈도우 X좌표
			mdicreate[midx].y = 0; // 자식 윈도우 Y좌표
			mdicreate[midx].cx = 800; // 자식 윈도우 폭
			mdicreate[midx].cy = 600; // 자식 윈도우 높이
			mdicreate[midx].style = 0;
			mdicreate[midx].lParam = 0; // MDI 클라이언트 윈도우를 맊들어라

			hwndChild[midx] = (HWND)SendMessage(hwndClient, WM_MDICREATE,
				0, (LPARAM)(LPMDICREATESTRUCT)&mdicreate[midx]);
			midx++;
			break;
		case ID_LOAD:
			memset(&OFN, 0, sizeof(OPENFILENAME)); // 초기화
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = L"Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = L"."; // 초기 디렉토리
			if (GetOpenFileName(&OFN) != 0) {
				mdicreate[midx].szClass = WIN_CHILDCLASSNAME;
				mdicreate[midx].szTitle = WIN_TITLENAME;
				mdicreate[midx].hOwner = g_hInst; // 프로그램 인스턴스 핶들
				mdicreate[midx].x = 0; // 자식 윈도우 X좌표
				mdicreate[midx].y = 0; // 자식 윈도우 Y좌표
				mdicreate[midx].cx = 800; // 자식 윈도우 폭
				mdicreate[midx].cy = 600; // 자식 윈도우 높이
				mdicreate[midx].style = 0;
				mdicreate[midx].lParam = 0; // MDI 클라이언트 윈도우를 맊들어라

				hwndChild[midx] = (HWND)SendMessage(hwndClient, WM_MDICREATE,
					0, (LPARAM)(LPMDICREATESTRUCT)&mdicreate[midx]);
				midx++;
				hFile = CreateFile(OFN.lpstrFile,
					GENERIC_READ,
					FILE_SHARE_READ, NULL,
					OPEN_EXISTING, 0, 0); 
					memset(buff, 0, (STRMAX - 1) * sizeof(char));
					ReadFile(hFile, buff, size, &size, NULL);
					MultiByteToWideChar(CP_ACP, 0, buff, -1, data[midx - 1].str[0], STRMAX * 10 - 10);
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 1000; j++)
					{
						if (i == 9 && j > 99) break;
						else if (data[midx - 1].str[i][j] == '\n')
						{
							if(i < 9) lstrcpy(data[midx - 1].str[i+1], data[midx - 1].str[i] + j + 1);
							data[midx - 1].str[i][j - 1] = '\0';
							data[midx - 1].count = j - 1;
							data[midx - 1].linecount = i;
							break;
						}
					}
				}
				CloseHandle(hFile);
			}
			break;
		case ID_SAVE:
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter =
				L"Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = L".";
			if (GetSaveFileName(&OFN) != 0) {
				hFile = CreateFile(OFN.lpstrFile,
					GENERIC_WRITE,
					FILE_SHARE_WRITE, NULL,
					CREATE_ALWAYS, 0, 0); //OPEN_EXISTING
				for (int i = 0; i < data[idx].linecount + 1; i++)
				{
					memset(buff, 0, 999 * sizeof(char));
					WideCharToMultiByte(CP_ACP, 0, data[idx].str[i], -1, buff, STRMAX - 1, NULL, NULL);
					WriteFile(hFile, buff, strlen(buff), &size, NULL);
					WriteFile(hFile, "\r\n", strlen("\r\n"), &size, NULL);
				}
				CloseHandle(hFile);
			}
			break;
		}
		break;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		return 0;
	}
	return(DefFrameProc(hWnd, hwndClient, iMessage, wParam, lParam));
}

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int i;

	switch (iMessage)
	{
	case WM_CREATE:
		data[idx].count = 0;
		data[idx].linecount = 0;
		i = 0;
		return 0;
	case WM_LBUTTONDOWN:
		for (int i = 0; i < midx + 1; i++)
		{
			if (hwndChild[i] == (HWND)SendMessage(hwndClient, WM_MDIGETACTIVE, 0, 0))
			{
				idx = i;
				InvalidateRect(hwndChild[i], nullptr, true);
			}
		}
		break;
	case WM_CHAR:
		hdc = GetDC(hwndChild[idx]);
		if (wParam == VK_BACK) {
			if (data[idx].count == 0 && data[idx].linecount != 0) {
				data[idx].count = lstrlen(data[idx].str[--data[idx].linecount]);
			}
			else data[idx].str[data[idx].linecount][--data[idx].count] = '\0';
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (wParam == VK_RETURN) {
			data[idx].linecount++;
			data[idx].count = 0;
		}
		else if (wParam == VK_TAB)
		{
			data[idx].str[data[idx].linecount][data[idx].count++] = ' ';
			data[idx].str[data[idx].linecount][data[idx].count++] = ' ';
			data[idx].str[data[idx].linecount][data[idx].count++] = ' ';
			data[idx].str[data[idx].linecount][data[idx].count++] = ' ';
			data[idx].str[data[idx].linecount][data[idx].count] = '\0';
		}
		else if (wParam == '\\')
		{
			data[idx].wp = '\\';

		}
		else if (wParam == VK_ESCAPE)
		{
			for (data[idx].linecount = 0; data[idx].linecount < 10; data[idx].linecount++)
				for (data[idx].count = 0; data[idx].count < 100; data[idx].count++) {
					data[idx].str[data[idx].linecount][data[idx].count] = '\0';
				}
			data[idx].linecount = 0;
			data[idx].count = 0;
			InvalidateRect(hwndChild[idx], NULL, TRUE);
		}
		else {
			data[idx].str[data[idx].linecount][data[idx].count++] = wParam;
			data[idx].str[data[idx].linecount][data[idx].count] = '\0';
		}
		InvalidateRect(hwndChild[idx], NULL, TRUE);
		ReleaseDC(hwndChild[idx], hdc);

		break;
	case WM_PAINT:
		hdc = BeginPaint(hwndChild[idx], &ps);
		//이하 출력
		CreateCaret(hwndChild[idx], NULL, 5, 15);
		//ShowCaret(hwndChild[idx]); // 빈 화면에 캐럿 표시
		GetTextExtentPoint(hdc, data[idx].str[data[idx].linecount], lstrlen(data[idx].str[data[idx].linecount]), &data[idx].size);
		SetCaretPos(data[idx].size.cx, data[idx].linecount * 20);
		if (data[idx].wp == '\\')
		{
			TextOut(hdc, 0, data[idx].linecount * 20, data[idx].str[data[idx].linecount], lstrlen(data[idx].str[data[idx].linecount]));
			SetCaretPos(0, data[idx].linecount * 20);
			data[idx].wp = 0;
		}
		else for (i = 0; i < data[idx].linecount + 1; i++) {
			TextOut(hdc, 0, i * 20, data[idx].str[i], lstrlen(data[idx].str[i]));
		}
		EndPaint(hwndChild[idx], &ps);
		break;
	case WM_DESTROY:
		HideCaret(hwndChild[idx]);
		DestroyCaret();
		midx--;
		break;
	}
	return DefMDIChildProc(hWnd, iMessage, wParam, lParam);
}
