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
	//AddKey함수를 통해 등록된 키는 KeyInfo를 통해 down,hold,up 3가지 상태를 확인할 수 있습니다.
	if (InputMgr::Instance()->GetKeyInfo("up").isHold)
	{	
		//Camera의 GetForward()함수는 카메라가 바라보는 방향 Vector를 반환해 줍니다.
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
		//Camera의 GetRight()함수는 카메라의 오른쪽 방향 Vector를 반환해 줍니다.
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

	//GetMouseDisplacement()함수는 이전 프레임과 현재 프레임의 마우스 위치 차를 반환해줍니다. 
	Vec2i displacement = InputManager::Instance()->GetMouseDisplacement();

	m_pGameObject->GetTransform()->AddRotation(
		Vec3f(-displacement.y / 6.f, -displacement.x / 6.f, 0.f)
	);

	if (InputMgr::Instance()->GetKeyInfo("esc").isDown)
	{
		m_isCursorLock = !m_isCursorLock;
		//SetCursorLock()함수는 마우스가 보일지, 위치를 고정시킬지 여부를 결정하는 함수입니다.
		InputManager::Instance()->SetCursorLock(m_isCursorLock);
	}
	
		
}
