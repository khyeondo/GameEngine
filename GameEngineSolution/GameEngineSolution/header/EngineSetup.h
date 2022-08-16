#ifndef _ENGINE_SETUP_H_
#define _ENGINE_SETUP_H_

#include <string>
#include "SceneManager.h"
#include "EngineTime.h"

#define START_SCENE(SceneType) SetStartScene<SceneType>

template<class T>
void SetStartScene()
{
	SceneManager::Instance()->LoadScene<T>();
}

enum RenderSDK
{
	OpenGL,
};

class EngineSetup
{
	friend class EngineCore;
public:
	EngineSetup(unsigned int windowWidght,int windowHeight,
		std::wstring title,		
		RenderSDK renderSDK,
		double renderFrame,
		void(*startScene)())
	{
		this->windowHeight = windowHeight;
		this->windowWidth = windowWidght;		
		this->title = title;
		//wcscpy_s(this->title, sizeof(this->title), title);
		this->renderSDK = renderSDK;
		Time::Instance()->SetRenderFrame(renderFrame);
		startScene();
	}

private:
	int windowHeight;
	int windowWidth;
	RenderSDK renderSDK;
	std::wstring title;

};

#endif
