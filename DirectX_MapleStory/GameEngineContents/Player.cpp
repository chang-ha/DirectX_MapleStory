// PreCompile은 항상 최상단에 두자...
// #include 순서로 오류 발생 가능 << 잡기 정말 힘들다

#include "PreCompile.h"

#include <GameEngineCore\GameEngineCamera.h>

#include "Player.h"
#include "ContentLevel.h"
#include "ContentMap.h"
#include "SkillManager.h"
#include "PlayerUIManager.h"

#define MIN_CAMERA_MOVE 15.0f

Player* Player::MainPlayer = nullptr;
int Player::PlayerHP = PLAYER_MAX_HP;
int Player::PlayerMP = PLAYER_MAX_MP;

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::LevelStart(GameEngineLevel* _PrevLevel)
{
	HP = PlayerHP;
	MP = PlayerMP;
	ContentActor::LevelStart(_PrevLevel);
	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
	MainPlayer = this;
}

void Player::LevelEnd(GameEngineLevel* _NextLevel)
{
	PlayerHP = HP;
	PlayerMP = MP;
	ContentActor::LevelEnd(_NextLevel);
	Death();
}

void Player::Start()
{
	ContentActor::Start();
	GameEngineInput::AddInputObject(this);
	if (nullptr == MainSpriteRenderer)
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAY);
		MainSpriteRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::play});
	}

	// Create Sprite 
	if (nullptr == GameEngineSprite::Find("Idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Character");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& ChildDir = Directorys[i];
			GameEngineSprite::CreateFolder(ChildDir.GetStringPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("PlayerNameTag.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\Character\\PlayerNameTag.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	// Create Animation
	{
		MainSpriteRenderer->CreateAnimation("Idle", "Idle", IDLE_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Alert", "Alert", IDLE_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Walk", "Walk", WALK_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("HowlingGale", "Shoot", SHOOT1_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("SongOfHeaven", "Shoot", 0.1f, 1, 1);
		MainSpriteRenderer->CreateAnimation("Ladder", "Ladder", ROPE_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Down", "Down");
		MainSpriteRenderer->CreateAnimation("Jump", "Jump");
		MainSpriteRenderer->CreateAnimation("WindWalk", "WindWalk");
		MainSpriteRenderer->CreateAnimation("FairySpiral", "FairySpiral");
		MainSpriteRenderer->CreateAnimation("VortexSphere", "VortexSphere", 0.2f);
		MainSpriteRenderer->CreateAnimation("MercilessWinds", "MercilessWinds", 0.4f);
		MainSpriteRenderer->CreateAnimation("Monsoon", "Monsoon", 0.05f);
		
		std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("Idle");
		PlayerScale = Sprite->GetSpriteData(0).GetScale();
	}
	MainSpriteRenderer->AutoSpriteSizeOn();
	State = PlayerState::Idle;
	Dir = ActorDir::Right;
	MainSpriteRenderer->LeftFlip();
	IdleStart();

	// Animation Speed Setting
	std::shared_ptr<GameEngineFrameAnimation> _Animation = MainSpriteRenderer->FindAnimation("FairySpiral");
	_Animation->Inter[0] = 0.05f;
	_Animation->Inter[1] = 0.05f;

	_Animation = MainSpriteRenderer->FindAnimation("HowlingGale");
	_Animation->Inter[0] = 0.6f;

	_Animation = MainSpriteRenderer->FindAnimation("VortexSphere");
	_Animation->Inter[2] = 0.2f;

	_Animation = MainSpriteRenderer->FindAnimation("MercilessWinds");
	_Animation->Inter[0] = 0.05f;
	_Animation->Inter[2] = 0.2f;

	_Animation = MainSpriteRenderer->FindAnimation("Monsoon");
	_Animation->Inter[0] = 0.3f;
	_Animation->Inter[2] = 1.0f;

	if (nullptr == HitCollision)
	{
		HitCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Player);
		// HitCollision->Transform.SetLocalScale({ 32, 70 });
		// HitCollision->Transform.SetLocalPosition({ 0, 35 });
	}


	if (nullptr == NameBGRenderer)
	{
		NameBGRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAY);
		NameBGRenderer->Transform.SetLocalPosition({ -6, -12, RenderDepth::play });
		NameBGRenderer->SetSprite("PlayerNameTag.png");
	}

	if (nullptr == NameRenderer)
	{
		NameRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAY);
		NameRenderer->Transform.SetLocalPosition({ 0, -5.5f, RenderDepth::play });
		NameRenderer->SetText("돋움", "윈드브레이커", 11.0f, {1.0f, 1.0f, 0.6f}, FW1_CENTER);
	}

	if (nullptr == SkillManagerActor)
	{
		SkillManagerActor = GetLevel()->CreateActor<SkillManager>(UpdateOrder::Skill);
	}

	if (nullptr == UIManager)
	{
		UIManager = GetLevel()->CreateActor<PlayerUIManager>(UpdateOrder::UI);
	}
}

void Player::Update(float _Delta)
{
	ContentActor::Update(_Delta);
	ChasingCamera(_Delta);
	BlockOutMap();

	if (true == GameEngineInput::IsDown('Q', this))
	{
		HP = PLAYER_MAX_HP;
		MP = PLAYER_MAX_MP;
	}

	if (0 == HP && true == HitCollision->IsUpdate())
	{
		HitCollision->Off();
	}
	else if (0 != HP && false == HitCollision->IsUpdate() && false == Invincibility)
	{
		HitCollision->On();
	}



	DirCheck();
	LadderCheck();
	StateUpdate(_Delta);

	if ((PlayerState::Down & State || PlayerState::Alert & State || PlayerState::Idle & State || PlayerState::Walk &  State) && false == IsGround)
	{
		ChangeState(PlayerState::Jump);
	}

	//if (true == IsGround && (PlayerState::Idle == State || PlayerState::Alert == State || PlayerState::Down == State))
	//{
	//	MoveVectorForceReset();
	//	GravityReset();
	//}
	 
	if (true == IsGround /*&& 0.0f >= MoveVectorForce.Y*/ && (PlayerState::Jump != State && PlayerState::WindWalk != State && PlayerState::Walk != State))
	{
		MoveVectorForceReset();
		GravityReset();
	}
}

void Player::Release()
{
	if (nullptr != MainSpriteRenderer)
	{
		MainSpriteRenderer->Death();
		MainSpriteRenderer = nullptr;
	}

	if (nullptr != HitCollision)
	{
		HitCollision->Death();
		HitCollision = nullptr;
	}

	if (nullptr != NameRenderer)
	{
		NameRenderer->Death();
		NameRenderer = nullptr;
	}

	if (nullptr != NameBGRenderer)
	{
		NameBGRenderer->Death();
		NameBGRenderer = nullptr;
	}

	if (nullptr != SkillManagerActor)
	{
		SkillManagerActor->Death();
		SkillManagerActor = nullptr;
	}

	if (nullptr != UIManager)
	{
		UIManager->Death();
		UIManager = nullptr;
	}
}

void Player::DirCheck()
{
	if (false == IsDirCheck)
	{
		return;
	}

	ActorDir CheckDir = ActorDir::Null;
	// bool ChangeDir = false;

	if (true == GameEngineInput::IsPress(VK_LEFT, this))
	{
		CheckDir = ActorDir::Left;
		MainSpriteRenderer->RightFlip();
	} 
	else if (true == GameEngineInput::IsPress(VK_RIGHT, this))
	{
		CheckDir = ActorDir::Right;
		MainSpriteRenderer->LeftFlip();
	}

	if (ActorDir::Null != CheckDir)
	{
		Dir = CheckDir;
		// ChangeDir = true;
	}

	//if (PlayerDir::Null != CheckDir && true == ChangeDir)
	//{
	//	ChangeAnimationState(CurState);
	//}
}

void Player::ChasingCamera(float _Delta)
{
	if (true == GetLevel()->GetMainCamera()->IsFreeCamera())
	{
		return;
	}

	float4 StartPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 EndPos = Transform.GetWorldPosition();
	float4 MovePos = float4::LerpClamp(StartPos, EndPos, CameraSpeed * _Delta);

	float4 Distance = EndPos - MovePos;

	if ((MIN_CAMERA_MOVE > abs(Distance.X)))
	{
		MovePos.X = StartPos.X;
	}
	
	if((MIN_CAMERA_MOVE > abs(Distance.Y)))
	{
		MovePos.Y = StartPos.Y;
	}

	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(MovePos);
	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	// Right Left
	if (GlobalValue::WinScale.hX() >= CameraPos.X)
	{
		CameraPos.X = GlobalValue::WinScale.hX();
	}
	else if (CurMapScale.X - GlobalValue::WinScale.hX() <= CameraPos.X)
	{
		CameraPos.X = CurMapScale.X - GlobalValue::WinScale.hX();
	}

	// Up Down
	if (GlobalValue::WinScale.hY() >= -CameraPos.Y)
	{
		CameraPos.Y = -GlobalValue::WinScale.hY();
	}
	else if (CurMapScale.Y - GlobalValue::WinScale.hY() <= -CameraPos.Y)
	{
		CameraPos.Y = -(CurMapScale.Y - GlobalValue::WinScale.hY());
	}

	CameraPos.Z = 0.0f;
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(CameraPos);
}

void Player::BlockOutMap()
{
	float4 CurPos = Transform.GetWorldPosition();
	if (0 > CurPos.X - PlayerScale.hX())
	{
		Transform.SetLocalPosition(float4{ PlayerScale.hX(), CurPos.Y });
		MoveVectorForceXReset();
	}
	else if (CurMapScale.X <= CurPos.X + PlayerScale.hX())
	{
		Transform.SetLocalPosition(float4{ CurMapScale.X - PlayerScale.hX(), CurPos.Y });
		MoveVectorForceXReset();
	}

	// Need Test More
	CurPos.Y *= -1.0f;
	if (0 > CurPos.Y - PlayerScale.hY())
	{
		Transform.SetLocalPosition(float4{ CurPos.X, -PlayerScale.hY() });
		MoveVectorForceYReset();
	}
	else if (CurMapScale.Y <= CurPos.Y + PlayerScale.hY())
	{
		Transform.SetLocalPosition(float4{ CurPos.X, - CurMapScale.Y});
		MoveVectorForceYReset();
	}
}

void Player::LadderCheck()
{
	//if (PlayerState::Alert != State && PlayerState::Down != State && PlayerState::Idle != State && PlayerState::Jump != State && PlayerState::Walk != State)
	//{
	//	return;
	//}

	float YPivot = 0.0f;
	if (GameEngineInput::IsPress(VK_UP, this))
	{
		YPivot = LADDER_Y_PIVOT;
	}
	else if(GameEngineInput::IsPress(VK_DOWN, this))
	{
		YPivot = -LADDER_Y_PIVOT;
	}

	IsLadder = false;
	for (float i = -2.0f; i < 4.0f; i += 1.0f)
	{
		GameEngineColor CheckColor = CheckGroundColor(float4(i, YPivot));
		if (LADDER_COLOR == CheckColor)
		{
			IsLadder = true;
			LadderPivot = i;
			return;
		}
	}
}

bool Player::CheckGround(float4 PlusCheckPos /*= float4::ZERO*/)
{
	if (false == IsGroundCheck)
	{
		return false;
	}

	float CurYPos = Transform.GetWorldPosition().Y;
	if (0.0f != SkipGround && SkipGround <= CurYPos)
	{
		return false;
	}
	else if (0.0f != SkipGround && SkipGround > CurYPos)
	{
		SkipGround = 0.0f;
	}

	std::set<float>::iterator StartIter = NotGround.begin();
	std::set<float>::iterator EndIter = NotGround.end();

	for (; StartIter != EndIter ;)
	{
		float CheckPos = *StartIter;
		if (0.0f != CheckPos && (CheckPos + 1.0f >= CurYPos && CheckPos - 2.0f <= CurYPos))
		{
			return false;
		}
		++StartIter;
	}

	return ContentActor::CheckGround(PlusCheckPos);
}

void Player::ChangeToIdle()
{
	//GravityReset();
	//MoveVectorForceReset();
	if (true == IsGround)
	{
		GroundJump = false;
		DoubleJump = false;
	}

	if (0.0f < AlertTime)
	{
		ChangeState(PlayerState::Alert);
	}
	else
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::ChangeState(PlayerState _State)
{
	if (_State != State)
	{
		// State End
		switch (State)
		{
		case PlayerState::Idle:
			IdleEnd();
			break;
		case PlayerState::Alert:
			AlertEnd();
			break;
		case PlayerState::Walk:
			WalkEnd();
			break;
		case PlayerState::Jump:
			JumpEnd();
			break;
		case PlayerState::Down:
			DownEnd();
			break;
		case PlayerState::Ladder:
			LadderEnd();
			break;
		case PlayerState::SongOfHeaven:
			SongOfHeavenEnd();
			break;
		case PlayerState::FairySpiral:
			FairySpiralEnd();
			break;
		case PlayerState::WindWalk:
			WindWalkEnd();
			break;
		case PlayerState::HowlingGale:
			HowlingGaleEnd();
			break;
		case PlayerState::VortexSphere:
			VortexSphereEnd();
			break;
		case PlayerState::MercilessWinds:
			MercilessWindsEnd();
			break;
		case PlayerState::Monsoon:
			MonsoonEnd();
			break;
		case PlayerState::Null:
		default:
			MsgBoxAssert("존재하지 않는 상태값을 끝내려고 했습니다.");
			break;
		}

		// State Start
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Alert:
			AlertStart();
			break;
		case PlayerState::Walk:
			WalkStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::Down:
			DownStart();
			break;
		case PlayerState::Ladder:
			LadderStart();
			break;
		case PlayerState::SongOfHeaven:
			SongOfHeavenStart();
			break;
		case PlayerState::FairySpiral:
			FairySpiralStart();
			break;
		case PlayerState::WindWalk:
			WindWalkStart();
			break;
		case PlayerState::HowlingGale:
			HowlingGaleStart();
			break;
		case PlayerState::VortexSphere:
			VortexSphereStart();
			break;
		case PlayerState::MercilessWinds:
			MercilessWindsStart();
			break;
		case PlayerState::Monsoon:
			MonsoonStart();
			break;
		case PlayerState::Null:
		default:
			MsgBoxAssert("존재하지 않는 상태값으로 변경하려고 했습니다.");
			break;
		}
	}

	State = _State;
}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Alert:
		return AlertUpdate(_Delta);
	case PlayerState::Walk:
		return WalkUpdate(_Delta);
	case PlayerState::Jump:
		return JumpUpdate(_Delta);
	case PlayerState::Down:
		return DownUpdate(_Delta);
	case PlayerState::Ladder:
		return LadderUpdate(_Delta);
	case PlayerState::SongOfHeaven:
		return SongOfHeavenUpdate(_Delta);
	case PlayerState::FairySpiral:
		return FairySpiralUpdate(_Delta);
	case PlayerState::WindWalk:
		return WindWalkUpdate(_Delta);
	case PlayerState::HowlingGale:
		return HowlingGaleUpdate(_Delta);
	case PlayerState::VortexSphere:
		return VortexSphereUpdate(_Delta);
	case PlayerState::MercilessWinds:
		return MercilessWindsUpdate(_Delta);
	case PlayerState::Monsoon:
		return MonsoonUpdate(_Delta);
	case PlayerState::Null:
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}
