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
	FadeInObject->SetAlpha(0.0f);

	FadeOutObject->SetChangeLevel("4.Lucid_Phase1");
	FadeOutObject->SetFadeSpeed(-1.0f);

	if (nullptr == _CutsceneActor)
	{
		_CutsceneActor = CreateActor<CutsceneActor>(UpdateOrder::UI);
		_CutsceneActor->Init("Lucid", "4.Lucid_Phase1");
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