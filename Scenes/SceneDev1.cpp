#include "pch.h"
#include "SceneDev1.h"
#include "rapidcsv.h"
#include "ZombieTable.h"

SceneDev1::SceneDev1(SceneIds id) : Scene(id)
{
}

SceneDev1::~SceneDev1()
{
}

void SceneDev1::Init()
{
	
}

void SceneDev1::Release()
{
	Scene::Release();
}

void SceneDev1::Enter()
{
	Scene::Enter();

	std::cout << ZOMBIE_TABLE->Get(Zombie::Types::Bloater).nameId << std::endl;


}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		STRING_TABLE->Load(Languages::Korean);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		STRING_TABLE->Load(Languages::English);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		std::cout << STRING_TABLE->Get("HI") << std::endl;
	}
}
