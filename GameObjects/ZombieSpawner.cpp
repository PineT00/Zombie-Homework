#include "pch.h"
#include "ZombieSpawner.h"
#include "SceneGame.h"

ZombieSpawner::ZombieSpawner(const std::string& name) : Spawner(name)
{
}


//void ZombieSpawner::Spawn()
//{
//	sf::Vector2f pos = position + Utils::RandomOnUnitCircle() * radius;
//	if (sceneGame != nullptr)
//	{
//		pos = sceneGame->ClampByTileMap(pos);
//	}
//	GameObject* newGo = Create();
//	newGo->Init();
//	newGo->Reset();
//	newGo->SetPosition(pos);
//
//	SCENE_MGR.GetCurrentScene()->AddGo(newGo);
//
//}

GameObject* ZombieSpawner::Create()
{
	Zombie::Types zombieType = zombieTypes[Utils::RandomRange(0, zombieTypes.size())];

	return Zombie::Create(zombieType);
}

void ZombieSpawner::Reset()
{
	Spawner::Reset();

	zombieTypes.clear();
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Crawler);
	zombieTypes.push_back(Zombie::Types::Crawler);
	zombieTypes.push_back(Zombie::Types::Crawler);
	zombieTypes.push_back(Zombie::Types::Crawler);


	interval = 5.f;
	spawnCount = 1;
	radius = 250.f;
	timer = 0.f;
}

void ZombieSpawner::NextWave(int a)
{

	if (a > 2 && a <= 4)
	{
		zombieTypes.clear();
		zombieTypes.push_back(Zombie::Types::Bloater);
		zombieTypes.push_back(Zombie::Types::Chaser);
		zombieTypes.push_back(Zombie::Types::Chaser);
		zombieTypes.push_back(Zombie::Types::Crawler);
		zombieTypes.push_back(Zombie::Types::Crawler);
		zombieTypes.push_back(Zombie::Types::Crawler);
		zombieTypes.push_back(Zombie::Types::Crawler);

	}

	if (a > 4 && a <= 6)
	{
		zombieTypes.clear();
		zombieTypes.push_back(Zombie::Types::Bloater);
		zombieTypes.push_back(Zombie::Types::Chaser);
		zombieTypes.push_back(Zombie::Types::Crawler);
		zombieTypes.push_back(Zombie::Types::Crawler);
		zombieTypes.push_back(Zombie::Types::Crawler);
		zombieTypes.push_back(Zombie::Types::Crawler);
		zombieTypes.push_back(Zombie::Types::Worm);
		zombieTypes.push_back(Zombie::Types::Worm);
	}

	if (a > 6)
	{
		zombieTypes.clear();
		zombieTypes.push_back(Zombie::Types::Bloater);
		zombieTypes.push_back(Zombie::Types::Chaser);
		zombieTypes.push_back(Zombie::Types::Chaser);
		zombieTypes.push_back(Zombie::Types::Crawler);
		zombieTypes.push_back(Zombie::Types::Crawler);
		zombieTypes.push_back(Zombie::Types::Crawler);
		zombieTypes.push_back(Zombie::Types::Crawler);
		zombieTypes.push_back(Zombie::Types::Worm);
		zombieTypes.push_back(Zombie::Types::Worm);
		zombieTypes.push_back(Zombie::Types::Worm);
	}


}
