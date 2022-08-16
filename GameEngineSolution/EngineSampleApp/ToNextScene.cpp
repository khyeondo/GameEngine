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
		//LoadScene�Լ��� �ٸ� Scene�� �ε��� �� �ֽ��ϴ�.
		SceneMgr::Instance()->LoadScene<SolarSystemScene>();
	}
}