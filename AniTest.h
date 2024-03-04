#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class AniTest : public SpriteGo
{
protected:
	Animator animator;


	float gravity = 500.f;

	float speed = 300.f;
	sf::Vector2f velocity;

	bool isGrounded = true;

public:
	AniTest(const std::string& name = "");
	~AniTest();

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	//void Draw(sf::RenderWindow& window) override;
};

