#include "Rotator.h"
#include "EngineTime.h"
#include "Transform.h"
#include "GameObject.h"

Rotator::Rotator()
{
}

Rotator::~Rotator()
{
}

void Rotator::Update()
{
	m_pGameObject->GetTransform()->AddRotation(Vec3f(0.f,speed* DELTA_TIME,0.f));
}

void Rotator::SetSpeed(float speed)
{
	this->speed = speed;
}