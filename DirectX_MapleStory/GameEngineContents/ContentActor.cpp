#include "PreCompile.h"
#include "ContentActor.h"
#include "ContentLevel.h"
#include "ContentMap.h"

ContentActor::ContentActor()
{

}

ContentActor::~ContentActor()
{
}

void ContentActor::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void ContentActor::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void ContentActor::Start()
{

}

void ContentActor::Update(float _Delta)
{
	IsWall = false;
	IsGround = CheckGround();
	Gravity(_Delta); // AddLocalPosition for MoveVector.Y
	AirResistance(_Delta);
	CalcuMove(_Delta); // AddLocalPosition for MoveVector.X
}

void ContentActor::Release()
{
	if (nullptr != MainSpriteRenderer)
	{
		MainSpriteRenderer->Death();
		MainSpriteRenderer = nullptr;
	}
}

void ContentActor::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	if (true == IsGround && 0.0f >= MoveVectorForce.Y)
	{
		return;
	}

	GravityForce += GravitySpeed * _Delta;
	if (MAX_GRAVITY_FORCE <= GravityForce)
	{
		GravityForce = MAX_GRAVITY_FORCE;
	}

	MoveVectorForce.Y -= GravityForce * _Delta;
	float MoveVectorForceDelta = MoveVectorForce.Y * _Delta;
	if (MaxGraviry <= MoveVectorForceDelta)
	{
		MoveVectorForceDelta = MaxGraviry;
	}
	if (0.0f > MoveVectorForce.Y)
	{
		GameEngineColor GroundColor = CheckGroundColor();
		float Count = 0.0f;
		for (; Count <= static_cast<int>(-MoveVectorForceDelta); Count += 1.0f)
		{
			if (GROUND_COLOR == GroundColor || FLOOR_COLOR == GroundColor)
			{
				break;
			}
			GroundColor = CheckGroundColor(-float4(0, 1.0f * Count));
		}
		if (0 != Count)
		{
			MoveVectorForceDelta = -1.0f * Count;
		}
		Transform.AddLocalPosition(float4(0, MoveVectorForceDelta));
	}
	else
	{
		Transform.AddLocalPosition(float4(0, MoveVectorForceDelta));
	}
}

void ContentActor::AirResistance(float _Delta)
{
	if (false == IsAirResis)
	{
		return;
	}

	switch (AirResisDir)
	{
	case ActorDir::Right:
		MoveVectorForce.X += -ResistanceForce * _Delta;
		if (0.0f >= MoveVectorForce.X)
		{
			MoveVectorForce.X = 0.0f;
		}
		break;
	case ActorDir::Left:
		MoveVectorForce.X += ResistanceForce * _Delta;
		if (0.0f <= MoveVectorForce.X)
		{
			MoveVectorForce.X = 0.0f;
		}
		break;
	case ActorDir::Null:
	default:
		break;
	}
}

void ContentActor::CalcuMove(float _Delta)
{
	float4 MovePos = MoveVectorForce.X * _Delta;
	GameEngineColor CheckColor = GROUND_COLOR;

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

		if (UP_PIXEL_LIMIT < UpYPivot && true == WallCheck)
		{
			MovePos = float4::ZERO;
			MoveVectorForce.X = 0.0f;
			IsWall = true;
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

bool ContentActor::CheckGround(float4 PlusCheckPos /*= float4::ZERO*/)
{
	bool Result = false;
	GameEngineColor CheckColor = ContentLevel::CurContentLevel->GetCurMap()->GetColor(Transform.GetWorldPosition() + PlusCheckPos/*, GameEngineColor(0, 0, 0, 255)*/);
	if (GROUND_COLOR == CheckColor || FLOOR_COLOR == CheckColor)
	{
		GravityReset();
		Result = true;
	}
	else
	{
		Result = false;
	}

	return Result;
}

GameEngineColor ContentActor::CheckGroundColor(float4 PlusCheckPos /*= float4::ZERO*/)
{
	GameEngineColor CheckColor = ContentLevel::CurContentLevel->GetCurMap()->GetColor(Transform.GetWorldPosition() + PlusCheckPos/*, GameEngineColor(0, 0, 0, 255)*/);
	return CheckColor;
}
