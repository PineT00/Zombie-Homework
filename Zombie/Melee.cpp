#include "pch.h"
#include "Melee.h"
#include "Player.h"
#include "SceneGame.h"
#include "Zombie.h"

Melee::Melee(const std::string& name)
	:SpriteGo(name)
{
}

void Melee::MeleeAttack(float angle, float t, int d)
{
	currentAngle = angle;
	endAngle = angle + 360;
	SetPosition(player->GetPosition());
	angleSpeed = 180.f / t;
	damage = d;
}

void Melee::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/ball.png");
	sf::FloatRect ballBounds = sprite.getLocalBounds();
	SetOrigin(sf::Vector2f(ballBounds.width + radius, ballBounds.height / 2.f));
	
	hasHitBox = true;
}

void Melee::Reset()
{
	SpriteGo::Reset();

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

}

void Melee::Update(float dt)
{
	currentAngle += angleSpeed * dt;
	
	sf::Vector2f pos = player->GetPosition();
	SetPosition(pos);
	SetRotation(currentAngle);
	
	if (currentAngle > endAngle)
	{
		SetActive(false);
	}
}

void Melee::FixedUpdate(float dt)
{
	const std::list<GameObject*>& list = sceneGame->GetZombieList();
	for (auto go : list)
	{
		if (!go->GetActive())
			continue;

		if (GetGlobalBounds().intersects(go->GetGlobalBounds()))
		{

			Zombie* zombie = dynamic_cast<Zombie*>(go);
			if (zombie != nullptr)
				zombie->OnDamage(damage);

			break;
		}

		if (currentAngle > endAngle)
		{
			SetActive(false);
		}
	}
}
