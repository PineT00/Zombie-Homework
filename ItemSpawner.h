#pragma once
#include "Spawner.h"
#include "Item.h"

class SceneGame;

class ItemSpawner :
    public Spawner
{
protected:
    std::vector<Item::Types> itemTypes;

    float interval = 1.f;

    int spawnCount = 1;

    float radius = 250.f;

    float timer = 0.f;

    SceneGame* sceneGame;

public:
    ItemSpawner(const std::string& name = "");
    ~ItemSpawner() override = default;

    GameObject* Create() override;

    void Reset() override;
};

