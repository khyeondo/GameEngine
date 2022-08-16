#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Component.h"

class Vec3f;

class Camera : public Component
{	
	ENGINE_INSTANCE(Camera)
private:
	float m_fov = 40.0f;
	float m_near = 0.1f;
	float m_far = 1000.0f;

public:
	void Start() override;

	float GetFov() const;
	float GetNear() const;
	float GetFar() const;
	Vec3f GetPosition() const;
	Vec3f GetRotation() const;

	void SetFov(float fov);
	void SetNear(float _near);
	void SetFar(float _far);

	Vec3f GetForward();
	Vec3f GetRight();
};

#endif // !_CAMERA_H_