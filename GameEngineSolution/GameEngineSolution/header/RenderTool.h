#ifndef _GRAPHICS_API_H_
#define _GRAPHICS_API_H_

#include <Windows.h>
#include <string>

#include "Singleton.h"

#include "Texture.h"
class Transform;
class Camera;
class Mesh;

enum Anchor
{
	LEFT   = 0b000001,
	CENTER = 0b000010,
	RIGHT  = 0b000100,
	BOTTOM = 0b001000,
	MIDDLE = 0b010000,
	TOP	   = 0b100000,
};

class RenderTool
{	
private:
	static RenderTool* m_pInst;

public:
	static RenderTool* Instance() {
		return m_pInst;
	}
	static void DestroySingle() {
		delete m_pInst;
	}

protected:
	Camera* m_pCamera = nullptr;

protected:
	RenderTool();
	virtual ~RenderTool();

public:
	virtual bool Init(HDC hDC) = 0;
	
	virtual void ProjectionPerspective() = 0;
	virtual void ProjectionOrtho() = 0;
	virtual void LocalToWorld(const Transform& tramsform) = 0;
	virtual void WorldToView() = 0;
	virtual void PushMatrix() = 0;
	virtual void PopMatrix() = 0;
	virtual void StartRender() = 0;
	virtual void StartRenderUI() = 0;
	virtual void EndRender() = 0;

	virtual void Reshape(int w, int h) = 0;

	virtual void RenderMesh(const Mesh* pMesh, const Texture* pTexture) = 0;
	virtual void RenderSkyBox(Texture *pTexture[6]) = 0;
	virtual void DrawTexture(const Texture* pTexture,const Vec2f& pos, unsigned int width, unsigned int height,const Vec2f& pivot, int anchor) = 0;

	virtual bool LoadTexture(const std::wstring& path, Texture* out_pTexture) = 0;

	virtual void SetCamera(Camera* pCamera);


	template<class T>
	static void CreateRenderTool()
	{
		m_pInst = new T();
	}	 
};

#endif // !_TOOL_INTERFACE_H
