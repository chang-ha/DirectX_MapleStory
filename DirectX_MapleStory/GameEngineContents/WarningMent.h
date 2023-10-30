#pragma once

#define WarningTime_Value 5.0f

class WarningMentFrame
{
	friend class WarningMent;
	std::shared_ptr<GameEngineSpriteRenderer> FrameStart = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> FrameMiddle = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> FrameEnd = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> WarningMent = nullptr;
};

class WarningMent : public GameEngineActor
{
public:
	// constructer destructer
	WarningMent();
	~WarningMent();

	// delete function
	WarningMent(const WarningMent& _Ohter) = delete;
	WarningMent(WarningMent&& _Ohter) noexcept = delete;
	WarningMent& operator=(const WarningMent& _Other) = delete;
	WarningMent& operator=(WarningMent&& _Other) noexcept = delete;

	void SetWarningMent(std::string_view _Ment);

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	float WarningTime = WarningTime_Value;
	WarningMentFrame Frame;
};

