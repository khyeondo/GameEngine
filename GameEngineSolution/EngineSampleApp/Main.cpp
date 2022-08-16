
#include "EngineCore.h"
#include "EngineSetup.h"
#include "InputManager.h"
#include "SampleScene.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//엔진 초기 셋팅 값을 입력하는 구조체입니다.
	EngineSetup setup(
		1600, 900,			//초기 화면 크기
		L"EngineSampleApp",	//타이틀 바
		OpenGL,				//렌더링 툴(현재는 OpenGL만 사용 가능합니다)
		144.0,				//렌더 프레임
		START_SCENE(SampleScene) //시작 씬
	);

	//InputManager에 키를 등록하여 사용할 수 있습니다.
	InputManager::Instance()->AddKey("left", 'a');
	InputManager::Instance()->AddKey("right", 'd');
	InputManager::Instance()->AddKey("up", 'w');
	InputManager::Instance()->AddKey("down", 's');
	InputManager::Instance()->AddKey("esc", VK_ESCAPE);

	if (!EngineCore::Instance()->Init(hInstance, setup)) {
		EngineCore::DestroySingle();
		return 0;
	}

	EngineCore::Instance()->Run();

	EngineCore::DestroySingle();
}