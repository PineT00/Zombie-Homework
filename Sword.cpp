#include "pch.h"
#include "Sword.h"
#include "Player.h"
#include "SceneGame.h"
#include "Zombie.h"

Sword::Sword(const std::string& name)
	:SpriteGo(name)
{
}

void Sword::SwordAttack(float angle, float t, int d)
{
	currentAngle = angle + 90;
	endAngle = angle - 90;
	SetPosition(player->GetPosition());
	angleSpeed = 180.f / t;
	timer = 0.f;
	interval = t;
	damage = d;
}

void Sword::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/sword.png");
	sf::FloatRect swordBounds = sprite.getLocalBounds();
	SetOrigin(sf::Vector2f(swordBounds.width + radius, swordBounds.height / 2.f));

	hasHitBox = true;
}

void Sword::Reset()
{
	SpriteGo::Reset();

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

}

void Sword::Update(float dt)
{
	currentAngle += angleSpeed * dt;

	SetPosition(player->GetPosition());
	SetRotation(currentAngle);
	timer += dt;
	if (timer > interval)
	{
		timer = 0.f;
		SetActive(false);
	}
}

void Sword::FixedUpdate(float dt)
{
	const std::list<GameObject*>& list = sceneGame->GetZombieList();
	for (auto go : list)
	{
		if (!go->GetActive())
			continue;

		if (GetGlobalBounds().intersects(go->GetGlobalBounds()))
		{
			SetActive(false);

			Zombie* zombie = dynamic_cast<Zombie*>(go);
			if (zombie != nullptr)
				zombie->OnDamage(damage);

			break;
		}
	}
}
