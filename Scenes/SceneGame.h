#pragma once
#include "Scene.h"

class SpriteGo;
class TextGo;
class Player;
class TileMap;
class Zombie;
class ZombieSpawner;
class ItemSpawner;
class TileMap;
class Bullet;
class HealthBar;
class UiHUD;


class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	TileMap* tileMap = nullptr;
	UiHUD* hud;

	enum class Status
	{
		Awake,
		Game,
		GameOver,
		Pause,
	};
	Status currStatus;

	std::vector<ZombieSpawner*> zombieSpawner;
	std::list<GameObject*> zombieList;

	std::vector<ItemSpawner*> itemSpawner;
	std::list<GameObject*> itemList;

	TextGo* uiStates = nullptr;
	//TextGo* uiZombieNum = nullptr;
	//HealthBar* healthBar = nullptr;
	SpriteGo* title = nullptr;

	SpriteGo* crosshair = nullptr;



public:
	bool isWaveCleared = false;
	int wave = 0;
	int score = 0;
	int highScore = 0;

	SceneGame(SceneIds id);
	~SceneGame() override = default;

	UiHUD* GetHUD() const
	{
		return hud;
	};

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

