#pragma once

class GameEngineRenderUnit
{
public:
	// constructer destructer
	GameEngineRenderUnit();
	~GameEngineRenderUnit();

	// delete function
	GameEngineRenderUnit(const GameEngineRenderUnit& _Ohter) = delete;
	GameEngineRenderUnit(GameEngineRenderUnit&& _Ohter) noexcept = delete;
	GameEngineRenderUnit& operator=(const GameEngineRenderUnit& _Other) = delete;
	GameEngineRenderUnit& operator=(GameEngineRenderUnit&& _Other) noexcept = delete;

protected:

private:

};

