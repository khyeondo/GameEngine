#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <list>
#include <vector>
#include <typeinfo>

#include "Transform.h"

class Scene;
class Component;

class GameObject
{	
	friend class Scene;
private:
	static std::list<GameObject*> m_sDestroyList;

	GameObject* m_pParent = nullptr;
	std::list<GameObject*> m_children;
	std::vector<Component*> m_components;

private:
	GameObject();
	~GameObject();

public:
	static GameObject* Instantiate();
	static GameObject* Instantiate(GameObject* pParent);
	static void ClearDestroyList();

	void Start();
	void Update();
	void LateUpdate();
	void Render();
	void RenderUI();
	void OnDestroy();

	void Destroy();

	GameObject* AddChild(GameObject* pGameObject);
	GameObject* AddChildren(int num, GameObject* ...);	

	Transform* GetTransform();
    
	template<class T>
	T* GetComponent() 
	{
		for (Component* pComponent : m_components)
		{
			T* tmp = dynamic_cast<T*>(pComponent);
			if (tmp != nullptr) {				
				return tmp;
			}
		}
		return nullptr;
	}

	template<class T>
	T* AddComponent() {
		Component* pComponent = new T();
		m_components.push_back(pComponent);
		pComponent->m_pGameObject = this;

		return (T*)pComponent;
	}
};

#endif // !_GAME_OBJECT_H


