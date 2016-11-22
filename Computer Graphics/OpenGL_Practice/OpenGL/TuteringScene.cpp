#include "stdafx.h"

#include "Framework.h"
#include "TuteringScene.h"



CTuteringScene::CTuteringScene()
{
	m_x = 0.0f;
	m_y = 0.0f;
}

CTuteringScene::~CTuteringScene()
{
}

void CTuteringScene::Update(float fTimeElapsed)
{
}

void CTuteringScene::Rendering()
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(m_x, m_y);
	glEnd();
}

bool CTuteringScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		return true;
	case WM_KEYUP:
		return true;
	}
	return false;
}

bool CTuteringScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		m_pFramework->ChangeScene(CScene::CurrentScene::Main);
		break;
	case WM_MOUSEMOVE:
		break;
	}
	return false;
}

bool CTuteringScene::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_SIZE:
		break;
	case WM_DESTROY:
		break;
	}
	return false;
}

void CTuteringScene::BuildObjects(CFramework * pFramework, HWND hwnd, CurrentScene tag)
{
	CScene::BuildObjects(pFramework, hwnd, tag);
}

void CTuteringScene::ReleaseObjects()
{
}
