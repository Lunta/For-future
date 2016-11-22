#pragma once
#include "Practice.h"


class CPractice20 : public CPractice
{
private:
	CCamera m_camera;
	CCube m_cube;
	CBuilding_Cone m_build_cone;
	CTree_Cube m_tree_cube;
	CTree_Sphere m_tree_sphere;
	CBuilding_n m_build_n;
	CBuilding_Torus m_build_torus;
	CCrane m_Crane;
	CSphere m_sphere;

	float m_angle_x = 0.0f;
	float m_angle_y = 0.0f;
	float m_angle_z = 0.0f;

	bool m_rotate_x = false;
	bool m_rotate_y = false;
	bool m_rotate_z = false;

public:
	CPractice20();
	~CPractice20();

	void DrawAxis();

	void Reset();

	bool CheckCollide(Vertex3f* a, Vertex3f* b);

	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag);
	virtual void Rendering();
	virtual void Update(float fTimeElapsed);
	virtual bool ProcessInput();
};