#include "pch.h"
#include "AniTest.h"

AniTest::AniTest(const std::string& name)
	: SpriteGo(name)
{
}

AniTest::~AniTest()
{
}

void AniTest::TestInstance()
{
	std::cout << "TestInstance()" << std::endl;
}

void AniTest::TestStatic()
{
	std::cout << "TestStatic()" << std::endl;
}

void AniTest::Init()
{
	SpriteGo::Init();

	//animator.AddClip(RES_MGR_ANI_CLIP.Get("Animations/idle.csv"));
	//animator.AddClip(RES_MGR_ANI_CLIP.Get("Animations/Jump.csv"));
	//animator.AddClip(RES_MGR_ANI_CLIP.Get("Animations/Run.csv"));

	animator.SetTarget(&sprite);
}

void AniTest::Reset()
{
	animator.ClearEvent();

	std::function<void()> funcInstance = std::bind(&AniTest::TestInstance, this);
	animator.AddEvent("Animations/Jump.csv", 5, funcInstance);

	std::function<void()> funcStatic = std::bind(&AniTest::TestStatic);
	animator.AddEvent("Animations/Idle.csv", 5, funcStatic);

	animator.Play("Animations/Idle.csv");
	SetOrigin(Origins::BC);
	SetPosition({ 0.f, 0.f });
}

void AniTest::Update(float dt)
{
	//SpriteGo::Update(dt);
	animator.Update(dt);

	float h = InputMgr::GetAxis(Axis::Horizontal);

	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isGrounded = false;
		animator.Play("Animations/Jump.csv");
		velocity.y = -500.f;
	}

	velocity.x = h * speed;
	velocity.y += gravity * dt;

	position += velocity * dt;

	if (position.y > 0.f)
	{
		isGrounded = true;
		position.y = 0.f;
		velocity.y = 0.f;
	}
	SetPosition(position);

	if (h != 0.f)
	{
		SetFlipX(h < 0);
	}

	if (animator.GetCurrentClipId() == "Animations/Idle.csv")
	{
		if (h != 0.f)
		{
			animator.Play("Animations/Run.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Animations/Run.csv")
	{
		if (h == 0.f)
		{
			animator.Play("Animations/Idle.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Animations/Jump.csv" && isGrounded)
	{
		animator.Play("Animations/Idle.csv");
	}

}
