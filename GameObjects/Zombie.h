#pragma once
#include "SpriteGo.h"
#include "Player.h"

//class TileMap;
class SceneGame;

class Zombie :
    public SpriteGo
{

public:
    enum class Types
    {
        Bloater,
        Chaser,
        Crawler,
    };
    static const int TotalTypes = 3;
    static Zombie* Create(Types zombieType);

    SceneGame* sceneGame = nullptr;
    //TileMap* tileMap;




protected:
    sf::Vector2f direction = { 0.f, 0.f };
    sf::Vector2f look = { 1.0f, 0.f };
    
    Player* player;

    Types type;
    int maxHp;
    float speed;
    int hp;
    
    bool isAlive;
    //bool isNoDamage;
    //float noDamageTimer = 0.f;

    int damage = 10;
    float attackInterval;
    float attckTimer = 0.f;

public:

    Zombie(const std::string& name = "");
    ~Zombie() override = default;

    void Init() override;
    void Release() override;
    void Reset() override;

    void Update(float dt) override;
    void FixedUpdate(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    void OnDamage(int damage);
    void OnDie();

};

