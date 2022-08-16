#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "IResource.h"
#include "Vec2f.h"

struct Texture : public IResource
{
	void* m_pTexture;

	unsigned int width;
	unsigned int height;

	Texture();
	~Texture();
	bool Load(const std::wstring& path) override;
};

#endif // !_TEXTURE_H_