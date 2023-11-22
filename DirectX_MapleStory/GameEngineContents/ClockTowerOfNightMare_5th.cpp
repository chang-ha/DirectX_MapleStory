#include "PreCompile.h"
#include "ClockTowerOfNightMare_5th.h"
#include "ContentMap.h"
#include "Player.h"
#include "Portal.h"
#include "Minimap.h"
#include "BlueEyed_Gargoyle.h"
#include "RedEyed_Gargoyle.h"
#include "LinkPortal.h"
#include "Boss_WaitingRoom.h"
#include "ReleaseFunction.h"

ClockTowerOfNightMare_5th::ClockTowerOfNightMare_5th()
{

}

ClockTowerOfNightMare_5th::~ClockTowerOfNightMare_5th()
{

}


void ClockTowerOfNightMare_5th::LevelStart(GameEngineLevel* _PrevLevel)
{
	PrevLevel = "08.ClockTowerOfNightMare_4th";
	NextLevel = "10.Boss_WaitingRoom";

	ClockTowerBaseLevel::LevelStart(_PrevLevel);

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMap("ClockOfTower_5th.png");
		CurMap->InitMapCollision("Collision_ClockOfTower_5th.png");
		CurMap->InitFootHold("ClockOfTower_5th_FootHold.png");
	}

	TeleportPos = float4(1150, -2780);

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
	}

	Boss_WaitingRoom* PrevLevel = dynamic_cast<Boss_WaitingRoom*>(_PrevLevel);
	if (nullptr != PrevLevel)
	{
		CurPlayer->Transform.SetLocalPosition({ 600, -350 });
		GetMainCamera()->Transform.SetLocalPosition(float4(600, -350, -100000));
	}
	else
	{
		CurPlayer->Transform.SetLocalPosition({ 500, -2878 });
		GetMainCamera()->Transform.SetLocalPosition(float4(500, -2878, -100000));
	}

	std::shared_ptr<Portal> _Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 600, -360 });
	_Portal->SetMoveMap("10.Boss_WaitingRoom");

	_Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 500, -2885 });
	_Portal->SetMoveMap("08.ClockTowerOfNightMare_4th");

	std::shared_ptr<LinkPortal> _LinkPortal1 = CreateActor<LinkPortal>(UpdateOrder::Portal);
	_LinkPortal1->Transform.SetLocalPosition({ 1150, -2845 });

	std::shared_ptr<LinkPortal> _LinkPortal2 = CreateActor<LinkPortal>(UpdateOrder::Portal);
	_LinkPortal2->Transform.SetLocalPosition({ 1350, -530 });
	_LinkPortal2->DoubleLinkPortal(_LinkPortal1.get());

	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
	Minimap::CreateMinimap("Minimap_ClockTowerOfNightMare_5th.png", "악몽의시계탑 5층");

	// CreateMonster<RedEyed_Gargoyle>({ 900, -525 });
	// CreateMonster<BlueEyed_Gargoyle>({1000, -525 });
	// CreateMonster<RedEyed_Gargoyle>({ 1150, -525 });
	// CreateMonster<RedEyed_Gargoyle>({ 970, -710 });
	// CreateMonster<BlueEyed_Gargoyle>({ 1100, -690 });
	// CreateMonster<RedEyed_Gargoyle>({ 800, -880 });
	// CreateMonster<BlueEyed_Gargoyle>({ 600, -1016 });
	// CreateMonster<BlueEyed_Gargoyle>({ 1080, -1057 });
	// CreateMonster<RedEyed_Gargoyle>({ 1330, -1133 });
	// CreateMonster<RedEyed_Gargoyle>({ 900, -1389 });
	// CreateMonster<BlueEyed_Gargoyle>({ 550, -1614 });
	// CreateMonster<BlueEyed_Gargoyle>({ 550, -2017 });
	// CreateMonster<RedEyed_Gargoyle>({ 780, -1943 });
	// CreateMonster<BlueEyed_Gargoyle>({ 1100, -1943 });
	// CreateMonster<RedEyed_Gargoyle>({ 1350, -2017 });
	// CreateMonster<RedEyed_Gargoyle>({ 700, -2289 });
	// CreateMonster<RedEyed_Gargoyle>({ 1150, -2288 });
	// CreateMonster<BlueEyed_Gargoyle>({ 510, -2364 });
	// CreateMonster<BlueEyed_Gargoyle>({ 1350, -2363});
	// CreateMonster<BlueEyed_Gargoyle>({ 800, -2465});
	// CreateMonster<RedEyed_Gargoyle>({ 600, -2540});
	// CreateMonster<BlueEyed_Gargoyle>({ 1100, -2577});
	// CreateMonster<RedEyed_Gargoyle>({ 700, -2802 });
	// CreateMonster<BlueEyed_Gargoyle>({ 650, -2953});
	// CreateMonster<RedEyed_Gargoyle>({ 750, -2953 });
	// CreateMonster<BlueEyed_Gargoyle>({ 1150, -2840});
	// CreateMonster<RedEyed_Gargoyle>({ 1350, -2765 });
}

void ClockTowerOfNightMare_5th::LevelEnd(GameEngineLevel* _NextLevel)
{
	ClockTowerBaseLevel::LevelEnd(_NextLevel);

	if (nullptr != GameEngineSprite::Find("BlueEyed_Gargoyle_Death"))
	{
		ReleaseFunction::FolderRelease("BlueEyed_Gargoyle_Death", "BlueEyed_Gargoyle_Death_");
		ReleaseFunction::FolderRelease("BlueEyed_Gargoyle_Attack", "BlueEyed_Gargoyle_Attack_");
		ReleaseFunction::FolderRelease("BlueEyed_Gargoyle_Attack_Hit", "BlueEyed_Gargoyle_Attack_Hit_");
		ReleaseFunction::FolderRelease("BlueEyed_Gargoyle_Idle", "BlueEyed_Gargoyle_Idle_");
		ReleaseFunction::FolderRelease("BlueEyed_Gargoyle_Move", "BlueEyed_Gargoyle_Move_");
		ReleaseFunction::FolderRelease("BlueEyed_Gargoyle_Ready", "BlueEyed_Gargoyle_Ready_");
	}

	if (nullptr != GameEngineSprite::Find("RedEyed_Gargoyle_Death"))
	{
		ReleaseFunction::FolderRelease("RedEyed_Gargoyle_Death", "RedEyed_Gargoyle_Death_");
		ReleaseFunction::FolderRelease("RedEyed_Gargoyle_Attack", "RedEyed_Gargoyle_Attack_");
		ReleaseFunction::FolderRelease("RedEyed_Gargoyle_Attack_Hit", "RedEyed_Gargoyle_Attack_Hit_");
		ReleaseFunction::FolderRelease("RedEyed_Gargoyle_Idle", "RedEyed_Gargoyle_Idle_");
		ReleaseFunction::FolderRelease("RedEyed_Gargoyle_Move", "RedEyed_Gargoyle_Move_");
		ReleaseFunction::FolderRelease("RedEyed_Gargoyle_Ready", "RedEyed_Gargoyle_Ready_");
	}
}

void ClockTowerOfNightMare_5th::Start()
{
	ClockTowerBaseLevel::Start();
}

void ClockTowerOfNightMare_5th::Update(float _Delta)
{
	ClockTowerBaseLevel::Update(_Delta);
}