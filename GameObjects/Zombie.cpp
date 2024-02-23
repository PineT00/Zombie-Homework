#include "pch.h"
#include "Zombie.h"
#include "SceneGame.h"

Zombie* Zombie::Create(Types zombieType)
{
    Zombie* zombie = new Zombie();
    zombie->type = zombieType;

    switch (zombieType)
    {
    case Zombie::Types::Bloater:
        zombie->texturId = "graphics/bloater.png";
        zombie->maxHp = 50;
        zombie->speed = 50;
        break;
    case Zombie::Types::Chaser:
        zombie->texturId = "graphics/chaser.png";
        zombie->maxHp = 20;
        zombie->speed = 90;
        break;
    case Zombie::Types::Crawler:
        zombie->texturId = "graphics/crawler.png";
        zombie->maxHp = 30;
        zombie->speed = 20;
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

    player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
    //tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background"));
    sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
    //SCENE_MGR.GetCurrentScene()->RemoveGo(this);
}


void Zombie::Update(float dt)
{
    SpriteGo::Update(dt);

    look = player->GetPosition() - position;
    Utils::Normalize(look); 

    SetRotation(Utils::Angle(look));


    const sf::FloatRect& zombieBounds = sprite.getGlobalBounds();

    if (Utils::Distance(position, player->GetPosition()) < 10.f)
    {
        player->hp -= 10.f;
        //SCENE_MGR.GetCurrentScene()->RemoveGo(this);
    }


    //SCENE_MGR.GetCurrentScene()->RemoveGo(this);

    sf::Vector2f pos = position + look * speed * dt;


    
    if (sceneGame != nullptr)
    {
        pos = sceneGame->ClampByTileMap(pos);
    }
    SetPosition(pos);

    //Translate(look * speed * dt);
}

void Zombie::Draw(sf::RenderWindow& window)
{
    SpriteGo::Draw(window);
}
