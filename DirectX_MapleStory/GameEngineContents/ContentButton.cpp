#include "PreCompile.h"
#include "ContentButton.h"
#include "ContentLevel.h"

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
		ButtonRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::ui });
	}

	if (nullptr == ButtonCollision)
	{
		ButtonCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Button);
	}
}

void ContentButton::Update(float _Delta)
{
	StateUpdate(_Delta);
	CalcuUItoMain();
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
	ButtonName = _ButtonName;
	if (nullptr == GameEngineSprite::Find(std::string(ButtonName) + "_Normal.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\Button\\" + std::string(ButtonName));
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& Childs = Files[i];
			GameEngineTexture::Load(Childs.GetStringPath());
			GameEngineSprite::CreateSingle(Childs.GetFileName());
		}
	}

	ButtonRenderer->SetSprite(std::string(ButtonName) + "_Normal.png");

	std::shared_ptr<GameEngineTexture> _Texture = GameEngineTexture::Find(std::string(ButtonName) + "_Normal.png");
	ButtonScale = _Texture->GetScale();
	ButtonScale.Z = 1.0f;
	ButtonCollision->Transform.SetLocalScale(ButtonScale);
}

void ContentButton::ReleaseButton(std::string_view _ButtonTextureName)
{
	if (nullptr != GameEngineSprite::Find(std::string(_ButtonTextureName) + "_Normal.png"))
	{
		GameEngineSprite::Release(std::string(_ButtonTextureName) + "_Normal.png");
	}

	if (nullptr != GameEngineSprite::Find(std::string(_ButtonTextureName) + "_MouseOver.png"))
	{
		GameEngineSprite::Release(std::string(_ButtonTextureName) + "_MouseOver.png");
	}

	if (nullptr != GameEngineSprite::Find(std::string(_ButtonTextureName) + "_Click.png"))
	{
		GameEngineSprite::Release(std::string(_ButtonTextureName) + "_Click.png");
	}

	if (nullptr != GameEngineSprite::Find(std::string(_ButtonTextureName) + "_Disabled.png"))
	{
		GameEngineSprite::Release(std::string(_ButtonTextureName) + "_Disabled.png");
	}
}

void ContentButton::CalcuUItoMain()
{
	float4 Pos = /*ContentLevel::CurContentLevel->GetCamera(static_cast<int>(ECAMERAORDER::UI))->*/Transform.GetWorldPosition();
	const TransformData& MainTrans = ContentLevel::CurContentLevel->GetMainCamera()->Transform.GetConstTransformDataRef();
	const TransformData& UITrans = ContentLevel::CurContentLevel->GetCamera(static_cast<int>(ECAMERAORDER::UI))->Transform.GetConstTransformDataRef();

	Pos *= UITrans.ViewMatrix;
	Pos *= UITrans.ProjectionMatrix;
	Pos *= MainTrans.ProjectionMatrix.InverseReturn();
	Pos *= MainTrans.ViewMatrix.InverseReturn();
	ButtonCollision->Transform.SetWorldPosition(Pos);
}

void ContentButton::ChangeState(ButtonState _State)
{
	if (_State != State)
	{
		// State End
		switch (State)
		{
		case ButtonState::Normal:
			NormalEnd();
			break;
		case ButtonState::MouseOver:
			MouseOverEnd();
			break;
		case ButtonState::Click:
			ClickEnd();
			break;
		case ButtonState::Disabled:
			DisabledEnd();
			break;
		default:
			MsgBoxAssert("존재하지 않는 상태값으로 변경하려고 했습니다.");
			break;
		}

		// State Start
		switch (_State)
		{
		case ButtonState::Normal:
			NormalStart();
			break;
		case ButtonState::MouseOver:
			MouseOverStart();
			break;
		case ButtonState::Click:
			ClickStart();
			break;
		case ButtonState::Disabled:
			DisabledStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void ContentButton::StateUpdate(float _Delta)
{
	switch (State)
	{
	case ButtonState::Normal:
		return NormalUpdate(_Delta);
	case ButtonState::MouseOver:
		return MouseOverUpdate(_Delta);
	case ButtonState::Click:
		return ClickUpdate(_Delta);
	case ButtonState::Disabled:
		return DisabledUpdate(_Delta);
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
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

void ContentButton::NormalStart()
{
	ButtonRenderer->SetSprite(std::string(ButtonName) + "_Normal.png");
}

void ContentButton::MouseOverStart()
{
	ButtonRenderer->SetSprite(std::string(ButtonName) + "_MouseOver.png");

}

void ContentButton::ClickStart()
{
	ButtonRenderer->SetSprite(std::string(ButtonName) + "_Click.png");
}

void ContentButton::DisabledStart()
{
	// ButtonRenderer->SetSprite(std::string(ButtonName) + "_Disabled.png");
}

void ContentButton::NormalUpdate(float _Delta)
{
	if (true == ButtonCollision->Collision(CollisionOrder::Mouse))
	{
		ChangeState(ButtonState::MouseOver);
		return;
	}
}

void ContentButton::MouseOverUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_LBUTTON, this))
	{
		if (nullptr != ButtonClickEvent)
		{
			ButtonClickEvent();
		}
		ChangeState(ButtonState::Click);
		return;
	}

	if (false == ButtonCollision->Collision(CollisionOrder::Mouse))
	{
		ChangeState(ButtonState::Normal);
		return;
	}

	if (nullptr != ButtonStayEvent)
	{
		ButtonStayEvent();
	}
}

void ContentButton::ClickUpdate(float _Delta)
{
	if (true == GameEngineInput::IsUp(VK_LBUTTON, this))
	{
		if (true == ButtonCollision->Collision(CollisionOrder::Mouse))
		{
			if (nullptr != ButtonClickEndEvent)
			{
				ButtonClickEndEvent();
			}
			ChangeState(ButtonState::Normal);
			return;
		}
		else
		{
			ChangeState(ButtonState::Normal);
			return;
		}
	}
}

void ContentButton::DisabledUpdate(float _Delta)
{

}

void ContentButton::NormalEnd()
{

}

void ContentButton::MouseOverEnd()
{

}

void ContentButton::ClickEnd()
{

}

void ContentButton::DisabledEnd()
{

}