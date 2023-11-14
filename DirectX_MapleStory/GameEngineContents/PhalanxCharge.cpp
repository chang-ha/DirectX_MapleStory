#include "PreCompile.h"
#include "PhalanxCharge.h"
#include "PhalanxCharge_Actor.h"

PhalanxCharge::PhalanxCharge()
{
	
}

PhalanxCharge::~PhalanxCharge()
{

}

void PhalanxCharge::UseSkill()
{
	if (nullptr != PhalanxCharge_Actor::Main_PhalanxCharge)
	{
		return;
	}

	ContentSkill::UseSkill();
	On();
	SkillRenderer1->On();
	SkillRenderer1->ChangeAnimation("Effect1", true);
	SkillRenderer1->SetPivotValue({ 0.55f, 1.0f });

	switch (PlayerDir)
	{
	case ActorDir::Right:
		Transform.SetLocalScale({ -1.0f, 1.0f, 1.0f });
		break;
	case ActorDir::Left:
		Transform.SetLocalScale({ 1.0f, 1.0f, 1.0f });
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void PhalanxCharge::EndSkill()
{
	ContentSkill::EndSkill();
	Off();
	SkillRenderer1->Off();
}

void PhalanxCharge::Start()
{
	ContentSkill::Start();

	if (nullptr == GameEngineSprite::Find("PhalanxCharge_Effect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\PhalanxCharge");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("PhalanxCharge_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	SkillRenderer1->CreateAnimation("Effect1", "PhalanxCharge_Effect1", 0.06f);
	
	SkillRenderer1->SetStartEvent("Effect1", [&](GameEngineRenderer* _Renderer)
		{
			float4 PivotValue = float4::ZERO;
			switch (PlayerDir)
			{
			case ActorDir::Right:
				PivotValue.X = 180.0f;
				break;
			case ActorDir::Left:
				PivotValue.X = -180.0f;
				break;
			case ActorDir::Null:
			default:
				MsgBoxAssert("존재하지 않는 방향입니다.");
				break;
			}
			std::shared_ptr<PhalanxCharge_Actor> _Actor = GetLevel()->CreateActor<PhalanxCharge_Actor>(UpdateOrder::Skill);
			_Actor->Transform.SetLocalPosition(PlayerPos + PivotValue);
			_Actor->SetDir(PlayerDir);
		}
	);

	SkillRenderer1->SetEndEvent("Effect1", [&](GameEngineRenderer* _Renderer)
		{
			EndSkill();
		}
	);
}

void PhalanxCharge::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
	Transform.SetLocalPosition(PlayerPos);
}

void PhalanxCharge::Init()
{
	Key = 'E';
	InputTypeValue = InputType::IsDown;
	SkillCoolDown = 30.0f;
	UseState = PlayerState::Idle | PlayerState::Alert | PlayerState::Walk;
	ChangeState = PlayerState::Alert;
}
