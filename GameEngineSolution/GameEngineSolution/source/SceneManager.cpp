#include "../header/SceneManager.h"
#include "../header/WindowManager.h"
#include "../header/InputManager.h"
#include "../header/Scene.h"
#include "../header/EngineTime.h"
#include "../header/GameObject.h"

#include <iostream>

SINGLETON_CPP(SceneManager)

SceneManager::SceneManager()
{
	m_renderTimer = 1.f / 60.f;
}

SceneManager::~SceneManager()
{
	delete m_pCurScene;
}

void SceneManager::Update()
{	
	m_renderTimer -= Time::Instance()->GetDeltaTime();
	GameObject::ClearDestroyList();

	if (m_pNextScene != nullptr)
	{
		if(m_pCurScene != nullptr) m_pCurScene->OnDestroy();
		delete m_pCurScene;
		m_pCurScene = m_pNextScene;

		m_pCurScene->SetHierarchy();
		m_pCurScene->Start();
		m_pNextScene = nullptr;
	}
		
	InputManager::Instance()->Update();
	m_pCurScene->Update();
	m_pCurScene->LateUpdate();

	if (m_renderTimer <= 0.f)
	{
		m_renderTimer += 1.f / Time::Instance()->GetRenderFrame();
		m_pCurScene->Render();
		m_pCurScene->RenderUI();
	}
}

Scene* SceneManager::GetCurrentScene()
{
	return m_pCurScene;
}