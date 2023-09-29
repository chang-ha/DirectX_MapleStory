#pragma once

class CutsceneActor : public GameEngineActor
{
public:
	// constructer destructer
	CutsceneActor();
	~CutsceneActor();

	// delete function
	CutsceneActor(const CutsceneActor& _Ohter) = delete;
	CutsceneActor(CutsceneActor&& _Ohter) noexcept = delete;
	CutsceneActor& operator=(const CutsceneActor& _Other) = delete;
	CutsceneActor& operator=(CutsceneActor&& _Other) noexcept = delete;

	void Init(std::string_view _BossName, std::string_view _NextLevelName);

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Update(float _Delta) override;

private:
	std::string BossName = "";
	std::string NextLevelName = "";
	std::shared_ptr<GameEngineUIRenderer> CutRenderer = nullptr;
};

