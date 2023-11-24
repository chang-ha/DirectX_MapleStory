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
#include "ClockTowerOfNightMare_1th.h"
#include "FireWork.h"
#include "ContentNpc.h"
#include "ReleaseFunction.h"
#include "DamageSkinManager.h"

Lachlen::Lachlen()
{

}

Lachlen::~Lachlen()
{

}

void Lachlen::LevelStart(GameEngineLevel* _PrevLevel)
{
	PrevLevel = "03.CharacterSelect";
	NextLevel = "05.ClockTowerOfNightMare_1th";

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

	if (nullptr == GameEngineSound::FindSound("Lachlen.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\BGM\\Lachlen.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath());
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

	std::shared_ptr<BackGroundActor> _Water = CreateActor<BackGroundActor>(UpdateOrder::Map);
	_Water->Transform.SetLocalPosition({-100, -1006});
	_Water->Init("BG_Lachlen_Water.png", 8, 4440, 0.8f);

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);

		ClockTowerOfNightMare_1th* _Level = dynamic_cast<ClockTowerOfNightMare_1th*>(_PrevLevel);
		if (nullptr != _Level)
		{
			CurPlayer->Transform.SetLocalPosition(float4(3770, -817));
			GetMainCamera()->Transform.SetLocalPosition(float4(3770, -817, -100000));
			CurPlayer->SetDir(ActorDir::Left);
		}
		else
		{
			CurPlayer->Transform.SetLocalPosition(float4(3500, -817));
			GetMainCamera()->Transform.SetLocalPosition(float4(3500, -817, -100000));
		}
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
		_Actor->Renderer->ChangeAnimation("Boat1", true, 3);

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
		_Actor->Renderer->ChangeAnimation("Boat1", true, 3);

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
	_Portal->Transform.SetLocalPosition({ 3770, -825 });
	_Portal->SetMoveMap("05.ClockTowerOfNightMare_1th");

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

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork1);
	_FireWork->Transform.SetLocalPosition({ 2300, -120 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork3);
	_FireWork->Transform.SetLocalPosition({ 2200, -260 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork2);
	_FireWork->Transform.SetLocalPosition({ 2600, -120 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork1);
	_FireWork->Transform.SetLocalPosition({ 3000, -220 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork4);
	_FireWork->Transform.SetLocalPosition({ 3000, -250 });

	std::shared_ptr<ContentNpc> _Npc = CreateActor<ContentNpc>(UpdateOrder::RenderActor);
	_Npc->Transform.SetLocalPosition({ 2700, -817 });
	_Npc->Init("BeautyMask", "미녀가면", ActorDir::Left, 0.18f);
	_Npc->CreateOneButtonMent("Npc_Ok");
	_Npc->SetMentText(L"미녀가면");

	_Npc = CreateActor<ContentNpc>(UpdateOrder::RenderActor);
	_Npc->Transform.SetLocalPosition({ 2550, -817 });
	_Npc->Init("GentleCatMask", "신사고냥이가면", ActorDir::Right, 0.18f);
	_Npc->CreateOneButtonMent("Npc_Ok");
	_Npc->SetMentText(L"신사고냥이가면");

	_Npc = CreateActor<ContentNpc>(UpdateOrder::RenderActor);
	_Npc->Transform.SetLocalPosition({ 2360, -817 });
	_Npc->Init("RabbitMask", "토끼가면", ActorDir::Left);
	_Npc->CreateOneButtonMent("Npc_Ok");
	_Npc->SetMentText(L"토끼가면");

	_Npc = CreateActor<ContentNpc>(UpdateOrder::RenderActor);
	_Npc->Transform.SetLocalPosition({ 2260, -817 });
	_Npc->Init("CatMask", "고양이가면", ActorDir::Left, 0.21f);
	_Npc->CreateOneButtonMent("Npc_Ok");
	_Npc->SetMentText(L"고양이가면");

	_Npc = CreateActor<ContentNpc>(UpdateOrder::RenderActor);
	_Npc->Transform.SetLocalPosition({ 1600, -817 });
	_Npc->Init("PiedPiperMask", "피리리가면", ActorDir::Left, 0.18f);
	_Npc->CreateOneButtonMent("Npc_Ok");
	_Npc->SetMentText(L"피리리가면");

	_Npc = CreateActor<ContentNpc>(UpdateOrder::RenderActor);
	_Npc->Transform.SetLocalPosition({ 1500, -817 });
	_Npc->Init("GasMask", "방독면", ActorDir::Right);
	_Npc->CreateOneButtonMent("Npc_Ok");
	_Npc->SetMentText(L"방독면");

	_Npc = CreateActor<ContentNpc>(UpdateOrder::RenderActor);
	_Npc->Transform.SetLocalPosition({ 1270, -790 });
	_Npc->Init("ShrimpMask_Ani", "새우가면", ActorDir::Right, 0.15f);
	_Npc->CreateOneButtonMent("Npc_Ok");
	_Npc->SetMentText(L"새우가면");

	_Npc = CreateActor<ContentNpc>(UpdateOrder::RenderActor);
	_Npc->Transform.SetLocalPosition({ 1100, -790 });
	_Npc->Init("OctopusMask", "문어가면", ActorDir::Left, 0.15f);
	_Npc->CreateOneButtonMent("Npc_Ok");
	_Npc->SetMentText(L"문어가면");

	_Npc = CreateActor<ContentNpc>(UpdateOrder::RenderActor);
	_Npc->Transform.SetLocalPosition({ 980, -500 });
	_Npc->Init("DandyMask", "멋쟁이가면", ActorDir::Right, 0.18f);
	_Npc->CreateOneButtonMent("Npc_Ok");
	_Npc->SetMentText(L"멋쟁이가면");

	Minimap::CreateMinimap("Minimap_Lachlen.png", "레헬른 중심가");

	//test
	CreateActor<DamageSkinManager>();
	///

	if (false == BGMPlayer.IsPlaying())
	{
		BGMPlayer = GameEngineSound::SoundPlay("Lachlen.mp3", 10000);
		return;
	}

	std::string BGMName = BGMPlayer.GetCurSoundName();
	if ("Lachlen.mp3" != BGMName)
	{
		BGMPlayer.Stop();
		BGMPlayer = GameEngineSound::SoundPlay("Lachlen.mp3", 10000);
	}

}

void Lachlen::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);

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

	MapObjects.clear();

	if (nullptr != GameEngineSprite::Find("WaterMelonMen"))
	{
		ReleaseFunction::FolderRelease("WaterMelonMen", "WaterMelonMen_");
	}

	if (nullptr != GameEngineSprite::Find("Boat1"))
	{
		ReleaseFunction::FolderRelease("Boat1", "Boat1_");
	}

	if (nullptr != GameEngineSprite::Find("Wood1.png"))
	{
		GameEngineTexture::Release("Wood1.png");
		GameEngineSprite::Release("Wood1.png");
	}

	if (nullptr != GameEngineSprite::Find("Wood2.png"))
	{
		GameEngineTexture::Release("Wood2.png");
		GameEngineSprite::Release("Wood2.png");
	}

	if (nullptr != GameEngineSprite::Find("Wood3.png"))
	{
		GameEngineTexture::Release("Wood3.png");
		GameEngineSprite::Release("Wood3.png");
	}

	if (nullptr != GameEngineSprite::Find("Bridge.png"))
	{
		GameEngineTexture::Release("Bridge.png");
		GameEngineSprite::Release("Bridge.png");
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