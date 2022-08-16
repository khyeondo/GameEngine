#ifndef _MESH_H_
#define _MESH_H_

#include <list>

#include "IResource.h"
#include "Vec3f.h"
#include "Vec2f.h"
#include "Vec3i.h"


struct Mesh : public IResource
{
public:
	Vec3f* vertex = nullptr;
	Vec2f* uv = nullptr;
	Vec3f* normal = nullptr;

	int* vertexTriIdx = nullptr;
	int* uvTriIdx = nullptr;
	int* normalTriIdx = nullptr;

	int* vertexQuadIdx = nullptr;
	int* uvQuadIdx = nullptr;
	int* normalQuadIdx = nullptr;

	int triIdxNum = 0;
	int quadIdxNum = 0;

private:
	std::list<int> lineCount;

public:
	~Mesh();
	bool Load(const std::wstring& path) override;
};
#endif // !_MESH_H_