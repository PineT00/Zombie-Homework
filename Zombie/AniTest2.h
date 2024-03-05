#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class AniTest2 :
    public SpriteGo
{
public:
	struct ClipInfo
	{
		std::string idle;
		std::string move;
		bool flipX = false;
		sf::Vector2f point;

		ClipInfo()
		{

		}
		ClipInfo(const std::string& idle, const std::string& move, bool flipX,
			const sf::Vector2f& point)
			:idle(idle), move(move), flipX(flipX), point(point)
		{
		}
	};

protected:
	Animator animator;

	sf::Vector2f direction;
	float speed = 500.f;

	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;

public:
	AniTest2(const std::string& name = "") : SpriteGo(name) {};
	~AniTest2() = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
};

