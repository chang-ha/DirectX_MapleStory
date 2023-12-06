#include "PreCompile.h"
#include "TestMonster.h"
#include "ReleaseFunction.h"

TestMonster::TestMonster()
{

}

TestMonster::~TestMonster()
{

}

void TestMonster::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void TestMonster::Start()
{
	HP = INT_MAX;

	if (nullptr == GameEngineSprite::Find("TestMonster_Idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Monster\\TestMonster\\Idle");
		GameEngineSprite::CreateFolder("TestMonster_Idle", Dir.GetStringPath());
	}

	if (nullptr == Renderer)
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
		Renderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::monster });
		Renderer->AutoSpriteSizeOn();
	}

	if (nullptr == Collision)
	{
		Collision = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
	}

	Renderer->CreateAnimation("Idle", "TestMonster_Idle", 0.12f);
	Renderer->ChangeAnimation("Idle");
	Renderer->SetPivotType(PivotType::Bottom);

	std::shared_ptr<GameEngineTexture> _Texture = GameEngineTexture::Find("TestMonster_Idle_001.png");
	float4 _TextureScale = _Texture->GetScale();
	_TextureScale.Z = 1.0f;
	Collision->Transform.SetLocalScale(_TextureScale);
	Collision->Transform.SetLocalPosition({ 0, _TextureScale.hY()});
	DamageSkinPivot = { 0, _TextureScale.Y };
}

void TestMonster::Update(float _Delta)
{

}

void TestMonster::Release()
{
	if (nullptr != Renderer)
	{
		Renderer->Death();
		Renderer = nullptr;
	}

	if (nullptr != Collision)
	{
		Collision->Death();
		Collision = nullptr;
	}

	if (nullptr != GameEngineSprite::Find("TestMonster_Idle"))
	{
		ReleaseFunction::FolderRelease("TestMonster_Idle", "TestMonster_Idle_");
	}
}