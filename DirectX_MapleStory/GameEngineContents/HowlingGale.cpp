#include "PreCompile.h"
#include "HowlingGale.h"
#include "HowlingGale_Actor.h"

#define ANI_SPEED 0.08f
float HowlingGale::WholeCoolDown = 0.0f;

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

	SkillPlayer = GameEngineSound::SoundPlay("HowlingGale_Use.mp3");
	SkillPlayer.SetVolume(GlobalValue::SkillVolume);

	if (true == GameEngineInput::IsPress(VK_DOWN, this))
	{
		_SummonStack = HowlingStack::Stack2;
	}
	else
	{
		_SummonStack = HowlingStack::Stack1;
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

	GameEngineInput::AddInputObject(this);

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
		Dir.MoveChild("ContentResources\\Textures\\Skill\\HowlingGale_Actor\\Stack1");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder(Childs.GetFileName() + "_Stack1", Childs.GetStringPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("Ready_Stack2"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\HowlingGale_Actor\\Stack2");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder(Childs.GetFileName() + "_Stack2", Childs.GetStringPath());
		}
	}

	if (nullptr == GameEngineSound::FindSound("HowlingGale_Use.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\Skill\\");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "HowlingGale_Use.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "HowlingGale_Loop.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "HowlingGale_Death.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "HowlingGale_Hit.mp3");
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
			_Actor->Init(_SummonStack);
		});

	SkillRenderer1->SetEndEvent("Effect", [&](GameEngineRenderer* _Renderer)
		{
			EndSkill();
		});

	SkillCurCoolDown = WholeCoolDown;
}

void HowlingGale::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
	Transform.SetLocalPosition(PlayerPos);
}

void HowlingGale::Release()
{
	ContentSkill::Release();
	WholeCoolDown = SkillCurCoolDown;
}

void HowlingGale::Init()
{
	Key = 'F';
	InputTypeValue = InputType::IsDown;
	SkillCoolDown = 20.0f;
	UseState = PlayerState::Idle | PlayerState::Alert | PlayerState::Walk | PlayerState::Down;
	ChangeState = PlayerState::HowlingGale;
}