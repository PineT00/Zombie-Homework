#include "pch.h"
#include "Animator.h"

Animator::Animator()
{
}

Animator::~Animator()
{
}

void Animator::AddClip(const AnimationClip& clip)
{
	if (clips.find(clip.id) == clips.end()) //중복 클립명이 없는지 확인
	{
		//clips.insert({ clip.id, clip });  아래와 같음
		clips[clip.id] = clip;
	}
}

void Animator::Update(float dt)
{
	if (!isPlaying)
		return;

	accumTime += dt * speed;
	if (accumTime < clipDuration)
		return;

	accumTime = 0;
	currentFrame += addFrame;

	if (currentFrame == totalFrame)
	{
		if (!queue.empty())
		{
			std::string id = queue.front();
			queue.pop();
			Play(id, false);
			return;
		}


		switch (currentClip->loopTypes)
		{
		case AnimationLoopTypes::Single:
			currentFrame = totalFrame - 1;
			break;
		case AnimationLoopTypes::Loop:
			currentFrame = 0;
			break;
		case AnimationLoopTypes::PingPong:
			if (addFrame > 0)
			{
				currentFrame = totalFrame - 2;
				addFrame = -1;
				totalFrame = -1;
			}
			else
			{
				currentFrame = 1;
				addFrame = 1;
				totalFrame = currentClip->frames.size();
			}
			break;
		}
	}

	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::Play(const std::string& clipId, bool clearQueue)
{
	if (clearQueue)
	{
		while (!queue.empty())
		{
			queue.pop();
		}
	}

	addFrame = 1;
	isPlaying = true;
	accumTime = 0.f;

	currentClip = &clips[clipId];
	currentFrame = 0;
	totalFrame = currentClip->GetTotalFrame();
	clipDuration = 1.f / currentClip->fps;
	SetFrame(currentClip->frames[currentFrame]);

}


void Animator::PlayQueue(const std::string& clipId)
{
	queue.push(clipId);
}

void Animator::Stop()
{
	isPlaying = false;
}

void Animator::SetFrame(const AnimationFrame& frame)
{
	target->setTexture(frame.GetTexture());
	target->setTextureRect(frame.texCoord);
}

