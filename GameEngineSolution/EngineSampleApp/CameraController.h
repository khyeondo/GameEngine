#ifndef _CAMERA_CONTROLLER_H_
#define _CAMERA_CONTROLLER_H_

#include "Component.h"

class CameraController : public Component
{
	//해당 클래스를 GameObject에 friend로 등록하여 
	//GameObject에서 메모리를 관리할 수 있게 하기 위한 매크로입니다.
	ENGINE_INSTANCE(CameraController)
private:
	class Camera* m_pCamera;
	bool m_isCursorLock = false;

public:
	void Start() override;
	void Update() override;
};


#endif // !_CAMERA_CONTROLLER_H_

