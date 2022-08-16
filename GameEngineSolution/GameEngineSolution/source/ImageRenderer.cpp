#include "../header/ImageRenderer.h"
#include "../header/GameObject.h"

ImageRenderer::ImageRenderer():
	m_pTexture(nullptr),
	m_pivot(Vec2f(0.5f,0.5f)),
	m_anchor(Anchor::LEFT | Anchor::BOTTOM)
{

}
ImageRenderer::~ImageRenderer() {}

void ImageRenderer::Start()
{
	m_pTransform = m_pGameObject->GetTransform();
}

void ImageRenderer::SetTexture(Texture* pTexture)
{
	if (pTexture == nullptr)
		return;
	m_pTexture = pTexture;

	if(m_width == 0)
		m_width = pTexture->width;

	if(m_height == 0)
		m_height = pTexture->height;
}

void ImageRenderer::SetPivot(Vec2f pivot)
{
	m_pivot = pivot;
}

void ImageRenderer::SetAnchor(int anchor)
{
	m_anchor = anchor;
}

void ImageRenderer::SetWidth(unsigned int width)
{
	m_width = width;
}

void ImageRenderer::SetHeight(unsigned int height)
{
	m_height = height;
}

void ImageRenderer::RenderUI()
{
	Vec2f pos = Vec2f(m_pTransform->GetPosition().x, m_pTransform->GetPosition().y);
	RenderTool::Instance()->DrawTexture(m_pTexture, pos, m_width, m_height, m_pivot, m_anchor);
}
