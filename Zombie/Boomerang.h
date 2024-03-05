#pragma once
#include "SpriteGo.h"

class SceneGame;
class Player;

class Boomerang : public SpriteGo
{
protected:
	sf::Vector2f direction;
	float speed = 0;
	int damage = 0;

	float rotationSpeed = 3000.f;

	float dirTimer = 0.f;
	float dirInterval = 1.f;
	float atkTimer = 0.f;
	float atkInterval = 0.3f;

	bool isBackword = false;

	Player* player = nullptr;
	SceneGame* sceneGame = nullptr;
public:
	Boomerang(const std::string& name = "");
	~Boomerang() override = default;

	void BoomerangAttack(sf::Vector2f& dir, float s, int d);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;

};