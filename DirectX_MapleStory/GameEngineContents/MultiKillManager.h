#pragma once

class MultiKillManager : public GameEngineActor
{
public:
	// constructer destructer
	MultiKillManager();
	~MultiKillManager();

	// delete function
	MultiKillManager(const MultiKillManager& _Ohter) = delete;
	MultiKillManager(MultiKillManager&& _Ohter) noexcept = delete;
	MultiKillManager& operator=(const MultiKillManager& _Other) = delete;
	MultiKillManager& operator=(MultiKillManager&& _Other) noexcept = delete;
	
	static void MultiKillPrint(int _KillCount);

protected:

private:
	std::shared_ptr<GameEngineUIRenderer> MultiKill_BG_Renderer = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MultiKill_Num_Renderer = nullptr;

	void LevelStart(class GameEngineLevel* _PrevLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void Init(int _KillCount);
};

