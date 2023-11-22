#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "HitRenderManager.h"
#include "ContentActor.h"
#include "Player.h"
#include "BaseWindActor.h"

#define HIT_ANI_TIME 0.04f
#define HIT_DELAY 0.12f
#define RANDOMRANGE 30

HitRenderManager* HitRenderManager::MainHitRenderManager;

HitRenderManager::HitRenderManager()
{

}

HitRenderManager::~HitRenderManager()
{

}

void HitRenderManager::LevelStart(GameEngineLevel* _PrevLevel)
{
	MainHitRenderManager = this;
}

void HitRenderManager::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void HitRenderManager::Start()
{
	
}

void HitRenderManager::Update(float _Delta)
{
	HitPrintUpdate(_Delta);
}

void HitRenderManager::HitPrint(std::string_view _HitSpriteName, int _HitCount, GameEngineObject* _Object, int _Damage, bool _RandomPivot /*= true*/, PivotType _PivotType /*= PivotType::Bottom*/)
{
	if ("" == _HitSpriteName)
	{
		ContentBaseActor* _BaseActor = dynamic_cast<ContentBaseActor*>(_Object);
		if (nullptr != _BaseActor)
		{
			if (-1 == _Damage)
			{
				_BaseActor->AddHP(-_HitCount);
			}
			else
			{
				_BaseActor->AddHP(-_Damage);
			}
		}
		return;
	}

	GameEngineRandom RandomActor;
	std::shared_ptr<HitRenderData> _Data = std::make_shared<HitRenderData>();
	_Data->HitSpriteName = _HitSpriteName;
	_Data->Object = _Object;
	_Data->HitAnimations.resize(_HitCount);
	_Data->RandomPivot.resize(_HitCount);
	// _Data.DamageAnimations.resize(_HitCount);

	for (int i = 0; i < _HitCount; i++)
	{
		std::shared_ptr<GameEngineSpriteRenderer> _HitAnimation = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::HITANI);

		if (true == _RandomPivot)
		{
			RandomActor.SetSeed(reinterpret_cast<long long>(_Object) + time(nullptr) + i);
			float4 RandomValue = RandomActor.RandomVectorBox2D(-RANDOMRANGE, RANDOMRANGE, -RANDOMRANGE, RANDOMRANGE);
			_Data->RandomPivot[i].X = RandomValue.X;
			_Data->RandomPivot[i].Y = RandomValue.Y;
		}

		_HitAnimation->CreateAnimation("Hit", _HitSpriteName, HIT_ANI_TIME);
		_HitAnimation->ChangeAnimation("Hit");
		float4 Pos = _Object->Transform.GetWorldPosition() + _Data->RandomPivot[i];
		Pos.Z = RenderDepth::hitani;
		_HitAnimation->Transform.SetLocalPosition(Pos);
		_HitAnimation->AutoSpriteSizeOn();
		_HitAnimation->SetEndEvent("Hit", [&](GameEngineSpriteRenderer* _Renderer)
			{
				_Renderer->Off();
				_Renderer->Death();
			}
		);
		_HitAnimation->Off();
		_HitAnimation->SetPivotType(_PivotType);

		_Data->HitAnimations[i] = _HitAnimation;
	}
	
	ContentBaseActor* _BaseActor = dynamic_cast<ContentBaseActor*>(_Object);
	if (nullptr != _BaseActor)
	{
		if (-1 == _Damage)
		{
			_BaseActor->AddHP(-_HitCount);
		}
		else
		{
			_BaseActor->AddHP(-_Damage);
		}
	}

	Player* _Player = dynamic_cast<Player*>(_Object);
	if (nullptr == _Player)
	{
		BaseWindActor::CreateTriflingWind();
	}

	AllHitRenderers.push_back(_Data);
}

void HitRenderManager::HitPrintUpdate(float _Delta)
{
	std::list<std::shared_ptr<HitRenderData>>::iterator StartIter = AllHitRenderers.begin();
	std::list<std::shared_ptr<HitRenderData>>::iterator EndIter = AllHitRenderers.end();

	for (; StartIter != EndIter;)
	{
		std::shared_ptr<HitRenderData> _CurData = (*StartIter);
		if (_CurData->HitAnimations.size() == _CurData->CurIndex)
		{
			if (true == _CurData->HitAnimations[_CurData->CurIndex - 1]->IsCurAnimationEnd())
			{
				_CurData->Object = nullptr;
				StartIter = AllHitRenderers.erase(StartIter);
				continue;
			}
			++StartIter;
			continue;
		}

		_CurData->DelayTime -= _Delta;
		if (0.0f >= _CurData->DelayTime)
		{
			_CurData->HitAnimations[_CurData->CurIndex]->On();
			_CurData->HitAnimations[_CurData->CurIndex]->GetColorData().MulColor.A = GlobalValue::SkillEffectAlpha;
			_CurData->CurIndex += 1;
			_CurData->DelayTime = HIT_DELAY;

			if (nullptr != GameEngineSound::FindSound(_CurData->HitSpriteName + ".mp3"))
			{
				GameEngineSoundPlayer HitSound = GameEngineSound::SoundPlay(_CurData->HitSpriteName + ".mp3");
				HitSound.SetVolume(GlobalValue::HitVolume);
			}
		}
		++StartIter;
	}
}