#pragma once
#include "Vector3D.h"


class CHexTechTower
{
private:
	float m_radius{128};
	float m_height{512};

	Vec3f m_gray{ 0.5f,0.5f,0.5f };
	Vec3f m_specref{ 1.0f,1.0f,1.0f };

	int m_gearangle{};
public:
	enum class CubePos {
		LTF = 0
		, LTB
		, RTF
		, RTB
		, LBF
		, LBB
		, RBF
		, RBB
	};
public:
	CHexTechTower();
	~CHexTechTower();

	bool Update();
	void Rander();

	void RandColumns();
	void RandWallGears();
};

