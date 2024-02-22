#include "pch.h"
#include "Player.h"

Player::Player(const std::string& name)
    : SpriteGo(name)
{

}

void Player::Init()
{
    SpriteGo::Init();
    SetTexture("graphics/player.png");
    SetOrigin(Origins::MC);
    hp = hpMax;
}

void Player::Release()
{
    SpriteGo::Release();
}

void Player::Reset()
{
    SpriteGo::Reset();
    hp = hpMax;
}

void Player::PlayerMove(float dt)
{
    direction.x = InputMgr::GetAxis(Axis::Horizontal);
    direction.y = InputMgr::GetAxis(Axis::Vertical);
    if (Utils::Magnitude(direction) > 1.f)
    {
        Utils::Normalize(direction);
    }
    //SetPosition(position + direction * speed * dt);
    Translate(direction * speed * dt);
}

void Player::PlayerDead()
{
    SetTexture("graphics/blood.png");
}

void Player::Update(float dt)
{

    SpriteGo::Update(dt);

    if (!isDead)
    {
        sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
        sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);
        look = mouseWorldPos - position;
        Utils::Normalize(look);

        SetRotation(Utils::Angle(look));

        PlayerMove(dt);
    }

    if (stageBounds.top >= position.y)
    {
        position.y = stageBounds.top;
    }
    if (stageBounds.height <= position.y)
    {
        direction.y = stageBounds.height;
    }
    if (stageBounds.left >= position.x)
    {
        direction.x = stageBounds.left;
    }
    if (stageBounds.width <= position.x)
    {
        direction.x = stageBounds.width;
    }

    if (hp == 0)
    {
        isDead = true;
        PlayerDead();
    }
}



void Player::Draw(sf::RenderWindow& window)
{
    SpriteGo::Draw(window);
}
