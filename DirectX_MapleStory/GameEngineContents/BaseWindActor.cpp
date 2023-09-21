#include "PreCompile.h"
#include "BaseWindActor.h"
#include "Player.h"
#include <GameEngineBase\GameEngineRandom.h>

#define DETECT_RANGE 700

BaseWindActor::BaseWindActor()
{

}

BaseWindActor::~BaseWindActor()
{

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
			// OtherPos = _Other->GetParentObject()->Transform.GetWorldPosition();
			// SkillManager::PlayerSkillManager->HitPrint("VortexSphere_Hit", 6, _Other->GetParentObject());
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
			RotationSpeed += 50.0f * _Delta;


			MoveVector = float4::GetUnitVectorFromDeg(DirAngle);


			Transform.AddLocalPosition( MoveVector * Speed * _Delta);
		}
	);
}

void BaseWindActor::Init(std::string_view _WindName)
{
	if (nullptr == GameEngineSprite::Find(""))
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
	MainSpriteRenderer->CreateAnimation("Death", std::string(_WindName) + "_Death");
	MainSpriteRenderer->ChangeAnimation("Ready");

	MainSpriteRenderer->SetEndEvent("Ready", [&](GameEngineRenderer* _Renderer)
		{
			MainSpriteRenderer->ChangeAnimation("Attack");
		}
	);

	MainSpriteRenderer->SetEndEvent("Hit", [&](GameEngineRenderer* _Renderer)
		{
			Death();
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

	// Random DirAngle
	GameEngineRandom Random;
	Random.SetSeed(reinterpret_cast<long long>(this));
	int RandomValue = Random.RandomInt(0, 1);
	if (0 == RandomValue)
	{
		DirAngle = 90.0f;
	}
	else
	{
		DirAngle = -90.0f;
	}
	MoveVector = float4::GetUnitVectorFromDeg(DirAngle);
}