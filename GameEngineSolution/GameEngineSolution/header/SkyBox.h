#ifndef _SKY_BOX_H_
#define _SKY_BOX_H_

#include "Component.h"

class Texture;

enum class SideOfSkyBox
{
	TOP,
	BOTTOM,
	LEFT,
	FRONT,
	RIGHT,
	BACK	
};

class SkyBox : public Component
{
	ENGINE_INSTANCE(SkyBox)

private:
	Texture *m_pTexture[6];

public:
	void Render() override;
	void SetTexture(SideOfSkyBox side, Texture* pTexture);
};

#endif // !_SKY_BOX_H_

