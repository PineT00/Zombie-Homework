#pragma once
#include "GameObject.h"
#include "player.h"

class HealthBar :
    public GameObject
{
protected:

public:

	sf::RectangleShape healthBar;
	sf::Vector2f healthBarMaxSize;
	sf::Vector2f healthBarCurrSize;

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

