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

HINSTANCE g_hInst;
HWND g_hwnd;

typedef struct List
{
	TCHAR name[20];
	TCHAR pnum[20];
	TCHAR birth[20];
	bool s;
};

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
	HDC hdc, memdc;
	HBITMAP memBit;
	PAINTSTRUCT ps;
	static RECT rc;
	static HWND hDlg = nullptr;

	switch (iMessage) {
	case WM_CREATE:
		//SetWindowText(hWnd, L"계산기");
		GetWindowRect(hWnd, &rc);
		srand((unsigned)time(0));
		SetTimer(hWnd, 1, 60, nullptr);
		SetTimer(hWnd, 2, 300, nullptr);
		break;
	case WM_LBUTTONDOWN:
		LOWORD(lParam);
		HIWORD(lParam);

		InvalidateRect(hWnd, nullptr, false);
		break;
	case WM_MOUSEMOVE:

		break;
	case WM_LBUTTONUP:
		if (!IsWindow(hDlg))
		{
			hDlg = CreateDialog(g_hInst,
				MAKEINTRESOURCE(IDD_DIALOG6_5), hWnd, (DLGPROC)DlgProc);
			ShowWindow(hDlg, SW_SHOW);
		}
		else
		{
			DestroyWindow(hDlg);
			hDlg = nullptr;
		}
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
		memBit = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		SelectObject(memdc, memBit);
		FillRect(memdc, &rc, WHITE_BRUSH);
		//


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

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC dhdc, dmemdc;
	PAINTSTRUCT dps;
	static int lselection, cselection, idx;
	static HWND hCombo, hList;
	static HBITMAP memBit;
	static RECT drc;
	static List list[10];
	static TCHAR name[20], num[20], birth[20];
	static bool s, n;

	switch (iMsg) {
	case WM_INITDIALOG:
		GetClientRect(hDlg, &drc);
		hCombo = GetDlgItem(hDlg, IDC_BIRTH);
		hList = GetDlgItem(hDlg, IDC_LIST1);
		CheckRadioButton(hDlg, IDC_MALE, IDC_FEMALE, IDC_MALE);
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)(L"1994"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)(L"1995"));
		idx = 0;
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
		case IDC_BIRTH:
			if (HIWORD(wParam) == CBN_SELCHANGE) // 하나가 선택됨(상태 변경)
				cselection = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
				//SendMessage(hCombo, CB_GETLBTEXTLEN, selection, 0);문자열 길이 반환
				SendMessage(hCombo, CB_GETLBTEXT, cselection, (LPARAM)birth);
			break;
		case IDC_Out:
			SendMessage(hList, LB_DELETESTRING, lselection, 0);
			break;
		case IDC_EDIT_NAME:
			GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 20);
			break;
		case IDC_EDIT_PHONE:
			GetDlgItemText(hDlg, IDC_EDIT_PHONE, num, 20);
			break;
		case IDC_MALE:
			s = true;
			break;
		case IDC_FEMALE:
			s = false;
			break;
		case IDC_LIST1:
			if (HIWORD(wParam) == LBN_SELCHANGE)
				lselection = SendMessage(hList, LB_GETCURSEL, 0, 0);
			break;
		case IDC_SORT:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				for(int i = 0; i < idx + 1; i++)
					SendMessage(hList, LB_DELETESTRING, 0, 0);
				for (int i = 0; i < idx + 1; ++i)
				{
					for (int j = i ; j < idx ; ++j)
					{
						if (lstrcmp(list[i].name, list[j].name)>0)
						{
							List a;
							lstrcpy(a.birth, list[i].birth);
							lstrcpy(a.name, list[i].name);
							lstrcpy(a.pnum, list[i].pnum);
							a.s = list[i].s;

							lstrcpy(list[i].birth, list[j].birth);
							lstrcpy(list[i].name, list[j].name);
							lstrcpy(list[i].pnum, list[j].pnum);
							list[i].s = list[j].s;

							lstrcpy(list[j].birth, a.birth);
							lstrcpy(list[j].name, a.name);
							lstrcpy(list[j].pnum, a.pnum);
							list[j].s = a.s;
						}
					}
				}
				for (int i = 0; i < idx ; i++)
				{
					TCHAR str[100], s[20];
					if (s) lstrcpy(s, L"남자");
					else if (!s) lstrcpy(s, L"여자");
					wsprintf(str, TEXT("이름:%s 전화번호:%s, 생년월일:%s, 성별: %s"),
						list[i].name, list[i].pnum, list[i].birth, s);
					SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);
				}
			}
			break;
		case IDC_NEW:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				n = true;
			}
			break;
		case IDC_JOIN:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				if (n)
				{
					TCHAR str[100], s[10];
					lstrcpy(list[idx].birth, birth);
					lstrcpy(list[idx].name, name);
					lstrcpy(list[idx].pnum, num);
					list[idx].s = s;
					if (s) lstrcpy(s, L"남자");
					else if (!s) lstrcpy(s, L"여자");
					wsprintf(str, TEXT("이름:%s 전화번호:%s, 생년월일:%s, 성별: %s"),
						list[idx].name, list[idx].pnum, list[idx].birth, s);
					SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str);
					idx++;
					n = false;
				}
			}
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