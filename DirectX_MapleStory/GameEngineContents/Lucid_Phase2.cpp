#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "Lucid_Phase2.h"
#include "Player.h"
#include "ContentMap.h"
#include "SkillManager.h"
#include "ContentBackGround.h"
#include "RenderActor.h"
#include "Boss_Lucid_Phase2.h"
#include "Dragon.h"

#define FALL_SPEED1 60.0f
#define FALL_SPEED2 55.0f
#define FALL_SPEED3 50.0f
#define FALL_SPEED4 45.0f
#define FALL_SPEED5 40.0f
#define FALL_SPEED6 35.0f
#define FALL_SPEED7 30.0f
#define FALL_SPEED8 25.0f
#define FALL_SPEED9 20.0f
#define FALL_SPEED10 10.0f
#define FALL_SPEED11 300.0f

void FallingObject::Init(int _ObjectNumber, float _Speed, float _StartPos, int _RenderOrder, float _RenderDepth)
{
	float Depth = _RenderDepth;
	if (20 >= _ObjectNumber)
	{
	}
	else if (29 >= _ObjectNumber)
	{
		Depth += 0.2f;
	}
	else if (36 >= _ObjectNumber)
	{
		Depth += 0.4f;
	}
	else
	{
		Depth += 0.6f;
	}

	RenderActor::Init(_RenderOrder, Depth);

	if (10 > _ObjectNumber)
	{
		Renderer->SetSprite("FallingObject_00" + std::to_string(_ObjectNumber) + ".png");
	}
	else
	{
		Renderer->SetSprite("FallingObject_0"+ std::to_string(_ObjectNumber) + ".png");
	}
	Renderer->SetPivotType(PivotType::Bottom);

	ObjectSpeed = _Speed;
	StartPos = _StartPos;
}

void FallingObject::Update(float _Delta)
{
	Transform.AddLocalPosition(float4::UP * ObjectSpeed * _Delta);

	if (0.0f <= Transform.GetWorldPosition().Y)
	{
		Transform.SetLocalPosition({Transform.GetLocalPosition().X, -StartPos });
	}
}

void FootHold::Init(int _FootHoldNumber)
{
	FootHoldNumber = _FootHoldNumber;
	RenderActor::Init(RenderOrder::MAP, RenderDepth::map);
	Renderer->CreateAnimation("Idle", "StainedGlass" + std::to_string(_FootHoldNumber) + "_Idle", 0.09f);
	Renderer->CreateAnimation("Break", "StainedGlass" + std::to_string(_FootHoldNumber) + "_Break", 0.09f, -1, -1, false);
	IdleStart();
}

void FootHold::ChangeState(FootHoldState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case FootHold::FootHoldState::Idle:
			IdleStart();
			break;
		case FootHold::FootHoldState::Break:
			BreakStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void FootHold::StateUpdate(float _Delta)
{
	switch (State)
	{
	case FootHoldState::Idle:
		return IdleUpdate(_Delta);
		break;
	case FootHoldState::Break:
		return BreakUpdate(_Delta);
		break;
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

void FootHold::IdleStart()
{
	Renderer->ChangeAnimation("Idle");
	Renderer->SetPivotType(PivotType::Bottom);
}

void FootHold::BreakStart()
{
	Renderer->ChangeAnimation("Break");
	Renderer->SetPivotType(PivotType::Center);
}

void FootHold::IdleUpdate(float _Delta)
{
	if (1.0f > Renderer->GetColorData().MulColor.A)
	{
		Renderer->GetColorData().MulColor.A += _Delta;
	}
}

void FootHold::BreakUpdate(float _Delta)
{
	BreakTime += _Delta;
	if (2.0f <= BreakTime)
	{
		ChangeState(FootHoldState::Idle);
		Renderer->GetColorData().MulColor.A = 0.0f;
	}
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
		Dir.MoveChild("ContentResources\\Textures\\MapObject\\Lucid_Phase2\\StarObject");
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

	if (nullptr == GameEngineSprite::Find("FallingObject_001.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\MapObject\\Lucid_Phase2\\FallingObject");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& Childs = Files[i];
			GameEngineTexture::Load(Childs.GetStringPath(), "FallingObject_" + Childs.GetFileName());
			GameEngineSprite::CreateSingle("FallingObject_" + Childs.GetFileName());
		}
	}

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMapCollision("Collision_Lucid_Phase2.png");
		CurMap->GetMapScale().Y = 1550.0f;
	}

	if (nullptr == Back)
	{
		Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
		Back->Init("BG_Lucid_Phase2.png");
	}

	if (nullptr == Boss)
	{
		Boss = CreateActor<Boss_Lucid_Phase2>(UpdateOrder::Monster);
		Boss->Transform.SetLocalPosition(float4(1000, -850));
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

	if (nullptr == LeftDragon)
	{
		LeftDragon = CreateActor<Dragon>(UpdateOrder::Monster);
		LeftDragon->Transform.SetLocalPosition(float4(50, 200));
		LeftDragon->SetDir(ActorDir::Right);
		LeftDragon->SetBreathPos({ 1100, 150 });
		LeftDragon->SetDestination_YPos(-1050.0f);
		LeftDragon->SetBreathMinMaxPos(850.0f, 1200.0f);
	}

	if (nullptr == RightDragon)
	{
		RightDragon = CreateActor<Dragon>(UpdateOrder::Monster);
		RightDragon->Transform.SetLocalPosition(float4(2000, 200));
		RightDragon->SetDir(ActorDir::Left);
		RightDragon->SetBreathPos({ -1100, 150 });
		RightDragon->SetDestination_YPos(-1050.0f);
		RightDragon->SetBreathMinMaxPos(850.0f, 1200.0f);
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

	// FootHold Renderer
	std::shared_ptr<FootHold> FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(0);
	FootHold1->Transform.SetLocalPosition({ 712, -1277 });
	AllFootHolds.push_back(FootHold1);

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(0);
	FootHold1->Transform.SetLocalPosition({ 1120, -913 });
	AllFootHolds.push_back(FootHold1);

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(0);
	FootHold1->Transform.SetLocalPosition({ 730, -550 });
	AllFootHolds.push_back(FootHold1);

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(1);
	FootHold1->Transform.SetLocalPosition({ 563, -845 });
	AllFootHolds.push_back(FootHold1);

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(1);
	FootHold1->Transform.SetLocalPosition({ 1198, -1200 });
	AllFootHolds.push_back(FootHold1);

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(1);
	FootHold1->Transform.SetLocalPosition({ 1507, -775 });
	AllFootHolds.push_back(FootHold1);

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(2);
	FootHold1->Transform.SetLocalPosition({ 1555, -1255 });
	AllFootHolds.push_back(FootHold1);

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(2);
	FootHold1->Transform.SetLocalPosition({ 530, -1130 });
	AllFootHolds.push_back(FootHold1);

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(2);
	FootHold1->Transform.SetLocalPosition({ 935, -712 });
	AllFootHolds.push_back(FootHold1);

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(3);
	FootHold1->Transform.SetLocalPosition({ 783, -1020 });
	AllFootHolds.push_back(FootHold1);

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(3);
	FootHold1->Transform.SetLocalPosition({ 1370, -1065 });
	AllFootHolds.push_back(FootHold1);

	////// UnBreak FootHold [11]~[14]
	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(4);
	FootHold1->Transform.SetLocalPosition({ 475, -698 });
	AllFootHolds.push_back(FootHold1);

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(4);
	FootHold1->Transform.SetLocalPosition({ 1610, -1013 });
	AllFootHolds.push_back(FootHold1);

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(5);
	FootHold1->Transform.SetLocalPosition({ 1417, -550 });
	AllFootHolds.push_back(FootHold1);

	FootHold1 = CreateActor<FootHold>(UpdateOrder::RenderActor);
	FootHold1->Init(5);
	FootHold1->Transform.SetLocalPosition({ 1009, -1346 });
	AllFootHolds.push_back(FootHold1);

	// FallingObject

	// Front Object
	//std::shared_ptr<FallingObject> FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	//FallObject->Transform.SetLocalPosition({ 423, -12, 0 });
	//FallObject->Init(58, FALL_SPEED11, 10000, RenderOrder::RENDERACTOR, RenderDepth::renderactor);
	//MapObjects.push_back(FallObject);

	//FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	//FallObject->Transform.SetLocalPosition({ 1021, 1575, 0 });
	//FallObject->Init(59, FALL_SPEED11, 10000, RenderOrder::RENDERACTOR, RenderDepth::renderactor);
	//MapObjects.push_back(FallObject);

	//FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	//FallObject->Transform.SetLocalPosition({ 24, 4996, 0 });
	//FallObject->Init(60, FALL_SPEED11, 10000, RenderOrder::RENDERACTOR, RenderDepth::renderactor);
	//MapObjects.push_back(FallObject);

	//FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	//FallObject->Transform.SetLocalPosition({ 482, 6000, 0 });
	//FallObject->Init(61, FALL_SPEED11, 10000, RenderOrder::RENDERACTOR, RenderDepth::renderactor);
	//MapObjects.push_back(FallObject);

	//// BackBackBackBack
	std::shared_ptr<FallingObject> FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 510, -1428, 0 });
	FallObject->Init(49, FALL_SPEED10, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 950, -921, 0 });
	FallObject->Init(50, FALL_SPEED9, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 850, -790, 0 });
	FallObject->Init(50, FALL_SPEED9, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 750, -224, 0 });
	FallObject->Init(51, FALL_SPEED9, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 750, -743, 0 });
	FallObject->Init(51, FALL_SPEED9, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1590, -605, 0 });
	FallObject->Init(52, FALL_SPEED9, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1450, -228, 0 });
	FallObject->Init(53, FALL_SPEED9, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1170, -6, 0 });
	FallObject->Init(54, FALL_SPEED9, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 960, -409, 0 });
	FallObject->Init(55, FALL_SPEED9, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 880, -294, 0 });
	FallObject->Init(56, FALL_SPEED9, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 530, -218, 0 });
	FallObject->Init(57, FALL_SPEED9, 2000);
	MapObjects.push_back(FallObject);

	//// BackBackBack
	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 650, -905, 0 });
	FallObject->Init(37, FALL_SPEED8, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 810, -844, 0 });
	FallObject->Init(38, FALL_SPEED8, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1400, -1469, 0 });
	FallObject->Init(39, FALL_SPEED8, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 720, -1361, 0 });
	FallObject->Init(40, FALL_SPEED8, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 120, -1242, 0 });
	FallObject->Init(41, FALL_SPEED8, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1550, -786, 0 });
	FallObject->Init(42, FALL_SPEED8, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 570, -857, 0 });
	FallObject->Init(43, FALL_SPEED8, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1430, -193, 0 });
	FallObject->Init(44, FALL_SPEED8, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1380, -537, 0 });
	FallObject->Init(45, FALL_SPEED8, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 840, -379, 0 });
	FallObject->Init(46, FALL_SPEED8, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 920, -255, 0 });
	FallObject->Init(47, FALL_SPEED8, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 480, -1454, 0 });
	FallObject->Init(48, FALL_SPEED8, 2000);
	MapObjects.push_back(FallObject);

	//// BackBack
	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1550, -363, 0 });
	FallObject->Init(30, FALL_SPEED7, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 700, -624, 0 });
	FallObject->Init(31, FALL_SPEED7, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 910, -280, 0 });
	FallObject->Init(32, FALL_SPEED7, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 910, -288, 0 });
	FallObject->Init(32, FALL_SPEED7, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1500, -1014, 0 });
	FallObject->Init(33, FALL_SPEED7, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1260, -267, 0 });
	FallObject->Init(34, FALL_SPEED7, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 830, -1135, 0 });
	FallObject->Init(35, FALL_SPEED7, 2000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1190, -767, 0 });
	FallObject->Init(36, FALL_SPEED7, 2000);
	MapObjects.push_back(FallObject);

	//// Back
	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 670, -1670, 0 });
	FallObject->Init(21, FALL_SPEED6, 3000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1400, -2230, 0 });
	FallObject->Init(22, FALL_SPEED6, 3000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 820, -634, 0 });
	FallObject->Init(23, FALL_SPEED6, 3000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1330, -2332, 0 });
	FallObject->Init(24, FALL_SPEED6, 3000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 430, -1501, 0 });
	FallObject->Init(25, FALL_SPEED6, 3000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1560, -1689, 0 });
	FallObject->Init(26, FALL_SPEED6, 3000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1380, -961, 0 });
	FallObject->Init(27, FALL_SPEED6, 3000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1810, -1383, 0 });
	FallObject->Init(28, FALL_SPEED6, 3000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 780, -197, 0 });
	FallObject->Init(29, FALL_SPEED6, 3000);
	MapObjects.push_back(FallObject);

	//// 
	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 950, -4000, 0 });
	FallObject->Init(1, FALL_SPEED1, 7000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1500, -243, 0 });
	FallObject->Init(2, FALL_SPEED1, 7000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1050, -5068, 0 });
	FallObject->Init(3, FALL_SPEED2, 6000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1000, -2320, 0 });
	FallObject->Init(4, FALL_SPEED2, 6000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 350, -4017, 0 });
	FallObject->Init(5, FALL_SPEED2, 6000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 600, -4238, 0 });
	FallObject->Init(6, FALL_SPEED2, 6000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1300, -2607, 0 });
	FallObject->Init(7, FALL_SPEED2, 6000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1050, -2381, 0 });
	FallObject->Init(8, FALL_SPEED2, 6000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1450, -472, 0 });
	FallObject->Init(9, FALL_SPEED3, 6000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1250, -150, 0 });
	FallObject->Init(10, FALL_SPEED3, 6000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1550, -609, 0 });
	FallObject->Init(11, FALL_SPEED4, 5000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1500, -484, 0 });
	FallObject->Init(12, FALL_SPEED4, 5000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 650, -40, 0 });
	FallObject->Init(13, FALL_SPEED4, 5000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1130, -502, 0 });
	FallObject->Init(14, FALL_SPEED5, 4000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1750, -773, 0 });
	FallObject->Init(15, FALL_SPEED5, 4000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 500, -1249, 0 });
	FallObject->Init(16, FALL_SPEED5, 4000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1200, -982, 0 });
	FallObject->Init(17, FALL_SPEED5, 4000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 400, -251, 0 });
	FallObject->Init(18, FALL_SPEED5, 4000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 900, -321, 0 });
	FallObject->Init(19, FALL_SPEED6, 3000);
	MapObjects.push_back(FallObject);

	FallObject = CreateActor<FallingObject>(UpdateOrder::RenderActor);
	FallObject->Transform.SetLocalPosition({ 1850, -683, 0 });
	FallObject->Init(20, FALL_SPEED6, 3000);
	MapObjects.push_back(FallObject);

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

	for (size_t i = 0; i < AllFootHolds.size(); i++)
	{
		AllFootHolds[i]->Death();
		AllFootHolds[i] = nullptr;
	}

	MapObjects.clear();
	AllFootHolds.clear();
}

void Lucid_Phase2::Start()
{
	ContentLevel::Start();
	MapObjects.reserve(100);
	AllFootHolds.reserve(15);
}

void Lucid_Phase2::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
	ObjectUpdate(_Delta);

	if (Player::MainPlayer->Transform.GetWorldPosition().Y <= -CurMapScale.Y)
	{
		Player::MainPlayer->Transform.SetLocalPosition({ 1120, -800 });
		Player::MainPlayer->MoveVectorForceReset();
	}

	if (true == GameEngineInput::IsDown('K', this))
	{
		for (size_t i = 0; i < AllFootHolds.size(); i++)
		{
			AllFootHolds[i]->ChangeState(FootHold::FootHoldState::Break);
		}
	}

	if (true == GameEngineInput::IsDown('L', this))
	{
		for (size_t i = 0; i < AllFootHolds.size(); i++)
		{
			AllFootHolds[i]->ChangeState(FootHold::FootHoldState::Idle);
		}
	}
}

void Lucid_Phase2::ObjectUpdate(float _Delta)
{
	for (size_t i = 0; i < MapObjects.size(); i++)
	{
		// std::shared_ptr<FallingObject> CurObject = MapObjects[i];
		MapObjects[i]->Update(_Delta);
	}

	for (size_t i = 0; i < AllFootHolds.size(); i++)
	{
		AllFootHolds[i]->StateUpdate(_Delta);
	}
}

void Lucid_Phase2::CallDragon()
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