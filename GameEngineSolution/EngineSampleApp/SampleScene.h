#ifndef __SAMPLE_SCENE__
#define __SAMPLE_SCENE__

#include "Scene.h"

class SampleScene : public Scene 
{
public:
	void SetHierarchy() override; //GameObject의 계층구조와 초기 값을 설정하는 함수입니다.
};
#endif // !__SAMPLE_SCENE__
