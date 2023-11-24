#include "PreCompile.h"
#include "DamageSkinManager.h"
#include "ContentLevel.h"
#include "DamageSkinRenderer.h"
#include "Player.h"

DamageSkinManager::DamageSkinManager()
{

}

DamageSkinManager::~DamageSkinManager()
{

}

void DamageSkinManager::LevelStart(class GameEngineLevel* _PrevLevel)
{

}

void DamageSkinManager::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void DamageSkinManager::Start()
{
	if (nullptr == GameEngineSprite::Find("Character_Empty.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\DamageSkin\\DamageSkin_Num_Merge.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	std::shared_ptr<DamageSkinRenderer> _Renderer = CreateComponent<DamageSkinRenderer>(RenderOrder::UI);
	_Renderer->SetDamage(19283746);
	_Renderer->Transform.SetWorldPosition(float4(3500, -717));
}

void DamageSkinManager::Update(float _Delta)
{
	
}

void DamageSkinManager::Release()
{

}

void DamageSkinManager::DamageSkinPrint(int _DamageSkinCount, int _Damage)
{

}

void DamageSkinManager::Init()
{

}