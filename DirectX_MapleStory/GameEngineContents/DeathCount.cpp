#include "PreCompile.h"
#include "DeathCount.h"

DeathCount::DeathCount()
{

}

DeathCount::~DeathCount()
{

}

void DeathCount::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void DeathCount::Start()
{
	if (nullptr == GameEngineSprite::Find("DeathCountFrame.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\DeathCount");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& Childs = Files[i];
			GameEngineTexture::Load(Childs.GetStringPath());
			GameEngineSprite::CreateSingle(Childs.GetFileName());
		}
	}

	Frame.CounterFrame = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Frame.CounterNum1 = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Frame.CounterNum2 = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);

	Frame.CounterFrame->SetSprite("DeathCountFrame.png");
	Frame.CounterNum1->SetSprite("DeathCountNum_1.png");
	Frame.CounterNum2->SetSprite("DeathCountNum_0.png");

	Frame.CounterFrame->AutoSpriteSizeOn();
	Frame.CounterNum1->AutoSpriteSizeOn();
	Frame.CounterNum2->AutoSpriteSizeOn();

	Frame.CounterFrame->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 160, -75.0f, RenderDepth::ui});
	Frame.CounterNum1->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 148, -85.0f, RenderDepth::ui });
	Frame.CounterNum2->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 133, -85.0f, RenderDepth::ui});
}

void DeathCount::Update(float _Delta)
{
	
}

void DeathCount::Release()
{

}