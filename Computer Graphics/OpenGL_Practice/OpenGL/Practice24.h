#pragma once
#include "Practice.h"


class CPractice24 : public CPractice
{
private:
	CCamera m_camera;
	Scale3f m_scale;
	Vertex3f m_Cube[8];
	SFormularf m_Surface[6];
	CCube m_fallCube[3];

	float m_matrix[16];

	std::list<CSphere*> m_SphereList;

	float m_angle_x = 0.0f;
	float m_angle_y = 0.0f;
	float m_angle_z = 0.0f;

	bool m_rotate_x = false;
	bool m_rotate_y = false;
	bool m_rotate_z = false;
	bool m_bAdd = false;

	bool m_btop = false;
	bool m_bbottom = false;
	bool m_bback = false;
	bool m_bforward = false;
	bool m_bleft = false;
	bool m_bright = false;

	int prev_x;
public:
	CPractice24();
	~CPractice24();

	void DrawAxis();
	void DrawCube();

	void Reset();

	void CheckCollide();

	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag);
	virtual void Rendering();
	virtual void Update(float fTimeElapsed);
	virtual bool ProcessInput();
};