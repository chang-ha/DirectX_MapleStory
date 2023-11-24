#include "PreCompile.h"
#include "Dreamkeeper.h"

Dreamkeeper::Dreamkeeper()
{

}

Dreamkeeper::~Dreamkeeper()
{

}


void Dreamkeeper::LevelEnd(GameEngineLevel* _NextLevel)
{
	FieldMonster::LevelEnd(_NextLevel);
}

void Dreamkeeper::Start()
{
	if (nullptr == GameEngineSound::FindSound("DreamKeeper_Death.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\FieldMonster\\");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "DreamKeeper_Death.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "DreamKeeper_Attack.mp3");
	}

	DamageSkinPivot = {0, 150};
	FieldMonster::Start();
	FieldMonster::Init("Dreamkeeper");

	MainSpriteRenderer->CreateAnimation("Idle", std::string(MonsterName) + "_Idle", 0.15f);
	MainSpriteRenderer->CreateAnimation("Move", std::string(MonsterName) + "_Move", 0.15f);
	MainSpriteRenderer->CreateAnimation("Attack", std::string(MonsterName) + "_Attack");


	MainSpriteRenderer->SetFrameEvent("Attack", 8, [&](GameEngineSpriteRenderer* _Renderer)
		{
			AttackCollision->On();
		});

	MonsterCollision->Transform.SetLocalScale({ 100, 100 });
	MonsterCollision->Transform.SetLocalPosition({ 0, 70 });
	AttackCollision->Transform.SetLocalScale({ 200, 150 });

	ReadyStart();
}

void Dreamkeeper::Update(float _Delta)
{
	FieldMonster::Update(_Delta);

	if (1.0f > MainSpriteRenderer->GetColorData().MulColor.A)
	{
		MainSpriteRenderer->GetColorData().MulColor.A += _Delta;
		if (1.0f < MainSpriteRenderer->GetColorData().MulColor.A)
		{
			MainSpriteRenderer->GetColorData().MulColor.A = 1.0f;
			ChangeState(FieldMonsterState::Idle);
		}
	}
}

void Dreamkeeper::Release()
{
	FieldMonster::Release();
}

void Dreamkeeper::ReadyStart()
{
	FieldMonster::ReadyStart();
	MainSpriteRenderer->ChangeAnimation("Idle");
	MainSpriteRenderer->GetColorData().MulColor.A = 0.0f;
	MainSpriteRenderer->SetPivotValue({ 0.5f, 1.0f });
}

void Dreamkeeper::IdleStart()
{
	FieldMonster::IdleStart();
}

void Dreamkeeper::MoveStart()
{
	FieldMonster::MoveStart();
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.54f, 1.0f });
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.46f, 1.0f });
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
	MainSpriteRenderer->ChangeAnimation("Move");
}

void Dreamkeeper::AttackStart()
{
	FieldMonster::AttackStart();

	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.7f, 0.89f });
		AttackCollision->Transform.SetLocalPosition({ 150, 50 });
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.3f, 0.89f });
		AttackCollision->Transform.SetLocalPosition({ -150, 50 });
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	FieldMonsterPlayer = GameEngineSound::SoundPlay("DreamKeeper_Attack.mp3");
	FieldMonsterPlayer.SetVolume(GlobalValue::FieldMonsterVolume);
}

void Dreamkeeper::DeathStart()
{
	FieldMonster::DeathStart();
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.465f, 0.94f });
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.42f, 0.84f });
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	FieldMonsterPlayer = GameEngineSound::SoundPlay("DreamKeeper_Death.mp3");
	FieldMonsterPlayer.SetVolume(GlobalValue::FieldMonsterVolume);
}