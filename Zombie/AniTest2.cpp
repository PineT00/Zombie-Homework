#include "pch.h"
#include "AniTest2.h"

void AniTest2::Init()
{
	//std::string textureId = "graphics/RubySheet.png";
	int width = 256;
	int height = 256;

	/*{
		AnimationClip clip;
		clip.id = "IdleSide";
		clip.fps = 5;
		clip.loopTypes = AnimationLoopTypes::Loop;
		clip.frames.push_back({ textureId, { 0, 3 * height, width, height } });
		clip.frames.push_back({ textureId, { 1 * width, 5 * height, width, height } });
		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "IdleDown";
		clip.fps = 5;
		clip.loopTypes = AnimationLoopTypes::Loop;
		clip.frames.push_back({ textureId, { 1 * width, 3 * height, width, height } });
		clip.frames.push_back({ textureId, { 2 * width, 5 * height, width, height } });
		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "IdleUp";
		clip.fps = 5;
		clip.loopTypes = AnimationLoopTypes::Loop;
		clip.frames.push_back({ textureId, { 2 * width, 3 * height, width, height } });
		clip.frames.push_back({ textureId, { 3 * width, 5 * height, width, height } });
		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "MoveSide";
		clip.fps = 5;
		clip.loopTypes = AnimationLoopTypes::Loop;
		for (int i = 0; i < 4; ++i)
		{
			clip.frames.push_back({ textureId, { i * width, 0, width, height } });
		}
		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "MoveUp";
		clip.fps = 5;
		clip.loopTypes = AnimationLoopTypes::Loop;
		for (int i = 0; i < 4; ++i)
		{
			clip.frames.push_back({ textureId, { i * width, 1 * height, width, height } });
		}
		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "MoveDown";
		clip.fps = 5;
		clip.loopTypes = AnimationLoopTypes::Loop;
		for (int i = 0; i < 4; ++i)
		{
			clip.frames.push_back({ textureId, { i * width, 2 * height, width, height } });
		}
		animator.AddClip(clip);
	}*/


	animator.SetTarget(&sprite);

	clipInfos.push_back({ "Animations/Ruby/IdleSide.csv", "Animations/Ruby/MoveSide.csv", false, Utils::GetNormal({ -1.f, -1.f }) });
	clipInfos.push_back({ "Animations/Ruby/IdleUp.csv", "Animations/Ruby/MoveUp.csv", false, { 0.f, -1.f } });
	clipInfos.push_back({ "Animations/Ruby/IdleSide.csv", "Animations/Ruby/MoveSide.csv", true, Utils::GetNormal({ 1.f, -1.f }) });

	clipInfos.push_back({ "Animations/Ruby/IdleSide.csv", "Animations/Ruby/MoveSide.csv", false, { -1.f, 0.f } });
	clipInfos.push_back({ "Animations/Ruby/IdleSide.csv", "Animations/Ruby/MoveSide.csv", true, { 1.f, 0.f } });

	clipInfos.push_back({ "Animations/Ruby/IdleSide.csv", "Animations/Ruby/MoveSide.csv", false, Utils::GetNormal({ -1.f, 1.f }) });
	clipInfos.push_back({ "Animations/Ruby/IdleDown.csv", "Animations/Ruby/MoveDown.csv", false, { 0.f, 1.f} });
	clipInfos.push_back({ "Animations/Ruby/IdleSide.csv", "Animations/Ruby/MoveSide.csv", true, Utils::GetNormal({ 1.f, 1.f }) });

}

void AniTest2::Reset()
{
	animator.Play("Animations/Ruby/IdleDown.csv");
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetFlipX(false);

	currentClipInfo = clipInfos[6];
}

void AniTest2::Update(float dt)
{
	animator.Update(dt);

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	float mag = Utils::Magnitude(direction);
	if (mag > 1.f)
	{
		direction /= mag;
	}

	position += direction * speed * dt;
	SetPosition(position);

	// 입력이 없으면, 마지막 애니메이션 유지
	if (direction.x != 0.f || direction.y != 0.f)
	{
		// 컨테이너 값 중 제일 작은 값 반환
		auto min = std::min_element(clipInfos.begin(), clipInfos.end(),
			[this](const ClipInfo& lhs, const ClipInfo& rhs)
			{
				return Utils::Distance(direction, lhs.point) <
					Utils::Distance(direction, rhs.point);
			});
		currentClipInfo = *min;
	}

	SetFlipX(currentClipInfo.flipX);

	const std::string& clipId = (direction.x != 0.f || direction.y != 0.f) ?
		currentClipInfo.move : currentClipInfo.idle;

	if (animator.GetCurrentClipId() != clipId)
		animator.Play(clipId);
}