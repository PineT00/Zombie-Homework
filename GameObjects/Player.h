#pragma once
#include "SpriteGo.h"


class Player : public SpriteGo
{
protected:
    sf::Vector2f direction = { 0.f, 0.f };
    sf::Vector2f look = { 1.0f, 0.f };
    float speed = 300.f;

    bool isDead = false;
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

    const sf::Vector2f GetLook() const { return look; }
};

