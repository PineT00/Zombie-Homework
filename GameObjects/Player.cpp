#include "pch.h"
#include "Player.h"
#include "TileMap.h"
#include "SceneGame.h"

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
    //tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background"));
    sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

    SetTexture("graphics/player.png");
    hp = hpMax;
    isDead = false;
}

void Player::PlayerMove(float dt)
{
    direction.x = InputMgr::GetAxis(Axis::Horizontal);
    direction.y = InputMgr::GetAxis(Axis::Vertical);
    if (Utils::Magnitude(direction) > 1.f)
    {
        Utils::Normalize(direction);
    }

    sf::Vector2f pos = position + direction * speed * dt;
    if (sceneGame != nullptr)
    {
        if (sceneGame != nullptr)
        {
            pos = sceneGame->ClampByTileMap(pos);
        }
        SetPosition(pos);
    }

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
