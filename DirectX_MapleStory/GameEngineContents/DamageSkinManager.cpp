#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "DamageSkinManager.h"
#include "ContentLevel.h"
#include "DamageSkinRenderer.h"
#include "Player.h"

DamageSkinManager* DamageSkinManager::MainDamageSkinManager = nullptr;


DamageSkinManager::DamageSkinManager()
{

}

DamageSkinManager::~DamageSkinManager()
{

}

void DamageSkinManager::LevelStart(class GameEngineLevel* _PrevLevel)
{
	MainDamageSkinManager = this;
}

void DamageSkinManager::LevelEnd(class GameEngineLevel* _NextLevel)
{
	MainDamageSkinManager = nullptr;
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
}

void DamageSkinManager::Update(float _Delta)
{
	
}

void DamageSkinManager::Release()
{

}

std::shared_ptr<DamageSkinRenderer> DamageSkinManager::CreateDamageSkin(ContentBaseActor* _Actor, int _Damage)
{
	std::shared_ptr<DamageSkinRenderer> _Renderer = CreateComponent<DamageSkinRenderer>(UpdateOrder::UI);
	_Renderer->SetDamage(_Damage);
	_Renderer->Transform.SetLocalPosition(_Actor->Transform.GetWorldPosition() + _Actor->GetDamageSkinPivot());

	return _Renderer;
}

std::shared_ptr<class DamageSkinRenderer> DamageSkinManager::CreateDamageSkin(const float4& _RenderPos, int _Damage)
{
	std::shared_ptr<DamageSkinRenderer> _Renderer = CreateComponent<DamageSkinRenderer>(UpdateOrder::UI);
	_Renderer->SetDamage(_Damage);
	_Renderer->Transform.SetLocalPosition(_RenderPos);

	return _Renderer;
}

//
//std::shared_ptr<DamageSkinRenderer> DamageSkinManager::CreateDamageSkin(class ContentBaseActor* _Actor, int _Damage, int _DamageCount)
//{
//	GameEngineRandom Random;
//	for (size_t i = 0; i < _DamageCount; i++)
//	{
//		Random.SetSeed(reinterpret_cast<long long>(_Actor) + _DamageCount * time(nullptr));
//		int RandomDamage = Random.RandomInt(10000000, 99999999);
//
//	}
//}
