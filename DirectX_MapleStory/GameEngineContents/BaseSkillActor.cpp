#include "PreCompile.h"
#include "BaseSkillActor.h"
#include "ContentLevel.h"
#include "ContentMap.h"

BaseSkillActor::BaseSkillActor()
{

}

BaseSkillActor::~BaseSkillActor()
{

}


void BaseSkillActor::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentActor::LevelStart(_PrevLevel);
}

void BaseSkillActor::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentActor::LevelEnd(_NextLevel);
	Death();
}

void BaseSkillActor::Start()
{
	ContentActor::Start();
	if (nullptr == MainSpriteRenderer)
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAYBELOW);
		MainSpriteRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::playbelow});
	}

	if (nullptr == SkillCollision)
	{
		SkillCollision = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerAttack);
	}

	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
}

void BaseSkillActor::Update(float _Delta)
{
	MainSpriteRenderer->GetColorData().MulColor.A = GlobalValue::SkillEffectAlpha;

	if (false == IsUpdate)
	{
		return;
	}

	ContentActor::Update(_Delta);
	BlockOutMap();
	MoveUpdate(_Delta);
	// CollisionTimeUpdate(_Delta);
	AttackFunction.CollisionTimeUpdate(_Delta);
}

void BaseSkillActor::Release()
{
	if (nullptr != MainSpriteRenderer)
	{
		MainSpriteRenderer->Death();
		MainSpriteRenderer = nullptr;
	}

	if (nullptr != SkillCollision)
	{
		SkillCollision->Death();
		SkillCollision = nullptr;
	}

	AttackFunction.CollisionTime.clear();
	// CollisionTime.clear();
}

void BaseSkillActor::MoveUpdate(float _Delta)
{
	float MoveDir = 0.0f;

	switch (Dir)
	{
	case ActorDir::Right:
		MoveDir = 1.0f;
		break;
	case ActorDir::Left:
		MoveDir = -1.0f;
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
	SetMoveVectorXForce(MoveDir * Speed);
}

void BaseSkillActor::BlockOutMap()
{
	if (true == IsWall)
	{
		switch (Dir)
		{
		case ActorDir::Right:
			SetDir(ActorDir::Left);
			break;
		case ActorDir::Left:
			SetDir(ActorDir::Right);
			break;
		case ActorDir::Null:
		default:
			MsgBoxAssert("존재하지 않는 방향입니다.");
			break;
		}
	}

	if (false == IsBlockOut)
	{
		return;
	}

	float4 CurPos = Transform.GetWorldPosition();
	if (0 > CurPos.X - Scale.hX())
	{
		Transform.SetLocalPosition(float4{ Scale.hX(), CurPos.Y });
		SetDir(ActorDir::Right);
	}
	else if (CurMapScale.X <= CurPos.X + Scale.hX())
	{
		Transform.SetLocalPosition(float4{ CurMapScale.X - Scale.hX(), CurPos.Y });
		SetDir(ActorDir::Left);
	}
}

//void BaseSkillActor::CollisionTimeUpdate(float _Delta)
//{
//	for (std::pair<const std::shared_ptr<GameEngineCollision>, float>& _Pair : CollisionTime)
//	{
//		_Pair.second -= _Delta;
//	}
//}
