#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>

// lib를 가져다 사용하겠다는 전처리문입니다.
// lib는 구현이다.
#ifdef _DEBUG
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#else
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

////////////////////////////////////////////////// SoundPlayer

void GameEngineSoundPlayer::SetLoop(int _Count)
{
	Control->setLoopCount(_Count);
}

void GameEngineSoundPlayer::SetVolume(float _Volume)
{
	Control->setVolume(_Volume * GameEngineSound::GlobalVolume);
}

void GameEngineSoundPlayer::Stop()
{
	Control->stop();
}


//////////////////////////////////////////////// 관리를 위한 코드 

// FMOD를 사용하기 위한 핸들 및 객체
FMOD::System* SoundSystem = nullptr;

class SoundSystemCreator
{
public:
	SoundSystemCreator()
	{
		// 이런 외부 함수는 내부에서 new를 하고 있습니다.
		if (FMOD_RESULT::FMOD_OK != FMOD::System_Create(&SoundSystem))
		{
			MsgBoxAssert("사운드 시스템 생성에 실패했습니다.");
		}

		if (FMOD_RESULT::FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgBoxAssert("사운드 시스템 이니셜라이즈에 실패했습니다.");
		}
	}

	~SoundSystemCreator()
	{


		SoundSystem->release();
	}
};


void GameEngineSound::Update()
{
	if (nullptr == SoundSystem)
	{
		MsgBoxAssert("Sound System이 생성되지 않아서 사운드 업데이트를 돌릴수가 없습니다.");
	}

	SoundSystem->update();
}



SoundSystemCreator SoundInitObject = SoundSystemCreator();
float GameEngineSound::GlobalVolume = 1.0f;

std::map<std::string, GameEngineSound*> GameEngineSound::AllSound;


GameEngineSound::GameEngineSound() 
{
}

GameEngineSound::~GameEngineSound() 
{
	if (nullptr != SoundHandle)
	{
		SoundHandle->release();
	}
}

//
//void GameEngineSound::Init()
//{
//	static bool IsOnce = false;
//
//	if (true == IsOnce)
//	{
//		return;
//	}
//
//
//
//
//	// Fmod를 사용하기 위한 준비를 하는 함수
//	IsOnce = true;
//}

GameEngineSound* GameEngineSound::FindSound(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineSound*>::iterator FindIter = AllSound.find(UpperName);

	if (FindIter == AllSound.end())
	{
		return nullptr;
	}
	
	return FindIter->second;
}

void GameEngineSound::SoundLoad(const std::string& _Name, const std::string& _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	GameEngineSound* NewSound = new GameEngineSound();

	NewSound->Load(_Path);

	AllSound.insert(std::make_pair(UpperName, NewSound));
}

GameEngineSoundPlayer GameEngineSound::SoundPlay(const std::string& _Name, int _Loop)
{
	GameEngineSound* FindSoundPtr = FindSound(_Name);

	if (nullptr == FindSoundPtr)
	{
		MsgBoxAssert("존재하지 않는 사운드를 재생하려고 했습니다.");
		return nullptr;
	}

	GameEngineSoundPlayer Player = FindSoundPtr->Play();

	Player.SetVolume(1.0f);

	Player.SetLoop(_Loop);

	return Player;
}

void GameEngineSound::Release()
{
	for (std::pair<std::string, GameEngineSound*> Pair  : GameEngineSound::AllSound)
	{
		if (nullptr == Pair.second)
		{
			return;
		}

		delete Pair.second;
	}
}



/////////////////////////////// 맴버




void GameEngineSound::Load(const std::string& _Path)
{
	// 멀티바이트 => UTF-8 인코딩으로 변환해줄 함수가 필요하다.



	// "asdfasdfasdfad" <== 멀티바이트 인코딩
	// 이녀석이 원하는 인코딩방식이 UTF-8
	// 근래에는 언어나 국가마다 오류를 일으킬 여지가 있는 string 인코딩은 안쓰려고 하는 추세다.

	std::string UTF8 = GameEngineString::AnsiToUTF8(_Path);

	// const가 안붙어있으면
	// 로드한 사운드의 정보를 리턴해주는 걸수 
	SoundSystem->createSound(UTF8.c_str(), FMOD_LOOP_NORMAL, nullptr, &SoundHandle);

	if (nullptr == SoundHandle)
	{
		MsgBoxAssert("사운드 로드에 실패했습니다.");
	}
}

FMOD::Channel* GameEngineSound::Play()
{
	FMOD::Channel* SoundControl = nullptr;

 	SoundSystem->playSound(SoundHandle, nullptr, false, &SoundControl);

	return SoundControl;
}