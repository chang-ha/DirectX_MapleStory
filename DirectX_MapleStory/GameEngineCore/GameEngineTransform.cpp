#include "PreCompile.h"
#include "GameEngineTransform.h"

std::function<bool(const CollisionParameter& _Data)> ArrColFunction[static_cast<int>(ColType::MAX)][static_cast<int>(ColType::MAX)];

class InitColFunction
{
public:
	InitColFunction()
	{
		// Init ArrColFunction
		for (size_t Left = 0; Left < static_cast<size_t>(ColType::MAX); Left++)
		{
			for (size_t Right = 0; Right < static_cast<size_t>(ColType::MAX); Right++)
			{
				ArrColFunction[Left][Right] = [](const CollisionParameter& _Data)
					{
						MsgBoxAssert("���� �������� ���� �浹�Լ� �Դϴ�.");
						return false;
					};
			}
		}

		// Function
		ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::AABBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingBox Left = _Data.Left.AABB;
				Left.Center.z = 0.0f;
				DirectX::BoundingBox Right = _Data.Right.AABB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::SPHERE2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingBox Left = _Data.Left.AABB;
				Left.Center.z = 0.0f;
				DirectX::BoundingSphere Right = _Data.Right.SPHERE;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::OBBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingBox Left = _Data.Left.AABB;
				Left.Center.z = 0.0f;
				DirectX::BoundingOrientedBox Right = _Data.Right.OBB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::AABBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingSphere Left = _Data.Left.SPHERE;
				Left.Center.z = 0.0f;
				DirectX::BoundingBox Right = _Data.Right.AABB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::SPHERE2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingSphere Left = _Data.Left.SPHERE;
				Left.Center.z = 0.0f;
				DirectX::BoundingSphere Right = _Data.Right.SPHERE;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::OBBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingSphere Left = _Data.Left.SPHERE;
				Left.Center.z = 0.0f;
				DirectX::BoundingOrientedBox Right = _Data.Right.OBB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};


		ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::AABBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingOrientedBox Left = _Data.Left.OBB;
				Left.Center.z = 0.0f;
				DirectX::BoundingBox Right = _Data.Right.AABB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::SPHERE2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingOrientedBox Left = _Data.Left.OBB;
				Left.Center.z = 0.0f;
				DirectX::BoundingSphere Right = _Data.Right.SPHERE;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::OBBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingOrientedBox Left = _Data.Left.OBB;
				Left.Center.z = 0.0f;
				DirectX::BoundingOrientedBox Right = _Data.Right.OBB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};
	}
};

InitColFunction Inst;

GameEngineTransform::GameEngineTransform() 
{
}

GameEngineTransform::~GameEngineTransform() 
{
}


void GameEngineTransform::TransformUpdate()
{
	TransData.LocalCalculation();

	if (nullptr != Parent)
	{
		TransData.ParentMatrix = Parent->TransData.WorldMatrix;
		TransData.WorldMatrix = TransData.WorldMatrix * TransData.ParentMatrix;

		if (true == AbsoluteScale || true == AbsoluteRotation || true == AbsolutePosition)
		{
			float4 WScale, WRotation, WPosition;
			float4 LScale, LRotation, LPosition;

			TransData.WorldMatrix.Decompose(WScale, WRotation, WPosition); // TransData�� WorldMatrix�� Scale, Rotation, Position���� ���� �и�

			// SetWorldScale || Rotation || Position�� �ߴٸ� �޾ƿ� ���� �־���
			if (true == AbsoluteScale)
			{
				WScale = TransData.Scale;
			}

			if (true == AbsoluteRotation)
			{
				WRotation = TransData.Rotation.EulerDegToQuaternion();
			}

			if (true == AbsolutePosition)
			{
				WPosition = TransData.Position;
			}

			TransData.WorldMatrix.Compose(WScale, WRotation, WPosition); // �ٽ� �ش� ����� WorldMatrix�� ����
			TransData.LocalWorldMatrix = TransData.WorldMatrix * TransData.ParentMatrix.InverseReturn(); // ���� ���尪�� �°� Local���� �������� (�θ��� ������� �����ָ� ��)
		}
	}

	/////// Collision
	TransData.WorldMatrix.Decompose(TransData.WorldScale, TransData.WorldQuaternion, TransData.WorldPosition);
	TransData.WorldRotation = TransData.WorldQuaternion.QuaternionToEulerDeg();

	TransData.LocalWorldMatrix.Decompose(TransData.LocalScale, TransData.LocalQuaternion, TransData.LocalPosition);
	TransData.LocalRotation = TransData.LocalQuaternion.QuaternionToEulerDeg();

	ColData.OBB.Extents = TransData.WorldScale.ToABS().Half().Float3;
	ColData.OBB.Center = TransData.WorldPosition.Float3;
	ColData.OBB.Orientation = TransData.WorldQuaternion.Float4;
	///////
	CalChilds();

	AbsoluteScale = false;
	AbsoluteRotation = false;
	AbsolutePosition = false;
}

void GameEngineTransform::CalculationViewAndProjection(const TransformData& _Transform)
{
	CalculationViewAndProjection(_Transform.ViewMatrix, _Transform.ProjectionMatrix);
}

void GameEngineTransform::CalculationViewAndProjection(const float4x4& _View, const float4x4& _Projection)
{
	TransData.ViewMatrix = _View;
	TransData.ProjectionMatrix = _Projection;
	TransData.WorldViewProjectionCalculation();
}

void GameEngineTransform::CalChilds()
{
	if (0 == Childs.size())
	{
		return;
	}

	for (GameEngineTransform* Trans : Childs)
	{
		Trans->TransformUpdate();
	}
}

bool GameEngineTransform::Collision(const CollisionParameter& _Data)
{
	return ArrColFunction[_Data.GetLeftTypeToInt()][_Data.GetRightTypeToInt()](_Data);
}