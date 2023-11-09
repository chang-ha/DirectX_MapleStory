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

SkillManager* SkillManager::PlayerSkillManager = nullptr;

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

	std::shared_ptr<ContentSkill> Skill = AllSkills[UpperName.data()];
	Skill->On();
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

	std::shared_ptr<ContentSkill> Skill = AllSkills[UpperName.data()];
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

	std::shared_ptr<ContentSkill> Skill = AllSkills[UpperName.data()];
	return Skill->IsSkillUsing();
}


void SkillManager::LevelStart(class GameEngineLevel* _PrevLevel)
{
	PlayerSkillManager = this;
}

void SkillManager::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void SkillManager::Start()
{
	GameEngineGUI::CreateGUIWindow<SkillManagerGUI>("SkillManager");

	CreateSkill<DoubleJump>("DoubleJump");
	CreateSkill<SongOfHeaven>("SongOfHeaven");
	CreateSkill<FairySpiral>("FairySpiral");
	CreateSkill<WindWalk>("WindWalk");
	CreateSkill<HowlingGale>("HowlingGale");
	CreateSkill<Monsoon>("Monsoon");
	CreateSkill<VortexSphere>("VortexSphere");
	CreateSkill<PhalanxCharge>("PhalanxCharge");
	CreateSkill<MercilessWinds>("MercilessWinds");	

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
	QuickSlot->Transform.SetLocalPosition({GlobalValue::WinScale.X, -GlobalValue::WinScale.Y + 10, RenderDepth::ui});
	// QuickSlot->SetAutoScaleRatio(1.1f);

	HitPrintManager = GetLevel()->CreateActor<HitRenderManager>(UpdateOrder::Skill);
}

void SkillManager::Update(float _Delta)
{

}

void SkillManager::Release()
{
	std::map<std::string, std::shared_ptr<ContentSkill>>::iterator StartIter = AllSkills.begin();
	std::map<std::string, std::shared_ptr<ContentSkill>>::iterator EndIter = AllSkills.end();

	for (std::pair<const std::string, std::shared_ptr<ContentSkill>>& _Pair : AllSkills)
	{
		if (nullptr != _Pair.second)
		{
			_Pair.second->Release();
			_Pair.second = nullptr;
		}
	}
}

void SkillManager::SkillInit(std::shared_ptr<ContentSkill> _Skill)
{
	_Skill->Init();
	_Skill->Off();
}