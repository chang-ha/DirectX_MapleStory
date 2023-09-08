#include "PreCompile.h"
#include "DoubleJump.h"

DoubleJump::DoubleJump()
{

}

DoubleJump::~DoubleJump()
{

}
void DoubleJump::Init()
{
	int a = 0;
}

void DoubleJump::UseSkill()
{
	int a = 0;
}

void DoubleJump::Start() 
{
	ContentSkill::Start();

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentResources");
	Dir.MoveChild("ContentResources\\Textures\\Skill\\DoubleJump");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Childs = Directorys[i];
		GameEngineSprite::CreateFolder(Childs.GetStringPath());
	}

	SkillRenderer1->CreateAnimation("Effect1", "Effect1");
	SkillRenderer1->CreateAnimation("Up_Effect1", "Up_Effect1");
	SkillRenderer2->CreateAnimation("Effect2", "Effect2");
	SkillRenderer2->CreateAnimation("Up_Effect2", "Up_Effect2");
	SkillAfterImageRenderer->CreateAnimation("AfterImage", "AfterImage");
}

void DoubleJump::Update(float _Delta)
{

}

