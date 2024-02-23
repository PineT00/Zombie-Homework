#pragma once
#include "SpriteGo.h"

class SceneGame;

class Bullet : public SpriteGo
{
protected:
	sf::Vector2f direction;
	float speed;

	SceneGame* sceneGame;

public:
	Bullet(const std::string& name = "");
	~Bullet() override = default;

	void Fire(const sf::Vector2f& dir, float s);

	virtual void Init();
	virtual void Reset();
	virtual void Update(float dt);
};

