#include "PreCompile.h"
#include "BlueEyed_Gargoyle.h"

BlueEyed_Gargoyle::BlueEyed_Gargoyle()
{

}

BlueEyed_Gargoyle::~BlueEyed_Gargoyle()
{

}

void BlueEyed_Gargoyle::LevelEnd(GameEngineLevel* _NextLevel)
{
	FieldMonster::LevelEnd(_NextLevel);
}

void BlueEyed_Gargoyle::Start()
{
	FieldMonster::Start();
	FieldMonster::Init("BlueEyed_Gargoyle");

	MainSpriteRenderer->CreateAnimation("Ready", std::string(MonsterName) + "_Ready", 0.12f, -1, -1, false);
	MainSpriteRenderer->CreateAnimation("Idle", std::string(MonsterName) + "_Idle", 0.18f);
	MainSpriteRenderer->CreateAnimation("Move", std::string(MonsterName) + "_Move", 0.15f);
	MainSpriteRenderer->CreateAnimation("Attack", std::string(MonsterName) + "_Attack");

	MainSpriteRenderer->SetFrameEvent("Attack", 8, [&](GameEngineSpriteRenderer* _Renderer)
		{
			AttackCollision->On();
		});

	MonsterCollision->Transform.SetLocalScale({ 100, 100 });
	MonsterCollision->Transform.SetLocalPosition({ 0, 70 });
	AttackCollision->Transform.SetLocalScale({ 250, 150 });

	ReadyStart();
}

void BlueEyed_Gargoyle::Update(float _Delta)
{
	FieldMonster::Update(_Delta);
}

void BlueEyed_Gargoyle::Release()
{
	FieldMonster::Release();
}

void BlueEyed_Gargoyle::ReadyStart()
{
	FieldMonster::ReadyStart();
	MainSpriteRenderer->SetPivotValue({ 0.5f, 0.9f });
	MainSpriteRenderer->ChangeAnimation("Ready");
}

void BlueEyed_Gargoyle::IdleStart()
{
	FieldMonster::IdleStart();

	MainSpriteRenderer->SetPivotValue({ 0.5f, 0.97f });
	MainSpriteRenderer->ChangeAnimation("Idle");
}

void BlueEyed_Gargoyle::MoveStart()
{
	FieldMonster::MoveStart();
	MainSpriteRenderer->SetPivotValue({ 0.5f, 0.96f });
}

void BlueEyed_Gargoyle::AttackStart()
{
	FieldMonster::AttackStart();

	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.662f, 0.858f });
		AttackCollision->Transform.SetLocalPosition({ 175, 50 });
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.338f, 0.858f });
		AttackCollision->Transform.SetLocalPosition({ -175, 50 });
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void BlueEyed_Gargoyle::DeathStart()
{
	FieldMonster::DeathStart();
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->LeftFlip();
		MainSpriteRenderer->SetPivotValue({ 0.465f, 0.94f });
		break;
	case ActorDir::Left:
		MainSpriteRenderer->RightFlip();
		MainSpriteRenderer->SetPivotValue({ 0.535f, 0.94f });
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}