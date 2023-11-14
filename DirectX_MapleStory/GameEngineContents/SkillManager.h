#pragma once
#include "ContentSkill.h"

class SkillManagerGUI : public GameEngineGUIWindow
{
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
};

class SkillInfo : public std::enable_shared_from_this<SkillInfo>
{
	friend class SkillManager;

	std::string IconSpriteName = "";
	// int Key = VK_F24;
	// float* SkillCurCoolDown = nullptr;
	// float* SkillCoolDown = nullptr;
	std::shared_ptr<ContentSkill> Skill = nullptr;

	void SkillInfoUpdate(float _Delta);
};

class QuickSlotFrame
{
	friend class SkillManager;
	std::shared_ptr<GameEngineUIRenderer> QuickSlotBG = nullptr;
	std::vector<std::vector<std::shared_ptr<GameEngineUIRenderer>>> CoolDownAniRenderers;
};

class AlertFrame : public std::enable_shared_from_this<AlertFrame>
{
	friend class SkillManager;
	std::shared_ptr<GameEngineUIRenderer> CoolDownAlertBG = nullptr;
	std::shared_ptr<GameEngineUIRenderer> CoolDownAlertIcon = nullptr;
};

class SkillManager : public GameEngineActor
{
public:
	// constructer destructer
	SkillManager();
	~SkillManager();

	// delete function
	SkillManager(const SkillManager& _Other) = delete;
	SkillManager(SkillManager&& _Other) noexcept = delete;
	SkillManager& operator=(const SkillManager& _Other) = delete;
	SkillManager& operator=(SkillManager&& _Other) noexcept = delete;

	template<typename SkillType>
	void CreateSkill(std::string _SkillName)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_SkillName);
		if (false == AllSkills.contains(UpperName))
		{
			AllSkills[UpperName] = std::make_shared<SkillInfo>();
		}
		std::shared_ptr<ContentSkill> NewSkill = GetLevel()->CreateActor<SkillType>(UpdateOrder::Skill);
		NewSkill->SkillName = UpperName;
		SkillInit(NewSkill);
		AllSkills[UpperName]->Skill = NewSkill;
		// AllSkills[UpperName]->SkillCurCoolDown = &NewSkill->SkillCurCoolDown;
		// AllSkills[UpperName]->SkillCoolDown = &NewSkill->SkillCoolDown;
		// AllSkills[UpperName]->Key = NewSkill->Key;
		AllSkills[UpperName]->IconSpriteName = "Icon_" + _SkillName + ".png";
	}

	void UseSkill(std::string_view _SkillName);
	void EndSkill(std::string_view _SkillName);
	bool IsSkillUsing(std::string_view _SkillName);

protected:
	void LevelStart(class GameEngineLevel* _PrevLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	QuickSlotFrame QuickSlot;
	std::shared_ptr<class HitRenderManager> HitPrintManager;
	std::map<std::string, std::shared_ptr<SkillInfo>> AllSkills;
	std::vector<std::shared_ptr<AlertFrame>> CoolDownAlerts;

	void SkillInit(std::shared_ptr<ContentSkill> _Skill);
	void CheckUseSkill();
	void SkillAlert(std::string_view _IconName);
};

