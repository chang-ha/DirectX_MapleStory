#include "PreCompile.h"
#include "CharacterSelect.h"
#include "ContentMap.h"
#include "RenderActor.h"
#include "FadeObject.h"
#include "UIRenderActor.h"
#include "ContentButton.h"

CharacterSelect::CharacterSelect()
{

}

CharacterSelect::~CharacterSelect()
{

}

void CharacterSelect::LevelStart(GameEngineLevel* _PrevLevel)
{
	AllCharacter.reserve(12);

	ContentLevel::LevelStart(_PrevLevel);
	FadeInObject->SetFadeSpeed(2.0f);

	if (nullptr == GameEngineSprite::Find("CharacterSelect_BG.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Login\\CharacterSelect");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& Childs = Files[i];
			GameEngineTexture::Load(Childs.GetStringPath());
			GameEngineSprite::CreateSingle(Childs.GetFileName());
		}
	}

	if (nullptr == GameEngineSprite::Find("ServerName.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\ServerName.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("ServerCharacterInfo_BG.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\ServerCharacterInfo_BG.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("Character_Empty.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\Character_Empty.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("Character_FootHold"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\Character_FootHold");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("RenderCharacter_Idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\RenderCharacter");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("RenderCharacter_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	std::shared_ptr<RenderActor> _Actor = CreateActor<RenderActor>(UpdateOrder::RenderActor);
	_Actor->Init(RenderOrder::MAP, RenderDepth::map);
	_Actor->Renderer->SetSprite("CharacterSelect_BG.png");
	_Actor->Renderer->AutoSpriteSizeOff();
	_Actor->Renderer->SetImageScale(GlobalValue::WinScale);
	_Actor->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());

	_Actor = CreateActor<RenderActor>(UpdateOrder::RenderActor);
	_Actor->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor->Renderer->SetSprite("ServerName.png");
	_Actor->Transform.SetLocalPosition({ 1205, -50 });

	if (nullptr == CharacterInfo_BG)
	{
		CharacterInfo_BG = CreateActor<RenderActor>(UpdateOrder::RenderActor);
		CharacterInfo_BG->Init(RenderOrder::UI, RenderDepth::ui);
		CharacterInfo_BG->Renderer->SetSprite("ServerCharacterInfo_BG.png");
		CharacterInfo_BG->Transform.SetLocalPosition({ 1200, -475 });
		CharacterInfo_BG->Off();
	}

	_Actor = CreateActor<UIRenderActor>(UpdateOrder::UI);
	_Actor->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor->Renderer->SetSprite("CharacterSelect_Front.png");
	_Actor->Renderer->AutoSpriteSizeOff();
	_Actor->Renderer->SetImageScale(GlobalValue::WinScale);
	_Actor->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());

	GetMainCamera()->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());

	std::shared_ptr<ContentButton> _Button = CreateActor<ContentButton>(UpdateOrder::UI);
	_Button->Init("PrevButton");
	_Button->Transform.SetLocalPosition({ _Button->GetButtonScale().hX(), -730 });
	_Button->SetButtonClickEndEvent([&]()
		{
			FadeOutObject->SetFadeSpeed(2.0f);
			FadeOutObject->SetChangeLevel("2.ServerLevel");
			FadeOutObject->FadeStart();
		});

	{
		SelectCharacterFrame Frame;
		Frame.CharacterRenderer = CreateActor<RenderActor>(UpdateOrder::RenderActor);
		Frame.CharacterRenderer->Init(RenderOrder::UI, RenderDepth::ui);
		Frame.CharacterRenderer->Renderer->CreateAnimation("Idle", "RenderCharacter_Idle", 0.5f);
		Frame.CharacterRenderer->Renderer->CreateAnimation("Walk", "RenderCharacter_Walk", 0.15f);
		Frame.CharacterRenderer->Renderer->ChangeAnimation("Idle");
		Frame.CharacterRenderer->Transform.SetLocalPosition({ 175, -311 });
		Frame.CharacterRenderer->Renderer->LeftFlip();


		Frame.CharacterFootHold = CreateActor<RenderActor>(UpdateOrder::RenderActor);
		Frame.CharacterFootHold->Init(RenderOrder::UI, RenderDepth::ui);
		Frame.CharacterFootHold->Renderer->CreateAnimation("Character_FootHold", "Character_FootHold", 0.13f);
		Frame.CharacterFootHold->Renderer->ChangeAnimation("Character_FootHold");
		Frame.CharacterFootHold->Transform.SetLocalPosition({ 175, -350 });

		AllCharacter.push_back(Frame);

		SelectCollision = Frame.CharacterRenderer->CreateComponent<GameEngineCollision>(CollisionOrder::UI);
		SelectCollision->Transform.SetLocalScale({65, 78});
	}

	for (int i = 0; i < 6; i++)
	{
		if (0 == i)
		{
			continue;
		}

		SelectCharacterFrame Frame;
		Frame.CharacterRenderer = CreateActor<RenderActor>(UpdateOrder::RenderActor);
		Frame.CharacterRenderer->Init(RenderOrder::UI, RenderDepth::ui);
		Frame.CharacterRenderer->Renderer->SetSprite("Character_Empty.png");
		Frame.CharacterRenderer->Transform.SetLocalPosition({ 175 + 165 * static_cast<float>(i), -315 });
		if (3 <= i)
		{
			Frame.CharacterRenderer->Renderer->LeftFlip();
		}

		Frame.CharacterFootHold = CreateActor<RenderActor>(UpdateOrder::RenderActor);
		Frame.CharacterFootHold->Init(RenderOrder::UI, RenderDepth::ui);
		Frame.CharacterFootHold->Renderer->CreateAnimation("Character_FootHold", "Character_FootHold", 0.13f);
		Frame.CharacterFootHold->Renderer->ChangeAnimation("Character_FootHold");
		Frame.CharacterFootHold->Transform.SetLocalPosition({ 175 + 165 * static_cast<float>(i), -350 });

		AllCharacter.push_back(Frame);
	}

	for (int i = 0; i < 6; i++)
	{
		SelectCharacterFrame Frame;
		Frame.CharacterRenderer = CreateActor<RenderActor>(UpdateOrder::RenderActor);
		Frame.CharacterRenderer->Init(RenderOrder::UI, RenderDepth::ui);
		Frame.CharacterRenderer->Renderer->SetSprite("Character_Empty.png");
		Frame.CharacterRenderer->Transform.SetLocalPosition({ 175 + 165 * static_cast<float>(i), -550 });
		if (3 <= i)
		{
			Frame.CharacterRenderer->Renderer->LeftFlip();
		}

		Frame.CharacterFootHold = CreateActor<RenderActor>(UpdateOrder::RenderActor);
		Frame.CharacterFootHold->Init(RenderOrder::UI, RenderDepth::ui);
		Frame.CharacterFootHold->Renderer->CreateAnimation("Character_FootHold", "Character_FootHold", 0.13f);
		Frame.CharacterFootHold->Renderer->ChangeAnimation("Character_FootHold");
		Frame.CharacterFootHold->Transform.SetLocalPosition({ 175 + 165 * static_cast<float>(i), -585 });

		AllCharacter.push_back(Frame);
	}
}

void CharacterSelect::LevelEnd(GameEngineLevel* _NextLevel)
{
	AllCharacter.clear();
	ContentLevel::LevelEnd(_NextLevel);

	if (nullptr != CharacterInfo_BG)
	{
		CharacterInfo_BG->Death();
		CharacterInfo_BG = nullptr;
	}
}

void CharacterSelect::Start()
{
	ContentLevel::Start();
	GameEngineInput::AddInputObject(this);
}

void CharacterSelect::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	if (true == IsCharacterSelect)
	{
		return;
	}

	if (true == SelectCollision->Collision(CollisionOrder::Mouse) && GameEngineInput::IsDown(VK_LBUTTON, this))
	{
		SelectCharacter();
	}

	if (GameEngineInput::IsPress(VK_LEFT, this) || GameEngineInput::IsPress(VK_RIGHT, this))
	{
		SelectCharacter();
	}
}

void CharacterSelect::SelectCharacter()
{
	IsCharacterSelect = true;
	AllCharacter[0].CharacterRenderer->Renderer->ChangeAnimation("Walk");
	CharacterInfo_BG->On();
}
