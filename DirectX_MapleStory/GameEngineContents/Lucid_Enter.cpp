#include "PreCompile.h"
#include "Lucid_Enter.h"
#include "CutsceneActor.h"
#include "FadeObject.h"

Lucid_Enter::Lucid_Enter()
{

}

Lucid_Enter::~Lucid_Enter()
{

}

void Lucid_Enter::LevelStart(GameEngineLevel* _PrevLevel)
{
	PrevLevel = "10.Boss_WaitingRoom";
	NextLevel = "12.Lucid_Phase1";

	ContentLevel::LevelStart(_PrevLevel);
	FadeInObject->Off();

	FadeOutObject->SetChangeLevel("12.Lucid_Phase1");

	if (nullptr == GameEngineSound::FindSound("ClockTowerofNightMare.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\BGM\\ClockTowerofNightMare.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath());
	}

	if (nullptr == GameEngineSound::FindSound("Lucid_Enter.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\BossRoom\\Lucid_Enter.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath());
	}

	if (nullptr == _CutsceneActor)
	{
		_CutsceneActor = CreateActor<CutsceneActor>(UpdateOrder::UI);
		_CutsceneActor->Init("Lucid");
		_CutsceneActor->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());
	}

	GameEngineSoundPlayer EnterPlayer = GameEngineSound::SoundPlay("Lucid_Enter.mp3");
	if (false == BGMPlayer.IsPlaying())
	{
		BGMPlayer = GameEngineSound::SoundPlay("ClockTowerofNightMare.mp3", 10000);
		BGMPlayer.SetVolume(GlobalValue::BGVolume);
		return;
	}

	std::string BGMName = BGMPlayer.GetCurSoundName();
	if ("ClockTowerofNightMare.mp3" != BGMName)
	{
		BGMPlayer.Stop();
		BGMPlayer = GameEngineSound::SoundPlay("ClockTowerofNightMare.mp3", 10000);
		BGMPlayer.SetVolume(GlobalValue::BGVolume);
	}
}

void Lucid_Enter::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
	if (nullptr != _CutsceneActor)
	{
		_CutsceneActor = nullptr;
	}
}

void Lucid_Enter::Start()
{
	ContentLevel::Start();
}

void Lucid_Enter::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}