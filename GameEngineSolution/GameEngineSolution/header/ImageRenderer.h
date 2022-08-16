#ifndef _IMAGE_REDNERER_H_
#define _IMAGE_REDNERER_H_

#include "Component.h"
#include "RenderTool.h"

class Texture;
class Transform;

class ImageRenderer : public Component
{
	ENGINE_INSTANCE(ImageRenderer)
private:
	Texture* m_pTexture = nullptr;
	Vec2f m_pivot = { 0.5f,0.5f };
	Transform* m_pTransform = nullptr;
	int m_anchor;

	unsigned int m_width;
	unsigned int m_height;	
	
public:
	void Start() override;

	void SetTexture(Texture* pTexture);
	void SetPivot(Vec2f pivot);
	void SetAnchor(int anchor);
	void SetWidth(unsigned int width);
	void SetHeight(unsigned int height);

	void RenderUI() override;
};

#endif // !_IMAGE_REDNERER_H_
