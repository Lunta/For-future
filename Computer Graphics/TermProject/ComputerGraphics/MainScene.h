#pragma once
#include "Scene.h"

class CMainScene :public CScene
{
private:
	CCamera_OpenGL* m_pCamera;
	CLight *m_pLight;
	CTextureLibraray * m_TextureLib;

	CSurface m_Bottom;

	bool m_bFront = false;
	bool m_bBack = false;
	bool m_bLeft = false;
	bool m_bRight = false;
public:
	CMainScene();
	~CMainScene();

	void DrawAxis();
	void SettingLight();

	virtual void Update(float fTimeElapsed);
	virtual void Rendering();

	virtual bool OnProcessingKeyboardMessage	(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildObjects(CFramework* pFramework, HWND hwnd, CurrentScene tag);
	virtual void ReleaseObjects();

	CCamera_OpenGL* GetCamera() { return m_pFramework->GetCamera(); }
	CLight* GetLight() { return m_pFramework->GetLight(); }

	bool ProcessInput();
};
