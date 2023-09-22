#include "PreCompile.h"
#include "VortexSphere.h"
#include "VortexSphere_Actor.h"

VortexSphere::VortexSphere()
{
	
}

VortexSphere::~VortexSphere()
{

}

void VortexSphere::UseSkill()
{
	ContentSkill::UseSkill();
	On();
	SkillRenderer1->On();
	SkillRenderer1->ChangeAnimation("Effect1", true);

	switch (PlayerDir)
	{
	case ActorDir::Right:
		SkillRenderer1->LeftFlip();
		SkillRenderer2->LeftFlip();
		break;
	case ActorDir::Left:
		SkillRenderer1->RightFlip();
		SkillRenderer2->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void VortexSphere::EndSkill()
{
	ContentSkill::EndSkill();
	SkillRenderer1->Off();
	SkillRenderer2->Off();
	Off();
}

void VortexSphere::Start()
{
	ContentSkill::Start();

	if (nullptr == GameEngineSprite::Find("VortexSphere_Effect1"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\VortexSphere");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("VortexSphere_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	SkillRenderer1->CreateAnimation("Effect1", "VortexSphere_Effect1", 0.08f);
	SkillRenderer1->SetPivotValue({0.37f, 0.55f});
	SkillRenderer2->CreateAnimation("Effect2", "VortexSphere_Effect2", 0.08f);
	SkillRenderer2->SetPivotValue({0.9f, 0.51f});

	SkillRenderer1->SetFrameEvent("Effect1", 5, [&](GameEngineSpriteRenderer* _Renderer)
		{
			SkillRenderer2->On();
			SkillRenderer2->ChangeAnimation("Effect2", true);

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
			PivotValue.Y = 20.0f;

			std::shared_ptr<VortexSphere_Actor> _Actor = GetLevel()->CreateActor<VortexSphere_Actor>(UpdateOrder::Skill);
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

void VortexSphere::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
	Transform.SetLocalPosition(PlayerPos);
}