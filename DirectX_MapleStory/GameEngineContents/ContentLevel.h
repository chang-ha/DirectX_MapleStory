#pragma once
#include <GameEngineCore\GameEngineLevel.h>
#include "RenderActor.h"

class LevelDebug : public GameEngineGUIWindow
{
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
};

class FlowObject : public RenderActor
{
	friend class Lachlen;
	friend class Lucid_Phase1;
private:
	std::string SpriteName = "";
	float ObjectSpeed = 0.0f;
	float4 StartPos = 0.0f;
	float4 EndPos = 0.0f;

	void Init(std::string_view _SpriteName, float _ObjectSpeed, const float4& _StartPos, const float4& _EndPos);
	void Update(float _Delta) override;
	void Release() override;
};

// ���� :
class ContentLevel : public GameEngineLevel
{
public:
	static ContentLevel* CurContentLevel;
	// static GameEngineSoundPlayer EffectPlayer;
public:
	// constructer destructer
	ContentLevel();
	~ContentLevel();

	// delete function
	ContentLevel(const ContentLevel& _Ohter) = delete;
	ContentLevel(ContentLevel&& _Ohter) noexcept = delete;
	ContentLevel& operator=(const ContentLevel& _Other) = delete;
	ContentLevel& operator=(ContentLevel&& _Other) noexcept = delete;

	std::shared_ptr<class ContentMap> GetCurMap()
	{
		return CurMap;
	}

	void AllButtonOn();
	void AllButtonOff();

	std::shared_ptr<class FadeObject> FadeInObject = nullptr;
	std::shared_ptr<class FadeObject> FadeOutObject = nullptr;

protected:
	std::string PrevLevel = "";
	std::string NextLevel = "";
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	std::shared_ptr<class ContentMap> CurMap = nullptr;
	std::vector<std::shared_ptr<class ContentButton>> AllButton;

	static GameEngineSoundPlayer BGMPlayer;
private:

};

