#pragma once
#include "Scene.h"
#include "Practice.h"
#include "Framework.h" 

#define GetPracticeEnumInt(Enum) GetEnumValueByType(CPractice::CurrentPractice::Enum)

class CPractice;

class CMainScene :public CScene
{
private:
	CPractice* m_pCurrentPractice{ nullptr };
	CPractice* m_arrPractice[GetEnumValueByType(CPractice::CurrentPractice::count)];
	

public:
	CMainScene();
	~CMainScene();

	virtual void Update(float fTimeElapsed);
	virtual void Rendering();

	// 함수 호출 이후에도 처리를 원하면 false 반환
	virtual bool OnProcessingKeyboardMessage	(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildObjects(CFramework* pFramework, HWND hwnd, CurrentScene tag);
	virtual void ReleaseObjects();

	void BuildPractices();
	void ChangePractice(CPractice::CurrentPractice tag, bool bDestroy = false);
	CCamera_OpenGL* GetCamera() { return m_pFramework->GetCamera(); }

	bool ProcessInput();
};
