#include "PreCompile.h"
#include "VortexSphere.h"

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
	SkillRenderer1->ChangeAnimation("Effect1");
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

	SkillRenderer1->CreateAnimation("Effect1", "VortexSphere_Effect1");
	SkillRenderer2->CreateAnimation("Effect2", "VortexSphere_Effect2");

	SkillRenderer1->SetFrameEvent("Effect1", 5, [&](GameEngineSpriteRenderer* _Renderer)
		{
			SkillRenderer2->On();
			SkillRenderer2->ChangeAnimation("Effect2");
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
}