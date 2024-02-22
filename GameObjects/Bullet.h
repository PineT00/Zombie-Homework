#pragma once
#include "GameObject.h"

class Bullet :
    public GameObject
{

protected:

public:
	Bullet(const std::string& name = "");

	void Init();
	void Release();
	void Reset();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);


};

