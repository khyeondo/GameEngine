#ifndef __ROTATOR_H__
#define __ROTATOR_H__

#include "Component.h"

class Rotator : public Component
{
	ENGINE_INSTANCE(Rotator)
private:
	float speed = 10.f;

public:
	void Update() override;
	void SetSpeed(float speed);
};


#endif // !__ROTATOR_H__
