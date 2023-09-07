#pragma once

class SkillManager : public GameEngineActor
{
public:
	static SkillManager* PlayerSkillManager;
public:
	// constructer destructer
	SkillManager();
	~SkillManager();

	// delete function
	SkillManager(const SkillManager& _Ohter) = delete;
	SkillManager(SkillManager&& _Ohter) noexcept = delete;
	SkillManager& operator=(const SkillManager& _Other) = delete;
	SkillManager& operator=(SkillManager&& _Other) noexcept = delete;

	template<typename SkillType>
	void CreateSkill(std::string _SkillName)
	{
		std::shared_ptr<class ContentSkill> NewSkill = std::make_shared<SkillType>();
		if (false == AllSkills.contains(_SkillName))
		{
			AllSkills[_SkillName] = std::shared_ptr<class ContentSkill>();
		}
		AllSkills[_SkillName] = NewSkill;
		SkillInit(NewSkill);
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::map<std::string, std::shared_ptr<class ContentSkill>> AllSkills;

	void SkillInit(std::shared_ptr<class ContentSkill> _Skill);
};

