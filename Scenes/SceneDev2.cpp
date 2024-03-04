#include "pch.h"
#include "SceneDev2.h"
#include "rapidcsv.h"
#include "ZombieTable.h"

SceneDev2::SceneDev2(SceneIds id) : Scene(id)
{
}

SceneDev2::~SceneDev2()
{
}

void SceneDev2::Init()
{
}

void SceneDev2::Release()
{
	Scene::Release();
}

void SceneDev2::Enter()
{
	Scene::Enter();

	std::cout << ZOMBIE_TABLE->Get(Zombie::Types::Bloater).nameId << std::endl;
}

void SceneDev2::Exit()
{
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SceneDev1);
	}

	// 한국어 <-> 영어 테스트 코드
	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		std::cout << STRING_TABLE->Get("HI") << std::endl;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		STRING_TABLE->Load(Languages::Korean);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		STRING_TABLE->Load(Languages::English);
	}
}
