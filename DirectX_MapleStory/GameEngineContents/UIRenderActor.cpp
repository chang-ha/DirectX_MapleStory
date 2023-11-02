#include "PreCompile.h"
#include "UIRenderActor.h"

UIRenderActor::UIRenderActor()
{

}

UIRenderActor::~UIRenderActor()
{

}

void UIRenderActor::Init(int _Order, float _Depth)
{
	if (nullptr == Renderer)
	{
		Renderer = CreateComponent<GameEngineUIRenderer>(_Order);
		Renderer->Transform.SetLocalPosition({ 0, 0, _Depth });
		Renderer->AutoSpriteSizeOn();
	}
}