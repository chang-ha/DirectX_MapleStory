#pragma once
#include "RenderActor.h"

class UIRenderActor : public RenderActor
{
public:
	// constructer destructer
	UIRenderActor();
	~UIRenderActor();

	// delete function
	UIRenderActor(const UIRenderActor& _Ohter) = delete;
	UIRenderActor(UIRenderActor&& _Ohter) noexcept = delete;
	UIRenderActor& operator=(const UIRenderActor& _Other) = delete;
	UIRenderActor& operator=(UIRenderActor&& _Other) noexcept = delete;

	template <typename EnumType, typename DepthType>
	void Init(EnumType _Order , DepthType _Depth)
	{
		Init(static_cast<int>(_Order), static_cast<float>(_Depth));
	}

	void Init(int _Order, float _Depth) override;

protected:

private:

};

