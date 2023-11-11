#pragma once

class SkillManagerGUI : public GameEngineGUIWindow
{
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
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
		std::shared_ptr<class ContentSkill> NewSkill = GetLevel()->CreateActor<SkillType>(UpdateOrder::Skill);
		if (false == AllSkills.contains(UpperName))
		{
			AllSkills[UpperName] = std::shared_ptr<class ContentSkill>();
		}
		AllSkills[UpperName] = NewSkill;
		SkillInit(NewSkill);
	}


	void UseSkill(std::string_view _SkillName);
	void EndSkill(std::string_view _SkillName);
	bool IsSkillUsing(std::string_view _SkillName);
	void Release() override;

protected:
	void LevelStart(class GameEngineLevel* _PrevLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineUIRenderer> QuickSlot;
	std::shared_ptr<class HitRenderManager> HitPrintManager;
	std::map<std::string, std::shared_ptr<class ContentSkill>> AllSkills;
 
	void SkillInit(std::shared_ptr<class ContentSkill> _Skill);
};

