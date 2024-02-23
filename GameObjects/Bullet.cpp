#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(const std::string& name) : GameObject(name)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	shape.setPosition(pos);
}

void Bullet::Translate(const sf::Vector2f& delta)
{
	position += delta;
	shape.setPosition(position);
}

void Bullet::SetOrigin(Origins preset)
{
	if (preset == Origins::Custom)
	{
		preset = Origins::MC;
	}
	originPreset = preset;
	origin = Utils::SetOrigin(shape, originPreset);
}

void Bullet::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	shape.setOrigin(newOrigin);
}

void Bullet::SetScale(const sf::Vector2f& scale)
{
	shape.setScale(scale);
}

void Bullet::Fire(sf::Vector2f d, float s)
{
	direction = d;
	speed = s;
}

void Bullet::Init()
{
	GameObject::Init();
	shape.setRadius(8.f);
	shape.setFillColor(sf::Color::Yellow);
	Utils::SetOrigin(shape, Origins::MC);
}

void Bullet::Release()
{
	GameObject::Release();
}

void Bullet::Update(float dt)
{
	GameObject::Update(dt);
	timer += dt;
	sf::Vector2f pos = shape.getPosition();
	pos += direction * speed * dt;
	shape.setPosition(pos);
	if (timer > duration)
	{
		timer = 0;
		SetActive(false);
	}
}


void Bullet::Reset()
{
}

void Bullet::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(shape);
}
