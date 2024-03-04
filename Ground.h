#pragma once
class Ground : public GameObject
{
protected:
	sf::RectangleShape ground;

public:
	Ground(const std::string& name = "");
	~Ground();

	void Init();
	//void Release();

	//void Reset();

	//void Update(float dt);
	//void LateUpdate(float dt);
	//void FixedUpdate(float dt);
	void Draw(sf::RenderWindow& window);

};

