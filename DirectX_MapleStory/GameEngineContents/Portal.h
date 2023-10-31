#pragma once

class Portal : public GameEngineActor
{
public:
	// constructer destructer
	Portal();
	~Portal();

	// delete function
	Portal(const Portal& _Ohter) = delete;
	Portal(Portal&& _Ohter) noexcept = delete;
	Portal& operator=(const Portal& _Other) = delete;
	Portal& operator=(Portal&& _Other) noexcept = delete;

	void SetMoveMap(std::string_view _MapName)
	{
		MoveMap = _MapName.data();
	}

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	std::string MoveMap = "";
	std::shared_ptr<GameEngineSpriteRenderer> PortalRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> PortalCollision = nullptr;
};

