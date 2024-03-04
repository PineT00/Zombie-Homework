#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "ItemSpawner.h"
#include "TextGo.h"
#include "UiHud.h"
#include "StatusUpgrade.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{
}

bool SceneGame::IsInTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);

	return rect.contains(point);
}

sf::Vector2f SceneGame::ClampByTileMap(const sf::Vector2f point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);

	return Utils::Clamp(point, rect);
}

int SceneGame::AddScore(const int score)
{
	this->score += score;
	return this->score;
}

void SceneGame::Init()
{
	// 배경
	tileMap = new TileMap("Background");
	tileMap->sortLayer = -1;
	AddGo(tileMap);

	// 스포너
	zombieSpawner = new ZombieSpawner("Zombie Spawner");
	zombieSpawner->SetPosition({ 0.f, 0.f });
	zombieSpawner->SetActive(false);
	AddGo(zombieSpawner);

	itemSpawner = new ItemSpawner("Item Spawner");
	itemSpawner->SetPosition({ 0.f, 0.f });
	AddGo(itemSpawner);
	/*for (auto s : spawners)
	{
		s->SetPosition(Utils::RandomInUnitCircle() * 250.f);
		AddGo(s);
	}*/
	
	// 플레이어
	player = new Player("Player");
	player->sortLayer = 1;
	AddGo(player);

	crosshair = new SpriteGo("Crosshair");
	crosshair->sortLayer = -1;
	crosshair->SetTexture("graphics/crosshair.png");
	crosshair->SetOrigin(Origins::MC);
	AddGo(crosshair, Layers::Ui);

	//배경 이미지
	title = new SpriteGo("Title Img");
	title->SetTexture("graphics/background2.png");
	AddGo(title, Ui);

	// UI
	uiHud = new UiHud("UI HUD");
	AddGo(uiHud, Layers::Ui);

	upgradeMenu = new StatusUpgrade("Upgrade Menu");
	AddGo(upgradeMenu, Ui);


	textTitle = new TextGo("Title Text");
	textTitle->Set(font, "Press Enter to Start!", 80, sf::Color::Red);
	textTitle->SetOutline(sf::Color::Black, 3.f);

	textTitle->SetOrigin(Origins::MC);
	textTitle->SetPosition((sf::Vector2f)FRAMEWORK.GetWindowSize() * 0.5f);

	AddGo(textTitle, Ui);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();

	FRAMEWORK.GetWindow().setMouseCursorVisible(false);
	SetStatus(Status::Awake);
	wave = 1;
	zombieCount = 2;

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	// 테스트 코드
	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	tileMap->SetPosition({ 0.f,0.f });
	tileMap->SetOrigin(Origins::MC);
	/*tileMap->SetScale({ 2.f, 2.f });
	tileMap->SetRotation(45);*/

	player->SetPosition({ 0.f,0.f });

	zombieSpawner->SetActive(false);
	zombieSpawner->Spawn(zombieNum);

	std::ifstream file("hiscore.txt");
	std::string line;
	if (file.is_open())
	{
		if (getline(file, line))
		{
			hiscore = std::stoi(line);
		}
	}
	else
	{
		std::cout << "파일을 열 수 없습니다." << std::endl;
	}
	file.close();

	// UI
	uiHud->SetScore(score);
	uiHud->SetHiScore(hiscore);
	// uiHud->SetAmmo(3, 8);
	// uiHud->SetHp(player->GetPlayerHP(), player->GetPlayerMaxHP());
	uiHud->SetWave(wave);
	uiHud->SetZombieCount(zombieNum);

}

void SceneGame::Exit()
{
	Scene::Exit();

	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
}

void SceneGame::Update(float dt)
{
	FindGoAll("Zombie", zombieList, Layers::World);
	FindGoAll("Item", itemList, Layers::World);

	Scene::Update(dt);

	crosshair->SetPosition(ScreenToUi((sf::Vector2i)InputMgr::GetMousePos()));

	sf::Vector2f worldViewCenter = worldView.getCenter();
	worldViewCenter = Utils::Lerp(worldViewCenter, player->GetPosition(), dt * 1.5f);
	worldView.setCenter(worldViewCenter);

	switch (currStatus)
	{
	case Status::Awake:
		UpdateAwake(dt);
		break;
	case Status::MeleeSelect:
		UpdateMeleeSelect(dt);
		break;
	case Status::Game:
		UpdateGame(dt);
		break;
	case Status::NextWave:
		UpdateNextWave(dt);
		break;
	case Status::GameOver:
		UpdateGameOver(dt);
		break;
	case Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void SceneGame::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneGame::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::MeleeSelect);
	}	
}

void SceneGame::UpdateMeleeSelect(float dt)
{
	textTitle->Set(font, "Select Weapon!  1:Boomerang 2:Fencing 3:Sword 4:Ball", 60, sf::Color::Red);
	textTitle->SetOrigin(Origins::MC);

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		meleeChoice = 1;
		SetStatus(Status::Game);
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		meleeChoice = 2;
		SetStatus(Status::Game);
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		meleeChoice = 3;
		SetStatus(Status::Game);
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Num4))
	{
		meleeChoice = 4;
		SetStatus(Status::Game);
	}
	player->Reset();
}


void SceneGame::UpdateGame(float dt)
{
	if (zombieNum <= 0)
	{
		SetStatus(Status::NextWave);
		return;
	}
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
		return;
	}

	if (SCENE_MGR.GetDeveloperMode() && InputMgr::GetKeyDown(sf::Keyboard::Delete))
	{
		for (auto go : zombieList)
		{
			Zombie* zombie = dynamic_cast<Zombie*>(go);
			zombie->OnDie();
		}
	}

}

void SceneGame::UpdateNextWave(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter) || InputMgr::GetKeyDown(sf::Keyboard::Num1) 
		|| InputMgr::GetKeyDown(sf::Keyboard::Num2) || InputMgr::GetKeyDown(sf::Keyboard::Num3)
		|| InputMgr::GetKeyDown(sf::Keyboard::Num4) || InputMgr::GetKeyDown(sf::Keyboard::Num5) || InputMgr::GetKeyDown(sf::Keyboard::Num6))
	{
		SetStatus(Status::Game);

		++wave;

		player->SetPosition({ 0.f, 0.f });
		if (wave < 7)
		{
			tileMap->Set({ wave * 9, wave * 7 }, { 50.f, 50.f });
			tileMap->SetOrigin(Origins::MC);

			zombieCount *= 2;
		}
		else
		{
			zombieCount += 10;
		}
		zombieNum = zombieCount;

		for (auto item : itemList)
		{
			RemoveGo(item);
		}

		itemSpawner->SetRadius(250.f * wave);
		zombieSpawner->SetRadius(250.f * wave);

		zombieSpawner->Spawn(zombieNum);

		dynamic_cast<ZombieSpawner*>(zombieSpawner)->NextWave(wave);

		uiHud->SetWave(wave);
		uiHud->SetZombieCount(zombieNum);
	}
}

void SceneGame::UpdateGameOver(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		Release();
		Init();

		score = 0;
		wave = 1;
		zombieCount = 2;
		zombieNum = zombieCount;
		meleeChoice = 0;
		Enter();
		SetStatus(Status::Awake);
	}
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

void SceneGame::SetStatus(Status newStatus)
{
	Status prevStatus = currStatus;
	currStatus = newStatus;

	switch (currStatus)
	{
	case Status::Awake:
		title->SetTexture("graphics/background2.png");
		title->SetActive(true);
		textTitle->SetActive(true);
		upgradeMenu->SetActive(false);
		uiHud->SetActive(false);
		SOUND_MGR.PlayBgm("sound/bossFight.mp3", false);
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case Status::Game:
		title->SetActive(false);
		textTitle->SetActive(false);
		upgradeMenu->SetActive(false);
		uiHud->SetActive(true);
		uiHud->SetMessage("");
		uiHud->SetMessageActive(false);
		uiHud->SetHp(player->GetPlayerHP(), player->GetPlayerMaxHP());
		FRAMEWORK.SetTimeScale(1.f);
		break;
	case Status::NextWave:
		title->SetTexture("graphics/background.png");
		title->SetActive(true);
		upgradeMenu->SetActive(true);
		uiHud->SetActive(false);
		uiHud->SetMessage("Next Wave!");
		uiHud->SetMessageActive(true);
		FRAMEWORK.SetTimeScale(0.f);

		if (meleeChoice == 1)
		{
			player->SetThrowing(false);
			FindGo("Boomerang")->SetActive(false);
		}
		break;
	case Status::GameOver:
		if (score > hiscore)
		{
			std::ofstream file("hiscore.txt");
			if (file.is_open())
			{
				file.write(std::to_string(score).c_str(), std::to_string(score).size());  //.c_str() : string형 -> char*형
			}
			file.close();
		}
		uiHud->SetMessage("Game Over!");
		uiHud->SetMessageActive(true);
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case Status::Pause:
		uiHud->SetMessage("Pause!");
		uiHud->SetMessageActive(true);
		FRAMEWORK.SetTimeScale(0.f);
		break;
	}
}
