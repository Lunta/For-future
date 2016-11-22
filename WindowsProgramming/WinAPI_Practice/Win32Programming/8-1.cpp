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
	WNDCLASS WndClass; //����ü ����
	RECT rc = { 0, 0, WIN_Width, WIN_Height };
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX |
		WS_BORDER | WS_MAXIMIZEBOX; //WS_HSCROLL | WS_VSCROLL | WS_THICKFRAME
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0; // O/S ��� ���� �޸�(Class)
	WndClass.cbWndExtra = 0; // O/S ��� ���� �޸�(Window)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ�� ����
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //���������� WndClass.hIconSM : ����������
	WndClass.lpfnWndProc = FrameWndProc; // ���ν��� �Լ���
	WndClass.hInstance = hInstance; //���� ���α׷� ID
	WndClass.lpszClassName = WIN_FRAMECLASSNAME; // Ŭ���� �̸�
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU7_1); // �޴� �̸�
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = ChildWndProc; // ���ν��� �Լ���
	WndClass.lpszClassName = WIN_CHILDCLASSNAME; // Ŭ���� �̸�

	RegisterClass(&WndClass);

	AdjustWindowRect(&rc, dwStyle, FALSE);
	hwnd = CreateWindow( // �����찡 �����Ǹ� �ڵ�(hwnd)�� ��ȯ��
		WIN_FRAMECLASSNAME,	// ������ Ŭ���� �̸�
		WIN_TITLENAME,	 // ������ Ÿ��Ʋ �̸�
		dwStyle,	 //������ ��Ÿ��
		WIN_XPOS,	// ������ ��ġ, x��ǥ
		WIN_YPOS,	// ������ ��ġ, y��ǥ
		rc.right - rc.left, // ������ ��
		rc.bottom - rc.top, // ������ ����
		NULL,		// �θ� ������ �ڵ�
		(HMENU)NULL, // �޴� �ڵ�
		hInstance,	 // ���� ���α׷� ID
		NULL);		// ������ ������ ����
	g_hwnd = hwnd;
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message); // Shift ��a�� -> �빮�� ��A��
		DispatchMessage(&Message); // WinMain -> WinProc
	}
	return Message.wParam;
}

LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	CLIENTCREATESTRUCT clientcreate; // ���ϵ� ������ �����ϱ� ���� ����ü
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
		clientcreate.idFirstChild = 100; // ù ��° ���ϵ� ID
		hwndClient = CreateWindow(TEXT("MDICLIENT"),
			NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, // ������ ��Ÿ��
			0, 0, 0, 0, // ��ǥ
			hWnd, NULL,
			g_hInst, (LPSTR)&clientcreate);
		ShowWindow(hwndClient, SW_SHOW); // Ŭ���̾�Ʈ ������ ���
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
			mdicreate[midx].hOwner = g_hInst; // ���α׷� �ν��Ͻ� �L��
			mdicreate[midx].x = 0; // �ڽ� ������ X��ǥ
			mdicreate[midx].y = 0; // �ڽ� ������ Y��ǥ
			mdicreate[midx].cx = 800; // �ڽ� ������ ��
			mdicreate[midx].cy = 600; // �ڽ� ������ ����
			mdicreate[midx].style = 0;
			mdicreate[midx].lParam = 0; // MDI Ŭ���̾�Ʈ �����츦 ������

			hwndChild[midx] = (HWND)SendMessage(hwndClient, WM_MDICREATE,
				0, (LPARAM)(LPMDICREATESTRUCT)&mdicreate[midx]);
			midx++;
			break;
		case ID_LOAD:
			memset(&OFN, 0, sizeof(OPENFILENAME)); // �ʱ�ȭ
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = L"Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = L"."; // �ʱ� ���丮
			if (GetOpenFileName(&OFN) != 0) {
				mdicreate[midx].szClass = WIN_CHILDCLASSNAME;
				mdicreate[midx].szTitle = WIN_TITLENAME;
				mdicreate[midx].hOwner = g_hInst; // ���α׷� �ν��Ͻ� �L��
				mdicreate[midx].x = 0; // �ڽ� ������ X��ǥ
				mdicreate[midx].y = 0; // �ڽ� ������ Y��ǥ
				mdicreate[midx].cx = 800; // �ڽ� ������ ��
				mdicreate[midx].cy = 600; // �ڽ� ������ ����
				mdicreate[midx].style = 0;
				mdicreate[midx].lParam = 0; // MDI Ŭ���̾�Ʈ �����츦 ������

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
		//���� ���
		CreateCaret(hwndChild[idx], NULL, 5, 15);
		//ShowCaret(hwndChild[idx]); // �� ȭ�鿡 ĳ�� ǥ��
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
