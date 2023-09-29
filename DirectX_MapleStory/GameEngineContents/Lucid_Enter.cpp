#include "PreCompile.h"
#include "Lucid_Enter.h"
#include "CutsceneActor.h"

Lucid_Enter::Lucid_Enter()
{

}

Lucid_Enter::~Lucid_Enter()
{

}

void Lucid_Enter::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
}

void Lucid_Enter::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
}

void Lucid_Enter::Start()
{
	ContentLevel::Start();
	std::shared_ptr<CutsceneActor> _CutsceneActor = CreateActor<CutsceneActor>(UpdateOrder::UI);
	_CutsceneActor->Init("Lucid", "Lucid_Phase1");
}

void Lucid_Enter::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}