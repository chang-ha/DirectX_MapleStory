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

#define Lase_Cooldown 8.0f

Lucid_Phase1::Lucid_Phase1()
{

}

Lucid_Phase1::~Lucid_Phase1()
{

}

void Lucid_Phase1::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->Init("Lucid_Phase1.png");
	}

	if (nullptr == Back)
	{
		Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
		Back->Init("BG_Lucid_Phase1.png");
	}
	
	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
		CurPlayer->Transform.SetLocalPosition(float4(100, -700));
		GetMainCamera()->Transform.SetLocalPosition(float4(100, -700));
	}

	if (nullptr == SkillManagerActor)
	{
		SkillManagerActor = CreateActor<SkillManager>();
	}

	if (nullptr == Boss)
	{
		Boss = CreateActor<Boss_Lucid_Phase1>(UpdateOrder::Monster);
		Boss->Transform.SetLocalPosition(float4(1000, -700));
	}

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
}

void Lucid_Phase1::Start()
{
	ContentLevel::Start();
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
}

void Lucid_Phase1::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

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
