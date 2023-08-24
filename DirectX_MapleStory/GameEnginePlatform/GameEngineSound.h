#pragma once
#include <string>
#include <map>
#include <GameEngineBase/GameEnginePath.h>

// ����
#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>

class GameEngineSoundPlayer 
{
	friend class GameEngineSound;

public:
	void SetLoop(int _Count);
	void SetVolume(float _Volume);
	void Stop();

	GameEngineSoundPlayer() 
	{

	}


private:
	GameEngineSoundPlayer(FMOD::Channel* _Control)
		: Control(_Control)
	{
	}

	FMOD::Channel* Control = nullptr;
};

// ���� :
class GameEngineSound
{
	static float GlobalVolume;

	// Management

	friend class SoundSystemCreator;
	friend class GameEngineSoundPlayer;

private:
	static std::map<std::string, GameEngineSound*> AllSound;

public:
	static void SetGlobalVolume(float _Value) 
	{
		GlobalVolume = _Value;
	}

	static float GetGlobalVolume()
	{
		return GlobalVolume;
	}

	static void SoundLoad(std::string_view _Path)
	{
		GameEnginePath Path = GameEnginePath(_Path);
		SoundLoad(Path.GetFileName(), _Path);
	}

	static GameEngineSound* FindSound(std::string_view _path);

	static void SoundLoad(std::string_view _Name, std::string_view _Path);

	// 1���� ����� �ϰ� ������ �׳� �����ϰ� ���� ��Ʈ���Ҽ� ����.
	static GameEngineSoundPlayer SoundPlay(std::string_view _Name, int _Loop = 0);

	static void Release();

	static void Update();

public:
	// constrcuter destructer
	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

protected:

	// GameEngineSound::SoundLoad("C:\\AAAA\\AAAA\\A\\AAA.Mp3");
	// GameEngineSound::SoundPlay("AAA.Mp3");
	// GameEngineSound::PlayBgm("AAA.Mp3");
	// GameEngineSound::StopBgm("AAA.Mp3");
private:
	FMOD::Sound* SoundHandle = nullptr;

	FMOD::Channel* Play();
	void Load(std::string_view _Path);

};

