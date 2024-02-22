#include "pch.h"
#include "HealthBar.h"

HealthBar::HealthBar(const std::string& name)
	:GameObject(name)
{
	healthBar.setFillColor(sf::Color::Red);
}

void HealthBar::SetValue(float value)
{
}

void HealthBar::Recover(float addedHealth)
{
}

void HealthBar::SetOrigin(Origins preset)
{
	if (preset == Origins::Custom)
	{
		preset = Origins::TL;
	}
	originPreset = preset;
	origin = Utils::SetOrigin(healthBar, originPreset);
}

void HealthBar::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	healthBar.setOrigin(newOrigin);
}

void HealthBar::SetPosition(const sf::Vector2f pos)
{
	healthBar.setPosition(pos);
}

void HealthBar::Init()
{
	GameObject::Init();
	healthBarCurrSize = healthBarMaxSize;
	healthBar.setSize(healthBarCurrSize);
}

void HealthBar::Release()
{
	GameObject::Release();
}

void HealthBar::Reset()
{
	GameObject::Reset();
	healthBarCurrSize = healthBarMaxSize;
}

void HealthBar::Update(float dt)
{
	GameObject::Update(dt);
}

void HealthBar::Draw(sf::RenderWindow& window)
{
	//GameObject::Draw(window);
	window.draw(healthBar);
}