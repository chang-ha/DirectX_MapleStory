#include "PreCompile.h"
#include "Minimap.h"


Minimap::Minimap()
{

}

Minimap::~Minimap()
{

}

void Minimap::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Minimap::Start()
{

}

void Minimap::Update(float _Delta)
{
	
}

void Minimap::Release()
{

}

void Minimap::Init(std::string_view _MinimapName)
{
	MinimapObject.LT = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MinimapObject.LT->AutoSpriteSizeOn();
	MinimapObject.RT = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MinimapObject.RT->AutoSpriteSizeOn();
	MinimapObject.LB = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MinimapObject.LB->AutoSpriteSizeOn();
	MinimapObject.RB = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MinimapObject.RB->AutoSpriteSizeOn();
	MinimapObject.Minimap = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MinimapObject.Minimap->AutoSpriteSizeOn();
	// Scale값 계산해서 조정
	MinimapObject.RM = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MinimapObject.LM = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MinimapObject.MB = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MinimapObject.MT = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	
	// Load MinimapFrame
	if (nullptr == GameEngineSprite::Find("Map_LT.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\MinimapFrame");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& Childs = Files[i];
			GameEngineTexture::Load(Childs.GetStringPath());
			GameEngineSprite::CreateSingle(Childs.GetFileName());
		}
	}

	// Load Minimap
	if (nullptr == GameEngineSprite::Find(_MinimapName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Textures\\UI\\Minimap\\");
		GameEngineTexture::Load(FilePath.GetStringPath() + std::string(_MinimapName.data()));
		GameEngineSprite::CreateSingle(_MinimapName);
	}
	MinimapScale = GameEngineTexture::Find(_MinimapName)->GetScale();
	MinimapObject.Minimap->SetSprite(_MinimapName);
	FullMinimapScale = MinimapScale + float4{18, 70};

	MinimapObject.LT->SetSprite("Map_LT.png");
	MinimapObject.RT->SetSprite("Map_RT.png");
	MinimapObject.LB->SetSprite("Map_LB.png");
	MinimapObject.RB->SetSprite("Map_RB.png");

	MinimapObject.RM->SetSprite("Map_RM.png");
	MinimapObject.LM->SetSprite("Map_LM.png");
	MinimapObject.MB->SetSprite("Map_MB.png");
	MinimapObject.MT->SetSprite("Map_MT.png");

	MinimapObject.LT->Transform.SetLocalPosition({0, 0, RenderDepth::ui});
	MinimapObject.RT->Transform.SetLocalPosition({ FullMinimapScale.X, 0, RenderDepth::ui});
	MinimapObject.LB->Transform.SetLocalPosition({0, - FullMinimapScale.Y, RenderDepth::ui});
	MinimapObject.RB->Transform.SetLocalPosition({ FullMinimapScale.X, - FullMinimapScale.Y, RenderDepth::ui});
	MinimapObject.RM->Transform.SetLocalPosition({ FullMinimapScale.X, - FullMinimapScale.Y + 61, RenderDepth::ui});
	MinimapObject.LM->Transform.SetLocalPosition({0, - FullMinimapScale.Y + 61, RenderDepth::ui});
	MinimapObject.MB->Transform.SetLocalPosition({64, FullMinimapScale.Y, RenderDepth::ui});
	MinimapObject.MT->Transform.SetLocalPosition({64, 0, RenderDepth::ui});
	MinimapObject.Minimap->Transform.SetLocalPosition({9, -FullMinimapScale.Y + 9, RenderDepth::ui});

	MinimapObject.LT->SetPivotType(PivotType::LeftTop);
	MinimapObject.RT->SetPivotType(PivotType::RightUp);
	MinimapObject.LB->SetPivotType(PivotType::LeftBottom);
	MinimapObject.RB->SetPivotType(PivotType::RightBottom);
	MinimapObject.MT->SetPivotType(PivotType::LeftTop);
	MinimapObject.MB->SetPivotType(PivotType::LeftBottom);
	MinimapObject.RM->SetPivotType(PivotType::RightUp);
	MinimapObject.LM->SetPivotType(PivotType::LeftTop);
	MinimapObject.Minimap->SetPivotType(PivotType::LeftBottom);
}
