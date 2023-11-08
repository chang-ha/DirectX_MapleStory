#include "PreCompile.h"
#include "Lachlen.h"
#include "Player.h"
#include "SkillManager.h"
#include "ContentMap.h"
#include "ContentBackGround.h"
#include "RenderActor.h"
#include "BackGroundActor.h"
#include "Portal.h"
#include "Minimap.h"
#include "Boss_WaitingRoom.h"
#include "FireWork.h"

Lachlen::Lachlen()
{

}

Lachlen::~Lachlen()
{

}

void Lachlen::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	if (nullptr == GameEngineSprite::Find("WaterMelonMen"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\MapObject\\Lachlen\\WaterMelonMen");
		GameEngineSprite::CreateFolder("WaterMelonMen", Dir.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("Boat1"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\MapObject\\Lachlen\\Boat1");
		GameEngineSprite::CreateFolder("Boat1", Dir.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("Wood1.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\MapObject\\Lachlen\\Wood1.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("Wood2.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\MapObject\\Lachlen\\Wood2.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("Wood3.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\MapObject\\Lachlen\\Wood3.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("Bridge.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\MapObject\\Lachlen\\Bridge.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMap("Lachlen_NBG.png");
		CurMap->InitMapCollision("Collision_Lacheln.png");
	}

	if (nullptr == Back)
	{
		Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
		Back->Init("BG_Lachlen.png");
	}

	//std::shared_ptr<BackGroundActor> _Sky = CreateActor<BackGroundActor>(UpdateOrder::Map);
	//_Sky->Transform.SetLocalPosition({ -100, -440 });
	//_Sky->Init("BG_Lachlen_Sky.png", 13, 4440, 0.65f);

	std::shared_ptr<BackGroundActor> _Water = CreateActor<BackGroundActor>(UpdateOrder::Map);
	_Water->Transform.SetLocalPosition({-100, -1006});
	_Water->Init("BG_Lachlen_Water.png", 8, 4440, 0.8f);

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);

		Boss_WaitingRoom* _Level = dynamic_cast<Boss_WaitingRoom*>(_PrevLevel);
		if (nullptr != _Level)
		{
			CurPlayer->Transform.SetLocalPosition(float4(3820, -750));
			GetMainCamera()->Transform.SetLocalPosition(float4(3820, -750, -100000));
		}
		else
		{
			CurPlayer->Transform.SetLocalPosition(float4(1500, -800));
			GetMainCamera()->Transform.SetLocalPosition(float4(1500, -800, -100000));
			// CurPlayer->Transform.SetLocalPosition(float4(3000, -800));
			// GetMainCamera()->Transform.SetLocalPosition(float4(3000, -800, -100000));
		}
	}

	if (nullptr == SkillManagerActor)
	{
		SkillManagerActor = CreateActor<SkillManager>();
	}

	std::shared_ptr<GameEngineFrameAnimation> _Animation = nullptr;
	std::shared_ptr<RenderActor> _Actor = nullptr;

	{
		_Actor = CreateActor<RenderActor>(UpdateOrder::Map);
		_Actor->Init(RenderOrder::MAPOBJECT, RenderDepth::mapobject);
		_Actor->Renderer->SetPivotType(PivotType::Bottom);
		_Actor->Renderer->CreateAnimation("WaterMelonMen", "WaterMelonMen", 0.12f);
		_Actor->Renderer->ChangeAnimation("WaterMelonMen");

		_Animation = _Actor->Renderer->FindAnimation("WaterMelonMen");
		_Animation->Inter[0] = 5.4f;

		_Actor->Transform.SetLocalPosition({1484, -818});
	}

	//{
	//	_Actor = CreateActor<RenderActor>(UpdateOrder::Map);
	//	_Actor->Init(RenderOrder::RENDERACTOR, RenderDepth::renderactor);
	//	_Actor->Renderer->SetPivotType(PivotType::Bottom);
	//	_Actor->Renderer->SetSprite("Bridge.png");

	//	_Actor->Transform.SetLocalPosition({ 1960, -845 });
	//}

	//{
	//	_Actor = CreateActor<RenderActor>(UpdateOrder::Map);
	//	_Actor->Init(RenderOrder::RENDERACTOR, RenderDepth::renderactor);
	//	_Actor->Renderer->SetPivotType(PivotType::Bottom);
	//	_Actor->Renderer->SetSprite("Wood1.png");

	//	_Actor->Transform.SetLocalPosition({ 3000, -1180 });
	//}

	{
		_Actor = CreateActor<RenderActor>(UpdateOrder::Map);
		_Actor->Init(RenderOrder::RENDERACTOR, RenderDepth::renderactor);
		_Actor->Renderer->SetPivotType(PivotType::Bottom);
		_Actor->Renderer->CreateAnimation("Boat1", "Boat1", 0.24f);
		_Actor->Renderer->ChangeAnimation("Boat1");

		_Actor->Transform.SetLocalPosition({ 543.0f, -1070.0f, 1.0f });
	}

	{
		_Actor = CreateActor<RenderActor>(UpdateOrder::Map);
		_Actor->Init(RenderOrder::RENDERACTOR, RenderDepth::renderactor);
		_Actor->Renderer->SetPivotType(PivotType::Bottom);
		_Actor->Renderer->CreateAnimation("Boat1", "Boat1", 0.24f);
		_Actor->Renderer->ChangeAnimation("Boat1");

		_Actor->Transform.SetLocalPosition({ 768.0f, -1100.0f, 1.0f });
	}

	{
		_Actor = CreateActor<RenderActor>(UpdateOrder::Map);
		_Actor->Init(RenderOrder::RENDERACTOR, RenderDepth::renderactor);
		_Actor->Renderer->SetPivotType(PivotType::Bottom);
		_Actor->Renderer->SetSprite("Wood2.png");

		_Actor->Transform.SetLocalPosition({ 430.0f, -1210.0f, 1.0f });
	}

	{
		_Actor = CreateActor<RenderActor>(UpdateOrder::Map);
		_Actor->Init(RenderOrder::RENDERACTOR, RenderDepth::renderactor);
		_Actor->Renderer->SetPivotType(PivotType::Bottom);
		_Actor->Renderer->SetSprite("Wood3.png");

		_Actor->Transform.SetLocalPosition({ 670.0f, -1130.0f, 1.0f });
	}

	{
		_Actor = CreateActor<RenderActor>(UpdateOrder::Map);
		_Actor->Init(RenderOrder::RENDERACTOR, RenderDepth::renderactor);
		_Actor->Renderer->SetPivotType(PivotType::Bottom);
		_Actor->Renderer->CreateAnimation("Boat1", "Boat1", 0.24f);
		_Actor->Renderer->ChangeAnimation("Boat1");

		_Actor->Transform.SetLocalPosition({ 2650.0f, -1090.0f, 1.0f });
	}

	{
		_Actor = CreateActor<RenderActor>(UpdateOrder::Map);
		_Actor->Init(RenderOrder::RENDERACTOR, RenderDepth::renderactor);
		_Actor->Renderer->SetPivotType(PivotType::Bottom);
		_Actor->Renderer->CreateAnimation("Boat1", "Boat1", 0.24f);
		_Actor->Renderer->ChangeAnimation("Boat1");

		_Actor->Transform.SetLocalPosition({ 2820.0f, -1120.0f, 1.0f });
	}

	{
		_Actor = CreateActor<RenderActor>(UpdateOrder::Map);
		_Actor->Init(RenderOrder::RENDERACTOR, RenderDepth::renderactor);
		_Actor->Renderer->SetPivotType(PivotType::Bottom);
		_Actor->Renderer->SetSprite("Wood2.png");

		_Actor->Transform.SetLocalPosition({ 2430.0f, -1170.0f, 1.0f });
	}

	{
		_Actor = CreateActor<RenderActor>(UpdateOrder::Map);
		_Actor->Init(RenderOrder::RENDERACTOR, RenderDepth::renderactor);
		_Actor->Renderer->SetPivotType(PivotType::Bottom);
		_Actor->Renderer->SetSprite("Wood3.png");

		_Actor->Transform.SetLocalPosition({ 2600.0f, -1120.0f, 1.0f });
	}

	{
		_Actor = CreateActor<RenderActor>(UpdateOrder::Map);
		_Actor->Init(RenderOrder::RENDERACTOR, RenderDepth::renderactor);
		_Actor->Renderer->SetPivotType(PivotType::Bottom);
		_Actor->Renderer->SetSprite("Wood1.png");

		_Actor->Transform.SetLocalPosition({ 3000.0f, -1180.0f, 1.0f });
	}

	std::shared_ptr<Portal> _Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 3820, -710 });
	_Portal->SetMoveMap("Boss_WaitingRoom");

	for (size_t i = 0; i < 8; i++)
	{
		std::shared_ptr<FlowObject> Water = CreateActor<FlowObject>(UpdateOrder::RenderActor);
		Water->RenderActor::Init(RenderOrder::MAPOBJECT, RenderDepth::mapobject);
		Water->Init("Lachlen_Water.png", 40.0f, float4{ -300, -1000 }, float4{ 5200, -1000 });
		Water->Transform.SetLocalPosition({ -500 + 700 * static_cast<float>(i), -1000, 0 });
		MapObjects.push_back(Water);
	}

	for (size_t i = 0; i < 12; i++)
	{
		std::shared_ptr<FlowObject> Water = CreateActor<FlowObject>(UpdateOrder::RenderActor);
		Water->RenderActor::Init(RenderOrder::MAPOBJECT, RenderDepth::mapobject);
		Water->Init("Lachlen_WaterStar.png", 40.0f, float4{ -300, -1020 }, float4{ 5200, -1020 });
		Water->Transform.SetLocalPosition({ -500 + 500 * static_cast<float>(i), -1020, 0 });
		MapObjects.push_back(Water);
	}

	std::shared_ptr<FireWork> _FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork4);
	_FireWork->Transform.SetLocalPosition({ 600, -100 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork2);
	_FireWork->Transform.SetLocalPosition({ 540, -350 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork1);
	_FireWork->Transform.SetLocalPosition({ 660, -320 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork3);
	_FireWork->Transform.SetLocalPosition({ 1350, -100 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork3);
	_FireWork->Transform.SetLocalPosition({ 1950, -140 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork2);
	_FireWork->Transform.SetLocalPosition({ 1550, -400 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork4);
	_FireWork->Transform.SetLocalPosition({ 1750, -70 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork1);
	_FireWork->Transform.SetLocalPosition({ 1780, -320 });

	Minimap::CreateMinimap("Minimap_Lachlen.png", "레헬른 중심가");
}

void Lachlen::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);

	if (nullptr != GameEngineSprite::Find("Lachlen_NBG.png"))
	{
		GameEngineTexture::Release("Lachlen_NBG.png");
		GameEngineSprite::Release("Lachlen_NBG.png");
	}

	if (nullptr != GameEngineSprite::Find("Collision_Lacheln.png"))
	{
		GameEngineTexture::Release("Collision_Lacheln.png");
		GameEngineSprite::Release("Collision_Lacheln.png");
	}

	//if (nullptr != GameEngineSprite::Find("BG_Lachlen_Sky.png"))
	//{
	//	GameEngineTexture::Release("BG_Lachlen_Sky.png");
	//	GameEngineSprite::Release("BG_Lachlen_Sky.png");
	//}

	if (nullptr != GameEngineSprite::Find("BG_Lachlen_Water.png"))
	{
		GameEngineTexture::Release("BG_Lachlen_Water.png");
		GameEngineSprite::Release("BG_Lachlen_Water.png");
	}

	for (size_t i = 0; i < MapObjects.size(); i++)
	{
		MapObjects[i]->Death();
		MapObjects[i] = nullptr;
	}

	if (nullptr != CurMap)
	{
		CurMap = nullptr;
	}

	if (nullptr != Back)
	{
		Back = nullptr;
	}

	if (nullptr != CurPlayer)
	{
		CurPlayer = nullptr;
	}

	if (nullptr != SkillManagerActor)
	{
		SkillManagerActor = nullptr;
	}
}

void Lachlen::Start()
{
	ContentLevel::Start();

}

void Lachlen::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

}