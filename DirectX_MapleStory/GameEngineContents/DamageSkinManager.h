#pragma once

class DamageSkin : public GameEngineActor
{

};

class DamageSkinManager : public GameEngineActor
{
public:
	static DamageSkinManager* MainDamageSkinManager;

	// constructer destructer
	DamageSkinManager();
	~DamageSkinManager();

	// delete function
	DamageSkinManager(const DamageSkinManager& _Ohter) = delete;
	DamageSkinManager(DamageSkinManager&& _Ohter) noexcept = delete;
	DamageSkinManager& operator=(const DamageSkinManager& _Other) = delete;
	DamageSkinManager& operator=(DamageSkinManager&& _Other) noexcept = delete;

	std::shared_ptr<class DamageSkinRenderer> CreateDamageSkin(class ContentBaseActor* _Actor, int _Damage);
	std::shared_ptr<class DamageSkinRenderer> CreateDamageSkin(const float4& _RenderPos, int _Damage);

protected:

private:
	void LevelStart(class GameEngineLevel* _PrevLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;
	void Start() override;
};

