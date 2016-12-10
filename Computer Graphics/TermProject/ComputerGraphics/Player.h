#pragma once
#include "MyObject.h"
#include "M_Player.h"

class CPlayer : public CMyObject
{
private:
	C_M_Player m_Model;
	Vec3f m_vDirection;
	CCube m_BindingCube;

	int m_Hp = 5;
	int m_Barrier = 100;
	int m_Boost = 100;
	float m_Speed = 200.0f;

	bool m_bDie = false;
public:
	CPlayer();
	~CPlayer();

	void SetPos(Vec3f& pos) { m_BindingCube.SetPos(pos); m_vCenter = pos; m_vCenter -= 6.0f*m_vDirection; }
	void RotateToDirection(Vec3f& look, Vec3f& angle);

	const float GetSpeed() const { return m_Speed; }

	virtual void Update(const float fTimeElapsed);
	virtual void Rendering();

	virtual void Translate(const Vec3f move) { m_vCenter += move; }
	virtual void Rotate(const float angle, bool x, bool y, bool z);
};

