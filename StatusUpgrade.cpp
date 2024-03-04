#include "pch.h"
#include "StatusUpgrade.h"
#include "Player.h"
#include "ItemSpawner.h"

StatusUpgrade::StatusUpgrade(const std::string& name)
	:GameObject(name)
{

}

void StatusUpgrade::Init()
{
	sf::Font& font = RES_MGR_FONT.Get("fonts/zombiecontrol.ttf");

	textFireRateUp.Set(font, "1. Rate of Fire UP", fontSize, sf::Color::White);
	textReloadSizeUp.Set(font, "2. Size of Magazine Up", fontSize, sf::Color::White);
	textMaxHpUp.Set(font, "3. Max Health UP", fontSize, sf::Color::White);
	textRunSpeedUp.Set(font, "4. Max Speed UP", fontSize, sf::Color::White);
	textBetterHpItem.Set(font, "5. Better HP PickUp Item", fontSize, sf::Color::White);
	textBetterAmmoItem.Set(font, "6. Better Ammo PickUp Item", fontSize, sf::Color::White);

	textFireRateUp.SetOrigin(Origins::TL);
	textReloadSizeUp.SetOrigin(Origins::TL);
	textMaxHpUp.SetOrigin(Origins::TL);
	textRunSpeedUp.SetOrigin(Origins::TL);
	textBetterHpItem.SetOrigin(Origins::TL);
	textBetterAmmoItem.SetOrigin(Origins::TL);

	float topX = 400.f;
	textFireRateUp.SetPosition({ topX, 200 });
	textReloadSizeUp.SetPosition({ topX, 300 });
	textMaxHpUp.SetPosition({ topX, 400 });
	textRunSpeedUp.SetPosition({ topX, 500 });
	textBetterHpItem.SetPosition({ topX, 600 });
	textBetterAmmoItem.SetPosition({ topX, 700 });

}

void StatusUpgrade::Release()
{
}

void StatusUpgrade::Reset()
{
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	itemSpawner = dynamic_cast<ItemSpawner*>(SCENE_MGR.GetCurrentScene()->FindGo("Item Spawner"));
}

void StatusUpgrade::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		player->SetPlayerFireRate(0.7f);
		SOUND_MGR.PlaySfx("sound/powerup.wav");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		player->SetPlayerMaxMagazine(6);
		SOUND_MGR.PlaySfx("sound/powerup.wav");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		player->SetPlayerMaxHP(50);
		SOUND_MGR.PlaySfx("sound/powerup.wav");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num4))
	{
		player->SetPlayerSpeed(50);
		SOUND_MGR.PlaySfx("sound/powerup.wav");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num5))
	{
		itemSpawner->hpItemValue += 20;
		SOUND_MGR.PlaySfx("sound/powerup.wav");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num6))
	{
		itemSpawner->ammoItemValue += 10;
		SOUND_MGR.PlaySfx("sound/powerup.wav");
	}

}

void StatusUpgrade::Draw(sf::RenderWindow& window)
{
	textFireRateUp.Draw(window);
	textReloadSizeUp.Draw(window);
	textMaxHpUp.Draw(window);
	textRunSpeedUp.Draw(window);
	textBetterHpItem.Draw(window);
	textBetterAmmoItem.Draw(window);
}

