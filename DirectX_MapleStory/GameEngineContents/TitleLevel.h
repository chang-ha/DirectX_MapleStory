#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class TitleLevel : public GameEngineLevel
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

};

