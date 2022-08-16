#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "Singleton.h"

class Scene;

class SceneManager
{
	SINGLETON_H(SceneManager)

private:
	Scene* m_pCurScene = nullptr;
	Scene* m_pNextScene = nullptr;
	double m_renderTimer;

private:
	SceneManager();
	~SceneManager();
	
public:
	void Update();	
	
	template<class T>
	void LoadScene() 
	{
		m_pNextScene = new T();
	}

	Scene* GetCurrentScene();
};

typedef SceneManager SceneMgr;
#endif // !_SCENE_MANAGER_+