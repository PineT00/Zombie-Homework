#include "pch.h"
#include "Fencing.h"
#include "SceneGame.h"
#include "Zombie.h"
#include "Player.h"

Fencing::Fencing(const std::string& name)
	:SpriteGo(name)
{
}

void Fencing::stingAttack(const sf::Vector2f& dir, int d)
{
	direction = dir;
	damage = d;

	SetRotation(Utils::Angle(direction));
}

void Fencing::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/fencing.png");
	SetOrigin(Origins::ML);

	hasHitBox = true;
}

void Fencing::Reset()
{
	SpriteGo::Reset();

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));

}

void Fencing::Update(float dt)
{
	sprite.setRotation(player->GetPlayerAngle());

	SetPosition(player->GetPosition());
	timer += dt;
	if (timer > interval)
	{
		timer = 0.f;
		SetActive(false);
	}
}

void Fencing::FixedUpdate(float dt)
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
		}
		if (timer > interval)
		{
			SetActive(false);
			break;
		}
	}
}
