#pragma once
#include "Spawner.h"
#include "Item.h"

class ItemSpawner : public Spawner
{
protected:
	std::vector<Item::Types> itemTypes;

public:
	int hpItemValue = 50;
	int ammoItemValue = 10;

	ItemSpawner(const std::string& name = "");
	~ItemSpawner() override = default;

	GameObject* Create() override;
	GameObject* dropCreate();
	void DropItem(const sf::Vector2f& position);

	void Reset() override;
};