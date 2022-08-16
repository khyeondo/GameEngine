#include "CameraController.h"
#include "GameObject.h"
#include "EngineTime.h"
#include "InputManager.h"
#include "Camera.h"

#include <iostream>

CameraController::CameraController() {}
CameraController::~CameraController() {}

void CameraController::Start()
{
	m_pCamera = m_pGameObject->GetComponent<Camera>();
	InputManager::Instance()->SetCursorLock(true);
}

void CameraController::Update()
{
	//AddKey�Լ��� ���� ��ϵ� Ű�� KeyInfo�� ���� down,hold,up 3���� ���¸� Ȯ���� �� �ֽ��ϴ�.
	if (InputMgr::Instance()->GetKeyInfo("up").isHold)
	{	
		//Camera�� GetForward()�Լ��� ī�޶� �ٶ󺸴� ���� Vector�� ��ȯ�� �ݴϴ�.
		m_pGameObject->GetTransform()->AddPosition(
			m_pCamera->GetForward() *6.0f*DELTA_TIME);
	}
	if (InputMgr::Instance()->GetKeyInfo("down").isHold)
	{
		m_pGameObject->GetTransform()->AddPosition(
			m_pCamera->GetForward()* -6.f * DELTA_TIME);
	}
	if (InputMgr::Instance()->GetKeyInfo("left").isHold)
	{
		//Camera�� GetRight()�Լ��� ī�޶��� ������ ���� Vector�� ��ȯ�� �ݴϴ�.
		m_pGameObject->GetTransform()->AddPosition(
			m_pCamera->GetRight()* -6.f * DELTA_TIME);
	}
	if (InputMgr::Instance()->GetKeyInfo("right").isHold)
	{
		m_pGameObject->GetTransform()->AddPosition(
			m_pCamera->GetRight()*6.0f*DELTA_TIME);
	}	

	if (InputMgr::Instance()->GetKeyDown('Q'))
	{
		m_pGameObject->GetTransform()->AddPosition(
			Vec3f(0, 6.f * DELTA_TIME, 0));
	}
	if (InputMgr::Instance()->GetKeyDown('E'))
	{
		m_pGameObject->GetTransform()->AddPosition(
			Vec3f(0, -6.f * DELTA_TIME, 0));
	}

	//GetMouseDisplacement()�Լ��� ���� �����Ӱ� ���� �������� ���콺 ��ġ ���� ��ȯ���ݴϴ�. 
	Vec2i displacement = InputManager::Instance()->GetMouseDisplacement();

	m_pGameObject->GetTransform()->AddRotation(
		Vec3f(-displacement.y / 6.f, -displacement.x / 6.f, 0.f)
	);

	if (InputMgr::Instance()->GetKeyInfo("esc").isDown)
	{
		m_isCursorLock = !m_isCursorLock;
		//SetCursorLock()�Լ��� ���콺�� ������, ��ġ�� ������ų�� ���θ� �����ϴ� �Լ��Դϴ�.
		InputManager::Instance()->SetCursorLock(m_isCursorLock);
	}
	
		
}
