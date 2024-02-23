#pragma once
#include "Scene.h"

class SpriteGo;
class TextGo;
class Player;
class TileMap;
class Zombie;
class ZombieSpawner;
class TileMap;
class Bullet;
class HealthBar;



class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	TileMap* tileMap = nullptr;

	enum class Status
	{
		Awake,
		Game,
		GameOver,
		Pause,
	};
	Status currStatus;

	std::vector<ZombieSpawner*> spawner;
	std::list<GameObject*> zombieList;

	TextGo* uiStates = nullptr;
	TextGo* uiZombieNum = nullptr;
	HealthBar* healthBar = nullptr;
	SpriteGo* title = nullptr;

	std::list<Bullet*> usedBulletList;
	std::list<Bullet*> unUsedBulletList;

	int currentBullet;
	int totalBullet;


public:

	SceneGame(SceneIds id);
	~SceneGame() override = default;

	const std::list<GameObject*>& GetZombieList() const { return zombieList; }

	bool IsInTileMap(const sf::Vector2f& point);

	void SetStatus(Status newStatus);
	Status GetStatus() const { return currStatus; }

	sf::Vector2f ClampByTileMap(const sf::Vector2f& point);

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateGameOver(float dt);
	void UpdatePause(float dt);
	void Draw(sf::RenderWindow& window) override;
};

