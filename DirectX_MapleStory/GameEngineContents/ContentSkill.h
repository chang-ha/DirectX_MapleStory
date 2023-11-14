#pragma once
#include "Player.h"

class ContentSkill : public GameEngineActor
{ 
	friend class SkillManager;
	friend class SkillInfo;
public:
	enum InputType
	{
		IsDown = 1, // 비트 연산을 위해 1
		IsPress,
	};

	// constructer destructer
	ContentSkill();
	~ContentSkill();

	// delete function
	ContentSkill(const ContentSkill& _Ohter) = delete;
	ContentSkill(ContentSkill&& _Ohter) noexcept = delete;
	ContentSkill& operator=(const ContentSkill& _Other) = delete;
	ContentSkill& operator=(ContentSkill&& _Other) noexcept = delete;

	virtual void EndSkill()
	{
		IsSkillStart = false;
		IsSkillEnd = true;
	}

	bool IsSkillUsing()
	{
		return true == IsSkillStart && false == IsSkillEnd ? true : false;
	}

	virtual void Init() {}
	virtual void UseSkill();
	void SkillLeftFlip();
	void SkillRightFlip();

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	bool IsSkillStart = false;
	bool IsSkillEnd = true;
	ActorDir PlayerDir = ActorDir::Null;
	float4 PlayerPos = float4::ZERO;
	float4 PlayerScale = float4::ZERO;
	float4 Pivot = float4::ZERO;
	std::shared_ptr<GameEngineSpriteRenderer> SkillRenderer1 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> SkillRenderer2 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> SkillAfterImageRenderer = nullptr;

	std::string SkillName = "";
	int Key = VK_F24; // 초기화용 값
	int InputTypeValue = InputType::IsDown;
	float SkillCurCoolDown = 0.0f;
	float SkillCoolDown = 0.0f;
	int UseState = PlayerState::Null;
	PlayerState ChangeState = PlayerState::Null;
private:
};

