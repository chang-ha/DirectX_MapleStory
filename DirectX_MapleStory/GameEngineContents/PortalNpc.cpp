#include "PreCompile.h"
#include "PortalNpc.h"
#include "Player.h"
#include "ContentLevel.h"
#include "FadeObject.h"

PortalNpc::PortalNpc()
{

}

PortalNpc::~PortalNpc()
{

}

void PortalNpc::Start()
{
	ContentNpc::Start();
	ContentNpc::Init("BossMapPortal", "포탈", ActorDir::Left, 0.09f);
	CreateTwoButtonMent("Npc_BossEnter_Cancel", "Npc_BossEnter_Ok", [=]()
		{
			NpcMentOff();
			std::shared_ptr<FadeObject> _FadeObject = ContentLevel::CurContentLevel->FadeOutObject;
			_FadeObject->SetChangeLevel("10.Boss_WaitingRoom");
			_FadeObject->FadeStart();
		});
	SetMentText(L"전투를 마치고 밖으로 나갈까?");

	NpcCollision->Transform.SetLocalScale({75, 120});

	NpcNameBGRenderer->Off();
	NpcNameRenderer->Off();
}

void PortalNpc::Update(float _Delta)
{
	ContentNpc::Update(_Delta);

	//if (false == Player::MainPlayer->GetGroundValue())
	//{
	//	return;
	//}

	//if (false == NpcCollision->Collision(CollisionOrder::Player))
	//{
	//	return;
	//}

	//if (true == GameEngineInput::IsDown(VK_UP, this))
	//{
	//	Ment->On();
	//	Player::MainPlayer->InputObjectOff();
	//}
}

void PortalNpc::Release()
{
	ContentNpc::Release();
}