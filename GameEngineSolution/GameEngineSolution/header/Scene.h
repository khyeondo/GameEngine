#ifndef _SCENE_H_
#define _SCENE_H_

#include <list>

class GameObject;

class Scene
{
	friend class SceneManager;
private:
	std::list<GameObject*> m_pGameObjects;

protected:
	Scene() {}
	virtual ~Scene();

public:

	virtual void SetHierarchy() = 0;

	void Start();
	void Update();
	void LateUpdate();
	void Render();
	void RenderUI();
	void OnDestroy();

	void AddGameObject(GameObject* pGameObject);
	void EraseGameObject(GameObject* pGameObject);
};

#endif // !_SCENE_H_