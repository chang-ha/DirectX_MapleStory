#include "PreCompile.h"
#include "PlayerUIManager.h"
#include "Player.h"

PlayerUIManager::PlayerUIManager()
{

}

PlayerUIManager::~PlayerUIManager()
{

}

void PlayerUIManager::LevelStart(class GameEngineLevel* _PrevLevel)
{
	if (nullptr == GameEngineSprite::Find("HP_Bar.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\HP_Bar.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("HP_Bar_BG.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\HP_Bar_BG.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("EXP_Bar.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\EXP_Bar.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("HP.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\HP.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	if (nullptr == GameEngineSprite::Find("MP.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\MP.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	EXP_Bar = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	EXP_Bar->SetPivotType(PivotType::Bottom);
	EXP_Bar->Transform.SetLocalPosition({ GlobalValue::WinScale.hX(), -GlobalValue::WinScale.Y, RenderDepth::ui });
	EXP_Bar->SetSprite("EXP_Bar.png");

	HP_Bar_BG = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	HP_Bar_BG->SetPivotType(PivotType::Bottom);
	HP_Bar_BG->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 9.0f, -GlobalValue::WinScale.Y + 19.0f, RenderDepth::ui });
	HP_Bar_BG->SetSprite("HP_Bar_BG.png");
	HP_Bar_BG->SetImageScale({ 173, 32 });

	HP = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	HP->SetPivotType(PivotType::LeftBottom);
	HP->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 76.0f, -GlobalValue::WinScale.Y + 37.0f, RenderDepth::ui });
	HP->SetSprite("HP.png");

	MP = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MP->SetPivotType(PivotType::LeftBottom);
	MP->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 76.0f, -GlobalValue::WinScale.Y + 21.0f, RenderDepth::ui });
	MP->SetSprite("MP.png");

	HP_Bar = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	HP_Bar->SetPivotType(PivotType::Bottom);
	HP_Bar->Transform.SetLocalPosition({ GlobalValue::WinScale.hX(), -GlobalValue::WinScale.Y + 8.0f, RenderDepth::ui });
	HP_Bar->SetSprite("HP_Bar.png");

	Bar_Name = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Bar_Name->SetText("돋움", "윈드브레이커", 13.0f, float4::WHITE, FW1_CENTER);
	Bar_Name->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 15.0f, -GlobalValue::WinScale.Y + 74.0f, RenderDepth::ui });

	CurHPScale = static_cast<float>(Player::MainPlayer->HP);
	HP->SetImageScale({ 171.0f * (CurHPScale * 0.01f), 13, 1 });
	CurMPScale = static_cast<float>(Player::MainPlayer->MP);
	MP->SetImageScale({ 171.0f * (CurMPScale * 0.01f), 13, 1 });
}

void PlayerUIManager::LevelEnd(class GameEngineLevel* _NextLevel)
{

}

void PlayerUIManager::Start()
{

}

void PlayerUIManager::Update(float _Delta)
{
	if (0 > Player::MainPlayer->HP)
	{
		Player::MainPlayer->HP = 0;
	}

	if (0 > Player::MainPlayer->MP)
	{
		Player::MainPlayer->MP = 0;
	}

	PlayerStatusUpdate(_Delta);
}

void PlayerUIManager::PlayerStatusUpdate(float _Delta)
{
	float PlayerHP = static_cast<float>(Player::MainPlayer->HP);
	if (PlayerHP < CurHPScale)
	{
		CurHPScale -= ReflectDownSpeed * _Delta;
		if (PlayerHP > CurHPScale)
		{
			CurHPScale = PlayerHP;
		}
	}
	else if (PlayerHP > CurHPScale)
	{
		CurHPScale += ReflectUpSpeed * _Delta;
		if (PlayerHP < CurHPScale)
		{
			CurHPScale = PlayerHP;
		}
	}
	HP->SetImageScale({ 171.0f * (CurHPScale * 0.01f), 13, 1 });

	float PlayerMP = static_cast<float>(Player::MainPlayer->MP);
	if (PlayerMP < CurMPScale)
	{
		CurMPScale -= ReflectDownSpeed * _Delta;
		if (PlayerMP > CurMPScale)
		{
			CurMPScale = PlayerMP;
		}
	}
	else if (PlayerMP > CurMPScale)
	{
		CurMPScale += ReflectUpSpeed * _Delta;
		if (PlayerMP < CurMPScale)
		{
			CurMPScale = PlayerMP;
		}
	}
	MP->SetImageScale({ 171.0f * (CurMPScale * 0.01f), 13, 1 });
}
