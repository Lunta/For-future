#pragma once
#include "Practice.h"
class CPractice11 : public CPractice
{
private:
	float m_fStartAngle{ 0.0f }; // Animation
	float m_fScale{ 1.0f };
	float m_fRotateAngle_X{ 0.0f };
	float m_fRotateAngle_Y{ 0.0f };
	float m_fRotateAngle_Z{ 0.0f };
	float m_fTranslateLength{ 0.0f };

	bool m_bRotate_Axis_X{ false };
	bool m_bRotate_Axis_Y{ false };
	bool m_bRotate_Axis_Z{ false };
	bool m_bReset{ false };
	bool m_bAnimation{ false };
	bool m_bScale{ false };
	bool m_bDeScale{ false };
	bool m_bTranslate_Left{ false };
	bool m_bTranslate_Right{ false };

public:
	CPractice11();
	~CPractice11();

	void DrawAxis();
	void DrawSin();
	void DrawCos();
	void DrawSpring();
	void DrawRect();

	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag);
	virtual void Rendering();
	virtual void Update(float fTimeElapsed);
	virtual bool ProcessInput();
};

