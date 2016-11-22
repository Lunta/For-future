#pragma once
#include "Practice.h"


class CPractice14 : public CPractice
{
private:
	enum class Figure {
		Cube,
		Sphere,
		Teapot,
		Cone
	};
private:
	Figure m_type{ Figure::Cube };

	float m_camera_Z{ 0.0f };

	float m_rad_X{ 0.0f };
	float m_rad_Y{ 0.0f };
	float m_rad_Z{ 0.0f };

	float m_rad_Solid{ 0.0f };
	float m_rad_Wire{ 0.0f };

	bool m_bRotate_X{ false };
	bool m_bRotate_Y{ false };
	bool m_bRotate_Z{ false };

	bool m_bRotate_Solid{ false };
	bool m_bRotate_Wire{ false };
public:
	CPractice14();
	~CPractice14();

	void DrawAxis();
	void DrawFloor();
	void DrawFigure_Solid();
	void DrawFigure_Wire();

	void RotateAxis();

	void Reset();

	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag);
	virtual void Rendering();
	virtual void Update(float fTimeElapsed);
	virtual bool ProcessInput();
};

