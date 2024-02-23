#pragma once
#include "SpriteGo.h"

//class TileMap;
class SceneGame;

class Player : public SpriteGo
{
protected:
    sf::Vector2f direction = { 0.f, 0.f };
    sf::Vector2f look = { 1.0f, 0.f };
    float speed = 300.f;

    SceneGame* sceneGame = nullptr;

    bool isDead = false;

    //TileMap* tileMap;

    bool isFiring = false;
    float fireInterval = 0.5f;
    float fireTimer = 0.f;

public:
    sf::FloatRect stageBounds{ { 0.f, 0.f }, { 500.f, 500.f } };

    float hpMax = 300.f;
    float hp;

    Player(const std::string& name = "");
    ~Player() override = default;

    void Init() override;
    void Release() override;

    void Reset() override;

    void PlayerMove(float dt);

    void PlayerDead();

    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    void Fire();

    const sf::Vector2f GetLook() const { return look; }
    bool GetIsDead() { return isDead; }
};

