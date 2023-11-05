#include "PreCompile.h"
#include "WarningMent.h"

WarningMent::WarningMent()
{

}

WarningMent::~WarningMent()
{

}

void WarningMent::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void WarningMent::Start()
{
	if (nullptr == GameEngineSprite::Find("WarningMent_Start.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\WarningMentFrame");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& Childs = Files[i];
			GameEngineTexture::Load(Childs.GetStringPath());
			GameEngineSprite::CreateSingle(Childs.GetFileName());
		}
	}
	Frame.FrameStart = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Frame.FrameMiddle = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Frame.FrameEnd = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Frame.WarningMent = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);

	Frame.FrameStart->SetSprite("WarningMent_Start.png");
	Frame.FrameMiddle->SetSprite("WarningMent_Middle.png");
	Frame.FrameEnd->SetSprite("WarningMent_End.png");

	Frame.FrameStart->AutoSpriteSizeOn();
	Frame.FrameEnd->AutoSpriteSizeOn();

	Frame.FrameStart->SetPivotType(PivotType::Right);
	Frame.FrameMiddle->SetPivotType(PivotType::Center);
	Frame.FrameEnd->SetPivotType(PivotType::Left);

	Off();
}

void WarningMent::Update(float _Delta)
{
	WarningTime -= _Delta;

	if (0.0f >= WarningTime)
	{
		Off();
		WarningTime = WarningTime_Value;
	}
}

void WarningMent::Release()
{

}

void WarningMent::SetWarningMent(std::string_view _Ment)
{
	On();

	float TextBoxSize = static_cast<float>(_Ment.size()) * 11.0f;

	Frame.WarningMent->SetText("돋움", _Ment.data() , 19.0f, float4::WHITE, FW1_CENTER);

	Frame.FrameStart->Transform.SetLocalPosition({ GlobalValue::WinScale.Half().X - TextBoxSize / 2.0f, -200, RenderDepth::ui });
	Frame.FrameMiddle->Transform.SetLocalPosition({ GlobalValue::WinScale.Half().X, -200, RenderDepth::ui });
	Frame.FrameEnd->Transform.SetLocalPosition({ GlobalValue::WinScale.Half().X + TextBoxSize / 2.0f, -200, RenderDepth::ui });
	Frame.WarningMent->Transform.SetLocalPosition({ GlobalValue::WinScale.Half().X, -203, RenderDepth::ui });

	Frame.FrameMiddle->SetImageScale({ TextBoxSize, 92, 1 });
	Frame.FrameMiddle->RenderBaseInfoValue.VertexUVMul.X = TextBoxSize;
}
