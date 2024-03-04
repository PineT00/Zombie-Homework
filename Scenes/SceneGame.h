#pragma once
#include "Scene.h"

class TileMap;
class Player;
class Spawner;
class UiHud;
class SpriteGo;
class StatusUpgrade;
class TextGo;

class SceneGame : public Scene
{
public:
	enum class Status
	{
		Awake,
		MeleeSelect,
		Game,
		NextWave,
		GameOver,
		Pause
	};

protected:
	Status currStatus = Status::Awake;

	TileMap* tileMap = nullptr;
	Player* player = nullptr;
	UiHud* uiHud = nullptr;
	SpriteGo* crosshair = nullptr;
	SpriteGo* title = nullptr;
	StatusUpgrade* upgradeMenu = nullptr;
	TextGo* textTitle = nullptr;

	std::list<GameObject*> zombieList;
	std::list<GameObject*> itemList;
	Spawner* zombieSpawner = nullptr;
	Spawner* itemSpawner = nullptr;

	int score = 0;
	int wave = 1;
	int zombieNum = 2;
	int zombieCount = 2;
	int hiscore = 0;

	int meleeChoice = 0;

public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	bool IsInTileMap(const sf::Vector2f& point);
	sf::Vector2f ClampByTileMap(const sf::Vector2f point);
	const std::list<GameObject*>& GetZombieList() const { return zombieList; }
	sf::Font& font = RES_MGR_FONT.Get("fonts/zombiecontrol.ttf");

	UiHud* GetHud() const { return uiHud; }

	int AddScore(const int score);
	int MinusZombieNum() { return --zombieNum; }

	int GetMeleeChoice() { return meleeChoice; }

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;

	void UpdateAwake(float dt);
	void UpdateMeleeSelect(float dt);
	void UpdateGame(float dt);
	void UpdateNextWave(float dt);
	void UpdateGameOver(float dt);
	void UpdatePause(float dt);

	void Draw(sf::RenderWindow& window) override;

	void SetStatus(Status newStatus);
	Status GetStatus() { return currStatus; }
};

