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

void SkillInfo::SkillInfoUpdate(float _Delta)
{
	Skill->SkillCurCoolDown -= _Delta;
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
		MsgBoxAssert("�������� �ʴ� ��ų�� ����Ϸ��� �߽��ϴ�.");
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
		MsgBoxAssert("�������� �ʴ� ��ų�� �������� �߽��ϴ�.");
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
		MsgBoxAssert("�������� �ʴ� ��ų�� ��������� Ȯ���Ϸ��� �߽��ϴ�.");
		return false;
	}

	std::shared_ptr<ContentSkill> Skill = AllSkills[UpperName.data()]->Skill;
	return Skill->IsSkillUsing();
}


void SkillManager::LevelStart(class GameEngineLevel* _PrevLevel)
{

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

	QuickSlot = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	QuickSlot->SetPivotType(PivotType::RightBottom);
	QuickSlot->SetSprite("QuickSlot.png");
	QuickSlot->AutoSpriteSizeOn();
	QuickSlot->Transform.SetLocalPosition({ GlobalValue::WinScale.X, -GlobalValue::WinScale.Y + 10, RenderDepth::ui });
	// QuickSlot->SetAutoScaleRatio(1.1f);

	HitPrintManager = GetLevel()->CreateActor<HitRenderManager>(UpdateOrder::Skill);

	GameEngineInput::AddInputObject(this);
}

void SkillManager::Update(float _Delta)
{
	for (std::pair<const std::string, std::shared_ptr<SkillInfo>>& _Pair : AllSkills)
	{
		_Pair.second->SkillInfoUpdate(_Delta);
	}
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
