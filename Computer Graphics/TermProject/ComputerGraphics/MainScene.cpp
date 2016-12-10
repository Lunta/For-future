#include "stdafx.h"

#include "Framework.h"
#include "M_Sky.h"
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

void CMainScene::SettingTexture()
{
	m_TextureLib->SetTexture(L"Texture/TILE_1.png");
	m_TextureLib->SetTexture(L"Texture/TILE_2.png");
	m_TextureLib->SetTexture(L"Texture/TILE_3.png");
	m_TextureLib->SetTexture(L"Texture/TILE_4.png");
	m_TextureLib->SetTexture(L"Texture/TILE_5.png");
	m_TextureLib->SetTexture(L"Texture/TILE_6.png");
	m_TextureLib->SetTexture(L"Texture/Bottom.jpg");
	m_TextureLib->SetTexture(L"Texture/Storm.jpg");
	m_TextureLib->SetTexture(L"Texture/Radar.png");
}

void CMainScene::SettingObjects()
{
	// 하늘 생성
	m_Sky = new CM_Sky(m_TextureLib);
	// 바닥 생성
	m_Bottom = new CSurface(m_TextureLib);
	m_Bottom->SetScale(MapSize, 10, MapSize);
	// 장애물 생성
	for (int i = 0; i < ObstarcleNum; i++)
		m_ObstarcleList.push_back(new CCube(m_TextureLib));
	m_ObstarcleList.remove_if([](CCube* p)->bool {return Length(p->GetCenter()) > (MapSize * 0.5f); });
	// 플레이어 기체 생성
	m_Player = new CPlayer();
	m_pCamera->SetTarget(m_Player);
	// 적기체 생성
	for (int i =0; i < InitEnemyNum; i++)
		m_EnemyList.push_back(new CEnemy(Vec3f{0.0f, 0.0f, 0.0f}, m_Player));
	// 보스 생성
	m_Boss = new CBoss(m_Player);
}

void CMainScene::Update(float fTimeElapsed)
{
	m_pCamera->Update(fTimeElapsed);
	ProcessInput();
	float speed = m_Player->GetSpeed();
	if (m_bFront) m_pCamera->TranslatePos(0.0f, 0.0f, speed*fTimeElapsed);
	if (m_bBack ) m_pCamera->TranslatePos(0.0f, 0.0f, -speed*fTimeElapsed);
	if (m_bLeft ) m_pCamera->TranslatePos(speed*fTimeElapsed, 0.0f, 0.0f);
	if (m_bRight) m_pCamera->TranslatePos(-speed*fTimeElapsed, 0.0f, 0.0f);
	m_Sky->Update(fTimeElapsed);
	m_Player->Update(fTimeElapsed);
	for (auto &p : m_EnemyList)
		p->Update(fTimeElapsed);
	m_Boss->Update(fTimeElapsed);
}

void CMainScene::Rendering()
{
	glPushMatrix();
	m_pCamera->LookAt();
	m_pLight->Light(CLight::LightTag::Light0);
	DrawAxis();
	m_Sky->Rander();
	m_Bottom->Rendering();
	for(auto p: m_ObstarcleList)
		p->Rendering();
	for (auto &p : m_EnemyList)
		p->Rendering();
	m_Boss->Rendering();
	m_Player->Rendering();
	glPopMatrix();
}

void CMainScene::RendMiniMap()
{
	glViewport(CLIENT_WIDTH - 300, CLIENT_HEIGHT - 300, 300, 300);
	glPushMatrix();
	m_MiniMapCamera->LookAt();
	m_pLight->Light(CLight::LightTag::Light0);
	DrawAxis();
	for (auto p : m_ObstarcleList)
		p->Rendering();
	glColor3f(1, 0, 0);
	glPointSize(5);
	glBegin(GL_POINTS);
	for (auto p : m_EnemyList)
		glVertex3fv(p->GetCenter().arr);
	glEnd();
	m_Player->Rendering();
	CTextureLibraray::UsingTexture2D();
	m_TextureLib->LoadTexture(CTextureLibraray::TextureIndex::MiniMap);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 0.3f);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(MapSize, 0.0f, MapSize);
	glTexCoord2f(0, 0);
	glVertex3f(MapSize, 0.0f, -MapSize);
	glTexCoord2f(1, 0);
	glVertex3f(-MapSize, 0.0f, -MapSize);
	glTexCoord2f(1, 1);
	glVertex3f(-MapSize, 0.0f, MapSize);
	glEnd();
	glDisable(GL_BLEND);
	CTextureLibraray::StopUsingTexture2D();
	glPopMatrix();
	glViewport(0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
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
	m_MiniMapCamera = m_pFramework->GetMiniMapCamera();
	m_pLight = m_pFramework->GetLight();
	m_TextureLib = m_pFramework->GetTextureLib();
	SettingLight();
	SettingTexture();
	SettingObjects();
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
