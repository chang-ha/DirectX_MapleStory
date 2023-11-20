#include "PreCompile.h"
#include "CharacterSelect.h"
#include "ContentMap.h"
#include "RenderActor.h"
#include "FadeObject.h"
#include "UIRenderActor.h"
#include "ContentButton.h"
#include "ButtonWarningMent.h"
#include "ReleaseFunction.h"

void CharacterInfoFrame::FrameOff()
{
	CharacterInfo_BG->Off();
	GameStartButton->Off();
	CharacterName->Off();
	JobName->Off();
	STR->Off();
	DEX->Off();
	INT->Off();
	LUK->Off();
}

void CharacterInfoFrame::FrameOn()
{
	CharacterInfo_BG->On();
	GameStartButton->On();
	CharacterName->On();
	JobName->On();
	STR->On();
	DEX->On();
	INT->On();
	LUK->On();
}

CharacterSelect::CharacterSelect()
{

}

CharacterSelect::~CharacterSelect()
{

}

void CharacterSelect::LevelStart(GameEngineLevel* _PrevLevel)
{
	PrevLevel = "02.ServerLevel";
	NextLevel = "04.Lachlen";

	AllCharacter.reserve(12);

	ContentLevel::LevelStart(_PrevLevel);
	FadeInObject->SetFadeSpeed(2.0f);

	if (nullptr == GameEngineSprite::Find("CharacterSelect_BG.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\Login\\CharacterSelect\\CharacterSelect_BG.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("CharacterSelect_Front.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\Login\\CharacterSelect\\CharacterSelect_Front.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
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

	if (nullptr == GameEngineSprite::Find("Character_Job.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\Character_Job.png");
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

	if (nullptr == GameEngineSprite::Find("Render_Idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Character\\Idle");
		GameEngineSprite::CreateFolder("Render_Idle", Dir.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("Render_Walk"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Character\\Walk");
		GameEngineSprite::CreateFolder("Render_Walk", Dir.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("CharSelectEffect0"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\CharSelectEffect0");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("CharSelectEffect1"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\CharSelectEffect1");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("Button_ChangeCP.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\Button_ChangeCP.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("Button_SecondPassword.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\Button_SecondPassword.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("Button_Otp.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\Button_Otp.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("PageNumber.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\PageNumber.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("NameTag.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\NameTag.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSound::FindSound("ServerSelect.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\BGM\\ServerSelect.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath());
	}

	if (nullptr == GameEngineSound::FindSound("CharSelect.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\BGM\\CharSelect.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath());
	}

	std::shared_ptr<UIRenderActor> _Actor = CreateActor<UIRenderActor>(UpdateOrder::UI);
	_Actor->Init(RenderOrder::MAP, RenderDepth::map);
	_Actor->Renderer->SetSprite("CharacterSelect_BG.png");
	_Actor->Renderer->AutoSpriteSizeOff();
	_Actor->Renderer->SetImageScale(GlobalValue::WinScale);
	_Actor->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());

	_Actor = CreateActor<UIRenderActor>(UpdateOrder::UI);
	_Actor->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor->Renderer->SetSprite("ServerName.png");
	_Actor->Transform.SetLocalPosition({ 1205, -50 });

	if (nullptr == InfoFrame.CharacterInfo_BG)
	{
		InfoFrame.CharacterInfo_BG = CreateActor<UIRenderActor>(UpdateOrder::UI);
		InfoFrame.CharacterInfo_BG->Init(RenderOrder::UI, RenderDepth::ui);
		InfoFrame.CharacterInfo_BG->Renderer->SetSprite("ServerCharacterInfo_BG.png");
		InfoFrame.CharacterInfo_BG->Transform.SetLocalPosition({ 1200, -475 });

		InfoFrame.GameStartButton = CreateActor<ContentButton>(UpdateOrder::UI);
		InfoFrame.GameStartButton->Init("GameStart");
		InfoFrame.GameStartButton->Transform.SetLocalPosition({ 1200, -555 });
		InfoFrame.GameStartButton->SetButtonClickEndEvent([&]()
			{
				FadeOutObject->SetFadeSpeed(1.0f);
				FadeOutObject->SetChangeLevel("04.Lachlen");
				FadeOutObject->FadeStart();
			});
		AllButton.push_back(InfoFrame.GameStartButton);

		InfoFrame.CharacterName = InfoFrame.CharacterInfo_BG->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		InfoFrame.CharacterName->SetText("메이플스토리", "윈드브레이커", 19.0f, float4::WHITE);
		InfoFrame.CharacterName->Transform.SetLocalPosition({ -45, 75.0f });

		InfoFrame.JobName = InfoFrame.CharacterInfo_BG->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		InfoFrame.JobName->SetText("메이플스토리", "윈드브레이커", 15.0f, float4::WHITE, FW1_RIGHT);
		InfoFrame.JobName->Transform.SetLocalPosition({ 65, 43.0f });

		InfoFrame.STR = InfoFrame.CharacterInfo_BG->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		InfoFrame.STR->SetText("메이플스토리", "4", 12.0f, float4::WHITE, FW1_RIGHT);
		InfoFrame.STR->Transform.SetLocalPosition({ -5, 17.0f });

		InfoFrame.DEX = InfoFrame.CharacterInfo_BG->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		InfoFrame.DEX->SetText("메이플스토리", "1300", 12.0f, float4::WHITE, FW1_RIGHT);
		InfoFrame.DEX->Transform.SetLocalPosition({ -5, -7.0f });

		InfoFrame.INT = InfoFrame.CharacterInfo_BG->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		InfoFrame.INT->SetText("메이플스토리", "4", 12.0f, float4::WHITE, FW1_RIGHT);
		InfoFrame.INT->Transform.SetLocalPosition({ 65, 17.0f });

		InfoFrame.LUK = InfoFrame.CharacterInfo_BG->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		InfoFrame.LUK->SetText("메이플스토리", "4", 12.0f, float4::WHITE, FW1_RIGHT);
		InfoFrame.LUK->Transform.SetLocalPosition({ 65, -7.0f });
	}
	InfoFrame.FrameOff();

	_Actor = CreateActor<UIRenderActor>(UpdateOrder::UI);
	_Actor->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor->Renderer->SetSprite("CharacterSelect_Front.png");
	_Actor->Renderer->AutoSpriteSizeOff();
	_Actor->Renderer->SetImageScale(GlobalValue::WinScale);
	_Actor->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());

	_Actor = CreateActor<UIRenderActor>(UpdateOrder::UI);
	_Actor->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor->Renderer->SetSprite("Button_SecondPassword.png");
	_Actor->Transform.SetLocalPosition({ 58, -50 });

	_Actor = CreateActor<UIRenderActor>(UpdateOrder::UI);
	_Actor->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor->Renderer->SetSprite("Button_Otp.png");
	_Actor->Transform.SetLocalPosition({ 58, -100 });

	_Actor = CreateActor<UIRenderActor>(UpdateOrder::UI);
	_Actor->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor->Renderer->SetSprite("Button_ChangeCP.png");
	_Actor->Transform.SetLocalPosition({ 58, -150 });

	_Actor = CreateActor<UIRenderActor>(UpdateOrder::UI);
	_Actor->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor->Renderer->SetSprite("PageNumber.png");
	_Actor->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 90, -645 });

	_Actor = CreateActor<UIRenderActor>(UpdateOrder::UI);
	_Actor->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor->Renderer->SetSprite("NameTag.png");
	_Actor->Transform.SetLocalPosition({ 180, -368 });

	_Actor = CreateActor<UIRenderActor>(UpdateOrder::UI);
	_Actor->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor->Renderer->SetText("메이플스토리", "윈드브레이커", 14.0f, float4::WHITE, FW1_CENTER);
	_Actor->Transform.SetLocalPosition({ 180, -362 });

	GetMainCamera()->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());

	std::shared_ptr<ContentButton> _Button = CreateActor<ContentButton>(UpdateOrder::UI);
	_Button->Init("PrevButton");
	_Button->Transform.SetLocalPosition({ _Button->GetButtonScale().hX(), -730 });
	_Button->SetButtonClickEndEvent([&]()
		{
			FadeOutObject->SetFadeSpeed(2.0f);
			FadeOutObject->SetChangeLevel("02.ServerLevel");
			FadeOutObject->FadeStart();
		});
	AllButton.push_back(_Button);

	_Button = CreateActor<ContentButton>(UpdateOrder::UI);
	_Button->Init("GoFirstLevel");
	_Button->Transform.SetLocalPosition({ _Button->GetButtonScale().hX(), -680 });
	_Button->SetButtonClickEndEvent([&]()
		{
			std::shared_ptr<ButtonWarningMent> _Ment = ButtonWarningMent::CreateTwoButtonMent();
			_Ment->Init("MentBG_Normal.png", "Ment_GoFirst.png");

			std::shared_ptr<ContentButton> _MentButton = _Ment->GetOkButton();
			_MentButton->SetButtonClickEndEvent([&]()
				{
					FadeOutObject->SetChangeLevel("01.TitleLevel");
					FadeOutObject->FadeStart();
				});
		});
	AllButton.push_back(_Button);

	_Button = CreateActor<ContentButton>(UpdateOrder::UI);
	_Button->Init("LeftButton");
	_Button->Transform.SetLocalPosition({ 400, -700 });
	AllButton.push_back(_Button);

	_Button = CreateActor<ContentButton>(UpdateOrder::UI);
	_Button->Init("CreateCharacter");
	_Button->Transform.SetLocalPosition({ 525, -700 });
	_Button->SetButtonClickEndEvent([&]()
		{
			std::shared_ptr<ButtonWarningMent> _Ment = ButtonWarningMent::CreateOneButtonMent();
			_Ment->Init("MentBG_Warning.png", "Ment_Normal.png");
		});
	AllButton.push_back(_Button);

	_Button = CreateActor<ContentButton>(UpdateOrder::UI);
	_Button->Init("DeleteCharacter");
	_Button->Transform.SetLocalPosition({ 675, -700 });
	_Button->SetButtonClickEndEvent([&]()
		{
			std::shared_ptr<ButtonWarningMent> _Ment = ButtonWarningMent::CreateOneButtonMent();
			_Ment->Init("MentBG_Warning.png", "Ment_DeleteFail.png");
		});
	AllButton.push_back(_Button);

	_Button = CreateActor<ContentButton>(UpdateOrder::UI);
	_Button->Init("RightButton");
	_Button->Transform.SetLocalPosition({ 800, -700 });
	AllButton.push_back(_Button);

	CharSelectEffect1 = CreateActor<UIRenderActor>(UpdateOrder::UI);
	CharSelectEffect1->Init(RenderOrder::UI, RenderDepth::ui);
	CharSelectEffect1->Renderer->CreateAnimation("Effect1", "CharSelectEffect1", 0.15f);
	CharSelectEffect1->Renderer->ChangeAnimation("Effect1");
	CharSelectEffect1->Transform.SetLocalPosition({ 175, -270 });
	CharSelectEffect1->Off();

	CharSelectEffect0 = CreateActor<UIRenderActor>(UpdateOrder::UI);
	CharSelectEffect0->Init(RenderOrder::UI, RenderDepth::ui);
	CharSelectEffect0->Renderer->CreateAnimation("Effect0", "CharSelectEffect0", 0.03f);
	CharSelectEffect0->Renderer->ChangeAnimation("Effect0");
	CharSelectEffect0->Transform.SetLocalPosition({ 170, -260 });
	CharSelectEffect0->Off();

	std::shared_ptr<GameEngineFrameAnimation> _Animation = CharSelectEffect0->Renderer->FindAnimation("Effect0");
	_Animation->Inter[20] = 0.15f;
	_Animation->Inter[21] = 0.15f;
	_Animation->Inter[22] = 0.15f;
	_Animation->Inter[23] = 0.15f;

	_Actor = CreateActor<UIRenderActor>(UpdateOrder::UI);
	_Actor->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor->Renderer->SetSprite("Character_Job.png");
	_Actor->Transform.SetLocalPosition({ 155, -275 });

	{
		SelectCharacterFrame Frame;
		Frame.CharacterRenderer = CreateActor<UIRenderActor>(UpdateOrder::UI);
		Frame.CharacterRenderer->Init(RenderOrder::UI, RenderDepth::ui);
		Frame.CharacterRenderer->Renderer->CreateAnimation("Idle", "Render_Idle", 0.5f);
		Frame.CharacterRenderer->Renderer->CreateAnimation("Walk", "Render_Walk", 0.15f);
		Frame.CharacterRenderer->Renderer->ChangeAnimation("Idle");
		Frame.CharacterRenderer->Transform.SetLocalPosition({ 175, -311 });
		Frame.CharacterRenderer->Renderer->LeftFlip();
		Frame.CharacterRenderer->Renderer->SetPivotValue({0.33f, 0.5f});


		Frame.CharacterFootHold = CreateActor<UIRenderActor>(UpdateOrder::UI);
		Frame.CharacterFootHold->Init(RenderOrder::UI, RenderDepth::ui);
		Frame.CharacterFootHold->Renderer->CreateAnimation("Character_FootHold", "Character_FootHold", 0.13f);
		Frame.CharacterFootHold->Renderer->ChangeAnimation("Character_FootHold");
		Frame.CharacterFootHold->Transform.SetLocalPosition({ 175, -350 });

		AllCharacter.push_back(Frame);

		SelectCollision = Frame.CharacterRenderer->CreateComponent<GameEngineCollision>(CollisionOrder::UI);
		SelectCollision->Transform.SetLocalScale({ 65, 78 });
	}

	for (int i = 0; i < 6; i++)
	{
		if (0 == i)
		{
			continue;
		}

		SelectCharacterFrame Frame;
		Frame.CharacterRenderer = CreateActor<UIRenderActor>(UpdateOrder::UI);
		Frame.CharacterRenderer->Init(RenderOrder::UI, RenderDepth::ui);
		Frame.CharacterRenderer->Renderer->SetSprite("Character_Empty.png");
		Frame.CharacterRenderer->Transform.SetLocalPosition({ 175 + 165 * static_cast<float>(i), -315 });
		if (3 <= i)
		{
			Frame.CharacterRenderer->Renderer->LeftFlip();
		}

		Frame.CharacterFootHold = CreateActor<UIRenderActor>(UpdateOrder::UI);
		Frame.CharacterFootHold->Init(RenderOrder::UI, RenderDepth::ui);
		Frame.CharacterFootHold->Renderer->CreateAnimation("Character_FootHold", "Character_FootHold", 0.13f);
		Frame.CharacterFootHold->Renderer->ChangeAnimation("Character_FootHold");
		Frame.CharacterFootHold->Transform.SetLocalPosition({ 175 + 165 * static_cast<float>(i), -350 });

		AllCharacter.push_back(Frame);
	}

	for (int i = 0; i < 6; i++)
	{
		SelectCharacterFrame Frame;
		Frame.CharacterRenderer = CreateActor<UIRenderActor>(UpdateOrder::UI);
		Frame.CharacterRenderer->Init(RenderOrder::UI, RenderDepth::ui);
		Frame.CharacterRenderer->Renderer->SetSprite("Character_Empty.png");
		Frame.CharacterRenderer->Transform.SetLocalPosition({ 175 + 165 * static_cast<float>(i), -550 });
		if (3 <= i)
		{
			Frame.CharacterRenderer->Renderer->LeftFlip();
		}

		Frame.CharacterFootHold = CreateActor<UIRenderActor>(UpdateOrder::UI);
		Frame.CharacterFootHold->Init(RenderOrder::UI, RenderDepth::ui);
		Frame.CharacterFootHold->Renderer->CreateAnimation("Character_FootHold", "Character_FootHold", 0.13f);
		Frame.CharacterFootHold->Renderer->ChangeAnimation("Character_FootHold");
		Frame.CharacterFootHold->Transform.SetLocalPosition({ 175 + 165 * static_cast<float>(i), -585 });

		AllCharacter.push_back(Frame);
	}

	if (false == BGMPlayer.IsPlaying())
	{
		BGMPlayer = GameEngineSound::SoundPlay("ServerSelect.mp3", 10000);
		return;
	}

	std::string BGMName = BGMPlayer.GetCurSoundName();
	if ("ServerSelect.mp3" != BGMName)
	{
		BGMPlayer.Stop();
		BGMPlayer = GameEngineSound::SoundPlay("ServerSelect.mp3", 10000);
	}
}

void CharacterSelect::LevelEnd(GameEngineLevel* _NextLevel)
{
	IsCharacterSelect = false;

	ContentLevel::LevelEnd(_NextLevel);

	if (nullptr != InfoFrame.CharacterInfo_BG)
	{
		InfoFrame.CharacterInfo_BG->Death();
		InfoFrame.CharacterInfo_BG = nullptr;

		InfoFrame.CharacterName->Death();
		InfoFrame.CharacterName = nullptr;

		InfoFrame.JobName->Death();
		InfoFrame.JobName = nullptr;

		InfoFrame.STR->Death();
		InfoFrame.STR = nullptr;

		InfoFrame.DEX->Death();
		InfoFrame.DEX = nullptr;

		InfoFrame.INT->Death();
		InfoFrame.INT = nullptr;

		InfoFrame.LUK->Death();
		InfoFrame.LUK = nullptr;
	}

	for (size_t i = 0; i < AllCharacter.size(); i++)
	{
		AllCharacter[i].CharacterRenderer->Death();
		AllCharacter[i].CharacterRenderer = nullptr;

		AllCharacter[i].CharacterFootHold->Death();
		AllCharacter[i].CharacterFootHold = nullptr;
	}

	SelectCollision->Death();
	SelectCollision = nullptr;

	AllCharacter.clear();
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
		if (true == GameEngineInput::IsDown(VK_RETURN, this))
		{
			FadeOutObject->SetChangeLevel("04.Lachlen");
			FadeOutObject->FadeStart();
			return;
		}

		if (true == SelectCollision->Collision(CollisionOrder::Mouse) && GameEngineInput::IsDown(VK_LBUTTON, this))
		{
			FadeOutObject->SetChangeLevel("04.Lachlen");
			FadeOutObject->FadeStart();
			return;
		}
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
	AllCharacter[0].CharacterRenderer->Renderer->SetPivotValue({ 0.35f, 0.5f });

	InfoFrame.FrameOn();
	CharSelectEffect0->On();
	CharSelectEffect1->On();

	GameEngineSoundPlayer CharSelectPlayer = GameEngineSound::SoundPlay("CharSelect.mp3");
}

void CharacterSelect::ResourcesRelease()
{
	ContentLevel::ResourcesRelease();

	if (nullptr != GameEngineSprite::Find("CharacterSelect_BG.png"))
	{
		GameEngineTexture::Release("CharacterSelect_BG.png");
		GameEngineSprite::Release("CharacterSelect_BG.png");
	}

	if (nullptr != GameEngineSprite::Find("CharacterSelect_Front.png"))
	{
		GameEngineTexture::Release("CharacterSelect_Front.png");
		GameEngineSprite::Release("CharacterSelect_Front.png");
	}

	if (nullptr != GameEngineSprite::Find("ServerName.png"))
	{
		GameEngineTexture::Release("ServerName.png");
		GameEngineSprite::Release("ServerName.png");
	}

	if (nullptr != GameEngineSprite::Find("ServerCharacterInfo_BG.png"))
	{
		GameEngineTexture::Release("ServerCharacterInfo_BG.png");
		GameEngineSprite::Release("ServerCharacterInfo_BG.png");
	}

	if (nullptr != GameEngineSprite::Find("Character_Empty.png"))
	{
		GameEngineTexture::Release("Character_Empty.png");
		GameEngineSprite::Release("Character_Empty.png");
	}

	if (nullptr != GameEngineSprite::Find("Character_Job.png"))
	{
		GameEngineTexture::Release("Character_Job.png");
		GameEngineSprite::Release("Character_Job.png");
	}

	if (nullptr != GameEngineSprite::Find("Character_FootHold"))
	{
		ReleaseFunction::FolderRelease("Character_FootHold", "Character_FootHold");
	}

	if (nullptr != GameEngineSprite::Find("Render_Idle"))
	{
		ReleaseFunction::FolderRelease("Render_Idle", "Idle_");
	}

	if (nullptr != GameEngineSprite::Find("Render_Walk"))
	{
		ReleaseFunction::FolderRelease("Render_Walk", "Walk_");
	}

	if (nullptr != GameEngineSprite::Find("CharSelectEffect0"))
	{
		ReleaseFunction::FolderRelease("CharSelectEffect0", "CharSelectEffect0_");
	}

	if (nullptr != GameEngineSprite::Find("CharSelectEffect1"))
	{
		ReleaseFunction::FolderRelease("CharSelectEffect1", "CharSelectEffect1_");
	}

	if (nullptr != GameEngineSprite::Find("Button_ChangeCP.png"))
	{
		GameEngineTexture::Release("Button_ChangeCP.png");
		GameEngineSprite::Release("Button_ChangeCP.png");
	}

	if (nullptr != GameEngineSprite::Find("Button_SecondPassword.png"))
	{
		GameEngineTexture::Release("Button_SecondPassword.png");
		GameEngineSprite::Release("Button_SecondPassword.png");
	}

	if (nullptr != GameEngineSprite::Find("Button_Otp.png"))
	{
		GameEngineTexture::Release("Button_Otp.png");
		GameEngineSprite::Release("Button_Otp.png");
	}

	if (nullptr != GameEngineSprite::Find("PageNumber.png"))
	{
		GameEngineTexture::Release("PageNumber.png");
		GameEngineSprite::Release("PageNumber.png");
	}

	if (nullptr != GameEngineSprite::Find("NameTag.png"))
	{
		GameEngineTexture::Release("NameTag.png");
		GameEngineSprite::Release("NameTag.png");
	}

	ContentButton::ReleaseButton("PrevButton");
	ContentButton::ReleaseButton("GoFirstLevel");
	ContentButton::ReleaseButton("LeftButton");
	ContentButton::ReleaseButton("PrevButton");
	ContentButton::ReleaseButton("CreateCharacter");
	ContentButton::ReleaseButton("DeleteCharacter");
	ContentButton::ReleaseButton("RightButton");
}