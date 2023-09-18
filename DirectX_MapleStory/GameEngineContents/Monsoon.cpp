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
	// Screen �� Collision�� ȭ���� �������� ������ �浹�ϱ� ������ ���� UI��������� �߰��� ��
	SkillRenderer2->CreateAnimation("Screen", "Monsoon_Screen", 0.9f);
}

void Monsoon::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
}
