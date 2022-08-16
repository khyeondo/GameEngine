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
	//ResourceManagerŬ������ ���� Mesh�� Texture�� �ε��� �� �ֽ��ϴ�.	
	//texture�� jpg,png,bmp���� Ȯ���ڸ� �ε��� �� �ְ�,
	ResourceMgr<Texture>::Instance()->Load(L"Assets/sword.bmp", "sword");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/tip.png", "tip");
	//mesh�� .obj������ �ε��� �� �ֽ��ϴ�.
	ResourceMgr<Mesh>::Instance()->Load(L"Assets/sword.obj", "sword");
	ResourceMgr<Mesh>::Instance()->Load(L"Assets/axis.obj", "axis");

	ResourceMgr<Texture>::Instance()->Load(L"Assets/skybox/back.jpg", "back");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/skybox/bottom.jpg", "bottom");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/skybox/front.jpg", "front");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/skybox/left.jpg", "left");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/skybox/right.jpg", "right");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/skybox/top.jpg", "top");

	//Instantiate()�Լ��� ���� ���ӿ�����Ʈ�� ������ �� �ְ� ������ ������Ʈ�� Scene�� �ٷ� ��ġ�˴ϴ�.
	//�Ǵ� �����ε��� �Լ� Instantiate(GameObject* pParent)�� �̿��Ͽ� �ٷ� �θ� ������Ʈ�� ������ ���� �ֽ��ϴ�.
	GameObject* pSword = GameObject::Instantiate();

	//AddComponent()�Լ��� �������� �����ϴ� Component Ȥ�� ����ڰ� �������� Component�� ������Ʈ�� �߰��� �� �ֽ��ϴ�.
	MeshRenderer* pMeshRenderer = pSword->AddComponent<MeshRenderer>();
	pMeshRenderer->SetMesh(ResourceMgr<Mesh>::Instance()->GetResource("sword"));
	pMeshRenderer->SetTexture(ResourceMgr<Texture>::Instance()->GetResource("sword"));


	GameObject* pCamera = GameObject::Instantiate();
	pCamera->AddComponent<CameraController>();
	//�� Scene���� Camera Component�� ���� ������Ʈ�� �ݵ�� 1�� �����ؾ� �մϴ�.
	Camera* pCameraComponent = pCamera->AddComponent<Camera>();
	pCameraComponent->SetFar(1000.0f);
	pCameraComponent->SetNear(0.1f);
	pCameraComponent->SetFov(45.f);

	GameObject* pSkyBox = GameObject::Instantiate();
	//SkyBox����� �ϴ� Component�Դϴ�.
	SkyBox* pSkyBoxComponent = pSkyBox->AddComponent<SkyBox>();
	//�� �鿡 �ش��ϴ� texture�� ������ �� �ֽ��ϴ�.
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


	//AddChildren�Լ��� �ټ� ������ �ѹ��� ������ �� �ֽ��ϴ�.
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

	//2D�̹��� ����� ���� Component�Դϴ�.
	ImageRenderer* pImageRenderer = pTip->AddComponent<ImageRenderer>();
	pImageRenderer->SetTexture(ResourceMgr<Texture>::Instance()->GetResource("tip"));
	//Pivot�� ������ �� �ֽ��ϴ�.
	pImageRenderer->SetPivot(Vec2f(0, 1));
	//SetAnchor�� ��Ŀ�� �����մϴ�. ���ڷ� ������ Anchor�� or������ ������� ���ϴ�.
	pImageRenderer->SetAnchor(Anchor::LEFT | Anchor::TOP);
	//��µ� �̹��� ũ�⸦ �����մϴ�.
	//������ �������� �ʴ´ٸ� ���� �̹��� ũ��� ��µ˴ϴ�.
	pImageRenderer->SetWidth(350);
	pImageRenderer->SetHeight(250);

}