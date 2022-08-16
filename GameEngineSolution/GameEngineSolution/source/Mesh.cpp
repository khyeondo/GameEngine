

#include "../header/Mesh.h"

#include <iostream>
#include <fstream>
#include <strstream>

Mesh::~Mesh()
{
	delete[] vertex;
	delete[] uv;
	delete[] normal;
	//delete[] vertexIdx;
}

bool Mesh::Load(const std::wstring& path)
{
	std::ifstream f(path);

	if (!f.is_open())
		return false;

	int vertexCnt = 0;
	int indexCnt = 0;
	int uvCnt = 0;
	int normalCnt = 0;

	bool isLineTri = true;

	int lineNum = 0;
	while (!f.eof())
	{
		char line[128];
		f.getline(line, 128);	
		if (line[0] == 'v')
		{
			if (line[1] == 't')
				uvCnt++;
			else if (line[1] == 'n')
				normalCnt++;
			else
				vertexCnt++;
		}
		else if (line[0] == 'f')
		{
			indexCnt++;

			int i = 0;
			int n = 0;
			while (line[i] != '\0')
			{
				if (line[i] == ' ')
				{
					n++;
				}
				i++;
			}
			if (n == 3) {
				if (isLineTri == false) {
					lineCount.push_back(lineNum);
				}
				isLineTri = true;
				triIdxNum++;
			}
			else if (n == 4) {
				if (isLineTri == true) {
					lineCount.push_back(lineNum);
				}
				isLineTri = false;
				quadIdxNum++;
			}
		}
		lineNum++;
	}

	vertex = new Vec3f[vertexCnt];

	if (uvCnt != 0) {
		uv = new Vec2f[uvCnt];		
	}
	if (normalCnt != 0) {
		normal = new Vec3f[normalCnt];
	}

	if (triIdxNum != 0) {
		vertexTriIdx = new int[triIdxNum * 3];
		if (uvCnt != 0)
			uvTriIdx = new int[triIdxNum * 3];
		if(normalCnt != 0)
			normalTriIdx = new int[triIdxNum * 3];
	}
	if (quadIdxNum != 0) {
		vertexQuadIdx = new int[quadIdxNum * 4];
		if (uvCnt != 0)
			uvQuadIdx = new int[quadIdxNum * 4];
		if (normalCnt != 0)
			normalQuadIdx = new int[quadIdxNum * 4];
	}

	//idxNum = indexCnt;

	int triIdxCnt = 0;
	int quadIdxCnt = 0;
	vertexCnt = 0;
	uvCnt = 0;
	normalCnt = 0;

	f.clear();
	f.seekg(0, std::ios_base::beg);

	isLineTri = true;
	lineNum = 0;
	char tmp;
	char line[128];

	while (!f.eof())
	{
		f.getline(line, 128);

		std::strstream s;
		s << line;		

		if (line[0] == 'v')
		{
			if (line[1] == 'n')
			{
				s >> tmp >> normal[normalCnt].x >> normal[normalCnt].y >> normal[normalCnt].z;
				normalCnt++;
			}
			else if (line[1] == 't')
			{
				s >> tmp >> tmp >> uv[uvCnt].x >> uv[uvCnt].y;
				uvCnt++;
			}
			else
			{
				s >> tmp >> vertex[vertexCnt].x >> vertex[vertexCnt].y >> vertex[vertexCnt].z;
				vertexCnt++;
			}
		}
		if (line[0] == 'f')
		{
			if (lineCount.size() != 0) {
				if (lineCount.front() == lineNum)
				{
					isLineTri = !isLineTri;
					lineCount.pop_front();
				}
			}


			if (isLineTri == true)
			{
				if (uv != nullptr && normal != nullptr)
				{
					s >> tmp >> vertexTriIdx[triIdxCnt*3]     >> tmp >> uvTriIdx[triIdxCnt*3]	  >> tmp >> normalTriIdx[triIdxCnt*3]
							 >> vertexTriIdx[triIdxCnt*3 + 1] >> tmp >> uvTriIdx[triIdxCnt*3 + 1] >> tmp >> normalTriIdx[triIdxCnt*3 + 1]
							 >> vertexTriIdx[triIdxCnt*3 + 2] >> tmp >> uvTriIdx[triIdxCnt*3 + 2] >> tmp >> normalTriIdx[triIdxCnt*3 + 2];
					vertexTriIdx[triIdxCnt*3]--;
					vertexTriIdx[triIdxCnt*3 + 1]--;
					vertexTriIdx[triIdxCnt*3 + 2]--;
					uvTriIdx[triIdxCnt*3]--;
					uvTriIdx[triIdxCnt*3 + 1]--;
					uvTriIdx[triIdxCnt*3 + 2]--;
					normalTriIdx[triIdxCnt*3]--;
					normalTriIdx[triIdxCnt*3 + 1]--;
					normalTriIdx[triIdxCnt*3 + 2]--;
				}
				else if (normal != nullptr)
				{
					s >> tmp >> vertexTriIdx[triIdxCnt*3] >> tmp >> uvTriIdx[triIdxCnt*3] >> tmp 
						>> vertexTriIdx[triIdxCnt*3 + 1] >> tmp >> uvTriIdx[triIdxCnt*3 + 1] >> tmp 
						>> vertexTriIdx[triIdxCnt*3 + 2] >> tmp >> uvTriIdx[triIdxCnt*3 + 2] >> tmp;
					vertexTriIdx[triIdxCnt*3]--;
					vertexTriIdx[triIdxCnt*3 + 1]--;
					vertexTriIdx[triIdxCnt*3 + 2]--;
					uvTriIdx[triIdxCnt*3]--;
					uvTriIdx[triIdxCnt*3 + 1]--;
					uvTriIdx[triIdxCnt*3 + 2]--;
				}
				else if (uv != nullptr) 
				{
					s >> tmp >> vertexTriIdx[triIdxCnt*3] >> tmp >> normalTriIdx[triIdxCnt*3] 
						>> vertexTriIdx[triIdxCnt*3 + 1] >> tmp >> normalTriIdx[triIdxCnt*3 + 1]
						>> vertexTriIdx[triIdxCnt*3 + 2] >> tmp >> normalTriIdx[triIdxCnt*3 + 2];
					vertexTriIdx[triIdxCnt*3]--;
					vertexTriIdx[triIdxCnt*3 + 1]--;
					vertexTriIdx[triIdxCnt*3 + 2]--;
					normalTriIdx[triIdxCnt*3]--;
					normalTriIdx[triIdxCnt*3 + 1]--;
					normalTriIdx[triIdxCnt*3 + 2]--;
				}
				else
				{
					s >> tmp >> vertexTriIdx[triIdxCnt*3]
						>> vertexTriIdx[triIdxCnt*3 + 1]
						>> vertexTriIdx[triIdxCnt*3 + 2];
					vertexTriIdx[triIdxCnt*3]--;
					vertexTriIdx[triIdxCnt*3 + 1]--;
					vertexTriIdx[triIdxCnt*3 + 2]--;
				}
				triIdxCnt++;
			}
			else
			{
				if (uv != nullptr && normal != nullptr)
				{
					s >> tmp >> vertexQuadIdx[quadIdxCnt*4] >> tmp >> uvQuadIdx[quadIdxCnt*4] >> tmp >> normalQuadIdx[quadIdxCnt*4]
						>> vertexQuadIdx[quadIdxCnt*4 + 1] >> tmp >> uvQuadIdx[quadIdxCnt*4 + 1] >> tmp >> normalQuadIdx[quadIdxCnt*4 + 1]
						>> vertexQuadIdx[quadIdxCnt*4 + 2] >> tmp >> uvQuadIdx[quadIdxCnt*4 + 2] >> tmp >> normalQuadIdx[quadIdxCnt*4 + 2]
						>> vertexQuadIdx[quadIdxCnt*4 + 3] >> tmp >> uvQuadIdx[quadIdxCnt*4 + 3] >> tmp >> normalQuadIdx[quadIdxCnt*4 + 3];

					for (size_t i = 0; i < 4; i++)
					{
						vertexQuadIdx[quadIdxCnt*4 + i]--;
						uvQuadIdx[quadIdxCnt*4 + i]--;
						normalQuadIdx[quadIdxCnt*4 + i]--;
					}
				}
				else if (normal != nullptr)
				{
					s >> tmp >> vertexQuadIdx[quadIdxCnt*4] >> tmp >> uvQuadIdx[quadIdxCnt*4] >> tmp
						>> vertexQuadIdx[quadIdxCnt*4 + 1] >> tmp >> uvQuadIdx[quadIdxCnt*4 + 1] >> tmp
						>> vertexQuadIdx[quadIdxCnt*4 + 2] >> tmp >> uvQuadIdx[quadIdxCnt*4 + 2] >> tmp;

					for (size_t i = 0; i < 4; i++)
					{
						vertexQuadIdx[quadIdxCnt*4 + i]--;
						uvQuadIdx[quadIdxCnt*4 + i]--;
					}
				}
				else if (uv != nullptr)
				{
					s >> tmp >> vertexQuadIdx[quadIdxCnt*4] >> tmp >> normalQuadIdx[quadIdxCnt*4]
						>> vertexQuadIdx[quadIdxCnt*4 + 1] >> tmp >> normalQuadIdx[quadIdxCnt*4 + 1]
						>> vertexQuadIdx[quadIdxCnt*4 + 2] >> tmp >> normalQuadIdx[quadIdxCnt*4 + 2]
						>> vertexQuadIdx[quadIdxCnt*4 + 3] >> tmp >> normalQuadIdx[quadIdxCnt*4 + 3];

					for (size_t i = 0; i < 4; i++)
					{
						vertexQuadIdx[quadIdxCnt*4 + i]--;
						normalQuadIdx[quadIdxCnt*4 + i]--;
					}
				}
				else
				{
					s >> tmp >> vertexTriIdx[quadIdxCnt]
						>> vertexTriIdx[quadIdxCnt + 1]
						>> vertexTriIdx[quadIdxCnt + 2]
						>> vertexTriIdx[quadIdxCnt + 3];
					for (size_t i = 0; i < 4; i++)
					{
						vertexQuadIdx[quadIdxCnt*4 + i]--;
					}
				}
				quadIdxCnt++;
			}
		}
		lineNum++;
	}

	f.close();
	return true;
}