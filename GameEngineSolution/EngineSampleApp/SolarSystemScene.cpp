
#include "SolarSystemScene.h"

#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "ImageRenderer.h"
#include "Camera.h"
#include "SkyBox.h"
#include "CameraController.h"
#include "ResourceManager.h"
#include "Rotator.h"
#include "Texture.h"
#include "Mesh.h"

void SolarSystemScene::SetHierarchy()
{
	ResourceMgr<Texture>::Instance()->Clear();

	ResourceMgr<Texture>::Instance()->Load(L"Assets/GL.jpg", "logo");
	
	ResourceMgr<Texture>::Instance()->Load(L"Assets/sun.jpg", "sun");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/mercury.jpg", "mercury");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/venus.jpg", "venus");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/earth.jpg", "earth");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/moon.jpg", "moon");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/mars.jpg", "mars");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/jupiter.jpg", "jupiter");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/saturn.jpg", "saturn");

	ResourceMgr<Texture>::Instance()->Load(L"Assets/Skybox_Space/back.png", "back");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/Skybox_Space/bottom.png", "bottom");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/Skybox_Space/front.png", "front");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/Skybox_Space/left.png", "left");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/Skybox_Space/right.png", "right");
	ResourceMgr<Texture>::Instance()->Load(L"Assets/Skybox_Space/top.png", "top");

	ResourceMgr<Mesh>::Instance()->Load(L"Assets/sphere.obj","sphere");
			
	GameObject* pSunOrbit		= GameObject::Instantiate();
	GameObject* pMercuryOrbit	= GameObject::Instantiate();
	GameObject* pVenusOrbit		= GameObject::Instantiate();
	GameObject* pEarthOrbit		= GameObject::Instantiate();
	GameObject* pMoonOrbit		= GameObject::Instantiate();
	GameObject* pMarthOrbit		= GameObject::Instantiate();
	GameObject* pJupiterOrbit	= GameObject::Instantiate();
	GameObject* pSaturnOrbit = GameObject::Instantiate();

	pSunOrbit->AddComponent<Rotator>()->SetSpeed(0.f);
	pMercuryOrbit->AddComponent<Rotator>()->SetSpeed(20.f);
	pEarthOrbit->AddComponent<Rotator>()->SetSpeed(13.f);
	pVenusOrbit->AddComponent<Rotator>()->SetSpeed(15.f);
	pMoonOrbit->AddComponent<Rotator>()->SetSpeed(20.f);
	pMarthOrbit->AddComponent<Rotator>()->SetSpeed(10.f);
	pJupiterOrbit->AddComponent<Rotator>()->SetSpeed(4.f);
	pSaturnOrbit->AddComponent<Rotator>()->SetSpeed(3.f);

	pSunOrbit->AddChildren(5,
		pMercuryOrbit,
		pVenusOrbit,
		pEarthOrbit,
		pMarthOrbit,
		pJupiterOrbit,
		pSaturnOrbit
	);

	std::map<std::string, GameObject*> solarSystem;
	solarSystem["sun"]		= GameObject::Instantiate(pSunOrbit);
	solarSystem["mercury"]	= GameObject::Instantiate(pMercuryOrbit);
	solarSystem["venus"]	= GameObject::Instantiate(pVenusOrbit);
	solarSystem["earth"]	= GameObject::Instantiate(pEarthOrbit);
	solarSystem["moon"]		= GameObject::Instantiate(pMoonOrbit);
	solarSystem["mars"]		= GameObject::Instantiate(pMarthOrbit);
	solarSystem["jupiter"]	 = GameObject::Instantiate(pJupiterOrbit);
	solarSystem["saturn"] = GameObject::Instantiate(pSaturnOrbit);

	solarSystem["earth"]->AddChild(pMoonOrbit);

	std::map<std::string, float> radius;
	radius["sun"]		= 0.f;
	radius["mercury"]	= 4.f;
	radius["venus"]		= 6.f;
	radius["earth"]		= 8.f;
	radius["moon"]		= 3.f;
	radius["mars"]		= 10.f;
	radius["jupiter"]	= 14.f;
	radius["saturn"] = 17.f;
	
	std::map<std::string, float> scale;
	scale["sun"]		= 2.0f;
	scale["mercury"]	= 0.1f;
	scale["venus"]		= 0.2f;
	scale["earth"]		= 0.25f;
	scale["moon"]		= 0.2f;
	scale["mars"]		= 0.2f;
	scale["jupiter"]	= 0.5f;
	scale["saturn"]		= 0.4f;

	for (auto planet : solarSystem)
	{
		planet.second->AddComponent<Rotator>();		
		MeshRenderer* pMeshRenderer = planet.second->AddComponent<MeshRenderer>();
		pMeshRenderer->SetMesh(ResourceMgr<Mesh>::Instance()->GetResource("sphere"));
		pMeshRenderer->SetTexture(ResourceMgr<Texture>::Instance()->GetResource(planet.first.c_str()));
		planet.second->GetTransform()->SetPosition(Vec3f(radius[planet.first], 0.f, 0.f));
		solarSystem[planet.first]->GetTransform()->SetScale(Vec3f::Identity() * scale[planet.first]);
	}
	
#pragma region Init pCameraObj
	GameObject* pCameraObj = GameObject::Instantiate();
	pCameraObj->AddComponent<Camera>();
	pCameraObj->AddComponent<CameraController>();

	Camera* pCamera = pCameraObj->GetComponent<Camera>();
	pCamera->SetFar(1000.0f);
	pCamera->SetNear(0.1f);
	pCamera->SetFov(90.f);
#pragma endregion

#pragma region Init pSkyBoxObj
	GameObject* pSkyBoxObj = GameObject::Instantiate();
	SkyBox* pSkybox = pSkyBoxObj->AddComponent<SkyBox>();
	pSkybox->SetTexture(SideOfSkyBox::TOP, ResourceMgr<Texture>::Instance()->GetResource("top"));
	pSkybox->SetTexture(SideOfSkyBox::BOTTOM, ResourceMgr<Texture>::Instance()->GetResource("bottom"));
	pSkybox->SetTexture(SideOfSkyBox::LEFT, ResourceMgr<Texture>::Instance()->GetResource("left"));
	pSkybox->SetTexture(SideOfSkyBox::RIGHT, ResourceMgr<Texture>::Instance()->GetResource("right"));
	pSkybox->SetTexture(SideOfSkyBox::FRONT, ResourceMgr<Texture>::Instance()->GetResource("front"));
	pSkybox->SetTexture(SideOfSkyBox::BACK, ResourceMgr<Texture>::Instance()->GetResource("back"));
#pragma endregion

	GameObject* pGlLogo = GameObject::Instantiate();
	ImageRenderer* pImageRenderer = pGlLogo->AddComponent<ImageRenderer>();
	pImageRenderer->SetTexture(ResourceMgr<Texture>::Instance()->GetResource("logo"));
	pImageRenderer->SetPivot(Vec2f(1, 1));
	pImageRenderer->SetAnchor(Anchor::RIGHT | Anchor::TOP);
	pGlLogo->GetTransform()->SetPosition(Vec3f(-20, -20, 0));
}