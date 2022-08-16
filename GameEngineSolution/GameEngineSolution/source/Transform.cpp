#include "../header/Transform.h"

Transform::Transform():
	m_position(0.f,0.f,0.f),
	m_rotation(0.f, 0.f, 0.f),
	m_scale(1.f, 1.f, 1.f)
{	
}

Transform::~Transform() {}

Vec3f Transform::GetPosition() const
{
	return m_position;
}

Vec3f Transform::GetRotation() const
{
	return m_rotation;
}

Vec3f Transform::GetScale() const
{
	return m_scale;
}

void Transform::SetPosition(const Vec3f& pos)
{
	m_position = pos;
}

void Transform::SetRotation(const Vec3f& rot)
{
	m_rotation = rot;
}

void Transform::SetScale(const Vec3f& scale)
{
	m_scale = scale;
}

void Transform::AddPosition(const Vec3f& vec)
{
	m_position += vec;
}

void Transform::AddRotation(const Vec3f& vec)
{
	m_rotation += vec;
}

void Transform::AddScale(const Vec3f& vec)
{
	m_scale += vec;
}
