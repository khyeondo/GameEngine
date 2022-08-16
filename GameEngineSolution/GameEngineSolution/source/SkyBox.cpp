#include "../header/SkyBox.h"
#include "../header/RenderTool.h"

SkyBox::SkyBox() {}
SkyBox::~SkyBox() {}

void SkyBox::Render()
{
	RenderTool::Instance()->RenderSkyBox(m_pTexture);
}

void SkyBox::SetTexture(SideOfSkyBox side, Texture* pTexture)
{
	m_pTexture[(int)side] = pTexture;	
}