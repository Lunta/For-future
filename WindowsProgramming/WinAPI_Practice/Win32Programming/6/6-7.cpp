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
#define STRMAX 100

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
HWND g_hwnd;
TCHAR BK[10];
CImage imgBK_sky, imgBK_hill;
Tile * thead = nullptr, *ttail = nullptr;
Object * ohead = nullptr, *otail = nullptr;
char tile;
char obj;
unsigned short mapWidth, mapHeight, tileWidth, tileHeight;
bool isO;

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
	static CImage imgt, imgO1, imgO2;
	Tile * tmp;
	Object * otmp;

	switch (iMessage) {
	case WM_CREATE:
		//SetWindowText(hWnd, L"계산기");
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
		if (!IsWindow(hDlg))
		{
			hDlg = CreateDialog(g_hInst,
				MAKEINTRESOURCE(IDD_DIALOG6_7), hWnd, (DLGPROC)DlgProc);
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
	static int cselection;
	HBITMAP hBit[6], hObjBit[2];
	HWND hButton;
	int buffer;

	switch (iMsg) {
	case WM_INITDIALOG:
		GetClientRect(hDlg, &drc);
		hCombo = GetDlgItem(hDlg, IDC_BKIMAGE);
		hList = GetDlgItem(hDlg, IDC_LIST1);
		SetDlgItemInt(hDlg, IDC_MAPWIDTH, mapWidth, true);
		SetDlgItemInt(hDlg, IDC_MAPHEIGHT, mapHeight, true);
		SetDlgItemInt(hDlg, IDC_TILEWIDTH, tileWidth, true);
		SetDlgItemInt(hDlg, IDC_TILEHEIGHT, tileHeight, true);

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

		hButton = GetDlgItem(hDlg, IDC_OBJECT1);
		hObjBit[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_OBJECT1));
		SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hObjBit[0]);
		hButton = GetDlgItem(hDlg, IDC_OBJECT2);
		hObjBit[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_OBJECT2));
		SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hObjBit[1]);

		imgBK_sky.Load(TEXT("배경.bmp"));
		imgBK_hill.Load(TEXT("5-8배경.png"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)(L"SKY"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)(L"HILL"));
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
			if (HIWORD(wParam) == BN_CLICKED) {
				tile = 1;
				isO = false;
			}
			break;
		case IDC_TILE2:
			if (HIWORD(wParam) == BN_CLICKED) {
				tile = 2;
				isO = false;
			}
			break;
		case IDC_TILE3:
			if (HIWORD(wParam) == BN_CLICKED) {
				tile = 3;
				isO = false;
			}
			break;
		case IDC_TILE4:
			if (HIWORD(wParam) == BN_CLICKED) {
				tile = 4;
				isO = false;
			}
			break;
		case IDC_TILE5:
			if (HIWORD(wParam) == BN_CLICKED) {
				tile = 5;
				isO = false;
			}
			break;
		case IDC_TILE6:
			if (HIWORD(wParam) == BN_CLICKED) {
				tile = 6;
				isO = false;
			}
			break;
		case IDC_OBJECT1:
			if (HIWORD(wParam) == BN_CLICKED) {
				obj = 1;
				isO = true;
			}
			break;
		case IDC_OBJECT2:
			if (HIWORD(wParam) == BN_CLICKED) {
				obj = 2;
				isO = true;
			}
			break;
		case IDC_BKIMAGE:
			if (HIWORD(wParam) == CBN_SELCHANGE) // 하나가 선택됨(상태 변경)
				cselection = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			//SendMessage(hCombo, CB_GETLBTEXTLEN, selection, 0);문자열 길이 반환
			SendMessage(hCombo, CB_GETLBTEXT, cselection, (LPARAM)BK);
			InvalidateRect(g_hwnd, nullptr, true);
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
맵툴2
리스트박스 혹은 콤보박스 : 배경화면으로 사용할 이미지리스트
이미지선택버튼

이미지:
버튼 혹은 이미질 사용하여 객체를 올려놓도록 한다.
최소한 두 종류의 이미지를 사용한다.
이미지 0 : 그리드의 이미지 위에 0이라고 쓰고 그 그리드는 다시 이미지를 바꿀 수 없다.(통과할 수 없는 장애물)
이미지 1: 그리드의 이미지 위에1이라고 쓰고 그 그리드 위에 다른 이미지를 올려놓을 수 있다.(통과할 수 있는 객체)
맵툴의 그리드의 한 칸에 이미지를 올려놓는다.
*/

