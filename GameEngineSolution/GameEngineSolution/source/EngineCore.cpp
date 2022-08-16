#include <iostream>

#include "../header/EngineCore.h"
#include "../header/SceneManager.h"
#include "../header/RenderTool.h"
#include "../header/GLRenderTool.h"
#include "../header/ResourceManager.h"
#include "../header/InputManager.h"
#include "../header/EngineTime.h"

SINGLETON_CPP(EngineCore)

EngineCore::~EngineCore()
{	
	WindowMgr::DestroySingle();
	InputMgr::DestroySingle();
	RenderTool::DestroySingle();
	SceneMgr::DestroySingle();
	Time::DestroySingle();
}

bool EngineCore::Init(HINSTANCE hInstance, const EngineSetup& setup)
{	
	if (!WindowMgr::Instance()->Init(
		hInstance,
		setup.windowWidth, setup.windowHeight,
		setup.title)) {

		std::cout << "윈도우 생성 실패" << std::endl;
		return false;
	}

	switch (setup.renderSDK)
	{
	case OpenGL:
		RenderTool::CreateRenderTool<GLRenderTool>();
		break;
	}
	
	if (!RenderTool::Instance()->Init(WindowMgr::Instance()->GetHDC())) {
		std::cout << "fail to init RenderTool" << std::endl;
		return false;
	}

	ShowWindow(WindowMgr::Instance()->GetHWND(),SW_SHOW);
	UpdateWindow(WindowMgr::Instance()->GetHWND());

	return true;
}

void EngineCore::Run()
{
	MSG msg;

	while (m_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Time::Instance()->Update();
			SceneMgr::Instance()->Update();
		}
	}
}

void EngineCore::EndLoop()
{
	m_bLoop = false;
}
