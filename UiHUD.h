#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"

class SpriteGo;
class TextGo;

class UiHUD :
    public GameObject
{
protected:
	std::string formatScore = "SCORE: ";
	std::string formatHighScore = "HIGH SCORE: ";
	std::string formatAmmo = "{0}/{1}";
	std::string formatWave = "WAVE: ";
	std::string formatZombieCount = "ZOMBIES: ";

	float textSize = 50.f;

	TextGo textScore;
	TextGo textHiScore;

	SpriteGo imgAmmoIcon;
	TextGo textAmmo;
	sf::RectangleShape gaugeHP;
	TextGo textWave;
	TextGo textZombieCount;

	sf::Vector2f gaugeHpSize = {400.f, 30.f};

	sf::Vector2f referenceResolution = { 1920, 1080 };
	sf::Vector2f resolution = referenceResolution;
	
	int zombieCount = 0;

public:
	UiHUD(const std::string& name = "");
	~UiHUD() override = default;

	void SetResolution(const sf::Vector2f resolution);

	void SetScore(int s);
	void SetHiScore(int s);

	void SetAmmo(int current, int total);
	void SetHp(int hp, int max);
	void SetWave(int w);
	void SetZombieCount(int count);
	int GetZombieCount() { return zombieCount; }

	void Init() override;
	void Release() override;
	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

