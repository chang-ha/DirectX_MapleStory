#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "ContentLevel.h"
#include "BaseWindActor.h"
#include "Player.h"

#define DETECT_RANGE 700

BaseWindActor::BaseWindActor()
{

}

BaseWindActor::~BaseWindActor()
{

}

std::shared_ptr<BaseWindActor> BaseWindActor::CreateMercilessWind()
{
	std::shared_ptr<BaseWindActor> _Wind = ContentLevel::CurContentLevel->CreateActor<BaseWindActor>(UpdateOrder::Skill);
	_Wind->Init("Wind3");
	_Wind->Off();
	GameEngineRandom Random;
	Random.SetSeed(reinterpret_cast<long long>(_Wind.get()));
	float4 PivotValue = Random.RandomVectorBox2D(-150, 150, 100, 200);
	_Wind->Transform.AddLocalPosition(PivotValue);

	float RandomValue = Random.RandomFloat(0, 1);
	if (0.5 >= RandomValue)
	{
		_Wind->DirAngle = 90.0f;
	}
	else
	{
		_Wind->DirAngle = -90.0f;
	}

	return _Wind;
}

void BaseWindActor::CreateTriflingWind()
{
	std::shared_ptr<BaseWindActor> _Wind = ContentLevel::CurContentLevel->CreateActor<BaseWindActor>(UpdateOrder::Skill);

	GameEngineRandom Random;
	Random.SetSeed(reinterpret_cast<long long>(_Wind.get()));
	float4 RandomValue = Random.RandomVectorBox2D(0, 1, 0, 1);
	if (0.10 >= RandomValue.X)
	{
		_Wind->Init("Wind2");
	}
	else
	{
		_Wind->Init("Wind1");
	}

	if (0.5 >= RandomValue.Y)
	{
		_Wind->DirAngle = 90.0f;
	}
	else
	{
		_Wind->DirAngle = -90.0f;
	}
}

void BaseWindActor::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void BaseWindActor::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void BaseWindActor::Start()
{
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Skill);
	MainSpriteRenderer->AutoSpriteSizeOn();
	HitCollision = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerAttack);
	// DetectCollision의 CollisionOrder 추후 변경 필요?
	DetectCollision = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerAttack);
}

void BaseWindActor::Update(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimation("Hit") || true == MainSpriteRenderer->IsCurAnimation("Death"))
	{
		return;
	}

	LiveTime -= _Delta;
	if (0.0f >= LiveTime)
	{
		MainSpriteRenderer->ChangeAnimation("Death");
	}

	MainSpriteRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, -DirAngle });

	HitCollision->Collision(CollisionOrder::Monster, [&](std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup)
		{
			// 가장 먼저 충돌하는 녀석에게
			std::shared_ptr<GameEngineCollision> _Other = _CollisionGroup[0];
			MainSpriteRenderer->ChangeAnimation("Hit");
		}
	);

	DetectCollision->Collision(CollisionOrder::Monster, [&](std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup)
		{
			// Targeting
			float4 MostCloseTargetPos = float4::ZERO;
			float4 CurPos = Transform.GetWorldPosition();

			for (size_t i = 0; i < _CollisionGroup.size(); i++)
			{
				std::shared_ptr<GameEngineCollision> _Other = _CollisionGroup[i];
				float4 OtherPos = _Other->GetParentObject()->Transform.GetWorldPosition();

				if ((MostCloseTargetPos - CurPos).Size() > (OtherPos - CurPos).Size() || MostCloseTargetPos == float4::ZERO)
				{
					MostCloseTargetPos = OtherPos;
				}
			}

			float4 DirVector = (MostCloseTargetPos - CurPos ).NormalizeReturn();
			// 현재 이동벡터와 목적지까지의 벡터 사이의 각도를 구함
			float4 Angle = DirectX::XMVector2AngleBetweenNormals(DirVector.DirectXVector, MoveVector.DirectXVector);
			// Radina to Degree
			float PlusAngle = Angle.X * GameEngineMath::R2D;

			// 회전방향 결정용 외적
			float4 RotationDir = DirectX::XMVector2Cross(DirVector.DirectXVector, MoveVector.DirectXVector);
			if (0.0f <= RotationDir.X)
			{
				DirAngle -= PlusAngle * RotationSpeed * _Delta;
			}
			else
			{
				DirAngle += PlusAngle * RotationSpeed * _Delta;
			}
			RotationSpeed += 30.0f * _Delta;

			MoveVector = float4::GetUnitVectorFromDeg(DirAngle);

			Transform.AddLocalPosition( MoveVector * Speed * _Delta);
		}
	);
}

void BaseWindActor::Init(std::string_view _WindName)
{
	if (nullptr == GameEngineSprite::Find(std::string(_WindName) + "_Ready"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\Wind\\" + std::string(_WindName.data()));
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder(std::string(_WindName) + "_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	Transform.SetLocalPosition(Player::MainPlayer->Transform.GetWorldPosition());

	MainSpriteRenderer->CreateAnimation("Ready", std::string(_WindName) + "_Ready", 0.03f);
	MainSpriteRenderer->CreateAnimation("Attack", std::string(_WindName) + "_Attack", 0.06f);
	MainSpriteRenderer->CreateAnimation("Hit", std::string(_WindName) + "_Hit", 0.06f);
	MainSpriteRenderer->CreateAnimation("Death", std::string(_WindName) + "_Death", 0.08f);
	MainSpriteRenderer->ChangeAnimation("Ready");
	MainSpriteRenderer->SetPivotValue({0.625f, 0.44f});

	MainSpriteRenderer->SetEndEvent("Ready", [&](GameEngineRenderer* _Renderer)
		{
			MainSpriteRenderer->ChangeAnimation("Attack");
			MainSpriteRenderer->SetPivotType(PivotType::Center);
		}
	);

	MainSpriteRenderer->SetEndEvent("Hit", [&](GameEngineRenderer* _Renderer)
		{
			Death();
		}
	);

	MainSpriteRenderer->SetStartEvent("Death", [&](GameEngineRenderer* _Renderer)
		{
			MainSpriteRenderer->SetPivotValue({0.6f, 0.51f});
		}
	);

	MainSpriteRenderer->SetEndEvent("Death", [&](GameEngineRenderer* _Renderer)
		{
			Death();
		}
	);

	DetectCollision->Transform.SetLocalScale({ DETECT_RANGE, DETECT_RANGE });
	HitCollision->Transform.SetLocalScale({90, 40});
	Transform.SetLocalScale({ -1.0f, 1.0f, 1.0f });

	MoveVector = float4::GetUnitVectorFromDeg(DirAngle);
}