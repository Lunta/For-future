#pragma once
class COrbit
{
private:
	float m_rad{ 0.0f };
	bool m_bSolid{ false };

public:
	COrbit();
	~COrbit();

	void Rendering(float fScale);
	void Update(float fTimeElapsed);

	void SwapType() { if (m_bSolid) m_bSolid = false; else m_bSolid = true; }
};

class CRevolution
{
private:
	COrbit m_orbit_01;
	COrbit m_orbit_02;
	COrbit m_orbit_03;

	float m_rad_01;
	float m_rad_02;
	float m_rad_03;

	bool m_bSolid{ false };

public:
	CRevolution();
	~CRevolution();

	void DrawOrbit(float fScale);

	void Rendering(float fScale);
	void Update(float fTimeElapsed);

	void SwapType();
};