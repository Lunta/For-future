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
				MAKEINTRESOURCE(IDD_DIALOG6_4), hWnd, (DLGPROC)DlgProc);
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
	static HBITMAP memBit;
	static RECT drc;
	static TCHAR c, str[STRMAX];
	static double a, b, result;
	static bool dicimal;
	static int l, binary[STRMAX];
	switch (iMsg) {
	case WM_INITDIALOG:
		GetClientRect(hDlg, &drc);
		lstrcpy(str , L"");
		dicimal = true;
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
		case IDC_EDIT:
			GetDlgItemText(hDlg, IDC_EDIT, str, STRMAX);
			break;
		case IDC_BUTTON1:
			l = lstrlen(str);
			str[l++] = L'1';
			str[l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_BUTTON2:
			l = lstrlen(str);
			str[l++] = L'2';
			str[l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_BUTTON3:
			l = lstrlen(str);
			str[l++] = L'3';
			str[l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_BUTTON4:
			l = lstrlen(str);
			str[l++] = L'4';
			str[l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_BUTTON5:
			l = lstrlen(str);
			str[l++] = L'5';
			str[l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_BUTTON6:
			l = lstrlen(str);
			str[l++] = L'6';
			str[l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_BUTTON7:
			l = lstrlen(str);
			str[l++] = L'7';
			str[l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_BUTTON8:
			l = lstrlen(str);
			str[l++] = L'8';
			str[l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_BUTTON9:
			l = lstrlen(str);
			str[l++] = L'9';
			str[l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_BUTTON0:
			l = lstrlen(str);
			str[l++] = L'0';
			str[l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_DOT:
			l = lstrlen(str);
			str[l++] = L'.';
			str[l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_EQUAL:
			for (int i = 0; i < STRMAX; i++)
			{
				if (str[i] == L'+' || str[i] == L'-' || str[i] == L'×' || str[i] == L'÷')
				{
					a = _wtoi(str);
					b = _wtoi(str + i + 1);
					if (str[i] == L'+')
					{
						result = a + b;
					}
					if (str[i] == L'-')
					{
						result = a - b;
					}
					if (str[i] == L'×')
					{
						result = a * b;
					}
					if (str[i] == L'÷')
					{
						result = a / b;
					}
					swprintf_s(str, TEXT("%lf"), result);
					SetDlgItemText(hDlg, IDC_EDIT, str);
					break;
				}
			}
			break;
		case IDC_ADD:
			l = lstrlen(str);
			str[l++] = L'+';
			str[l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_SUBTRACT:
			l = lstrlen(str);
			str[l++] = L'-';
			str[l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_MULTIPLY:
			l = lstrlen(str);
			str[l++] = L'×';
			str[l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_DIVIDE:
			l = lstrlen(str);
			str[l++] = L'÷';
			str[l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_CANCLE:
			l = lstrlen(str);
			str[--l] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_RESET:
			l = lstrlen(str);
			for(int i = 0; i < l + 1; i++)
				str[i] = L'\0';
			SetDlgItemText(hDlg, IDC_EDIT, str);
			break;
		case IDC_BINARY:
			if (dicimal) {
				for (int i = 0; i < STRMAX; i++)
				{
					if (str[i] == L'+' || str[i] == L'-' || str[i] == L'×' || str[i] == L'÷')
					{
						a = _wtoi(str);
						b = _wtoi(str + i + 1);
						c = str[i];
						for (int j = 0; j < STRMAX; j++)
						{
							if (b != 0)
							{
								if ((int)b==1) {
									binary[j] = b;
									b = 0;
									j++;
									binary[j] = c;
								}
								else if (b != 1) {
									binary[j] = (int)b % 2;
									b = b / 2;
								}
							}
							else if (b == 0)
							{
								if ((int)a==1) {
									binary[j] = a;
									a = 0;
									j++;
									//binary[j] = L'\0';
									l = j;
									break;
								}
								else if (a != 1) {
									binary[j] = (int)a % 2;
									a = a / 2;
								}
							}
						}
						for (int i = 0; i < l; i++)
						{
							switch (binary[i])
							{
							case 0:str[i] = L'0'; break;
							case 1:str[i] = L'1'; break;
							case 'c':str[i] = c; break;
							}
						}
					}
				}
				str[l] = L'\0';
				dicimal = false;
				_tcsrev(str);
				SetDlgItemText(hDlg, IDC_EDIT, str);
			}
			break;
		case IDC_DECIMAL:
			if (!dicimal) {
				_tcsrev(str);
				l = 0;
				for (int i = 0; i < STRMAX; i++)
				{
					switch (str[i])
					{
					case '0': break;
					case '1':
						for (int j = 0; j < i+ 1; j++)
						{
							if (j == 0) binary[0] = 1;
							else binary[0] *= 2;
						}
						l += binary[0];
						binary[0] = 1;
						break;
					}
					if (str[i] == L'\0')
					{
						dicimal = true;
						swprintf_s(str, TEXT("%d"), l);
						SetDlgItemText(hDlg, IDC_EDIT, str);
						break;
					}
				}
			}
			break;
		case IDC_REVERSE:
			_tcsrev(str);
			SetDlgItemText(hDlg, IDC_EDIT, str);
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