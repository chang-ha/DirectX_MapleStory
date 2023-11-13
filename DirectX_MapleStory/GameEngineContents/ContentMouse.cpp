#include "PreCompile.h"
#include "ContentMouse.h"

ContentMouse* ContentMouse::MainMouse = nullptr;

ContentMouse::ContentMouse()
{

}

ContentMouse::~ContentMouse()
{

}

void ContentMouse::LevelStart(GameEngineLevel* _PrevLevel)
{
	MainMouse = this;
}

void ContentMouse::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void ContentMouse::Start()
{
	GameEngineInput::AddInputObject(this);

	if (nullptr == GameEngineSprite::Find("Mouse_Normal.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\Mouse");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& Childs = Files[i];
			GameEngineTexture::Load(Childs.GetStringPath());
			GameEngineSprite::CreateSingle(Childs.GetFileName());
		}
	}

	if (nullptr == MouseRenderer)
	{
		MouseRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::MOUSE);
		MouseRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::mouse});
	}

	if (nullptr == MouseCollision)
	{
		MouseCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Mouse);
	}

	MouseRenderer->SetSprite("Mouse_Normal.png");
	MouseRenderer->SetPivotType(PivotType::LeftTop);
	MouseCollision->Transform.SetLocalScale({10, 10});
}

void ContentMouse::Update(float _Delta)
{
	// Position Setting
	float4 WindowPos = GetLevel()->GetMainCamera()->GetScreenMousePos();
	WindowPos.Y *= -1.0f;
	Transform.SetLocalPosition(WindowPos);
	MouseCollision->Transform.SetWorldPosition(GetLevel()->GetMainCamera()->GetWorldMousePos2D());

	// Click
	if (true == GameEngineInput::IsDown(VK_LBUTTON, this))
	{
		switch (State)
		{
		case MouseState::Normal:
			MouseRenderer->SetSprite("Mouse_Normal_Click.png");
			break;
		case MouseState::Button:
			MouseRenderer->SetSprite("Mouse_Button_Click.png");
			break;
		default:
			break;
		}
	}

	if (true == GameEngineInput::IsFree(VK_LBUTTON, this))
	{
		switch (State)
		{
		case MouseState::Normal:
			MouseRenderer->SetSprite("Mouse_Normal.png");
			break;
		case MouseState::Button:
			MouseRenderer->SetSprite("Mouse_Button.png");
			break;
		default:
			break;
		}
	}
}

void ContentMouse::Release()
{
	if (nullptr != MouseRenderer)
	{
		MouseRenderer->Death();
		MouseRenderer = nullptr;
	}

	if (nullptr != MouseCollision)
	{
		MouseCollision->Death();
		MouseCollision = nullptr;
	}
}