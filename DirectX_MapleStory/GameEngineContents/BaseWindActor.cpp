#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "ContentLevel.h"
#include "BaseWindActor.h"
#include "Player.h"

#define DETECT_XRANGE 1500
#define DETECT_YRANGE 1000

BaseWindActor::BaseWindActor()
{

}

BaseWindActor::~BaseWindActor()
{

}

void BaseWindActor::CreateTriflingWind()
{
	std::shared_ptr<BaseWindActor> _Wind = ContentLevel::CurContentLevel->CreateActor<BaseWindActor>(UpdateOrder::Skill);

	GameEngineRandom Random;
	Random.SetSeed(reinterpret_cast<long long>(_Wind.get()));
	float4 RandomValue = Random.RandomVectorBox2D(0, 1, 0, 1);
	if (0.3f >= RandomValue.X)
	{
		_Wind->Init("Wind2");
	}
	else
	{
		_Wind->Init("Wind1");
		_Wind->MainSpriteRenderer->SetAutoScaleRatio(0.8f);
		_Wind->HitCollision->Transform.SetLocalScale({ 60, 20 });
	}

	if (0.5 >= RandomValue.Y)
	{
		_Wind->DirAngle = Random.RandomFloat(60.0f, 90.0f);
	}
	else
	{
		_Wind->DirAngle = -Random.RandomFloat(60.0f, 90.0f);
	}
}

void BaseWindActor::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void BaseWindActor::Start()
{
	if (nullptr == MainSpriteRenderer)
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::SKILL);
		MainSpriteRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::skill});
		MainSpriteRenderer->AutoSpriteSizeOn();
	}

	if (nullptr == HitCollision)
	{
		HitCollision = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerAttack);
		HitCollision->SetCollisionType(ColType::OBBBOX2D);
	}

	if (nullptr == DetectCollision)
	{
		DetectCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Detect);
	}
}

void BaseWindActor::Update(float _Delta)
{
	MainSpriteRenderer->GetColorData().MulColor.A = GlobalValue::SkillEffectAlpha;

	LiveTime -= _Delta;
	if (0.0f >= LiveTime)
	{
		ChangeState(WindState::Death);
	}

	StateUpdate(_Delta);
}

void BaseWindActor::Release()
{
	if (nullptr != MainSpriteRenderer)
	{
		MainSpriteRenderer->Death();
		MainSpriteRenderer = nullptr;
	}

	if (nullptr != DetectCollision)
	{
		DetectCollision->Death();
		DetectCollision = nullptr;
	}
	
	if (nullptr != HitCollision)
	{
		HitCollision->Death();
		HitCollision = nullptr;
	}
}

void BaseWindActor::Init(std::string_view _WindName)
{
	WindName = _WindName;
	if (nullptr == GameEngineSprite::Find(WindName + "_Ready"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\Wind\\" + WindName);
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder(WindName + "_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	if (nullptr == GameEngineSound::FindSound(WindName + "_Ready.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\Skill\\");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + WindName + "_Ready.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + WindName + "_Hit.mp3");
	}

	Transform.SetLocalPosition(Player::MainPlayer->Transform.GetWorldPosition());

	MainSpriteRenderer->CreateAnimation("Ready", WindName + "_Ready", 0.03f);
	MainSpriteRenderer->CreateAnimation("Attack", WindName + "_Attack", 0.06f);
	MainSpriteRenderer->CreateAnimation("Hit", WindName + "_Hit", 0.06f);
	MainSpriteRenderer->CreateAnimation("Death", WindName + "_Death", 0.08f);
	ReadyStart();

	MainSpriteRenderer->SetEndEvent("Ready", [&](GameEngineRenderer* _Renderer)
		{
			ChangeState(WindState::Attack);
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

	DetectCollision->Transform.SetLocalScale({ DETECT_XRANGE, DETECT_YRANGE });
	HitCollision->Transform.SetLocalScale({90, 40});
	MainSpriteRenderer->LeftFlip();

	MoveVector = float4::GetUnitVectorFromDeg(DirAngle);
}

void BaseWindActor::ChangeState(WindState _State)
{
	if (_State != State)
	{
		// State Start
		switch (_State)
		{
		case WindState::Ready:
			ReadyStart();
			break;
		case WindState::Attack:
			AttackStart();
			break;
		case WindState::Hit:
			HitStart();
			break;
		case WindState::Death:
			DeathStart();
			break;
		default:
			MsgBoxAssert("존재하지 않는 상태값을 시작하려고 했습니다.");
			break;
		}
	}

	State = _State;
}

void BaseWindActor::StateUpdate(float _Delta)
{
	switch (State)
	{
	case WindState::Ready:
		return ReadyUpdate(_Delta);
	case WindState::Attack:
		return AttackUpdate(_Delta);
	case WindState::Hit:
		return HitUpdate(_Delta);
	case WindState::Death:
		return DeathUpdate(_Delta);
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

void BaseWindActor::ReadyStart()
{
	MainSpriteRenderer->ChangeAnimation("Ready");
	MainSpriteRenderer->SetPivotValue({ 0.625f, 0.44f });
	WindPlayer = GameEngineSound::SoundPlay(WindName + "_Ready.mp3");
	WindPlayer.SetVolume(GlobalValue::HitVolume);
}

void BaseWindActor::AttackStart()
{
	MainSpriteRenderer->ChangeAnimation("Attack");
	MainSpriteRenderer->SetPivotType(PivotType::Center);
}

void BaseWindActor::HitStart()
{
	MainSpriteRenderer->ChangeAnimation("Hit", true, 0);
	HitCollision->Off();
	DetectCollision->Off();
	WindPlayer = GameEngineSound::SoundPlay(WindName + "_Hit.mp3");
	WindPlayer.SetVolume(GlobalValue::HitVolume);
}

void BaseWindActor::DeathStart()
{
	MainSpriteRenderer->ChangeAnimation("Death");
	HitCollision->Off();
	DetectCollision->Off();
}

void BaseWindActor::ReadyUpdate(float _Delta)
{
	AttackUpdate(_Delta);
}

void BaseWindActor::AttackUpdate(float _Delta)
{
	MainSpriteRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, DirAngle });
	HitCollision->Transform.SetLocalRotation({ 0.0f, 0.0f, DirAngle });

	HitCollision->Collision(CollisionOrder::Monster, [&](std::vector<GameEngineCollision*>& _CollisionGroup)
		{
			// 가장 먼저 충돌하는 녀석에게
			GameEngineCollision* _Other = _CollisionGroup[0];
			ChangeState(WindState::Hit);

			ContentBaseActor* _BaseActor = dynamic_cast<ContentBaseActor*>(_Other->GetParentObject());
			if (nullptr != _BaseActor)
			{
				_BaseActor->AddHP(-1);
			}
		}
	);

	DetectCollision->Collision(CollisionOrder::Monster, [&](std::vector<GameEngineCollision*>& _CollisionGroup)
		{
			// Targeting
			float4 MostCloseTargetPos = float4::ZERO;
			float4 CurPos = Transform.GetWorldPosition();

			for (size_t i = 0; i < _CollisionGroup.size(); i++)
			{
				GameEngineCollision* _Other = _CollisionGroup[i];
				float4 OtherPos = _Other->GetParentObject()->Transform.GetWorldPosition();

				if ((MostCloseTargetPos - CurPos).Size() > (OtherPos - CurPos).Size() || MostCloseTargetPos == float4::ZERO)
				{
					MostCloseTargetPos = OtherPos;
				}
			}

			float4 DirVector = (MostCloseTargetPos - CurPos).NormalizeReturn();
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

			Transform.AddLocalPosition(MoveVector * Speed * _Delta);
		}
	);
}

void BaseWindActor::HitUpdate(float _Delta)
{

}

void BaseWindActor::DeathUpdate(float _Delta)
{

}