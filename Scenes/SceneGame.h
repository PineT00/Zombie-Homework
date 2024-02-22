#pragma once
#include "Scene.h"

class Player;
class TileMap;
class ZombieSpawner;
class Bullet;
class HealthBar;


class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	TileMap* tileMap = nullptr;
	std::vector<ZombieSpawner*> spawner;

	HealthBar* healthBar = nullptr;

	std::list<Bullet*> usedBulletList;
	std::list<Bullet*> unUsedBulletList;

	int currentBullet;
	int totalBullet;


public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;
	void Init() override;
	void Release() override;

	void Shoot();

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

