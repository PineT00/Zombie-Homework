#include "pch.h"
#include "Player.h"
#include "TileMap.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "Zombie.h"
#include "Item.h"
#include "UiHUD.h"

Player::Player(const std::string& name)
    : SpriteGo(name)
{

}

void Player::Init()
{
    SpriteGo::Init();
    SetTexture("graphics/player.png");
    SetOrigin(Origins::MC);

    isFiring = false;
    fireTimer = fireInterval;
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

    isDead = false;
    noDamageTime = 0.f;
    isNoDamage = false;
    hp = hpMax;
    ammo = maxAmmo;

    sceneGame->GetHUD()->SetHp(hp, hpMax);
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
        pos = sceneGame->ClampByTileMap(pos);
    }
    SetPosition(pos);
}


void Player::Update(float dt)
{
    SpriteGo::Update(dt);

    if (isDead)
        return;
    
    sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
    sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);
    look = mouseWorldPos - position;
    Utils::Normalize(look);

    SetRotation(Utils::Angle(look));

    PlayerMove(dt);

    if (hp <= 0)
    {
        isDead = true;
        PlayerDead();
    }

    if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
    {
        isFiring = true;
    }
    if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
    {
        isFiring = false;
    }

    fireTimer += dt;
    if (isFiring && fireTimer > fireInterval && ammo > 0)
    {
        Fire();
        fireTimer = 0.f;
    }

    if (InputMgr::GetKeyDown(sf::Keyboard::R))
    {
        Reload();
    }
}

void Player::FixedUpdate(float dt)
{
    if (isNoDamage)
    {
        noDamageTime += dt;
        if (noDamageTime > noDamageInterval)
        {
            isNoDamage = false;
        }
    }
}


void Player::Draw(sf::RenderWindow& window)
{
    SpriteGo::Draw(window);
}

void Player::Fire()
{
    Bullet* bullet = new Bullet();
    bullet->Init();
    bullet->Reset();
    bullet->SetPosition(position);
    bullet->Fire(look, bulletSpeed, bulletDamage);
    ammo -= 1;
    sceneGame->AddGo(bullet);
    std::cout << ammo << std::endl;

    SOUND_MGR.PlaySfx("sound/shoot.wav");
}

void Player::Reload()
{
    int load = (12 - ammo);

    magazine -= load;

    if (magazine > 0)
    {
        load += magazine;
        magazine = 0;
    }
    ammo += load;
}

void Player::OnDamage(int damage)
{
    if (isDead || isNoDamage)
        return;

    hp -= damage;
    isNoDamage = true;
    noDamageTime = 0.f;
    std::cout << hp << std::endl;

    sceneGame->GetHUD()->SetHp(hp, hpMax);
}


void Player::PlayerDead()
{
    SetTexture("graphics/blood.png");
}

void Player::OnItem(Item* item)
{
    switch (item->GetType())
    {
    case Item::Types::Ammo:
        magazine += item->GetValue();
        break;
    case Item::Types::Health:
        hp += item->GetValue();
        break;
    }
    if (hp >= hpMax)
    {
        hp = hpMax;
    }
    sceneGame->GetHUD()->SetHp(hp, hpMax);
}
