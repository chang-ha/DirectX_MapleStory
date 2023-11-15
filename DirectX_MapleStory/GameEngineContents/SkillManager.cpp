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

	if (nullptr == GameEngineSprite::Find("CoolDown_001.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\QuickSlot\\CoolDownAni");
		std::vector<GameEngineFile> Directorys = Dir.GetAllFile();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineFile& ChildFile = Directorys[i];
			GameEngineTexture::Load(ChildFile.GetStringPath());
			GameEngineSprite::CreateSingle(ChildFile.GetFileName());
		}
	}

	if (nullptr == GameEngineSprite::Find("CoolDownNum_0.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\QuickSlot\\CoolDownNum");
		std::vector<GameEngineFile> Directorys = Dir.GetAllFile();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineFile& ChildFile = Directorys[i];
			GameEngineTexture::Load(ChildFile.GetStringPath());
			GameEngineSprite::CreateSingle(ChildFile.GetFileName());
		}
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

	QuickSlotCoolDownCreate('Q', 1, 0);
	QuickSlotCoolDownCreate('W', 2, 0);
	QuickSlotCoolDownCreate('E', 3, 0);
	QuickSlotCoolDownCreate('R', 4, 0);
	QuickSlotCoolDownCreate('S', 2, 1);
	QuickSlotCoolDownCreate('F', 4, 1);

	HitPrintManager = GetLevel()->CreateActor<HitRenderManager>(UpdateOrder::Skill);

	GameEngineInput::AddInputObject(this);
}

void SkillManager::Update(float _Delta)
{
	AlertUpdate(_Delta);
	QuickSlotUpdate(_Delta);
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

	QuickSlot.QuickSlotBG->Death();
	for (std::pair<const int, std::shared_ptr<CoolDownFrame>>& _Pair : QuickSlot.CoolDownAniRenderers)
	{
		if (nullptr != _Pair.second)
		{
			_Pair.second->CoolDown_AniRenderer->Death();
			_Pair.second->CoolDown_TenNumRenderer->Death();
			_Pair.second->CoolDown_OneNumRenderer->Death();

			_Pair.second->CoolDown_AniRenderer = nullptr;
			_Pair.second->CoolDown_TenNumRenderer = nullptr;
			_Pair.second->CoolDown_OneNumRenderer = nullptr;
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

void SkillManager::QuickSlotCoolDownCreate(int _Key, int _Index_X, int _Index_Y)
{
	std::shared_ptr<CoolDownFrame> Frame = std::make_shared<CoolDownFrame>();

	Frame->CoolDown_AniRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Frame->CoolDown_AniRenderer->AutoSpriteSizeOn();
	Frame->CoolDown_AniRenderer->SetSprite("CoolDown_015.png");
	Frame->CoolDown_AniRenderer->Transform.SetLocalPosition({ GlobalValue::WinScale.X - 18 - 35 * (9 - _Index_X), -GlobalValue::WinScale.Y - 6 + 35 * (2 - _Index_Y), RenderDepth::ui });
	Frame->OnlyOneNumPos = { GlobalValue::WinScale.X - 18 - 35 * (9 - _Index_X), -GlobalValue::WinScale.Y - 6 + 35 * (2 - _Index_Y), RenderDepth::ui };

	Frame->CoolDown_OneNumRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Frame->CoolDown_OneNumRenderer->AutoSpriteSizeOn();
	Frame->CoolDown_OneNumRenderer->SetSprite("CoolDownNum_0.png");
	Frame->CoolDown_OneNumRenderer->Transform.SetLocalPosition({ GlobalValue::WinScale.X - 14 - 35 * (9 - _Index_X), -GlobalValue::WinScale.Y - 6 + 35 * (2 - _Index_Y), RenderDepth::ui });
	Frame->CoolDown_OneNumRenderer->Off();
	Frame->OneNumPos = { GlobalValue::WinScale.X - 14 - 35 * (9 - _Index_X), -GlobalValue::WinScale.Y - 6 + 35 * (2 - _Index_Y), RenderDepth::ui };

	Frame->CoolDown_TenNumRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Frame->CoolDown_TenNumRenderer->AutoSpriteSizeOn();
	Frame->CoolDown_TenNumRenderer->SetSprite("CoolDownNum_0.png");
	Frame->CoolDown_TenNumRenderer->Transform.SetLocalPosition({ GlobalValue::WinScale.X - 22 - 35 * (9 - _Index_X), -GlobalValue::WinScale.Y - 6 + 35 * (2 - _Index_Y), RenderDepth::ui });
	Frame->CoolDown_TenNumRenderer->Off();

	QuickSlot.CoolDownAniRenderers[_Key] = Frame;
}

void SkillManager::QuickSlotUpdate(float _Delta)
{
	// CurCoolDowm/CoolDown -> 0 ~ 1사이 값
	// * 16 -> 0 ~ 16사이 값
	// 16 - 결과값
	for (std::pair<const std::string, std::shared_ptr<SkillInfo>>& _Pair : AllSkills)
	{
		if (false == QuickSlot.CoolDownAniRenderers.contains(_Pair.second->Key))
		{
			continue;
		}
		std::shared_ptr<CoolDownFrame> Frame = QuickSlot.CoolDownAniRenderers[_Pair.second->Key];
		std::shared_ptr<ContentSkill> CurSkill = _Pair.second->Skill;
		float RemainCoolRatio = CurSkill->SkillCurCoolDown / CurSkill->SkillCoolDown;
		int SpriteNum = static_cast<int>((1 - RemainCoolRatio) * 15);

		if (10 > SpriteNum)
		{
			Frame->CoolDown_AniRenderer->SetSprite("CoolDown_00" + std::to_string(SpriteNum) + ".png");
		}
		else
		{
			Frame->CoolDown_AniRenderer->SetSprite("CoolDown_0" + std::to_string(SpriteNum) + ".png");
		}

		int RemainCoolInt = static_cast<int>(CurSkill->SkillCurCoolDown);
		if (10 > RemainCoolInt)
		{
			if (true == Frame->CoolDown_TenNumRenderer->IsUpdate())
			{
				Frame->CoolDown_TenNumRenderer->Off();
				Frame->CoolDown_OneNumRenderer->Transform.SetLocalPosition(Frame->OnlyOneNumPos);
			}

			if (5 > RemainCoolInt && true == true == Frame->CoolDown_OneNumRenderer->IsUpdate())
			{
				Frame->CoolDown_OneNumRenderer->Off();
				continue;
			}

			Frame->CoolDown_OneNumRenderer->SetSprite("CoolDownNum_" + std::to_string(RemainCoolInt) + ".png");
		}
		else
		{
			if (false == Frame->CoolDown_TenNumRenderer->IsUpdate())
			{
				Frame->CoolDown_TenNumRenderer->On();
				Frame->CoolDown_OneNumRenderer->On();
			}

			int TenNum = RemainCoolInt / 10;
			int OneNum = RemainCoolInt % 10;

			Frame->CoolDown_TenNumRenderer->SetSprite("CoolDownNum_" + std::to_string(TenNum) + ".png");
			Frame->CoolDown_OneNumRenderer->SetSprite("CoolDownNum_" + std::to_string(OneNum) + ".png");
		}
	}
}
