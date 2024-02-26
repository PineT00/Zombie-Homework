#pragma once
#include "GameObject.h"

class Player;

class HealthBar :
    public GameObject
{
protected:

public:
	Player* player;

	sf::RectangleShape healthBar;
	sf::Vector2f healthBarMaxSize = { 100, 10 };
	sf::Vector2f healthBarCurrSize = { 100, 10 };

	HealthBar(const std::string& name = "");

	void SetValue(float value);

	void Recover(float addedHealth);
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Damagmed(float dagame);

	void SetPosition(const sf::Vector2f pos);

	void Init() override;
	void Release() override;
	void Reset()override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

