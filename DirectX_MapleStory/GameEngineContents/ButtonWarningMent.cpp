#include "PreCompile.h"
#include "ButtonWarningMent.h"
#include "ContentButton.h"
#include "ContentLevel.h"

void OneButtonWarningMentStruct::StructStart(ButtonWarningMent* _Parent)
{
	Parent = _Parent;

	MentBG = Parent->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MentBG->SetSprite("MentBG_0.png");
	MentBG->Transform.SetLocalPosition({ 0, 0, RenderDepth::ui });
	MentBG->GetColorData().MulColor.A = 0.0f;

	CancelButton = ContentLevel::CurContentLevel->CreateActor<ContentButton>(UpdateOrder::UI);
	CancelButton->Init("CancelButton");
	CancelButton->SetParent(Parent, 0);
	CancelButton->GetButtonRenderer()->GetColorData().MulColor.A = 0.0f;
	CancelButton->CollisionOff();

	CancelButton->SetButtonClickEndEvent([&]()
		{
			IsClickOff = true;
			CancelButton->CollisionOff();
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
	if (nullptr == GameEngineSprite::Find("MentBG_0.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\Button\\MentBG_0.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}
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

