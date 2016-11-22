#pragma once
class CPractice28 : public CPractice
{
private:
	CCamera m_camera;

	float m_angle_x = 0.0f;
	float m_angle_y = 0.0f;
	float m_angle_z = 0.0f;

	bool m_rotate_x = false;
	bool m_rotate_y = false;
	bool m_rotate_z = false;

public:
	CPractice28();
	~CPractice28();

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

