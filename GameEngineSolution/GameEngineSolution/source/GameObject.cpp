#include <stdarg.h>

#include "../header/GameObject.h"
#include "../header/SceneManager.h"
#include "../header/Scene.h"
#include "../header/RenderTool.h"

std::list<GameObject*> GameObject::m_sDestroyList;

GameObject::GameObject()
{
	m_components.push_back(new Transform());
}

GameObject::~GameObject()
{
	for (Component* pComponent : m_components)
	{
		delete pComponent;
	}
	m_components.clear();

	for (GameObject* pGameObject : m_children)
	{
		delete pGameObject;
	}
	m_children.clear();
}

GameObject* GameObject::Instantiate()
{
	GameObject* pGameOject =  new GameObject();
	SceneMgr::Instance()->GetCurrentScene()->AddGameObject(pGameOject);
	return pGameOject;
}

GameObject* GameObject::Instantiate(GameObject* pParent)
{
	GameObject* pGameObject = new GameObject();
	pParent->AddChild(pGameObject);

	return pGameObject;
}

void GameObject::ClearDestroyList()
{
	std::list<GameObject*>::iterator iter;
	std::list<GameObject*>::iterator iterEnd;
	for (GameObject* pGameObject : m_sDestroyList)
	{
		if (pGameObject->m_pParent == nullptr)
		{
			SceneMgr::Instance()->GetCurrentScene()->EraseGameObject(pGameObject);
		}
		else
		{	
			
			iterEnd = pGameObject->m_pParent->m_children.end();
			for (iter = pGameObject->m_pParent->m_children.begin(); 
				iter != iterEnd;
				iter++)
			{
				pGameObject->m_pParent->m_children.erase(iter);
				break;
			}
		}
		pGameObject->OnDestroy();
		delete pGameObject;
	}
}

void GameObject::Destroy()
{
	m_sDestroyList.push_back(this);
}

GameObject* GameObject::AddChild(GameObject* pGameObject)
{
	if (pGameObject->m_pParent == nullptr)
	{
		pGameObject->m_pParent = this;
		SceneMgr::Instance()->GetCurrentScene()->EraseGameObject(pGameObject);
		m_children.push_back(pGameObject);
		//pGameObject->m_iter = m_children.end();
	}

	return this;
}

GameObject* GameObject::AddChildren(int num, GameObject* ...)
{
	va_list list;
	va_start(list, num);

	GameObject* pGameObject;
	for (size_t i = 0; i < num; i++)
	{
		pGameObject = va_arg(list, GameObject*);
		if (pGameObject != nullptr)
		{
			if (pGameObject->m_pParent == nullptr)
			{
				pGameObject->m_pParent = this;
				SceneMgr::Instance()->GetCurrentScene()->EraseGameObject(pGameObject);
				m_children.push_back(pGameObject);
				//pGameObject->m_iter = m_children.end();
			}
		}
	}

	return this;
}

Transform* GameObject::GetTransform()
{
	return (Transform*)m_components.at(0);
}

void GameObject::Start()
{
	for (Component* pComponent : m_components)
	{
		pComponent->Start();
	}
	for (GameObject* pGameObject : m_children)
	{
		pGameObject->Start();
	}
}

void GameObject::Update()
{	
	for (Component* pComponent : m_components)
	{
		pComponent->Update();
	}
	for (GameObject* pGameObject : m_children)
	{
		pGameObject->Update();
	}
}

void GameObject::LateUpdate()
{
	for (Component* pComponent : m_components)
	{
		pComponent->LateUpdate();
	}
	for (GameObject* pGameObject : m_children)
	{
		pGameObject->LateUpdate();
	}
}

void GameObject::Render() 
{
	for (Component* pComponent : m_components)
	{
		pComponent->Render();
	}

	for (GameObject* pGameObject : m_children)
	{
		RenderTool::Instance()->PushMatrix();
		RenderTool::Instance()->LocalToWorld(*(pGameObject->GetTransform()));				
		pGameObject->Render();				
		RenderTool::Instance()->PopMatrix();
	}
}

void GameObject::RenderUI()
{
	for (Component* pComponent : m_components)
	{
		pComponent->RenderUI();
	}
	for (GameObject* pGameObject : m_children)
	{
		pGameObject->RenderUI();
	}
}

void GameObject::OnDestroy()
{
	for (Component* pComponent : m_components)
	{		
		pComponent->OnDestroy();
		delete pComponent;
	}
	m_components.clear();

	for (GameObject* pGameObject : m_children)
	{
		pGameObject->OnDestroy();
		delete pGameObject;
	}
	m_children.clear();
}