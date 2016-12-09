#pragma once
#include "Player_Model.h"
#include "MyObject.h"


class CPlayer : public CMyObject
{
private:
	CPlayer_Model m_Model;

public:
	CPlayer();
	~CPlayer();
};

