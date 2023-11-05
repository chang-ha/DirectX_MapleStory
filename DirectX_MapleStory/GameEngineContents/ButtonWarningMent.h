#pragma once

class ButtonWarningMentStruct
{
	friend class ButtonWarningMent;

	std::shared_ptr<GameEngineSpriteRenderer> MentBG = nullptr;
	std::shared_ptr<class ContentButton> _OkButton = nullptr;
	std::shared_ptr<class ContentButton> _CancelButton = nullptr;
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

	// static std::shared_ptr<ButtonWarningMent> CreateOneButtonMent();
	// static std::shared_ptr<ButtonWarningMent> CreateTwoButtonMent();

protected:
	ButtonWarningMentStruct MentObject;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	
};

