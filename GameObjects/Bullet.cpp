#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(const std::string& name) : SpriteGo(name)
{
}

void Bullet::Fire(const sf::Vector2f& dir, float s)
{
	direction = dir;
	speed = s;

	SetRotation(Utils::Angle(direction));
}

void Bullet::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/bullet.png");
	SetOrigin(Origins::ML);
}

void Bullet::Reset()
{
	SpriteGo::Reset();
}

void Bullet::Update(float dt)
{
	sf::Vector2f pos = position + direction * speed * dt;

	if (sceneGame != nullptr)
	{

	}
	SetPosition(pos);
}