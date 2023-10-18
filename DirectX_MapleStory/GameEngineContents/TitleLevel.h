#pragma once
#include "ContentLevel.h"

class TitleLevel : public ContentLevel
{
public:
	// constructer destructer
	TitleLevel();
	~TitleLevel();

	// delete function
	TitleLevel(const TitleLevel& _Ohter) = delete;
	TitleLevel(TitleLevel&& _Ohter) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:

private:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
};

