#include "PreCompile.h"
#include "BaseWindActor.h"
#include "Player.h"

#define LERPRATIO 0.5f
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
	DetectCollision = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerAttack);
}

void BaseWindActor::Update(float _Delta)
{
	MainSpriteRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, DirAngle });

	DetectCollision->Collision(CollisionOrder::Monster, [&](std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup)
		{
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

			// 나와 목표 사이의 Angle을 구함
			float4 VectorAngle = DirectX::XMVector2AngleBetweenVectors((CurPos - MostCloseTargetPos).DirectXVector, float4::RIGHT.DirectXVector);
			VectorAngle.X *= GameEngineMath::R2D;
			// 현재 Angle에서 
			DirAngle = DirAngle * (1 - LERPRATIO * _Delta) + VectorAngle.X * LERPRATIO * _Delta;

			// MoveVector.VectorRotationToDegZReturn(VectorAngle.X);
			float4 MovePos = float4::GetUnitVectorFromDeg(DirAngle);
			Transform.AddLocalPosition( -MovePos * 10.0f * _Delta);
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

	DetectCollision->Transform.SetLocalScale({300, 300});

	DirAngle = 90.0f;
	MoveVector = {0, 10};
}