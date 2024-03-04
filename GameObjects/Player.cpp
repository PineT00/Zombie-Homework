#include "pch.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "Item.h"
#include "UiHud.h"
#include "Melee.h"
#include "Sword.h"
#include "Boomerang.h"
#include "Fencing.h"

Player::Player(const std::string& name) : SpriteGo(name)
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/player.png");
	SetOrigin(Origins::MC);

	isFiring = false;
	fireTimer = fireInterval;

	hasHitBox = true;
}

void Player::Release()
{
	SpriteGo::Release();
	if(melee != nullptr)
		delete melee;
	melee = nullptr;

	if (sword != nullptr)
		delete sword;
	sword = nullptr;

	if (boomerang != nullptr)
		delete boomerang;
	boomerang = nullptr;
	
	if (fencing != nullptr)
		delete fencing;
	fencing = nullptr;
}

void Player::Reset()
{
	SpriteGo::Reset();

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	uiHud = dynamic_cast<UiHud*>(SCENE_MGR.GetCurrentScene()->FindGo("UI HUD"));

	hp = maxHp;
	isAlive = true;

	uiHud->SetHp(hp, maxHp);
	uiHud->SetAmmo(magazine, ammo);


	switch (sceneGame->GetMeleeChoice())
	{
	case 1:
		boomerang = new Boomerang("Boomerang");
		boomerang->Init();
		boomerang->Reset();
		boomerang->SetActive(false);
		sceneGame->AddGo(boomerang);
		break;
	case 2:
		fencing = new Fencing("fencing");
		fencing->Init();
		fencing->Reset();
		fencing->SetActive(false);
		sceneGame->AddGo(fencing);
		break;
	case 3:
		sword = new Sword("Sword");
		sword->Init();
		sword->Reset();
		sword->SetActive(false);
		sceneGame->AddGo(sword);
		break;
	case 4:
		melee = new Melee("Melee");
		melee->Init();
		melee->Reset();
		melee->SetActive(false);
		sceneGame->AddGo(melee);
		break;
	default:
		break;
	}

}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	if (!isAlive)
		return;

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	look = mouseWorldPos - position;
	Utils::Normalize(look);

	angle = Utils::Angle(look);
	sprite.setRotation(angle);

	// 상하좌우(WASD) 이동
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f)
		Utils::Normalize(direction);

	sf::Vector2f pos = position + direction * speed * dt;
	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}
	SetPosition(pos);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		isFiring = true;
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
		isFiring = false;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		if (ammo == 0)
		{
			SOUND_MGR.PlaySfx("sound/reload_failed.wav");
			return;
		}

		SOUND_MGR.PlaySfx("sound/reload.wav");

		int load = (maxMagazine - magazine);
		ammo -= load;
		if (ammo < 0)
		{
			load += ammo;
			ammo = 0;
		}
		magazine += load;

		uiHud->SetAmmo(magazine, ammo);
	}

	fireTimer += dt;
	if (isFiring && fireTimer > fireInterval && magazine > 0)
	{
		Fire();
		--magazine;
		fireTimer = 0.f;

		uiHud->SetAmmo(magazine, ammo);
	}


	//근접 무기 공격
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
	{
		if (melee != nullptr)
		{
			melee->SetActive(true);
			melee->MeleeAttack(angle, MeleeSpeed, MeleeDamage);
		}
		else if (sword != nullptr)
		{
			sword->SetActive(true);
			sword->SwordAttack(angle, MeleeSpeed, MeleeDamage);
		}
		else if (!isThrowing && boomerang != nullptr)
		{
			boomerang->SetActive(true);
			boomerang->BoomerangAttack(look, boomerangSpeed, boomerangDamage);
			boomerang->SetPosition(position);
			isThrowing = true;
		}
		else if (fencing != nullptr)
		{
			fencing->SetActive(true);
			fencing->stingAttack(look, MeleeDamage);
		}
	}


	//if (InputMgr::GetKeyDown(sf::Keyboard::LShift))
	//{

	//}
	//if (InputMgr::GetKeyDown(sf::Keyboard::Q) && )
	//{

	//}
	//if (InputMgr::GetKeyDown(sf::Keyboard::E))
	//{

	//}

	if (SCENE_MGR.GetDeveloperMode())
	{
		isNoDamage = true;
	}
	else if (isNoDamage)
	{
		noDamageTimer += dt;
		if (noDamageTimer > noDamageInterval)
		{
			isNoDamage = false;
		}
	}
}

void Player::FixedUpdate(float dt)
{
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Player::Fire()
{
	Bullet* bullet = new Bullet();
	bullet->Init();
	bullet->Reset();

	bullet->SetPosition(position);
	bullet->Fire(look, bulletSpeed, bulletDamage);
	sceneGame->AddGo(bullet);

	SOUND_MGR.PlaySfx("sound/shoot.wav");
}

void Player::OnDamage(int damage)
{
	if (!isAlive || isNoDamage)
		return;

	hp -= damage;

	isNoDamage = true;
	noDamageTimer = 0.f;

	if (hp <= 0) 
	{
		hp = 0;
		OnDie();
	}

	uiHud->SetHp(hp, maxHp);
}

void Player::OnDie()
{
	if (!isAlive)
		return;

	isAlive = false;
	SetTexture("graphics/blood.png");
	sceneGame->SetStatus(SceneGame::Status::GameOver);
}

void Player::OnItem(Item* item)
{
	switch (item->GetType())
	{
	case Item::Types::Ammo:
		ammo += item->GetValue();
		uiHud->SetAmmo(magazine, ammo);
		break;
	case Item::Types::Health:
		hp += item->GetValue();
		if (hp > maxHp)
			hp = maxHp;
		uiHud->SetHp(hp, maxHp);
		break;
	}
	SOUND_MGR.PlaySfx("sound/pickup.wav");
}