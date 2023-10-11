#pragma once

struct HitRenderData
{
	friend class SkillManager;
private:
	bool AniEnd = false;
	int CurIndex = 0;
	float DelayTime = 0.0f;
	GameEngineObject* Object = nullptr;
	std::vector<float4> RandomPivot;
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> HitAnimations;
	// std::vector<std::shared_ptr<GameEngineSpriteRenderer>> DamageAnimations;
	// Sound 추후 추가
};

class SkillManager : public GameEngineActor
{
public:
	static SkillManager* PlayerSkillManager;
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

	void HitPrint(std::string_view _HitSpriteName, size_t _HitCount, GameEngineObject* _Object, bool _RandomPivot = true, PivotType _PivotType = PivotType::Bottom);

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
	std::map<std::string, std::shared_ptr<class ContentSkill>> AllSkills;
	std::list<std::shared_ptr<HitRenderData>> AllHitRenderers;
 
	void SkillInit(std::shared_ptr<class ContentSkill> _Skill);
	void HitPrintUpdate(float _Delta);
};

