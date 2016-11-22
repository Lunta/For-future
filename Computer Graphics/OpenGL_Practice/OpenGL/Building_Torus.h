#pragma once

class CBuilding_Torus
{
private:
	Vertex3f m_Center;
	Angle3f m_Angle;
	Scale3f m_Scale;
	Vertex3f m_BindingBox[8];
	float m_matrix[16];

	CCube m_body;
	float m_traslate;
	bool m_bflag = false;
public:
	CBuilding_Torus();
	~CBuilding_Torus();

	void Rendering();
	void Update(float fTimeElapsed);

	void Rotate(float move_angle, bool move_x, bool move_y, float move_z);
	void Translate(float move_x, float move_y, float move_z);
	void Scale(float scale_x, float scale_y, float scale_z);

	void SetColor(BYTE r, BYTE g, BYTE b, BYTE a = 255);

	Vertex3f* GetBB() { return m_BindingBox; }
	Vertex3f GetCenter() { return m_Center; }

	void Reset();
};

