#include "../header/Scene.h"
#include "../header/GameObject.h"
#include "../header/RenderTool.h"

Scene::~Scene()
{
	for (GameObject* pGameObject : m_pGameObjects)
	{
		delete pGameObject;
	}
	m_pGameObjects.clear();
}

void Scene::Start()
{
	for (GameObject* pGameObject : m_pGameObjects)
	{
		pGameObject->Start();
	}
}

void Scene::Update()
{
	for (GameObject* pGameObject : m_pGameObjects)
	{
		pGameObject->Update();
	}
}

void Scene::LateUpdate()
{
	for (GameObject* pGameObject : m_pGameObjects)
	{
		pGameObject->LateUpdate();
	}
}

void Scene::Render()
{
	RenderTool::Instance()->StartRender();
	RenderTool::Instance()->PushMatrix();
	RenderTool::Instance()->WorldToView();
	for (GameObject* pGameObject : m_pGameObjects)
	{
		RenderTool::Instance()->PushMatrix();
		RenderTool::Instance()->LocalToWorld(*(pGameObject->GetTransform()));		
		pGameObject->Render();
		RenderTool::Instance()->PopMatrix();
	}	
	RenderTool::Instance()->PopMatrix();
}

void Scene::RenderUI()
{
	RenderTool::Instance()->StartRenderUI();
	for (GameObject* pGameObject : m_pGameObjects)
	{
		pGameObject->RenderUI();
	}
	RenderTool::Instance()->EndRender();
}

void Scene::OnDestroy()
{
	for (GameObject* pGameObject : m_pGameObjects)
	{
		pGameObject->OnDestroy();
		delete pGameObject;
	}
	m_pGameObjects.clear();
}

void Scene::AddGameObject(GameObject* pGameObject)
{
	m_pGameObjects.push_back(pGameObject);
	//pGameObject->m_iter = m_pGameObjects.end();
}

void Scene::EraseGameObject(GameObject* pGameObject)
{
	std::list<GameObject*>::iterator iter;
	std::list<GameObject*>::iterator iterEnd = m_pGameObjects.end();

	for (iter = m_pGameObjects.begin();
		iter != iterEnd;
		iter++)
	{
		if (*iter == pGameObject)
		{
			m_pGameObjects.erase(iter);
			return;
		}
	}
}
