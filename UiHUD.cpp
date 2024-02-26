#include "pch.h"
#include "UiHUD.h"

UiHUD::UiHUD(const std::string& name)
	:GameObject(name)
{
}

void UiHUD::SetResolution(const sf::Vector2f resolution)
{
}

void UiHUD::SetScore(int s)
{
	textScore.SetString(formatScore + std::to_string(s));
}

void UiHUD::SetHiScore(int s)
{
	textHiScore.SetString(formatHighScore + std::to_string(s));
}

void UiHUD::SetAmmo(int current, int total)
{
	textAmmo.SetString(std::to_string(current) + "/" + std::to_string(total));
}

void UiHUD::SetHp(int hp, int max)
{
	float value = (float)hp / max;

	gaugeHP.setSize({gaugeHpSize.x * value, gaugeHpSize.y });

}

void UiHUD::SetWave(int w)
{
	textWave.SetString(formatWave + std::to_string(w));
}

void UiHUD::SetZombieCount(int count)
{
	textZombieCount.SetString(formatZombieCount + std::to_string(count));
}

void UiHUD::Init()
{
	GameObject::Init();


	textScore.Init();
	textHiScore.Init();
	imgAmmoIcon.Init();
	textAmmo.Init();
	textWave.Init();
	textZombieCount.Init();

	sf::Font& font = RES_MGR_FONT.Get("fonts/zombiecontrol.ttf");

	textScore.Set(font, "", textSize, sf::Color::White);
	textHiScore.Set(font, "", textSize, sf::Color::White);
	textAmmo.Set(font, "", textSize, sf::Color::White);
	textWave.Set(font, "", textSize, sf::Color::White);
	textZombieCount.Set(font, "", textSize, sf::Color::White);

	imgAmmoIcon.SetTexture("graphics/ammo_icon.png");

	gaugeHP.setFillColor(sf::Color::Red);
	gaugeHP.setSize(gaugeHpSize);

	textScore.SetOrigin(Origins::TL);
	textHiScore.SetOrigin(Origins::TL);
	imgAmmoIcon.SetOrigin(Origins::ML);
	textAmmo.SetOrigin(Origins::BL);
	Utils::SetOrigin(gaugeHP, Origins::BL);
	textWave.SetOrigin(Origins::BR);
	textZombieCount.SetOrigin(Origins::BR);


	// TOP
	float topY = 100.f;

	textScore.SetPosition({ 150.f, topY });
	textHiScore.SetPosition({ 600.f, topY });

	//Bottom
	float BottomY = referenceResolution.y - 150.f;
	imgAmmoIcon.SetPosition({ 150.f, BottomY });
	textAmmo.SetPosition({ 200.f, BottomY });
	gaugeHP.setPosition({ 600.f, BottomY });

	textWave.SetPosition({ referenceResolution.x - 400.f, BottomY });
	textZombieCount.SetPosition({ referenceResolution.x - 150.f, BottomY });
}

void UiHUD::Release()
{
	GameObject::Release();
}

void UiHUD::Reset()
{
	GameObject::Reset();
	textScore.Reset();
	textHiScore.Reset();
	imgAmmoIcon.Reset();
	textAmmo.Reset();
	textWave.Reset();
	textZombieCount.Reset();
}

void UiHUD::Update(float dt)
{
	GameObject::Update(dt);
}

void UiHUD::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);

}

void UiHUD::FixedUpdate(float dt)
{
	GameObject::FixedUpdate(dt);

}

void UiHUD::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	textScore.Draw(window);
	textHiScore.Draw(window);
	imgAmmoIcon.Draw(window);
	textAmmo.Draw(window);
	textWave.Draw(window);
	textZombieCount.Draw(window);
	window.draw(gaugeHP);
}
