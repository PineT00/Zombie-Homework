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
				it = playing.erase(it); //it을 제거하고 it의 다음요소를 반환한다.
				//std::cout << "Test 사운드 waiting list로 이동." << std::endl;
			}
			else
			{
				it++;
			}
		}
	}

	//if (isFading)
	//{
	//	fadeTimer += dt;
	//	float fadeIn = bgmVolume * fadeTimer / fadeDuration;
	//	float fadeOut = bgmVolume - fadeIn;

	//	if (fadeTimer >= fadeDuration)
	//	{
	//		bgm[backBgmIndex].stop();
	//		fadeTimer = 0.f;
	//		isFading = false;
	//	}
	//	bgm[backBgmIndex].setVolume(fadeOut);
	//	bgm[frontBgmIndex].setVolume(fadeIn);
	//}


	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		bgmVolume = 0;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		bgmVolume = 50;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		bgmVolume = 100;
	}

	if (isFading)
	{
		bool isEndBack = false;
		bool isFrontBack = false;

		int backBgmIndex = (frontBgmIndex == 1) ? 0 : 1;

		float backVolume = Utils::Lerp(backVolume = 1, 0.f, dt * fadeSpeed);
		bgm[backBgmIndex].setVolume(backVolume);
		if (std::abs(backVolume) < fadeLimit)
		{
			bgm[backBgmIndex].setVolume(0.f);
			bgm[backBgmIndex].stop();
			isEndBack = true;
		}

		float frontVolume = bgm[frontBgmIndex].getVolume();
		frontVolume = Utils::Lerp(frontVolume, bgmVolume, dt * fadeSpeed);
		bgm[frontBgmIndex].setVolume(frontVolume);

		if (std::abs(backVolume - frontVolume) < fadeLimit)
		{
			bgm[frontBgmIndex].setVolume(bgmVolume);
			isFrontBack = true;
		}

		if (isEndBack && isFrontBack)
		{
			isFading = false;
		}




		//fadeTimer += dt;
		//float volume = bgm[0].getVolume();

		//bgm[0].setVolume(Utils::Lerp(volume, bgmVolume, dt * 0.5));

		//if (fadeTimer >= fadeDuration)
		//{
		//	fadeTimer = 0.f;
		//	isFading = false;
		//}
	}
}

void SoundMgr::PlayBgm(std::string id, bool crossFade)
{
	isFading = true;
	frontBgmIndex = (frontBgmIndex + 1) % 2;
	int backBgmIndex = (frontBgmIndex == 1) ? 0 : 1;

	bgm[frontBgmIndex].setBuffer(RES_MGR_SOUND_BUFFER.Get(id));
	bgm[frontBgmIndex].setVolume(bgmVolume);
	bgm[frontBgmIndex].setLoop(true);
	bgm[frontBgmIndex].play();

	/*
	fadeTimer = 0.f;
	bgm[0].setBuffer(RES_MGR_SOUND_BUFFER.Get(id));
	bgm[0].setVolume(bgmVolume);
	bgm[frontBgmIndex].setLoop(true);
	bgm[frontBgmIndex].play();
	
	int tempIndex = frontBgmIndex;
	frontBgmIndex = backBgmIndex;
	backBgmIndex = tempIndex;

	if (crossFade)
	{
		bgm[frontBgmIndex].setVolume(0);
		isFading = true;
	}
	else
	{
		StopBgm();
		bgm[frontBgmIndex].setVolume(bgmVolume);
	}

	bgm[frontBgmIndex].setBuffer(RES_MGR_SOUND_BUFFER.Get(id));
	bgm[frontBgmIndex].setLoop(true);
	bgm[frontBgmIndex].play();
	*/
}


void SoundMgr::StopBgm()
{
	isFading = false;
	bgm[0].stop();
	bgm[1].stop();
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
