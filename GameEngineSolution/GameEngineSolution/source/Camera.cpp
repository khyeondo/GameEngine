
#include "../header/Camera.h"
#include "../header/Vec3f.h"
#include "../header/GameObject.h"
#include "../header/Transform.h"
#include "../header/RenderTool.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

#define ToRadian 3.141592/180.0

Camera::Camera() 
{
	RenderTool::Instance()->SetCamera(this);
}
Camera::~Camera() {}

float Camera::GetFov() const
{
	
	return m_fov;
}

float Camera::GetNear() const
{
	return m_near;
}

float Camera::GetFar() const
{
	return m_far;
}

Vec3f Camera::GetPosition()  const
{
	return m_pGameObject->GetComponent<Transform>()->GetPosition();
}

Vec3f Camera::GetRotation() const
{
	return m_pGameObject->GetTransform()->GetRotation();
}

void Camera::SetFov(float fov)
{
	m_fov = fov;
}

void Camera::SetNear(float _near)
{
	m_near = _near;
}

void Camera::SetFar(float _far)
{
	m_far = _far;
}

void Camera::Start()
{
	
}

Vec3f Camera::GetForward()
{
	Transform* pTrasform = m_pGameObject->GetTransform();
	Vec3f rotation = pTrasform->GetRotation();

	glm::mat4 rotationMat = glm::mat4(1.0f);
	glm::vec4 forward = { 0.f,0.f,1.f,1.f };	
	
	rotationMat = glm::rotate(rotationMat, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	rotationMat = glm::rotate(rotationMat, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		
	forward = rotationMat * forward;

	return Vec3f(
		forward.x,
		forward.y,
		forward.z
	) * -1.f;
}

Vec3f Camera::GetRight()
{	
	Transform* pTrasform = m_pGameObject->GetTransform();
	Vec3f rotation = pTrasform->GetRotation();

	glm::mat4 rotationMat = glm::mat4(1.0f);;
	glm::vec4 right = { 1.f,0.f,0.f,1.f };

	rotationMat = glm::rotate(rotationMat, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	rotationMat = glm::rotate(rotationMat, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));

	right = rotationMat * right;

	return Vec3f(
		right.x,
		right.y,
		right.z
	);
}