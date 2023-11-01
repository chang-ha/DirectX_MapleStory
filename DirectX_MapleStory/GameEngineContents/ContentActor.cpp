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
	AirResistance(_Delta);
	Gravity(_Delta); // AddLocalPosition for MoveVector.Y
	CalcuMove(_Delta); // AddLocalPosition for MoveVector.X
	IsGround = CheckGround();
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
	if (-MaxGraviry >= MoveVectorForceDelta)
	{
		MoveVectorForceDelta = -MaxGraviry;
	}

	if (0.0f > MoveVectorForce.Y && -1.0f > MoveVectorForceDelta)
	{
		// GameEngineColor GroundColor = CheckGroundColor();
		float Count = 0.0f;
		for (; ; Count -= 1.0f)
		{
			if (Count <= MoveVectorForceDelta)
			{
				Count = MoveVectorForceDelta;
				break;
			}

			if (true == CheckGround(float4(0, Count)))
			{
				break;
			}
			//GroundColor = CheckGroundColor(float4(0, Count));
			//if (GROUND_COLOR == GroundColor || FLOOR_COLOR == GroundColor)
			//{
			//	break;
			//}
		}
		Transform.AddLocalPosition(float4(0, Count));
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
	float MovePosDelta = MoveVectorForce.X * _Delta;
	if (0.0f == MovePosDelta)
	{
		return;
	}

	float Count = 0.0f;
	for (; abs(Count) < abs(MovePosDelta);)
	{
		// MOVE_CHECK_FLOAT씩 이동하면서 땅 체크
		float4 MovePos = float4::ZERO;
		GameEngineColor CheckColor = GameEngineColor(0, 0, 0, 0);

		if (0.0f > MovePosDelta)
		{
			Count -= MOVE_CHECK_FLOAT;
			MovePos = -MOVE_CHECK_FLOAT;
			if (Count < MovePosDelta)
			{
				MovePos = MovePosDelta - (Count + MOVE_CHECK_FLOAT);
				Count = MovePosDelta;
			}
		}
		else if (0.0f < MovePosDelta)
		{
			Count += MOVE_CHECK_FLOAT;
			MovePos = MOVE_CHECK_FLOAT;
			if (Count > MovePosDelta)
			{
				MovePos = MovePosDelta - (Count - MOVE_CHECK_FLOAT);
				Count = MovePosDelta;
			}
		}

		CheckColor = CheckGroundColor(MovePos + float4::UP);
		float UpYPivot = 1.0f;
		if ((GROUND_COLOR == CheckColor || FLOOR_COLOR == CheckColor))
		{
			// 내 위에 땅이 몇 블록인지 체크
			GameEngineColor PivotColor = GROUND_COLOR;
			while (UP_PIXEL_LIMIT >= UpYPivot && (GROUND_COLOR == PivotColor || FLOOR_COLOR == PivotColor))
			{
				++UpYPivot;
				PivotColor = CheckGroundColor(MovePos + float4(0, UpYPivot));
			}

			// 올라가는 경사면 타는 중이면 1칸씩 올려줌
			while (0.0f == MoveVectorForce.Y && UP_PIXEL_LIMIT >= UpYPivot && (GROUND_COLOR == CheckColor || FLOOR_COLOR == CheckColor))
			{
				MovePos += float4::UP;
				CheckColor = CheckGroundColor(MovePos + float4::UP);
			}

			// 5칸이상이 땅이면 벽으로 인식
			if (UP_PIXEL_LIMIT < UpYPivot && true == WallCheck)
			{
				MovePos = float4::ZERO;
				MoveVectorForce.X = 0.0f;
				IsWall = true;
				break;
			}
		}

		CheckColor = CheckGroundColor(MovePos);
		float DownYPivot = 0.0f;
		if ( (GROUND_COLOR != CheckColor && FLOOR_COLOR != CheckColor))
		{
			GameEngineColor PivotColor = LADDER_COLOR;
			while (-DOWN_PIXEL_LIMIT < DownYPivot && (GROUND_COLOR != PivotColor && FLOOR_COLOR != PivotColor))
			{
				--DownYPivot;
				PivotColor = CheckGroundColor(MovePos + float4(0, DownYPivot));
			}

			// 내려가는 경사면 타는 중이면 1칸씩 내려줌
			while (0.0f == MoveVectorForce.Y && -DOWN_PIXEL_LIMIT < DownYPivot && (GROUND_COLOR != CheckColor && FLOOR_COLOR != CheckColor))
			{
				MovePos += float4::DOWN;
				CheckColor = CheckGroundColor(MovePos);
			}
		}

		// 이동중 땅을 만나면 멈춤
		if (false == IsGround && 0.0f == DownYPivot && (GROUND_COLOR == CheckColor || FLOOR_COLOR == CheckColor))
		{
			Transform.AddLocalPosition(MovePos);
			if (true == IsGroundVectorReset)
			{
				MoveVectorForceReset();
			}
			break;
		}

		Transform.AddLocalPosition(MovePos);
	}
}

bool ContentActor::CheckGround(float4 PlusCheckPos /*= float4::ZERO*/)
{
	//if (0.0 < MoveVectorForce.Y)
	//{
	//	return false;
	//}

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
