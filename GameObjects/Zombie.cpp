#include "pch.h"
#include "Zombie.h"
#include "SceneGame.h"

Zombie* Zombie::Create(Types zombieType)
{
    Zombie* zombie = new Zombie("Zombie");
    zombie->type = zombieType;

    switch (zombieType)
    {
    case Zombie::Types::Bloater:
        zombie->texturId = "graphics/bloater.png";
        zombie->maxHp = 50;
        zombie->speed = 50;
        zombie->damage = 30;
        zombie->attackInterval = 2;
        break;
    case Zombie::Types::Chaser:
        zombie->texturId = "graphics/chaser.png";
        zombie->maxHp = 20;
        zombie->speed = 90;
        zombie->damage = 20;
        zombie->attackInterval = 0.5f;
        break;
    case Zombie::Types::Crawler:
        zombie->texturId = "graphics/crawler.png";
        zombie->maxHp = 30;
        zombie->speed = 20;
        zombie->damage = 10;
        zombie->attackInterval = 0.5;
        break;
    }

    return zombie;
}

Zombie::Zombie(const std::string& name)
    :SpriteGo(name)
{
}

void Zombie::Init()
{
    SpriteGo::Init();
    SetTexture(texturId);
    SetOrigin(Origins::MC);
}

void Zombie::Release()
{
    SpriteGo::Release();
}

void Zombie::Reset()
{
    SpriteGo::Reset();
    hp = maxHp;
    isAlive = true;
    player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
    //tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background"));
    sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
    //SCENE_MGR.GetCurrentScene()->RemoveGo(this);
    attackTimer = 0.f;
}


void Zombie::Update(float dt)
{
    SpriteGo::Update(dt);

    if (!isAlive)
        return;

    look = player->GetPosition() - position;
    Utils::Normalize(look); 

    SetRotation(Utils::Angle(look));

    const sf::FloatRect& zombieBounds = sprite.getGlobalBounds();

    sf::Vector2f pos = position + look * speed * dt;

    if (sceneGame != nullptr)
    {
        pos = sceneGame->ClampByTileMap(pos);
    }
    SetPosition(pos);
    //Translate(look * speed * dt);

    //SCENE_MGR.GetCurrentScene()->RemoveGo(this);
}

void Zombie::FixedUpdate(float dt)
{
    attackTimer += dt;
    if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
    {
        if (attackTimer > attackInterval)
        {
            player->OnDamage(damage);
            attackTimer = 0.f;
        }
    }
}

void Zombie::Draw(sf::RenderWindow& window)
{
    SpriteGo::Draw(window);
}

void Zombie::OnDamage(int damage)
{
    if (!isAlive)
        return;

    hp -= damage;
    if (hp <= 0)
    {
        hp = 0;
        OnDie();
    }
}

void Zombie::OnDie()
{
    if (!isAlive)
        return;

    isAlive = false;
    SetActive(false);
    sceneGame->RemoveGo(this);
}
