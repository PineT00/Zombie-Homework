#pragma once
#include "TextGo.h"

class Player;
class ItemSpawner;

class StatusUpgrade : public GameObject
{
protected:
	TextGo textFireRateUp;
	TextGo textReloadSizeUp;
	TextGo textMaxHpUp;
	TextGo textRunSpeedUp;
	TextGo textBetterHpItem;
	TextGo textBetterAmmoItem;

	int fontSize = 50;
public:
	Player* player;
	ItemSpawner* itemSpawner;

	StatusUpgrade(const std::string& name = "");
	~StatusUpgrade() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

