#include "PreCompile.h"
#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>

// lib�� ������ ����ϰڴٴ� ��ó�����Դϴ�.
// lib�� �����̴�.
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

void GameEngineSoundPlayer::Pause()
{
	Control->setPaused(true);
}

void GameEngineSoundPlayer::Resume()
{
	Control->setPaused(false);
}

bool GameEngineSoundPlayer::IsPlaying()
{
	bool Result = false;
	if (FMOD_OK != Control->isPlaying(&Result))
	{
		return false;
	}
	return Result;
}

std::string GameEngineSoundPlayer::GetCurSoundName()
{
	FMOD::Sound* _Sound;
	if (FMOD_OK != Control->getCurrentSound(&_Sound))
	{
		MsgBoxAssert("FMOD::Sound�� �����µ� �����߽��ϴ�.");
	}

	char _Name[512] = {};
	if (FMOD_OK != _Sound->getName(_Name, 512))
	{
		MsgBoxAssert("�̸��� �����µ� �����߽��ϴ�.");
	}
	std::string Result = _Name;

	return Result;
}

//////////////////////////////////////////////// ������ ���� �ڵ� 

// FMOD�� ����ϱ� ���� �ڵ� �� ��ü
FMOD::System* SoundSystem = nullptr;

class SoundSystemCreator
{
public:
	SoundSystemCreator()
	{
		// �̷� �ܺ� �Լ��� ���ο��� new�� �ϰ� �ֽ��ϴ�.
		if (FMOD_RESULT::FMOD_OK != FMOD::System_Create(&SoundSystem))
		{
			MsgBoxAssert("���� �ý��� ������ �����߽��ϴ�.");
		}

		if (FMOD_RESULT::FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgBoxAssert("���� �ý��� �̴ϼȶ���� �����߽��ϴ�.");
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
		MsgBoxAssert("Sound System�� �������� �ʾƼ� ���� ������Ʈ�� �������� �����ϴ�.");
	}

	SoundSystem->update();
}



SoundSystemCreator SoundInitObject = SoundSystemCreator();
float GameEngineSound::GlobalVolume = 1.0f;

std::map<std::string, std::shared_ptr<GameEngineSound>> GameEngineSound::AllSound;


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
//	// Fmod�� ����ϱ� ���� �غ� �ϴ� �Լ�
//	IsOnce = true;
//}

std::shared_ptr<GameEngineSound> GameEngineSound::FindSound(std::string_view _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, std::shared_ptr<GameEngineSound>>::iterator FindIter = AllSound.find(UpperName);

	if (FindIter == AllSound.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void GameEngineSound::SoundLoad(std::string_view _Name, std::string_view _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::shared_ptr<GameEngineSound> NewSound = std::make_shared<GameEngineSound>();

	NewSound->Load(_Path);

	AllSound.insert(std::make_pair(UpperName, NewSound));
}

GameEngineSoundPlayer GameEngineSound::SoundPlay(std::string_view _Name, int _Loop)
{
	std::shared_ptr<GameEngineSound> FindSoundPtr = FindSound(_Name);

	if (nullptr == FindSoundPtr)
	{
		MsgBoxAssert("�������� �ʴ� ���带 ����Ϸ��� �߽��ϴ�.");
		return nullptr;
	}

	GameEngineSoundPlayer Player = FindSoundPtr->Play();

	Player.SetVolume(1.0f);

	Player.SetLoop(_Loop);

	return Player;
}

void GameEngineSound::Release()
{
	GameEngineSound::AllSound.clear();
}



/////////////////////////////// �ɹ�




void GameEngineSound::Load(std::string_view _Path)
{
	// ��Ƽ����Ʈ => UTF-8 ���ڵ����� ��ȯ���� �Լ��� �ʿ��ϴ�.



	// "asdfasdfasdfad" <== ��Ƽ����Ʈ ���ڵ�
	// �̳༮�� ���ϴ� ���ڵ������ UTF-8
	// �ٷ����� �� �������� ������ ����ų ������ �ִ� string ���ڵ��� �Ⱦ����� �ϴ� �߼���.

	std::string UTF8 = GameEngineString::AnsiToUTF8(_Path);

	// const�� �Ⱥپ�������
	// �ε��� ������ ������ �������ִ� �ɼ� 
	SoundSystem->createSound(UTF8.c_str(), FMOD_LOOP_NORMAL, nullptr, &SoundHandle);

	if (nullptr == SoundHandle)
	{
		MsgBoxAssert("���� �ε忡 �����߽��ϴ�.");
	}
}

FMOD::Channel* GameEngineSound::Play()
{
	FMOD::Channel* SoundControl = nullptr;

 	SoundSystem->playSound(SoundHandle, nullptr, false, &SoundControl);

	return SoundControl;
}