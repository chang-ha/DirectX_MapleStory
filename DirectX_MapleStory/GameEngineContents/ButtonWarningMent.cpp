#include "PreCompile.h"
#include "ButtonWarningMent.h"
#include "ContentButton.h"
#include "ContentLevel.h"

void OneButtonWarningMentStruct::StructStart(GameEngineActor* _Parent)
{
	Parent = _Parent;

	MentBG = Parent->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MentBG->SetSprite("MentBG_0.png");
	MentBG->Transform.SetLocalPosition({ 0, 0, RenderDepth::ui });

	CancelButton = ContentLevel::CurContentLevel->CreateActor<ContentButton>(UpdateOrder::UI);
	CancelButton->Init("CancelButton");
	CancelButton->SetParent(Parent, 0);

	CancelButton->SetButtonClickEndEvent([&]()
		{
			Parent->Death();
		});

	CancelButton->Transform.SetLocalPosition({ 0, -50 });
}

void TwoButtonWarningMentStruct::StructStart(GameEngineActor* _Parent)
{
	OneButtonWarningMentStruct::StructStart(_Parent);

	OkButton = ContentLevel::CurContentLevel->CreateActor<ContentButton>(UpdateOrder::UI);
	OkButton->Init("OkButton");
	OkButton->SetParent(Parent, 0);
	OkButton->Transform.SetLocalPosition({ -40, -50 });

	CancelButton->Transform.SetLocalPosition({ 40, -50 });
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
	
}

void ButtonWarningMent::Release()
{

}

std::shared_ptr<ButtonWarningMent> ButtonWarningMent::CreateOneButtonMent()
{
	std::shared_ptr<ButtonWarningMent> _Ment = ContentLevel::CurContentLevel->CreateActor<ButtonWarningMent>(UpdateOrder::UI);

	std::shared_ptr<OneButtonWarningMentStruct> _MentObject = std::make_shared<OneButtonWarningMentStruct>();
	_MentObject->StructStart(_Ment.get());
	_Ment->MentObject = _MentObject;

	return _Ment;
}

std::shared_ptr<ButtonWarningMent> ButtonWarningMent::CreateTwoButtonMent()
{
	std::shared_ptr<ButtonWarningMent> _Ment = ContentLevel::CurContentLevel->CreateActor<ButtonWarningMent>(UpdateOrder::UI);

	std::shared_ptr<TwoButtonWarningMentStruct> _MentObject = std::make_shared<TwoButtonWarningMentStruct>();
	_MentObject->StructStart(_Ment.get());
	_Ment->MentObject = _MentObject;

	return _Ment;
}