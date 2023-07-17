#pragma once
#include <random>

// 없을리가 없어.
// 내가 만드는 최후의 수단.
// 누가가지고 있지?
// std 헤더와 코드들

// std <= 최종 인정
// tr1 <= 인정 직전
// tr2 <= 인정 중
// boost <= 아무나 막올려.

// 난수알고리즘의 종류 
// 메르센트위스터
// well512 1024

// window 헤더와 코드들
// window에 random
// window and directx

// unreal
// unity

// 설명 :
class GameEngineRandom
{
public:
	// static 남발하게 되면 절대로 안지워지고 프로그램과 함께하는 메모리가 되어버립니다.

	// constrcuter destructer
	GameEngineRandom();
	GameEngineRandom(int _Seed);
	~GameEngineRandom();

	// delete Function
	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _Other) noexcept = delete;

	int RandomInt(int _Min, int _Max);

	float RandomFloat(float _Min, float _Max);

	void SetSeed(__int64 _Seed) 
	{
		MtGen = std::mt19937_64(_Seed);
	}

protected:

private:
	std::mt19937_64 MtGen = std::mt19937_64(time(nullptr));
	// int Seed = 0;

};

