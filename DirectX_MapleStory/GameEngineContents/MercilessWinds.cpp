﻿#include "PreCompile.h"

#include "MercilessWinds.h"
#include "MercilessWinds_Actor.h"
#include "ContentLevel.h"

float MercilessWinds::WholeCoolDown = 0.0f;

MercilessWinds::MercilessWinds()
{

}

MercilessWinds::~MercilessWinds()
{

}

void MercilessWinds::UseSkill()
{
	ContentSkill::UseSkill();
	On();
	SkillRenderer1->On();

	switch (PlayerDir)
	{
	case ActorDir::Right:
		SkillRenderer1->LeftFlip();
		break;
	case ActorDir::Left:
		SkillRenderer1->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	SkillRenderer1->ChangeAnimation("Effect1", true);

	SkillPlayer = GameEngineSound::SoundPlay("MercilessWinds_Use.mp3");
	SkillPlayer.SetVolume(GlobalValue::SkillVolume);
}

void MercilessWinds::EndSkill()
{
	ContentSkill::EndSkill();
	Off();
	SkillRenderer1->Off();
}

void MercilessWinds::Start()
{
	AllWindActor.reserve(8);
	ContentSkill::Start();
	SkillRenderer1->SetRenderOrder(RenderOrder::PLAYBELOW);
	SkillRenderer1->Transform.SetLocalPosition({0, 0, RenderDepth::playbelow});

	if (nullptr == GameEngineSprite::Find("MercilessWinds_Effect1"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\MercilessWinds");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("MercilessWinds_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	if (nullptr == GameEngineSound::FindSound("MercilessWinds_Use.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\Skill\\");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "MercilessWinds_Use.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "MercilessWinds_Hit.mp3");
	}

	SkillRenderer1->CreateAnimation("Effect1", "MercilessWinds_Effect1", 0.06f);
	SkillRenderer1->SetPivotValue({0.5f, 0.6f});
	SkillRenderer1->AutoSpriteSizeOn();
	SkillRenderer1->Off();

	// 한 프레임에서 여러 객체 만들면 느려져서 프레임마다 2객체씩 만드는 방법을 채택
	for (int i = 0; i < 7; i++)
	{
		SkillRenderer1->SetFrameEvent("Effect1", i, [&](GameEngineRenderer* _Renderer)
			{
				CreateWind();
				CreateWind();
			}
		);
	}

	SkillRenderer1->SetFrameEvent("Effect1", 8 ,[&](GameEngineRenderer* _Renderer)
		{
			for (size_t i = 0; i < AllWindActor.size(); i++)
			{
				AllWindActor[i]->On();
			}
		}
	);

	SkillRenderer1->SetEndEvent("Effect1", [&](GameEngineRenderer* _Renderer)
		{
			EndSkill();
		}
	);

	SkillCurCoolDown = WholeCoolDown;
}

void MercilessWinds::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
	PlayerPos.Z = RenderDepth::playbelow;
	SkillRenderer1->Transform.SetLocalPosition(PlayerPos);
}

void MercilessWinds::CreateWind()
{
	std::shared_ptr<MercilessWinds_Actor> _Actor = ContentLevel::CurContentLevel->CreateActor<MercilessWinds_Actor>(UpdateOrder::Skill);
	AllWindActor.push_back(_Actor);
}

void MercilessWinds::Release()
{
	ContentSkill::Release();
	WholeCoolDown = SkillCurCoolDown;
}


void MercilessWinds::Init()
{
	Key = 'R';
	InputTypeValue = InputType::IsDown;
	SkillCoolDown = 1.0f;
	UseState = PlayerState::Idle | PlayerState::Alert | PlayerState::Walk | PlayerState::Jump;
	ChangeState = PlayerState::MercilessWinds;
}
