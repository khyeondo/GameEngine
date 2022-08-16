#ifndef _CAMERA_CONTROLLER_H_
#define _CAMERA_CONTROLLER_H_

#include "Component.h"

class CameraController : public Component
{
	//�ش� Ŭ������ GameObject�� friend�� ����Ͽ� 
	//GameObject���� �޸𸮸� ������ �� �ְ� �ϱ� ���� ��ũ���Դϴ�.
	ENGINE_INSTANCE(CameraController)
private:
	class Camera* m_pCamera;
	bool m_isCursorLock = false;

public:
	void Start() override;
	void Update() override;
};


#endif // !_CAMERA_CONTROLLER_H_

