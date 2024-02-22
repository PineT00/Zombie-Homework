#pragma once
#include "GameObject.h"

class Bullet :
    public GameObject
{

protected:

public:
	Bullet();

	void Init();
	void Release();
	void Reset();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);


};

