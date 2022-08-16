#ifndef __TO_NEXT_SCENE_H__
#define __TO_NEXT_SCENE_H__

#include "Component.h"

class ToNextScene :public Component
{
	ENGINE_INSTANCE(ToNextScene)
public:
	void Update() override;
};

#endif 