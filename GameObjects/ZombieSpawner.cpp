#include "pch.h"
#include "ZombieSpawner.h"
#include "SceneGame.h"

ZombieSpawner::ZombieSpawner(const std::string& name)
	: Spawner(name)
{
}

GameObject* ZombieSpawner::Create()
{
	Zombie::Types zombieType = zombieTypes[Utils::RandomRange(0, zombieTypes.size())];
	return Zombie::Create(zombieType);
}

void ZombieSpawner::Reset()
{
	Spawner::Reset();

	zombieTypes.clear();
	zombieTypes.push_back(Zombie::Types::Bloater);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Crawler);
	zombieTypes.push_back(Zombie::Types::Crawler);
	zombieTypes.push_back(Zombie::Types::Crawler);

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
}

void ZombieSpawner::WaveStart()
{
	for (int i = 0; i < spawnCount; ++i)
	{
		timer = 0.f;
		sf::Vector2f pos = position + Utils::RandomInUnitCircle() * radius;

		if (sceneGame != nullptr)
		{
			pos = sceneGame->ClampByTileMap(pos);
		}
		GameObject* newGo = Create();
		newGo->Init();
		newGo->Reset();
		newGo->SetPosition(pos);
		SCENE_MGR.GetCurrentScene()->AddGo(newGo);
	}
}

void ZombieSpawner::Update(float dt)
{	
	if (sceneGame->isWaveCleared)
	{
		WaveStart();
		sceneGame->isWaveCleared = false;
	}
}
