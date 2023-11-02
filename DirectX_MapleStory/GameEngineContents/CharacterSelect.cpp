#include "PreCompile.h"
#include "CharacterSelect.h"
#include "ContentMap.h"
#include "RenderActor.h"
#include "FadeObject.h"

CharacterSelect::CharacterSelect()
{

}

CharacterSelect::~CharacterSelect()
{

}

void CharacterSelect::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
	FadeInObject->SetFadeSpeed(2.0f);

	if (nullptr == GameEngineSprite::Find("CharacterSelect_BG.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Login\\CharacterSelect");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& Childs = Files[i];
			GameEngineTexture::Load(Childs.GetStringPath());
			GameEngineSprite::CreateSingle(Childs.GetFileName());
		}
	}

	std::shared_ptr<RenderActor> _Actor = CreateActor<RenderActor>(UpdateOrder::RenderActor);
	_Actor->Init(RenderOrder::MAP, RenderDepth::map);
	_Actor->Renderer->SetSprite("CharacterSelect_BG.png");
	_Actor->Renderer->AutoSpriteSizeOff();
	_Actor->Renderer->SetImageScale(GlobalValue::WinScale);
	_Actor->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());

	_Actor = CreateActor<RenderActor>(UpdateOrder::RenderActor);
	_Actor->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor->Renderer->SetSprite("CharacterSelect_Front.png");
	_Actor->Renderer->AutoSpriteSizeOff();
	_Actor->Renderer->SetImageScale(GlobalValue::WinScale);
	_Actor->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());

	GetMainCamera()->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());
}

void CharacterSelect::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
}

void CharacterSelect::Start()
{
	ContentLevel::Start();

}

void CharacterSelect::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}