#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "SkillManager.h"
#include "ContentSkill.h"
#include "DoubleJump.h"
#include "SongOfHeaven.h"
#include "FairySpiral.h"
#include "WindWalk.h"
#include "HowlingGale.h"
#include "Monsoon.h"
#include "VortexSphere.h"
#include "PhalanxCharge.h"
#include "MercilessWinds.h"
#include "BaseWindActor.h"
#include "ContentActor.h"
#include "Player.h"
#include "HitRenderManager.h"

void SkillManagerGUI::Start()
{

}

void SkillManagerGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::SliderFloat("SkillEffect", &GlobalValue::SkillEffectAlpha, 0.2f, 1.0f);
}

void QuickSlotFrame::CreateCoolDownRenderers(int _Key)
{
}

SkillManager::SkillManager()
{

}

SkillManager::~SkillManager()
{

}

void SkillManager::UseSkill(std::string_view _SkillName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SkillName);
	if (false == AllSkills.contains(UpperName.data()))
	{
		MsgBoxAssert("존재하지 않는 스킬을 사용하려고 했습니다.");
		return;
	}

	if (0.0f < AllSkills[UpperName.data()]->Skill->SkillCurCoolDown)
	{
		return;
	}

	int UseState = AllSkills[UpperName.data()]->Skill->UseState;
	if (0 == (Player::MainPlayer->GetState() & UseState))
	{
		return;
	}

	std::shared_ptr<ContentSkill> Skill = AllSkills[UpperName.data()]->Skill;

	Skill->On();

	if (PlayerState::Null != AllSkills[UpperName.data()]->Skill->ChangeState)
	{
		Player::MainPlayer->ChangeState(AllSkills[UpperName.data()]->Skill->ChangeState);
	}

	Skill->UseSkill();
}

void SkillManager::EndSkill(std::string_view _SkillName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SkillName);
	if (false == AllSkills.contains(UpperName.data()))
	{
		MsgBoxAssert("존재하지 않는 스킬을 끝내려고 했습니다.");
		return;
	}

	std::shared_ptr<ContentSkill> Skill = AllSkills[UpperName.data()]->Skill;
	Skill->EndSkill();
}

bool SkillManager::IsSkillUsing(std::string_view _SkillName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SkillName);
	if (false == AllSkills.contains(UpperName.data()))
	{
		MsgBoxAssert("존재하지 않는 스킬을 사용중인지 확인하려고 했습니다.");
		return false;
	}

	std::shared_ptr<ContentSkill> Skill = AllSkills[UpperName.data()]->Skill;
	return Skill->IsSkillUsing();
}

void SkillManager::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Release();
	Death();
}

void SkillManager::Start()
{
	GameEngineGUI::CreateGUIWindow<SkillManagerGUI>("SkillManager");

	CreateSkill<class DoubleJump>("DoubleJump");
	CreateSkill<class SongOfHeaven>("SongOfHeaven");
	CreateSkill<class FairySpiral>("FairySpiral");
	CreateSkill<class WindWalk>("WindWalk");
	CreateSkill<class HowlingGale>("HowlingGale");
	CreateSkill<class Monsoon>("Monsoon");
	CreateSkill<class VortexSphere>("VortexSphere");
	CreateSkill<class PhalanxCharge>("PhalanxCharge");
	CreateSkill<class MercilessWinds>("MercilessWinds");

	if (nullptr == GameEngineSprite::Find("QuickSlot.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\QuickSlot\\QuickSlot.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("CoolDownAni"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\QuickSlot\\CoolDownAni");
		GameEngineSprite::CreateFolder("CoolDownAni", Dir.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("CoolDownAlert"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\QuickSlot\\CoolDownAlert");
		GameEngineSprite::CreateFolder("CoolDownAlert", Dir.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("Icon_DoubleJump.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\QuickSlot\\SkillIcon");
		std::vector<GameEngineFile> Directorys = Dir.GetAllFile();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineFile& ChildFile = Directorys[i];
			GameEngineTexture::Load(ChildFile.GetStringPath());
			GameEngineSprite::CreateSingle(ChildFile.GetFileName());
		}
	}

	CoolDownAlerts.resize(6);
	for (size_t i = 0; i < CoolDownAlerts.size(); i++)
	{
		std::shared_ptr<AlertFrame> Frame = std::make_shared<AlertFrame>();
		Frame->CoolDownAlertBG = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		Frame->CoolDownAlertBG->SetPivotType(PivotType::Right);
		Frame->CoolDownAlertBG->AutoSpriteSizeOn();
		Frame->CoolDownAlertBG->Off();
		Frame->CoolDownAlertIcon = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		Frame->CoolDownAlertIcon->AutoSpriteSizeOn();
		Frame->CoolDownAlertIcon->Off();
		Frame->CoolDownAlertBG->CreateAnimation("Alert", "CoolDownAlert", 0.09f, -1, -1, false);
		Frame->CoolDownAlertBG->ChangeAnimation("Alert");

		std::shared_ptr<GameEngineFrameAnimation> _Ani = Frame->CoolDownAlertBG->FindAnimation("Alert");
		_Ani->Inter[2] = 1.5f;

		Frame->CoolDownAlertBG->SetFrameEvent("Alert", 2, [=](GameEngineSpriteRenderer* _Renderer)
			{
				Frame->CoolDownAlertIcon->On();
			});

		Frame->CoolDownAlertBG->SetFrameEvent("Alert", 3, [=](GameEngineSpriteRenderer* _Renderer)
			{
				Frame->CoolDownAlertIcon->Off();
			});

		Frame->CoolDownAlertBG->SetEndEvent("Alert", [=](GameEngineSpriteRenderer* _Renderer)
			{
				Frame->CoolDownAlertBG->Off();
			});

		Frame->CoolDownAlertBG->Transform.SetLocalPosition({ GlobalValue::WinScale.X, -GlobalValue::WinScale.Y + 80 * (i + 2), RenderDepth::ui });
		Frame->CoolDownAlertIcon->Transform.SetLocalPosition({ GlobalValue::WinScale.X - 156, -GlobalValue::WinScale.Y + 80 * (i + 2), RenderDepth::ui });

		CoolDownAlerts[i] = Frame;
	}

	QuickSlot.QuickSlotBG = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	QuickSlot.QuickSlotBG->SetPivotType(PivotType::RightBottom);
	QuickSlot.QuickSlotBG->SetSprite("QuickSlot.png");
	QuickSlot.QuickSlotBG->AutoSpriteSizeOn();
	QuickSlot.QuickSlotBG->Transform.SetLocalPosition({ GlobalValue::WinScale.X, -GlobalValue::WinScale.Y + 10, RenderDepth::ui });

	//QuickSlot.CoolDownAniRenderers.resize(2);
	//for (size_t i = 0; i < QuickSlot.CoolDownAniRenderers.size(); i++)
	//{
	//	QuickSlot.CoolDownAniRenderers[i].reserve(10);
	//}

	//for (size_t j = 0; j < QuickSlot.CoolDownAniRenderers.size(); j++)
	//{
	//	for (size_t i = 0; i < QuickSlot.CoolDownAniRenderers[j].capacity(); i++)
	//	{
	//		std::shared_ptr<GameEngineUIRenderer> _CoolDownRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	//		_CoolDownRenderer->AutoSpriteSizeOn();
	//		_CoolDownRenderer->CreateAnimation("CoolDownStart", "CoolDownAni", 10.0f, -1, -1, false);
	//		_CoolDownRenderer->ChangeAnimation("CoolDownStart");
	//		_CoolDownRenderer->Transform.SetLocalPosition({ GlobalValue::WinScale.X - 18 -  35 * (9 - i), -GlobalValue::WinScale.Y - 8 + 36 * (2 - j), RenderDepth::ui});
	//		QuickSlot.CoolDownAniRenderers[j].push_back(_CoolDownRenderer);
	//	}
	//}m

	std::vector<int> Keys = {'W', 'E', 'R', 'S', 'F'};

	QuickSlot.CoolDownAniRenderers['Q'] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);


	HitPrintManager = GetLevel()->CreateActor<HitRenderManager>(UpdateOrder::Skill);

	GameEngineInput::AddInputObject(this);
}

void SkillManager::Update(float _Delta)
{
	AlertUpdate(_Delta);
	CheckUseSkill();
}

void SkillManager::Release()
{
	// std::map<std::string, std::shared_ptr<ContentSkill>>::iterator StartIter = AllSkills.begin();
	// std::map<std::string, std::shared_ptr<ContentSkill>>::iterator EndIter = AllSkills.end();

	for (std::pair<const std::string, std::shared_ptr<SkillInfo>>& _Pair : AllSkills)
	{
		if (nullptr != _Pair.second)
		{
			_Pair.second->Skill->Release();
			_Pair.second->Skill = nullptr;
			_Pair.second = nullptr;
		}
	}

	for (size_t i = 0; i < CoolDownAlerts.size(); i++)
	{
		if (nullptr != CoolDownAlerts[i]->CoolDownAlertBG)
		{
			CoolDownAlerts[i]->CoolDownAlertBG->Death();
			CoolDownAlerts[i]->CoolDownAlertIcon->Death();

			CoolDownAlerts[i]->CoolDownAlertBG = nullptr;
			CoolDownAlerts[i]->CoolDownAlertIcon = nullptr;
		}
	}

	AllSkills.clear();
}

void SkillManager::SkillInit(std::shared_ptr<ContentSkill> _Skill)
{
	_Skill->Init();
	_Skill->Off();
}

void SkillManager::CheckUseSkill()
{
	for (std::pair<const std::string, std::shared_ptr<SkillInfo>>& _Pair : AllSkills)
	{
		switch (_Pair.second->Skill->InputTypeValue)
		{
		case ContentSkill::InputType::IsDown:
		{
			if (true == GameEngineInput::IsDown(_Pair.second->Skill->Key, this))
			{
				UseSkill(_Pair.second->Skill->SkillName);
			}
			break;
		}
		case ContentSkill::InputType::IsPress:
		{
			if (true == GameEngineInput::IsPress(_Pair.second->Skill->Key, this))
			{
				UseSkill(_Pair.second->Skill->SkillName);
			}
			break;
		}
		case ContentSkill::InputType::IsDown | ContentSkill::InputType::IsPress:
		{
			if (true == GameEngineInput::IsDown(_Pair.second->Skill->Key, this) ||
				true == GameEngineInput::IsPress(_Pair.second->Skill->Key, this))
			{
				UseSkill(_Pair.second->Skill->SkillName);
			}
			break;
		}
		default:
			break;
		}
	}
}

void SkillManager::AlertUpdate(float _Delta)
{
	for (std::pair<const std::string, std::shared_ptr<SkillInfo>>& _Pair : AllSkills)
	{
		if (0 == _Pair.second->Skill->SkillCurCoolDown)
		{
			continue;
		}

		_Pair.second->Skill->SkillCurCoolDown -= _Delta;
		if (0 == _Pair.second->Skill->SkillCoolDown)
		{
			continue;
		}

		if (0 >= _Pair.second->Skill->SkillCurCoolDown)
		{
			_Pair.second->Skill->SkillCurCoolDown = 0.0f;
			SkillAlert(_Pair.second->IconSpriteName);
		}
	}
}

void SkillManager::SkillAlert(std::string_view _IconName)
{
	for (size_t i = 0; i < CoolDownAlerts.size(); i++)
	{
		if (true == CoolDownAlerts[i]->CoolDownAlertBG->IsUpdate())
		{
			continue;
		}
		CoolDownAlerts[i]->CoolDownAlertBG->On();

		CoolDownAlerts[i]->CoolDownAlertBG->ChangeAnimation("Alert", true, 0);
		CoolDownAlerts[i]->CoolDownAlertIcon->SetSprite(_IconName);
		return;
	}
}
