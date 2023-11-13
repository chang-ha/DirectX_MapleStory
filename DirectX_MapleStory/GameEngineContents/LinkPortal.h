#pragma once

#define LINK_DELAY_TIME 1.0f

class LinkPortal : public GameEngineActor
{
public:
	static float LinkPortalDelayTime;
public:
	// constructer destructer
	LinkPortal();
	~LinkPortal();

	// delete function
	LinkPortal(const LinkPortal& _Ohter) = delete;
	LinkPortal(LinkPortal&& _Ohter) noexcept = delete;
	LinkPortal& operator=(const LinkPortal& _Other) = delete;
	LinkPortal& operator=(LinkPortal&& _Other) noexcept = delete;

	void DoubleLinkPortal(LinkPortal* _LinkPortal);

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	// 쉐어드ptr 순환참조 방지
	LinkPortal* LinkedPortal = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> PortalRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> PortalCollision = nullptr;
	
	void Link(LinkPortal* _LinkPortal);
};

