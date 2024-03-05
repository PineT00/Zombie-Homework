#include "pch.h"
#include "Zombie.h"
#include "SceneGame.h"
#include "UiHud.h"
#include "SpriteGoEffect.h"
#include "ZombieTable.h"
#include "ItemSpawner.h"

Zombie* Zombie::Create(Types zombieType)
{
	Zombie* zombie = new Zombie("Zombie");
	zombie->type = zombieType;

	const DataZombie& data = ZOMBIE_TABLE->Get(zombieType);
	zombie->textureId = data.textureId;
	zombie->maxHp = data.maxHp;
	zombie->speed = data.speed;
	zombie->damage = data.damage;
	zombie->attackInterval = data.attackInterval;
	zombie->sortLayer = 1;

	zombie->dashSpeed = zombie->speed * 5.f;
	zombie->originalSpeed = zombie->speed;


	return zombie;
}

Zombie::Zombie(const std::string& name) : SpriteGo(name)
{
}

void Zombie::Dash(bool isDash)
{
	if (isDash)
	{
		speed = dashSpeed;
	}
	else
	{
		speed = originalSpeed;
	}
}

void Zombie::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);

	hpBar.setFillColor(sf::Color::Red);
	hpBar.setSize(hpBarSize);
	Utils::SetOrigin(hpBar, Origins::BL);

	hasHitBox = true;

	if (type == Zombie::Types::Worm)
	{
		direction = sf::Vector2f(1.0f, 1.0f);

		direction.x = Utils::RandomRange(-1, 1);
		direction.y = Utils::RandomRange(-1, 1);

		Utils::Normalize(direction);
		float angle = Utils::Angle(direction);
		SetRotation(angle);
	}
}

void Zombie::Release()
{
	SpriteGo::Release();
}

void Zombie::Reset()
{
	SpriteGo::Reset();
	hp = maxHp;
	attackTimer = attackInterval;

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	uiHud = dynamic_cast<UiHud*>(SCENE_MGR.GetCurrentScene()->FindGo("UI HUD"));
	itemSpawner = dynamic_cast<ItemSpawner*>(SCENE_MGR.GetCurrentScene()->FindGo("Item Spawner"));

	isAlive = true;
}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);

	if (!isAlive)
		return;

	if (!isDash && type != Zombie::Types::Worm)
	{
		direction = player->GetPosition() - position;
		float distance = Utils::Magnitude(direction);
		Utils::Normalize(direction);
		float angle = Utils::Angle(direction);
		SetRotation(angle);
	}

	sf::Vector2f pos = position + direction * speed * dt;

	wormTimer += dt;
	if (type == Zombie::Types::Worm)
	{
		if (wormTimer < wormInterval)
		{
			direction = player->GetPosition() - position;
			float distance = Utils::Magnitude(direction);
			Utils::Normalize(direction);
			float angle = Utils::Angle(direction);
			speed = 1.f;
			SetRotation(angle);
		}
		if (wormTimer > wormInterval)
		{
			speed = 500.f;
		}
		if (!sceneGame->IsInTileMap(pos))
		{
			float angle = Utils::Angle(direction);
			SetRotation(angle);
			wormTimer = 0.f;
		}
	}

	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}
	SetPosition(pos);

	hpBar.setPosition(position.x - 40.f, position.y - 40.f);
}

void Zombie::FixedUpdate(float dt)
{
	attackTimer += dt;

	if (attackTimer > attackInterval)
	{
		if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
		{
			if (type == Zombie::Types::Bloater)
			{
				player->OnDamage(damage * 1.5f);
				SOUND_MGR.PlaySfx("sound/zombieExplode.wav");
				OnDie();
			}
			else
			{
				player->OnDamage(damage);
				attackInterval = 0.f;
			}
		}
	}

	hpBar.setScale({ (float)hp / maxHp, 1.f });

	dashTimer += dt;
	if (type == Zombie::Types::Chaser)
	{
		if (!isDash && dashTimer > dashInterval)
		{
			speed = dashSpeed;
			isDash = true;
		}
		if (isDash && dashTimer > dashInterval + dashTime)
		{
			speed = originalSpeed;
			int rand = Utils::RandomRange(0, 8);
			dashTimer = (float)0.1 * rand;
			isDash = false;
		}
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	if (SCENE_MGR.GetDeveloperMode())
		window.draw(hpBar);
}

void Zombie::OnDamage(int damage)
{
	SOUND_MGR.PlaySfx("sound/hit.wav");

	if (!isAlive)
		return;

	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
		SOUND_MGR.PlaySfx("sound/splat.wav");
		OnDie();
	}
}

void Zombie::OnDie()
{
	if (!isAlive)
		return;

	uiHud->SetScore(sceneGame->AddScore(10));
	uiHud->SetZombieCount(sceneGame->MinusZombieNum());
	isAlive = false;
	SetActive(false);
	sceneGame->RemoveGo(this);

	SpriteGoEffect* effectBlood = new SpriteGoEffect();
	effectBlood->Init();
	effectBlood->SetOrigin(Origins::MC);
	effectBlood->SetTexture("graphics/blood.png");
	effectBlood->Reset();
	effectBlood->sortLayer = -1;
	effectBlood->sortOrder = 1;
	effectBlood->SetPosition(position);
	effectBlood->SetRotation(Utils::RandomRange(0.f, 360.f));

	if (type == Zombie::Types::Bloater)
	{
		effectBlood->SetTexture("graphics/blood2.png");
		effectBlood->SetScale({ 2.f, 2.f });
	}
	if (type == Zombie::Types::Worm)
	{
		effectBlood->SetTexture("graphics/blood3.png");
		effectBlood->SetScale({ 1.5f, 1.5f });
	}

	sceneGame->AddGo(effectBlood);

	int rand = Utils::RandomRange(0,3);  // 0, 1, 2
	if (rand)
	{
		itemSpawner->DropItem(position);
	}
}