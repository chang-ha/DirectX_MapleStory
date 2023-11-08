#include "PreCompile.h"
#include "Lachlen.h"
#include "Player.h"
#include "SkillManager.h"
#include "ContentMap.h"
#include "ContentBackGround.h"
#include "RenderActor.h"
#include "BackGroundActor.h"

Lachlen::Lachlen()
{

}

Lachlen::~Lachlen()
{

}

void Lachlen::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMap("Lacheln.png");
		CurMap->InitMapCollision("Collision_Lacheln.png");
	}

	std::shared_ptr<BackGroundActor> _Water = CreateActor<BackGroundActor>(UpdateOrder::Map);
	_Water->Transform.SetLocalPosition({-100, -1006});
	_Water->Init("BG_Lachlen_Water.png", 8, 4440, 0.8f);

	std::shared_ptr<BackGroundActor> _Sky = CreateActor<BackGroundActor>(UpdateOrder::Map);
	_Sky->Transform.SetLocalPosition({ -100, -418 });
	_Sky->Init("BG_Lachlen_Sky.png", 11, 4440, 0.65f);

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
		CurPlayer->Transform.SetLocalPosition(float4(100, -800));
		GetMainCamera()->Transform.SetLocalPosition(float4(100, -690, -100000));
	}

	if (nullptr == SkillManagerActor)
	{
		SkillManagerActor = CreateActor<SkillManager>();
	}
}

void Lachlen::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);

}

void Lachlen::Start()
{
	ContentLevel::Start();

}

void Lachlen::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

}