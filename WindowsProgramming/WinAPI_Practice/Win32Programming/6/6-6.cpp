#include <windows.h> 
#include <tchar.h>
#include <ctime>
#include <math.h>
#include <atlimage.h> 
#include "resource.h"

#define WIN_CLASSNAME TEXT("Timer")
#define WIN_TITLENAME TEXT("Timer")
#define WIN_XPOS 0 
#define WIN_YPOS 0 
#define WIN_Width 800 
#define WIN_Height 600

#define Dlgtimer 1
#define Wintimer 2

enum KindOfTile {
	// 1~6번 타일
	tile1 = 1, tile2, tile3, tile4, tile5, tile6
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

HINSTANCE g_hInst;
HWND g_hwnd;
CImage img;
Tile * head = nullptr, *tail = nullptr;
char tile;
unsigned short mapWidth, mapHeight, tileWidth, tileHeight;

LPCTSTR lpszClass = WIN_CLASSNAME;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

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
	WndClass.hInstance = hInstance; //응용 프로그램 ID
	WndClass.lpfnWndProc = (WNDPROC)WndProc; // 프로시저 함수명
	WndClass.lpszClassName = lpszClass; // 클래스 이름
	WndClass.lpszMenuName = NULL; // 메뉴 이름
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

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
	HBITMAP memBit;
	PAINTSTRUCT ps;
	static RECT rc;
	static HWND hDlg = nullptr;
	Tile * tmp;

	switch (iMessage) {
	case WM_CREATE:
		//SetWindowText(hWnd, L"계산기");
		GetWindowRect(hWnd, &rc);
		srand((unsigned)time(0));
		tile = 1;
		mapWidth = rc.right;
		mapHeight = rc.bottom;
		tileWidth = tileHeight = 30;
		img.Load(L"tile.png");
		break;
	case WM_LBUTTONDOWN:
		LOWORD(lParam);
		HIWORD(lParam);

		InvalidateRect(hWnd, nullptr, false);
		break;
	case WM_MOUSEMOVE:

		break;
	case WM_LBUTTONUP:
		for (int i = 0; i < mapHeight / tileHeight; i++)
			for (int j = 0; j < mapWidth / tileWidth; j++)
			{
				RECT temp = { tileWidth * j, tileHeight * i, tileWidth * (j + 1), tileHeight * (i + 1) };
				if (temp.left < LOWORD(lParam) && temp.right > LOWORD(lParam) &&
					temp.top < HIWORD(lParam) && temp.bottom > HIWORD(lParam))
				{
					if (head == nullptr) {
						head = new Tile;
						head->Set(temp, tile, nullptr);
						tail = head;
					}
					else
					{
						Tile * t = new Tile;
						t->Set(temp, tile, tail);
						tail->next = t;
						tail = tail->next;
					}
					tmp = head;
					while (tmp->next != nullptr)
					{
						bool flag = false;
						if (tail->rc.left < tmp->rc.right && tail->rc.right > tmp->rc.left &&
							tail->rc.top < tmp->rc.bottom && tail->rc.bottom > tmp->rc.top)
						{
							Tile * del = tmp;
							if (tmp == head && tmp == tail) break;
							else if (tmp == head)
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
						if(!flag) tmp = tmp->next;
						flag = false;
					}
				}
			}
	
		InvalidateRect(hWnd, nullptr, false);
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
		FillRect(memdc, &rc, WHITE_BRUSH);
		//
		for(int i = 0; i < mapHeight / tileHeight; i++)
			for (int j = 0; j < mapWidth / tileWidth; j++)
			{
				RECT temp = {tileWidth * j, tileHeight * i, tileWidth * (j + 1), tileHeight * (i + 1)};
				FrameRect(memdc, &temp, (HBRUSH)GetStockObject(BLACK_BRUSH));
			}
		tmp = head;
		while (tmp != nullptr)
		{
			switch (tmp->tilekind)
			{
			case 1:
				img.BitBlt(memdc, tmp->rc.left, tmp->rc.top, tmp->rc.right - tmp->rc.left, tmp->rc.bottom - tmp->rc.top,
					(img.GetWidth() / 2) * 0, (img.GetHeight() / 3) * 0, SRCCOPY);
				break;
			case 2:
				img.BitBlt(memdc, tmp->rc.left, tmp->rc.top, tmp->rc.right - tmp->rc.left, tmp->rc.bottom - tmp->rc.top,
					(img.GetWidth() / 2) * 0, (img.GetHeight() / 3) * 1, SRCCOPY);
				break;
			case 3:
				img.BitBlt(memdc, tmp->rc.left, tmp->rc.top, tmp->rc.right - tmp->rc.left, tmp->rc.bottom - tmp->rc.top,
					(img.GetWidth() / 2) * 0, (img.GetHeight() / 3) * 2, SRCCOPY);
				break;
			case 4:
				img.BitBlt(memdc, tmp->rc.left, tmp->rc.top, tmp->rc.right - tmp->rc.left, tmp->rc.bottom - tmp->rc.top,
					(img.GetWidth() / 2) * 1, (img.GetHeight() / 3) * 0, SRCCOPY);
				break;
			case 5:
				img.BitBlt(memdc, tmp->rc.left, tmp->rc.top, tmp->rc.right - tmp->rc.left, tmp->rc.bottom - tmp->rc.top,
					(img.GetWidth() / 2) * 1, (img.GetHeight() / 3) * 1, SRCCOPY);
				break;
			case 6:
				img.BitBlt(memdc, tmp->rc.left, tmp->rc.top, tmp->rc.right - tmp->rc.left, tmp->rc.bottom - tmp->rc.top,
					(img.GetWidth() / 2) * 1, (img.GetHeight() / 3) * 2, SRCCOPY);
				break;
			}
			tmp = tmp->next;
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
		if (!IsWindow(hDlg))
		{
			hDlg = CreateDialog(g_hInst,
				MAKEINTRESOURCE(IDD_DIALOG6_6), hWnd, (DLGPROC)DlgProc);
			ShowWindow(hDlg, SW_SHOW);
		}
		else
		{
			DestroyWindow(hDlg);
			hDlg = nullptr;
		}
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

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC dhdc, dmemdc;
	PAINTSTRUCT dps;
	static HWND hCombo, hList;
	static HBITMAP memBit;
	static RECT drc;
	HBITMAP hBit[6];
	HWND hButton;
	int buffer;

	switch (iMsg) {
	case WM_INITDIALOG:
		GetClientRect(hDlg, &drc);
		hCombo = GetDlgItem(hDlg, IDC_BIRTH);
		hList = GetDlgItem(hDlg, IDC_LIST1);
		SetDlgItemInt(hDlg, IDC_MAPWIDTH, mapWidth, true);
		SetDlgItemInt(hDlg, IDC_MAPHEIGHT, mapHeight, true);
		SetDlgItemInt(hDlg, IDC_TILEWIDTH, tileWidth, true);
		SetDlgItemInt(hDlg, IDC_TILEHEIGHT,tileHeight, true);
		hButton = GetDlgItem(hDlg, IDC_TILE1);
		hBit[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_TILE1));
		SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit[0]);
		hButton = GetDlgItem(hDlg, IDC_TILE2);
		hBit[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_TILE2));
		SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit[1]);
		hButton = GetDlgItem(hDlg, IDC_TILE3);
		hBit[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_TILE3));
		SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit[2]);
		hButton = GetDlgItem(hDlg, IDC_TILE4);
		hBit[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_TILE4));
		SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit[3]);
		hButton = GetDlgItem(hDlg, IDC_TILE5);
		hBit[4] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_TILE5));
		SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit[4]);
		hButton = GetDlgItem(hDlg, IDC_TILE6);
		hBit[5] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_TILE1));
		SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit[5]);
		break;
	case WM_PAINT:
		dhdc = BeginPaint(hDlg, &dps);
		dmemdc = CreateCompatibleDC(dhdc);
		memBit = CreateCompatibleBitmap(dhdc, drc.right, drc.bottom);
		SelectObject(dmemdc, memBit);
		FillRect(dmemdc, &drc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		//

		// hdc에 복사
		BitBlt(dhdc, 0, 0, drc.right, drc.bottom, dmemdc, 0, 0, SRCCOPY);

		SelectObject(dmemdc, NULL);
		DeleteDC(dmemdc);
		DeleteObject(memBit);
		EndPaint(hDlg, &dps);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case Dlgtimer:

			break;
		}
		//InvalidateRect(g_hwnd, NULL, FALSE);
		InvalidateRect(hDlg, NULL, FALSE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_MAPWIDTH: 
			if (HIWORD(wParam) == EN_KILLFOCUS) {
				buffer = GetDlgItemInt(hDlg, IDC_MAPWIDTH, 0, true);
				if (buffer != 0) mapWidth = buffer;
				else SetDlgItemInt(hDlg, IDC_MAPWIDTH, mapWidth, true);
				InvalidateRect(g_hwnd, nullptr, true);
			}
			break;
		case IDC_MAPHEIGHT:
			if (HIWORD(wParam) == EN_KILLFOCUS) {
				buffer = GetDlgItemInt(hDlg, IDC_MAPHEIGHT, 0, true);
				if (buffer != 0) mapHeight = buffer;
				else SetDlgItemInt(hDlg, IDC_MAPHEIGHT, mapHeight, true);
				InvalidateRect(g_hwnd, nullptr, true);
			}
			break;
		case IDC_TILEWIDTH:
			if (HIWORD(wParam) == EN_KILLFOCUS) {
				buffer = GetDlgItemInt(hDlg, IDC_TILEWIDTH, 0, true);
				if (buffer != 0) tileWidth = buffer;
				else SetDlgItemInt(hDlg, IDC_TILEWIDTH, tileWidth, true);
				InvalidateRect(g_hwnd, nullptr, true);
			}
			break;
		case IDC_TILEHEIGHT:
			if (HIWORD(wParam) == EN_KILLFOCUS) {
				buffer = GetDlgItemInt(hDlg, IDC_TILEHEIGHT, 0, true);
				if (buffer != 0) tileHeight = buffer;
				else SetDlgItemInt(hDlg, IDC_TILEHEIGHT, tileHeight, true);
				InvalidateRect(g_hwnd, nullptr, true);
			}
			break;
		case IDC_TILE1:
			if (HIWORD(wParam) == BN_CLICKED)
				tile = 1;
			break;
		case IDC_TILE2:
			if (HIWORD(wParam) == BN_CLICKED)
				tile = 2;
			break;
		case IDC_TILE3:
			if (HIWORD(wParam) == BN_CLICKED)
				tile = 3;
			break;
		case IDC_TILE4:
			if (HIWORD(wParam) == BN_CLICKED)
				tile = 4;
			break;
		case IDC_TILE5:
			if (HIWORD(wParam) == BN_CLICKED)
				tile = 5;
			break;
		case IDC_TILE6:
			if (HIWORD(wParam) == BN_CLICKED)
				tile = 6;
			break;
		case IDC_EXIT:
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
	return false;
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
	if (head == tail)
	{
		head = nullptr;
		tail = nullptr;
	}
	else if (this == head) head = head->next;
	else if (this == tail) tail = tail->prev;
	else
	{
		prev->next = next;
		next->prev = prev;
	}
	delete this;
}
/*
맵툴만들기
모델리스대화상자
맵의크기설정하는 에디트박스(가로세로크기)
가로와 세로의 타일 개수를 설정하는 에디트박스(가로와 세로의 타일 개수)
타일 이미지 선택버튼: 6개의 선택 가능한 타일을 만들기

타일 버튼을 선택한 후 화면의 그리드 칸을 클릭/드래그하면 선택된 이미지가 그려진다.
버튼에 이미지입히기
버튼의 속성에서 모양-이미지를 트루로 바꿈

HBITMAP hBit;
HWND hButton;

hBit = LoadBitmap (hInst, MAKEINTRESOURCE(IDB_BITMAP1));
hButton = GetDlgItem(hwnd, IDC_BUTTON1);
SendMessage (hButton, BM_SETIMAGE, 0, (LPARAM)hBit);
*/

