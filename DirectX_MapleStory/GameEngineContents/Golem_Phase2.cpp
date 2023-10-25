#include "PreCompile.h"
#include "Golem_Phase2.h"
#include "Lucid_Phase2.h"
Golem_Phase2::Golem_Phase2()
{

}

Golem_Phase2::~Golem_Phase2()
{

}

void Golem_Phase2::LevelEnd(GameEngineLevel* _NextLevel)
{
	Golem::LevelEnd(_NextLevel);
}

void Golem_Phase2::Start()
{
	Golem::Start();
	Golem::Init(Golem_Phase::Phase2);
}

void Golem_Phase2::Update(float _Delta)
{
	Golem::Update(_Delta);
}

void Golem_Phase2::Release()
{
	Golem::Release();
}


void Golem_Phase2::SetSummonFootHold(int _SummonFootHold)
{
	SummonFootHold = _SummonFootHold;

	MainSpriteRenderer->SetStartEvent("Revive", [&](GameEngineSpriteRenderer*)
		{
			Lucid_Phase2* Map = dynamic_cast<Lucid_Phase2*>(ContentLevel::CurContentLevel);
			Map->BreakFootHold(SummonFootHold);
		});
}

void Golem_Phase2::ReadyStart()
{
	Golem::ReadyStart();
	MainSpriteRenderer->SetPivotValue({0.45f, 0.58f});
}


void Golem_Phase2::ReviveStart()
{
	Golem::ReviveStart();
	MainSpriteRenderer->SetPivotValue({ 0.49f, 0.63f });
}

void Golem_Phase2::IdleStart()
{
	Golem::IdleStart();
	MainSpriteRenderer->SetPivotValue({ 0.49f, 0.915f });
	// MainSpriteRenderer->SetPivotValue();
}

void Golem_Phase2::AttackStart()
{
	Golem::AttackStart();
	// MainSpriteRenderer->SetPivotValue();
}

void Golem_Phase2::DeathStart()
{
	Golem::DeathStart();
	// MainSpriteRenderer->SetPivotValue();
}