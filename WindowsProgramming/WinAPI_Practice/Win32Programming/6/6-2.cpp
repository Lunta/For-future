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
#define Size 30

enum class KEYDOWN
{
	left = 1, right = 2, up = 3, down = 4
};
enum RGB {
	G = 0, R = 1, Y = 2, RAND = 3
};
enum Shape {
	rectangle, ellipse
};

HINSTANCE g_hInst;
HWND g_hwnd;
bool jump, fimg, ex, sh, strmove, ch;
int flag, v, speed;
LPCTSTR lpszClass = WIN_CLASSNAME;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG Message;
	WNDCLASS WndClass; //구조체 정의
	RECT rc = { 0, 0, WIN_Width, WIN_Height };
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_BORDER | WS_THICKFRAME;
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
	HDC hdc, memdc, bmpdc;
	HBITMAP membit;
	PAINTSTRUCT ps;
	BITMAP bmp;
	static CImage cat;
	static HBITMAP rand, sky, sprite, boom, enemy, memBit, oldbit;
	static RECT rc, chara, enemyrc;
	static bool inputkey, crash;
	static int timer, sp, msp, l;

	srand((unsigned)time(NULL));

	switch (iMessage) {
	case WM_CREATE:
		GetWindowRect(hWnd, &rc);
		srand((unsigned)time(NULL));
		SetTimer(hWnd, 1, 60, NULL);
		SetTimer(hWnd, 2, 300, NULL);
		cat.Load(L"고양이 스프라이트.png");
		rand = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_EARTH));
		sky = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_SKY));
		sprite = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_SPRITE));
		boom = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BOOM));
		enemy = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_ENEMY));
		chara = { rc.right - 100, rc.bottom - 100, rc.right - 60, rc.bottom - 70 };
		GetObject(enemy, sizeof(BITMAP), &bmp);
		enemyrc = { 100 - (bmp.bmWidth / 8), rc.bottom - 100 - (bmp.bmHeight / 2),
			100 + (bmp.bmWidth / 8), rc.bottom - 100 + (bmp.bmHeight / 2) };
		ch = strmove = ex = sh = fimg = crash = jump = false;
		inputkey = true;
		flag = -1;
		speed = 25;
		timer = 0;
		sp = msp = v = 0;
		break;
	case WM_LBUTTONDOWN:
		LOWORD(lParam);
		HIWORD(lParam);

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:

		break;
	case WM_LBUTTONUP:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG6_2), hWnd, (DLGPROC)DlgProc);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if (timer++ == 10000000) timer = 0;
			OffsetRect(&enemyrc, 10, 0);
			if (enemyrc.left > rc.right)
			{
				GetObject(enemy, sizeof(BITMAP), &bmp);
				enemyrc.left = 0;
				enemyrc.right = bmp.bmWidth / 4;
			}
			
			if (flag == (int)KEYDOWN::left && inputkey) OffsetRect(&chara, -speed, 0);
			else if (flag == (int)KEYDOWN::right && inputkey) OffsetRect(&chara, speed, 0);
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
					OffsetRect(&chara, 0, -25);
					msp++;
				}
				else if (msp < 10)
				{
					OffsetRect(&chara, 0, 25);
					msp++;
				}
			}
			if (crash) {
				sp++;
				if (sp == 3) {
					sp = 0;
					crash = false;
				}
			}
			if (chara.right > enemyrc.left && chara.left < enemyrc.right &&
				chara.top < enemyrc.bottom && chara.bottom > enemyrc.top) {
				crash = true;
			}
			break;
		case 2:
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		bmpdc = CreateCompatibleDC(memdc);
		memBit = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		SelectObject(memdc, memBit);
		FillRect(memdc, &rc, WHITE_BRUSH);

		if (ex) l = 20;
		else if (sh) l = -10;
		if (!ex && !sh) l = 0;
		oldbit = (HBITMAP)SelectObject(bmpdc, sky);
		GetObject(sky, sizeof(BITMAP), &bmp);
		BitBlt(memdc, 0, 0, rc.right, rc.bottom, bmpdc, (timer * 2) % (bmp.bmWidth - rc.right), 0, SRCCOPY);
		oldbit = (HBITMAP)SelectObject(bmpdc, rand);
		GetObject(rand, sizeof(BITMAP), &bmp);
		BitBlt(memdc, 0, rc.bottom - bmp.bmHeight, rc.right, rc.bottom, bmpdc, timer % (bmp.bmWidth - rc.right), 0, SRCCOPY);

		if (!ch)
		{
			oldbit = (HBITMAP)SelectObject(bmpdc, sprite);
			TransparentBlt(memdc, chara.left - l, chara.top - l, 40 + l, 30 + l, bmpdc, 40 * (timer % 4), 30 * v, 40, 30, RGB(0, 0, 0));
		}
		else if (ch)
		{
			cat.TransparentBlt(memdc, chara.left - l, chara.top - l, 40 + l, 30 + l,
				(cat.GetWidth() / 4) * (timer % 4), 0, cat.GetWidth() / 4, cat.GetHeight(), RGB(0, 0, 0));
		}
		GetObject(enemy, sizeof(BITMAP), &bmp);
		oldbit = (HBITMAP)SelectObject(bmpdc, enemy);
		TransparentBlt(memdc, enemyrc.left, enemyrc.top, bmp.bmWidth / 4, bmp.bmHeight,
			bmpdc, (bmp.bmWidth / 4) * (timer % 4), 0, bmp.bmWidth / 4, bmp.bmHeight, RGB(255, 255, 255));

		if (fimg) cat.TransparentBlt(memdc, enemyrc.left - 100, enemyrc.top, 40, 40,
			(cat.GetWidth() / 4) * (timer % 4), 0, cat.GetWidth() / 4, cat.GetHeight(), RGB(0, 0, 0));
		GetObject(boom, sizeof(BITMAP), &bmp);
		if (crash) {
			oldbit = (HBITMAP)SelectObject(bmpdc, boom);
			if (sp < 2)
				TransparentBlt(memdc, chara.left - 30, chara.top - 30, bmp.bmWidth / 2, bmp.bmHeight / 2,
					bmpdc, (bmp.bmWidth / 2) * (sp % 2), 0, bmp.bmWidth / 2, bmp.bmHeight / 2,
					RGB(255, 255, 255));
			else if (sp >= 2 && sp < 4)
				TransparentBlt(memdc, chara.left - 30, chara.top - 30, bmp.bmWidth / 2, bmp.bmHeight / 2,
					bmpdc, (bmp.bmWidth / 2) * (sp % 2), bmp.bmHeight / 2, bmp.bmWidth / 2, bmp.bmHeight / 2,
					RGB(255, 255, 255));
		}
		if (strmove)
		{
			TextOut(memdc, enemyrc.left, 100, L"예제 6-2", lstrlen(L"예제 6-2"));
		}
		// hdc에 복사
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, memdc, 0, 0, SRCCOPY);

		SelectObject(memdc, NULL);
		SelectObject(bmpdc, oldbit);
		DeleteDC(memdc);
		DeleteDC(bmpdc);
		DeleteObject(memBit);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		if (wParam == 'J') jump = true;
		if (wParam == VK_LEFT)
		{
			flag = (int)KEYDOWN::left;
			v = 1;
		}
		if (wParam == VK_UP) flag = (int)KEYDOWN::up;
		if (wParam == VK_RIGHT)
		{
			flag = (int)KEYDOWN::right;
			v = 0;
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

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC dhdc, dmemdc;
	PAINTSTRUCT dps;
	static HBITMAP memBit;
	static RECT drc;

	switch (iMsg) {
	case WM_INITDIALOG:
		GetClientRect(hDlg, &drc);
		SetTimer(hDlg, Dlgtimer, 30, NULL);
		CheckRadioButton(hDlg, IDC_CHARA1, IDC_CHARA2, IDC_CHARA1);
		CheckRadioButton(hDlg, IDC_EXPAND, IDC_CANCLE, IDC_CANCLE);
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
		case IDC_SPEEDUP:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				speed += 10;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_SPEEDDOWN:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				speed -= 10;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_FRONT:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				flag = (int)KEYDOWN::left;
				v = 1;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_BACK:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				flag = (int)KEYDOWN::right;
				v = 0;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_JUMP:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				jump = true;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_STRMOVE:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				if (strmove) strmove = false;
				else strmove = true;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_FALLOWIMG:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				if (fimg) fimg = false;
				else fimg = true;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_CHARA1:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				ch = false;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_CHARA2:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				ch = true;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_EXPAND:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				ex = true;
				sh = false;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_SHRINK:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				sh = true;
				ex = false;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
			break;
		case IDC_CANCLE:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				ex = false;
				sh = false;
			}
			InvalidateRect(g_hwnd, NULL, FALSE);
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
/*
•버튼
•1: jump (캐릭터 점프)
•2: Front (캐릭터 앞으로 이동)
•3: Back (캐릭터 뒤로 이동)
•4: Speed+ (캐릭터 이동 속도를 올린다)
•5: Speed- (캐릭터 이동 속도를 내린다)
•체크박스
•6: 화면의 하늘 부분에 글이 좌우로 이동한다.
•7: 화면의 몬스터 뒤에 다른 그림이 따라온다.
•라디오 버튼
•8: 캐릭터 1 (이미지 사용)
•9: 캐릭터 2 (이미지 사용)
•라디오 버튼
•10: 확대 (캐릭터 크기를 2배로 확대)
•11: 축소 (캐릭터 크기를 0.5배로 축소)
•12: 제자리 (캐릭터 크기를 원래 크기로)
•버튼
•13: exit (프로그램 종료
*/