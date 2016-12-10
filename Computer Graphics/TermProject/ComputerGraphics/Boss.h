#pragma once
#include "MyObject.h"
#include "M_HexTechTower.h"

class CBoss : public CMyObject
{
private:
	C_M_HexTechTower m_Model;

	Vec3f m_vDirection;
	CCube m_BindingCube;

	CPlayer * m_Target;

	int m_Hp = 3;
	int m_Barrier = 10;

	bool m_bDie = false;
public:
	CBoss();
	CBoss(CPlayer * target);
	~CBoss();

	virtual void Update(const float fTimeElapsed);
	virtual void Rendering();

	virtual void Translate(const Vec3f move) { m_vCenter += move; }
	virtual void Rotate(const float angle, bool x, bool y, bool z);
};

