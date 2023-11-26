#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "Lucid_Phase1.h"
#include "Player.h"
#include "ContentMap.h"
#include "SkillManager.h"
#include "ContentBackGround.h"
#include "Boss_Lucid_Phase1.h"
#include "Dragon.h"
#include "Laser.h"
#include "RenderActor.h"
#include "FadeObject.h"
#include "Minimap.h"
#include "BossTimer.h"
#include "DeathCount.h"
#include "ReleaseFunction.h"
#include "PortalNpc.h"

#define Lase_Cooldown 8.0f

Lucid_Phase1::Lucid_Phase1()
{

}

Lucid_Phase1::~Lucid_Phase1()
{

}

void Lucid_Phase1::LevelStart(GameEngineLevel* _PrevLevel)
{
	PrevLevel = "10.Boss_WaitingRoom";
	NextLevel = "14.Lucid_Phase2";

	ContentLevel::LevelStart(_PrevLevel);

	FadeOutObject->SetChangeLevel("13.Lucid_Next");

	if (nullptr == GameEngineSprite::Find("BackObject1.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\MapObject\\Lucid_Phase1");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& Childs = Files[i];
			GameEngineTexture::Load(Childs.GetStringPath());
			GameEngineSprite::CreateSingle(Childs.GetFileName());
		}
	}

	// LaserResources
	if (nullptr == GameEngineSprite::Find("Phase1_S"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Laser\\");
		GameEngineSprite::CreateFolder(Dir.GetStringPath() + "Phase1_S");
		GameEngineSprite::CreateFolder(Dir.GetStringPath() + "Phase1_M");
		GameEngineSprite::CreateFolder(Dir.GetStringPath() + "Phase1_L");
		GameEngineSprite::CreateFolder(Dir.GetStringPath() + "Phase1_XL");
	}

	if (nullptr == GameEngineSprite::Find("Phase1_Hit"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Laser\\Phase1_Hit");
		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	}

	if (nullptr == GameEngineSound::FindSound("WierldForestIntheGirlsdream.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\BGM\\WierldForestIntheGirlsdream.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath());
	}

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMap("Lucid_Phase1.png");
		CurMap->InitMapCollision("Collision_Lucid_Phase1.png");
	}

	if (nullptr == Back)
	{
		Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
		Back->Init("BG_Lucid_Phase1.png");
	}
	
	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
		CurPlayer->Transform.SetLocalPosition(float4(100, -690));
		GetMainCamera()->Transform.SetLocalPosition(float4(100, -690, -100000));
	}

	if (nullptr == Boss)
	{
		Boss = CreateActor<Boss_Lucid_Phase1>(UpdateOrder::Monster);
		Boss->Transform.SetLocalPosition(float4(1000, -700));
	}

	// Dragon
	// while -750
	if (nullptr == LeftDragon)
	{
		LeftDragon = CreateActor<Dragon>(UpdateOrder::Monster);
		LeftDragon->Transform.SetLocalPosition(float4(30, 200));
		LeftDragon->SetDir(ActorDir::Right);
		LeftDragon->SetBreathPos({ 1100, 150 });
	}

	if (nullptr == RightDragon)
	{
		RightDragon = CreateActor<Dragon>(UpdateOrder::Monster);
		RightDragon->Transform.SetLocalPosition(float4(1970, 200));
		RightDragon->SetDir(ActorDir::Left);
		RightDragon->SetBreathPos({ -1100, 150 });
	}

	// BackGround Object
	{
		std::shared_ptr<RenderActor> BackObject1 = CreateActor<RenderActor>(UpdateOrder::RenderActor);
		BackObject1->Init(RenderOrder::BACKGROUND, RenderDepth::background);
		BackObject1->Renderer->SetSprite("BackObject1.png");
		BackObject1->Renderer->SetPivotType(PivotType::Bottom);
		BackObject1->Renderer->AutoSpriteSizeOff();
		BackObject1->Transform.SetLocalPosition({ 285 + 571, -700 });

		std::shared_ptr<GameEngineTexture> _Texture = GameEngineTexture::Find("BackObject1.png");
		float4 _TextureScale = _Texture->GetScale();

		BackObject1->Renderer->SetImageScale({ _TextureScale.X * 4.0f, _TextureScale.Y });
		BackObject1->Renderer->SetSampler("EngineBaseWRAPSampler");
		BackObject1->Renderer->RenderBaseInfoValue.VertexUVMul.X = 4.0f;
	}

	{
		std::shared_ptr<RenderActor> BackObject2 = CreateActor<RenderActor>(UpdateOrder::RenderActor);
		BackObject2->Init(RenderOrder::BACKGROUND, RenderDepth::background);
		BackObject2->Renderer->SetSprite("BackObject2.png");
		BackObject2->Renderer->SetPivotType(PivotType::Bottom);
		BackObject2->Renderer->AutoSpriteSizeOff();
		BackObject2->Transform.SetLocalPosition({ 326 + 652, -700 });

		std::shared_ptr<GameEngineTexture> _Texture = GameEngineTexture::Find("BackObject2.png");
		float4 _TextureScale = _Texture->GetScale();

		BackObject2->Renderer->SetImageScale({ _TextureScale.X * 3.0f, _TextureScale.Y });
		BackObject2->Renderer->SetSampler("EngineBaseWRAPSampler");
		BackObject2->Renderer->RenderBaseInfoValue.VertexUVMul.X = 3.0f;

	}

	{
		std::shared_ptr<RenderActor> BackObject3 = CreateActor<RenderActor>(UpdateOrder::RenderActor);
		BackObject3->Init(RenderOrder::BACKGROUND, RenderDepth::background);
		BackObject3->Renderer->SetSprite("BackObject3.png");
		BackObject3->Renderer->SetPivotType(PivotType::Bottom);
		BackObject3->Renderer->AutoSpriteSizeOff();
		BackObject3->Transform.SetLocalPosition({ 888, -700 });

		std::shared_ptr<GameEngineTexture> _Texture = GameEngineTexture::Find("BackObject3.png");
		float4 _TextureScale = _Texture->GetScale();

		BackObject3->Renderer->SetImageScale({ _TextureScale.X * 3.0f, _TextureScale.Y });
		BackObject3->Renderer->SetSampler("EngineBaseWRAPSampler");
		BackObject3->Renderer->RenderBaseInfoValue.VertexUVMul.X = 3.0f;
	}

	for (size_t i = 1; i < 5; i++)
	{
		std::shared_ptr<RenderActor> BackTree = CreateActor<RenderActor>(UpdateOrder::RenderActor);
		BackTree->Init(RenderOrder::BACKGROUND, RenderDepth::background);
		BackTree->Renderer->SetSprite("BackTree" + std::to_string(i) + ".png");
		BackTree->Renderer->SetPivotType(PivotType::Bottom);
		BackTree->Transform.SetLocalPosition({ -250 + static_cast<float>(i) * 500, -660 });
	}

	// Map Object
	for (size_t i = 0; i < 5; i++)
	{
		std::shared_ptr<FlowObject> Water = CreateActor<FlowObject>(UpdateOrder::RenderActor);
		Water->RenderActor::Init(RenderOrder::MAPOBJECT, RenderDepth::mapobject);
		Water->Init("Water.png", 20.0f, float4{ -1000, -830 }, float4{ 2400, -830 });
		Water->Transform.SetLocalPosition({ -900 + 700 * static_cast<float>(i), -830, 0 });
		MapObjects.push_back(Water);
	}

	for (size_t i = 0; i < 3; i++)
	{
		std::shared_ptr<FlowObject> Flower = CreateActor<FlowObject>(UpdateOrder::RenderActor);
		Flower->RenderActor::Init(RenderOrder::MAPOBJECT, RenderDepth::mapobject);
		Flower->Init("Flower1.png", 20.0f, float4{ -800, -860 }, float4{ 2200, -860 });
		Flower->Transform.SetLocalPosition({ -200 - 1000 * static_cast<float>(i), -860, 0 });
		MapObjects.push_back(Flower);
	}

	for (size_t i = 0; i < 3; i++)
	{
		std::shared_ptr<FlowObject> Flower = CreateActor<FlowObject>(UpdateOrder::RenderActor);
		Flower->RenderActor::Init(RenderOrder::MAPOBJECT, RenderDepth::mapobject);
		Flower->Init("Flower2.png", 20.0f, float4{ -1400, -790, 0 }, float4{ 2200, -790, 0 });
		Flower->Transform.SetLocalPosition({ -500 - 1200 * static_cast<float>(i), -790, 0 });
		MapObjects.push_back(Flower);
	}

	Minimap::CreateMinimap("Minimap_Lucid_Phase1.png", "몽환의 숲");
	CreateActor<BossTimer>(UpdateOrder::UI);
	BossTimer::TimeValue = 1800.0f;
	CreateActor<DeathCount>(UpdateOrder::UI);

	std::shared_ptr<PortalNpc> _Portal = CreateActor<PortalNpc>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 100, -720 });

	if (false == BGMPlayer.IsPlaying())
	{
		BGMPlayer = GameEngineSound::SoundPlay("WierldForestIntheGirlsdream.mp3", 10000);
		return;
	}

	std::string BGMName = BGMPlayer.GetCurSoundName();
	if ("WierldForestIntheGirlsdream.mp3" != BGMName)
	{
		BGMPlayer.Stop();
		BGMPlayer = GameEngineSound::SoundPlay("WierldForestIntheGirlsdream.mp3", 10000);
	}
}

void Lucid_Phase1::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);

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

	if (nullptr != Boss)
	{
		Boss = nullptr;
	}

	if (nullptr != LeftDragon)
	{
		LeftDragon = nullptr;
	}

	if (nullptr != RightDragon)
	{
		RightDragon = nullptr;
	}

	for (size_t i = 0; i < MapObjects.size(); i++)
	{
		MapObjects[i]->Death();
		MapObjects[i] = nullptr;
	}
	MapObjects.clear();

	if (nullptr != GameEngineSprite::Find("BackObject1.png"))
	{
		GameEngineTexture::Release("BackObject1.png");
		GameEngineSprite::Release("BackObject1.png");

		GameEngineTexture::Release("BackObject2.png");
		GameEngineSprite::Release("BackObject2.png");

		GameEngineTexture::Release("BackObject3.png");
		GameEngineSprite::Release("BackObject3.png");

		GameEngineTexture::Release("BackTree1.png");
		GameEngineSprite::Release("BackTree1.png");

		GameEngineTexture::Release("BackTree2.png");
		GameEngineSprite::Release("BackTree2.png");

		GameEngineTexture::Release("BackTree3.png");
		GameEngineSprite::Release("BackTree3.png");

		GameEngineTexture::Release("BackTree4.png");
		GameEngineSprite::Release("BackTree4.png");
	}

	if (nullptr != GameEngineSprite::Find("Phase1_S"))
	{
		ReleaseFunction::FolderRelease("Phase1_S", "Phase1_S_");
		ReleaseFunction::FolderRelease("Phase1_M", "Phase1_M_");
		ReleaseFunction::FolderRelease("Phase1_L", "Phase1_L_");
		ReleaseFunction::FolderRelease("Phase1_XL", "Phase1_XL_");
	}

	if (nullptr != GameEngineSprite::Find("Phase1_Hit"))
	{
		ReleaseFunction::FolderRelease("Phase1_Hit", "Phase1_Hit_");
	}

	if (nullptr != GameEngineSprite::Find("Lucid_Phase1_Golem_Ready"))
	{
		ReleaseFunction::FolderRelease("Lucid_Phase1_Golem_Ready", "Phase1_Golem_Ready_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Golem_Attack", "Phase1_Golem_Attack_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Golem_Death", "Phase1_Golem_Death_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Golem_Idle", "Phase1_Golem_Idle_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Golem_Revive", "Phase1_Golem_Revive_");
	}

	if (nullptr != GameEngineSprite::Find("Lucid_Phase1_Golem_TakeDown_Hit"))
	{
		ReleaseFunction::FolderRelease("Lucid_Phase1_Golem_TakeDown_Hit", "TakeDown_Hit_");
	}

	if (nullptr != GameEngineSprite::Find("Phase1_ButterFly_Ready"))
	{
		ReleaseFunction::FolderRelease("Phase1_ButterFly_Ready", "Phase1_ButterFly_Ready_");
		ReleaseFunction::FolderRelease("Phase1_ButterFly_Attack", "Phase1_ButterFly_Attack_");
		ReleaseFunction::FolderRelease("Phase1_ButterFly_Move", "Phase1_ButterFly_Move_");
		ReleaseFunction::FolderRelease("Phase1_ButterFly_Death", "Phase1_ButterFly_Death_");

		ReleaseFunction::FolderRelease("Phase1_ButterFly_Ball_Ball", "Phase1_ButterFly_Ball_Ball_");
		ReleaseFunction::FolderRelease("Phase1_ButterFly_Ball_Hit", "Phase1_ButterFly_Ball_Hit_");
	}

	if (nullptr != GameEngineSprite::Find("PhantasmalWind"))
	{
		ReleaseFunction::FolderRelease("PhantasmalWind", "PhantasmalWind_");
		ReleaseFunction::FolderRelease("PhantasmalWind_Hit", "PhantasmalWind_Hit_");
	}

	if (nullptr != GameEngineSprite::Find("WarningMent_Start.png"))
	{
		GameEngineTexture::Release("WarningMent_Start.png");
		GameEngineSprite::Release("WarningMent_Start.png");

		GameEngineTexture::Release("WarningMent_Middle.png");
		GameEngineSprite::Release("WarningMent_Middle.png");

		GameEngineTexture::Release("WarningMent_End.png");
		GameEngineSprite::Release("WarningMent_End.png");
	}
}

void Lucid_Phase1::Start()
{
	ContentLevel::Start();
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	MapObjects.reserve(11);
}

void Lucid_Phase1::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
	ObjectUpdate(_Delta);

	// Laser Pattern
	LaserCooldown -= _Delta;
	if (0.0f >= LaserCooldown)
	{
		GameEngineRandom Random;

		for (size_t i = 0; i < 7; i++)
		{
			std::shared_ptr<Laser> _Laser = CreateActor<Laser>(UpdateOrder::Monster);
			Random.SetSeed(reinterpret_cast<long long>(_Laser.get()));
			float4 RandomValue = Random.RandomVectorBox2D(0, 3, 0, 180.0f);
			switch (RandomValue.iX())
			{
			case 0:
				_Laser->Init("Phase1_S");
				_Laser->SetColScale({ 45, 320 });
				break;
			case 1:
				_Laser->Init("Phase1_M");
				_Laser->SetColScale({ 65, 420 });
				break;
			case 2:
				_Laser->Init("Phase1_L");
				_Laser->SetColScale({100, 570});
				break;
			case 3:
				_Laser->Init("Phase1_XL");
				_Laser->SetColScale({ 110, 670 });
				break;
			default:
				break;
			}
			_Laser->SetAngle(RandomValue.Y);

			float4 RandomFloat4 = Random.RandomVectorBox2D(300 + 200 * static_cast<float>(i), 300 + 200 * static_cast<float>((i + 1)), -500, -600);
			_Laser->Transform.SetLocalPosition(RandomFloat4);
		}
		LaserCooldown = Lase_Cooldown;
	}
}

void Lucid_Phase1::CallDragon()
{
	GameEngineRandom Random;
	Random.SetSeed(time(nullptr));
	int RandomValue = Random.RandomInt(0, 1);

	if (0 == RandomValue)
	{
		LeftDragon->ChangeState(DragonState::Down);
	}
	else
	{
		RightDragon->ChangeState(DragonState::Down);
	}
}

void Lucid_Phase1::ObjectUpdate(float _Delta)
{
	for (size_t i = 0; i < MapObjects.size(); i++)
	{
		std::shared_ptr<FlowObject> CurObject = MapObjects[i];
		CurObject->Update(_Delta);
	}
}