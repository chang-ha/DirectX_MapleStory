#include "PreCompile.h"
#include "ButtonWarningMent.h"
#include "ContentButton.h"

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
	MentObject.MentBG = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);

	MentObject._OkButton = GetLevel()->CreateActor<ContentButton>(UpdateOrder::UI);
	MentObject._CancelButton = GetLevel()->CreateActor<ContentButton>(UpdateOrder::UI);

	MentObject._OkButton->Init("OkButton");
	MentObject._CancelButton->Init("CancelButton");

	MentObject._CancelButton->SetButtonClickEndEvent([&]()
		{
			Death();
		});
}

void ButtonWarningMent::Update(float _Delta)
{
	
}

void ButtonWarningMent::Release()
{

}

std::shared_ptr<ButtonWarningMent> ButtonWarningMent::CreateOneButtonMent()
{
	
}

std::shared_ptr<ButtonWarningMent> ButtonWarningMent::CreateTwoButtonMent()
{

}