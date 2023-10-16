#include "PreCompile.h"
#include "Lucid_Phase2.h"
#include "Player.h"
#include "ContentMap.h"
#include "SkillManager.h"
#include "ContentBackGround.h"
#include "RenderActor.h"

void FootHold::Init(int _FootHoldNumber)

{
	RenderActor::Init(RenderOrder::MAP, RenderDepth::map);
	Renderer->CreateAnimation("Idle", "StainedGlass" + std::to_string(_FootHoldNumber) + "_Idle");
	Renderer->ChangeAnimation("Idle");
	Renderer->SetPivotType(PivotType::Bottom);
}

Lucid_Phase2::Lucid_Phase2()
{

}

Lucid_Phase2::~Lucid_Phase2()
{

}

void Lucid_Phase2::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	if (nullptr == GameEngineSprite::Find("BackStar1.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\MapObject\\Lucid_Phase2");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{  
			GameEngineFile& Childs = Files[i];
			GameEngineTexture::Load(Childs.GetStringPath());
			GameEngineSprite::CreateSingle(Childs.GetFileName());
		}
	}

	if (nullptr == GameEngineSprite::Find("StainedGlass0_Idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\MapObject\\Lucid_Phase2\\StainedGlass");
		for (size_t i = 0; i < 6; i++)
		{
			if (0 != i)
			{
				Dir.MoveParent();
			}
			Dir.MoveChild(std::to_string(i));
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();
			for (size_t x = 0; x < Directorys.size(); x++)
			{
				GameEngineDirectory& Childs = Directorys[x];
				GameEngineSprite::CreateFolder("StainedGlass" + std::to_string(i) + + "_" +Childs.GetFileName(), Childs.GetStringPath());
			}
		}
	}

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMapCollision("Collision_Lucid_Phase2.png");
	}

	if (nullptr == Back)
	{
		Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
		Back->Init("BG_Lucid_Phase2.png");
	}

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
		CurPlayer->Transform.SetLocalPosition({ 1120, -850 });
		GetMainCamera()->Transform.SetLocalPosition({ 1120, -850 });
	}

	if (nullptr == SkillManagerActor)
	{
		SkillManagerActor = CreateActor<SkillManager>();
	}

	// 2050, 1550
	// StarObject
	std::shared_ptr<RenderActor> BackObject1 = CreateActor<RenderActor>(UpdateOrder::RenderActor);
	BackObject1->Init(RenderOrder::BACKGROUND, RenderDepth::background);
	BackObject1->Renderer->SetSprite("BackStar1.png");
	BackObject1->Renderer->SetPivotType(PivotType::Bottom);
	BackObject1->Transform.SetLocalPosition({ 300, -1100 });

	BackObject1 = CreateActor<RenderActor>(UpdateOrder::RenderActor);
	BackObject1->Init(RenderOrder::BACKGROUND, RenderDepth::background);
	BackObject1->Renderer->SetSprite("BackStar2.png");
	BackObject1->Renderer->SetPivotType(PivotType::Bottom);
	BackObject1->Transform.SetLocalPosition({ 1100, -1850 });

	BackObject1 = CreateActor<RenderActor>(UpdateOrder::RenderActor);
	BackObject1->Init(RenderOrder::BACKGROUND, RenderDepth::background);
	BackObject1->Renderer->SetSprite("BackStar3.png");
	BackObject1->Renderer->SetPivotType(PivotType::Bottom);
	BackObject1->Transform.SetLocalPosition({ 1550, -1100 });

	std::shared_ptr<FootHold> FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(0);
	FootHold1->Transform.SetLocalPosition({ 712, -1277 });

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(0);
	FootHold1->Transform.SetLocalPosition({ 1120, -913 });

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(0);
	FootHold1->Transform.SetLocalPosition({ 730, -550 });

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(1);
	FootHold1->Transform.SetLocalPosition({ 563, -845 });

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(1);
	FootHold1->Transform.SetLocalPosition({ 1198, -1200 });

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(1);
	FootHold1->Transform.SetLocalPosition({ 1507, -775 });

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(2);
	FootHold1->Transform.SetLocalPosition({ 1555, -1255 });

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(2);
	FootHold1->Transform.SetLocalPosition({ 530, -1130 });

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(2);
	FootHold1->Transform.SetLocalPosition({ 935, -712 });

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(3);
	FootHold1->Transform.SetLocalPosition({ 783, -1020 });

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(3);
	FootHold1->Transform.SetLocalPosition({ 1370, -1065 });

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(4);
	FootHold1->Transform.SetLocalPosition({ 475, -698 });

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(4);
	FootHold1->Transform.SetLocalPosition({ 1610, -1013 });

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(5);
	FootHold1->Transform.SetLocalPosition({ 1417, -550 });


	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(5);
	FootHold1->Transform.SetLocalPosition({ 1009, -1346 });

	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
}

void Lucid_Phase2::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
	if (nullptr != CurPlayer)
	{
		CurPlayer = nullptr;
	}

	if (nullptr != SkillManagerActor)
	{
		SkillManagerActor = nullptr;
	}

	if (nullptr != Boss)
	{
		Boss = nullptr;
	}
}

void Lucid_Phase2::Start()
{
	ContentLevel::Start();
	// GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
}

void Lucid_Phase2::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	if (Player::MainPlayer->Transform.GetWorldPosition().Y == - CurMapScale.Y)
	{
		Player::MainPlayer->Transform.SetLocalPosition({ 1120, -800 });
		Player::MainPlayer->MoveVectorForceReset();
	}
}