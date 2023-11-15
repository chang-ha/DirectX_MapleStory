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

	if (nullptr == GameEngineSprite::Find("PlayerBarNum_0.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\PlayerBarNum");
		std::vector<GameEngineFile> Directorys = Dir.GetAllFile();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineFile& ChildFile = Directorys[i];
			GameEngineTexture::Load(ChildFile.GetStringPath());
			GameEngineSprite::CreateSingle(ChildFile.GetFileName());
		}
	}

	EXP_Bar = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	EXP_Bar->SetPivotType(PivotType::Bottom);
	EXP_Bar->Transform.SetLocalPosition({ GlobalValue::WinScale.hX(), -GlobalValue::WinScale.Y, RenderDepth::ui });
	EXP_Bar->SetSprite("EXP_Bar.png");

	HP_Bar_BG = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	HP_Bar_BG->SetPivotType(PivotType::Bottom);
	HP_Bar_BG->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 9.0f, -GlobalValue::WinScale.Y + 19.0f, RenderDepth::ui });
	HP_Bar_BG->SetSprite("HP_Bar_BG.png");
	HP_Bar_BG->SetImageScale({ 173, 32, 1 });

	HP.Bar = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	HP.Bar->SetPivotType(PivotType::LeftBottom);
	HP.Bar->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 76.0f, -GlobalValue::WinScale.Y + 37.0f, RenderDepth::ui });
	HP.Bar->SetSprite("HP.png");

	MP.Bar = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MP.Bar->SetPivotType(PivotType::LeftBottom);
	MP.Bar->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 76.0f, -GlobalValue::WinScale.Y + 21.0f, RenderDepth::ui });
	MP.Bar->SetSprite("MP.png");

	HP_Bar = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	HP_Bar->SetPivotType(PivotType::Bottom);
	HP_Bar->Transform.SetLocalPosition({ GlobalValue::WinScale.hX(), -GlobalValue::WinScale.Y + 8.0f, RenderDepth::ui });
	HP_Bar->SetSprite("HP_Bar.png");

	Bar_Name = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Bar_Name->SetText("돋움", "윈드브레이커", 13.0f, float4::WHITE, FW1_CENTER);
	Bar_Name->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 15.0f, -GlobalValue::WinScale.Y + 74.0f, RenderDepth::ui });

	HP.Slash = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	HP.Slash->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 7.0f, -GlobalValue::WinScale.Y + 43.0f, RenderDepth::ui });
	HP.Slash->SetSprite("PlayerBarNum_S.png");

	HP.MaxStatus_Hund = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	HP.MaxStatus_Hund->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 17.0f, -GlobalValue::WinScale.Y + 43.0f, RenderDepth::ui });
	HP.MaxStatus_Hund->SetSprite("PlayerBarNum_1.png");

	HP.MaxStatus_Ten = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	HP.MaxStatus_Ten->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 27.0f, -GlobalValue::WinScale.Y + 43.0f, RenderDepth::ui });
	HP.MaxStatus_Ten->SetSprite("PlayerBarNum_0.png");

	HP.MaxStatus_One = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	HP.MaxStatus_One->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 37.0f, -GlobalValue::WinScale.Y + 43.0f, RenderDepth::ui });
	HP.MaxStatus_One->SetSprite("PlayerBarNum_0.png");

	HP.CurStatus_Hund = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	HP.CurStatus_Hund->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 23.0f, -GlobalValue::WinScale.Y + 43.0f, RenderDepth::ui });

	HP.CurStatus_Ten = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	HP.CurStatus_Ten->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 13.0f, -GlobalValue::WinScale.Y + 43.0f, RenderDepth::ui });

	HP.CurStatus_One = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	HP.CurStatus_One->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 3.0f, -GlobalValue::WinScale.Y + 43.0f, RenderDepth::ui });

	MP.Slash = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MP.Slash->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 7.0f, -GlobalValue::WinScale.Y + 27.0f, RenderDepth::ui });
	MP.Slash->SetSprite("PlayerBarNum_S.png");

	MP.MaxStatus_Hund = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MP.MaxStatus_Hund->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 17.0f, -GlobalValue::WinScale.Y + 27.0f, RenderDepth::ui });
	MP.MaxStatus_Hund->SetSprite("PlayerBarNum_1.png");

	MP.MaxStatus_Ten = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MP.MaxStatus_Ten->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 27.0f, -GlobalValue::WinScale.Y + 27.0f, RenderDepth::ui });
	MP.MaxStatus_Ten->SetSprite("PlayerBarNum_0.png");

	MP.MaxStatus_One = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MP.MaxStatus_One->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 37.0f, -GlobalValue::WinScale.Y + 27.0f, RenderDepth::ui });
	MP.MaxStatus_One->SetSprite("PlayerBarNum_0.png");

	MP.CurStatus_Hund = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MP.CurStatus_Hund->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 23.0f, -GlobalValue::WinScale.Y + 27.0f, RenderDepth::ui });

	MP.CurStatus_Ten = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MP.CurStatus_Ten->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 13.0f, -GlobalValue::WinScale.Y + 27.0f, RenderDepth::ui });

	MP.CurStatus_One = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	MP.CurStatus_One->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 3.0f, -GlobalValue::WinScale.Y + 27.0f, RenderDepth::ui });

	NumUpdate(HP, Player::MainPlayer->HP);
	NumUpdate(MP, Player::MainPlayer->MP);

	CurHPScale = static_cast<float>(Player::MainPlayer->HP);
	HP.Bar->SetImageScale({ 171.0f * (CurHPScale * 0.01f), 13, 1 });
	CurMPScale = static_cast<float>(Player::MainPlayer->MP);
	MP.Bar->SetImageScale({ 171.0f * (CurMPScale * 0.01f), 13, 1 });
}

void PlayerUIManager::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
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

void PlayerUIManager::Release()
{
	if (nullptr != EXP_Bar)
	{
		EXP_Bar->Death();
		EXP_Bar = nullptr;
	}

	if (nullptr != HP_Bar)
	{
		HP_Bar->Death();
		HP_Bar = nullptr;
	}

	if (nullptr != HP_Bar_BG)
	{
		HP_Bar_BG->Death();
		HP_Bar_BG = nullptr;
	}

	if (nullptr != HP.Bar)
	{
		HP.Bar->Death();
		HP.Bar = nullptr;

		HP.Slash->Death();
		HP.Slash = nullptr;

		HP.CurStatus_Hund->Death();
		HP.CurStatus_Hund = nullptr;

		HP.CurStatus_Ten->Death();
		HP.CurStatus_Ten = nullptr;

		HP.CurStatus_One->Death();
		HP.CurStatus_One = nullptr;

		HP.MaxStatus_Hund->Death();
		HP.MaxStatus_Hund = nullptr;

		HP.MaxStatus_Ten->Death();
		HP.MaxStatus_Ten = nullptr;

		HP.MaxStatus_One->Death();
		HP.MaxStatus_One = nullptr;
	}

	if (nullptr != MP.Bar)
	{
		MP.Bar->Death();
		MP.Bar = nullptr;
	}

	if (nullptr != Bar_Name)
	{
		Bar_Name->Death();
		Bar_Name = nullptr;
	}
}

void PlayerUIManager::PlayerStatusUpdate(float _Delta)
{
	HPUpdate(_Delta);
	MPUpdate(_Delta);
}

void PlayerUIManager::HPUpdate(float _Delta)
{
	int PlayerHPInt = Player::MainPlayer->HP;
	// HpBar Scale
	float PlayerHP = static_cast<float>(PlayerHPInt);
	if (PlayerHP == CurHPScale)
	{
		return;
	}

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
	HP.Bar->SetImageScale({ 171.0f * (CurHPScale * 0.01f), 13, 1 });

	// HpNum
	NumUpdate(HP, PlayerHPInt);
}

void PlayerUIManager::MPUpdate(float _Delta)
{
	int PlayerMPInt = Player::MainPlayer->MP;
	// MpBar Scale
	float PlayerMP = static_cast<float>(PlayerMPInt);
	if (PlayerMP == CurMPScale)
	{
		return;
	}

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
	MP.Bar->SetImageScale({ 171.0f * (CurMPScale * 0.01f), 13, 1 });

	// MpNum
	NumUpdate(MP, PlayerMPInt);
}

void PlayerUIManager::NumUpdate(BarFrame _Bar, int PlayerStateValue)
{
	int HundNum = PlayerStateValue / 100;
	if (0 == HundNum)
	{
		_Bar.CurStatus_Hund->Off();
	}
	else
	{
		_Bar.CurStatus_Hund->On();
		_Bar.CurStatus_Hund->SetSprite("PlayerBarNum_" + std::to_string(HundNum) + ".png");
	}

	int TenNum = (PlayerStateValue / 10) % 10;
	if (0 == HundNum && 0 == TenNum)
	{
		_Bar.CurStatus_Ten->Off();
	}
	else
	{
		_Bar.CurStatus_Ten->On();
		_Bar.CurStatus_Ten->SetSprite("PlayerBarNum_" + std::to_string(TenNum) + ".png");
	}

	int OneNum = PlayerStateValue % 10;
	_Bar.CurStatus_One->SetSprite("PlayerBarNum_" + std::to_string(OneNum) + ".png");
}
