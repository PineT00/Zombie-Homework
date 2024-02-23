#pragma once
#include "GameObject.h"
#include "Zombie.h"

class SceneGame;

class ZombieSpawner :
    public GameObject
{

protected:
    std::vector<Zombie::Types> zombieTypes;

    float interval = 1.f;
    float intervalMin;
    float intervalMax;

    int spawnCount = 1;
    int spawnCountMin;
    int spawnCountMax;
    
    float radius = 250.f;
    
    float timer = 0.f;
    
    SceneGame* sceneGame;

public:
    ZombieSpawner(const std::string& name = "");
    ~ZombieSpawner() override = default;

    void Init() override;
    void Release() override;

    void Reset() override;
    void Update(float dt) override;



};

