#pragma once
#include "Practice.h"
#include "Orbit.h"


class CPractice15 : public CPractice
{
private:
	CRevolution m_orbit;

	float m_camera_X{ 0.0f };
	float m_camera_Y{ 0.0f };
	float m_camera_Z{ 0.0f };

	float m_rad_X{ 0.0f };
	float m_rad_Y{ 0.0f };
	float m_rad_Z{ 0.0f };
	
	bool m_bRotate_X{ false };
	bool m_bRotate_Y{ false };
	bool m_bRotate_Z{ false };

public:
	CPractice15();
	~CPractice15();

	void RotateAxis();
	void DrawAxis();

	void Reset();

	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag);
	virtual void Rendering();
	virtual void Update(float fTimeElapsed);
	virtual bool ProcessInput();
};

