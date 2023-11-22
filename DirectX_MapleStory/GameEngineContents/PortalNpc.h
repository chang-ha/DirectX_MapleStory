#pragma once
#include "ContentNpc.h"

class PortalNpc : public ContentNpc
{
public:
	// constructer destructer
	PortalNpc();
	~PortalNpc();

	// delete function
	PortalNpc(const PortalNpc& _Ohter) = delete;
	PortalNpc(PortalNpc&& _Ohter) noexcept = delete;
	PortalNpc& operator=(const PortalNpc& _Other) = delete;
	PortalNpc& operator=(PortalNpc&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
};

