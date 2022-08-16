#include "../header/RenderTool.h"
#include "../header/Vec3f.h"

RenderTool* RenderTool::m_pInst = nullptr;

RenderTool::RenderTool()
{
}

RenderTool::~RenderTool()
{
}

void RenderTool::SetCamera(Camera* pCamera)
{
	m_pCamera = pCamera;
}