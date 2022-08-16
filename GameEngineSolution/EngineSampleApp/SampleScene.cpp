#include "SampleScene.h"

#include "ResourceManager.h"
#include "Texture.h"
#include "Mesh.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "SkyBox.h"
#include "ImageRenderer.h"

#include "Rotator.h"
#include "CameraController.h"
#include "ToNextScene.h"

void SampleScene::SetHierarchy()
{
	//ResourceManager클래스를 통해 Mesh와 Texture를 로드할 수 있습니다.	
	//texture는 jpg,png,bmp등의 확장자를 로드할 수 있고,
	ResourceMgr<Texture>::Instance()->Load(L"Assets/sword.bmp", "sword");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/tip.png", "tip");
	//mesh는 .obj파일을 로드할 수 있습니다.
	ResourceMgr<Mesh>::Instance()->Load(L"Assets/sword.obj", "sword");
	ResourceMgr<Mesh>::Instance()->Load(L"Assets/axis.obj", "axis");

	ResourceMgr<Texture>::Instance()->Load(L"Assets/skybox/back.jpg", "back");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/skybox/bottom.jpg", "bottom");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/skybox/front.jpg", "front");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/skybox/left.jpg", "left");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/skybox/right.jpg", "right");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/skybox/top.jpg", "top");

	//Instantiate()함수를 통해 게임오브젝트를 생성할 수 있고 생성된 오브젝트는 Scene에 바로 배치됩니다.
	//또는 오버로딩된 함수 Instantiate(GameObject* pParent)를 이용하여 바로 부모 오브젝트를 설정할 수도 있습니다.
	GameObject* pSword = GameObject::Instantiate();

	//AddComponent()함수로 엔진에서 지원하는 Component 혹은 사용자가 재정의한 Component를 오브젝트에 추가할 수 있습니다.
	MeshRenderer* pMeshRenderer = pSword->AddComponent<MeshRenderer>();
	pMeshRenderer->SetMesh(ResourceMgr<Mesh>::Instance()->GetResource("sword"));
	pMeshRenderer->SetTexture(ResourceMgr<Texture>::Instance()->GetResource("sword"));


	GameObject* pCamera = GameObject::Instantiate();
	pCamera->AddComponent<CameraController>();
	//각 Scene에는 Camera Component를 갖는 오브젝트가 반드시 1개 존재해야 합니다.
	Camera* pCameraComponent = pCamera->AddComponent<Camera>();
	pCameraComponent->SetFar(1000.0f);
	pCameraComponent->SetNear(0.1f);
	pCameraComponent->SetFov(45.f);

	GameObject* pSkyBox = GameObject::Instantiate();
	//SkyBox기능을 하는 Component입니다.
	SkyBox* pSkyBoxComponent = pSkyBox->AddComponent<SkyBox>();
	//각 면에 해당하는 texture를 지정할 수 있습니다.
	pSkyBoxComponent->SetTexture(SideOfSkyBox::BACK, ResourceMgr<Texture>::Instance()->GetResource("back"));
	pSkyBoxComponent->SetTexture(SideOfSkyBox::BOTTOM, ResourceMgr<Texture>::Instance()->GetResource("bottom"));
	pSkyBoxComponent->SetTexture(SideOfSkyBox::FRONT, ResourceMgr<Texture>::Instance()->GetResource("front"));
	pSkyBoxComponent->SetTexture(SideOfSkyBox::LEFT, ResourceMgr<Texture>::Instance()->GetResource("left"));
	pSkyBoxComponent->SetTexture(SideOfSkyBox::RIGHT, ResourceMgr<Texture>::Instance()->GetResource("right"));
	pSkyBoxComponent->SetTexture(SideOfSkyBox::TOP, ResourceMgr<Texture>::Instance()->GetResource("top"));

	GameObject* axis1 = GameObject::Instantiate();
	GameObject* axis2 = GameObject::Instantiate();
	GameObject* axis3 = GameObject::Instantiate();
	GameObject* axis4 = GameObject::Instantiate();
	GameObject* axis5 = GameObject::Instantiate();
	GameObject* axis6 = GameObject::Instantiate();

	axis1->AddComponent<Rotator>();
	axis2->AddComponent<Rotator>()->SetSpeed(-20.f);
	axis3->AddComponent<Rotator>()->SetSpeed(20.f);
	axis4->AddComponent<Rotator>();
	axis5->AddComponent<Rotator>()->SetSpeed(-10.f);
	axis6->AddComponent<Rotator>();

	pMeshRenderer = axis1->AddComponent<MeshRenderer>();
	pMeshRenderer->SetMesh(ResourceMgr<Mesh>::Instance()->GetResource("axis"));
	pMeshRenderer = axis2->AddComponent<MeshRenderer>();
	pMeshRenderer->SetMesh(ResourceMgr<Mesh>::Instance()->GetResource("axis"));
	pMeshRenderer = axis3->AddComponent<MeshRenderer>();
	pMeshRenderer->SetMesh(ResourceMgr<Mesh>::Instance()->GetResource("axis"));
	pMeshRenderer = axis4->AddComponent<MeshRenderer>();
	pMeshRenderer->SetMesh(ResourceMgr<Mesh>::Instance()->GetResource("axis"));
	pMeshRenderer = axis5->AddComponent<MeshRenderer>();
	pMeshRenderer->SetMesh(ResourceMgr<Mesh>::Instance()->GetResource("axis"));
	pMeshRenderer = axis6->AddComponent<MeshRenderer>();
	pMeshRenderer->SetMesh(ResourceMgr<Mesh>::Instance()->GetResource("axis"));


	//AddChildren함수로 다수 계층을 한번에 설정할 수 있습니다.
	axis1->AddChildren(2,
		axis2->AddChildren(3,
			axis4,
			axis5,
			axis6
			),
		axis3
	);

	axis1->GetTransform()->SetPosition(Vec3f(0, 30, 0));
	axis2->GetTransform()->SetScale(Vec3f(0.5, 0.5, 0.5));

	axis2->GetTransform()->SetPosition(Vec3f(10, 0, 0));
	axis2->GetTransform()->SetRotation(Vec3f(80, 50, 40));
	axis2->GetTransform()->SetScale(Vec3f(0.5, 0.5, 0.5));

	axis3->GetTransform()->SetPosition(Vec3f(10, 20, 0));
	
	axis4->GetTransform()->SetPosition(Vec3f(0, 40, 0));

	axis5->GetTransform()->SetPosition(Vec3f(10, 20, 0));
	axis5->GetTransform()->SetRotation(Vec3f(10, 40, 0));
	axis5->GetTransform()->SetScale(Vec3f(0.4, 0.4, 0.4));

	axis6->GetTransform()->SetPosition(Vec3f(0, 0, -50));

	GameObject* pTip = GameObject::Instantiate();
	pTip->AddComponent<ToNextScene>();

	//2D이미지 출력을 위한 Component입니다.
	ImageRenderer* pImageRenderer = pTip->AddComponent<ImageRenderer>();
	pImageRenderer->SetTexture(ResourceMgr<Texture>::Instance()->GetResource("tip"));
	//Pivot을 설정할 수 있습니다.
	pImageRenderer->SetPivot(Vec2f(0, 1));
	//SetAnchor로 엥커를 설정합니다. 인자로 열겨형 Anchor의 or연산자 결과값이 들어갑니다.
	pImageRenderer->SetAnchor(Anchor::LEFT | Anchor::TOP);
	//출력될 이미지 크기를 설정합니다.
	//별도로 설정하지 않는다면 원본 이미지 크기로 출력됩니다.
	pImageRenderer->SetWidth(350);
	pImageRenderer->SetHeight(250);

}