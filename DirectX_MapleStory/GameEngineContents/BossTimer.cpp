#include "PreCompile.h"
#include "BossTimer.h"

float BossTimer::TimeValue = 0.0f;

BossTimer::BossTimer()
{

}

BossTimer::~BossTimer()
{

}

void BossTimer::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void BossTimer::Start()
{
	if (nullptr == GameEngineSprite::Find("Boss_TimerFrame.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\BossTimer");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& Childs = Files[i];
			GameEngineTexture::Load(Childs.GetStringPath());
			GameEngineSprite::CreateSingle(Childs.GetFileName());
		}
	}

	if (nullptr == Frame.TimerFrame)
	{
		Frame.TimerFrame = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	}

	if (nullptr == Frame.TimerNum1)
	{
		Frame.TimerNum1 = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	}

	if (nullptr == Frame.TimerNum2)
	{
		Frame.TimerNum2 = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	}

	if (nullptr == Frame.TimerNum3)
	{
		Frame.TimerNum3 = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	}

	if (nullptr == Frame.TimerNum4)
	{
		Frame.TimerNum4 = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	}

	Frame.TimerFrame->AutoSpriteSizeOn();

	Frame.TimerFrame->SetSprite("Boss_TimerFrame.png");
	Frame.TimerNum1->SetSprite("Boss_TimeNum_3.png");
	Frame.TimerNum2->SetSprite("Boss_TimeNum_0.png");
	Frame.TimerNum3->SetSprite("Boss_TimeNum_0.png");
	Frame.TimerNum4->SetSprite("Boss_TimeNum_0.png");

	Frame.TimerNum1->SetImageScale({ 18, 30 });
	Frame.TimerNum2->SetImageScale({ 18, 30 });
	Frame.TimerNum3->SetImageScale({ 18, 30 });
	Frame.TimerNum4->SetImageScale({ 18, 30 });

	Frame.TimerFrame->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 10, -75.0f, RenderDepth::ui});
	Frame.TimerNum1->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 28, -75.0f, RenderDepth::ui });
	Frame.TimerNum2->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 3, -75.0f, RenderDepth::ui });
	Frame.TimerNum3->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 39, -75.0f, RenderDepth::ui });
	Frame.TimerNum4->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 64, -75.0f, RenderDepth::ui});
}

void BossTimer::Update(float _Delta)
{
	if (0.0f == TimeValue)
	{
		return;
	}
	else if (0.0f > TimeValue)
	{
		TimeValue = 0.0f;
	}

	TimeValue -= _Delta;
	CalcuRemainTime();
}

void BossTimer::Release()
{
	if (nullptr != Frame.TimerFrame)
	{
		Frame.TimerFrame->Death();
		Frame.TimerFrame = nullptr;

		Frame.TimerNum1->Death();
		Frame.TimerNum1 = nullptr;

		Frame.TimerNum2->Death();
		Frame.TimerNum2 = nullptr;

		Frame.TimerNum3->Death();
		Frame.TimerNum3 = nullptr;

		Frame.TimerNum4->Death();
		Frame.TimerNum4 = nullptr;
	}

	if (nullptr != GameEngineSprite::Find("Boss_TimerFrame.png"))
	{
		GameEngineTexture::Release("Boss_TimerFrame.png");
		GameEngineSprite::Release("Boss_TimerFrame.png");

		for (size_t i = 0; i < 10; i++)
		{
			GameEngineTexture::Release("Boss_TimeNum_" + std::to_string(i) + ".png");
			GameEngineSprite::Release("Boss_TimeNum_" + std::to_string(i) + ".png");
		}
	}
}

void BossTimer::CalcuRemainTime()
{
	int Minute = static_cast<int>(TimeValue) / 60;
	int Second = static_cast<int>(TimeValue) % 60;

  	if (PrevTenMinute != Minute / 10)
	{
		PrevTenMinute = Minute / 10;
		Frame.TimerNum1->SetSprite("Boss_TimeNum_" + std::to_string(PrevTenMinute) + ".png");
		Frame.TimerNum1->SetImageScale({ 18, 30 });
	}

	if (PrevOneMinute != Minute % 10)
	{
		PrevOneMinute = Minute % 10;
		Frame.TimerNum2->SetSprite("Boss_TimeNum_" + std::to_string(PrevOneMinute) + ".png");
		Frame.TimerNum2->SetImageScale({ 18, 30 });
	}

	if (PrevTenSecond != Second / 10)
	{
		PrevTenSecond = Second / 10;
		Frame.TimerNum3->SetSprite("Boss_TimeNum_" + std::to_string(PrevTenSecond) + ".png");
		Frame.TimerNum3->SetImageScale({ 18, 30 });
	}

	Frame.TimerNum4->SetSprite("Boss_TimeNum_" + std::to_string(Second % 10) + ".png");
	Frame.TimerNum4->SetImageScale({ 18, 30 });
}