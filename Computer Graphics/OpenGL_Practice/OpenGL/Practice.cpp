#include "stdafx.h"

#include "MainScene.h"
#include "Practice.h"

CPractice::CPractice()
{
}
CPractice::~CPractice()
{
}

bool CPractice::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case WM_KEYDOWN:
		return true;
	case WM_KEYUP:
		return true;
	}
	return false;
}

bool CPractice::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case WM_LBUTTONDOWN:
		return true;
	case WM_MOUSEMOVE:
		return true;
	}
	return false;
}

bool CPractice::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case WM_SIZE:
		break;
	case WM_DESTROY:
		break;
	}
	return false;
}

void CPractice::BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag)
{
	m_pScene = CurrentScene;
	m_hWnd = hWnd;
	
	m_Tag = tag;

	RECT temp{ 0, 0, 0, 0 };
	::GetClientRect(m_hWnd, &temp);
	m_rcScene = { static_cast<float>(-temp.right / 2), static_cast<float>(-temp.bottom / 2),
		static_cast<float>(temp.right / 2), static_cast<float>(temp.bottom / 2) };
}

bool CPractice::ProcessInput()
{
	bool bProcessedByScene = false;

	if (!bProcessedByScene)
	{
		static UCHAR pKeyBuffer[256];
		DWORD dwDirection = 0;

		bool bPushShift = false;
		bool bControll = false;

		if (GetKeyboardState(pKeyBuffer))
		{
			if (pKeyBuffer[VK_LSHIFT] & 0xF0)	  bPushShift = true;
			if (pKeyBuffer[VK_LEFT] & 0xF0)  	  dwDirection |= DIR_LEFT;
			if (pKeyBuffer[VK_RIGHT] & 0xF0)	  dwDirection |= DIR_RIGHT;
			if (pKeyBuffer[VK_UP] & 0xF0)		  dwDirection |= DIR_UP;
			if (pKeyBuffer[VK_DOWN] & 0xF0)		  dwDirection |= DIR_DOWN;

			if (pKeyBuffer['X'] & 0xF0) { bControll = true; }
			else if (pKeyBuffer['Y'] & 0xF0) { bControll = true; }
			else if (pKeyBuffer['Z'] & 0xF0) { bControll = true; }
			else if (pKeyBuffer['A'] & 0xF0) { bControll = true; }
			else if (pKeyBuffer['I'] & 0xF0) { bControll = true; }
			else if (pKeyBuffer['Q'] & 0xF0) { bControll = true; }
			if ((pKeyBuffer[VK_LEFT] & 0xF0) || (pKeyBuffer[VK_RIGHT] & 0xF0))
			{
				if (dwDirection & DIR_LEFT) { bControll = true; }
				if (dwDirection & DIR_RIGHT) { bControll = true; }
			}
			if ((pKeyBuffer[VK_UP] & 0xF0) || (pKeyBuffer[VK_DOWN] & 0xF0))
			{
				if (dwDirection & DIR_UP) { bControll = true; }
				if (dwDirection & DIR_DOWN) { bControll = true; }
			}
		}

		if (!bControll)
		{

		}

		return bControll;
	}
	return false;
}
