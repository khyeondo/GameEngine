#ifndef _GL_REDNER_TOOL_
#define _GL_REDNER_TOOL_

#include "RenderTool.h"

class GLRenderTool : public RenderTool
{
private:

public:
	GLRenderTool() {}
	~GLRenderTool() {}

	bool Init(HDC hDC) override;

	void ProjectionPerspective() override;
	void ProjectionOrtho() override;
	void LocalToWorld(const Transform& transform) override;
	void WorldToView() override;
	void PushMatrix() override;
	void PopMatrix() override;
	void StartRender() override;
	void StartRenderUI() override;
	void EndRender() override;

	void Reshape(int w, int h) override;

	void RenderMesh(const Mesh* pMesh, const Texture* pTexture) override;
	void RenderSkyBox(Texture *pTexture[6]) override;
	void DrawTexture(const Texture* pTexture, const Vec2f& pos, unsigned int width, unsigned int height, const Vec2f& pivot, int anchor) override;

	bool LoadTexture(const std::wstring& path, Texture* out_pTexture) override;

	void SetCamera(Camera* pCamera) override;
};

#endif // !_GL_REDNER_TOOL_

