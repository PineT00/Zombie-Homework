#pragma once
#include "Scene.h"

class Player;
class TileMap;
class ZombieSpawner;
class HealthBar;



class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	TileMap* tileMap = nullptr;
	std::vector<ZombieSpawner*> spawner;

	HealthBar* healthBar = nullptr;


public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;
	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

