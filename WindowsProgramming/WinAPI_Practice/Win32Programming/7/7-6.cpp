#include <Windows.h>
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
#define WIN_Width 1200 
#define WIN_Height 700

#define STRMAX 100

#define BUTTON_SIZE 50
#define IDC_TILE1_BUTTON 100
#define IDC_TILE2_BUTTON 101
#define IDC_TILE3_BUTTON 102
#define IDC_TILE4_BUTTON 103
#define IDC_TILE5_BUTTON 104
#define IDC_TILE6_BUTTON 105
#define IDC_OBJECT1_BUTTON 106
#define IDC_OBJECT2_BUTTON 107
#define IDC_EXIT_BUTTON 108

#define IDC_MAPWIDTH_EDIT 110
#define IDC_MAPHEIGHT_EDIT 111
#define IDC_TILEWIDTH_EDIT 112
#define IDC_TILEHEIGHT_EDIT 113

#define IDC_BKIMAGE_COMBO 120
enum KindOfTile {
	// 1~6번 타일
	tile1 = 1, tile2, tile3, tile4, tile5, tile6
};
enum KindOfObject {
	obj1 = 1, obj2 = 2
};
typedef struct TILE
{
	RECT rc;
	char tilekind;
	TILE * prev;
	TILE * next;

	void Set(RECT r, char tk, TILE * p);
	void Delete();
}Tile;
typedef struct OBJECT
{
	RECT rc;
	char objectkind;

	OBJECT * prev;
	OBJECT * next;

	void Set(RECT r, char ok, OBJECT * p);
	void Delete();
}Object;

HINSTANCE g_hInst;
HWND g_hwnd, hwndChild;
HWND hCombo;
HWND hButton[9], hEdit[4];
TCHAR BK[10];
CImage imgBK_sky, imgBK_hill;
CImage imgt, imgO1, imgO2;
Tile * thead = nullptr, *ttail = nullptr;
Object * ohead = nullptr, *otail = nullptr;
Tile * tmp;
Object * otmp;
char tile;
char obj;
unsigned short mapWidth, mapHeight, tileWidth, tileHeight;
bool isO;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);	
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
	WndClass.lpfnWndProc = WndProc; // 프로시저 함수명
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc;
	PAINTSTRUCT ps;
	static HBITMAP memBit;
	static HWND hwndClient; // 클라이언트 윈도우
	CLIENTCREATESTRUCT clientcreate; // 차일드 생성을 관리하기 위핚 구조체
	static RECT rc;
	static int cselection;
	HBITMAP hBit[6], hObjBit[2];
	HWND hButtontemp;
	int buffer;

	switch (iMessage) {
	case WM_CREATE:

		GetClientRect(hWnd, &rc);
		srand((unsigned)time(0));
		isO = false;
		tile = 1;
		mapWidth = rc.right;
		mapHeight = rc.bottom;
		tileWidth = tileHeight = 30;
		imgt.Load(L"tile.png");
		imgO1.Load(L"Obj1.png");
		imgO2.Load(L"Obj2.png");

		clientcreate.hWindowMenu = GetSubMenu(GetMenu(hWnd), 0);
		clientcreate.idFirstChild = 100; // 첫 번째 차일드 ID
		hwndClient = CreateWindow(TEXT("MDICLIENT"),
			NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, // 윈도우 스타일
			0, 0, 0, 0, // 좌표
			hWnd, NULL,
			g_hInst, (LPSTR)&clientcreate);
		ShowWindow(hwndClient, SW_SHOW); // 클라이언트 윈도우 출력

		GetClientRect(hWnd, &rc);
		hwndChild = CreateWindowEx(WS_EX_CLIENTEDGE,
			WIN_CHILDCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			0, 0, (rc.right * 3) / 4, rc.bottom - 1,
			hWnd, NULL, g_hInst, NULL);

		hButton[0] = CreateWindow(L"button", L"Tile 1",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			(rc.right * 3) / 4 + 10, 25, BUTTON_SIZE, BUTTON_SIZE, hWnd,
			(HMENU)IDC_TILE1_BUTTON, g_hInst, NULL);
		hButton[1] = CreateWindow(L"button", L"Tile 2",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			(rc.right * 3) / 4 + 10 + BUTTON_SIZE, 25, BUTTON_SIZE, BUTTON_SIZE, hWnd,
			(HMENU)IDC_TILE2_BUTTON, g_hInst, NULL);
		hButton[2] = CreateWindow(L"button", L"Tile 3",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			(rc.right * 3) / 4 + 10 + (BUTTON_SIZE * 2), 25, BUTTON_SIZE, BUTTON_SIZE, hWnd,
			(HMENU)IDC_TILE3_BUTTON, g_hInst, NULL);
		hButton[3] = CreateWindow(L"button", L"Tile 4",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			(rc.right * 3) / 4 + 10, 25 + BUTTON_SIZE, BUTTON_SIZE, BUTTON_SIZE, hWnd,
			(HMENU)IDC_TILE4_BUTTON, g_hInst, NULL);
		hButton[4] = CreateWindow(L"button", L"Tile 5",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			(rc.right * 3) / 4 + 10 + BUTTON_SIZE, 25 + BUTTON_SIZE, BUTTON_SIZE, BUTTON_SIZE, hWnd,
			(HMENU)IDC_TILE5_BUTTON, g_hInst, NULL);
		hButton[5] = CreateWindow(L"button", L"Tile 6",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			(rc.right * 3) / 4 + 10 + (BUTTON_SIZE * 2), 25 + BUTTON_SIZE, BUTTON_SIZE, BUTTON_SIZE, hWnd,
			(HMENU)IDC_TILE6_BUTTON, g_hInst, NULL);

		CreateWindow(L"button", L"Tile", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 
			(rc.right * 3) / 4 + 5, 5, BUTTON_SIZE * 3 + 10, BUTTON_SIZE * 2 + 25, 
			hWnd, (HMENU)0, g_hInst, NULL);

		hButton[6] = CreateWindow(L"button", L"Object 1",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			(rc.right * 3) / 4 + 10, 50 + (BUTTON_SIZE * 2), BUTTON_SIZE, BUTTON_SIZE, hWnd,
			(HMENU)IDC_OBJECT1_BUTTON, g_hInst, NULL);
		hButton[7] = CreateWindow(L"button", L"Object 2",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			(rc.right * 3) / 4 + 10 + BUTTON_SIZE, 50 + (BUTTON_SIZE * 2), BUTTON_SIZE, BUTTON_SIZE, hWnd,
			(HMENU)IDC_OBJECT2_BUTTON, g_hInst, NULL);

		CreateWindow(L"button", L"Object", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			(rc.right * 3) / 4 + 5, 30 + (BUTTON_SIZE * 2), BUTTON_SIZE * 3 + 10, BUTTON_SIZE * 2 + 25,
			hWnd, (HMENU)0, g_hInst, NULL);

		hButton[8] = CreateWindow(L"button", L"Exit",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			rc.right - (BUTTON_SIZE * 3) / 2 - 1, rc.bottom - (BUTTON_SIZE * 2) / 3 - 1, (BUTTON_SIZE* 3) / 2, (BUTTON_SIZE * 2) / 3, hWnd,
			(HMENU)IDC_EXIT_BUTTON, g_hInst, NULL);

		hEdit[0] = CreateWindow(L"edit", L"Map Width", WS_CHILD | WS_VISIBLE | WS_BORDER,
			(rc.right * 3) / 4 + 20, (BUTTON_SIZE * 6), 50, 20, hWnd,
			(HMENU)IDC_MAPWIDTH_EDIT, g_hInst, NULL);
		hEdit[1] = CreateWindow(L"edit", L"Map Height", WS_CHILD | WS_VISIBLE | WS_BORDER,
			(rc.right * 3) / 4 + (BUTTON_SIZE * 2), (BUTTON_SIZE * 6), 50, 20, hWnd,
			(HMENU)IDC_MAPHEIGHT_EDIT, g_hInst, NULL);

		CreateWindow(L"static", L"Map Width", WS_CHILD | WS_VISIBLE,
			(rc.right * 3) / 4 + 10, 25 + (BUTTON_SIZE * 5), 70, 20,
			hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(L"static", L"Map Height", WS_CHILD | WS_VISIBLE,
			(rc.right * 3) / 4 + (BUTTON_SIZE * 2) - 15, 25 + (BUTTON_SIZE * 5), 80, 20,
			hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(L"button", L"Map Size", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			(rc.right * 3) / 4 + 5, 5 + (BUTTON_SIZE * 5), BUTTON_SIZE * 3 + 10, BUTTON_SIZE + 20,
			hWnd, (HMENU)0, g_hInst, NULL);

		hEdit[2] = CreateWindow(L"edit", L"Tile Width", WS_CHILD | WS_VISIBLE | WS_BORDER,
			(rc.right * 3) / 4 + 20, 15 + (BUTTON_SIZE * 7), 50, 20, hWnd,
			(HMENU)IDC_TILEWIDTH_EDIT, g_hInst, NULL);
		hEdit[3] = CreateWindow(L"edit", L"Tile Height", WS_CHILD | WS_VISIBLE | WS_BORDER,
			(rc.right * 3) / 4 + (BUTTON_SIZE * 2), 15 + (BUTTON_SIZE * 7), 50, 20, hWnd,
			(HMENU)IDC_TILEHEIGHT_EDIT, g_hInst, NULL);

		CreateWindow(L"static", L"Tile Width", WS_CHILD | WS_VISIBLE,
			(rc.right * 3) / 4 + 10, 45 + (BUTTON_SIZE * 6), 70, 20,
			hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(L"static", L"Tile Height", WS_CHILD | WS_VISIBLE,
			(rc.right * 3) / 4 + (BUTTON_SIZE * 2) - 15, 45 + (BUTTON_SIZE * 6), 80, 20,
			hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(L"button", L"Tile Size", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			(rc.right * 3) / 4 + 5, 25 + (BUTTON_SIZE * 6), BUTTON_SIZE * 3 + 10, BUTTON_SIZE + 20,
			hWnd, (HMENU)0, g_hInst, NULL);

		hCombo = CreateWindow(L"combobox", NULL,
			WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
			(rc.right * 3) / 4 + 10, 25 + (BUTTON_SIZE * 8), BUTTON_SIZE * 3 + 10, BUTTON_SIZE + 20,
			hWnd, (HMENU)IDC_BKIMAGE_COMBO, g_hInst, NULL);

		CreateWindow(L"static", L"Back Ground", WS_CHILD | WS_VISIBLE,
			(rc.right * 3) / 4 + 10, 5 + (BUTTON_SIZE * 8), 100, 20,
			hWnd, (HMENU)0, g_hInst, NULL);

		SetDlgItemInt(hWnd, IDC_MAPWIDTH_EDIT, mapWidth, true);
		SetDlgItemInt(hWnd, IDC_MAPHEIGHT_EDIT, mapHeight, true);
		SetDlgItemInt(hWnd, IDC_TILEWIDTH_EDIT, tileWidth, true);
		SetDlgItemInt(hWnd, IDC_TILEHEIGHT_EDIT, tileHeight, true);

		hBit[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_TILE1));
		hBit[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_TILE2));
		hBit[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_TILE3));
		hBit[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_TILE4));
		hBit[4] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_TILE5));
		hBit[5] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_TILE1));
		hObjBit[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_OBJECT1));
		hObjBit[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_OBJECT2));
		SendMessage(hButton[0], BM_SETIMAGE, 0, (LPARAM)hBit[0]);
		SendMessage(hButton[1], BM_SETIMAGE, 0, (LPARAM)hBit[1]);
		SendMessage(hButton[2], BM_SETIMAGE, 0, (LPARAM)hBit[2]);
		SendMessage(hButton[3], BM_SETIMAGE, 0, (LPARAM)hBit[3]);
		SendMessage(hButton[4], BM_SETIMAGE, 0, (LPARAM)hBit[4]);
		SendMessage(hButton[5], BM_SETIMAGE, 0, (LPARAM)hBit[5]);
		SendMessage(hButton[6], BM_SETIMAGE, 0, (LPARAM)hObjBit[0]);
		SendMessage(hButton[7], BM_SETIMAGE, 0, (LPARAM)hObjBit[1]);

		hCombo = GetDlgItem(hWnd, IDC_BKIMAGE_COMBO);
		imgBK_sky.Load(TEXT("배경.bmp"));
		imgBK_hill.Load(TEXT("5-8배경.png"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)(L"SKY"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)(L"HILL"));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		memBit = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		SelectObject(memdc, memBit);
		FillRect(memdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		//

		// hdc에 복사
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, memdc, 0, 0, SRCCOPY);

		SelectObject(memdc, NULL);
		DeleteDC(memdc);
		DeleteObject(memBit);
		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_MAPWIDTH_EDIT:
			if (HIWORD(wParam) == EN_KILLFOCUS) {
				buffer = GetDlgItemInt(hWnd, IDC_MAPWIDTH_EDIT, 0, true);
				if (buffer != 0) mapWidth = buffer;
				else SetDlgItemInt(hWnd, IDC_MAPWIDTH_EDIT, mapWidth, true);
				InvalidateRect(g_hwnd, nullptr, true);
			}
			break;
		case IDC_MAPHEIGHT_EDIT:
			if (HIWORD(wParam) == EN_KILLFOCUS) {
				buffer = GetDlgItemInt(hWnd, IDC_MAPHEIGHT_EDIT, 0, true);
				if (buffer != 0) mapHeight = buffer;
				else SetDlgItemInt(hWnd, IDC_MAPHEIGHT_EDIT, mapHeight, true);
				InvalidateRect(g_hwnd, nullptr, true);
			}
			break;
		case IDC_TILEWIDTH_EDIT:
			if (HIWORD(wParam) == EN_KILLFOCUS) {
				buffer = GetDlgItemInt(hWnd, IDC_TILEWIDTH_EDIT, 0, true);
				if (buffer != 0) tileWidth = buffer;
				else SetDlgItemInt(hWnd, IDC_TILEWIDTH_EDIT, tileWidth, true);
				InvalidateRect(g_hwnd, nullptr, true);
			}
			break;
		case IDC_TILEHEIGHT_EDIT:
			if (HIWORD(wParam) == EN_KILLFOCUS) {
				buffer = GetDlgItemInt(hWnd, IDC_TILEHEIGHT_EDIT, 0, true);
				if (buffer != 0) tileHeight = buffer;
				else SetDlgItemInt(hWnd, IDC_TILEHEIGHT_EDIT, tileHeight, true);
				InvalidateRect(g_hwnd, nullptr, true);
			}
			break;
		case IDC_TILE1_BUTTON:
			if (HIWORD(wParam) == BN_CLICKED) {
				tile = 1;
				isO = false;
			}
			break;
		case IDC_TILE2_BUTTON:
			if (HIWORD(wParam) == BN_CLICKED) {
				tile = 2;
				isO = false;
			}
			break;
		case IDC_TILE3_BUTTON:
			if (HIWORD(wParam) == BN_CLICKED) {
				tile = 3;
				isO = false;
			}
			break;
		case IDC_TILE4_BUTTON:
			if (HIWORD(wParam) == BN_CLICKED) {
				tile = 4;
				isO = false;
			}
			break;
		case IDC_TILE5_BUTTON:
			if (HIWORD(wParam) == BN_CLICKED) {
				tile = 5;
				isO = false;
			}
			break;
		case IDC_TILE6_BUTTON:
			if (HIWORD(wParam) == BN_CLICKED) {
				tile = 6;
				isO = false;
			}
			break;
		case IDC_OBJECT1_BUTTON:
			if (HIWORD(wParam) == BN_CLICKED) {
				obj = 1;
				isO = true;
			}
			break;
		case IDC_OBJECT2_BUTTON:
			if (HIWORD(wParam) == BN_CLICKED) {
				obj = 2;
				isO = true;
			}
			break;
		case IDC_BKIMAGE_COMBO:
			if (HIWORD(wParam) == CBN_SELCHANGE) // 하나가 선택됨(상태 변경)
				cselection = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			//SendMessage(hCombo, CB_GETLBTEXTLEN, selection, 0);문자열 길이 반환
			SendMessage(hCombo, CB_GETLBTEXT, cselection, (LPARAM)BK);
			InvalidateRect(g_hwnd, nullptr, true);
			break;
		case IDC_EXIT_BUTTON:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				KillTimer(g_hwnd, 1);
				KillTimer(g_hwnd, 2);
				PostQuitMessage(0);
			}
			break;
		}
		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc;
	PAINTSTRUCT ps;
	HBITMAP memBit;
	static RECT rc;
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:

		break;
	case WM_MOUSEMOVE:

		break;
	case WM_LBUTTONUP:
		if (hWnd == hwndChild)
		{
			SetFocus(hwndChild);
			GetClientRect(hwndChild, &rc);
		}
		for (int i = 0; i < mapHeight / tileHeight; i++)
			for (int j = 0; j < mapWidth / tileWidth; j++)
			{
				RECT temp = { tileWidth * j, tileHeight * i, tileWidth * (j + 1), tileHeight * (i + 1) };
				if (temp.left < LOWORD(lParam) && temp.right > LOWORD(lParam) &&
					temp.top < HIWORD(lParam) && temp.bottom > HIWORD(lParam))
				{
					if (!isO) {
						if (thead == nullptr) {
							thead = new Tile;
							thead->Set(temp, tile, nullptr);
							ttail = thead;
						}
						else
						{
							Tile * t = new Tile;
							t->Set(temp, tile, ttail);
							ttail->next = t;
							ttail = ttail->next;
						}

						tmp = thead;
						while (tmp->next != nullptr)
						{
							bool flag = false;
							if (ttail->rc.left < tmp->rc.right && ttail->rc.right > tmp->rc.left &&
								ttail->rc.top < tmp->rc.bottom && ttail->rc.bottom > tmp->rc.top)
							{
								Tile * del = tmp;
								if (tmp == thead && tmp == ttail) break;
								else if (tmp == thead)
								{
									tmp = tmp->next;
									tmp->prev = nullptr;
									flag = true;
								}
								else
								{
									tmp = tmp->prev;
									tmp->next = nullptr;
								}
								del->Delete();
							}
							if (!flag) tmp = tmp->next;
							flag = false;
						}
					}
					else if (isO) {
						if (ohead == nullptr) {
							ohead = new Object;
							ohead->Set(temp, obj, nullptr);
							otail = ohead;
						}
						else
						{
							Object * t = new Object;
							t->Set(temp, obj, otail);
							otail->next = t;
							otail = otail->next;
						}

						otmp = ohead;
						while (otmp->next != nullptr)
						{
							bool flag = false;
							if (otail->rc.left < otmp->rc.right && otail->rc.right > otmp->rc.left &&
								otail->rc.top < otmp->rc.bottom && otail->rc.bottom > otmp->rc.top)
							{
								if (otmp->objectkind == obj2) {
									Object * del = otmp;
									if (otmp == ohead && otmp == otail) break;
									else if (otmp == ohead)
									{
										otmp = otmp->next;
										otmp->prev = nullptr;
										flag = true;
									}
									else
									{
										otmp = otmp->prev;
										otmp->next = nullptr;
									}
									del->Delete();
								}
								if (otmp->objectkind == obj1) {
									Object * del = otail;
									if (otail == ohead)
									{
										otmp = nullptr;
										flag = true;
									}
									else if (otmp->next == otail)
									{
										otmp->next = nullptr;
										flag = true;
									}
									del->Delete();
								}
							}
							if (!flag) otmp = otmp->next;
							flag = false;
						}
					}
				}
			}

		InvalidateRect(hwndChild, NULL, FALSE);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			break;
		case 2:
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		memBit = CreateCompatibleBitmap(hdc, mapWidth, mapHeight);
		SelectObject(memdc, memBit);
		rc = { 0, 0, mapWidth, mapHeight };
		FillRect(memdc, &rc, WHITE_BRUSH);
		//
		if (lstrcmp(BK, L"SKY") == 0)
			imgBK_sky.Draw(memdc, rc.left, rc.top, rc.right, rc.bottom);
		if (lstrcmp(BK, L"HILL") == 0)
			imgBK_hill.Draw(memdc, rc.left, rc.top, rc.right, rc.bottom);
		for (int i = 0; i < mapHeight / tileHeight; i++)
			for (int j = 0; j < mapWidth / tileWidth; j++)
			{
				RECT temp = { tileWidth * j, tileHeight * i, tileWidth * (j + 1), tileHeight * (i + 1) };
				FrameRect(memdc, &temp, (HBRUSH)GetStockObject(BLACK_BRUSH));
			}
		tmp = thead;
		while (tmp != nullptr)
		{
			switch (tmp->tilekind)
			{
			case 1:
				imgt.BitBlt(memdc, tmp->rc.left, tmp->rc.top, tmp->rc.right - tmp->rc.left, tmp->rc.bottom - tmp->rc.top,
					(imgt.GetWidth() / 2) * 0, (imgt.GetHeight() / 3) * 0, SRCCOPY);
				break;
			case 2:
				imgt.BitBlt(memdc, tmp->rc.left, tmp->rc.top, tmp->rc.right - tmp->rc.left, tmp->rc.bottom - tmp->rc.top,
					(imgt.GetWidth() / 2) * 0, (imgt.GetHeight() / 3) * 1, SRCCOPY);
				break;
			case 3:
				imgt.BitBlt(memdc, tmp->rc.left, tmp->rc.top, tmp->rc.right - tmp->rc.left, tmp->rc.bottom - tmp->rc.top,
					(imgt.GetWidth() / 2) * 0, (imgt.GetHeight() / 3) * 2, SRCCOPY);
				break;
			case 4:
				imgt.BitBlt(memdc, tmp->rc.left, tmp->rc.top, tmp->rc.right - tmp->rc.left, tmp->rc.bottom - tmp->rc.top,
					(imgt.GetWidth() / 2) * 1, (imgt.GetHeight() / 3) * 0, SRCCOPY);
				break;
			case 5:
				imgt.BitBlt(memdc, tmp->rc.left, tmp->rc.top, tmp->rc.right - tmp->rc.left, tmp->rc.bottom - tmp->rc.top,
					(imgt.GetWidth() / 2) * 1, (imgt.GetHeight() / 3) * 1, SRCCOPY);
				break;
			case 6:
				imgt.BitBlt(memdc, tmp->rc.left, tmp->rc.top, tmp->rc.right - tmp->rc.left, tmp->rc.bottom - tmp->rc.top,
					(imgt.GetWidth() / 2) * 1, (imgt.GetHeight() / 3) * 2, SRCCOPY);
				break;
			}
			tmp = tmp->next;
		}
		otmp = ohead;
		while (otmp != nullptr)
		{
			switch (otmp->objectkind)
			{
			case 1:
				imgO1.Draw(memdc, otmp->rc.left, otmp->rc.top, otmp->rc.right - otmp->rc.left, otmp->rc.bottom - otmp->rc.top);
				DrawText(memdc, L"1", lstrlen(L"!"), &otmp->rc, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
				break;
			case 2:
				imgO2.Draw(memdc, otmp->rc.left, otmp->rc.top, otmp->rc.right - otmp->rc.left, otmp->rc.bottom - otmp->rc.top);
				DrawText(memdc, L"2", lstrlen(L"!"), &otmp->rc, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
				break;
			}
			otmp = otmp->next;
		}
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
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void TILE::Set(RECT r, char tk, TILE * p)
{
	rc = r;
	tilekind = tk;
	next = nullptr;
	prev = p;
}
void TILE::Delete()
{
	if (thead == ttail)
	{
		thead = nullptr;
		ttail = nullptr;
	}
	else if (this == thead)
	{
		thead = thead->next;
		thead->prev = nullptr;
	}
	else if (this == ttail)
	{
		ttail = ttail->prev;
		ttail->next = nullptr;
	}
	else
	{
		prev->next = next;
		next->prev = prev;
	}
	delete this;
}
void OBJECT::Set(RECT r, char ok, OBJECT * p)
{
	rc = r;
	objectkind = ok;
	next = nullptr;
	prev = p;
}

void OBJECT::Delete()
{
	if (ohead == otail)
	{
		ohead = nullptr;
		otail = nullptr;
	}
	else if (this == ohead)
	{
		ohead = ohead->next;
		ohead->prev = nullptr;
	}
	else if (this == otail)
	{
		otail = otail->prev;
		otail->next = nullptr;
	}
	else
	{
		prev->next = next;
		next->prev = prev;
	}
	delete this;
}
/*
6-7을 차일드 윈도우를 사용하여 바꾸기
좌측의 차일드 윈도우: 맵 그리기
우측: 컨ㅌ롤 차일드 윈도우
-타일개수 설정하는 에디트 박스
-타일 이미지 설정하는 버튼 3개
-배경화면 사용할 이미지 리스트
-리스트 선택을 위한 버튼 1개
-졸료버튼 1개

버튼 윈도우에 이미지 넣기:
버튼 스타일에 BS_BITMAP 추가
비트맵 로드하기
SendMessage로 BM_SETIMAGE 메시지 보내게하기
*/