#pragma once
#define radius_per_one_degree 0.0174532925f;

class CCamera_OpenGL
{
public:
	enum class ProjectionType {
		Perspective
		, Ortho
	};
	enum class CameraMoveMode {
		None
		, Straight
		, Curve
	};
	enum class CameraViewMode {
		TPS
		, FPS
		, TOP
	};
private:
	HWND m_hWnd;

	int m_Client_Width;
	int m_Client_Height;

	double m_fovy;
	double m_aspect;
	double m_zNear;
	double m_zFar;

	Angle3f m_Angle;
	float m_Sensitivity;

	Vec3f m_Pos;
	Vec3f m_Look;
	Vec3f m_Up;

	Vec3f m_TargetPos;

	ProjectionType m_P_Type;
	CameraMoveMode m_C_Type;
	CameraViewMode m_V_Type;

	bool m_bFixTarget;
	bool m_bShake;
public:
	CCamera_OpenGL(); 
	CCamera_OpenGL(HWND hWnd, const int client_width, const int client_height);
	~CCamera_OpenGL();

	void Projection(); // It must use in reshape function of framework.
	void LookAt(); // Use glLookAt function. It must use in rendering function of scene.
	
	void SetProjection(ProjectionType type);
	void SetViewMode(CameraViewMode mode);
	void SetTargetPos(const float x, const float y, const float z);

	void FixTarget();
	void ReleaseTarget();

	void TranslatePos(const float side, const float up, const float forward); // Move the camera position.
	void RotateViewDirection(const int x, const int y); // Rotate the look vector and you can look around.
	void TargetTracing(CameraMoveMode mode);
	void ZoomScaling(const int scale, const bool smooth = false);
	void ShakeCamera(const float power, const bool axis_x = false, const bool axis_y = true); // Shake the camera about axis y or axis x.

	void Update(float fTimeElapsed);

	void SetSensivity(const float sensitivity);
};

