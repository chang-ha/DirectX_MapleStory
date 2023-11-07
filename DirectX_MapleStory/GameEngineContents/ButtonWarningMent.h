#pragma once

#define MOVEPOS_X 50.0f
#define MOVEPOS_Y 50.0f

class OneButtonWarningMentStruct : public std::enable_shared_from_this<OneButtonWarningMentStruct>
{
	friend class ButtonWarningMent;
protected:
	bool AlphaUpdateValue = true;
	bool IsClickOff = false;
	float AlphaSpeed = 5.0f;
	ButtonWarningMent* Parent;
	std::shared_ptr<GameEngineSpriteRenderer> MentBG = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Ment = nullptr;
	std::shared_ptr<class ContentButton> CancelButton = nullptr;

	virtual void StructStart(ButtonWarningMent* _Parent);
	virtual void AlphaUpdate(float _Delta);
	virtual void DeathUpdate(float _Delta);
private:
};

class TwoButtonWarningMentStruct : public OneButtonWarningMentStruct
{
	friend class ButtonWarningMent;

	std::shared_ptr<class ContentButton> OkButton = nullptr;

	void StructStart(ButtonWarningMent* _Parent) override;
	void DeathUpdate(float _Delta) override;
	void AlphaUpdate(float _Delta) override;
};

class ButtonWarningMent : public GameEngineActor
{
public:
	// constructer destructer
	ButtonWarningMent();
	~ButtonWarningMent();

	// delete function
	ButtonWarningMent(const ButtonWarningMent& _Ohter) = delete;
	ButtonWarningMent(ButtonWarningMent&& _Ohter) noexcept = delete;
	ButtonWarningMent& operator=(const ButtonWarningMent& _Other) = delete;
	ButtonWarningMent& operator=(ButtonWarningMent&& _Other) noexcept = delete;

	void Init(std::string_view _BGName, std::string_view _WarningMentName);

	static std::shared_ptr<ButtonWarningMent> CreateOneButtonMent();
	static std::shared_ptr<ButtonWarningMent> CreateTwoButtonMent();
	
protected:
	float MoveSpeed = 200.0f;
	float RemainMoveX = MOVEPOS_X;
	float RemainMoveY = MOVEPOS_Y;
	std::shared_ptr<OneButtonWarningMentStruct> MentObject;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	void MoveUpdate(float _Delta);
};

