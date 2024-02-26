#include "pch.h"
#include "SceneGame.h"
#include "TextGo.h"
#include "SpriteGo.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "ItemSpawner.h"
#include "Bullet.h"
#include "UiScore.h"
#include "HealthBar.h"
#include "UiHUD.h"


SceneGame::SceneGame(SceneIds id)
    :Scene(id)
{
}

sf::Vector2f SceneGame::ClampByTileMap(const sf::Vector2f& point)
{
    sf::FloatRect rect = tileMap->GetGlobalBounds();
    rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);
    return Utils::Clamp(point, rect);
}

void SceneGame::Init()
{

    player = new Player("Player");
    AddGo(player);
 
    tileMap = new TileMap("Background");
    AddGo(tileMap);
    tileMap->sortLayer = -1; 
    //AddGo에 넣은 정렬 정상작동. 배경을 나중에 그려도 sortingLayer를 바꾸면 아래에 출력됨.

    crosshair = new SpriteGo("Crosshair");
    crosshair->SetTexture("graphics/crosshair.png");
    crosshair->SetOrigin(Origins::MC);
    crosshair->sortLayer = -1;
    AddGo(crosshair, Ui);


    //zombieSpawner.push_back(new ZombieSpawner());
    zombieSpawner.push_back(new ZombieSpawner());
    for (auto s : zombieSpawner)
    {
        s->SetPosition(Utils::RandomOnUnitCircle() * 250.f);
        AddGo(s);
    }

    itemSpawner.push_back(new ItemSpawner());
    itemSpawner.push_back(new ItemSpawner());
    for (auto m : itemSpawner)
    {
        m->SetPosition(Utils::RandomOnUnitCircle() * 10.f);
        AddGo(m);
    }

    uiStates = new TextGo("Game State");
    uiStates->Set(RES_MGR_FONT.Get("fonts/zombiecontrol.ttf"), "asda", 150, sf::Color::White);
    uiStates->SetOrigin(Origins::MC);
    uiStates->SetPosition({ 1920 * 0.5, 1080 * 0.5 - 100 });
    AddGo(uiStates, Ui);
    uiStates->sortLayer = 1;

    hud = new UiHUD("HUD");
    AddGo(hud, Ui);

    title = new SpriteGo("titleScene");
    title->SetTexture("graphics/background.png");
    AddGo(title, Ui);

    Scene::Init();
}

void SceneGame::Release()
{
    Scene::Release();
}

void SceneGame::Enter()
{
    FRAMEWORK.GetWindow().setMouseCursorVisible(false);

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

    hud->SetScore(0);
    hud->SetHiScore(0);
    hud->SetHp(300, 300);
    hud->SetWave(wave);
    hud->SetZombieCount(0);

    SOUND_MGR.PlayBgm("sound/bossFight.mp3");

    SetStatus(Status::Awake);
}

void SceneGame::Exit()
{
    Scene::Exit();
    FRAMEWORK.GetWindow().setMouseCursorVisible(true);
}


void SceneGame::Update(float dt)
{
    Scene::Update(dt);
    
    switch (currStatus)
    {
    case Status::Awake:
        UpdateAwake(dt);
        break;
    case Status::Game:
        UpdateGame(dt);
        break;
    case Status::GameOver:
        UpdateGameOver(dt);
        break;
    case Status::Pause:
        UpdatePause(dt);
        break;
    }
}

void SceneGame::UpdateAwake(float dt)
{
    worldView.setCenter(player->GetPosition());
    if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
    {
        SetStatus(Status::Game);
        SOUND_MGR.PlayBgm("sound/scaryBGM.mp3");
    }
}

void SceneGame::UpdateGame(float dt)
{
    FindGoAll("Zombie", zombieList, Layers::World);

    //Scene::Update(dt);

    crosshair->SetPosition(ScreenToUi((sf::Vector2i)InputMgr::GetMousePos()));

    hud->SetScore(score);

    if (InputMgr::GetKeyDown(sf::Keyboard::Space))
    {
        //테스트. 스페이스를 누르면 배경의 레이어가 위로 올라온다
        TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
        tileMap->sortLayer *= -1;
        ResortGo(tileMap);
    }
    
    //hud->SetHp(player->hp, player->hpMax);

    hud->SetZombieCount(FindGoAll("Zombie", zombieList, Layers::World));

    if (hud->GetZombieCount() == 0)
    {
        isWaveCleared = true;
        wave += 1;
        hud->SetWave(wave);
    }

    if (player->GetIsDead())
    {
        SetStatus(Status::GameOver);
    }
    if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
    {
        SetStatus(Status::Pause);
    }
}

void SceneGame::UpdateGameOver(float dt)
{
    if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
    {
        SetStatus(Status::Awake);
        player->Reset();
        player->SetPosition({ 0.f, 0.f });
    }
    highScore = score;
    hud->SetHiScore(highScore);
}

void SceneGame::UpdatePause(float dt)
{
    if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
    {
        SetStatus(Status::Game);
    }
}

void SceneGame::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window);
}

bool SceneGame::IsInTileMap(const sf::Vector2f& point)
{
    sf::FloatRect rect = tileMap->GetGlobalBounds();
    rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);

    return rect.contains(point);
}

void SceneGame::SetStatus(Status newStatus)
{
    FindGoAll("Zombie", zombieList, Layers::World);
    Status prevStatus = currStatus;
    currStatus = newStatus;

    switch (currStatus)
    {
    case Status::Awake:
        title->SetActive(true);
        uiStates->SetString("Press Enter to Start!");
        uiStates->SetActive(true);
        FRAMEWORK.SetTimeScale(0.f);
        break;
    case Status::Game:
        if (prevStatus == Status::GameOver)
        {
            hud->Reset();
        }
        uiStates->SetActive(false);
        title->SetActive(false);
        FRAMEWORK.SetTimeScale(1.f);
        break;
    case Status::GameOver:
        uiStates->SetString("Game Over!");
        uiStates->SetActive(true);

        FRAMEWORK.SetTimeScale(0.f);
        break;
    case Status::Pause:
        uiStates->SetString("Press Esc to Resume");
        uiStates->SetActive(true);
        FRAMEWORK.SetTimeScale(0.f);

        break;
    }
}