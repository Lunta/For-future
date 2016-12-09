#include "stdafx.h"

#include "Framework.h"
#include "MainScene.h"

using namespace std;

CMainScene::CMainScene()
{
}
CMainScene::~CMainScene()
{
}

void CMainScene::DrawAxis()
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
}

void CMainScene::SettingLight()
{
	m_pLight->LightOn(CLight::LightTag::Light0);
	m_pLight->SetLightAmbient(CLight::LightTag::Light0, 1.0f, 1.0f, 1.0f);
	m_pLight->SetLightDiffuse(CLight::LightTag::Light0, 1.0f, 1.0f, 1.0f);
	m_pLight->SetLightSpecular(CLight::LightTag::Light0, 1.0f, 1.0f, 1.0f);
	m_pLight->SetLightPosition(CLight::LightTag::Light0, 1.0f, 1.0f, 1.0f);
}

void CMainScene::Update(float fTimeElapsed)
{
	m_pCamera->Update(fTimeElapsed);
	ProcessInput();
	if (m_bFront) m_pCamera->TranslatePos(0.0f, 0.0f, 100.0f*fTimeElapsed);
	if (m_bBack ) m_pCamera->TranslatePos(0.0f, 0.0f, -100.0f*fTimeElapsed);
	if (m_bLeft ) m_pCamera->TranslatePos(100.0f*fTimeElapsed, 0.0f, 0.0f);
	if (m_bRight) m_pCamera->TranslatePos(-100.0f*fTimeElapsed, 0.0f, 0.0f);
	if (m_bFront)std::cout<<"m_bFront"<<std::endl;
	if (m_bBack) std::cout<<"m_bBack"<<std::endl;
	if (m_bLeft) std::cout<<"m_bLeft"<<std::endl;
	if (m_bRight)std::cout<<"m_bRight"<<std::endl;
}

void CMainScene::Rendering()
{
	glPushMatrix();
	glLoadIdentity();
	m_pCamera->LookAt();
	m_pLight->Light(CLight::LightTag::Light0);
	DrawAxis();
	m_Bottom.Rendering();
	glutSolidCube(100.0f);
	glPopMatrix();
}

bool CMainScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	}
	return false;
}

bool CMainScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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
		break;
	case WM_MOUSEMOVE:
		m_pCamera->RotateViewDirection(LOWORD(lParam), HIWORD(lParam));
		break;
	}
	return false;
}

bool CMainScene::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

void CMainScene::BuildObjects(CFramework * myFramework, HWND hWnd, CurrentScene tag)
{
	CScene::BuildObjects(myFramework, hWnd, tag);
	m_pCamera = m_pFramework->GetCamera();
	m_pLight = m_pFramework->GetLight();
	m_TextureLib = m_pFramework->GetTextureLib();
	SettingLight();
	m_Bottom.SetScale(1000, 10, 1000);
}

void CMainScene::ReleaseObjects()
{
}


bool CMainScene::ProcessInput()
{
	bool bProcessedByScene = false;

	if (!bProcessedByScene)
	{
		static UCHAR pKeyBuffer[256];
		DWORD dwLRDirection = 0;
		DWORD dwUDDirection = 0;

		bool bPushShift = false;
		bool bControll = false;

		if (GetKeyboardState(pKeyBuffer))
		{
			if (pKeyBuffer[VK_LSHIFT] & 0xF0)	bPushShift = true;
			if (pKeyBuffer['W'] & 0xF0)			dwUDDirection |= DIR_UP;
			if (pKeyBuffer['S'] & 0xF0)			dwUDDirection |= DIR_DOWN;
			if (pKeyBuffer['A'] & 0xF0)			dwLRDirection |= DIR_LEFT;
			if (pKeyBuffer['D'] & 0xF0)			dwLRDirection |= DIR_RIGHT;

			if (pKeyBuffer['F'] & 0xF0) { bControll = true; m_pCamera->SetProjection(CCamera_OpenGL::ProjectionType::Ortho); }
			else if (pKeyBuffer['Q'] & 0xF0) { bControll = true; PostQuitMessage(0); }
			if ((pKeyBuffer['A'] & 0xF0) || (pKeyBuffer['D'] & 0xF0))
			{
				if (dwLRDirection & DIR_LEFT) { bControll = true; m_bLeft = true;}
				else m_bLeft = false;
				if (dwLRDirection & DIR_RIGHT) { bControll = true; m_bRight = true;}
				else m_bRight = false;
			}
			else
			{
				m_bLeft = false;
				m_bRight = false;
			}
			if ((pKeyBuffer['W'] & 0xF0) || (pKeyBuffer['S'] & 0xF0))
			{
				if (dwUDDirection & DIR_UP) { bControll = true; m_bFront = true; }
				else m_bFront = false;
				if (dwUDDirection & DIR_DOWN) { bControll = true; m_bBack = true; }
				else m_bBack = false;
			}
			else
			{
				m_bFront = false;
				m_bBack = false;
			}
		}

		if (!bControll)
		{
			
		}

		return bControll;
	}
	return false;
}
