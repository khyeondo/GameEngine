#include "../header/MeshRenderer.h"
#include "../header/RenderTool.h"
#include "../header/Mesh.h"
#include "../header/Texture.h"

MeshRenderer::MeshRenderer() {}
MeshRenderer::~MeshRenderer() {}

void MeshRenderer::Render() 
{
	if (m_pMesh != nullptr)
	{
		RenderTool::Instance()->RenderMesh(m_pMesh,m_pTexture);
	}
}

void MeshRenderer::SetMesh(Mesh* pMesh)
{
	m_pMesh = pMesh;
}

void MeshRenderer::SetTexture(Texture* pTexture)
{
	m_pTexture = pTexture;
}
