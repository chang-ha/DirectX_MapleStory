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
	ContentLevel::LevelStart(_PrevLevel);
	FadeInObject->Off();

	FadeOutObject->SetChangeLevel("4.Lucid_Phase1");

	if (nullptr == GameEngineSound::FindSound("ClockTowerofNightMare.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\BGM\\ClockTowerofNightMare.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath());
	}

	if (nullptr == _CutsceneActor)
	{
		_CutsceneActor = CreateActor<CutsceneActor>(UpdateOrder::UI);
		_CutsceneActor->Init("Lucid", "4.Lucid_Phase1");
		_CutsceneActor->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());
	}

	if (false == BGMPlayer.IsPlaying())
	{
		BGMPlayer = GameEngineSound::SoundPlay("ClockTowerofNightMare.mp3", 10000);
		return;
	}

	std::string BGMName = BGMPlayer.GetCurSoundName();
	if ("ClockTowerofNightMare.mp3" != BGMName)
	{
		BGMPlayer.Stop();
		BGMPlayer = GameEngineSound::SoundPlay("ClockTowerofNightMare.mp3", 10000);
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

void Lucid_Enter::ResourcesRelease()
{

}
