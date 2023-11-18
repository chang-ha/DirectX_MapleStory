﻿#include "PreCompile.h"
#include "ContentNpc.h"
#include "ContentMouse.h"
#include "ContentButton.h"
#include "ContentLevel.h"
#include "Player.h"

void OneButtonNpcMentFrame::StructStart(ContentNpc* _Parent, std::string_view _NpcName, std::string_view _CancelButtonName)
{
	if (nullptr == GameEngineSprite::Find("NpcMent_BG.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\NpcMent_BG.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());

	MentBG = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MentBG->Transform.SetLocalPosition({0, 0, RenderDepth::ui});
	MentBG->SetSprite("NpcMent_BG.png");

	MentNpc = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MentNpc->Transform.SetLocalPosition({ -180, 15, RenderDepth::ui });
	MentNpc->SetSprite(_Parent->GetNpcName());

	NpcName = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	NpcName->Transform.SetLocalPosition({ -180, -27, RenderDepth::ui });
	NpcName->SetText( "돋움", _NpcName.data(), 13.0f, float4::WHITE, FW1_CENTER);

	MentText = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MentText->SetText("돋움", "", 11.0f, float4::ZERO);
	MentText->Transform.SetLocalPosition({-90, 20});

	CancelButton = ContentLevel::CurContentLevel->CreateActor<ContentButton>(UpdateOrder::UI);
	CancelButton->SetParent(this, static_cast<int>(UpdateOrder::UI));
	CancelButton->Init(_CancelButtonName);
	CancelButton->Transform.SetLocalPosition({210, -79});

	CancelButton->SetButtonClickEndEvent([&]()
		{
			MentOff();
			Player::MainPlayer->InputObjectOn();
		});

	GameEngineInput::AddInputObject(this);
}

void OneButtonNpcMentFrame::MentOff()
{
	Off();
	MentIndex = 0;
	MentEnd = false;
	MentText->SetText("돋움", "", 11.0f, float4::ZERO);
}

void OneButtonNpcMentFrame::Update(float _Delta)
{
	MentUpdate(_Delta);
	SkipUpdate(_Delta);
}

void OneButtonNpcMentFrame::Release()
{
	if (nullptr != MentBG)
	{
		MentBG->Death();
		MentBG = nullptr;
	}

	if (nullptr != MentNpc)
	{
		MentNpc->Death();
		MentNpc = nullptr;
	}

	if (nullptr != NpcName)
	{
		NpcName->Death();
		NpcName = nullptr;
	}

	if (nullptr != MentText)
	{
		MentText->Death();
		MentText = nullptr;
	}

	if (nullptr != CancelButton)
	{
		CancelButton->Death();
		CancelButton = nullptr;
	}
}

void OneButtonNpcMentFrame::MentUpdate(float _Delta)
{
	if (true == MentEnd)
	{
		return;
	}

	MentSpeed -= _Delta;
	if (0.0f >= MentSpeed)
	{
		MentSpeed = MENT_SPEED;
		++MentIndex;
		std::wstring OutString = Ment.substr(0, MentIndex);
		std::string Result = GameEngineString::UnicodeToAnsi(OutString);
		MentText->SetText("돋움", Result, 11.0f, float4::ZERO);

		if (MentIndex == MentMaxIndex)
		{
			MentEnd = true;
		}
	}
}

void OneButtonNpcMentFrame::SkipUpdate(float _Delta)
{
	if (L"" == Ment)
	{
		return;
	}

	if (true == GameEngineInput::IsDown(VK_ESCAPE, this))
	{
		MentIndex = MentMaxIndex - 1;
	}
}


void TwoButtonNpcMentFrame::StructStart(class ContentNpc* _Parent, std::string_view _NpcName, std::string_view _CancelButtonName, std::string_view _OkButtonName, std::function<void()> _OkButtonEndFunction /*= nullptr*/)
{
	OneButtonNpcMentFrame::StructStart(_Parent, _NpcName, _CancelButtonName);

	OkButton = ContentLevel::CurContentLevel->CreateActor<ContentButton>(UpdateOrder::UI);
	OkButton->SetParent(this, static_cast<int>(UpdateOrder::UI));
	OkButton->Init(_OkButtonName);
	OkButton->Transform.SetLocalPosition({ 140, -79 });

	if (nullptr == _OkButtonEndFunction)
	{
		OkButton->SetButtonClickEndEvent(CancelButton->GetButtonClickEndEvent());
	}
	else
	{
		OkButton->SetButtonClickEvent(_OkButtonEndFunction);
	}
}

void TwoButtonNpcMentFrame::Release()
{
	OneButtonNpcMentFrame::Release();

	if (nullptr != OkButton)
	{
		OkButton->Death();
		OkButton = nullptr;
	}
}

ContentNpc::ContentNpc()
{

}

ContentNpc::~ContentNpc()
{

}

void ContentNpc::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();

	if (nullptr != Ment)
	{
		Ment->Death();
		Ment = nullptr;
	}
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

	if (nullptr == NpcNameBGRenderer)
	{
		NpcNameBGRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAYBELOW);
		NpcNameBGRenderer->Transform.SetLocalPosition({ 0, -1, RenderDepth::playbelow });
		NpcNameBGRenderer->SetPivotType(PivotType::Top);
		NpcNameBGRenderer->AutoSpriteSizeOff();
	}

	if (nullptr == NpcNameRenderer)
	{
		NpcNameRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAYBELOW);
		NpcNameRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::playbelow });
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

	if (nullptr  != NpcNameRenderer)
	{
		NpcNameRenderer->Death();
		NpcNameRenderer = nullptr;
	}

	if (nullptr != NpcCollision)
	{
		NpcCollision->Death();
		NpcCollision = nullptr;
	}
}

void ContentNpc::Init(std::string_view _NpcName, std::string_view _KoreanName, ActorDir _Dir, float _AniSpeed)
{
	NpcName = _NpcName;
	KoreanName = _KoreanName;
	if (nullptr == GameEngineSprite::Find(NpcName))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Npc\\" + NpcName);
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}
	NpcRenderer->CreateAnimation("Idle", NpcName, _AniSpeed);
	NpcRenderer->ChangeAnimation("Idle");

	if (nullptr == GameEngineSprite::Find("Npc_NameTag.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\Npc_NameTag.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

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

	NpcNameBGRenderer->SetSprite("Npc_NameTag.png");
	NpcNameBGRenderer->SetSampler("EngineBaseWRAPSampler");

	size_t TextSize = KoreanName.size();

	NpcNameBGRenderer->SetImageScale({ 7.5f * TextSize, 16, 1 });
	NpcNameBGRenderer->RenderBaseInfoValue.VertexUVMul.X = 7.5f * TextSize;

	NpcNameRenderer->SetText("돋움", KoreanName, 13.0f, {1.0f, 1.0f, 0.0f}, FW1_CENTER);

	std::shared_ptr<GameEngineSprite> _Sprite = GameEngineSprite::Find(NpcName);
	float4 TextureScale = _Sprite->GetSpriteData(0).Texture->GetScale();
	NpcCollision->Transform.SetLocalScale(TextureScale);
	NpcCollision->Transform.SetLocalPosition({0, TextureScale.hY()});
}

void ContentNpc::CreateOneButtonMent(std::string_view _CancelButtonName)
{
	Ment = ContentLevel::CurContentLevel->CreateActor<OneButtonNpcMentFrame>(UpdateOrder::UI);
	Ment->StructStart(this, KoreanName, _CancelButtonName);
	Ment->Off();
}

void ContentNpc::CreateTwoButtonMent(std::string_view _CancelButtonName, std::string_view _OkButtonName, std::function<void()> _OkButtonEndFunction /*= nullptr*/)
{
	std::shared_ptr<TwoButtonNpcMentFrame> Frame = ContentLevel::CurContentLevel->CreateActor<TwoButtonNpcMentFrame>(UpdateOrder::UI);
	Frame->StructStart(this, KoreanName, _CancelButtonName, _OkButtonName, _OkButtonEndFunction);
	Ment = Frame;
	Ment->Off();
}

void ContentNpc::CollisionEnter(GameEngineCollision* _this, GameEngineCollision* _Other)
{
	ContentMouse::MainMouse->ButtonAniMouse();
}

void ContentNpc::CollisionStay(GameEngineCollision* _this, GameEngineCollision* _Other)
{
	if (true == GameEngineInput::IsFree(VK_LBUTTON, this))
	{
		ContentMouse::MainMouse->ButtonAniMouse();
	}

	if (L"" == Ment->Ment)
	{
		return;
	}

	if (true == GameEngineInput::IsDown(VK_LBUTTON, this))
	{
		Ment->On();
		Player::MainPlayer->InputObjectOff();
	}
}

void ContentNpc::CollisionExit(GameEngineCollision* _this, GameEngineCollision* _Other)
{
	ContentMouse::MainMouse->NormalMouse();
}