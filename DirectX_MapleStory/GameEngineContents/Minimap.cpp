#include "PreCompile.h"
#include "Minimap.h"
#include "Player.h"
#include "ContentMap.h"

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
	if (nullptr == Player::MainPlayer)
	{
		MinimapObject.MiniPlayer->Off();
	}
	else
	{
		PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
		PlayerPos = (PlayerPos * MinimapScale) / RealMapScale;
		MinimapObject.MiniPlayer->Transform.SetLocalPosition(PlayerPos + float4{ 9, -61, RenderDepth::ui });
	}
}

void Minimap::Release()
{

}

void Minimap::Init(std::string_view _MinimapName, std::string_view _MinimapTextName)
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

	MinimapObject.MiniPlayer = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MinimapObject.MiniPlayer->AutoSpriteSizeOn();

	MinimapObject.MapName1 = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MinimapObject.MapName2 = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);

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

	MinimapObject.MiniPlayer->SetSprite("user.png");

	MinimapObject.LT->Transform.SetLocalPosition({0, 0, RenderDepth::ui});
	MinimapObject.RT->Transform.SetLocalPosition({ FullMinimapScale.X, 0, RenderDepth::ui});
	MinimapObject.LB->Transform.SetLocalPosition({0, - FullMinimapScale.Y, RenderDepth::ui});
	MinimapObject.RB->Transform.SetLocalPosition({ FullMinimapScale.X, - FullMinimapScale.Y, RenderDepth::ui});
	MinimapObject.RM->Transform.SetLocalPosition({ FullMinimapScale.X, -67, RenderDepth::ui});
	MinimapObject.LM->Transform.SetLocalPosition({0, -67, RenderDepth::ui});
	MinimapObject.MB->Transform.SetLocalPosition({64, - FullMinimapScale.Y, RenderDepth::ui});
	MinimapObject.MT->Transform.SetLocalPosition({64, 0, RenderDepth::ui});
	MinimapObject.Minimap->Transform.SetLocalPosition({9, -FullMinimapScale.Y + 9, RenderDepth::ui});
	MinimapObject.MapName1->Transform.SetLocalPosition({ 48, -17, RenderDepth::ui });
	MinimapObject.MapName2->Transform.SetLocalPosition({ 48, -35, RenderDepth::ui });

	MinimapObject.LT->SetPivotType(PivotType::LeftTop);
	MinimapObject.RT->SetPivotType(PivotType::RightUp);
	MinimapObject.LB->SetPivotType(PivotType::LeftBottom);
	MinimapObject.RB->SetPivotType(PivotType::RightBottom);
	MinimapObject.MT->SetPivotType(PivotType::LeftTop);
	MinimapObject.MB->SetPivotType(PivotType::LeftBottom);
	MinimapObject.RM->SetPivotType(PivotType::RightUp);
	MinimapObject.LM->SetPivotType(PivotType::LeftTop);
	MinimapObject.Minimap->SetPivotType(PivotType::LeftBottom);
	MinimapObject.MiniPlayer->SetPivotType(PivotType::Bottom);

	MinimapObject.MT->SetImageScale({ FullMinimapScale.X - 128 , 61, 1});
	MinimapObject.MT->RenderBaseInfoValue.VertexUVMul.X = FullMinimapScale.X - 128;

	MinimapObject.MB->SetImageScale({ FullMinimapScale.X - 128 , 9, 1 });
	MinimapObject.MB->RenderBaseInfoValue.VertexUVMul.X = FullMinimapScale.X - 128;

	MinimapObject.LM->SetImageScale({ 9 , FullMinimapScale.Y - 94, 1 });
	MinimapObject.LM->RenderBaseInfoValue.VertexUVMul.Y = FullMinimapScale.Y - 94;

	MinimapObject.RM->SetImageScale({ 9 , FullMinimapScale.Y - 94, 1 });
	MinimapObject.RM->RenderBaseInfoValue.VertexUVMul.Y = FullMinimapScale.Y - 94;

	RealMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();

	MinimapObject.MapName1->SetText("돋움", "레헬른", 13.0f, float4::WHITE, FW1_LEFT);
	MinimapObject.MapName2->SetText("돋움", _MinimapTextName.data(), 13.0f, float4::WHITE, FW1_LEFT);
}
