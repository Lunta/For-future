#pragma once

class CMainScene;

class CPractice
{
public:

	enum class CurrentPractice : int {
		Practice_11 = 0
		, Practice_12
		, Practice_13
		, Practice_14
		, Practice_15
		, Practice_16
		, Practice_17
		, Practice_18
		, Practice_19
		, Practice_20
		, Practice_21
		, Practice_22
		, Practice_23
		, Practice_24
		, Practice_25
		, Practice_26
		, Practice_27
		, Practice_28
		, count
	};

protected:

	CMainScene 		*m_pScene;

	HWND			m_hWnd;
	RECTf			m_rcScene;

	CurrentPractice m_Tag;

public:
	CPractice();
	~CPractice();
	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag);

	virtual void Rendering() = 0;
	virtual void Update(float fTimeElapsed) = 0;
	virtual bool ProcessInput();

	CMainScene* GetMyScene() { return m_pScene; }

	bool IsMyTag(CurrentPractice tag) const { return (tag == m_Tag); }
	CurrentPractice GetMyTag() const { return m_Tag; };
};

