#pragma once
#include "Spawner.h"
#include "Zombie.h"

class SceneGame;

class ZombieSpawner :
    public Spawner
{

protected:
    std::vector<Zombie::Types> zombieTypes;

    float interval = 1.f;
    //float intervalMin;
    //float intervalMax;

    int spawnCount = 5;
    //int spawnCountMin;
    //int spawnCountMax;
    
    float radius = 500.f;
    
    float timer = 0.f;

    SceneGame* sceneGame;

public:
    ZombieSpawner(const std::string& name = "");
    ~ZombieSpawner() override = default;

    GameObject* Create() override;

    void Reset() override;

    void WaveStart();

    void Update(float dt) override;

};

