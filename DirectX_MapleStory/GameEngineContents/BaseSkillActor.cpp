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
	// Death();
}

void BaseSkillActor::Start()
{
	ContentActor::Start();
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PlayBelow);
	SkillCollision = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerAttack);
	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
}

void BaseSkillActor::Update(float _Delta)
{
	if (false == IsUpdate)
	{
		return;
	}

	ContentActor::Update(_Delta);
	BlockOutMap();
	MoveUpdate(_Delta);
	CollisionTimeUpdate(_Delta);
}

void BaseSkillActor::MoveUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 MoveDir = float4::ZERO;
	GameEngineColor CheckColor = GROUND_COLOR;

	switch (Dir)
	{
	case ActorDir::Right:
		MoveDir = float4::RIGHT;
		break;
	case ActorDir::Left:
		MoveDir = float4::LEFT;
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
	MovePos += MoveDir * _Delta * Speed;

	// 올라가는 경사면
	CheckColor = CheckGroundColor(MovePos + float4::UP);
	if ((GROUND_COLOR == CheckColor || FLOOR_COLOR == CheckColor))
	{
		float UpYPivot = 1.0f;
		GameEngineColor PivotColor = GROUND_COLOR;
		while (UP_PIXEL_LIMIT >= UpYPivot && (GROUND_COLOR == PivotColor || FLOOR_COLOR == PivotColor))
		{
			++UpYPivot;
			PivotColor = CheckGroundColor(MovePos + float4(0, UpYPivot));
		}

		while (UP_PIXEL_LIMIT >= UpYPivot && (GROUND_COLOR == CheckColor || FLOOR_COLOR == CheckColor))
		{
			MovePos += float4::UP;
			CheckColor = CheckGroundColor(MovePos + float4::UP);
		}
	}

	// 내려가는 경사면
	CheckColor = CheckGroundColor(MovePos);
	if ((GROUND_COLOR != CheckColor && FLOOR_COLOR != CheckColor))
	{
		float DownYPivot = 0.0f;
		GameEngineColor PivotColor = LADDER_COLOR;
		while (-DOWN_PIXEL_LIMIT < DownYPivot && (GROUND_COLOR != PivotColor && FLOOR_COLOR != PivotColor))
		{
			--DownYPivot;
			PivotColor = CheckGroundColor(MovePos + float4(0, DownYPivot));
		}

		while (-DOWN_PIXEL_LIMIT < DownYPivot && (GROUND_COLOR != CheckColor && FLOOR_COLOR != CheckColor))
		{
			MovePos += float4::DOWN;
			CheckColor = CheckGroundColor(MovePos);
		}
	}
	Transform.AddLocalPosition(MovePos);
}

void BaseSkillActor::BlockOutMap()
{
	if (false == IsBlockOut)
	{
		return;
	}

	float4 CurPos = Transform.GetWorldPosition();
	if (0 > CurPos.X - Scale.hX())
	{
		Transform.SetLocalPosition(float4{ Scale.hX(), CurPos.Y });
		Transform.SetLocalScale({ -1.0f, 1.0f, 1.0 });
		Dir = ActorDir::Right;
	}
	else if (CurMapScale.X <= CurPos.X + Scale.hX())
	{
		Transform.SetLocalPosition(float4{ CurMapScale.X - Scale.hX(), CurPos.Y });
		Transform.SetLocalScale({ 1.0f, 1.0f, 1.0 });
		Dir = ActorDir::Left;
	}

	//// Need Test More
	//CurPos.Y *= -1.0f;
	//if (0 > CurPos.Y - Scale.hY())
	//{
	//	Transform.SetLocalPosition(float4{ CurPos.X, -Scale.hY() });
	//}
	//else if (CurMapScale.Y <= CurPos.Y + Scale.hY())
	//{
	//	Transform.SetLocalPosition(float4{ CurPos.X, CurMapScale.Y - Scale.hY() }); 
	//}
}

void BaseSkillActor::CollisionTimeUpdate(float _Delta)
{
	for (std::pair<const std::shared_ptr<GameEngineCollision>, float>& _Pair : CollisionTime)
	{
		_Pair.second -= _Delta;
	}
}
