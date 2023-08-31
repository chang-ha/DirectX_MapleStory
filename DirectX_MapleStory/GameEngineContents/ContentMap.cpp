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
	MapRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(RenderOrder::Map));
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
	}
	MapCollisionTexture = GameEngineTexture::Find("Collision_" + std::string(_MapName.data()));
	MapRenderer->SetSprite(_MapName);
	float4 MapScale = MapCollisionTexture->GetScale().Half();
	MapScale.Y *= -1.0f;
	this->Transform.SetLocalPosition(MapScale);
}


GameEngineColor ContentMap::GetColor(float4 _Pos, GameEngineColor _DefaultColor /*= { 255, 255, 255, 255 }*/)
{
	// 플레이어의 위치를 이미지의 좌표계에 맞게 변형한다.
	// 이미지는 위에서부터 아래로 내려갈수록 +가 되기 때문이다. (DirectX의 Y좌표계는 아래로 내려갈수록 -)
	_Pos.Y *= -1.0f;
	return MapCollisionTexture->GetColor(_Pos, _DefaultColor);
}