#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "HitRenderManager.h"
#include "ContentActor.h"
#include "Player.h"
#include "BaseWindActor.h"
#include "DamageSkinManager.h"
#include "DamageSkinRenderer.h"

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
	if (0 > _HitCount)
	{
		MsgBoxAssert("히트 카운트가 잘못입력되었습니다.");
		return;
	}

	if (nullptr == _Object)
	{
		MsgBoxAssert("존재하지 않는 오브젝트입니다.");
		return;
	}

	ContentBaseActor* _BaseActor = dynamic_cast<ContentBaseActor*>(_Object);
	if (nullptr == _BaseActor)
	{
		MsgBoxAssert("잘못된 Object가 들어왔습니다.");
		return;
	}

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

	if ("" == _HitSpriteName)
	{
		return;
	}

	GameEngineRandom RandomActor;
	std::shared_ptr<HitRenderData> _Data = std::make_shared<HitRenderData>();
	_Data->HitSpriteName = _HitSpriteName;
	_Data->Object = _BaseActor;
	_Data->HitAnimations.resize(_HitCount);
	_Data->RandomPivot.resize(_HitCount);
	_Data->DamageSkinRenderers.resize(_HitCount);

	for (int i = 0; i < _HitCount; i++)
	{
		/// Hit Ani
		std::shared_ptr<GameEngineSpriteRenderer> _HitAnimation = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::HITANI);

		RandomActor.SetSeed(reinterpret_cast<long long>(_BaseActor) + time(nullptr) + i);
		if (true == _RandomPivot)
		{
			float4 RandomValue = RandomActor.RandomVectorBox2D(-RANDOMRANGE, RANDOMRANGE, -RANDOMRANGE, RANDOMRANGE);
			_Data->RandomPivot[i].X = RandomValue.X;
			_Data->RandomPivot[i].Y = RandomValue.Y;
		}

		_HitAnimation->CreateAnimation("Hit", _HitSpriteName, HIT_ANI_TIME);
		_HitAnimation->ChangeAnimation("Hit");
		float4 Pos = _BaseActor->Transform.GetWorldPosition() + _Data->RandomPivot[i];
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

		if (nullptr != GameEngineSound::FindSound(_Data->HitSpriteName + ".mp3"))
		{
			_Data->HitSoundPlayers.resize(_HitCount);
			_Data->HitSoundPlayers[i] = GameEngineSound::SoundPlay(_Data->HitSpriteName + ".mp3");
			_Data->HitSoundPlayers[i].SetVolume(GlobalValue::HitVolume);
			_Data->HitSoundPlayers[i].Pause();
		}

		/// DamageSkin
		 Player* _PlayerObject = dynamic_cast<Player*>(_BaseActor);
		if (nullptr != _PlayerObject)
		{
			_Data->IsPlayer = true;

			continue;
		}

		int RandomDamage = RandomActor.RandomInt(10000000, 99999999);
		_Data->DamageSkinRenderers[i] = DamageSkinManager::MainDamageSkinManager->CreateDamageSkin(_BaseActor, RandomDamage);
		_Data->DamageSkinRenderers[i]->Transform.AddLocalPosition({0, 25.0f * i});
		_Data->DamageSkinRenderers[i]->Off();

		if (0 == _BaseActor->GetHP())
		{
			continue;
		}

		float RandomFloat = RandomActor.RandomFloat(0.0f, 1.0f);
		if (0.5f < RandomFloat)
		{
			continue;
		}
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
			if (false == _CurData->IsPlayer)
			{
				_CurData->DamageSkinRenderers[_CurData->CurIndex]->On();
			}
			if (0 != _CurData->HitSoundPlayers.size())
			{
				_CurData->HitSoundPlayers[_CurData->CurIndex].Resume();
			}

			_CurData->CurIndex += 1;
			_CurData->DelayTime = HIT_DELAY;
		}
		++StartIter;
	}
}