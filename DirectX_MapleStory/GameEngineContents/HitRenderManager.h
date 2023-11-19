#pragma once

struct HitRenderData
{
	friend class HitRenderManager;
private:
	std::string HitSpriteName = "";
	bool AniEnd = false;
	int CurIndex = 0;
	float DelayTime = 0.0f;
	GameEngineObject* Object = nullptr;
	std::vector<float4> RandomPivot;
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> HitAnimations;
	// std::vector<std::shared_ptr<GameEngineSpriteRenderer>> DamageAnimations;
	// Sound 추후 추가
};

class HitRenderManager : public GameEngineActor
{
public:
	static HitRenderManager* MainHitRenderManager;
public:
	// constructer destructer
	HitRenderManager();
	~HitRenderManager();

	// delete function
	HitRenderManager(const HitRenderManager& _Ohter) = delete;
	HitRenderManager(HitRenderManager&& _Ohter) noexcept = delete;
	HitRenderManager& operator=(const HitRenderManager& _Other) = delete;
	HitRenderManager& operator=(HitRenderManager&& _Other) noexcept = delete;

	void HitPrint(std::string_view _HitSpriteName, int _HitCount, GameEngineObject* _Object, int _Damage = -1, bool _RandomPivot = true, PivotType _PivotType = PivotType::Bottom);

protected:
	std::list<std::shared_ptr<HitRenderData>> AllHitRenderers;

	void LevelStart(class GameEngineLevel* _PrevLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;

private:
	void HitPrintUpdate(float _Delta);

};

