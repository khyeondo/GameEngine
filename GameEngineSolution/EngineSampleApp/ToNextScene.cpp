#include "ToNextScene.h"
#include "InputManager.h"
#include "SolarSystemScene.h"
#include "SceneManager.h"

ToNextScene::ToNextScene() {}
ToNextScene::~ToNextScene() {}

void ToNextScene::Update()
{
	if (InputMgr::Instance()->GetKeyDown('X'))
	{
		//LoadScene함수로 다른 Scene을 로드할 수 있습니다.
		SceneMgr::Instance()->LoadScene<SolarSystemScene>();
	}
}