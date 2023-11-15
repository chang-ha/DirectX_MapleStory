#include "PreCompile.h"
#include "ContentNpc.h"
#include "ContentMouse.h"

ContentNpc::ContentNpc()
{

}

ContentNpc::~ContentNpc()
{

}

void ContentNpc::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void ContentNpc::Start()
{
	if (nullptr == NpcRenderer)
	{
		NpcRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAYBELOW);
		NpcRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::playbelow});
		NpcRenderer->SetPivotType(PivotType::Bottom);
		NpcRenderer->AutoSpriteSizeOn();
	}

	if (nullptr == NpcCollision)
	{
		NpcCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Npc);
	}

	NpcEvent.Enter = std::bind(&ContentNpc::CollisionEnter, this, std::placeholders::_1, std::placeholders::_2);
	NpcEvent.Stay = std::bind(&ContentNpc::CollisionStay, this, std::placeholders::_1, std::placeholders::_2);
	NpcEvent.Exit = std::bind(&ContentNpc::CollisionExit, this, std::placeholders::_1, std::placeholders::_2);
	GameEngineInput::AddInputObject(this);
}

void ContentNpc::Update(float _Delta)
{
	NpcCollision->CollisionEvent(CollisionOrder::Mouse, NpcEvent);
}

void ContentNpc::Release()
{
	if (nullptr != NpcRenderer)
	{
		NpcRenderer->Death();
		NpcRenderer = nullptr;
	}

	if (nullptr != NpcCollision)
	{
		NpcCollision->Death();
		NpcCollision = nullptr;
	}
}

void ContentNpc::Init(std::string_view _NpcName, ActorDir _Dir)
{
	if (nullptr == GameEngineSprite::Find(_NpcName))
	{
		GameEnginePath Path;
		Path.SetCurrentPath();
		Path.MoveParentToExistsChild("ContentResources");
		Path.MoveChild("ContentResources\\Textures\\Npc\\" + std::string(_NpcName));
		GameEngineTexture::Load(Path.GetStringPath());
		GameEngineSprite::CreateSingle(std::string(_NpcName));
	}

	NpcRenderer->SetSprite(std::string(_NpcName));
	switch (_Dir)
	{
	case ActorDir::Right:
		NpcRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		NpcRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	std::shared_ptr<GameEngineSprite> _Sprite = GameEngineSprite::Find(_NpcName);
	float4 TextureScale = _Sprite->GetSpriteData(0).Texture->GetScale();
	NpcCollision->Transform.SetLocalScale(TextureScale);
	NpcCollision->Transform.SetLocalPosition({0, TextureScale.hY()});
}

void ContentNpc::CollisionEnter(GameEngineCollision* _this, GameEngineCollision* _Other)
{
	ContentMouse::MainMouse->ButtonAniMouse();
}

void ContentNpc::CollisionStay(GameEngineCollision* _this, GameEngineCollision* _Other)
{
	if (true == GameEngineInput::IsDown(VK_LBUTTON, this))
	{
		int a = 0;
	}
}

void ContentNpc::CollisionExit(GameEngineCollision* _this, GameEngineCollision* _Other)
{
	ContentMouse::MainMouse->NormalMouse();
}