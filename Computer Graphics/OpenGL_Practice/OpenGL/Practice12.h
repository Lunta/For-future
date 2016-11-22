#pragma once
#include "Practice.h"
class CPractice12 : public CPractice
{
private:
	enum class Mode {
		Normal,
		Sin,
		Spring,
		Zigzag,
		Free
	};
private:
	std::list<Vec2f*> m_MouseInput;
	Vec2f m_Center;
	Vec2f m_vec[5];
	int m_vec_idx;

	float m_x;
	float m_y;
	float m_rad;
	float m_size;

	float m_ratate_rad;

	Mode m_mode{ Mode::Normal };

	bool m_bTriangle{ true };
	bool m_bRotate{ false };
	bool m_bUp{ false };
	bool m_bMove{ false };

	float m_fInputTimer;

public:
	CPractice12();
	~CPractice12();

	void DrawBK();
	void DrawFigure();
	void Reset();

	void ModeNormal();
	void ModeSin();
	void ModeSpring();
	void ModeZigzag();
	void ModeFree();

	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag);
	virtual void Rendering();
	virtual void Update(float fTimeElapsed);
	virtual bool ProcessInput();
};

