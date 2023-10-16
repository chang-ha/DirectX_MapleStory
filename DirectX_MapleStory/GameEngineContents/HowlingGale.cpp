#include "PreCompile.h"
#include "HowlingGale.h"
#include "HowlingGale_Actor.h"

#define ANI_SPEED 0.08f

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

	switch (PlayerDir)
	{
	case ActorDir::Right:
		SkillRenderer1->LeftFlip();
		SkillRenderer1->SetPivotValue(float4(0.62f, 0.58f));
		break;
	case ActorDir::Left:
		SkillRenderer1->RightFlip();
		SkillRenderer1->SetPivotValue(float4(0.38f, 0.58f));
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void HowlingGale::EndSkill()
{
	ContentSkill::EndSkill();
	Off();
	SkillRenderer1->Off();
}

void HowlingGale::Start()
{
	ContentSkill::Start();

	if (nullptr == GameEngineSprite::Find("HowlingGale_Effect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\HowlingGale");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("HowlingGale_" + Childs.GetFileName(), Childs.GetStringPath());
		}

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
	
	SkillRenderer1->SetStartEvent("Effect", [&](GameEngineRenderer* _Renderer)
		{
			if (nullptr != HowlingGale_Actor::MainHowlingGale)
			{
				HowlingGale_Actor::MainHowlingGale->MainSpriteRenderer->ChangeAnimation("Death");
			}
		}
	);

	SkillRenderer1->SetFrameEvent("Effect", 10, [&](GameEngineRenderer* _Renderer)
		{
			std::shared_ptr<HowlingGale_Actor> _Actor = GetLevel()->CreateActor<HowlingGale_Actor>(UpdateOrder::Skill);
			_Actor->Transform.SetLocalPosition(PlayerPos);
			_Actor->SetDir(PlayerDir);
		});

	SkillRenderer1->SetEndEvent("Effect", [&](GameEngineRenderer* _Renderer)
		{
			EndSkill();
		});
}

void HowlingGale::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
	Transform.SetLocalPosition(PlayerPos);
}