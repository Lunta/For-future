#pragma once
#include "Practice.h"

class CPractice13 : public CPractice
{
private:
	float m_x;
	float m_y;
	float m_rad;

	bool m_bRotate{ false };
	bool m_bUp{ false };
public:
	CPractice13();
	~CPractice13();

	void DrawAixs();
	void DrawTriangles();
	void DrawRotateTriangles();

	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag);
	virtual void Rendering();
	virtual void Update(float fTimeElapsed);
	virtual bool ProcessInput();
};

