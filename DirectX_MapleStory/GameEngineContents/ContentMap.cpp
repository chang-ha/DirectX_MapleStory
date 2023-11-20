#include "PreCompile.h"
#include "ContentMap.h"

bool ContentMap::IsCollisionDebug = false;

ContentMap::ContentMap()
{

}

ContentMap::~ContentMap()
{

}

void ContentMap::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
	IsCollisionDebug = false;
}

void ContentMap::Start()
{
	GameEngineInput::AddInputObject(this);
}

void ContentMap::Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_F1, this) && nullptr != MapRenderer)
	{
		if (true == MapRenderer->IsUpdate())
		{
			MapRenderer->Off();
		}
		else
		{
			MapRenderer->On();
		}
	}

	if (nullptr == MapCollisionRenderer)
	{
		return;
	}

	if (true == IsCollisionDebug && false == MapCollisionRenderer->IsUpdate())
	{
		MapCollisionRenderer->On();
	}
	else if (false == IsCollisionDebug && true == MapCollisionRenderer->IsUpdate())
	{
		MapCollisionRenderer->Off();
	}
}

void ContentMap::CreateBaseColorMap(const float4& _Color)
{
	MapRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MAP);
	MapRenderer->RenderBaseInfoValue.BaseColorOnly = true;
	MapRenderer->RenderBaseInfoValue.BaseColor = _Color;

	float4 WindowScale = GlobalValue::WinScale;
	MapRenderer->SetImageScale(WindowScale);
	MapRenderer->Transform.SetLocalPosition({ WindowScale.hX(), -WindowScale.hY(), RenderDepth::map});
}

void ContentMap::InitMap(std::string_view _MapName)
{
	MapName = _MapName;

	if (nullptr == GameEngineTexture::Find(MapName))
	{
		GameEnginePath Path;
		Path.SetCurrentPath();
		Path.MoveParentToExistsChild("ContentResources");
		Path.MoveChild("ContentResources\\Textures\\Map\\");
		GameEngineTexture::Load(Path.GetStringPath() + MapName);
		GameEngineSprite::CreateSingle(MapName);
	}

	if (nullptr == MapRenderer)
	{
		MapRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MAP);
		MapRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::map });
	}

	MapRenderer->SetSprite(MapName);
	
	float4 HalfMapScale = GameEngineTexture::Find(MapName)->GetScale().Half();
	HalfMapScale.Y *= -1.0f;
	this->Transform.SetLocalPosition(HalfMapScale);
}

void ContentMap::InitMapCollision(std::string_view _MapCollisionName)
{
	MapCollisionName = _MapCollisionName;

	if (nullptr == GameEngineTexture::Find(MapCollisionName))
	{
		GameEnginePath Path;
		Path.SetCurrentPath();
		Path.MoveParentToExistsChild("ContentResources");
		Path.MoveChild("ContentResources\\Textures\\Map\\");
		GameEngineTexture::Load(Path.GetStringPath() + MapCollisionName);
		GameEngineSprite::CreateSingle(MapCollisionName);
	}

	if (nullptr == MapCollisionRenderer)
	{
		MapCollisionRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MAP);
		MapCollisionRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::map });
	}

	MapCollisionRenderer->SetSprite(MapCollisionName);
	MapCollisionRenderer->Off();

	MapCollisionTexture = GameEngineTexture::Find(MapCollisionName);
	MapScale = MapCollisionTexture->GetScale();
	float4 HalfMapScale = MapScale.Half();
	HalfMapScale.Y *= -1.0f;
	this->Transform.SetLocalPosition(HalfMapScale);
}

void ContentMap::InitFootHold(std::string_view _FootHoldName)
{
	FootHoldName = _FootHoldName;
	if (nullptr == GameEngineTexture::Find(FootHoldName))
	{
		GameEnginePath Path;
		Path.SetCurrentPath();
		Path.MoveParentToExistsChild("ContentResources");
		Path.MoveChild("ContentResources\\Textures\\Map\\");
		GameEngineTexture::Load(Path.GetStringPath() + FootHoldName);
		GameEngineSprite::CreateSingle(FootHoldName);
	}

	if (nullptr == FootHoldRenderer)
	{
		FootHoldRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::FOOTHOLD);
		FootHoldRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::foothold });
	}

	FootHoldRenderer->SetSprite(FootHoldName);
	float4 HalfMapScale = MapScale.Half();
	HalfMapScale.Y *= -1.0f;
	this->Transform.SetLocalPosition(HalfMapScale);
}

GameEngineColor ContentMap::GetColor(float4 _Pos, GameEngineColor _DefaultColor /*= GROUND_COLOR*/)
{
	// 플레이어의 위치를 이미지의 좌표계에 맞게 변형한다.
	// 이미지는 위에서부터 아래로 내려갈수록 +가 되기 때문이다. (DirectX의 Y좌표계는 아래로 내려갈수록 -)
	_Pos.Y *= -1.0f;
	return MapCollisionTexture->GetColor(_Pos, _DefaultColor);
}

void ContentMap::Release()
{
	if (nullptr != MapRenderer)
	{
		MapRenderer->Death();
		MapRenderer = nullptr;
	}

	if (nullptr != MapCollisionRenderer)
	{
		MapCollisionRenderer->Death();
		MapCollisionRenderer = nullptr;
	}

	if (nullptr != FootHoldRenderer)
	{
		FootHoldRenderer->Death();
		FootHoldRenderer = nullptr;
	}

	if ("" != MapName && nullptr != GameEngineSprite::Find(MapName))
	{
		GameEngineTexture::Release(MapName);
		GameEngineSprite::Release(MapName);
	}

	if ("" != MapCollisionName && nullptr != GameEngineSprite::Find(MapCollisionName))
	{
		GameEngineTexture::Release(MapCollisionName);
		GameEngineSprite::Release(MapCollisionName);
	}

	if ("" != FootHoldName && nullptr != GameEngineSprite::Find(FootHoldName))
	{
		GameEngineTexture::Release(FootHoldName);
		GameEngineSprite::Release(FootHoldName);
	}
}