#include "pch.h"
#include "Boomerang.h"
#include "SceneGame.h"
#include "Player.h"
#include "Zombie.h"

Boomerang::Boomerang(const std::string& name) : SpriteGo(name)
{
}

void Boomerang::BoomerangAttack(sf::Vector2f& dir, float s, int d)
{
	direction = dir;
	speed = s;
	damage = d;

	SetRotation(Utils::Angle(direction));
}

void Boomerang::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/boomerang.png");
	SetOrigin(Origins::MC);

	hasHitBox = true;
}

void Boomerang::Reset()
{
	SpriteGo::Reset();
	dirTimer = 0.f;

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
}

void Boomerang::Update(float dt)
{
	sprite.rotate(rotationSpeed * dt);
	SetPosition(position + direction * speed * dt);

	if (isBackword)
	{
		sf::Vector2f dir = player->GetPosition() - position;
		Utils::Normalize(dir);
		direction = dir;
	}
	else
	{
		dirTimer += dt;

		if (sceneGame != nullptr)
		{
			if (!sceneGame->IsInTileMap(position) || dirTimer > dirInterval)
			{
				dirTimer = 0.f;
				isBackword = true;
			}
		}
	}
}

void Boomerang::FixedUpdate(float dt)
{
	sf::Vector2f pos = player->GetPosition() - position;
	float distance = Utils::Magnitude(pos);
	if (distance < 50.f && isBackword)
	{
		SetActive(false);
		isBackword = false;
		player->SetThrowing(false);
	}

	const std::list<GameObject*>& list = sceneGame->GetZombieList();
	atkTimer += dt;
	for (auto go : list)
	{
		if (!go->GetActive())
			continue;

		if (GetGlobalBounds().intersects(go->GetGlobalBounds()) && atkTimer > atkInterval)
		{
			if (go != nullptr)
			{
				atkTimer = 0.f;

				Zombie* zombie = dynamic_cast<Zombie*>(go);
				if (zombie != nullptr)
					zombie->OnDamage(damage);

				break;
			}
		}
	}
}
