#include "PreCompile.h"
#include "HowlingGale.h"
#include "HowlingGale_Actor.h"

#define ANI_SPEED 0.09f

HowlingGale::HowlingGale()
{
	
}

HowlingGale::~HowlingGale()
{

}

void HowlingGale::UseSkill()
{
	ContentSkill::UseSkill();
	On();
	SkillRenderer1->On();

	SkillRenderer1->ChangeAnimation("Effect", true);
}

void HowlingGale::EndSkill()
{
	ContentSkill::EndSkill();
	Off();
}

void HowlingGale::Start()
{
	ContentSkill::Start();

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentResources");
	Dir.MoveChild("ContentResources\\Textures\\Skill\\HowlingGale");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Childs = Directorys[i];
		GameEngineSprite::CreateFolder("HowlingGale_" + Childs.GetFileName(), Childs.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("Ready_Stack1"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\HowlingGale_Actor");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t y = 0; y < Directorys.size(); y++)
		{
			std::vector<GameEngineDirectory> Directory = Directorys[y].GetAllDirectory();
			for (size_t i = 0; i < Directory.size(); i++)
			{
				GameEngineDirectory& Childs = Directory[i];
				GameEngineSprite::CreateFolder(Childs.GetFileName() + "_Stack" + std::to_string(y + 1), Childs.GetStringPath());
			}
		}
	}

	SkillRenderer1->CreateAnimation("Effect", "HowlingGale_Effect", ANI_SPEED);
	SkillRenderer1->AutoSpriteSizeOn();
	SkillRenderer1->SetPivotValue(float4(0.38f, 0.58f));
	
	SkillRenderer1->SetStartEvent("Effect", [&](GameEngineRenderer* _Renderer)
		{
			if (nullptr != HowlingGale_Actor::MainHowlingGale)
			{
				HowlingGale_Actor::MainHowlingGale->ChangeState(HowlingGaleState::Death);
			}
		}
	);
	SkillRenderer1->SetEndEvent("Effect", [&](GameEngineRenderer* _Renderer)
		{
			SkillRenderer1->Off();
			GetLevel()->CreateActor<HowlingGale_Actor>(UpdateOrder::Skill);
			HowlingGale_Actor::MainHowlingGale->Transform.SetLocalPosition(PlayerPos);
		}
	);
}

void HowlingGale::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
	Transform.SetLocalPosition(PlayerPos);
}