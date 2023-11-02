#include "PreCompile.h"
#include "ContentButton.h"

ContentButton::ContentButton()
{

}

ContentButton::~ContentButton()
{

}

void ContentButton::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void ContentButton::Start()
{
	GameEngineInput::AddInputObject(this);

	if (nullptr == ButtonRenderer)
	{
		ButtonRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		ButtonRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::ui});
	}

	if (nullptr == ButtonCollision)
	{
		ButtonCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Button);
	}
}

void ContentButton::Update(float _Delta)
{
	if (true == ButtonCollision->Collision(CollisionOrder::Mouse))
	{
		if (nullptr != ButtonStayEvent)
		{
			ButtonStayEvent();
		}

		if (true == GameEngineInput::IsDown(VK_LBUTTON, this))
		{
			IsClick = true;
			if (nullptr != ButtonClickEvent)
			{
				ButtonClickEvent();
			}
		}

		if (true == IsClick && true == GameEngineInput::IsUp(VK_LBUTTON, this))
		{
			IsClick = false;
			if (nullptr != ButtonClickEndEvent)
			{
				ButtonClickEndEvent();
			}
		}
	}
}

void ContentButton::Release()
{
	if (nullptr != ButtonRenderer)
	{
		ButtonRenderer->Death();
		ButtonRenderer = nullptr;
	}

	if (nullptr != ButtonCollision)
	{
		ButtonCollision->Death();
		ButtonCollision = nullptr;
	}
}

void ContentButton::Init(std::string_view _ButtonName)
{
	if (nullptr == GameEngineSprite::Find(std::string(_ButtonName) + "_Normal.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\Button\\" + std::string(_ButtonName));
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& Childs = Files[i];
			GameEngineTexture::Load(Childs.GetStringPath());
			GameEngineSprite::CreateSingle(Childs.GetFileName());
		}
	}

	ButtonRenderer->SetSprite(std::string(_ButtonName) + "_Normal.png");
	
	std::shared_ptr<GameEngineTexture> _Texture = GameEngineTexture::Find(std::string(_ButtonName) + "_Normal.png");
	float4 ButtonScale = _Texture->GetScale();
	ButtonScale.Z = 1.0f;
	ButtonCollision->Transform.SetLocalScale(ButtonScale);
}

void ContentButton::SetButtonClickEvent(std::function<void()> _Function)
{
	ButtonClickEvent = _Function;
}

void ContentButton::SetButtonClickEndEvent(std::function<void()> _Function)
{
	ButtonClickEndEvent = _Function;
}

void ContentButton::SetButtonStayEvent(std::function<void()> _Function)
{
	ButtonStayEvent = _Function;
}

