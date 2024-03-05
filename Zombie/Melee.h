#pragma once
#include "SpriteGo.h"

class SceneGame;
class Player;

class Melee : public SpriteGo
{
protected:
	sf::Vector2f direction;
	float angleSpeed = 0;
	int damage = 0;

	float radius = 50.f;         //�ݰ�

	float currentAngle;          //���� ����  :  Utils::Angle(look) + 90  
	float endAngle;              //���� ����  :  Utils::Angle(look) - 90  

	Player* player = nullptr;
	SceneGame* sceneGame = nullptr;
public:
	Melee(const std::string& name = "");
	~Melee() override = default;

	void MeleeAttack(float angle, float s, int d);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;

};

