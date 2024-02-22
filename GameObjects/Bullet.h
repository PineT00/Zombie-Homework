#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
protected:
	float timer = 0.f;
	float speed = 800.f;
	std::string textureId;
	sf::CircleShape shape;
	sf::Vector2f direction = { 0.f, 0.f };
	float duration = 3.f;


public:
	Bullet(const std::string& name = "");

	void SetPosition(const sf::Vector2f& pos) override;
	void Translate(const sf::Vector2f& delta) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetScale(const sf::Vector2f& scale) override;

	void Fire(sf::Vector2f d, float s);

	void Init() override;
	void Release() override;

	void Update(float dt) override;

	void Reset() override;

	void Draw(sf::RenderWindow& window) override;


	const sf::FloatRect GetBulletBound() const { return shape.getGlobalBounds(); }
};

