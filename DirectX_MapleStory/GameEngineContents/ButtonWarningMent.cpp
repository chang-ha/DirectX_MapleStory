#include "PreCompile.h"
#include "ButtonWarningMent.h"
#include "ContentButton.h"
#include "ContentLevel.h"

void OneButtonWarningMentStruct::StructStart(ButtonWarningMent* _Parent)
{
	Parent = _Parent;

	MentBG = Parent->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MentBG->Transform.SetLocalPosition({ 0, 0, RenderDepth::ui });
	MentBG->GetColorData().MulColor.A = 0.0f;

	Ment = Parent->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Ment->Transform.SetLocalPosition({ 1, 14, RenderDepth::ui });
	Ment->Off();

	CancelButton = ContentLevel::CurContentLevel->CreateActor<ContentButton>(UpdateOrder::UI);
	CancelButton->Init("CancelButton");
	CancelButton->SetParent(Parent, 0);
	CancelButton->GetButtonRenderer()->GetColorData().MulColor.A = 0.0f;
	CancelButton->CollisionOff();

	CancelButton->SetButtonClickEndEvent([&]()
		{
			IsClickOff = true;
			Ment->Off();
			CancelButton->CollisionOff();
			ContentLevel::CurContentLevel->AllButtonOn();
		});

	CancelButton->Transform.SetLocalPosition({ 0, -50 });
}

void OneButtonWarningMentStruct::AlphaUpdate(float _Delta)
{
	if (false == AlphaUpdateValue)
	{
		return;
	}

	if (1.0f > MentBG->GetColorData().MulColor.A)
	{
		MentBG->GetColorData().MulColor.A  += _Delta * AlphaSpeed;
		CancelButton->GetButtonRenderer()->GetColorData().MulColor.A += _Delta * AlphaSpeed;
	}

	if (1.0f < MentBG->GetColorData().MulColor.A)
	{
		MentBG->GetColorData().MulColor.A = 1.0f;
		CancelButton->GetButtonRenderer()->GetColorData().MulColor.A = 1.0f;
	}

	if (1.0f == MentBG->GetColorData().MulColor.A)
	{
		Ment->On();
		CancelButton->CollisionOn();
		AlphaUpdateValue = false;
	}
}

void OneButtonWarningMentStruct::DeathUpdate(float _Delta)
{
	if (false == IsClickOff)
	{
		return;
	}

	if (0.0f < MentBG->GetColorData().MulColor.A)
	{
		MentBG->GetColorData().MulColor.A -= _Delta * AlphaSpeed;
		CancelButton->GetButtonRenderer()->GetColorData().MulColor.A -= _Delta * AlphaSpeed;
	}

	if (0.0f > MentBG->GetColorData().MulColor.A)
	{
		MentBG->GetColorData().MulColor.A = 0.0f;
		CancelButton->GetButtonRenderer()->GetColorData().MulColor.A = 0.0f;
	}

	if (0.0f == MentBG->GetColorData().MulColor.A)
	{
		Parent->Death();
	}
}

void TwoButtonWarningMentStruct::StructStart(ButtonWarningMent* _Parent)
{
	OneButtonWarningMentStruct::StructStart(_Parent);

	OkButton = ContentLevel::CurContentLevel->CreateActor<ContentButton>(UpdateOrder::UI);
	OkButton->Init("OkButton");
	OkButton->SetParent(Parent, 0);
	OkButton->Transform.SetLocalPosition({ -40, -50 });
	OkButton->GetButtonRenderer()->GetColorData().MulColor.A = 0.0f;
	OkButton->CollisionOff();

	CancelButton->Transform.SetLocalPosition({ 40, -50 });
}

void TwoButtonWarningMentStruct::AlphaUpdate(float _Delta)
{
	if (false == AlphaUpdateValue)
	{
		return;
	}

	OkButton->CollisionOff();

	if (1.0f > MentBG->GetColorData().MulColor.A)
	{
		MentBG->GetColorData().MulColor.A += _Delta * AlphaSpeed;
		CancelButton->GetButtonRenderer()->GetColorData().MulColor.A += _Delta * AlphaSpeed;
		OkButton->GetButtonRenderer()->GetColorData().MulColor.A += _Delta * AlphaSpeed;
	}

	if (1.0f < MentBG->GetColorData().MulColor.A)
	{
		MentBG->GetColorData().MulColor.A = 1.0f;
		CancelButton->GetButtonRenderer()->GetColorData().MulColor.A = 1.0f;
		OkButton->GetButtonRenderer()->GetColorData().MulColor.A = 1.0f;
	}

	if (1.0f == MentBG->GetColorData().MulColor.A)
	{
		Ment->On();
		CancelButton->CollisionOn();
		OkButton->CollisionOn();
		AlphaUpdateValue = false;
	}
}

void TwoButtonWarningMentStruct::DeathUpdate(float _Delta)
{
	if (false == IsClickOff)
	{
		return;
	}

	if (0.0f < MentBG->GetColorData().MulColor.A)
	{
		MentBG->GetColorData().MulColor.A -= _Delta * AlphaSpeed;
		CancelButton->GetButtonRenderer()->GetColorData().MulColor.A -= _Delta * AlphaSpeed;
		OkButton->GetButtonRenderer()->GetColorData().MulColor.A -= _Delta * AlphaSpeed;
	}

	if (0.0f > MentBG->GetColorData().MulColor.A)
	{
		MentBG->GetColorData().MulColor.A = 0.0f;
		CancelButton->GetButtonRenderer()->GetColorData().MulColor.A = 0.0f;
		OkButton->GetButtonRenderer()->GetColorData().MulColor.A = 0.0f;
	}

	if (0.0f == MentBG->GetColorData().MulColor.A)
	{
		Parent->Death();
	}
}

ButtonWarningMent::ButtonWarningMent()
{

}

ButtonWarningMent::~ButtonWarningMent()
{

}

void ButtonWarningMent::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void ButtonWarningMent::Start()
{
	ContentLevel::CurContentLevel->AllButtonOff();
}

void ButtonWarningMent::Update(float _Delta)
{
	MentObject->AlphaUpdate(_Delta);
	MentObject->DeathUpdate(_Delta);
	MoveUpdate(_Delta);
}

void ButtonWarningMent::Release()
{

}

void ButtonWarningMent::MoveUpdate(float _Delta)
{
	if (0.0f < RemainMoveX)
	{
		float Move = MoveSpeed * _Delta;
		RemainMoveX -= Move;
		if (0.0f > RemainMoveX)
		{
			Move += RemainMoveX;
			RemainMoveX = 0.0f;
		}
		Transform.AddLocalPosition(-Move);
	}

	if (0.0f < RemainMoveY)
	{
		float Move = MoveSpeed * _Delta;
		RemainMoveY -= Move;
		if (0.0f > RemainMoveY)
		{
			Move += RemainMoveY;
			RemainMoveX = 0.0f;
		}
		Transform.AddLocalPosition(float4(0, -Move));
	}
}

void ButtonWarningMent::Init(std::string_view _BGName, std::string_view _WarningMentName)
{
	if (nullptr == GameEngineSprite::Find(_BGName))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\ButtonWarningMent\\BG\\" + std::string(_BGName));
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(_BGName);
	}

	if (nullptr == GameEngineSprite::Find(_WarningMentName))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\ButtonWarningMent\\Ment\\" + std::string(_WarningMentName));
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(_WarningMentName);
	}

	MentObject->MentBG->SetSprite(_BGName);
	MentObject->Ment->SetSprite(_WarningMentName);
}

std::shared_ptr<class ContentButton> ButtonWarningMent::GetOkButton()
{
	std::shared_ptr<TwoButtonWarningMentStruct> ConvertPtr = std::dynamic_pointer_cast<TwoButtonWarningMentStruct>(MentObject);

	if (nullptr == ConvertPtr)
	{
		MsgBoxAssert("Ok버튼이 존재하지 않는 경고문구 입니다.");
	}

	return ConvertPtr->OkButton;
}

std::shared_ptr<ButtonWarningMent> ButtonWarningMent::CreateOneButtonMent()
{
	std::shared_ptr<ButtonWarningMent> _Ment = ContentLevel::CurContentLevel->CreateActor<ButtonWarningMent>(UpdateOrder::UI);

	std::shared_ptr<OneButtonWarningMentStruct> _MentObject = std::make_shared<OneButtonWarningMentStruct>();
	_MentObject->StructStart(_Ment.get());
	_Ment->MentObject = _MentObject;
	_Ment->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half() + float4{ MOVEPOS_X, MOVEPOS_Y });

	return _Ment;
}

std::shared_ptr<ButtonWarningMent> ButtonWarningMent::CreateTwoButtonMent()
{
	std::shared_ptr<ButtonWarningMent> _Ment = ContentLevel::CurContentLevel->CreateActor<ButtonWarningMent>(UpdateOrder::UI);

	std::shared_ptr<TwoButtonWarningMentStruct> _MentObject = std::make_shared<TwoButtonWarningMentStruct>();
	_MentObject->StructStart(_Ment.get());
	_Ment->MentObject = _MentObject;
	_Ment->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half() + float4{ MOVEPOS_X, MOVEPOS_Y });

	return _Ment;
}

