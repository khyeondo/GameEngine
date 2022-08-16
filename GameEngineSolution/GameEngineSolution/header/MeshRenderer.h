#ifndef _MESH_RENDERER_H_
#define _MESH_RENDERER_H_

#include "Component.h"

class Mesh;
class Texture;

class MeshRenderer : public Component
{
	ENGINE_INSTANCE(MeshRenderer)
private:
	Mesh* m_pMesh = nullptr;
	Texture* m_pTexture = nullptr;

public:
	void Render() override;
	void SetMesh(Mesh* pMesh);
	void SetTexture(Texture* pTexture);
};

#endif // !_MESH_RENDERER_H_