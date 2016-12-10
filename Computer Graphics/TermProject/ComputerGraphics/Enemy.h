#pragma once
#include "MyObject.h"
#include "M_CombatDrone.h"
#define Turning_Speed 1.0f

class CEnemy : public CMyObject
{
private:
	C_M_CombatDrone m_Model;
	Vec3f m_vDirection;
	CCube m_BindingCube;

	CPlayer * m_Target;

	int m_Hp = 3;
	int m_Barrier = 10;
	float m_speed = 150;

	float m_Timer = 0.0f;

	bool m_bDie = false;
public:
	CEnemy();
	CEnemy(Vec3f &pos, CPlayer * target);
	~CEnemy();

	virtual void Update(const float fTimeElapsed);
	virtual void Rendering();

	virtual void Translate(const Vec3f move) { m_vCenter += move; }
	virtual void Rotate(const float angle, bool x, bool y, bool z);
};

