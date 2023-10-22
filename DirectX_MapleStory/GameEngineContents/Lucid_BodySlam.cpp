#include "PreCompile.h"
#include "Lucid_BodySlam.h"


Lucid_BodySlam::Lucid_BodySlam()
{

}

Lucid_BodySlam::~Lucid_BodySlam()
{

}

void Lucid_BodySlam::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void Lucid_BodySlam::Start()
{
	if (nullptr == BodySlamRenderer)
	{
		BodySlamRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
		BodySlamRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::monster});
		BodySlamRenderer->AutoSpriteSizeOn();
	}

	if (nullptr == BodySlamCollision)
	{
		BodySlamCollision = CreateComponent<GameEngineCollision>(CollisionOrder::MonsterAttack);
	}


	if (nullptr == GameEngineSprite::Find("Lucid_BodySlam"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Phase2_BodySlam");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Lucid_BodySlam_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	BodySlamRenderer->CreateAnimation("Ready", "Lucid_BodySlam_Ready");
	BodySlamRenderer->CreateAnimation("Attack", "Lucid_BodySlam_Attack");
	BodySlamRenderer->CreateAnimation("Death", "Lucid_BodySlam_Death");
	BodySlamRenderer->ChangeAnimation("Ready");
	ReadyStart();
}

void Lucid_BodySlam::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Lucid_BodySlam::Release()
{
	if (nullptr != BodySlamRenderer)
	{
		BodySlamRenderer->Death();
		BodySlamRenderer = nullptr;
	}

	if (nullptr != BodySlamCollision)
	{
		BodySlamCollision->Death();
		BodySlamCollision = nullptr;
	}
}

void Lucid_BodySlam::ChangeState(BodySlamState _State)
{
	if (_State != State)
	{
		// State End
		switch (State)
		{
		case BodySlamState::Ready:
			ReadyStart();
			break;
		case BodySlamState::Attack:
			AttackStart();
			break;
		case BodySlamState::Death:
			DeathStart();
			break;
		default:
			MsgBoxAssert("존재하지 않는 상태값을 끝내려고 했습니다.");
			break;
		}

		// State Start
		switch (_State)
		{
		case BodySlamState::Ready:
			ReadyEnd();
			break;
		case BodySlamState::Attack:
			AttackStart();
			break;
		case BodySlamState::Death:
			DeathStart();
			break;
		default:
			MsgBoxAssert("존재하지 않는 상태값을 시작하려고 했습니다.");
			break;
		}
	}

	State = _State;
}

void Lucid_BodySlam::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BodySlamState::Ready:
		return ReadyUpdate(_Delta);
	case BodySlamState::Attack:
		return AttackUpdate(_Delta);
	case BodySlamState::Death:
		return DeathUpdate(_Delta);
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

void Lucid_BodySlam::ReadyStart()
{

}

void Lucid_BodySlam::AttackStart()
{

}

void Lucid_BodySlam::DeathStart()
{

}

void Lucid_BodySlam::ReadyEnd()
{

}

void Lucid_BodySlam::AttackEnd()
{

}

void Lucid_BodySlam::DeathEnd()
{

}

void Lucid_BodySlam::ReadyUpdate(float _Delta)
{

}

void Lucid_BodySlam::AttackUpdate(float _Delta)
{
	
}

void Lucid_BodySlam::DeathUpdate(float _Delta)
{

}