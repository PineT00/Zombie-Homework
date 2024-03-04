#pragma once
#include "SpriteGo.h"
class Player;
class SceneGame;

class Sword : public SpriteGo
{
protected:
	float angleSpeed = 0;
	int damage = 0;

	float radius = 50.f;         //�ݰ�

	float timer = 0.f;
	float interval = 0.f;
	float currentAngle;          //���� ����  :  Utils::Angle(look) + 90  
	float endAngle;              //���� ����  :  Utils::Angle(look) - 90  

	Player* player = nullptr;
	SceneGame* sceneGame = nullptr;
public:
	Sword(const std::string& name = "");
	~Sword() override = default;

	void SwordAttack(float angle, float s, int d);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
};

