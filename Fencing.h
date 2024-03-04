#pragma once
#include "SpriteGo.h"

class SceneGame;
class Player;

class Fencing :
    public SpriteGo
{
protected:
	sf::Vector2f direction;
	int damage = 0;

	SceneGame* sceneGame = nullptr;
	Player* player = nullptr;

	float timer = 0.f;
	float interval = 1.f;

public:
	Fencing(const std::string& name = "");
	~Fencing() override = default;

	void stingAttack(const sf::Vector2f& dir, int d);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
};

