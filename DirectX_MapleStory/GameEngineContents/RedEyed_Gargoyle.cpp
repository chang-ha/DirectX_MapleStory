#include "PreCompile.h"
#include "RedEyed_Gargoyle.h"

RedEyed_Gargoyle::RedEyed_Gargoyle()
{

}

RedEyed_Gargoyle::~RedEyed_Gargoyle()
{

}

void RedEyed_Gargoyle::LevelEnd(GameEngineLevel* _NextLevel)
{
	FieldMonster::LevelEnd(_NextLevel);
}

void RedEyed_Gargoyle::Start()
{
	FieldMonster::Start();
	FieldMonster::Init("RedEyed_Gargoyle");

	MainSpriteRenderer->CreateAnimation("Ready", std::string(MonsterName) + "_Ready", 0.1f, -1, -1, false);
	MainSpriteRenderer->CreateAnimation("Idle", std::string(MonsterName) + "_Idle", 0.15f);
	MainSpriteRenderer->CreateAnimation("Move", std::string(MonsterName) + "_Move", 0.15f);
	MainSpriteRenderer->CreateAnimation("Attack", std::string(MonsterName) + "_Attack");
	MainSpriteRenderer->CreateAnimation("Death", std::string(MonsterName) + "_Death");

	MainSpriteRenderer->SetEndEvent("Death", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		});

	MainSpriteRenderer->SetFrameEvent("Attack", 8, [&](GameEngineSpriteRenderer* _Renderer)
		{
			AttackCollision->On();
		});

	MonsterCollision->Transform.SetLocalScale({ 100, 100 });
	MonsterCollision->Transform.SetLocalPosition({ 0, 70 });
	AttackCollision->Transform.SetLocalScale({ 250, 150 });

	ReadyStart();
}

void RedEyed_Gargoyle::Update(float _Delta)
{
	FieldMonster::Update(_Delta);
}

void RedEyed_Gargoyle::Release()
{
	FieldMonster::Release();
}

void RedEyed_Gargoyle::ReadyStart()
{
	FieldMonster::ReadyStart();
	MainSpriteRenderer->SetPivotValue({ 0.5f, 0.9f });
	MainSpriteRenderer->ChangeAnimation("Ready");
}

void RedEyed_Gargoyle::IdleStart()
{
	FieldMonster::IdleStart();

	MainSpriteRenderer->SetPivotValue({ 0.5f, 0.97f });
	MainSpriteRenderer->ChangeAnimation("Idle");
}

void RedEyed_Gargoyle::MoveStart()
{
	FieldMonster::MoveStart();
	MainSpriteRenderer->SetPivotValue({ 0.5f, 0.96f });
}

void RedEyed_Gargoyle::AttackStart()
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

void RedEyed_Gargoyle::DeathStart()
{
	FieldMonster::DeathStart();
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.465f, 0.94f });
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.535f, 0.94f });
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}