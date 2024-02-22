#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "UiScore.h"
#include "HealthBar.h"


SceneGame::SceneGame(SceneIds id)
    :Scene(id)
{
}

void SceneGame::Init()
{

    player = new Player("Player");
    AddGo(player);
 
    tileMap = new TileMap("Background");
    AddGo(tileMap);
    tileMap->sortLayer = -1; 
    //AddGo�� ���� ���� �����۵�. ����� ���߿� �׷��� sortingLayer�� �ٲٸ� �Ʒ��� ��µ�.

    //ZombieSpawner* spawner = new ZombieSpawner();
    spawner.push_back(new ZombieSpawner());
    spawner.push_back(new ZombieSpawner());
    for (auto s : spawner)
    {
        s->SetPosition(Utils::RandomOnUnitCircle() * 250.f);
        AddGo(s);
    }

    UiScore* scoreUi = new UiScore("Ui Score");
    scoreUi->Set(RES_MGR_FONT.Get("fonts/zombiecontrol.ttf"), "asdad", 50, sf::Color::White);
    //scoreUi->SetPosition({ -1920.f * 0.5f, -1080 * 0.5f });
    AddGo(scoreUi, Ui);

    healthBar = new HealthBar("Health Bar");
    healthBar->healthBarMaxSize = { 400.f, 80.f };
    healthBar->SetOrigin(Origins::MC);
    healthBar->SetPosition({ 1920.f * 0.5 - 200, 1000 });
    AddGo(healthBar, Ui);
    healthBar->sortLayer = 1;

    Scene::Init();
}

void SceneGame::Release()
{
    Scene::Release();
}

void SceneGame::Enter()
{
    Scene::Enter();

    sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
    sf::Vector2f centerPos = (sf::Vector2f)FRAMEWORK.GetWindowSize() * 0.5f;
    //sf::Vector2f centerPos = windowSize * 0.5f;
    worldView.setSize(windowSize);
    worldView.setCenter({ 0.f, 0.f });
    uiView.setSize(windowSize);
    uiView.setCenter(centerPos);

    TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
    tileMap->SetPosition({ 0.f, 0.f });
    tileMap->SetScale({ 1, 1 });
    tileMap->SetRotation(0);
    tileMap->SetOrigin(Origins::MC);

    player->SetPosition({ 0.f, 0.f });
}

void SceneGame::Exit()
{
    Scene::Exit();
}

void SceneGame::Update(float dt)
{
    Scene::Update(dt);

    worldView.setCenter(player->GetPosition());

    if (InputMgr::GetKeyDown(sf::Keyboard::Space))
    {
        //�׽�Ʈ. �����̽��� ������ ����� ���̾ ���� �ö�´�
        TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
        tileMap->sortLayer *= -1;
        ResortGo(tileMap);
    }

    //healthBar->Damagmed(player->hp);
    if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
    {
    }
}

void SceneGame::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window);
}
