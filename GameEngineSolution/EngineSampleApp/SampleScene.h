#ifndef __SAMPLE_SCENE__
#define __SAMPLE_SCENE__

#include "Scene.h"

class SampleScene : public Scene 
{
public:
	void SetHierarchy() override; //GameObject�� ���������� �ʱ� ���� �����ϴ� �Լ��Դϴ�.
};
#endif // !__SAMPLE_SCENE__
