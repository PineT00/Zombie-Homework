#pragma once
#include "Spawner.h"
#include "Zombie.h"

class SceneGame;

class ZombieSpawner : public Spawner
{
protected:
	std::vector<Zombie::Types> zombieTypes;

public:
	SceneGame* sceneGame = nullptr;

	ZombieSpawner(const std::string& name = "");
	~ZombieSpawner() override = default;

	//void Spawn() override;

	GameObject* Create() override;

	void Reset() override;

	void NextWave(int wave);
};