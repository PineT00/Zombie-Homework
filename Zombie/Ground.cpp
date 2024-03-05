#include "pch.h"
#include "Ground.h"

Ground::Ground(const std::string& name) : GameObject(name)
{
}

Ground::~Ground()
{
}

void Ground::Init()
{
	ground.setFillColor(sf::Color::White);
	ground.setSize({ 1920, 500 });
	Utils::SetOrigin(ground, Origins::TC);
	ground.setPosition({ 0, 150 });
}

void Ground::Draw(sf::RenderWindow& window)
{
	window.draw(ground);
}
