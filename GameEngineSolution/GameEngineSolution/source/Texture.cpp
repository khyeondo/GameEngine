#include "../header/Texture.h"
#include "../header/RenderTool.h"

Texture::Texture()
{}

Texture::~Texture() {
	delete m_pTexture;
}

bool Texture::Load(const std::wstring& path)
{
	if (!RenderTool::Instance()->LoadTexture(path, this))
		return false;

	return true;
}