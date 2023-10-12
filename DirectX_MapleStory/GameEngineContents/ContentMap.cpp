#include "PreCompile.h"
#include "ContentMap.h"

ContentMap::ContentMap()
{

}

ContentMap::~ContentMap()
{

}

void ContentMap::Start()
{
	GameEngineInput::AddInputObject(this);
	if (nullptr == MapRenderer)
	{
		MapRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Map);
	}
}

void ContentMap::Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_F1, this))
	{
		MapRenderer->SetSprite(MapName);
	}
	else if (GameEngineInput::IsDown(VK_F2, this))
	{
		MapRenderer->SetSprite("Collision_" + MapName);
	}
}


void ContentMap::Init(std::string_view _MapName)
{
	if (nullptr == GameEngineTexture::Find(_MapName))
	{
		GameEnginePath Path;
		Path.SetCurrentPath();
		Path.MoveParentToExistsChild("ContentResources");
		Path.MoveChild("ContentResources\\Textures\\Map\\");
		GameEngineTexture::Load(Path.GetStringPath() + std::string(_MapName.data()));
		GameEngineTexture::Load(Path.GetStringPath() + "Collision_" + std::string(_MapName.data()));
		GameEngineSprite::CreateSingle(_MapName);
		GameEngineSprite::CreateSingle("Collision_" + std::string(_MapName.data()));
	}
	MapName = _MapName;
	MapCollisionTexture = GameEngineTexture::Find("Collision_" + std::string(_MapName.data()));
	MapRenderer->SetSprite(MapName);
	float4 HalfMapScale = MapCollisionTexture->GetScale().Half();
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
}