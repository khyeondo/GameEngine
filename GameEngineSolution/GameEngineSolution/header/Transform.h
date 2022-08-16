#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Component.h"
#include "Vec3f.h"

class Transform : public Component
{
	ENGINE_INSTANCE(Transform)
private:
	Vec3f m_position;
	Vec3f m_rotation;
	Vec3f m_scale;

public:
	Vec3f GetPosition() const;
	Vec3f GetRotation() const;
	Vec3f GetScale() const;

	void SetPosition(const Vec3f& pos);
	void SetRotation(const Vec3f& rot);
	void SetScale(const Vec3f& scale);

	void AddPosition(const Vec3f& vec);
	void AddRotation(const Vec3f& vec);
	void AddScale(const Vec3f& vec);
};

#endif // _TRANSFORM_H_