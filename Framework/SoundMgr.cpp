#include "pch.h"
#include "SoundMgr.h"

SoundMgr::SoundMgr()
{
}

SoundMgr::~SoundMgr()
{
	Release();
}

void SoundMgr::Init(int totalChannels)
{
	Release();
	for (int i = 0; i < totalChannels; ++i)
	{
		waiting.push_back(new sf::Sound());
	}
}

void SoundMgr::Release()
{
	StopAllSfx();
	StopBgm();

	for (auto sound : waiting)
	{
		delete sound;
	}
	waiting.clear();
	for (auto sound : playing)
	{
		delete sound;
	}
	playing.clear();
}

void SoundMgr::Update(float dt)
{
	if (!playing.empty())
	{
		for (auto it = playing.begin(); it != playing.end();)
		{
			if ((*it)->getStatus() == sf::SoundSource::Stopped)
			{
				waiting.push_back(*it);
				it = playing.erase(it); //it�� �����ϰ� it�� ������Ҹ� ��ȯ�Ѵ�.
				std::cout << "Test ���� waiting list�� �̵�." << std::endl;
			}
			else
			{
				it++;
			}
		}
	}

	if (PlayBgm)
	{
		float percent = fadeTimer / fadeDuration;
		bgmVolume = bgmVolume - percent * dt;
		bgm[0].setVolume(bgmVolume);
	}
}

void SoundMgr::PlayBgm(std::string id, bool crossFade)
{
	if (waiting.empty())
	{
		bgm[0] = *playing.front();
		playing.pop_front();

	}
	else
	{
		bgm[0] = *waiting.front();
		waiting.pop_front();
	}
	bgm[0].stop();

	bgm[1].setBuffer(RES_MGR_SOUND_BUFFER.Get(id));
	bgm[1].setLoop(true);
	bgm[1].setVolume(bgmVolume);
	bgm[1].play();
	playing.push_back(&bgm[1]);
}


void SoundMgr::StopBgm()
{
}

void SoundMgr::PlaySfx(std::string id, bool loop)
{

	PlaySfx(RES_MGR_SOUND_BUFFER.Get(id), loop);
}

void SoundMgr::PlaySfx(sf::SoundBuffer& buffer, bool loop)
{
	sf::Sound* sound = nullptr;
	if (waiting.empty())
	{
		sound = playing.front(); 
		playing.pop_front();
		sound->stop();
	}
	else
	{
		sound = waiting.front();
		waiting.pop_front();
	}
	sound->setBuffer(buffer);
	sound->setLoop(loop);
	sound->setVolume(sfxVolume);
	sound->play();
	playing.push_back(sound);
}

void SoundMgr::StopAllSfx()
{
	for (auto sound : playing)
	{
		sound->stop();
		waiting.push_back(sound);
	}
	playing.clear();
}