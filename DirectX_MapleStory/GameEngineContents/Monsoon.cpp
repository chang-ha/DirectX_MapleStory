#include "PreCompile.h"
#include "Monsoon.h"

Monsoon::Monsoon()
{
	
}

Monsoon::~Monsoon()
{

}

void Monsoon::UseSkill()
{
	ContentSkill::UseSkill();
}

void Monsoon::EndSkill()
{
	ContentSkill::EndSkill();
}

void Monsoon::Start()
{
	ContentSkill::Start();

	if (nullptr == GameEngineSprite::Find("Monsoon_Ready"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\Monsoon");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Monsoon_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	SkillRenderer1->CreateAnimation("Effect", "Monsoon_Effect", 0.9f);
	// Screen 및 Collision은 화면을 기준으로 나오고 충돌하기 때문에 추후 UI만들어지면 추가할 것
	SkillRenderer2->CreateAnimation("Screen", "Monsoon_Screen", 0.9f);
}

void Monsoon::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
}
