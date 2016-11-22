#pragma once
#include "Practice.h"


class CPractice21 : public CPractice
{
private:
	CCamera m_camera;
	Scale3f m_scale;
	Vertex3f m_Cube[8];

	float m_angle_x = 0.0f;
	float m_angle_y = 0.0f;
	float m_angle_z = 0.0f;

	bool m_rotate_x = false;
	bool m_rotate_y = false;
	bool m_rotate_z = false;

	bool m_shade = false;
	bool m_culling = false;
	bool m_depth = false;
	bool m_upsurface = false;
	bool m_forwardsurface = false;

	float m_uprotate = 0.0f;
	float m_forwardrotate = 0.0f;


public:
	CPractice21();
	~CPractice21();

	void DrawAxis();
	void DrawCube();

	void Reset();

	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag);
	virtual void Rendering();
	virtual void Update(float fTimeElapsed);
	virtual bool ProcessInput();
};