#pragma once
#include <random>

// �������� ����.
// ���� ����� ������ ����.
// ���������� ����?
// std ����� �ڵ��

// std <= ���� ����
// tr1 <= ���� ����
// tr2 <= ���� ��
// boost <= �ƹ��� ���÷�.

// �����˰����� ���� 
// �޸���Ʈ������
// well512 1024

// window ����� �ڵ��
// window�� random
// window and directx

// unreal
// unity

// ���� :
class GameEngineRandom
{
public:
	// static �����ϰ� �Ǹ� ����� ���������� ���α׷��� �Բ��ϴ� �޸𸮰� �Ǿ�����ϴ�.

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

