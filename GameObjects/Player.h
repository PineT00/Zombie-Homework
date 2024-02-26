#pragma once
#include "SpriteGo.h"

//class TileMap;
class SceneGame;
class Zombie;
class Item;

class Player : public SpriteGo
{
protected:
    sf::Vector2f direction = { 0.f, 0.f };
    sf::Vector2f look = { 1.0f, 0.f };
    float speed = 300.f;

    SceneGame* sceneGame = nullptr;
    Zombie* zombie = nullptr;

    bool isDead = false;

    bool isFiring = false;
    float fireInterval = 0.1f;
    float fireTimer = 0.f;
    float bulletSpeed = 1000.f;
    int bulletDamage = 10;

    bool isNoDamage;
    float noDamageInterval = 0.5f;
    float noDamageTime = 0.f;

public:
    sf::FloatRect stageBounds{ { 0.f, 0.f }, { 500.f, 500.f } };

    float hpMax = 400.f;
    float hp = hpMax;
    int maxAmmo = 12;
    int ammo = maxAmmo;
    int magazine = 0;

    Player(const std::string& name = "");
    ~Player() override = default;

    void Init() override;
    void Release() override;

    void Reset() override;

    void PlayerMove(float dt);



    void Update(float dt) override;

    void FixedUpdate(float dt) override;
    
    void Draw(sf::RenderWindow& window) override;

    void Fire();

    void Reload();

    const sf::Vector2f GetLook() const { return look; }

    void OnDamage(int damage);

    void PlayerDead();

    bool GetIsDead() { return isDead; }

    void OnItem(Item* item);
};

